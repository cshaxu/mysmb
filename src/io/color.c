#include "io/color.h"

unsigned long mysmb_io_color_rgb(mysmb_io_u8 index)
{
    static const unsigned long colors[64] = {
        0x545454UL,0x001e74UL,0x081090UL,0x300088UL,0x440064UL,0x5c0030UL,0x540400UL,0x3c1800UL,0x202a00UL,0x083a00UL,0x004000UL,0x003c00UL,0x00323cUL,0,0,0,
        0x989698UL,0x084cc4UL,0x3032ecUL,0x5c1ee4UL,0x8814b0UL,0xa01464UL,0x982220UL,0x783c00UL,0x545a00UL,0x287200UL,0x087c00UL,0x007628UL,0x006678UL,0,0,0,
        0xeceeeeUL,0x4c9aecUL,0x787cecUL,0xb062ecUL,0xe454ecUL,0xec58b4UL,0xec6a64UL,0xd48820UL,0xa0aa00UL,0x74c400UL,0x4cd020UL,0x38c06cUL,0x38b4ccUL,0x3c3c3cUL,0,0,
        0xeceeeeUL,0xa8ccecUL,0xbcbcecUL,0xd4b2ecUL,0xecaeecUL,0xecaed4UL,0xecb4b0UL,0xe4c690UL,0xccd278UL,0xb4de78UL,0xa8e290UL,0x98e2b4UL,0xa0d6e4UL,0xa0a2a0UL,0,0
    };
    return colors[index & 0x3fU];
}

static const unsigned long text_palette[16] = {
        0x000000UL,0x0000aaUL,0x00aa00UL,0x00aaaaUL,
        0xaa0000UL,0xaa00aaUL,0xaa5500UL,0xaaaaaaUL,
        0x555555UL,0x5555ffUL,0x55ff55UL,0x55ffffUL,
        0xff5555UL,0xff55ffUL,0xffff55UL,0xffffffUL
};

unsigned long mysmb_io_color_text_rgb(mysmb_io_u8 index)
{
    return text_palette[index&15U];
}

mysmb_io_u8 mysmb_io_color_text16(mysmb_io_u8 index)
{
    unsigned long rgb,text,distance,best;
    long r,g,b;
    mysmb_io_u8 i,choice;
    rgb=mysmb_io_color_rgb(index); best=0xffffffffUL; choice=0U;
    for(i=0U;i<16U;++i) {
        text=text_palette[i];
        r=(long)((rgb>>16U)&255UL)-(long)((text>>16U)&255UL);
        g=(long)((rgb>>8U)&255UL)-(long)((text>>8U)&255UL);
        b=(long)(rgb&255UL)-(long)(text&255UL);
        distance=(unsigned long)(r*r+g*g+b*b);
        if(distance<best) {best=distance;choice=i;}
    }
    return choice;
}
