#include "dos16/pcm.h"
#include <conio.h>
#include <dos.h>
#include "dos16/pcm_machine.h"
#ifdef MYGAMES_DOS16_PCM_DIAGNOSTICS
extern void mygames_pcm_irq_probe(int stage);
extern int mygames_pcm_port_in(unsigned port);
#define inp mygames_pcm_port_in
#endif

enum { MYGAMES_DOS16_PCM_DMA_PARAGRAPHS=256U };
static struct mygames_dos16_pcm_state audio;
static unsigned short audio_segment;
static unsigned long audio_physical;
static unsigned char far *audio_memory;
static unsigned char time_constant;
static unsigned long completion_budget;
static volatile unsigned char block_free[MYGAMES_DOS16_PCM_BLOCK_COUNT];
static volatile unsigned char block_ready[MYGAMES_DOS16_PCM_BLOCK_COUNT];
static volatile unsigned char active_block,playing,vector_ready,pic_ready;
static mygames_kvm_u8 old_master_mask,old_slave_mask;
static unsigned char fill_block=0xffU;
static unsigned short fill_count;
static void (interrupt far *old_audio_vector)();
enum { DSP_FOREGROUND_BUDGET=512U,DSP_IRQ_BUDGET=128U };
static volatile unsigned char fault,suspended;
static volatile unsigned short progress;
static unsigned short observed;
static unsigned long progress_stamp;
static int watching,closing,reset_pending;
static int dsp_write(mygames_kvm_u8 value,unsigned short *budget);
static void dma_mask(mygames_kvm_u8 mask);
static int stop_playback(void);

static void pic_enable_irq(void)
{
    old_master_mask=(mygames_kvm_u8)inp(0x21U);
    old_slave_mask=(mygames_kvm_u8)inp(0xa1U);
    if(audio.config.irq<8U)
        outp(0x21U,(unsigned int)(old_master_mask&~(1U<<audio.config.irq)));
    else {
        outp(0xa1U,(unsigned int)(old_slave_mask&~(1U<<(audio.config.irq-8U))));
        /* Every slave IRQ reaches the master through cascade IRQ2. */
        outp(0x21U,(unsigned int)(old_master_mask&~4U));
    }
    pic_ready=1U;
}

static void pic_restore(void)
{
    unsigned short bit;
    if(!pic_ready)return;
    if(audio.config.irq<8U) {
        bit=1U<<audio.config.irq;
        outp(0x21U,(inp(0x21U)&~bit)|(old_master_mask&bit));
    } else {
        bit=1U<<(audio.config.irq-8U);
        outp(0xa1U,(inp(0xa1U)&~bit)|(old_slave_mask&bit));
        outp(0x21U,(inp(0x21U)&~4U)|(old_master_mask&4U));
    }
    pic_ready=0U;
}

static void dsp_delay(void)
{
    unsigned short index;
    for(index=0U;index<32U;++index)(void)inp(0x80U);
}

static int dsp_probe(void *context,const struct mygames_dos16_pcm_config *config)
{
    unsigned short attempt;
    (void)context;
    outp((unsigned int)(config->base_port+6U),1);dsp_delay();
    outp((unsigned int)(config->base_port+6U),0);
    for(attempt=0U;attempt<1024U;++attempt) {
        if((inp((unsigned int)(config->base_port+14U))&0x80)!=0 &&
            (unsigned char)inp((unsigned int)(config->base_port+10U))==0xaaU)return 1;
    }
    return 0;
}

