#ifndef MYSMB_ENTRANCE_FIXTURE_H
#define MYSMB_ENTRANCE_FIXTURE_H
#include "game_entry_fixture.h"

/* Source-RAM setup at the ordinary NMI boundary; no CPU/stack redirection. */
static void mysmb_entrance_fixture(unsigned char *ram,unsigned char scenario)
{
    unsigned int i;
    mysmb_game_entry_fixture(ram,2U);
    ram[0xeU]=7U;ram[0x747U]=0xffU;ram[0x77fU]=0x10U;
    ram[0x74eU]=1U;ram[0x71fU]=7U;ram[0x769U]=0xffU;
    for(i=0U;i<6U;++i) ram[0xfU+i]=0U;
    for(i=0x500U;i<0x6a0U;++i) ram[i]=0U;
    ram[0x71aU]=7U;ram[0x71bU]=7U;ram[0x71cU]=0U;ram[0x71dU]=0xffU;
    ram[0x6dU]=7U;ram[0x86U]=0x40U;ram[0xb5U]=1U;ram[0xceU]=0x30U;
    ram[0x57U]=0U;ram[0x9fU]=0U;ram[0x1dU]=0U;ram[0x754U]=1U;
    ram[0x490U]=0xffU;ram[0x723U]=1U;ram[0x785U]=0U;
    ram[0x710U]=0U;ram[0x752U]=0U;ram[0x758U]=0U;
    ram[0x716U]=0U;ram[0x3c4U]=0U;ram[0x6deU]=2U;
    ram[0x778U]=0xa0U;ram[0x755U]=0x40U;
    if(scenario>=22U) {
        ram[0xeU]=(unsigned char)(scenario-22U);
        return;
    }
    if(scenario==1U) ram[0x752U]=3U;
    if(scenario==2U) ram[0xceU]=0x2fU;
    if(scenario>=3U && scenario<=10U) {
        ram[0x710U]=(scenario&1U)!=0U ? 6U:7U;
        if(scenario>=5U) {
            ram[0x3c4U]=0x20U;
            ram[0x6deU]=scenario<7U ? 2U:(scenario<9U ? 1U:0U);
            ram[0x86U]=0x41U;
        }
    }
    if(scenario>=11U && scenario<=15U) {
        static const unsigned char y[5]={0x92U,0x91U,0x90U,0U,0xffU};
        ram[0x752U]=2U;ram[0xceU]=y[scenario-11U];
    }
    if(scenario>=16U) {
        ram[0x752U]=2U;ram[0x758U]=scenario==17U ? 0xffU:8U;
        ram[0x399U]=scenario==16U ? 0x5fU:(scenario==17U ? 0x61U:0x60U);
        ram[0xceU]=scenario<20U ? 0x99U:0x98U;
        ram[0x86U]=(scenario&1U)!=0U ? 0x48U:0x47U;
    }
}

static int mysmb_entrance_argument(const char *text)
{
    static const char prefix[]="--fixture=t31-entrance=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>34U) return 0;
    return (int)value+1;
}
#endif
