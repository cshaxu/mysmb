#include "dos16/host.h"
#include "dos16/pit_clock.h"
#include "dos16/command_line.h"
#include <dos.h>
#include <conio.h>

static void (interrupt far *previous_keyboard)();
static mygames_dos16_scan_sink scan_sink;
static void *scan_context;
static unsigned char keyboard_open;

int mygames_dos16_command_line(char *output,unsigned short capacity)
{
    union REGS registers;
    unsigned long address;
    registers.h.ah=0x62U;
    intdos(&registers,&registers);
    address=((unsigned long)registers.x.bx<<16U)|0x80UL;
    return mygames_dos16_command_tail_copy(
        (const mygames_kvm_u8 far *)address,output,capacity);
}

static void interrupt far keyboard_interrupt(void)
{
    unsigned char scan,control;
    scan=(unsigned char)inp(0x60);
    control=(unsigned char)inp(0x61);
    outp(0x61,control|0x80U);
    outp(0x61,control);
    scan_sink(scan_context,scan);
    outp(0x20,0x20);
}

int mygames_dos16_keyboard_open(mygames_dos16_scan_sink sink,void *context)
{
    if(keyboard_open || !sink)return 0;
    scan_sink=sink;scan_context=context;
    previous_keyboard=_dos_getvect(9U);
    _dos_setvect(9U,keyboard_interrupt);
    keyboard_open=1U;
    return 1;
}

void mygames_dos16_keyboard_close(void)
{
    if(!keyboard_open)return;
    _dos_setvect(9U,previous_keyboard);
    keyboard_open=0U;
    scan_sink=0;scan_context=0;
}

unsigned long mygames_dos16_clock_stamp(void)
{
    unsigned short low,high,phase;
    unsigned int attempt;
    unsigned char status;
    unsigned long ticks;
    volatile unsigned long far *bios_ticks;
    bios_ticks=(volatile unsigned long far *)0x0040006cUL;
    _disable();
    /* Bound recapture of the ambiguous zero-count transition. */
    for(attempt=0U;attempt<4U;++attempt) {
        ticks=*bios_ticks;
        outp(0x43,0xc2U);
        status=(unsigned char)inp(0x40);
        low=(unsigned short)inp(0x40);
        high=(unsigned short)inp(0x40);
        if((low|(high<<8U))!=0U)break;
    }
    phase=mygames_dos16_pit_phase(status,(unsigned short)(low|(high<<8U)));
    outp(0x20,0x0aU);
    if((inp(0x20)&1U)!=0U && phase<32768U)++ticks;
    _enable();
    return (ticks<<16U)+phase;
}
