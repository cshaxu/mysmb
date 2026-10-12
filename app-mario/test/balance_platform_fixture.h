#ifndef MYSMB_BALANCE_PLATFORM_FIXTURE_H
#define MYSMB_BALANCE_PLATFORM_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_balance_platform_slot(unsigned int n)
{ return (unsigned char)((n&1U)*5U); }
static void mysmb_balance_platform_fixture(unsigned char *r,unsigned int n)
{
    unsigned int i;unsigned char s;
    mysmb_actor_dispatch_fixture(r,72U+(n&1U));s=mysmb_balance_platform_slot(n);
    for(i=0U;i<6U;++i)if(i!=s)r[0xfU+i]=0U;
    r[0x747U]=0U;r[0x1eU+s]=1U;
}
static void mysmb_balance_platform_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char xs[8]={0,0xe7,0xe8,0xef,0xf0,0xf7,0xf8,0xff};
    static const unsigned char ys[8]={0x40,0x7f,0xc0,0xdf,0xe0,0xe7,0xe8,0xff};
    static const unsigned char buffers[4]={0,0x1f,0x20,0xff};
    unsigned char s,p,m,v;
    s=mysmb_balance_platform_slot(n);m=(unsigned char)((n/2U)%32U);v=(unsigned char)(n/64U);
    p=(unsigned char)(v&8U?2U:1U);r[0x1eU+s]=p;r[0x1eU+p]=0xffU;
    r[0xb6U+s]=1U;r[0xb6U+p]=1U;r[0x46U+s]=0U;
    r[0xcfU+s]=ys[v%8U];r[0xcfU+p]=ys[7U-v%8U];
    r[0x87U+s]=xs[v%8U];r[0x87U+p]=xs[7U-v%8U];
    r[0x6eU+s]=(unsigned char)(v&2U?255U:1U);r[0x6eU+p]=2U;
    r[0xa0U+s]=0U;r[0x434U+s]=0U;r[0x417U+s]=0U;
    r[0xa0U+p]=0U;r[0x434U+p]=0U;r[0x417U+p]=0U;
    r[0x3a2U+s]=0xffU;r[0x300U]=buffers[(v/2U)%4U];r[0x6ccU]=(unsigned char)(v&1U);
    r[0x3adU]=0x67U;r[0xceU]=0x56U;r[0xb5U]=1U;r[0x1dU]=2U;
    if(m==0U)r[0xb6U+s]=3U;
    else if(m==1U)r[0x1eU+s]=0xffU;
    else if(m==2U || m==3U) {r[0x46U+s]=1U;if(m==3U)r[0x3a2U+s]=s;}
    else if(m==4U || m==5U) {r[0xcfU+s]=0x2dU;if(m==4U)r[0x3a2U+s]=p;}
    else if(m==6U || m==7U) {r[0xcfU+p]=0x2dU;if(m==6U)r[0x3a2U+s]=s;}
    else if(m==8U)r[0x3a2U+s]=s;
    else if(m==9U)r[0x3a2U+s]=p;
    else if(m==11U)r[0x434U+s]=5U;
    else if(m==12U)r[0x434U+s]=6U;
    else if(m==13U)r[0xa0U+s]=255U;
    else if(m==14U)r[0x434U+s]=251U;
    else if(m==15U){r[0xa0U+s]=255U;r[0x434U+s]=251U;}
    else if(m==16U)r[0xa0U+s]=1U;
    else if(m==17U){r[0xa0U+s]=127U;r[0x434U+s]=251U;}
    else if(m>=18U){r[0xa0U+s]=(unsigned char)(m&1U?1U:255U);r[0x434U+s]=(unsigned char)(m*7U);r[0x3a2U+s]=(unsigned char)(m%3U==0U?s:(m%3U==1U?p:255U));}
}
static int mysmb_balance_platform_argument(const char *text)
{
    static const char prefix[]="--fixture=t41-balance-platform=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<4U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits || text[i]!='\0' || value>=1024U)return 0;
    return (int)value+1;
}
#endif
