/* Original16-bit toolchain hardware probe;synthetic pixels,no ROM input. */
#include "platform/dos16/devices.h"
#include "platform/dos16/planar_row.h"
#include <dos.h>
#include <conio.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
static unsigned char pattern(unsigned short x,unsigned short y)
{return (unsigned char)((x*13U+y*7U)&63U);}
int main(void)
{
    unsigned short first,y,x,p,rows,i;
    unsigned long bad=0UL,compared=0UL;
    unsigned char far *storage,*video=(unsigned char far *)0xa0000000UL;
    struct mysmb_io_video_band band;
    struct mysmb_io_text_frame far *text;
    union REGS r;
    unsigned char original,restored;
    FILE *f;
    r.h.ah=15U;int86(16,&r,&r);original=r.h.al;
    storage=(unsigned char far *)_fmalloc(8192U);
    text=(struct mysmb_io_text_frame far *)_fmalloc(sizeof(*text));
    if(!storage || !text || !mysmb_dos16_devices_open())return 1;
    /* Exercise actual graphics/text/graphics mode ownership twice. */
    memset(text,0,sizeof(*text));text->rows=25U;
    text->colors[2]=0xffffffUL;
    for(i=0U;i<2000U;++i){text->cells[i].character='T';text->cells[i].foreground=2U;}
    for(i=0U;i<2U;++i){
        if(!mysmb_dos16_devices_mode(1U))return 2;
        mysmb_dos16_devices_text(text);
        if(*(volatile unsigned short far *)0xb8000000UL!=0x0254U)return 3;
        if(!mysmb_dos16_devices_mode(0U))return 4;
    }
    for(first=0U;first<240U;first+=16U){
        rows=16U;
        for(y=0U;y<rows;++y)for(x=0U;x<256U;++x)
            storage[y*256U+x]=pattern(x,(unsigned short)(first+y));
        band.pixels=storage;band.first=first;band.rows=rows;
        if(!mysmb_dos16_devices_present_band(&band))return 5;
    }
    for(y=0U;y<240U;++y)for(x=0U;x<256U;++x){
        if(video[y*256U+x]!=pattern(x,y))++bad;
        ++compared;
    }
    mysmb_dos16_devices_close();
    r.h.ah=15U;int86(16,&r,&r);restored=r.h.al;
    f=fopen("NATIVE.TXT","wt");if(!f)return 6;
    fprintf(f,"pixels%lu mismatch%lu tabRoundTrips2 original%u restored%u\n",
        compared,bad,original,restored);
    fclose(f);_ffree(storage);_ffree(text);
    return bad || restored!=original?7:0;
}
