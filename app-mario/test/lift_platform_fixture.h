#ifndef MYSMB_LIFT_PLATFORM_FIXTURE_H
#define MYSMB_LIFT_PLATFORM_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_lift_platform_slot(unsigned int n)
{ return (unsigned char)((n&1U)*5U); }
static unsigned int mysmb_lift_platform_entry(unsigned int n)
{ return n<256U?0xd64fU:0xd655U; }
static void mysmb_lift_platform_fixture(unsigned char *r,unsigned int n)
{
    unsigned int i;unsigned char s;
    mysmb_actor_dispatch_fixture(r,(n<256U?76U:86U)+(n&1U));s=mysmb_lift_platform_slot(n);
    for(i=0U;i<6U;++i)if(i!=s)r[0xfU+i]=0U;
    r[0x747U]=0U;
}
static void mysmb_lift_platform_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char values[8]={0,1,0x7f,0x80,0xe0,0xfe,0xff,0x10};
    unsigned char s,v;
    s=mysmb_lift_platform_slot(n);v=(unsigned char)((n%256U)/2U);
    r[0xa0U+s]=values[v%8U];r[0x417U+s]=values[(v/8U)%8U];
    r[0x434U+s]=values[(v+v/8U)%8U];r[0xcfU+s]=values[(v/4U)%8U];
    r[0xb6U+s]=1U;r[0x747U]=(unsigned char)(v&64U?1U:0U);
    r[0x3a2U+s]=(unsigned char)(n<256U?(v&32U?0U:0xffU):(v&32U?1U+(v&1U):0U));
    r[0x1dU]=2U;r[0xceU]=0x70U;r[0xb5U]=1U;
}
static int mysmb_lift_platform_argument(const char *text)
{
    static const char prefix[]="--fixture=t41-lift-platform=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<4U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits || text[i]!='\0' || value>=512U)return 0;
    return (int)value+1;
}
#endif
