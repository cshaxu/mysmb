#ifndef MYSMB_PLAYER_CONTROL_FIXTURE_H
#define MYSMB_PLAYER_CONTROL_FIXTURE_H
#include "entrance_fixture.h"

/* Original NMI inputs only. Movement freeze is a real source state, not a
 * patched return; its physics child still executes in the original ROM. */
static void mysmb_player_control_fixture(unsigned char *ram, unsigned char scenario)
{
    static const unsigned char high[12] = {0,1,2,3,4,5,6,7,0x7f,0x80,0x81,0xff};
    mysmb_entrance_fixture(ram,0U);
    ram[0xeU]=8U;ram[0x70bU]=1U;ram[0x716U]=1U;
    ram[0xceU]=0x80U;ram[0x3c4U]=0xa3U;ram[0x6fcU]=0xc1U;
    ram[0x712U]=0U;ram[0x759U]=0U;ram[0x743U]=0U;ram[0x7b1U]=0U;
    if(scenario>=1U && scenario<=4U) {
        ram[0x74eU]=0U;
        ram[0xceU]=scenario==1U ? 0xcfU:0xd0U;
        if(scenario==3U) ram[0xb5U]=0U;
        if(scenario==4U) ram[0xb5U]=2U;
    }
    if(scenario==5U) {ram[0xeU]=11U;ram[0x747U]=0xefU;}
    if(scenario>=6U && scenario<=8U) {
        ram[0x6fcU]=scenario==8U ? 4U:6U;
        if(scenario==7U) ram[0x1dU]=1U;
    }
    if(scenario==9U || scenario==10U) {
        ram[0x754U]=0U;ram[0x6fcU]=scenario==10U ? 4U:0U;
    }
    if(scenario==11U) ram[0x57U]=0x20U;
    if(scenario==12U) ram[0x57U]=0xe0U;
    if(scenario==13U) {ram[0x57U]=0U;ram[0x45U]=2U;}
    if(scenario==14U) ram[0xceU]=0x3fU;
    if(scenario==15U) ram[0xceU]=0x40U;
    if(scenario>=16U && scenario<=18U) {
        ram[0xeU]=scenario==16U ? 5U:(scenario==17U ? 4U:7U);
        ram[0x1bU]=0x30U;ram[0x710U]=6U;
        if(scenario==18U) ram[0x3c4U]=0U;
    }
    if(scenario>=19U && scenario<=42U) {
        ram[0xb5U]=high[(scenario-19U)%12U];
        ram[0x743U]=scenario>=31U ? 1U:0U;
    }
    if(scenario>=43U) {
        ram[0xb5U]=6U;
        if(scenario==43U) ram[0x712U]=1U;
        if(scenario==44U) ram[0x7b1U]=1U;
        if(scenario==45U) {ram[0x743U]=1U;ram[0x759U]=1U;}
        if(scenario==46U) {ram[0xeU]=11U;ram[0x747U]=0xefU;ram[0xb5U]=3U;}
        if(scenario==47U) {ram[0xeU]=11U;ram[0x747U]=0xefU;ram[0xb5U]=4U;}
        if(scenario==48U) {ram[0xeU]=2U;ram[0xb5U]=1U;ram[0x86U]=0x41U;}
        if(scenario==49U) ram[0xfcU]=1U;
    }
}
static int mysmb_player_control_argument(const char *text)
{
    static const char prefix[]="--fixture=t32-control=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>49U) return 0;
    return (int)value+1;
}
#endif
