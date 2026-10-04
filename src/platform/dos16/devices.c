#include "platform/dos16/devices.h"
#include "platform/dos16/keyboard.h"
#include "platform/dos16/pit_clock.h"
#include "io/color.h"
#include "io/pacing.h"
#include <dos.h>
#include <conio.h>

static struct mysmb_dos16_keyboard keyboard;
static void (interrupt far *old_keyboard)();
static unsigned char old_mode;
static struct mysmb_io_pacing pacing;
static unsigned char opened;

static void interrupt far keyboard_interrupt(void)
{
    unsigned char scan, control;
    scan=(unsigned char)inp(0x60);
    control=(unsigned char)inp(0x61);
    outp(0x61,control|0x80U);
    outp(0x61,control);
    mysmb_dos16_keyboard_scan(&keyboard,scan);
    outp(0x20,0x20);
}

/* Latch BIOS-owned PIT channel zero; never change its rate or IRQ vector. */
static unsigned long timer_stamp(void)
{
    unsigned short low, high, phase;
    unsigned char status;
    unsigned long ticks;
    volatile unsigned long far *bios_ticks;
    bios_ticks=(volatile unsigned long far *)0x0040006cUL;
    _disable();
    ticks=*bios_ticks;
    /* 8254 read-back latches both status and count for channel zero. */
    outp(0x43,0xc2U);
    status=(unsigned char)inp(0x40);
    low=(unsigned short)inp(0x40);
    high=(unsigned short)inp(0x40);
    phase=mysmb_dos16_pit_phase(status,(unsigned short)(low|(high<<8U)));
    /* A latched high count plus pending IRQ0 means a wrap not yet reflected
     * in the BIOS count. Leave the timer vector/rate and clock untouched. */
    outp(0x20,0x0aU);
    if ((inp(0x20)&1U)!=0U && phase<32768U) ++ticks;
    _enable();
    return (ticks<<16U)+phase;
}

void mysmb_dos16_devices_open(void)
{
    union REGS registers;
    unsigned short i;
    unsigned long rgb;
    if (opened!=0U) return;
    registers.h.ah=0x0fU;
    int86(0x10,&registers,&registers);
    old_mode=registers.h.al;
    registers.h.ah=0U;
    registers.h.al=0x13U;
    int86(0x10,&registers,&registers);
    outp(0x3c8,0U);
    for (i=0U;i<64U;++i) {
        rgb=mysmb_io_color_rgb((mysmb_io_u8)i);
        outp(0x3c9,(unsigned char)((rgb>>18U)&0x3fU));
        outp(0x3c9,(unsigned char)((rgb>>10U)&0x3fU));
        outp(0x3c9,(unsigned char)((rgb>>2U)&0x3fU));
    }
    mysmb_dos16_keyboard_initialize(&keyboard);
    old_keyboard=_dos_getvect(9U);
    _dos_setvect(9U,keyboard_interrupt);
    mysmb_io_pacing_initialize(&pacing,timer_stamp(),19886UL);
    opened=1U;
}

void mysmb_dos16_devices_close(void)
{
    union REGS registers;
    if (opened==0U) return;
    _dos_setvect(9U,old_keyboard);
    registers.h.ah=0U;
    registers.h.al=old_mode;
    int86(0x10,&registers,&registers);
    opened=0U;
}

void mysmb_dos16_devices_input(struct mysmb_io_input *input)
{
    _disable();
    mysmb_dos16_keyboard_input(&keyboard,input);
    _enable();
}

void mysmb_dos16_devices_present(const struct mysmb_vga_frame *frame)
{
    unsigned short page, offset;
    unsigned char far *video;
    video=(unsigned char far *)0xa0000000UL;
    for (page=0U;page<MYSMB_VGA_PAGE_COUNT;++page)
        for (offset=0U;offset<MYSMB_VGA_PAGE_SIZE;++offset)
            video[page*MYSMB_VGA_PAGE_SIZE+offset]=frame->pages[page][offset];
}

void mysmb_dos16_devices_wait(void)
{
    while (mysmb_io_pacing_remaining(&pacing,timer_stamp())!=0UL) { }
}
void mysmb_dos16_devices_after_load(void)
{
    _disable();mysmb_dos16_keyboard_after_load(&keyboard);_enable();
    mysmb_io_pacing_initialize(&pacing,timer_stamp(),19886UL);
}

mysmb_io_u8 mysmb_dos16_devices_audio(const struct mysmb_io_audio_frame *frame)
{
    /* No DOS sound hardware adapter is installed;never claim audible output. */
    (void)frame;
    return MYSMB_IO_AUDIO_UNAVAILABLE;
}
