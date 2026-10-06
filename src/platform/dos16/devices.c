#include "platform/dos16/devices.h"
#include "platform/dos16/keyboard.h"
#include "platform/dos16/pit_clock.h"
#include "io/color.h"
#include "io/pacing.h"
#include <dos.h>
#include <conio.h>
#include <string.h>

static struct mysmb_dos16_keyboard keyboard;
static void (interrupt far *old_keyboard)();
static unsigned char old_mode;
static unsigned char old_rows;
static unsigned char old_font;
static unsigned short old_cursor;
static unsigned char video_ready;
static struct mysmb_io_pacing pacing;
static unsigned char opened;
static unsigned char text_mode;

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
    unsigned int attempt;
    unsigned char status;
    unsigned long ticks;
    volatile unsigned long far *bios_ticks;
    bios_ticks=(volatile unsigned long far *)0x0040006cUL;
    _disable();
    /* A zero reload count at an OUT transition is ambiguous in a sampled
     * read-back. Recapture the whole BIOS/PIT pair;never change its rate.
     * Bound interrupt-disabled work even if the device stops advancing. */
    for(attempt=0U;attempt<4U;++attempt) {
        ticks=*bios_ticks;
        outp(0x43,0xc2U);
        status=(unsigned char)inp(0x40);
        low=(unsigned short)inp(0x40);
        high=(unsigned short)inp(0x40);
        if((low|(high<<8U))!=0U)break;
    }
    phase=mysmb_dos16_pit_phase(status,(unsigned short)(low|(high<<8U)));
    /* A latched high count plus pending IRQ0 means a wrap not yet reflected
     * in the BIOS count. Leave the timer vector/rate and clock untouched. */
    outp(0x20,0x0aU);
    if ((inp(0x20)&1U)!=0U && phase<32768U) ++ticks;
    _enable();
    return (ticks<<16U)+phase;
}

/* Keep BIOS mode13h timing;unchain memory and expose all400 scanlines.
 * One plane row is80bytes;byte addressing avoids DWORD scanout strides. */
static void vga_register(unsigned short port,unsigned char index,unsigned char value)
{ outp(port,index);outp((unsigned short)(port+1U),value); }
static void vga_400_rows(void)
{
    unsigned char scan;
    vga_register(0x3c4,4,6);
    outp(0x3d4,9);scan=(unsigned char)inp(0x3d5);
    vga_register(0x3d4,9,(unsigned char)(scan&0xe0U));
    vga_register(0x3d4,20,0);
    vga_register(0x3d4,23,0xe3);
    vga_register(0x3c4,2,15);
}
static int try_mode(mysmb_io_u8 text)
{
    union REGS registers;
    unsigned short i;
    unsigned long rgb;
    if(text) {
        registers.x.ax=0x1202U;registers.x.bx=0x30U;
        int86(0x10,&registers,&registers);
        registers.x.ax=3U;int86(0x10,&registers,&registers);
        registers.x.ax=0x1112U;registers.x.bx=0U;
        int86(0x10,&registers,&registers);
        registers.x.ax=0x1003U;registers.x.bx=0U;
        int86(0x10,&registers,&registers);
        registers.h.ah=1U;registers.h.ch=0x20U;registers.h.cl=0U;
        int86(0x10,&registers,&registers);
        registers.h.ah=0x0fU;int86(0x10,&registers,&registers);
        return registers.h.al==3U && registers.h.ah==80U &&
            *(volatile unsigned char far *)0x00400084UL==49U;
    }
    registers.h.ah=0U;
    registers.h.al=0x13U;
    int86(0x10,&registers,&registers);
    registers.h.ah=0x0fU;int86(0x10,&registers,&registers);
    if(registers.h.al!=0x13U)return 0;
    vga_400_rows();
    outp(0x3c8,0U);
    for (i=0U;i<64U;++i) {
        rgb=mysmb_io_color_rgb((mysmb_io_u8)i);
        outp(0x3c9,(unsigned char)((rgb>>18U)&0x3fU));
        outp(0x3c9,(unsigned char)((rgb>>10U)&0x3fU));
        outp(0x3c9,(unsigned char)((rgb>>2U)&0x3fU));
    }
    return 1;
}
int mysmb_dos16_devices_mode(mysmb_io_u8 text)
{
    if(!opened || !video_ready)return 0;
    text=(mysmb_io_u8)(text!=0U);
    if(text==text_mode)return 1;
    if(try_mode(text)) {text_mode=text;return 1;}
    /* A failed BIOS setup may already have changed the physical mode. */
    video_ready=(unsigned char)try_mode(text_mode);
    return 0;
}
static void restore_video(void)
{
    union REGS registers;
    if(old_mode<=3U || old_mode==7U) {
        /* 43 eight-pixel rows occupy344 of the350 scanlines. */
        registers.x.ax=(unsigned short)((old_rows+1U)*old_font>350U?0x1202U:
            (old_rows+1U)*old_font>200U?0x1201U:0x1200U);
        registers.x.bx=0x30U;int86(0x10,&registers,&registers);
    }
    registers.h.ah=0U;registers.h.al=old_mode;
    int86(0x10,&registers,&registers);
    if(old_mode<=3U || old_mode==7U) {
        if(old_font==8U || old_font==14U || old_font==16U) {
            registers.x.ax=old_font==8U?0x1112U:old_font==14U?0x1111U:0x1114U;
            registers.x.bx=0U;int86(0x10,&registers,&registers);
        }
        registers.h.ah=1U;registers.x.cx=old_cursor;
        int86(0x10,&registers,&registers);
    }
}
int mysmb_dos16_devices_open(void)
{
    union REGS registers;
    if(opened)return video_ready;
    registers.h.ah=0x0fU;int86(0x10,&registers,&registers);
    old_mode=registers.h.al;
    old_rows=*(volatile unsigned char far *)0x00400084UL;
    old_font=*(volatile unsigned char far *)0x00400085UL;
    registers.h.ah=3U;registers.h.bh=0U;
    int86(0x10,&registers,&registers);old_cursor=registers.x.cx;
    if(!try_mode(0U)) {restore_video();return 0;}
    text_mode=0U;video_ready=1U;
    mysmb_dos16_keyboard_initialize(&keyboard);
    old_keyboard=_dos_getvect(9U);
    _dos_setvect(9U,keyboard_interrupt);
    mysmb_io_pacing_initialize(&pacing,timer_stamp(),19886UL);
    opened=1U;
    return 1;
}

