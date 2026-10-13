#include "core/enemy/platform.h"
#include <stdio.h>
#include <string.h>
static struct mysmb_game g;
static unsigned char prg[32768],expected[2048];
static unsigned int errors,cases;
static void verify(mysmb_u8 slot,mysmb_u8 height)
{
    memcpy(expected,g.ram,2048U);
    if(g.ram[0xeU]!=11U&&g.ram[0xb6U+slot]==1U) {
        expected[0xceU]=(mysmb_u8)(height-32U);
        expected[0xb5U]=(mysmb_u8)(height/32U!=0U);
        expected[0x9fU]=expected[0x433U]=0U;
    }
}
int main(void)
{
    unsigned int n,y,c,engine,high;mysmb_u8 slot,height;
    static const mysmb_u8 edges[5]={0,1,31,32,255};
    for(n=0U;n<32768U;++n)prg[n]=(unsigned char)(n*37U+19U);
    prg[0x5c17U]=0x80U;prg[0x5c18U]=0U;
    memset(&g,0,sizeof(g));g.area_prg=prg;g.area_prg_size=32768U;
    for(engine=0U;engine<256U;++engine)for(high=0U;high<256U;++high)for(n=0U;n<5U;++n) {
        memset(g.ram,0xa5,2048U);slot=(mysmb_u8)((engine&1U)*5U);
        g.ram[0xeU]=(mysmb_u8)engine;g.ram[0xb6U+slot]=(mysmb_u8)high;
        g.ram[0xcfU+slot]=edges[n];verify(slot,edges[n]);
        mysmb_platform_position_player_vertical(&g,slot);
        if(memcmp(g.ram,expected,2048U))++errors;
        ++cases;
    }
    for(c=0U;c<256U;++c)for(y=0U;y<256U;++y) {
        memset(g.ram,0xa5,2048U);slot=(mysmb_u8)((c&1U)*5U);
        g.ram[0xeU]=8U;g.ram[0xb6U+slot]=1U;g.ram[0xcfU+slot]=(mysmb_u8)y;
        height=(mysmb_u8)(y+prg[0x5c16U+c]);verify(slot,height);
        mysmb_platform_position_player_small(&g,slot,(mysmb_u8)c);
        if(memcmp(g.ram,expected,2048U))++errors;
        ++cases;
    }
    printf("platform positioning: %u cases, %u errors\n",cases,errors);return errors?1:0;
}
