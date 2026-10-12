#ifndef MYSMB_BLOCK_REPLACEMENT_FIXTURE_H
#define MYSMB_BLOCK_REPLACEMENT_FIXTURE_H
#include "entrance_fixture.h"
static void mysmb_block_replacement_fixture(unsigned char *ram,unsigned char n)
{
    static const unsigned char tiles[8]={0U,0x51U,0x52U,0x58U,0x5dU,0xc4U,0xffU,0xc0U};
    mysmb_entrance_fixture(ram,0U);ram[0xeU]=8U;ram[0x747U]=0U;
    ram[0x3ecU]=(n&1U)?2U:0U;ram[0x3edU]=(n&2U)?0xffU:0U;
    ram[0x3e4U]=(unsigned char)((n&7U)<<4U);
    ram[0x3e5U]=(unsigned char)(0x80U+((n&7U)<<4U));
    ram[0x3e6U]=(n&4U)?0xdfU:0x0fU;ram[0x3e7U]=(n&8U)?0xd0U:0U;
    ram[0x3e8U]=tiles[n/4U];ram[0x3e9U]=tiles[n/4U];
    ram[0x26U]=0U;ram[0x27U]=0U;
    ram[0x300U]=0U;ram[0x301U]=n>=24U?0x20U:0U;
    ram[0x340U]=0U;ram[0x341U]=0U;ram[0x773U]=6U;
}
static int mysmb_block_replacement_argument(const char *text)
{
    static const char prefix[]="--fixture=t37-replacement=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>31U) return 0;
    return (int)value+1;
}
#endif
