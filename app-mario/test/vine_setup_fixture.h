#ifndef MYSMB_VINE_SETUP_FIXTURE_H
#define MYSMB_VINE_SETUP_FIXTURE_H
#include "entrance_fixture.h"
static void mysmb_vine_setup_fixture(unsigned char *ram,unsigned char n)
{
    static const unsigned char counts[4]={0U,1U,2U,0xffU};
    mysmb_entrance_fixture(ram,0U);
    ram[0xeU]=0U;ram[0x758U]=1U;ram[0x716U]=1U;
    ram[0x398U]=counts[n%4U];ram[0x399U]=0U;
    ram[0x39dU]=(unsigned char)(0x31U+n);
    ram[0x71aU]=(unsigned char)(n/4U==3U?0xffU:n/4U);
    ram[0x710U]=(unsigned char)(n%8U);
    ram[0x752U]=(unsigned char)(n/4U);
    ram[0x39aU]=5U;ram[0x39bU]=5U;

}
static int mysmb_vine_setup_argument(const char *text)
{
    static const char prefix[]="--fixture=t35-vine-setup=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>15U) return 0;
    return (int)value+1;
}
#endif
