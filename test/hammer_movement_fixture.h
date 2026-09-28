#ifndef MYSMB_HAMMER_MOVEMENT_FIXTURE_H
#define MYSMB_HAMMER_MOVEMENT_FIXTURE_H
#include "actor_dispatch_fixture.h"
#include "engine_normal_fixture.h"
static unsigned char mysmb_hammer_movement_slot(unsigned int n)
{ return (unsigned char)(n>=352U?5U:(n%2U)*5U); }
static unsigned int mysmb_hammer_movement_entry(unsigned int n)
{ return n<192U || (n>=256U && n<288U) ? 0xc9d8U : 0xca77U; }
static void mysmb_hammer_movement_fixture(unsigned char *ram,unsigned int n)
{
    static const unsigned char heights[6]={0U,0x6fU,0x70U,0x7fU,0x80U,0xffU};
    static const unsigned char states[16]={0U,1U,2U,3U,4U,5U,0x20U,0x40U,
        0x80U,0xc0U,0xa0U,0x42U,0x45U,0x85U,0x83U,0x43U};
    unsigned int mode,mix,i;
    unsigned char slot;
    if(n>=352U) {
        mysmb_engine_normal_fixture(ram,(unsigned char)(56U+n-352U));
        return;
    }
    if(n>=256U) {
        slot=mysmb_hammer_movement_slot(n);
        if(n<288U) {
            /* A solid landing lets the original background caller clear
             * the jumping bit before middle-height jump selection. */
            mode=(n-256U)/8U;mix=((n-256U)/2U)%4U;
            mysmb_hammer_movement_fixture(ram,(5U+mode)*2U+n%2U+mix*24U);
            for(i=0x500U;i<0x6a0U;++i) ram[i]=0x51U;
            ram[0x78aU+slot]=0U;
            ram[0x3cU+slot]=1U;
        }
        else {
            /* Y=$d0 takes the unmodified background early return, keeping
             * stunned/revival states intact for the movement entry. */
            mysmb_hammer_movement_fixture(ram,192U+n-288U);
            ram[0xcfU+slot]=0xd0U;
        }
        return;
    }
    slot=mysmb_hammer_movement_slot(n);
    mysmb_actor_dispatch_fixture(ram,(n<192U?10U:12U)+n%2U);
    for(i=0U;i<6U;++i) if(i!=slot) ram[0xfU+i]=0U;
    ram[0x747U]=0U;ram[0x6dU]=1U;ram[0x86U]=0x60U;ram[0xceU]=0x30U;
    ram[0x49aU+slot]=3U;ram[0x46U+slot]=2U;
    ram[0x58U+slot]=0xf8U;ram[0xa0U+slot]=0U;
    ram[0x434U+slot]=0xe9U;ram[0x417U+slot]=0xf0U;
    ram[0x3cU+slot]=0U;ram[0x3a2U+slot]=0U;
    if(n<192U) {
        mode=(n/2U)%12U;mix=n/24U;
        ram[0x6ccU]=(unsigned char)(mix&1U);
        ram[0x76aU]=(unsigned char)((mix&1U)^1U);
        ram[9U]=(unsigned char)(mix&2U?0x40U:0U);
        ram[0x87U+slot]=(unsigned char)(mix&2U?0x40U:0x80U);
        ram[0x796U+slot]=(unsigned char)(mix&4U?0U:2U);
        ram[0x7a8U]=2U;
        ram[0x7a8U+slot]=(unsigned char)(mix&3U);
        ram[0x7a9U+slot]=(unsigned char)(mix&4U?2U:0U);
        for(i=0U;i<9U;++i) ram[0x2aU+i]=(unsigned char)(mix&4U?1U:0U);
        if(mode==0U) ram[0x1eU+slot]=0x60U;
        else if(mode==3U) ram[0x1eU+slot]=1U;
        else if(mode>=4U && mode<=9U) ram[0xcfU+slot]=heights[mode-4U];
        else {
            ram[0x3cU+slot]=2U;
            if(mode==2U) ram[0x3a2U+slot]=2U;
            if(mode==10U) ram[0x87U+slot]=0x10U;
            if(mode==11U) ram[0x1eU+slot]=0x40U;
        }
    }
    else {
        mode=(n-192U)/4U;mix=(n-192U)%4U;
        ram[0x1eU+slot]=states[mode];
        ram[0x796U+slot]=(unsigned char)(mix&2U?14U:0U);
        ram[0x76aU]=(unsigned char)(mix&2U?1U:0U);
        ram[9U]=(unsigned char)(mix&2U?1U:0U);
        ram[0x58U+slot]=(unsigned char)(mix&2U?8U:0xf8U);
    }
}
static unsigned int mysmb_hammer_movement_target(unsigned int pc)
{
    return pc==0xba94U?1U:(pc==0xe143U?2U:(pc==0xbfadU?3U:
        (pc==0xbf02U?4U:(pc==0xc998U?5U:0U))));
}
/* Controlled RAM inputs at the naturally reached source entry. The actor
 * graphics/background phases otherwise replace the middle-height state
 * before the diagnostic frame. Apply equally with and without observers. */
static void mysmb_hammer_movement_entry_inputs(unsigned char *ram,unsigned int n)
{
    unsigned int mode,mix;
    unsigned char slot;
    static const unsigned char heights[4]={0x6fU,0x70U,0x7fU,0x80U};
    if(n>=300U && n<308U) {
        slot=mysmb_hammer_movement_slot(n);mix=n%4U;
        ram[0x76aU]=(unsigned char)(mix==1U?1U:0U);
        ram[0x796U+slot]=(unsigned char)(mix<2U?0U:(n==303U?15U:14U));
        if(n==307U) ram[0x16U+slot]=0U;
        return;
    }
    if(n<256U || n>=288U) return;
    slot=mysmb_hammer_movement_slot(n);mode=(n-256U)/8U;mix=((n-256U)/2U)%4U;
    ram[0x1eU+slot]=0U;ram[0x3cU+slot]=0U;
    ram[0xcfU+slot]=heights[mode];ram[0x6ccU]=(unsigned char)(mix&1U);
    ram[0x7a8U+slot]=(unsigned char)(mix/2U);
    ram[0x7a9U+slot]=(unsigned char)(mix&1U);
}
static int mysmb_hammer_movement_argument(const char *text)
{
    static const char prefix[]="--fixture=t40-hammer-movement=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    value=0U;digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<3U) {
        value=value*10U+(unsigned int)(text[i++]-'0');++digits;
    }
    if(!digits || text[i]!='\0' || value>=356U) return 0;
    return (int)value+1;
}
#endif
