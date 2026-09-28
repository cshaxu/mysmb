#ifndef MYSMB_FIREBALL_CORE_FIXTURE_H
#define MYSMB_FIREBALL_CORE_FIXTURE_H
#include "entrance_fixture.h"
/* Controlled source RAM before ordinary NMI; no CPU or ROM modification. */
static void mysmb_fireball_core_fixture(unsigned char *ram,unsigned char scenario)
{
    static const unsigned char states[16]={0,1,2,3,127,128,133,134,255,1,1,1,1,2,2,1};
    unsigned char n,slot;
    n=(unsigned char)(scenario%16U);slot=(unsigned char)(scenario/16U);
    mysmb_entrance_fixture(ram,0U);
    ram[0xeU]=8U;ram[0x70bU]=1U;ram[0x716U]=1U;ram[0x756U]=2U;
    ram[0x74eU]=1U;ram[0x33U]=(unsigned char)(1U+(n&1U));
    ram[0x70eU]=1U;ram[0x24U]=0U;ram[0x25U]=0U;
    ram[0x24U+slot]=states[n];ram[0x6dU]=1U;ram[0x86U]=0xfcU;
    ram[0xceU]=0x80U;ram[0x74U+slot]=1U;ram[0x8dU+slot]=0x80U;
    ram[0xd5U+slot]=0x80U;ram[0xbcU+slot]=1U;ram[0x4a0U+slot]=7U;
    ram[0x71aU]=1U;ram[0x71cU]=0U;ram[0x71bU]=1U;ram[0x71dU]=0xffU;
    if(n==9U) {ram[0x74U+slot]=0U;ram[0x8dU+slot]=0xd0U;}
    if(n==10U) {ram[0x74U+slot]=2U;ram[0x8dU+slot]=0x30U;}
    if(n==11U) ram[0xbcU+slot]=2U;
    if(n==12U) ram[0xbcU+slot]=0U;
    if(n==13U) {ram[0x86U]=0xffU;ram[0x6dU]=0xffU;}
    if(n==14U) ram[0x86U]=0xfbU;
    if(n==15U) ram[0xd5U+slot]=0xd8U;
}
static int mysmb_fireball_core_argument(const char *text)
{
    static const char prefix[]="--fixture=t34-core=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>31U) return 0;
    return (int)value+1;
}
#endif
