#include "core/area.h"
#include <stdio.h>
#include <string.h>
static unsigned int failures,calls,close_gate;
static mysmb_u8 sequence[2];
void mysmb_area_replace_block_metatile(struct mysmb_game *g,mysmb_u8 slot)
{
    mysmb_u16 address;
    if(calls>=2U) { ++failures;return; }
    sequence[calls++]=slot;
    address=(mysmb_u16)(0x500U+g->ram[6U]+g->ram[2U]);
    if(g->ram[8U]!=slot || g->ram[7U]!=5U ||
       g->ram[6U]!=g->ram[0x3e6U+slot] ||
       g->ram[2U]!=g->ram[0x3e4U+slot] ||
       g->ram[address]!=g->ram[0x3e8U+slot] ||
       g->ram[0x3ecU+slot]==0U) ++failures;
    g->ram[0x3ecU+slot]=0x77U;
    if(close_gate) g->ram[0x301U]=0x20U;
}
int main(void)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned int low,row,slot,n,old_failures,count;
    count=0U;
    for(slot=0U;slot<2U;++slot)
        for(low=0U;low<256U;++low)
            for(row=0U;row<256U;++row) {
                memset(&g,0xa5,sizeof(g));g.ram[0x301U]=0U;
                g.ram[0x3ecU]=0U;g.ram[0x3edU]=0U;
                g.ram[0x3ecU+slot]=0xffU;
                g.ram[0x3e6U+slot]=(mysmb_u8)low;
                g.ram[0x3e4U+slot]=(mysmb_u8)row;
                g.ram[0x3e8U+slot]=0xc4U;
                memcpy(expected,g.ram,sizeof(expected));
                expected[8U]=0U;expected[6U]=(mysmb_u8)low;
                expected[7U]=5U;expected[2U]=(mysmb_u8)row;
                expected[0x500U+low+row]=0xc4U;
                expected[0x3ecU+slot]=0U;calls=0U;old_failures=failures;
                mysmb_area_apply_block_replacements(&g);
                if(calls!=1U || sequence[0]!=slot ||
                   memcmp(expected,g.ram,sizeof(expected))) ++failures;
                if(failures!=old_failures) return 1;
                ++count;
            }
    for(n=0U;n<8U;++n) {
        memset(&g,0,sizeof(g));g.ram[0x300U]=0xa5U;
        g.ram[0x301U]=(n&1U)?0x20U:0U;
        g.ram[0x3ecU]=(n&2U)?2U:0U;g.ram[0x3edU]=(n&4U)?0xffU:0U;
        g.ram[8U]=0x55U;calls=0U;
        mysmb_area_apply_block_replacements(&g);
        if(g.ram[8U]!=0U || g.ram[0x300U]!=0xa5U) ++failures;
        if(n&1U) { if(calls!=0U || g.ram[0x3ecU]!=((n&2U)?2U:0U) ||
            g.ram[0x3edU]!=((n&4U)?0xffU:0U)) ++failures; }
        else if(calls!=((n&2U)?1U:0U)+((n&4U)?1U:0U) ||
                g.ram[0x3ecU]!=0U || g.ram[0x3edU]!=0U) ++failures;
        if(n==6U && (sequence[0]!=1U || sequence[1]!=0U)) ++failures;
    }
    memset(&g,0,sizeof(g));g.ram[0x3ecU]=2U;g.ram[0x3edU]=3U;
    close_gate=1U;calls=0U;mysmb_area_apply_block_replacements(&g);
    if(calls!=1U || sequence[0]!=1U || g.ram[0x3ecU]!=2U ||
       g.ram[0x3edU]!=0U || g.ram[8U]!=0U) ++failures;
    printf("%u full-pointer/write cases, 9 loop/gate cases, %u failures\n",count,failures);
    return failures?1:0;
}
