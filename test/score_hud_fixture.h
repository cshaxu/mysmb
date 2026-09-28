#ifndef MYSMB_SCORE_HUD_FIXTURE_H
#define MYSMB_SCORE_HUD_FIXTURE_H
#include "coin_allocation_fixture.h"
static void mysmb_score_hud_fixture(unsigned char *ram,unsigned char n)
{
    static const unsigned char counts[4]={0U,98U,99U,255U};
    unsigned int i;
    mysmb_coin_allocation_fixture(ram,0U);
    ram[0x753U]=(unsigned char)(n&1U);
    ram[0x75eU]=counts[(n>>1U)&3U];
    ram[0x75aU]=(n&8U)!=0U?255U:2U;
    for(i=0x7ddU;i<=0x7f4U;++i) ram[i]=0U;
    ram[0x7ddU+6U*(n&1U)]=(n&16U)!=0U?1U:0U;
}
static int mysmb_score_hud_argument(const char *text)
{
    static const char prefix[]="--fixture=t36-score=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>55U) return 0;
    return (int)value+1;
}
#endif
