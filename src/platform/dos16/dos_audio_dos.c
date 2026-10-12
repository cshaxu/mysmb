#include "platform/dos16/dos_audio.h"
#include <conio.h>
#include <dos.h>

enum { MYSMB_DOS16_AUDIO_DMA_PARAGRAPHS=256U };
static struct mysmb_dos16_audio_state audio;
static unsigned short audio_segment;

/* The OpenNT DOS link policy rejects CRT environment startup helpers.  Query
 * DOS for this process's PSP, then copy only its BLASTER value into a bounded
 * near buffer before the portable parser sees it. */
static int current_blaster(char *target,unsigned short capacity)
{
    union REGS registers;
    union {
        struct { unsigned short offset,segment; } address;
        const char far *pointer;
    } environment_address;
    const char far *environment;
    unsigned short offset=0U,write;
    static const char name[]="BLASTER=";
    registers.h.ah=0x62U;intdos(&registers,&registers);
    /* The OpenNT runtime exposes MK_FP as an unresolved CRT helper in this
     * model.  Build the standard segment:offset far address directly. */
    environment_address.address.offset=0U;
    environment_address.address.segment=registers.x.bx;
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

static int dsp_probe(void *context,const struct mysmb_dos16_audio_config *config)
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

static int dma_reserve(void *context,const struct mysmb_dos16_audio_config *config)
{
    (void)context;(void)config;
    if(audio_segment)return 0;
    return _dos_allocmem(MYSMB_DOS16_AUDIO_DMA_PARAGRAPHS,&audio_segment)==0;
}

static void dma_release(void *context)
{
    (void)context;
    if(audio_segment)_dos_freemem(audio_segment);
    audio_segment=0U;
}

static const struct mysmb_dos16_audio_ops hardware_ops={dsp_probe,dma_reserve,dma_release};

int mysmb_dos16_audio_dos_open(void)
{
    char blaster[128];
    /* Keep direct callers idempotent too; devices_open normally invokes this
     * once, but a failed host restart must never strand the reserved block. */
    mysmb_dos16_audio_dos_close();
    mysmb_dos16_audio_initialize(&audio);
    if(!current_blaster(blaster,sizeof(blaster)))return 0;
    return mysmb_dos16_audio_open(&audio,blaster,&hardware_ops,0);
}

void mysmb_dos16_audio_dos_close(void)
{ mysmb_dos16_audio_close(&audio); }

void mysmb_dos16_audio_dos_after_load(void)
{ (void)mysmb_dos16_audio_reprobe(&audio); }

int mysmb_dos16_audio_dos_prepared(void)
{ return audio.ready!=0U; }