static int dma_reserve(void *context,const struct mygames_dos16_pcm_config *config)
{
    unsigned long index;
    (void)context;(void)config;
    if(audio_segment)return 0;
    if(_dos_allocmem(MYGAMES_DOS16_PCM_DMA_PARAGRAPHS,&audio_segment)!=0)return 0;
    audio_physical=(unsigned long)audio_segment<<4U;
    /* An ISA 8-bit DMA block may not cross a 64KiB physical boundary. */
    if((audio_physical&0xffffUL)>0xf000UL) {
        _dos_freemem(audio_segment);audio_segment=0U;return 0;
    }
    audio_memory=pcm_segment(audio_segment);
    for(index=0UL;index<MYGAMES_DOS16_PCM_BLOCK_BYTES*MYGAMES_DOS16_PCM_BLOCK_COUNT;++index)
        audio_memory[index]=128U;
    block_free[0]=block_free[1]=1U;block_ready[0]=block_ready[1]=0U;
    fill_block=0xffU;fill_count=0U;playing=0U;vector_ready=0U;pic_ready=0U;
    progress=observed=0;watching=0;suspended=0;
    return 1;
}

static void dma_release(void *context)
{
    (void)context;
    if(audio_segment)_dos_freemem(audio_segment);
    audio_segment=0U;audio_memory=0;audio_physical=0UL;
}

static const struct mygames_dos16_pcm_ops hardware_ops={dsp_probe,dma_reserve,dma_release};

int mygames_dos16_pcm_dos_open(unsigned short rate)
{
    char blaster[128];
    if(rate<4000U || rate>22050U)return 0;
    /* Keep direct callers idempotent too; devices_open normally invokes this
     * once, but a failed host restart must never strand the reserved block. */
    if(!mygames_dos16_pcm_dos_close())return 0;
    time_constant=(mygames_kvm_u8)(256U-1000000UL/rate);
    completion_budget=(MYGAMES_DOS16_PCM_BLOCK_BYTES*1193182UL)/rate+596591UL;
    mygames_dos16_pcm_initialize(&audio);
    if(!current_blaster(blaster,sizeof(blaster)))return 0;
    return mygames_dos16_pcm_open(&audio,blaster,&hardware_ops,0);
}

int mygames_dos16_pcm_dos_close(void)
{
    closing=1;reset_pending=0;
    if(!stop_playback())return 0;
    mygames_dos16_pcm_close(&audio);fault=0;watching=closing=0;return 1;
}

void mygames_dos16_pcm_dos_reset(void)
{
    unsigned long index;
    /* Loading is a device reset boundary.  Never leave the DMA controller or
     * DSP referring to a buffer while the generic lifecycle re-probes it. */
    reset_pending=1;
    if(!stop_playback())return;
    reset_pending=0;
    if(!mygames_dos16_pcm_reprobe(&audio))return;
    for(index=0UL;audio_memory && index<MYGAMES_DOS16_PCM_BLOCK_BYTES*MYGAMES_DOS16_PCM_BLOCK_COUNT;++index)
        audio_memory[index]=128U;
    block_free[0]=block_free[1]=1U;block_ready[0]=block_ready[1]=0U;
    fill_block=0xffU;fill_count=0U;suspended=0;watching=0;
}

int mygames_dos16_pcm_dos_prepared(void)
{ return audio.ready!=0U && !suspended && !closing && !reset_pending && !fault; }

static int dsp_write(mygames_kvm_u8 value,unsigned short *budget)
{
    while(*budget) {
        --*budget;
        if((inp((unsigned int)(audio.config.base_port+12U))&0x80)==0) {
            outp((unsigned int)(audio.config.base_port+12U),value);return 1;
        }
    }
    return 0;
}

static void dma_mask(mygames_kvm_u8 mask)
{ outp(0x0aU,(unsigned int)(mask|(audio.config.dma_channel&3U))); }

static void latch_fault(unsigned char code)
{dma_mask(4U);audio.ready=0U;fault=code;playing=0U;}

