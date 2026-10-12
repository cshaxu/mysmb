#ifndef MYSMB_BULLET_MOVEMENT_FIXTURE_H
#define MYSMB_BULLET_MOVEMENT_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_bullet_movement_slot(unsigned int n)
{ return (unsigned char)((n%2U)*5U); }
static void mysmb_bullet_movement_fixture(unsigned char *ram,unsigned int n)
{
    static const unsigned char states[8]={0U,1U,0x1fU,0x20U,0x21U,0x3fU,0x80U,0xffU};
    unsigned int i,v;unsigned char slot;
    slot=mysmb_bullet_movement_slot(n);v=n/2U;
    mysmb_actor_dispatch_fixture(ram,16U+n%2U);
    for(i=0U;i<6U;++i) if(i!=slot) ram[0xfU+i]=0U;
    ram[0x747U]=0U;ram[0x6dU]=0U;ram[0x86U]=0U;ram[0xceU]=0x30U;
    ram[0x1eU+slot]=states[v%8U];
    ram[0xa0U+slot]=(unsigned char)(v&8U?0xfdU:1U);
    ram[0x434U+slot]=(unsigned char)(v&16U?0xffU:0U);
    ram[0x417U+slot]=(unsigned char)(v&32U?0xffU:0U);
    ram[0x401U+slot]=(unsigned char)(v&8U?0xffU:0U);
    ram[0x58U+slot]=(unsigned char)(v&16U?0x18U:0x80U);
}
static int mysmb_bullet_movement_argument(const char *text)
{
    static const char prefix[]="--fixture=t40-bullet-movement=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    value=0U;digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<3U) {
        value=value*10U+(unsigned int)(text[i++]-'0');++digits;
    }
    if(!digits || text[i]!='\0' || value>=128U) return 0;
    return (int)value+1;
}
#endif
