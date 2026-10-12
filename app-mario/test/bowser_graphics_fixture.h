#ifndef MYSMB_BOWSER_GRAPHICS_FIXTURE_H
#define MYSMB_BOWSER_GRAPHICS_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_bowser_graphics_slot(unsigned int n)
{ return (unsigned char)((n & 1U)*5U); }
static void mysmb_bowser_graphics_fixture(unsigned char *r,unsigned int n)
{ mysmb_actor_dispatch_fixture(r,90U+(n & 1U)); }
/* Inputs at naturally reached BowserGfxHandler; never patch CPU or outputs. */
static void mysmb_bowser_graphics_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char xs[8]={0,3,15,16,127,239,252,255};
    static const unsigned char ys[4]={0x70,0xdf,0xf8,0xfc};
    static const unsigned char states[4]={0,1,0x20,0x40};
    static const unsigned char flags[4]={0,1,254,255};
    unsigned char s,rear;
    s=mysmb_bowser_graphics_slot(n);rear=(unsigned char)(1U+3U*((n/2U)&1U));
    r[0x6cfU]=rear;r[0x36aU]=flags[(n/8U)%4U];
    r[0x87U+s]=xs[(n/4U)%8U];r[0xcfU+s]=ys[(n/32U)%4U];
    r[0x46U+s]=(unsigned char)(1U+(n/128U)%2U);
    r[0x1eU+s]=states[(n/2U)%4U];r[0x363U]=(unsigned char)((n/16U)%2U?0x81U:0U);
    r[0x6eU+s]=1U;r[0x6eU+rear]=(unsigned char)(n/256U);
    r[0xb6U+s]=r[0xb6U+rear]=1U;r[0xfU+rear]=0x80U;
    r[0x6e5U+s]=0x30U;r[0x6e5U+rear]=0x60U;
    r[0x49aU+s]=r[0x49aU+rear]=0x37U;
    r[9U]=(unsigned char)(n%2U);r[0xeU]=8U;
}
static int mysmb_bowser_graphics_argument(const char *text)
{
    static const char prefix[]="--fixture=t41-bowser-graphics=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<4U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits || text[i]!='\0' || value>=512U)return 0;
    return (int)value+1;
}
#endif
