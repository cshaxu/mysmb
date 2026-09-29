#ifndef MYSMB_OFFSCREEN_BOUNDS_FIXTURE_H
#define MYSMB_OFFSCREEN_BOUNDS_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_offscreen_bounds_slot(unsigned int n)
{ return (unsigned char)((n&1U)*5U); }
static void mysmb_offscreen_bounds_fixture(unsigned char *r,unsigned int n)
{
    unsigned int i;unsigned char s;
    mysmb_actor_dispatch_fixture(r,74U+(n&1U));s=mysmb_offscreen_bounds_slot(n);
    for(i=0U;i<6U;++i)if(i!=s)r[0xfU+i]=0U;
    r[0x747U]=0U;
}
static void mysmb_offscreen_bounds_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char ids[16]={0,4,5,6,12,13,14,19,20,21,47,48,49,50,51,255};
    static const unsigned char xs[8]={0,0x47,0x48,0xc6,0xc7,0xc8,0xfe,0xff};
    static const unsigned char pages[4]={0,1,0x7f,0xff};
    static const unsigned char offset[8]={0xfe,0xff,0,1,2,0x7f,0x80,0x81};
    unsigned char s,v;
    s=mysmb_offscreen_bounds_slot(n);v=(unsigned char)(n/32U);
    r[0x16U+s]=ids[(n/2U)%16U];r[0x1eU+s]=(unsigned char)(v&16U?5U:0U);
    r[0x71cU]=xs[v%8U];r[0x71aU]=pages[v/8U];
    r[0x71dU]=xs[7U-v%8U];r[0x71bU]=(unsigned char)(r[0x71aU]+1U);
    r[0x87U+s]=xs[(v/4U)%8U];r[0x6eU+s]=(unsigned char)(r[0x71aU]+offset[v%8U]);
    r[0U]=0xa1U;r[1U]=0xa2U;r[2U]=0xa3U;r[3U]=0xa4U;
}
static int mysmb_offscreen_bounds_argument(const char *text)
{
    static const char prefix[]="--fixture=t41-offscreen-bounds=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<4U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits || text[i]!='\0' || value>=1024U)return 0;
    return (int)value+1;
}
#endif
