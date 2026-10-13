#ifndef MYSMB_ENGINE_CANNON_FIXTURE_H
#define MYSMB_ENGINE_CANNON_FIXTURE_H
#include "engine_environment_fixture.h"

static void mysmb_engine_cannon_fixture(unsigned char *ram,unsigned char scenario)
{
    static const unsigned char no_run_ids[7]={0x17U,0x18U,0x19U,0x1aU,0x23U,0x30U,0x33U};
    unsigned int i;
    mysmb_engine_environment_fixture(ram,5U);
    ram[0x74eU]=1U;ram[0x6ccU]=0U;ram[0x71aU]=1U;ram[0x71bU]=1U;
    ram[0x71cU]=0U;ram[0x71dU]=0xffU;
    for(i=0U;i<6U;++i) {ram[0x46bU+i]=0U;ram[0x471U+i]=0U;ram[0x477U+i]=0U;ram[0x47dU+i]=0U;}
    for(i=0U;i<8U;++i) ram[0x7a7U+i]=0U;
    ram[0x46bU]=1U;ram[0x471U]=0xc0U;ram[0x477U]=0x90U;
    if(scenario==0U) ram[0x74eU]=0U;
    if(scenario==1U) for(i=0U;i<4U;++i) ram[0x7a7U+i]=0x1eU;
    if(scenario==2U) ram[0x46bU]=0U;
    if(scenario==3U) ram[0x47dU]=9U;
    if(scenario==4U) ram[0x747U]=0xffU;
    if(scenario==6U) {ram[0x47dU]=9U;ram[0x747U]=0xffU;}
    if(scenario==7U) {ram[0x6ccU]=1U;for(i=0U;i<4U;++i) ram[0x7a7U+i]=0x10U;}
    if(scenario>=8U) {
        ram[0xfU]=1U;ram[0x16U]=0x33U;ram[0x1eU]=1U;
        ram[0x6eU]=1U;ram[0x87U]=0xc0U;ram[0xcfU]=0x88U;
        ram[0xb6U]=1U;ram[0x58U]=0xe8U;ram[0x46U]=2U;
        ram[0x49aU]=9U;ram[0x47dU]=10U;
    }
    if(scenario==9U) ram[0x1eU]=0U;
    if(scenario==10U) {ram[0x1eU]=0U;ram[0x87U]=0x30U;}
    if(scenario==11U) {ram[0x1eU]=0U;ram[0x87U]=0x90U;}
    if(scenario==12U) ram[0x1eU]=0x20U;
    if(scenario==13U) ram[0x747U]=0xffU;
    if(scenario==14U) ram[0x6eU]=3U;
    if(scenario==15U) {ram[0x1eU]=0U;ram[0x6eU]=0U;ram[0x87U]=0xf0U;}
    if(scenario==16U || scenario==17U) {
        ram[0x78aU]=7U;ram[0x78eU]=0x55U;ram[0x796U]=8U;
        ram[0x125U]=3U;ram[0x3c5U]=0xa0U;ram[0x1eU]=0U;
        if(scenario==16U) ram[0x87U]=0x90U;
        else ram[0x6eU]=3U;
    }
    if(scenario>=18U) {
        ram[0x16U]=no_run_ids[scenario-18U];ram[0x74eU]=0U;
        for(i=0U;i<6U;++i) ram[0x46bU+i]=0U;
        ram[0x3c5U]=0xa0U;ram[0x3aeU]=0xa1U;ram[0x3b9U]=0xb2U;
        ram[0x3d1U]=0xc3U;
    }
}
static int mysmb_engine_cannon_argument(const char *text)
{
    static const char prefix[]="--fixture=t31-cannon=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>24U) return 0;
    return (int)value+1;
}
#endif
