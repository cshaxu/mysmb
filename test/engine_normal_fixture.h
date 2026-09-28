#ifndef MYSMB_ENGINE_NORMAL_FIXTURE_H
#define MYSMB_ENGINE_NORMAL_FIXTURE_H
#include "game_entry_fixture.h"

/* Ordinary engine entry from NMI. Cases 0..31 use Y=$d0 for the terrain
 * early return. Cases 32..55 exercise background-entry branch families.
 * Neither fixture bypasses the real parent calls. */
static void mysmb_engine_normal_fixture(unsigned char *ram,unsigned char scenario)
{
    static const unsigned char states[12]={0,1,2,3,4,5,0x20,0x40,0x41,0x80,0xa0,0xc0};
    unsigned int i;
    mysmb_game_entry_fixture(ram,2U);
    ram[0xeU]=9U;ram[0x747U]=0U;ram[0x74eU]=1U;ram[0x71fU]=7U;
    ram[0x71bU]=7U;ram[0x71cU]=0U;ram[0x71dU]=0xffU;
    for(i=0U;i<6U;++i) ram[0xfU+i]=0U;
    ram[0xfU]=1U;ram[0x16U]=6U;ram[0x1eU]=states[scenario<24U ? scenario/2U:3U];
    ram[0x6eU]=7U;ram[0x87U]=0x80U;ram[0xb6U]=1U;ram[0xcfU]=0xd0U;
    ram[0x58U]=(scenario&1U)!=0U ? 0xf8U:8U;
    ram[0x401U]=0x77U;ram[0x417U]=0x80U;ram[0x434U]=0x80U;ram[0xa0U]=0U;
    ram[0x796U]=0U;ram[0x76aU]=scenario>=24U ? 1U:0U;
    ram[9U]=(unsigned char)(scenario&1U);ram[0x46U]=2U;
    ram[0x49aU]=9U;ram[0x6e5U]=0x30U;
    if(scenario==26U || scenario==27U) ram[0x76aU]=0U;
    /* Keep interval timers fixed by inhibiting this NMI's interval tick. */
    ram[0x77fU]=0x10U;
    if(scenario==28U || scenario==29U) ram[0x796U]=0x0eU;
    if(scenario==29U) ram[0x16U]=0U;
    if(scenario==30U) {ram[0x1eU]=4U;ram[0x796U]=1U;}
    if(scenario==31U) ram[0x1eU]=6U;
    if(scenario>=32U) {
        static const unsigned char ids[24]={14,14,14,14,14,14,14,14,
            14,14,14,14,14,14,14,14,18,18,7,5,6,14,14,14};
        static const unsigned char speeds[24]={0,1,0xfd,0xfe,0xff,1,1,1,
            1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0};
        static const unsigned char tiles[24]={0x51,0x51,0x51,0x51,0x51,
            0,0x26,0xc2,0xc3,0x5f,0x60,0x23,0x51,0x51,0x51,0x51,
            0,0,0,0,0,0,0,0};
        unsigned int which;
        which=scenario-32U;
        for(i=0x500U;i<0x6a0U;++i) ram[i]=0U;
        ram[0x16U]=ids[which];ram[0x1eU]=0U;
        ram[0x87U]=0x40U;ram[0xcfU]=0x6fU;
        ram[0xa0U]=speeds[which];ram[0x46U]=1U;
        /* Enemy page 7 selects buffer 2; bottom column 4, row $60. */
        ram[0x634U]=tiles[which];
        if(which==12U || which==13U) ram[0x635U]=0x51U;
        if(which==13U) ram[0xa0U]=0U;
        if(which==14U) ram[0x1eU]=0x20U;
        if(which==15U) ram[0xcfU]=5U;
        if(which==16U) ram[0xcfU]=0x24U;
        if(which==17U) ram[0xcfU]=0x25U;
        if(which==21U) ram[0xcfU]=0xc1U;
        if(which==22U) ram[0xcfU]=0xc2U;
        if(which==23U) ram[0xcfU]=0xffU;
    }
}
static int mysmb_engine_normal_argument(const char *text)
{
    static const char prefix[]="--fixture=t31-normal=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>55U) return 0;
    return (int)value+1;
}
#endif
