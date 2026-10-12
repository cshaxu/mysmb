#ifndef MYSMB_PLATFORM_POSITION_FIXTURE_H
#define MYSMB_PLATFORM_POSITION_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned int mysmb_platform_position_small(unsigned int n)
{ return (n>=256U&&n<512U)||n>=544U; }
static unsigned char mysmb_platform_position_slot(unsigned int n)
{ return (unsigned char)((n&1U)*5U); }
static void mysmb_platform_position_fixture(unsigned char *r,unsigned int n)
{
    unsigned int i;unsigned char slot;
    mysmb_actor_dispatch_fixture(r,(mysmb_platform_position_small(n)?86U:76U)+(n&1U));
    slot=mysmb_platform_position_slot(n);
    for(i=0U;i<6U;++i)if(i!=slot)r[0xfU+i]=0U;
    r[0x747U]=0U;
}
static void mysmb_platform_position_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char extra[8]={3,4,7,31,63,127,254,255};
    static const unsigned char high[4]={0,2,255,1};
    unsigned char slot;
    slot=mysmb_platform_position_slot(n);
    r[8U]=slot;r[0xeU]=8U;r[0x747U]=0U;
    r[0xcfU+slot]=(unsigned char)n;r[0xb6U+slot]=1U;
    r[0x417U+slot]=0U;r[0x434U+slot]=0U;r[0xa0U+slot]=0U;
    r[0xceU]=0xa5U;r[0xb5U]=3U;r[0x9fU]=0xfcU;r[0x433U]=0x80U;
    r[0x1dU]=2U;
    r[0x3a2U+slot]=(unsigned char)(mysmb_platform_position_small(n)?1U+(n&1U):0U);
    if(n>=512U&&n<576U) {
        if(n%32U<16U)r[0xeU]=11U;
        else r[0xb6U+slot]=high[n%4U];
    }
    if(n>=576U)r[0x3a2U+slot]=extra[n-576U];
}
static int mysmb_platform_position_argument(const char *text)
{
    static const char prefix[]="--fixture=t42-platform-position=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0'&&text[i]<='9'&&digits<4U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits||text[i]!='\0'||value>=584U)return 0;
    return (int)value+1;
}
#endif
