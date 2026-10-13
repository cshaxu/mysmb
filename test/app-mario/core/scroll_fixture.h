#ifndef MYSMB_SCROLL_FIXTURE_H
#define MYSMB_SCROLL_FIXTURE_H
#include "game_entry_fixture.h"

/* Ordinary NMI -> GameRoutines -> VerticalPipeEntry -> ScrollHandler.
 * The pipe caller preserves the saved horizontal scroll force. */
static void mysmb_scroll_fixture(unsigned char *ram,unsigned char scenario)
{
    static const unsigned char force[14]={0,1,2,0x7f,0x80,0x80,0x81,0xff,
        0xff,0xff,1,2,2,2};
    static const unsigned char platform[14]={0,0,0,0,0,0,0,0,1,2,0xff,0,0,0};
    static const unsigned char position[14]={0x70,0x70,0x50,0x6f,0x6f,0x70,
        0x70,0x70,0x70,0x70,0x70,0x4f,0x6f,0x70};
    unsigned int i;
    mysmb_game_entry_fixture(ram,2U);
    ram[0xeU]=3U;ram[0x747U]=0xffU;ram[0x77fU]=0x10U;
    ram[0x74eU]=1U;ram[0x71fU]=7U;ram[0x6deU]=0xffU;
    for(i=0U;i<6U;++i) ram[0xfU+i]=0U;
    ram[0x71aU]=7U;ram[0x71bU]=8U;ram[0x71cU]=0xf0U;ram[0x71dU]=0xefU;
    ram[0x6dU]=8U;ram[0x86U]=0x40U;ram[0xb5U]=1U;ram[0xceU]=0x50U;
    ram[0x57U]=0x18U;ram[0xcU]=0U;ram[0x723U]=0U;ram[0x785U]=0U;
    ram[0x6ffU]=scenario<14U ? force[scenario]:1U;
    ram[0x3a1U]=scenario<14U ? platform[scenario]:0U;
    ram[0x755U]=scenario<14U ? position[scenario]:0x70U;
    ram[0x778U]=0xa6U;ram[0x73dU]=0xf8U;ram[0x795U]=0x37U;
    if(scenario==14U) ram[0x723U]=1U;
    if(scenario==15U) ram[0x785U]=0x20U;
    if(scenario>=16U) {
        ram[0x723U]=1U;
        ram[0x71aU]=0xffU;ram[0x71bU]=0U;
        ram[0x71cU]=0x10U;ram[0x71dU]=0x0fU;
        ram[0x6dU]=scenario<20U ? 0xffU:0U;
        /* At the right edge, raw bits are $7f: d5 set without d7. */
        ram[0x86U]=scenario<20U ? 0U:0x0fU;
        ram[0xcU]=(unsigned char)(scenario&3U);
    }
}

static int mysmb_scroll_argument(const char *text)
{
    static const char prefix[]="--fixture=t31-scroll=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>23U) return 0;
    return (int)value+1;
}
#endif
