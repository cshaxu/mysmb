/* Real DOS BIOS/device join with authored templates. No gameplay core or
 * owner-ROM resources are linked. */
#include "platform/dos16/devices.h"
#include <dos.h>
#include "io/text_glyph.h"
#include "game/presentation/text/elements.h"
#include <stdio.h>

static int rows(void)
{return *(volatile unsigned char far *)0x00400084UL;}
static int mode(void)
{
    union REGS r;
    r.h.ah=0x0fU;int86(0x10,&r,&r);return r.h.al;
}
static int fail(int code)
{
    FILE *file;
    mysmb_dos16_devices_close();file=fopen("device.err","w");
    if(file){fprintf(file,"device check %d\n",code);fclose(file);}
    return code;
}
int main(void)
{
    static struct mysmb_io_text_frame glyph_frame;
    static const unsigned char glyph_ids[16]={
        0xb3U,0xc4U,0xdaU,0xbfU,0xc0U,0xd9U,0xc3U,0xb4U,
        0xc2U,0xc1U,0xc5U,0xdbU,0xdcU,0xdfU,0xddU,0xdeU};
    static const char *words[16]={"100","200","400","500","800","1000",
        "2000","4000","5000","8000","1UP","5000","2000","800","400","100"};
    struct mysmb_text_element word;
    volatile unsigned short far *text;
    union REGS r;
    void (interrupt far *vector)();
    unsigned short i,cursor,seen,value,facing,bg,j;
    struct mysmb_io_input input;
    FILE *receipt;
    r.x.ax=3U;int86(0x10,&r,&r);
    if(!mysmb_dos16_devices_open())return fail(9);
    mysmb_dos16_devices_close();
    if(mode()!=3 || rows()!=24)return fail(10);
    r.x.ax=0x1201U;r.x.bx=0x30U;int86(0x10,&r,&r);
    r.x.ax=3U;int86(0x10,&r,&r);
    r.x.ax=0x1112U;r.x.bx=0U;int86(0x10,&r,&r);
    if(rows()!=42 || !mysmb_dos16_devices_open())return fail(11);
    if(!mysmb_dos16_devices_mode(1U) || rows()!=49)return fail(12);
    mysmb_dos16_devices_close();
    if(mode()!=3 || rows()!=42)return fail(13);
    r.x.ax=0x1202U;r.x.bx=0x30U;int86(0x10,&r,&r);
    r.x.ax=3U;int86(0x10,&r,&r);
    r.x.ax=0x1112U;r.x.bx=0U;int86(0x10,&r,&r);
    if(rows()!=49)return fail(1);
    r.h.ah=3U;r.h.bh=0U;int86(0x10,&r,&r);cursor=r.x.cx;
    vector=_dos_getvect(9U);
    if(!mysmb_dos16_devices_open() || mode()!=0x13)return fail(2);
    if(!mysmb_dos16_devices_mode(1U) || mode()!=3 || rows()!=49)return fail(3);
    for(i=0U;i<MYSMB_IO_TEXT_CELLS;++i) {
        glyph_frame.cells[i].character=' ';
        glyph_frame.cells[i].foreground=15U;glyph_frame.cells[i].background=1U;
    }
    for(i=0U;i<16U;++i)glyph_frame.cells[i].character=glyph_ids[i];
    mysmb_dos16_devices_text(&glyph_frame);
    text=(volatile unsigned short far *)0xb8000000UL;
    for(i=0U;i<16U;++i)if(text[i]!=(0x1f00U|glyph_ids[i]))return fail(14);
    word.x=word.y=0;word.foreground=15U;word.background=15U;
    for(value=0U;value<16U;++value)for(facing=0U;facing<2U;++facing)
        for(bg=1U;bg<=15U;bg+=14U) {
            word.kind=value<11U?MYSMB_TEXT_SCORE:MYSMB_TEXT_FLAG_SCORE;
            word.pose=(unsigned char)(value<11U?value:value-11U);
            word.face_left=(unsigned char)facing;
            if(!mysmb_text_elements_build(&word,1U,(unsigned char)bg,&glyph_frame))return fail(15);
            mysmb_dos16_devices_text(&glyph_frame);
            for(j=0U;words[value][j]!='\0';++j)
                if(text[j]!=((bg==15U?0xf000U:0x1f00U)|(unsigned char)words[value][j]))return fail(16);
        }
    *(volatile unsigned short far *)0xb8000000UL=0x1f58U;
    if(!mysmb_dos16_devices_mode(1U) ||
        *(volatile unsigned short far *)0xb8000000UL!=0x1f58U)return fail(4);
    if(!mysmb_dos16_devices_mode(0U) || mode()!=0x13)return fail(5);
    seen=0U;
    for(i=0U;i<600U;++i) {
        mysmb_dos16_devices_input(&input);
        seen|=input.buttons;
        if(input.requests&MYSMB_IO_REQUEST_EXIT)break;
        mysmb_dos16_devices_wait();
    }
    mysmb_dos16_devices_close();mysmb_dos16_devices_close();
    if(mode()!=3 || rows()!=49 || _dos_getvect(9U)!=vector)return fail(6);
    r.h.ah=3U;r.h.bh=0U;int86(0x10,&r,&r);
    if(r.x.cx!=cursor || i==600U ||
        (seen&(MYSMB_IO_BUTTON_START|MYSMB_IO_BUTTON_A|MYSMB_IO_BUTTON_B))!=
        (MYSMB_IO_BUTTON_START|MYSMB_IO_BUTTON_A|MYSMB_IO_BUTTON_B))return fail(7);
    receipt=fopen("device.ok","w");if(!receipt)return fail(8);
    fprintf(receipt,"graphics/text/held-mode/font/cursor/IRQ/timer/input/exit pass;16glyph slots/64authored score-word cases pass\n");
    fclose(receipt);return 0;
}
