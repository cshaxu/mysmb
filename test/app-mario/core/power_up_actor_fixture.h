#ifndef MYSMB_POWER_UP_ACTOR_FIXTURE_H
#define MYSMB_POWER_UP_ACTOR_FIXTURE_H
#include "entrance_fixture.h"
static void mysmb_power_up_actor_fixture(unsigned char *ram,unsigned char n)
{
    static const unsigned char states[7]={0U,1U,5U,6U,0x10U,0x11U,0x7fU};
    mysmb_entrance_fixture(ram,0U);
    ram[0xeU]=8U;ram[0x70bU]=1U;ram[0x716U]=1U;
    ram[0x14U]=1U;ram[0x1bU]=0x2eU;
    ram[0x73U]=7U;ram[0x8cU]=0x80U;ram[0xbbU]=1U;ram[0xd4U]=0x90U;
    ram[0x49fU]=3U;ram[0x3caU]=0x20U;ram[0x4bU]=1U;ram[0x5dU]=0x10U;
    ram[0xa5U]=0U;ram[0x41cU]=0U;ram[0x439U]=0U;ram[0x39U]=0U;
    ram[0x23U]=n<28U?states[n/4U]:0x80U;
    ram[0x9U]=(unsigned char)(n&3U);
    if(n>=28U && n<44U) {
        ram[0x39U]=(unsigned char)((n-28U)%4U);
        ram[0x747U]=(n&4U)!=0U?0xffU:0U;
        ram[0x23U]=(n&8U)!=0U?0xc0U:0x80U;
    }
    if(n>=44U && n<48U) {
        ram[0x39U]=(unsigned char)(n-44U);ram[0x23U]=6U;
        ram[0x8cU]=ram[0x86U];ram[0xd4U]=ram[0xceU];
        ram[0x9U]=0xffU;ram[0x756U]=1U;ram[0x754U]=0U;
    }
    if(n>=48U) {
        ram[0x73U]=n==48U?6U:8U;ram[0x8cU]=0x80U;ram[0x9U]=0xffU;
    }
}
static int mysmb_power_up_actor_argument(const char *text)
{
    static const char prefix[]="--fixture=t37-power=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>49U) return 0;
    return (int)value+1;
}
#endif
