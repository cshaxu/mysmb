#ifndef MYSMB_BLOCK_BUMP_FIXTURE_H
#define MYSMB_BLOCK_BUMP_FIXTURE_H
#include "block_head_fixture.h"
static void mysmb_block_bump_fixture(unsigned char *ram,unsigned char n)
{
    static const unsigned char tiles[15]={0xc1U,0xc0U,0x5fU,0x60U,0x55U,0x56U,0x57U,
        0x58U,0x59U,0x5aU,0x5bU,0x5cU,0x5dU,0x5eU,0x51U};
    unsigned int i;
    mysmb_block_head_fixture(ram,0U);
    ram[0x3eeU]=(unsigned char)((n/15U)&1U);
    for(i=0x500U;i<0x6a0U;++i) ram[i]=tiles[n%15U];
    if(n>=30U) ram[0x634U]=0xc2U;
    ram[0x60U]=0x35U;ram[0x61U]=0xcaU;
}
static int mysmb_block_bump_argument(const char *text)
{
    static const char prefix[]="--fixture=t37-bump=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>59U) return 0;
    return (int)value+1;
}
#endif
