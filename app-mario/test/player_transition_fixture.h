#ifndef MYSMB_PLAYER_TRANSITION_FIXTURE_H
#define MYSMB_PLAYER_TRANSITION_FIXTURE_H
#include "entrance_fixture.h"
/* Controlled RAM inputs at ordinary NMI; children still execute normally. */
static void mysmb_player_transition_fixture(unsigned char *ram,unsigned char scenario)
{
    static const unsigned char timers[4]={0U,1U,2U,0xffU};
    mysmb_entrance_fixture(ram,0U);
    ram[0x70bU]=1U;ram[0x716U]=1U;ram[0x722U]=0U;
    if(scenario<6U) {
        ram[0xeU]=1U;ram[0xb5U]=scenario<3U ? 0U:1U;
        ram[0xceU]=scenario%3U==0U ? 0xe3U:(scenario%3U==1U ? 0xe4U:0xffU);
    }
    else if(scenario<14U) {
        ram[0xeU]=2U;ram[0x86U]=(scenario&1U)!=0U ? 0x41U:0x40U;
        ram[0x6deU]=timers[(scenario-6U)/2U];
    }
    else if(scenario<26U) {
        unsigned char selector;
        selector=(unsigned char)((scenario-14U)/3U);
        ram[0xeU]=3U;ram[0xceU]=0xffU;
        ram[0x6deU]=(unsigned char)((scenario-14U)%3U);
        ram[0x74eU]=selector==2U ? 3U:(selector==0U ? 0U:1U);
        ram[0x6d6U]=selector==3U ? 1U:0U;
    }
    else {
        ram[0xeU]=7U;ram[0x752U]=2U;ram[0x758U]=0U;
        ram[0xceU]=scenario==26U ? 0U:0x91U;
    }
}
static int mysmb_player_transition_argument(const char *text)
{
    static const char prefix[]="--fixture=t32-transition=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>27U) return 0;
    return (int)value+1;
}
#endif