void mysmb_dos16_devices_close(void)
{
    if (opened==0U) return;
    _dos_setvect(9U,old_keyboard);
    restore_video();opened=video_ready=text_mode=0U;
}

void mysmb_dos16_devices_input(struct mysmb_io_input *input)
{
    _disable();
    mysmb_dos16_keyboard_input(&keyboard,input);
    if(!video_ready)input->requests|=MYSMB_IO_REQUEST_EXIT;
    _enable();
}

/* All validated plane transfers contain a multiple of four bytes.
 * USE16 addressing, DWORD operands only; original DOS segment ABI retained. */
static void copy_plane_dwords(unsigned char far *video,
    const unsigned char far *pixels,unsigned short count)
{
    _asm {
        push ds
        push es
        lds si,pixels
        les di,video
        mov cx,count
        shr cx,1
        shr cx,1
        cld
        _emit 0x66
        rep movsw
        pop es
        pop ds
    }
}


void mysmb_dos16_devices_present_rows(mysmb_io_u16 plane,
    mysmb_io_u16 first,mysmb_io_u16 rows,
    const mysmb_io_u8 MYSMB_VGA_FAR *pixels)
{
    unsigned char far *video;
    if(!video_ready || text_mode || plane>=MYSMB_VGA_PAGE_COUNT || pixels==0 || first>=400U || rows>400U-first)return;
    video=(unsigned char far *)0xa0000000UL;
    /* Select the independent plane at A000;copy remains within both segments. */
    vga_register(0x3c4,2,(unsigned char)(1U<<plane));
    copy_plane_dwords(video+first*80U,pixels,rows*80U);
}
void mysmb_dos16_devices_present(const struct mysmb_vga_frame *frame)
{
    mysmb_io_u16 page;
    for(page=0U;page<MYSMB_VGA_PAGE_COUNT;++page)
        mysmb_dos16_devices_present_rows(page,0U,400U,frame->pages[page]);
}
void mysmb_dos16_devices_text(const struct mysmb_io_text_frame MYSMB_IO_FAR *frame)
{
    unsigned short i;
    volatile unsigned short far *video;
    if(!video_ready || !text_mode || !frame)return;
    video=(volatile unsigned short far *)0xb8000000UL;
    for(i=0U;i<MYSMB_IO_TEXT_CELLS;++i)
        video[i]=(unsigned short)(frame->cells[i].character|
            ((unsigned short)(frame->cells[i].foreground&15U)<<8U)|
            ((unsigned short)(frame->cells[i].background&15U)<<12U));
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
