#ifndef MYSMB_BUBBLE_CORE_FIXTURE_H
#define MYSMB_BUBBLE_CORE_FIXTURE_H
#include "entrance_fixture.h"
static void mysmb_bubble_core_fixture(unsigned char *ram,unsigned char scenario)
{
    unsigned char slot,n;
    mysmb_entrance_fixture(ram,0U);
    slot=scenario<24U?(unsigned char)(scenario/8U):(unsigned char)((scenario-24U)/2U);
    n=scenario<24U?(unsigned char)(scenario%8U):(unsigned char)(1U+(scenario&1U));
    ram[0xeU]=8U;ram[0x70bU]=1U;ram[0x716U]=1U;ram[0x756U]=0U;
    ram[0x74eU]=0U;ram[0x70eU]=1U;ram[0x33U]=(unsigned char)(1U+(n&1U));
    ram[0x6dU]=0xffU;ram[0x86U]=0xffU;ram[0xceU]=n==2U?0xf0U:0x80U;
    ram[0xe4U]=0x80U;ram[0xe5U]=0x80U;ram[0xe6U]=0x80U;
    ram[0xe4U+slot]=n<=2U?0xf8U:(n<=4U?0x20U:(n==5U?0xffU:(n==6U?0U:1U)));
    ram[0x42cU+slot]=n==4U?0xffU:0U;
    ram[0x792U]=n==0U?4U:0U;
    /* NMI shifts this register bank once before BubbleCheck. */
    ram[0x7a7U+slot]=(unsigned char)((n&1U)!=0U?2U:0U);
    ram[0x7a8U+slot]=(unsigned char)((n&1U)!=0U?2U:0U);
}
static int mysmb_bubble_core_argument(const char *text)
{
    static const char prefix[]="--fixture=t35-bubble=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>29U) return 0;
    return (int)value+1;
}
#endif
