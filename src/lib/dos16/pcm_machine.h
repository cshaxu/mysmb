#ifndef MYGAMES_DOS16_PCM_MACHINE_H
#define MYGAMES_DOS16_PCM_MACHINE_H
/* Static hardware boundary. Tests replace only machine addressing/FLAGS;
 * DSP, DMA, PIC, queue and lifecycle production code remains the tested owner. */
#ifdef MYGAMES_DOS16_PCM_TEST
unsigned short pcm_irq_save(void);
void pcm_irq_restore(unsigned short flags);
unsigned char *pcm_segment(unsigned short segment);
int current_blaster(char *target,unsigned short capacity);
#else
static unsigned short pcm_irq_save(void)
{
    unsigned short flags;
    _asm pushf
    _asm pop ax
    _asm mov flags,ax
    _asm cli
    return flags;
}
static void pcm_irq_restore(unsigned short flags)
{
    _asm push flags
    _asm popf
}
static unsigned char far *pcm_segment(unsigned short segment)
{
    union {struct {unsigned short offset,segment;} address;unsigned char far *pointer;} p;
    p.address.offset=0;p.address.segment=segment;return p.pointer;
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

#endif
#endif