static int irq_pending(void)
{
    unsigned port=audio.config.irq<8U?0x20U:0xa0U;
    outp(port,0x0aU);
    return (inp(port)&(1U<<(audio.config.irq&7U)))!=0;
}
static int stop_playback(void)
{
    unsigned short flags,budget=DSP_FOREGROUND_BUDGET;
    if(!audio_segment)return 1;
    flags=pcm_irq_save();suspended=1;dma_mask(4U);playing=0;
    /* Leave this owner's ISR installed while an already latched edge drains.
     * No PIC poll command: it is unsupported by ordinary DOSBox. */
    pcm_irq_restore(flags);
    (void)dsp_write(0xd0U,&budget);(void)dsp_write(0xd3U,&budget);
    flags=pcm_irq_save();
    (void)inp((unsigned int)(audio.config.base_port+14U));
    if(vector_ready && irq_pending()) {
        /* With incoming IF clear we must not enable it. Main service completes
         * cleanup later; DMA is masked and its storage/vector remain owned. */
        pcm_irq_restore(flags);return 0;
    }
    if(vector_ready) {
        _dos_setvect((unsigned)(audio.config.irq<8U?audio.config.irq+8U:audio.config.irq+0x68U),old_audio_vector);
        vector_ready=0;
    }
    pic_restore();pcm_irq_restore(flags);return 1;
}

static void dma_program(mygames_kvm_u8 block)
{
    static const unsigned short address_port[4]={0x00U,0x02U,0x04U,0x06U};
    static const unsigned short count_port[4]={0x01U,0x03U,0x05U,0x07U};
    static const unsigned short page_port[4]={0x87U,0x83U,0x81U,0x82U};
    unsigned long address=audio_physical+(unsigned long)block*MYGAMES_DOS16_PCM_BLOCK_BYTES;
    unsigned short count=MYGAMES_DOS16_PCM_BLOCK_BYTES-1U;
    mygames_kvm_u8 channel=audio.config.dma_channel;
    dma_mask(4U);outp(0x0cU,0U);
    outp(address_port[channel],(unsigned int)(address&0xffUL));
    outp(address_port[channel],(unsigned int)((address>>8U)&0xffUL));
    outp(page_port[channel],(unsigned int)((address>>16U)&0xffUL));
    outp(count_port[channel],count&0xffU);outp(count_port[channel],count>>8U);
    /* memory-to-device, incrementing, single transfer */
    outp(0x0bU,(unsigned int)(0x44U|channel));dma_mask(0U);
}

static int start_block(mygames_kvm_u8 block,unsigned short budget)
{
    if(!dsp_write(0xd1U,&budget) || !dsp_write(0x40U,&budget) || !dsp_write(time_constant,&budget)){latch_fault(MYGAMES_DOS16_PCM_DSP_BUSY);return 0;}
    /* Program DMA before issuing the DSP transfer command: the DSP must
     * never consume the channel while its address/count registers are stale. */
    dma_program(block);
    if(!dsp_write(0x14U,&budget) || !dsp_write((mygames_kvm_u8)(MYGAMES_DOS16_PCM_BLOCK_BYTES-1U),&budget) ||
        !dsp_write(7U,&budget)) {
        latch_fault(MYGAMES_DOS16_PCM_DSP_BUSY);return 0;
    }
    active_block=block;playing=1U;++progress;return 1;
}

static void interrupt far audio_interrupt(void)
{
    mygames_kvm_u8 done,next;
#ifdef MYGAMES_DOS16_PCM_DIAGNOSTICS
    mygames_pcm_irq_probe(0);
#endif
    (void)inp((unsigned int)(audio.config.base_port+14U));
    if(playing && !suspended && !fault) {
        done=active_block;playing=0U;block_free[done]=1U;++progress;
        next=(mygames_kvm_u8)(done^1U);
        if(block_ready[next]) {
            block_ready[next]=0U;block_free[next]=0U;
            if(!start_block(next,DSP_IRQ_BUDGET))block_free[next]=1U;
        }
    }
    if(audio.config.irq>=8U)outp(0xa0U,0x20U);
    outp(0x20U,0x20U);
#ifdef MYGAMES_DOS16_PCM_DIAGNOSTICS
    mygames_pcm_irq_probe(playing?1:2);
#endif
}

