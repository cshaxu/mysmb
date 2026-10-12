#ifndef MYSMB_PLAYER_END_LEVEL_FIXTURE_H
#define MYSMB_PLAYER_END_LEVEL_FIXTURE_H
#include "entrance_fixture.h"
static void mysmb_player_end_level_fixture(unsigned char *ram,unsigned char scenario,
                                           const unsigned char *prg)
{
    mysmb_entrance_fixture(ram,0U);
    ram[0x70bU]=1U;ram[0x716U]=1U;
    if(scenario<4U) {
        ram[0xeU]=4U;ram[0x1bU]=scenario<2U?0x30U:0U;
        ram[0xceU]=(scenario&1U)!=0U?0x9eU:0x9dU;
        ram[0x713U]=0x40U;
    } else if(scenario<28U) {
        unsigned char n;
        n=(unsigned char)(scenario-4U);ram[0xeU]=5U;
        ram[0xceU]=n==0U?0xadU:0xaeU;
        ram[0x723U]=n==1U?0U:1U;
        ram[0x490U]=n==2U?0U:1U;
        ram[0x746U]=n<4U?0U:5U;
        if(n==3U) {ram[0x490U]=0U;ram[0x746U]=2U;}
        ram[0x75cU]=n==4U?0U:2U;
        ram[0x75fU]=n>=8U?(unsigned char)((n-8U)/2U):0U;
        ram[0x748U]=(n&1U)!=0U?0xffU:0U;
        if(n>=8U) ram[0x748U]=(unsigned char)(prg[0x32c2U+ram[0x75fU]]-
            ((n&1U)!=0U?0U:1U));
        ram[0x75dU]=0xffU;
    } else {
        mysmb_entrance_fixture(ram,7U);
        ram[0x70bU]=1U;ram[0x716U]=1U;ram[0x86U]=0x40U;
        ram[0x6deU]=1U;ram[0x75bU]=7U;
    }
}
static int mysmb_player_end_level_argument(const char *text)
{
    static const char prefix[]="--fixture=t32-end-level=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>28U) return 0;
    return (int)value+1;
}
#endif
