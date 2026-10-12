#ifndef MYSMB_BLOCK_HEAD_FIXTURE_H
#define MYSMB_BLOCK_HEAD_FIXTURE_H
#include "entrance_fixture.h"
static void mysmb_block_head_fixture(unsigned char *ram,unsigned char n)
{
    static const unsigned char tiles[12]={0x51U,0x52U,0xc1U,0xc0U,0x5fU,0x60U,
        0x58U,0x58U,0x58U,0x5dU,0x5dU,0x5dU};
    unsigned int i;
    unsigned char kind,body;
    kind=(unsigned char)(n%12U);body=(unsigned char)((n/12U)%3U);
    mysmb_entrance_fixture(ram,0U);
    ram[0xeU]=8U;ram[0x747U]=0U;ram[0x1dU]=1U;
    ram[0x754U]=body==0U?1U:0U;ram[0x756U]=body==0U?0U:1U;
    ram[0x714U]=body==2U?4U:0U;ram[0xceU]=0x85U;ram[0x9fU]=0xffU;
    ram[0x433U]=0U;ram[0x416U]=0U;ram[0x70aU]=0U;ram[0x70bU]=0U;
    ram[0x86U]=body==0U?0x40U:(body==1U?0xf8U:0xffU);
    ram[0x71bU]=8U;ram[0x71dU]=0xffU;ram[0x3eeU]=(unsigned char)(n/36U);
    ram[0x784U]=0U;ram[0x6bcU]=(kind==7U||kind==8U||kind==10U||kind==11U)?1U:0U;
    ram[0x79dU]=(kind==7U||kind==10U)?5U:0U;
    for(i=0x500U;i<0x6a0U;++i) ram[i]=tiles[kind];
}
static int mysmb_block_head_argument(const char *text)
{
    static const char prefix[]="--fixture=t37-head=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>71U) return 0;
    return (int)value+1;
}
#endif
