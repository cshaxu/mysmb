#ifndef MYSMB_FIREWORKS_LIFETIME_FIXTURE_H
#define MYSMB_FIREWORKS_LIFETIME_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_fireworks_lifetime_slot(unsigned int n)
{ return (unsigned char)((n & 1U)*5U); }
static void mysmb_fireworks_lifetime_fixture(unsigned char *r,unsigned int n)
{ mysmb_actor_dispatch_fixture(r,44U+(n & 1U)); }
static void mysmb_fireworks_lifetime_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char timers[5]={0,1,2,8,255};
    static const unsigned char frames[5]={0,1,2,254,255};
    static const unsigned char xs[8]={0,1,3,4,127,248,252,255};
    unsigned char s;
    s=mysmb_fireworks_lifetime_slot(n);r[0xa0U+s]=timers[(n/2U)%5U];
    r[0x58U+s]=r[0xa0U+s]==1U?frames[(n/10U)%5U]:(unsigned char)((n/10U)%3U);
    r[0x87U+s]=xs[(n/3U)%8U];r[0xcfU+s]=xs[(n/7U)%8U];
    r[0x6e5U+s]=(unsigned char)(n%5U==0U?0xfcU:0x40U);
    r[0x753U]=(unsigned char)((n/13U)%2U);r[0x747U]=(unsigned char)(n%3U);
    r[0xfeU]=0x80U;r[0x138U]=0U;
}
static int mysmb_fireworks_lifetime_argument(const char *text)
{
    static const char prefix[]="--fixture=t41-fireworks-lifetime=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<4U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits || text[i]!='\0' || value>=512U)return 0;
    return (int)value+1;
}
#endif
