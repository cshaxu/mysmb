#ifndef MYSMB_SWIMMING_CHEEP_MOVEMENT_FIXTURE_H
#define MYSMB_SWIMMING_CHEEP_MOVEMENT_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_swimming_cheep_slot(unsigned int n)
{
    static const unsigned char slots[4]={0U,1U,2U,5U};
    return slots[n%4U];
}
static void mysmb_swimming_cheep_fixture(unsigned char *ram,unsigned int n)
{
    static const unsigned char fractions[8]={0U,0x1fU,0x20U,0xdfU,0xe0U,0xffU,0xffU,0U};
    static const unsigned char ys[8]={0U,0xffU,0x80U,0x0fU,0x90U,0x80U,0x80U,0x80U};
    static const unsigned char anchors[8]={0x0fU,0xefU,0x70U,0x1eU,0x80U,0x90U,0U,0x80U};
    unsigned int i,mode,group;
    unsigned char slot,id,step;
    slot=mysmb_swimming_cheep_slot(n);id=(unsigned char)(10U+(n/4U)%2U);
    mysmb_actor_dispatch_fixture(ram,20U);
    for(i=0U;i<6U;++i) ram[0xfU+i]=0U;
    ram[0xfU+slot]=1U;ram[0x16U+slot]=id;
    ram[0x6eU+slot]=1U;ram[0x87U+slot]=0x70U;ram[0xb6U+slot]=1U;
    ram[0x49aU+slot]=9U;ram[0x6e5U+slot]=0x40U;
    ram[0x747U]=0U;ram[0x6dU]=0U;ram[0x86U]=0U;ram[0xceU]=0x30U;
    mode=(n/8U)%8U;group=n/64U;
    ram[0x1eU+slot]=(unsigned char)(group==7U?0x20U:(mode&1U?0x1fU:0U));
    ram[0x417U+slot]=fractions[mode];
    ram[0x58U+slot]=(unsigned char)(mode>=3U && mode!=6U?0x10U:0x0fU);
    ram[0xcfU+slot]=ys[group];ram[0x434U+slot]=anchors[group];
    step=(unsigned char)(id==10U?0x40U:0x80U);
    ram[0x401U+slot]=(unsigned char)(mode&2U?step:(mode&1U?step-1U:0xffU));
    ram[0xa0U+slot]=(unsigned char)(mode&1U?0xfdU:1U);
}
static int mysmb_swimming_cheep_argument(const char *text)
{
    static const char prefix[]="--fixture=t40-swimming-cheep=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    value=0U;digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<3U) {
        value=value*10U+(unsigned int)(text[i++]-'0');++digits;
    }
    if(!digits || text[i]!='\0' || value>=512U) return 0;
    return (int)value+1;
}
#endif
