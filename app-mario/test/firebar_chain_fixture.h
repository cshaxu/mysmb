#ifndef MYSMB_FIREBAR_CHAIN_FIXTURE_H
#define MYSMB_FIREBAR_CHAIN_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_firebar_chain_slot(unsigned int n)
{ return (unsigned char)((n%2U)*5U); }
static void mysmb_firebar_chain_fixture(unsigned char *ram,unsigned int n)
{
    unsigned int i,mode;
    unsigned char slot,id;
    slot=mysmb_firebar_chain_slot(n);id=(unsigned char)(n&2U?31U:27U);mode=n/128U;
    mysmb_actor_dispatch_fixture(ram,(unsigned int)id*2U+n%2U);
    for(i=0U;i<6U;++i) ram[0xfU+i]=0U;
    ram[0xfU+slot]=1U;ram[0x16U+slot]=id;ram[0x1eU+slot]=0U;
    ram[0x6eU+slot]=1U;ram[0x87U+slot]=0x70U;
    ram[0xcfU+slot]=0x80U;ram[0xb6U+slot]=1U;
    ram[0x6e5U+slot]=0x40U;ram[0x6e6U]=0x80U;ram[0x6cfU]=1U;
    ram[0xa0U+slot]=(unsigned char)((n/4U)%32U);
    ram[0x58U+slot]=(unsigned char)(n&4U?0xffU:0U);
    ram[0x388U+slot]=0x28U;ram[0x34U+slot]=(unsigned char)(n&8U?1U:0U);
    ram[0x747U]=(unsigned char)(mode==1U?0xffU:0U);
    ram[0x6dU]=0U;ram[0x86U]=0U;ram[0xceU]=0x30U;
    ram[0x79fU]=0U;ram[0x79eU]=0U;
    if(mode==2U) {
        ram[0x6dU]=1U;ram[0x86U]=0x70U;ram[0xceU]=0x68U;
        ram[0x754U]=(unsigned char)(n&4U?1U:0U);
        ram[0x714U]=(unsigned char)(n&8U?1U:0U);
        ram[0x756U]=(unsigned char)(n&16U?1U:0U);
        ram[0x79eU]=(unsigned char)(n&32U?8U:0U);
    }
    if(mode==3U) {
        ram[0x87U+slot]=(unsigned char)(n&4U?0xffU:0U);
        ram[0xcfU+slot]=(unsigned char)(n&8U?0xf8U:0x80U);
        ram[0x79fU]=(unsigned char)(n&16U?8U:0U);
        ram[0x6eU+slot]=(unsigned char)(n&32U?2U:1U);
    }
}
static int mysmb_firebar_chain_argument(const char *text)
{
    static const char prefix[]="--fixture=t40-firebar-chain=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    value=0U;digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<3U) {
        value=value*10U+(unsigned int)(text[i++]-'0');++digits;
    }
    if(!digits || text[i]!='\0' || value>=512U) return 0;
    return (int)value+1;
}
#endif
