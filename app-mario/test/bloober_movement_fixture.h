#ifndef MYSMB_BLOOBER_MOVEMENT_FIXTURE_H
#define MYSMB_BLOOBER_MOVEMENT_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_bloober_slot(unsigned int n)
{ return (unsigned char)((n % 2U) * 5U); }
static void mysmb_bloober_fixture(unsigned char *ram, unsigned int n)
{
    static const unsigned char forces[8] = {0U,1U,2U,3U,0x7fU,0x80U,0xfeU,0xffU};
    unsigned int i, v;
    unsigned char slot;
    slot = mysmb_bloober_slot(n); v = n / 2U;
    mysmb_actor_dispatch_fixture(ram, 14U + n % 2U);
    for (i=0U; i<6U; ++i) if (i!=slot) ram[0xfU+i]=0U;
    ram[0x747U]=0U;ram[0x6ccU]=(unsigned char)((v/16U)&1U);
    ram[0x6dU]=1U;ram[0x86U]=(unsigned char)(v&1U?0x60U:0x80U);
    ram[0xceU]=(unsigned char)(v&2U?0x91U:0x90U);
    ram[0x45U]=(unsigned char)(v&4U?1U:2U);
    ram[0x46U+slot]=(unsigned char)(v&4U?2U:1U);
    ram[0x7a8U+slot]=(unsigned char)(v&8U?0xffU:0U);
    ram[0x7a7U+slot]=0U;
    ram[0xa0U+slot]=(unsigned char)((v/32U)&3U);
    ram[0x434U+slot]=forces[v%8U];
    ram[0x58U+slot]=(unsigned char)(v&4U?0xffU:2U);
    ram[0x796U+slot]=(unsigned char)(v&16U?3U:0U);
    /* NMI increments this before movement: exercise phases zero and one. */
    ram[9U]=(unsigned char)(v<128U?0xffU:0U);
    if (n>=480U) {
        ram[0x1eU+slot]=0x20U;
        ram[0xa0U+slot]=(unsigned char)(v&1U?1U:0xffU);
    }
}
static int mysmb_bloober_argument(const char *text)
{
    static const char prefix[]="--fixture=t40-bloober=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    value=0U;digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<3U) {
        value=value*10U+(unsigned int)(text[i++]-'0');++digits;
    }
    if(!digits || text[i]!='\0' || value>=512U) return 0;
    return (int)value+1;
}
#endif
