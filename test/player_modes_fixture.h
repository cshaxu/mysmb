#ifndef MYSMB_PLAYER_MODES_FIXTURE_H
#define MYSMB_PLAYER_MODES_FIXTURE_H
#include "entrance_fixture.h"
/* RAM inputs before a normal NMI: nonzero TimerControl decrements once. */
static void mysmb_player_modes_fixture(unsigned char *ram,unsigned char scenario)
{
    static const unsigned char modes[22]={9U,9U,9U,9U,9U,10U,10U,10U,10U,10U,
        11U,11U,11U,12U,12U,12U,12U,12U,9U,9U,10U,10U};
    static const unsigned char timers[22]={0xf9U,0xf9U,0xc5U,0xc4U,1U,
        0xf1U,0xf0U,0xc9U,0xc8U,1U,0xf1U,0xf0U,1U,
        0xc1U,0xc2U,0xc0U,1U,0xffU,0xffU,0xffU,0xf2U,0xf1U};
    mysmb_entrance_fixture(ram,0U);
    ram[0xeU]=modes[scenario];ram[0x747U]=timers[scenario];
    ram[0x70bU]=(scenario==0U || scenario==5U || scenario==20U)?0U:1U;ram[0x70dU]=5U;
    ram[0x716U]=1U;ram[0x3c4U]=0xa7U;
    ram[9U]=(unsigned char)(scenario*13U);
    ram[0x79fU]=scenario==18U?9U:0U;
}
static int mysmb_player_modes_argument(const char *text)
{
    static const char prefix[]="--fixture=t32-modes=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>21U) return 0;
    return (int)value+1;
}
#endif
