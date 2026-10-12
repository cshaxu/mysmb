#ifndef MYSMB_POWER_UP_INIT_FIXTURE_H
#define MYSMB_POWER_UP_INIT_FIXTURE_H
#include "coin_allocation_fixture.h"
static void mysmb_power_up_init_fixture(unsigned char *ram,unsigned char n)
{
    static const unsigned char tiles[3]={0xc1U,0x57U,0x60U};
    unsigned int i,base;
    mysmb_coin_allocation_fixture(ram,0U);
    n=(unsigned char)(n%18U);
    ram[0x3eeU]=(unsigned char)(n/9U);
    ram[0x756U]=(unsigned char)((n/3U)%3U);
    for(base=0x500U;base<=0x5d0U;base+=0xd0U)
        for(i=0U;i<16U;++i) ram[base+0x50U+i]=tiles[n%3U];
}
static int mysmb_power_up_init_argument(const char *text)
{
    static const char prefix[]="--fixture=t36-power-init=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>35U) return 0;
    return (int)value+1;
}
#endif
