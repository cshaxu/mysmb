#include "text/layout.h"
#include "io/color.h"
#include <string.h>
static unsigned long distance(unsigned long a,unsigned long b)
{
    long r,g,v;
    r=(long)((a>>16U)&255UL)-(long)((b>>16U)&255UL);
    g=(long)((a>>8U)&255UL)-(long)((b>>8U)&255UL);
    v=(long)(a&255UL)-(long)(b&255UL);
    return (unsigned long)(r*r+g*g+v*v);
}
mysmb_io_u8 mysmb_text_color(const struct mysmb_io_text_frame MYSMB_IO_FAR *f,
    mysmb_io_u8 master)
{return f->source_colors==1U?f->master_map[master&63U]:mysmb_io_color_text16(master);}
mysmb_io_u8 mysmb_text_contrast(const struct mysmb_io_text_frame MYSMB_IO_FAR *f,
    mysmb_io_u8 background)
{
    unsigned long rgb,brightness;
    if(f->source_colors!=1U)return mysmb_io_color_text_contrast(background);
    rgb=f->colors[background&15U];
    brightness=(((rgb>>16U)&255UL)*3UL+((rgb>>8U)&255UL)*6UL+(rgb&255UL))/10UL;
    /* Light source-style lettering on blue/dark scenes;dark ink only for
     * light fills. The custom palette reserves black1 and white2. */
    return brightness>=192UL?1U:2U;
}
void mysmb_text_frame_initialize(struct mysmb_io_text_frame MYSMB_IO_FAR *f,
    mysmb_io_u8 sky,mysmb_io_u16 rows,const mysmb_io_u8 *palette)
{
    unsigned short i,j,count,used,filled,n,best;
    unsigned long color,d,minimum;
    /* The frame may borrow old graphical bytes. Initialize metadata padding
     * too,so its complete neutral value has a deterministic representation. */
    memset((unsigned char MYSMB_IO_FAR *)f+sizeof(f->cells),0,
        sizeof(*f)-sizeof(f->cells));
    f->rows=rows==25U?25U:50U;f->source_colors=(mysmb_io_u8)(palette!=0);
    for(i=0U;i<64U;++i)f->master_map[i]=0U;
    if(palette==0)for(i=0U;i<16U;++i)f->colors[i]=mysmb_io_color_text_rgb((mysmb_io_u8)i);
    else {
        f->colors[0U]=mysmb_io_color_rgb(palette[0U]);
        f->colors[1U]=mysmb_io_color_rgb(0x0fU);
        f->colors[2U]=mysmb_io_color_rgb(0x30U);used=3U;
        for(i=0U;i<32U && used<16U;++i) {
            color=mysmb_io_color_rgb(palette[i]);
            for(j=0U;j<used && f->colors[j]!=color;++j){}
            if(j==used)f->colors[used++]=color;
        }
        for(i=used;i<16U;++i)f->colors[i]=f->colors[0U];
        for(i=0U;i<64U;++i) {
            minimum=0xffffffffUL;best=0U;color=mysmb_io_color_rgb((mysmb_io_u8)i);
            for(j=0U;j<used;++j) {
                d=distance(color,f->colors[j]);
                if(d<minimum){minimum=d;best=j;}
            }
            f->master_map[i]=(mysmb_io_u8)best;
        }
        sky=mysmb_text_color(f,palette[0U]);
    }
    count=(unsigned short)(80U*f->rows);filled=1U;
    f->cells[0U].character=' ';f->cells[0U].foreground=sky;f->cells[0U].background=sky;
    while(filled<count) {
        n=filled;if(n>count-filled)n=(unsigned short)(count-filled);
        memcpy(f->cells+filled,f->cells,n*sizeof(f->cells[0U]));filled=(unsigned short)(filled+n);
    }
}
