#ifndef MYSMB_FIREBALL_DISPATCH_FIXTURE_H
#define MYSMB_FIREBALL_DISPATCH_FIXTURE_H
#include "entrance_fixture.h"
/* Source RAM before ordinary NMI; all original children execute. */
static void mysmb_fireball_dispatch_fixture(unsigned char *ram,unsigned char scenario)
{
    unsigned char n;
    mysmb_entrance_fixture(ram,0U);n=(unsigned char)(scenario%16U);
    ram[0xeU]=8U;ram[0x70bU]=1U;ram[0x716U]=1U;ram[0xceU]=0x80U;
    ram[0x756U]=n<4U?n:2U;ram[0x24U]=0U;ram[0x25U]=0U;
    ram[0x6ceU]=(n&1U);ram[0x70cU]=6U;ram[0xdU]=0U;
    ram[0x74eU]=scenario>=16U?0U:1U;
    ram[0x33U]=1U;ram[0x70eU]=1U;
    ram[0xdbU]=0xf8U;ram[0xdcU]=0xf8U;ram[0xddU]=0xf8U;
    if(n==6U) ram[0x24U]=1U;
    if(n==7U) ram[0xdU]=0x40U;
    if(n==8U) ram[0xb5U]=0U;
    if(n==9U) ram[0xb5U]=2U;
    if(n==10U) {ram[0x754U]=0U;ram[0x1dU]=1U;ram[0x714U]=4U;}
    if(n==11U) ram[0x1dU]=3U;
    if(n==12U) ram[0x70cU]=0U;
    if(n==13U) ram[0x70cU]=0xffU;
    if(n==14U) ram[0x6ceU]=0xffU;
    if(n==15U) ram[0x25U]=0x80U;
}
static int mysmb_fireball_dispatch_argument(const char *text)
{
    static const char prefix[]="--fixture=t34-dispatch=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>31U) return 0;
    return (int)value+1;
}
#endif
