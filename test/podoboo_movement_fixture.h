#ifndef MYSMB_PODOBOO_MOVEMENT_FIXTURE_H
#define MYSMB_PODOBOO_MOVEMENT_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_podoboo_slot(unsigned int n)
{ return (unsigned char)((n / 32U) * 5U); }
static void mysmb_podoboo_fixture(unsigned char *ram, unsigned int n)
{
    static const unsigned char randoms[8]={0U,1U,7U,8U,15U,0x7fU,0x80U,0xffU};
    static const unsigned char timers[4]={0U,1U,2U,0xffU};
    unsigned char slot;
    slot=mysmb_podoboo_slot(n);
    mysmb_actor_dispatch_fixture(ram,24U+(slot==5U?1U:0U));
    ram[0x747U]=0U; ram[0x6dU]=0U; ram[0x86U]=0U; ram[0xceU]=0x30U;
    ram[0x796U+slot]=timers[(n/8U)%4U];
    ram[0x7a8U+slot]=randoms[n%8U];
    ram[0x434U+slot]=0x71U; ram[0x417U+slot]=0xe9U;
    ram[0xa0U+slot]=0xffU; ram[0x1eU+slot]=2U;
    ram[0x49aU+slot]=0x0bU; ram[0x46U+slot]=2U;
}
static unsigned int mysmb_podoboo_target(unsigned int pc)
{ return pc==0xc2f7U ? 1U : (pc==0xbf92U ? 2U : 0U); }
static int mysmb_podoboo_argument(const char *text)
{
    static const char prefix[]="--fixture=t40-podoboo=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    value=0U;digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<2U) {
        value=value*10U+(unsigned int)(text[i++]-'0'); ++digits;
    }
    if(!digits || text[i]!='\0' || value>=64U) return 0;
    return (int)value+1;
}
#endif
