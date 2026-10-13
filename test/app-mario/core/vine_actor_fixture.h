#ifndef MYSMB_VINE_ACTOR_FIXTURE_H
#define MYSMB_VINE_ACTOR_FIXTURE_H
#include "entrance_fixture.h"
static void mysmb_vine_actor_fixture(unsigned char *ram,unsigned char n)
{
    static const unsigned char heights[10]={0U,7U,8U,0x1fU,0x20U,0x2fU,0x30U,0x5fU,0x60U,0xffU};
    static const unsigned char ys[7]={0U,0x10U,0xc0U,0xd0U,0xe0U,0xf0U,0xffU};
    unsigned char slot,count;
    unsigned int i;
    mysmb_entrance_fixture(ram,0U);
    slot=n<5U?n:5U;count=(unsigned char)(1U+(n&1U));
    ram[0xeU]=8U;ram[0x70bU]=1U;ram[0x716U]=1U;
    ram[0xfU+slot]=1U;ram[0x16U+slot]=0x2fU;
    ram[0x6eU+slot]=7U;ram[0x87U+slot]=0x80U;
    ram[0xb6U+slot]=1U;ram[0xcfU+slot]=0x90U;
    ram[0x398U]=count;ram[0x399U]=heights[n%10U];
    ram[0x39aU]=count==1U?slot:2U;ram[0x39bU]=slot;ram[0x39dU]=0xe0U;
    ram[0x9U]=(unsigned char)(n%4U);
    if(count==2U && slot==5U) {
        ram[0x11U]=1U;ram[0x18U]=0x2fU;ram[0x70U]=7U;
        ram[0x89U]=0x80U;ram[0xd1U]=0xc0U;ram[0xb8U]=1U;
    }
    if(n>=29U && n<=35U) {
        ram[0x399U]=0x20U;ram[0xcfU+slot]=ys[n-29U];ram[0x9U]=0xffU;
        if((n&1U)!=0U) for(i=0x500U;i<0x6a0U;++i) ram[i]=0x44U;
    }
    if(n>=36U) {
        ram[0x399U]=0x20U;ram[0x9U]=0xffU;
        ram[0x6eU+slot]=n<38U?6U:(n<40U?7U:8U);
        ram[0x87U+slot]=n<38U?0xe0U:(n<40U?0xfcU:0x10U);
    }

}
static int mysmb_vine_actor_argument(const char *text)
{
    static const char prefix[]="--fixture=t36-vine=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>41U) return 0;
    return (int)value+1;
}
#endif
