#ifndef MYSMB_NORMAL_ACTOR_FIXTURE_H
#define MYSMB_NORMAL_ACTOR_FIXTURE_H
#include "actor_dispatch_fixture.h"

static unsigned char mysmb_normal_actor_slot(unsigned int n)
{
    return (unsigned char)((n % 2U) * 5U);
}

static void mysmb_normal_actor_fixture(unsigned char *ram,unsigned int n)
{
    unsigned int id;
    unsigned char slot;
    id=n<84U?n/4U:(n-84U)/2U;
    slot=mysmb_normal_actor_slot(n);
    mysmb_actor_dispatch_fixture(ram,id*2U+n%2U);
    ram[0x747U]=(unsigned char)(n<84U && (n%4U)>=2U ? 0xffU:0U);
    ram[0x6dU]=0U;ram[0x86U]=0U;ram[0xceU]=0x30U;
    ram[0x49aU+slot]=3U;ram[0x46U+slot]=2U;
    ram[0x58U+slot]=0xf8U;ram[0xa0U+slot]=0U;ram[0x434U+slot]=0U;
    ram[0x401U+slot]=0U;ram[0x417U+slot]=0U;
    ram[0x3c5U+slot]=0xa5U;
}

static unsigned int mysmb_normal_actor_target(unsigned int pc)
{
    static const unsigned short targets[20]={
        0xf1afU,0xf152U,0xe87dU,0xe243U,0xdfc1U,0xda33U,0xd853U,0xd67aU,
        0xca77U,0xc9d8U,0xcb89U,0xcc36U,0xcc4aU,0xc9b0U,0xd3b0U,
        0xcaf9U,0xcaffU,0xcb25U,0xcf28U,0xcedfU
    };
    unsigned int i;
    for(i=0U;i<20U;++i) if(pc==targets[i]) return i+1U;
    return 0U;
}

static int mysmb_normal_actor_argument(const char *text)
{
    static const char prefix[]="--fixture=t39-normal-actor=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    value=0U;digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<3U) {
        value=value*10U+(unsigned int)(text[i++]-'0');++digits;
    }
    if(!digits || text[i]!='\0' || value>=126U) return 0;
    return (int)value+1;
}
#endif
