#ifndef MYSMB_HAMMER_CHAIN_FIXTURE_H
#define MYSMB_HAMMER_CHAIN_FIXTURE_H
#include "entrance_fixture.h"
/* Only RAM is initialized at the ordinary NMI boundary. */
static void mysmb_hammer_chain_fixture(unsigned char *ram,unsigned char n)
{
    unsigned int i;
    unsigned char slot,state;
    mysmb_entrance_fixture(ram,0U);
    ram[0xeU]=8U;ram[0x747U]=0U;ram[0x70bU]=1U;ram[0x716U]=1U;
    for(i=0U;i<9U;++i) {ram[0x2aU+i]=0U;ram[0x6beU+i]=0x5aU;}
    ram[0x7a7U]=0U;
    if(n<27U) {
        slot=(unsigned char)(n%9U);
        /* NMI rotates the LSFR before the source allocation entry. */
        ram[0x7a8U]=(unsigned char)(slot*2U);
        ram[0xfU]=1U;ram[0x16U]=5U;ram[0x1eU]=0U;
        ram[0x3cU]=0x40U;ram[0x3a2U]=0U;
        ram[0x6eU]=7U;ram[0x87U]=0x80U;ram[0xb6U]=1U;
        ram[0xcfU]=0x90U;ram[0x46U]=1U;
        if(n>=9U && n<18U) ram[0x2aU+slot]=0x90U;
        if(n>=18U) ram[0xfU+4U+slot/3U]=1U;
    }
    else {
        slot=(unsigned char)((n-27U)%9U);
        state=n<36U?0x90U:(n<45U?0x82U:0x81U);
        ram[0x2aU+slot]=state;ram[0x6aeU+slot]=4U;
        ram[0x4a2U+slot]=7U;ram[0x6f3U+slot]=0x40U;
        ram[0x22U]=0xffU;ram[0x4aU]=(unsigned char)(1U+(n&1U));
        ram[0x72U]=7U;ram[0x8bU]=(n&1U)!=0U?0xffU:0xfeU;
        ram[0xd3U]=(n&2U)!=0U?3U:0x90U;
        ram[0x7aU+slot]=7U;ram[0x93U+slot]=0x80U;
        ram[0xc2U+slot]=1U;ram[0xdbU+slot]=0x70U;
        ram[0x64U+slot]=(n&1U)!=0U?0xf0U:0x10U;
        ram[0xacU+slot]=0xfeU;ram[0x440U+slot]=0xf8U;
        if(n>=54U) ram[0x747U]=0xffU;
    }
}
static int mysmb_hammer_chain_argument(const char *text)
{
    static const char prefix[]="--fixture=t36-hammer=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>62U) return 0;
    return (int)value+1;
}
#endif
