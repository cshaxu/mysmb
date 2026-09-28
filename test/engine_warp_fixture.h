#ifndef MYSMB_ENGINE_WARP_FIXTURE_H
#define MYSMB_ENGINE_WARP_FIXTURE_H
#include "game_entry_fixture.h"

/* Source RAM at NMI only; the ordinary engine reaches the active object. */
static void mysmb_engine_warp_fixture(unsigned char *ram,unsigned char scenario)
{
    unsigned int i,slot;
    mysmb_game_entry_fixture(ram,2U);
    ram[0xeU]=9U;ram[0x747U]=0xffU;ram[0x74eU]=1U;ram[0x71fU]=7U;
    ram[0x723U]=0x80U;ram[0x6d6U]=0x7fU;
    ram[0xceU]=0x80U;ram[0xb5U]=1U;
    for(i=0U;i<6U;++i) ram[0xfU+i]=0U;
    slot=scenario<6U ? scenario:0U;
    ram[0xfU+slot]=1U;ram[0x16U+slot]=0x34U;
    ram[0x1eU+slot]=0x5aU;ram[0x110U+slot]=0x5aU;
    ram[0x796U+slot]=0x5aU;ram[0x125U+slot]=0x5aU;
    ram[0x3c5U+slot]=0x5aU;ram[0x78aU+slot]=0x5aU;
    if(scenario==5U) ram[0x6d6U]=0xffU;
    if(scenario==6U) ram[0x723U]=0U;
    if(scenario==7U) ram[0xceU]=0x81U;
    if(scenario==8U) {ram[0xceU]=0x82U;ram[0xb5U]=2U;}
    if(scenario==9U) {ram[0xceU]=0x81U;ram[0xb5U]=2U;}
}
static int mysmb_engine_warp_argument(const char *text)
{
    static const char prefix[]="--fixture=t31-warp=";
    unsigned int i;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9'||text[i+1U]!='\0') return 0;
    return (int)(text[i]-'0')+1;
}
#endif
