#ifndef MYSMB_GREEN_COUNTER_FIXTURE_H
#define MYSMB_GREEN_COUNTER_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_green_counter_slot(unsigned int n)
{ return (unsigned char)((n%2U)*5U); }
static unsigned int mysmb_green_counter_entry(unsigned int n)
{ return n<256U?0xcb25U:0xcb47U; }
static void mysmb_green_counter_fixture(unsigned char *ram,unsigned int n)
{
    static const unsigned char primary[4]={0U,1U,2U,0xffU};
    static const unsigned char secondary[8]={0U,1U,0x12U,0x13U,0x14U,0x7fU,0x80U,0xffU};
    static const unsigned char platform_secondary[4]={0U,13U,14U,15U};
    unsigned int i;
    unsigned char slot;
    slot=mysmb_green_counter_slot(n);
    mysmb_actor_dispatch_fixture(ram,(n<256U?32U:80U)+n%2U);
    for(i=0U;i<6U;++i) if(i!=slot) ram[0xfU+i]=0U;
    ram[0x747U]=0U;ram[0x6dU]=0U;ram[0x86U]=0U;ram[0xceU]=0x30U;
    ram[0x401U+slot]=0x77U;ram[0xcfU+slot]=(unsigned char)(n&32U?0xffU:0U);
    ram[0xa0U+slot]=primary[(n/2U)%4U];ram[0x3a2U+slot]=0xffU;
    if(n<256U) {
        ram[0x58U+slot]=secondary[(n/8U)%8U];
        ram[9U]=(unsigned char)(n/64U+(n&32U?0x40U:0U));
    }
    else {
        ram[0xcfU+slot]=0x80U;ram[0x49aU+slot]=6U;
        ram[0x58U+slot]=platform_secondary[((n-256U)/2U)%4U];
        ram[9U]=(unsigned char)((n-256U)/8U);
    }
}
static int mysmb_green_counter_argument(const char *text)
{
    static const char prefix[]="--fixture=t40-green-counter=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    value=0U;digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<3U) {
        value=value*10U+(unsigned int)(text[i++]-'0');++digits;
    }
    if(!digits || text[i]!='\0' || value>=288U) return 0;
    return (int)value+1;
}
#endif
