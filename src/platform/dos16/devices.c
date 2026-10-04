#include "platform/dos16/devices.h"
#include "platform/dos16/keyboard.h"
#include "io/color.h"
#include <dos.h>
#include <conio.h>

static struct mysmb_dos16_keyboard keyboard;
static void (interrupt far *old_keyboard)();
static unsigned char old_mode;
static unsigned short last_counter;
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
static unsigned short timer_counter(void)
{
    unsigned short low, high;
    _disable();
    outp(0x43,0U);
    low=(unsigned short)inp(0x40);
    high=(unsigned short)inp(0x40);
    _enable();
    return (unsigned short)(low|(high<<8U));
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
    last_counter=timer_counter();
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

int mysmb_dos16_devices_exit_requested(void)
{
    int requested;
    _disable();
    requested=keyboard.down[1U]!=0U;
    _enable();
    return requested;
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
    unsigned short current, elapsed;
    elapsed=0U;
    do {
        current=timer_counter();
        elapsed=(unsigned short)(elapsed+(unsigned short)(last_counter-current));
        last_counter=current;
    } while (elapsed<19886U && !mysmb_dos16_devices_exit_requested());
}
