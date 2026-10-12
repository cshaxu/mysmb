#ifndef MYSMB_BLOCK_LIFETIME_FIXTURE_H
#define MYSMB_BLOCK_LIFETIME_FIXTURE_H
#include "entrance_fixture.h"
static void mysmb_block_lifetime_fixture(unsigned char *ram,unsigned char n)
{
    static const unsigned char states[16]={0U,0x10U,1U,0x11U,0x81U,1U,
        2U,0x12U,0x82U,2U,2U,2U,2U,2U,2U,2U};
    static const unsigned char ys[16]={0xf0U,0xf0U,4U,5U,0U,0xffU,
        0xefU,0xf0U,0xf1U,0U,0xffU,0xf0U,0xf0U,0xf0U,0xf0U,0xffU};
    unsigned int i;unsigned char kind;
    mysmb_entrance_fixture(ram,0U);kind=(unsigned char)(n/2U);
    ram[0xeU]=8U;ram[0x747U]=0U;
    for(i=0U;i<4U;++i) {
        ram[0x76U+i]=7U;ram[0x8fU+i]=(i&1U)?0xffU:0U;
        ram[0xbeU+i]=kind>=14U?0U:1U;
        ram[0xd7U+i]=i<2U?ys[kind]:(unsigned char)(0xefU+kind%3U);
        ram[0x60U+i]=0xf0U;ram[0xa8U+i]=0U;
        ram[0x409U+i]=0xffU;ram[0x41fU+i]=0U;ram[0x43cU+i]=0U;
    }
    for(i=0U;i<2U;++i) {
        ram[0x26U+i]=states[kind];ram[0x3ecU+i]=0U;
        ram[0x3f1U+i]=ram[0x8fU+i];ram[0x3e8U+i]=0xc4U;
    }
}
static int mysmb_block_lifetime_argument(const char *text)
{
    static const char prefix[]="--fixture=t37-lifetime=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>31U) return 0;
    return (int)value+1;
}
#endif
