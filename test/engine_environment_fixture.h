#ifndef MYSMB_ENGINE_ENVIRONMENT_FIXTURE_H
#define MYSMB_ENGINE_ENVIRONMENT_FIXTURE_H
#include "game_entry_fixture.h"

/* Controlled RAM inputs at NMI; PlayerChangeSize takes its real idle return.
 * No child entry, CPU state or expected output is injected. */
static void mysmb_engine_environment_fixture(unsigned char *ram, unsigned char scenario)
{
    unsigned int i;
    mysmb_game_entry_fixture(ram,2U);
    ram[0xeU]=9U; ram[0x747U]=0U; ram[0x74eU]=0U; ram[0x71fU]=7U;
    ram[0x6dU]=1U; ram[0x86U]=0x88U; ram[0xb5U]=1U; ram[0xceU]=0x80U;
    ram[0x9fU]=0U; ram[0x416U]=0xf8U; ram[0x433U]=0x10U;
    ram[0x490U]=1U; ram[9U]=0U; ram[0x47dU]=0x7fU;
    for(i=0U;i<5U;++i) { ram[0x46bU+i]=0U; ram[0x471U+i]=0U; ram[0x477U+i]=0U; }
    ram[0x46fU]=1U; ram[0x475U]=0x80U; ram[0x47bU]=0x40U;
    if(scenario==0U) ram[0x74eU]=1U;
    if(scenario==1U) ram[0x747U]=0xffU;
    if(scenario==2U) ram[0x46fU]=0U;
    if(scenario==3U) ram[0x86U]=0x7fU;
    if(scenario==4U) ram[0x86U]=0xc1U;
    if(scenario==6U) ram[0x86U]=0xb0U;
    if(scenario==7U) ram[0x490U]=0U;
    if(scenario==8U) ram[9U]=1U;
    if(scenario==9U) { ram[0x475U]=0xf0U; ram[0x47bU]=0x40U; ram[0x86U]=0xffU; }
    if(scenario==10U) { ram[0x475U]=0xf0U; ram[0x47bU]=0x10U; ram[0x6dU]=2U; ram[0x86U]=0U; }
    if(scenario==11U) { ram[0x46fU]=0U; ram[0x46bU]=1U; ram[0x471U]=0x80U; ram[0x477U]=0x40U; }
}
static int mysmb_engine_environment_argument(const char *text)
{
    static const char prefix[]="--fixture=t31-environment=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>11U) return 0;
    return (int)value+1;
}
#endif
