#ifndef MYSMB_COIN_ALLOCATION_FIXTURE_H
#define MYSMB_COIN_ALLOCATION_FIXTURE_H
#include "entrance_fixture.h"
static void mysmb_coin_allocation_fixture(unsigned char *ram,unsigned char n)
{
    unsigned int i,base;
    unsigned char mask;
    mysmb_entrance_fixture(ram,0U);
    ram[0xeU]=8U;ram[0x747U]=0U;ram[0x70bU]=1U;ram[0x716U]=0U;
    ram[0xceU]=0x68U;ram[0x9fU]=0xfeU;ram[0x1dU]=1U;
    ram[0x490U]=0U;ram[0x3c4U]=0U;ram[0x784U]=0U;
    ram[0x6fcU]=0U;ram[0x754U]=1U;ram[0x6deU]=0U;
    ram[0x3eeU]=(unsigned char)((n/8U)&1U);
    if(n>=40U) {ram[0x6dU]=6U;ram[0x71aU]=6U;ram[0x71bU]=6U;}
    mask=(unsigned char)(n%8U);
    for(i=0U;i<9U;++i) ram[0x2aU+i]=0U;
    for(i=0U;i<3U;++i) {
        ram[0x30U+i]=(mask&(1U<<i))!=0U?2U:0U;
        ram[0x429U+i]=0xa5U;ram[0x446U+i]=0x5aU;
    }
    for(base=0x500U;base<=0x5d0U;base+=0xd0U)
    for(i=0U;i<16U;++i) {
        ram[base+0x50U+i]=n<16U?0xc0U:0x5dU;
        if(n>=32U) ram[base+0x40U+i]=0xc2U;
    }
    ram[0x748U]=(n&1U)!=0U?0xffU:0U;
    ram[0x75eU]=(n&2U)!=0U?99U:0U;
}
static int mysmb_coin_allocation_argument(const char *text)
{
    static const char prefix[]="--fixture=t36-coin=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>47U) return 0;
    return (int)value+1;
}
#endif
