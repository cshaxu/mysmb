#ifndef MYSMB_TIMER_FIXTURE_H
#define MYSMB_TIMER_FIXTURE_H
#include "entrance_fixture.h"
static void mysmb_timer_fixture(unsigned char *ram,unsigned char n)
{
    mysmb_entrance_fixture(ram,0U);
    ram[0xeU]=8U;ram[0x70bU]=1U;ram[0x716U]=1U;ram[0x70eU]=1U;
    ram[0x756U]=2U;ram[0x787U]=0U;ram[0x759U]=0U;
    ram[0xb5U]=1U;ram[0xceU]=0x80U;ram[0x7f8U]=2U;ram[0x7f9U]=0U;ram[0x7faU]=1U;
    ram[0x79eU]=0U;
    if(n==0U) {ram[0x770U]=0U;ram[0x7a2U]=0x18U;}
    if(n==1U) ram[0xeU]=0U;
    if(n==2U) ram[0xeU]=0x0bU;
    if(n==3U) ram[0xb5U]=2U;
    if(n==4U) ram[0xb5U]=0U;
    if(n==5U) ram[0x787U]=2U;
    if(n==6U || n==12U || n==13U) {ram[0x7f8U]=0U;ram[0x7faU]=0U;}
    if(n==7U || n==8U) {ram[0x7f8U]=1U;ram[0x7faU]=(unsigned char)(n-7U);}
    if(n==9U) {ram[0x7f8U]=0U;ram[0x7f9U]=1U;ram[0x7faU]=0U;}
    if(n==10U) ram[0x7f8U]=0U;
    if(n==11U) {ram[0x7f8U]=9U;ram[0x7f9U]=9U;ram[0x7faU]=9U;}
    if(n==12U) ram[0x759U]=0xffU;
    if(n==13U) ram[0x79eU]=8U;
    if(n==14U) ram[0x7faU]=0U;
    if(n==15U) {ram[0x7f8U]=0U;ram[0x7f9U]=9U;ram[0x7faU]=9U;}
}
static int mysmb_timer_argument(const char *text)
{
    static const char prefix[]="--fixture=t35-timer=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>15U) return 0;
    return (int)value+1;
}
#endif
