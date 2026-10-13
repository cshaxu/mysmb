#ifndef MYSMB_BLOCK_CHUNKS_FIXTURE_H
#define MYSMB_BLOCK_CHUNKS_FIXTURE_H
#include "block_head_fixture.h"
static void mysmb_block_chunks_fixture(unsigned char *ram,unsigned char n)
{
    unsigned int i;
    mysmb_block_head_fixture(ram,12U);
    ram[0x3eeU]=(unsigned char)(n&1U);
    ram[0x86U]=(n&2U)?0xf8U:0x40U;
    ram[0xceU]=(n&4U)?0x25U:0x85U;
    ram[0xc0U]=0x33U;ram[0xc1U]=0x77U;
    for(i=0x500U;i<0x6a0U;++i) ram[i]=0x51U;
    if((n&8U)!=0U && (n&4U)==0U) ram[(n&2U)?0x550U:0x624U]=0xc2U;
}
static int mysmb_block_chunks_argument(const char *text)
{
    static const char prefix[]="--fixture=t37-chunks=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>15U) return 0;
    return (int)value+1;
}
#endif
