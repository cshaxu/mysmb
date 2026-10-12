#ifndef MYSMB_STAR_FLAG_FIXTURE_H
#define MYSMB_STAR_FLAG_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_star_flag_slot(unsigned int n)
{ return (unsigned char)((n & 1U)*5U); }
static void mysmb_star_flag_fixture(unsigned char *r,unsigned int n)
{ mysmb_actor_dispatch_fixture(r,98U+(n & 1U)); }
static void mysmb_star_flag_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char tasks[8]={0,1,2,3,4,5,128,255};
    static const unsigned char digits[8]={0,1,3,6,2,9,5,7};
    static const unsigned char ys[8]={0,0x71,0x72,0x73,0x80,0xf8,0xff,0x70};
    static const unsigned char fireworks[8]={0,1,3,6,0x7f,0x80,0xfe,0xff};
    unsigned char s;unsigned int v;
    s=mysmb_star_flag_slot(n);v=n/16U;
    r[0x746U]=tasks[(n/2U)%8U];r[0x747U]=0U;
    r[0x7f8U]=(unsigned char)((v/8U)%2U);r[0x7f9U]=0U;
    r[0x7faU]=digits[v%8U];r[9U]=(unsigned char)((v/2U)%2U?4U:0U);
    r[0x753U]=(unsigned char)((v/4U)%2U);r[0xfeU]=0x80U;
    r[0xcfU+s]=ys[v%8U];r[0x6d7U]=fireworks[(v/8U)%8U];
    r[0x796U+s]=(unsigned char)(v%2U);r[0x7b1U]=(unsigned char)((v/2U)%2U);
    r[0xfcU]=(unsigned char)(r[0x7b1U]^1U);
    r[0x6e5U+s]=(unsigned char)(v%3U==0U?0xfcU:0x40U);
    r[0x87U+s]=(unsigned char)(v%2U?0xffU:0U);
    r[0x6cbU]=0x55U;
}
static int mysmb_star_flag_argument(const char *text)
{
    static const char prefix[]="--fixture=t41-star-flag=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<4U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits || text[i]!='\0' || value>=1024U)return 0;
    return (int)value+1;
}
#endif
