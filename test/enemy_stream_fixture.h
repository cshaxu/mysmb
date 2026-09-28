#ifndef MYSMB_ENEMY_STREAM_FIXTURE_H
#define MYSMB_ENEMY_STREAM_FIXTURE_H
#include "entrance_fixture.h"

/* Original enemy-record addresses; only RAM changes at the NMI boundary. */
static void mysmb_enemy_stream_fixture(unsigned char *ram,unsigned char n)
{
    static const unsigned short addresses[10]={
        0x9e59U,0x9d70U,0x9d8cU,0x9f4cU,0x9e21U,0x9e24U,0x9d96U,0x9d74U,
        0x9e9eU,0x9d96U};
    static const unsigned char columns[10]={0xa0U,0x70U,0U,0U,0x80U,0xb0U,0U,0xe0U,0xe0U,0U};
    unsigned char kind,variant,slot,i;
    unsigned short address;
    mysmb_entrance_fixture(ram,0U);
    kind=(unsigned char)(n/8U);variant=(unsigned char)(n%8U);
    slot=variant==5U?5U:0U;
    ram[0xeU]=12U;ram[0x747U]=0xffU;ram[0x71fU]=0U;
    for(i=0U;i<6U;++i) ram[0xfU+i]=(unsigned char)(0x80U+i);
    ram[0xfU+slot]=0U;
    ram[0x745U]=0U;ram[0x6cbU]=0U;ram[0x6cdU]=0U;ram[0x398U]=0U;
    ram[0x73aU]=4U;ram[0x73bU]=kind==2U?0U:1U;
    ram[0x71bU]=4U;ram[0x71dU]=columns[kind];
    ram[0x6ccU]=0U;ram[0x76aU]=0U;ram[0x75fU]=0U;
    if(variant==1U) ram[0x71bU]=5U;
    if(variant==2U) ram[0x71bU]=3U;
    if(variant==3U) { ram[0x73bU]=0U;ram[0x6ccU]=1U; }
    if(variant==3U && kind<2U) ram[0x73aU]=3U;
    if(variant==4U) { ram[0x76aU]=1U;ram[0x75fU]=7U; }
    if(variant==7U) ram[0x398U]=1U;
    if(kind>=8U) ram[0x6cbU]=0x11U;
    address=addresses[kind];ram[0x739U]=variant==6U?0xfeU:0U;
    address=(unsigned short)(address-ram[0x739U]);
    ram[0xe9U]=(unsigned char)address;ram[0xeaU]=(unsigned char)(address>>8U);
}
static int mysmb_enemy_stream_argument(const char *text)
{
    static const char prefix[]="--fixture=t38-stream=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>79U) return 0;
    return (int)value+1;
}
#endif
