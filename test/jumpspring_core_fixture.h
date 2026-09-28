#ifndef MYSMB_JUMPSPRING_CORE_FIXTURE_H
#define MYSMB_JUMPSPRING_CORE_FIXTURE_H
#include "entrance_fixture.h"
static void mysmb_jumpspring_core_fixture(unsigned char *ram,unsigned char n)
{
    unsigned char slot;
    mysmb_entrance_fixture(ram,0U);
    slot=n>=24U?5U:(n>=20U?2U:0U);
    ram[0xeU]=8U;ram[0x70bU]=1U;ram[0x716U]=1U;
    ram[0x747U]=n>=20U && n<24U?0xffU:0U;
    ram[0x70eU]=(unsigned char)(n%5U);
    ram[0x786U]=(n&1U)!=0U?2U:0U;ram[0x6dbU]=0xfaU;
    ram[0xdU]=(n/5U&2U)!=0U?0x80U:0U;
    ram[0xfU+slot]=1U;ram[0x16U+slot]=0x32U;
    ram[0x6eU+slot]=7U;ram[0x87U+slot]=0x80U;
    ram[0xb6U+slot]=1U;ram[0xcfU+slot]=0x90U;
    ram[0x58U+slot]=n>=24U?0xf8U:0x90U;
    ram[0x46U+slot]=(n&1U)!=0U?2U:1U;ram[0x3c5U+slot]=0U;
    if(n==29U) ram[0x87U+slot]=0xf8U;
    if(n==30U) {ram[0x6eU+slot]=6U;ram[0x87U+slot]=0x80U;}
    if(n==31U) ram[0x6eU+slot]=8U;
}
static int mysmb_jumpspring_core_argument(const char *text)
{
    static const char prefix[]="--fixture=t35-jumpspring=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>31U) return 0;
    return (int)value+1;
}
#endif
