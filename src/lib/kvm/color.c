#include "kvm/color.h"

static const unsigned long text_palette[16] = {
        0x000000UL,0x0000aaUL,0x00aa00UL,0x00aaaaUL,
        0xaa0000UL,0xaa00aaUL,0xaa5500UL,0xaaaaaaUL,
        0x555555UL,0x5555ffUL,0x55ff55UL,0x55ffffUL,
        0xff5555UL,0xff55ffUL,0xffff55UL,0xffffffUL
};

unsigned long mygames_kvm_color_text_rgb(mygames_kvm_u8 index)
{
    return text_palette[index&15U];
}
mygames_kvm_u8 mygames_kvm_color_text_nearest(unsigned long rgb)
{
    unsigned short i,best;
    long r,g,b;
    unsigned long d,minimum;
    minimum=0xffffffffUL;best=0U;
    for(i=0U;i<16U;++i) {
        r=(long)((rgb>>16U)&255UL)-(long)((text_palette[i]>>16U)&255UL);
        g=(long)((rgb>>8U)&255UL)-(long)((text_palette[i]>>8U)&255UL);
        b=(long)(rgb&255UL)-(long)(text_palette[i]&255UL);
        d=(unsigned long)(r*r+g*g+b*b);
        if(d<minimum){minimum=d;best=i;}
    }
    return (mygames_kvm_u8)best;
}

void mygames_kvm_color_text_attributes(const unsigned long *colors,
    mygames_kvm_u8 source_colors,mygames_kvm_u8 attributes[16])
{
    unsigned short i;
    for(i=0U;i<16U;++i)
        attributes[i]=source_colors!=0U?
            mygames_kvm_color_text_nearest(colors[i]):(mygames_kvm_u8)i;
}

mygames_kvm_u8 mygames_kvm_color_text_contrast(mygames_kvm_u8 background)
{
    static const mygames_kvm_u8 choices[16] = {
        15U,15U,15U,15U,15U,15U,15U,0U,15U,15U,0U,0U,0U,0U,0U,0U
    };
    return choices[background&15U];
}
