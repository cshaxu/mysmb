#ifndef MYSMB_VERTICAL_PLATFORM_FIXTURE_H
#define MYSMB_VERTICAL_PLATFORM_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_vertical_platform_slot(unsigned int n)
{ return (unsigned char)((n&1U)*5U); }
static void mysmb_vertical_platform_fixture(unsigned char *r,unsigned int n)
{
    unsigned int i;unsigned char s;
    mysmb_actor_dispatch_fixture(r,74U+(n&1U));s=mysmb_vertical_platform_slot(n);
    for(i=0U;i<6U;++i)if(i!=s)r[0xfU+i]=0U;
    r[0x747U]=0U;
}
static void mysmb_vertical_platform_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char ys[8]={0,1,0x2d,0x7f,0x80,0xe7,0xfe,0xff};
    unsigned char s,m,v,y;
    s=mysmb_vertical_platform_slot(n);m=(unsigned char)((n/2U)%16U);v=(unsigned char)(n/32U);y=ys[v%8U];
    r[0xa0U+s]=0U;r[0x434U+s]=0U;r[0x417U+s]=0xa5U;
    r[0xcfU+s]=y;r[0x401U+s]=0xffU;r[0x58U+s]=0x80U;
    r[9U]=(unsigned char)(m&7U);r[0x3a2U+s]=(unsigned char)(v&8U?0U:0xffU);
    r[0x1dU]=2U;r[0xceU]=0x70U;r[0xb5U]=1U;
    if(m==8U)r[0x401U+s]=y;
    if(m==9U){r[0x401U+s]=0U;r[0x58U+s]=y;}
    if(m==10U)r[0xa0U+s]=1U;
    if(m==11U)r[0xa0U+s]=0xffU;
    if(m==12U)r[0x434U+s]=1U;
    if(m==13U)r[0x434U+s]=0xffU;
    if(m==14U){r[0xa0U+s]=0xffU;r[0x434U+s]=0xffU;r[0x58U+s]=0xffU;}
    if(m==15U){r[0xa0U+s]=0x7fU;r[0x434U+s]=0x80U;r[0x58U+s]=0U;}
}
static int mysmb_vertical_platform_argument(const char *text)
{
    static const char prefix[]="--fixture=t41-vertical-platform=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<4U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits || text[i]!='\0' || value>=512U)return 0;
    return (int)value+1;
}
#endif
