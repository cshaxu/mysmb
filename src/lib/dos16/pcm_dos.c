#include "dos16/pcm.h"
#include <conio.h>
#include <dos.h>

enum { MYGAMES_DOS16_PCM_DMA_PARAGRAPHS=256U };
static struct mygames_dos16_pcm_state audio;
static unsigned short audio_segment;
static unsigned long audio_physical;
static unsigned char far *audio_memory;
static unsigned short sample_rate;
static volatile unsigned char block_free[MYGAMES_DOS16_PCM_BLOCK_COUNT];
static volatile unsigned char block_ready[MYGAMES_DOS16_PCM_BLOCK_COUNT];
static volatile unsigned char active_block,playing,vector_ready,pic_ready;
static mygames_kvm_u8 old_master_mask,old_slave_mask;
static unsigned char fill_block=0xffU;
static unsigned short fill_count;
static void (interrupt far *old_audio_vector)();
static int dsp_write(mygames_kvm_u8 value);
static void dma_mask(mygames_kvm_u8 mask);
static void stop_playback(void);

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
    if(!pic_ready)return;
    outp(0x21U,old_master_mask);outp(0xa1U,old_slave_mask);pic_ready=0U;
}

/* The OpenNT DOS link policy rejects CRT environment startup helpers.  Query
 * DOS for this process's PSP, then copy only its BLASTER value into a bounded
 * near buffer before the portable parser sees it. */
static int current_blaster(char *target,unsigned short capacity)
{
    union REGS registers;
    union {
        struct { unsigned short offset,segment; } address;
        const char far *pointer;
    } psp_address,environment_address;
    const char far *environment;
    unsigned short environment_segment,offset=0U,write;
    static const char name[]="BLASTER=";
    registers.h.ah=0x62U;intdos(&registers,&registers);
    /* AH=62 returns the PSP segment, not the environment segment.  DOS keeps
     * the latter as a word at PSP:002Ch.  Scanning PSP:0000 used to make the
     * backend silently miss BLASTER on every normal DOS host. */
    psp_address.address.offset=0x2cU;
    psp_address.address.segment=registers.x.bx;
    environment_segment=*(const unsigned short far *)psp_address.pointer;
    if(!environment_segment)return 0;
    /* The OpenNT runtime exposes MK_FP as an unresolved CRT helper in this
     * model. Build the standard segment:offset far address directly. */
    environment_address.address.offset=0U;
    environment_address.address.segment=environment_segment;
    environment=environment_address.pointer;
    while(offset<65534U && environment[offset]) {
        unsigned short match=0U;
        while(name[match] && environment[(unsigned short)(offset+match)]==name[match])++match;
        if(!name[match]) {
            offset=(unsigned short)(offset+match);write=0U;
            while(environment[offset] && write+1U<capacity) {
                target[write++]=environment[offset++];
            }
            if(environment[offset])return 0;
            target[write]=0;return write!=0U;
        }
        while(offset<65534U && environment[offset])++offset;
        ++offset;
    }
    return 0;
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
    union { struct { unsigned short offset,segment; } address; unsigned char far *pointer; } pointer;
    unsigned long index;
    (void)context;(void)config;
    if(audio_segment)return 0;
    if(_dos_allocmem(MYGAMES_DOS16_PCM_DMA_PARAGRAPHS,&audio_segment)!=0)return 0;
    audio_physical=(unsigned long)audio_segment<<4U;
    /* An ISA 8-bit DMA block may not cross a 64KiB physical boundary. */
    if((audio_physical&0xffffUL)>0xf000UL) {
        _dos_freemem(audio_segment);audio_segment=0U;return 0;
    }
    pointer.address.offset=0U;pointer.address.segment=audio_segment;audio_memory=pointer.pointer;
    for(index=0UL;index<MYGAMES_DOS16_PCM_BLOCK_BYTES*MYGAMES_DOS16_PCM_BLOCK_COUNT;++index)
        audio_memory[index]=128U;
    block_free[0]=block_free[1]=1U;block_ready[0]=block_ready[1]=0U;
    fill_block=0xffU;fill_count=0U;playing=0U;vector_ready=0U;pic_ready=0U;
    return 1;
}

static void dma_release(void *context)
{
    (void)context;
    /* The terminal-count IRQ may already be pending when a caller closes the
     * device.  Keep the DSP/DMA shutdown and IVT restoration atomic so it
     * cannot arrive at the restored owner with audio state still live. */
    _disable();
    stop_playback();
    if(vector_ready)_dos_setvect((unsigned)(audio.config.irq<8U?audio.config.irq+8U:audio.config.irq+0x68U),old_audio_vector);
    vector_ready=0U;pic_restore();playing=0U;
    _enable();
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
    mygames_dos16_pcm_dos_close();
    sample_rate=rate;
    mygames_dos16_pcm_initialize(&audio);
    if(!current_blaster(blaster,sizeof(blaster)))return 0;
    return mygames_dos16_pcm_open(&audio,blaster,&hardware_ops,0);
}