static int ensure_playing(void)
{
    mygames_kvm_u8 block;
    if(playing)return 1;
    for(block=0U;block<MYGAMES_DOS16_PCM_BLOCK_COUNT;++block)if(block_ready[block]) {
        if(!vector_ready) {
            old_audio_vector=_dos_getvect((unsigned)(audio.config.irq<8U?audio.config.irq+8U:audio.config.irq+0x68U));
            _dos_setvect((unsigned)(audio.config.irq<8U?audio.config.irq+8U:audio.config.irq+0x68U),audio_interrupt);
            pic_enable_irq();
            vector_ready=1U;
        }
        block_ready[block]=0U;block_free[block]=0U;
        if(start_block(block,DSP_IRQ_BUDGET))return 1;
        block_free[block]=1U;return 0;
    }
    return 0;
}

mygames_kvm_u16 mygames_dos16_pcm_dos_submit(const mygames_kvm_u8 MYGAMES_KVM_FAR *samples,unsigned short count)
{
    unsigned short offset,copy,i,flags;mygames_kvm_u8 block;
    if(!audio.ready || !audio_memory || !samples)return 0U;
    if(!count)return 0U;
    offset=0U;
    while(offset<count) {
        flags=pcm_irq_save();
        if(!audio.ready || suspended){pcm_irq_restore(flags);return offset;}
        if(fill_block==0xffU) {
            for(block=0U;block<MYGAMES_DOS16_PCM_BLOCK_COUNT;++block)if(block_free[block])break;
            /* Report backpressure; the caller decides what to do with samples
             * that could not be queued. A prefix may already be committed. */
            if(block==MYGAMES_DOS16_PCM_BLOCK_COUNT){pcm_irq_restore(flags);return offset;}
            block_free[block]=0U;fill_block=block;fill_count=0U;
        }
        pcm_irq_restore(flags);
        copy=(unsigned short)(count-offset);
        if(copy>MYGAMES_DOS16_PCM_BLOCK_BYTES-fill_count)copy=(unsigned short)(MYGAMES_DOS16_PCM_BLOCK_BYTES-fill_count);
        for(i=0U;i<copy;++i)audio_memory[(unsigned long)fill_block*MYGAMES_DOS16_PCM_BLOCK_BYTES+fill_count+i]=samples[offset+i];
        offset=(unsigned short)(offset+copy);fill_count=(unsigned short)(fill_count+copy);
        flags=pcm_irq_save();
        if(fill_count==MYGAMES_DOS16_PCM_BLOCK_BYTES && audio.ready) {
            block=fill_block;block_ready[block]=1U;fill_block=0xffU;fill_count=0U;
            if(!ensure_playing()){pcm_irq_restore(flags);return offset;}
        }
        pcm_irq_restore(flags);
    }
    return offset;
}

int mygames_dos16_pcm_dos_phase(void)
{return closing?MYGAMES_AUDIO_STOPPING:reset_pending?MYGAMES_AUDIO_RESETTING:
    fault?MYGAMES_AUDIO_FAILED:audio.ready?MYGAMES_AUDIO_READY:MYGAMES_AUDIO_CLOSED;}
unsigned short mygames_dos16_pcm_dos_error(void){return fault;}
void mygames_dos16_pcm_dos_service(unsigned long now)
{
    unsigned short flags;
    unsigned long elapsed;
    flags=pcm_irq_save();
    if(!playing)watching=0;
    else if(!watching || observed!=progress){observed=progress;progress_stamp=now;watching=1;}
    else {
        elapsed=(now-progress_stamp)&0xffffffffUL;
        if(elapsed>0x7fffffffUL)progress_stamp=now; /* BIOS midnight/reset */
        else if(elapsed>completion_budget)latch_fault(MYGAMES_DOS16_PCM_LOST_IRQ);
    }
    pcm_irq_restore(flags);
    if(closing)(void)mygames_dos16_pcm_dos_close();
    else if(fault && audio.reserved){if(stop_playback())mygames_dos16_pcm_close(&audio);}
    else if(reset_pending)mygames_dos16_pcm_dos_reset();
}
