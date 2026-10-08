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
static unsigned short text_rows=25U;
static unsigned char text_colors[16];
static mysmb_io_u8 palette_shadow[MYSMB_IO_VIDEO_PALETTE_COLORS],palette_valid;

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

/* Independent native256x240 timing:25.175MHz,800dots/525lines,approximately
 * 60Hz. VGA repeats each stored row twice;chain4 exposes61440linear bytes.
 * BIOS13h supplies initial graphics/attribute state;restore uses original mode. */
static void vga_register(unsigned short port,unsigned char index,unsigned char value)
{ outp(port,index);outp((unsigned short)(port+1U),value); }
static void vga_native_rows(void)
{
    unsigned char protect;
    vga_register(0x3c4,0,1);
    outp(0x3c2,0xe3);
    vga_register(0x3c4,4,14);
    outp(0x3d4,17);protect=(unsigned char)inp(0x3d5);
    vga_register(0x3d4,17,(unsigned char)(protect&0x7fU));
    vga_register(0x3d4,1,63);vga_register(0x3d4,2,64);
    vga_register(0x3d4,6,13);vga_register(0x3d4,7,62);
    vga_register(0x3d4,9,65);
    vga_register(0x3d4,16,234);vga_register(0x3d4,17,44);
    vga_register(0x3d4,18,223);vga_register(0x3d4,19,32);
    vga_register(0x3d4,20,64);
    vga_register(0x3d4,21,231);vga_register(0x3d4,22,6);
    vga_register(0x3d4,23,0xa3);
    vga_register(0x3c4,2,15);
    vga_register(0x3c4,0,3);
}
static int try_mode(mysmb_io_u8 text)
{
    union REGS registers;
    unsigned short i;
    unsigned long rgb;
    palette_valid=0U;
    if(text) {
        registers.x.ax=0x1202U;registers.x.bx=0x30U;
        int86(0x10,&registers,&registers);
        registers.x.ax=3U;int86(0x10,&registers,&registers);
        registers.x.ax=text_rows==50U?0x1112U:0x1114U;registers.x.bx=0U;
        int86(0x10,&registers,&registers);
        registers.x.ax=0x1003U;registers.x.bx=0U;
        int86(0x10,&registers,&registers);
        registers.h.ah=1U;registers.h.ch=0x20U;registers.h.cl=0U;
        int86(0x10,&registers,&registers);
        registers.h.ah=0x0fU;int86(0x10,&registers,&registers);
        return registers.h.al==3U && registers.h.ah==80U &&
            *(volatile unsigned char far *)0x00400084UL==(unsigned char)(text_rows-1U);
    }
    registers.h.ah=0U;
    registers.h.al=0x13U;
    int86(0x10,&registers,&registers);
    registers.h.ah=0x0fU;int86(0x10,&registers,&registers);
    if(registers.h.al!=0x13U)return 0;
    vga_native_rows();
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
void mysmb_dos16_devices_palette(const mysmb_io_u8 MYSMB_IO_FAR *palette)
{
    unsigned short i;unsigned long rgb;
    if(!video_ready || text_mode || !palette)return;
    for(i=0U;i<MYSMB_IO_VIDEO_PALETTE_COLORS;++i){
        if(palette_valid && palette_shadow[i]==palette[i])continue;
        rgb=mysmb_io_color_rgb(palette[i]);outp(0x3c8,i);
        outp(0x3c9,(unsigned char)((rgb>>18U)&63UL));
        outp(0x3c9,(unsigned char)((rgb>>10U)&63UL));
        outp(0x3c9,(unsigned char)((rgb>>2U)&63UL));
        palette_shadow[i]=palette[i];
    }
    palette_valid=1U;
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


int mysmb_dos16_devices_present_band(const struct mysmb_io_video_band *band)
{
    unsigned char far *video;
    if(!video_ready || text_mode || !band || !band->pixels || !band->rows ||
        band->first>=240U || band->rows>16U || band->rows>240U-band->first)return 0;
    video=(unsigned char far *)0xa0000000UL;
    /* A composition root may have written this exact logical band directly
     * to the chain-4 aperture. Keep the same synchronous ownership and
     * validation contract without copying it onto itself. */
    if(band->pixels==video+band->first*256U)return 1;
    /* Chain4 handles the plane selector/address from each CPU byte address.
     * Every band fits both segments;last source pixel is A000:EFFF. */
    copy_plane_dwords(video+band->first*256U,band->pixels,band->rows*256U);
    return 1;
}
mysmb_io_u8 MYSMB_IO_FAR *mysmb_dos16_devices_direct_band(mysmb_io_u16 first,
    mysmb_io_u16 rows)
{
    if(!video_ready || text_mode || !rows || first>=240U || rows>16U ||
        rows>240U-first)return 0;
    return (mysmb_io_u8 MYSMB_IO_FAR *)0xa0000000UL+first*256U;
}
void mysmb_dos16_devices_text(const struct mysmb_io_text_frame MYSMB_IO_FAR *frame)
{
    unsigned short i;
    volatile unsigned short far *video;
    if(!video_ready || !text_mode || !frame)return;
    if(text_rows!=MYSMB_IO_TEXT_FRAME_ROWS(frame)) {
        text_rows=(unsigned short)MYSMB_IO_TEXT_FRAME_ROWS(frame);
        if(!try_mode(1U))return;
    }
    for(i=0U;i<16U;++i)
        text_colors[i]=mysmb_io_color_text_nearest(frame->colors[i]);
    video=(volatile unsigned short far *)0xb8000000UL;
    for(i=0U;i<MYSMB_IO_TEXT_FRAME_CELLS(frame);++i)
        video[i]=(unsigned short)(frame->cells[i].character|
            ((unsigned short)text_colors[frame->cells[i].foreground&15U]<<8U)|
            ((unsigned short)text_colors[frame->cells[i].background&15U]<<12U));
}

void mysmb_dos16_devices_wait(void)
{
    while (mysmb_io_pacing_remaining(&pacing,timer_stamp())!=0UL) { }
}
void mysmb_dos16_devices_after_load(void)
{
    palette_valid=0U;
    _disable();mysmb_dos16_keyboard_after_load(&keyboard);_enable();
    mysmb_io_pacing_initialize(&pacing,timer_stamp(),19886UL);
}
void mysmb_dos16_devices_resume_clock(void)
{mysmb_io_pacing_initialize(&pacing,timer_stamp(),19886UL);}

mysmb_io_u8 mysmb_dos16_devices_audio(const struct mysmb_io_audio_frame *frame)
{
    /* No DOS sound hardware adapter is installed;never claim audible output. */
    (void)frame;
    return MYSMB_IO_AUDIO_UNAVAILABLE;
}