void mygames_dos16_pcm_dos_close(void)
{ mygames_dos16_pcm_close(&audio); }

void mygames_dos16_pcm_dos_reset(void)
{
    unsigned long index;
    /* Loading is a device reset boundary.  Never leave the DMA controller or
     * DSP referring to a buffer while the generic lifecycle re-probes it. */
    _disable();
    stop_playback();
    _enable();
    if(!mygames_dos16_pcm_reprobe(&audio))return;
    for(index=0UL;audio_memory && index<MYGAMES_DOS16_PCM_BLOCK_BYTES*MYGAMES_DOS16_PCM_BLOCK_COUNT;++index)
        audio_memory[index]=128U;
    block_free[0]=block_free[1]=1U;block_ready[0]=block_ready[1]=0U;
    fill_block=0xffU;fill_count=0U;
}

int mygames_dos16_pcm_dos_prepared(void)
{ return audio.ready!=0U; }

static int dsp_write(mygames_kvm_u8 value)
{
    unsigned short attempt;
    for(attempt=0U;attempt<4096U;++attempt) {
        if((inp((unsigned int)(audio.config.base_port+12U))&0x80)==0) {
            outp((unsigned int)(audio.config.base_port+12U),value);return 1;
        }
    }
    return 0;
}

static void dma_mask(mygames_kvm_u8 mask)
{ outp(0x0aU,(unsigned int)(mask|(audio.config.dma_channel&3U))); }

static void stop_playback(void)
{
    if(!playing)return;
    dma_mask(4U);
    (void)dsp_write(0xd0U); /* halt DMA playback on DSP 2.x+ */
    (void)dsp_write(0xd3U); /* speaker off while no block is active */
    playing=0U;
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

static int start_block(mygames_kvm_u8 block)
{
    mygames_kvm_u8 time_constant=(mygames_kvm_u8)(256U-1000000UL/sample_rate);
    if(!dsp_write(0xd1U) || !dsp_write(0x40U) || !dsp_write(time_constant))return 0;
    /* Program DMA before issuing the DSP transfer command: the DSP must
     * never consume the channel while its address/count registers are stale. */
    dma_program(block);
    if(!dsp_write(0x14U) || !dsp_write((mygames_kvm_u8)(MYGAMES_DOS16_PCM_BLOCK_BYTES-1U)) ||
        !dsp_write(7U)) {
        dma_mask(4U);return 0;
    }
    active_block=block;playing=1U;return 1;
}

static void interrupt far audio_interrupt(void)
{
    mygames_kvm_u8 done,next;
    (void)inp((unsigned int)(audio.config.base_port+14U));
    done=active_block;playing=0U;block_free[done]=1U;
    next=(mygames_kvm_u8)(done^1U);
    if(block_ready[next]) {
        block_ready[next]=0U;block_free[next]=0U;
        if(!start_block(next))block_free[next]=1U;
    }
    if(audio.config.irq>=8U)outp(0xa0U,0x20U);
    outp(0x20U,0x20U);
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
        if(start_block(block))return 1;
        block_free[block]=1U;
    }
    return 0;
}

mygames_kvm_u8 mygames_dos16_pcm_dos_submit(const mygames_kvm_u8 MYGAMES_KVM_FAR *samples,unsigned short count)
{
    unsigned short offset,copy,i;mygames_kvm_u8 block;
    if(!audio.ready || !audio_memory || !samples)return 0U;
    if(!count)return 0U;
    offset=0U;
    while(offset<count) {
        if(fill_block==0xffU) {
            for(block=0U;block<MYGAMES_DOS16_PCM_BLOCK_COUNT;++block)if(block_free[block])break;
            /* Report backpressure; the caller decides what to do with samples
             * that could not be queued. A prefix may already be committed. */
            if(block==MYGAMES_DOS16_PCM_BLOCK_COUNT)return 0U;
            block_free[block]=0U;fill_block=block;fill_count=0U;
        }
        copy=(unsigned short)(count-offset);
        if(copy>MYGAMES_DOS16_PCM_BLOCK_BYTES-fill_count)copy=(unsigned short)(MYGAMES_DOS16_PCM_BLOCK_BYTES-fill_count);
        for(i=0U;i<copy;++i)audio_memory[(unsigned long)fill_block*MYGAMES_DOS16_PCM_BLOCK_BYTES+fill_count+i]=samples[offset+i];
        offset=(unsigned short)(offset+copy);fill_count=(unsigned short)(fill_count+copy);
        if(fill_count==MYGAMES_DOS16_PCM_BLOCK_BYTES) {
            block=fill_block;block_ready[block]=1U;fill_block=0xffU;fill_count=0U;
            if(!ensure_playing())return 0U;
        }
    }
    return 1U;
}
