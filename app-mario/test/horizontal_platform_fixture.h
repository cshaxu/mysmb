#ifndef MYSMB_HORIZONTAL_PLATFORM_FIXTURE_H
#define MYSMB_HORIZONTAL_PLATFORM_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_horizontal_platform_slot(unsigned int n)
{ return (unsigned char)((n&1U)*5U); }
static unsigned int mysmb_horizontal_platform_entry(unsigned int n)
{ return n<256U?0xd607U:(n<512U?0xd631U:0xd63dU); }
static void mysmb_horizontal_platform_fixture(unsigned char *r,unsigned int n)
{
    unsigned int i;unsigned char s;
    mysmb_actor_dispatch_fixture(r,80U+2U*(n/256U)+(n&1U));s=mysmb_horizontal_platform_slot(n);
    for(i=0U;i<6U;++i)if(i!=s)r[0xfU+i]=0U;
    r[0x747U]=0U;
}
static void mysmb_horizontal_platform_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char speeds[16]={0,1,0x0d,0x0e,0x0f,0x10,0x7f,0x80,0x81,0x8f,0xe0,0xef,0xf0,0xf1,0xfe,0xff};
    static const unsigned char xs[8]={0,1,0x7f,0x80,0xf0,0xfe,0xff,0x10};
    unsigned char s,v;
    s=mysmb_horizontal_platform_slot(n);v=(unsigned char)((n%256U)/2U);
    r[0xa0U+s]=(unsigned char)(v/16U);r[0x58U+s]=speeds[v%16U];
    r[0x401U+s]=(unsigned char)(v&16U?0xffU:0U);r[0x434U+s]=(unsigned char)(v*17U);r[0x417U+s]=(unsigned char)(v&16U?0xffU:0U);
    r[0xcfU+s]=0x80U;r[0xb6U+s]=1U;r[0x87U+s]=xs[v%8U];r[0x6eU+s]=1U;
    r[0x86U]=xs[v%8U];r[0x6dU]=(unsigned char)(v&64U?0xffU:0U);
    r[9U]=(unsigned char)(v&3U);r[0x3a2U+s]=(unsigned char)(v&32U?0U:0xffU);
    r[0x1dU]=2U;r[0xceU]=0x70U;r[0xb5U]=1U;
}
static int mysmb_horizontal_platform_argument(const char *text)
{
    static const char prefix[]="--fixture=t41-horizontal-platform=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<4U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits || text[i]!='\0' || value>=768U)return 0;
    return (int)value+1;
}
#endif
