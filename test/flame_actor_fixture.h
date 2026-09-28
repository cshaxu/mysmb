#ifndef MYSMB_FLAME_ACTOR_FIXTURE_H
#define MYSMB_FLAME_ACTOR_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_flame_actor_slot(unsigned int n)
{ return (unsigned char)((n & 1U)*5U); }
static void mysmb_flame_actor_fixture(unsigned char *r,unsigned int n)
{ mysmb_actor_dispatch_fixture(r,42U+(n & 1U)); }
/* Input-only setup at naturally reached ProcBowserFlame. */
static void mysmb_flame_actor_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char xs[16]={0,1,2,7,8,15,16,23,24,31,32,127,239,247,248,255};
    static const unsigned char forces[6]={0,0x3f,0x40,0x5f,0x60,255};
    static const unsigned char ys[6]={0x70,0x80,0x90,0,255,0x71};
    unsigned char s;
    s=mysmb_flame_actor_slot(n);
    r[0x87U+s]=xs[(n/2U)%16U];r[0x401U+s]=forces[(n/5U)%6U];
    r[0x6eU+s]=(unsigned char)((n/32U)%3U);
    r[0xcfU+s]=ys[(n/7U)%6U];r[0x417U+s]=(unsigned char)((n/11U)%4U);
    r[0x434U+s]=(unsigned char)(n%3U==0U?255U:n%3U);
    r[0x747U]=(unsigned char)(n%9U==0U);r[0x6ccU]=(unsigned char)((n/13U)%2U);
    r[0x1eU+s]=(unsigned char)(n%17U==0U?1U:0U);
    r[9U]=(unsigned char)(n%4U);r[0x71aU]=1U;r[0x71cU]=0U;
    r[0x71bU]=1U;r[0x71dU]=255U;r[0x6e5U+s]=(unsigned char)(n%5U==0U?0xfcU:0x40U);
}
static int mysmb_flame_actor_argument(const char *text)
{
    static const char prefix[]="--fixture=t41-flame-actor=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<4U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits || text[i]!='\0' || value>=1024U)return 0;
    return (int)value+1;
}
#endif
