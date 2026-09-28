#ifndef MYSMB_PARATROOPA_MOVEMENT_FIXTURE_H
#define MYSMB_PARATROOPA_MOVEMENT_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_paratroopa_slot(unsigned int n)
{ return (unsigned char)((n%2U)*5U); }
static unsigned int mysmb_paratroopa_entry(unsigned int n)
{ return n<32U?0xcaf9U:0xcaffU; }
static void mysmb_paratroopa_fixture(unsigned char *ram,unsigned int n)
{
    unsigned char slot;
    unsigned int i,mode;
    slot=mysmb_paratroopa_slot(n);
    mysmb_actor_dispatch_fixture(ram,(n<32U?28U:30U)+n%2U);
    for(i=0U;i<6U;++i) if(i!=slot) ram[0xfU+i]=0U;
    ram[0x747U]=0U;ram[0x6dU]=0U;ram[0x86U]=0U;ram[0xceU]=0x30U;
    ram[0x417U+slot]=0xd7U;ram[0xcfU+slot]=0x80U;
    ram[0xa0U+slot]=0U;ram[0x434U+slot]=0U;
    if(n<32U) {
        ram[0xcfU+slot]=0xd0U;
        ram[0xa0U+slot]=(unsigned char)(n/8U==0U?0U:(n/8U==1U?1U:(n/8U==2U?0xffU:0xf9U)));
        ram[0x434U+slot]=(unsigned char)(n&4U?0xffU:0U);
        ram[0x58U+slot]=(unsigned char)(n&2U?0xf8U:8U);
    }
    else {
        mode=((n-32U)/2U)%8U;ram[9U]=(unsigned char)((n-32U)/16U);
        ram[0x401U+slot]=(unsigned char)(mode<2U?0x81U:(mode==2U?0x80U:0x7fU));
        ram[0x58U+slot]=(unsigned char)(mode==2U || mode==4U?0x81U:0x80U);
        if(mode==4U) ram[0xa0U+slot]=1U;
        if(mode==5U) ram[0xa0U+slot]=0xffU;
        if(mode==6U) ram[0x434U+slot]=0x80U;
        if(mode==7U) ram[0x434U+slot]=0xffU;
    }
}
static unsigned int mysmb_paratroopa_target(unsigned int pc)
{ return pc==0xbfadU?1U:(pc==0xbf02U?2U:(pc==0xbfd1U?3U:0U)); }
static int mysmb_paratroopa_argument(const char *text)
{
    static const char prefix[]="--fixture=t40-paratroopa=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    value=0U;digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<3U) {
        value=value*10U+(unsigned int)(text[i++]-'0');++digits;
    }
    if(!digits || text[i]!='\0' || value>=160U) return 0;
    return (int)value+1;
}
#endif
