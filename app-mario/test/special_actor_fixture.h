#ifndef MYSMB_SPECIAL_ACTOR_FIXTURE_H
#define MYSMB_SPECIAL_ACTOR_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_special_actor_id(unsigned int n)
{
    static const unsigned char ids[18]={21U,27U,28U,29U,30U,31U,32U,33U,34U,
        36U,37U,38U,39U,40U,41U,42U,43U,44U};
    return n<72U ? ids[n/4U] : (n<86U ? (unsigned char)(36U+(n-72U)/2U):37U);
}
static unsigned char mysmb_special_actor_slot(unsigned int n)
{ return (unsigned char)(n<86U ? (n%2U)*5U:n-86U); }
static unsigned int mysmb_special_actor_mode(unsigned int n)
{
    unsigned char id;
    if(n>=86U) return 6U;
    if(n>=72U) return 5U;
    id=mysmb_special_actor_id(n);
    return id==21U ? 1U:(id<36U ? 2U:(id>=43U ? 3U:4U));
}
static unsigned int mysmb_special_actor_entry(unsigned int n)
{
    static const unsigned short entries[6]={0xc935U,0xc947U,0xc94dU,0xc965U,0xc982U,0xc998U};
    return entries[mysmb_special_actor_mode(n)-1U];
}
static void mysmb_special_actor_fixture(unsigned char *ram,unsigned int n)
{
    unsigned char slot,id,i;
    id=mysmb_special_actor_id(n);slot=mysmb_special_actor_slot(n);
    mysmb_actor_dispatch_fixture(ram,(unsigned int)id*2U+(slot==5U?1U:0U));
    for(i=0U;i<6U;++i) ram[0xfU+i]=(unsigned char)(0x80U+i);
    ram[0xfU+slot]=1U;ram[0x16U+slot]=id;ram[0x1eU+slot]=0U;
    ram[0x6eU+slot]=(unsigned char)(n>=86U?4U:1U);ram[0x87U+slot]=0x70U;
    ram[0xcfU+slot]=0x80U;ram[0xb6U+slot]=1U;ram[0x6e5U+slot]=0x40U;
    ram[0x747U]=(unsigned char)(n>=86U || (n<72U && n%4U>=2U)?0xffU:0U);
    ram[0x6dU]=0U;ram[0x86U]=0U;ram[0xceU]=0x30U;
    ram[0x49aU+slot]=(unsigned char)(id>=43U?4U:6U);
    ram[0x3a2U+slot]=(unsigned char)(id>=43U?0U:0xffU);
    ram[0xa0U+slot]=0U;ram[0x434U+slot]=0U;ram[0x417U+slot]=0U;
    ram[0x401U+slot]=0U;ram[0x58U+slot]=0U;
    ram[0x388U+slot]=0x28U;ram[0x34U+slot]=0U;
}
static unsigned int mysmb_special_actor_target(unsigned int pc)
{
    static const unsigned short targets[20]={0xd1ebU,0xcd3cU,0xf1afU,0xf152U,
        0xe243U,0xd853U,0xd67aU,0xe24cU,0xdb7bU,0xed66U,0xd655U,
        0xe273U,0xdb45U,0xe5c8U,0xd432U,0xd5d3U,0xd64fU,0xd607U,0xd631U,0xd63dU};
    unsigned int i;
    for(i=0U;i<20U;++i) if(pc==targets[i]) return i+1U;
    return 0U;
}
static int mysmb_special_actor_argument(const char *text)
{
    static const char prefix[]="--fixture=t39-special-actor=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    value=0U;digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<3U) {
        value=value*10U+(unsigned int)(text[i++]-'0');++digits;
    }
    if(!digits || text[i]!='\0' || value>=92U) return 0;
    return (int)value+1;
}
#endif
