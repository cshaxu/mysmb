#ifndef MYSMB_HAMMER_CONTACT_FIXTURE_H
#define MYSMB_HAMMER_CONTACT_FIXTURE_H
#include "hammer_chain_fixture.h"
static unsigned char mysmb_hammer_contact_slot(unsigned int n)
{ return (unsigned char)(n%9U); }
static void mysmb_hammer_contact_fixture(unsigned char *r,unsigned int n)
{ mysmb_hammer_chain_fixture(r,(unsigned char)(45U+n%9U)); }
static void mysmb_hammer_contact_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char speeds[8]={0,1,0x10,0x7f,0x80,0xf0,0xfe,0xff};
    unsigned char s,v;unsigned int b;
    s=mysmb_hammer_contact_slot(n);v=(unsigned char)(n/9U);b=0x4d0U+s*4U;
    r[9U]=(unsigned char)(v==0U?0U:1U);r[0x747U]=(unsigned char)(v==1U?1U:0U);
    r[0x3d6U]=(unsigned char)(v==2U?0x80U:0U);r[0x6beU+s]=(unsigned char)(v==4U?1U:0U);
    r[0x64U+s]=speeds[v%8U];r[0x79fU]=(unsigned char)(v==5U?0x20U:0U);
    r[0x79eU]=(unsigned char)(v%4U==0U?8U:0U);r[0x756U]=(unsigned char)(v%3U);
    r[0x4acU]=0x40U;r[0x4adU]=0x60U;r[0x4aeU]=0x50U;r[0x4afU]=0x80U;
    r[b]=(unsigned char)(v==3U?0x80U:0x48U);r[b+1U]=0x68U;
    r[b+2U]=(unsigned char)(r[b]+8U);r[b+3U]=0x78U;
}
static int mysmb_hammer_contact_argument(const char *text)
{
    static const char prefix[]="--fixture=t42-hammer-contact=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0'&&text[i]<='9'&&digits<3U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits||text[i]!='\0'||value>=288U)return 0;
    return (int)value+1;
}
#endif
