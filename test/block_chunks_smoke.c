#include "game/blocks/chunks.h"
#include "game/score.h"
#include <stdio.h>
#include <string.h>
static unsigned int failures,calls;
static mysmb_u8 expected_slot;
void mysmb_area_remove_coin_axe(struct mysmb_game *g,mysmb_u8 low,mysmb_u8 row)
{
    if(calls++!=0U || low!=0x20U || row!=0x20U || g->ram[0x640U]!=0U) ++failures;
    g->ram[0x3eeU]=expected_slot;
    g->ram[2U]=0x37U;
}
void mysmb_objects_setup_jump_coin(struct mysmb_game *g,mysmb_u8 slot)
{ if(calls++!=1U || slot!=expected_slot || g->ram[2U]!=0x37U) ++failures; }
mysmb_u8 mysmb_score_add(struct mysmb_game *g)
{
    if(calls++!=0U || g->ram[0x9fU]!=0xfeU || g->ram[0x139U]!=5U ||
       g->ram[0xfdU]!=1U || g->ram[0xffU]!=0xa5U ||
       g->ram[0x3ecU+expected_slot]!=1U || g->ram[0xa8U+expected_slot]!=0xfaU ||
       g->ram[0xaaU+expected_slot]!=0xfcU) ++failures;
    return expected_slot;
}
int main(void)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned int slot,y,row,kind,count;
    count=0U;
    for(slot=0U;slot<2U;++slot) for(y=0U;y<256U;++y) {
        memset(&g,0xa5,sizeof(g));g.ram[0xd7U+slot]=(mysmb_u8)y;
        g.ram[0x8fU+slot]=(mysmb_u8)(255U-y);g.ram[0x76U+slot]=(mysmb_u8)y;
        memcpy(expected,g.ram,2048U);
        expected[0x3f1U+slot]=(mysmb_u8)(255U-y);
        expected[0x60U+slot]=0xf0U;expected[0x62U+slot]=0xf0U;
        expected[0xa8U+slot]=0xfaU;expected[0xaaU+slot]=0xfcU;
        expected[0x43cU+slot]=0U;expected[0x43eU+slot]=0U;
        expected[0x78U+slot]=(mysmb_u8)y;expected[0x91U+slot]=(mysmb_u8)(255U-y);
        expected[0xd9U+slot]=(mysmb_u8)(y+8U);
        mysmb_blocks_spawn_chunks(&g,(mysmb_u8)slot);
        if(memcmp(g.ram,expected,2048U)!=0) ++failures;
        ++count;
    }
    for(slot=0U;slot<2U;++slot) for(row=0U;row<256U;row+=16U) for(kind=0U;kind<2U;++kind) {
        mysmb_u16 address;
        memset(&g,0xa5,sizeof(g));g.ram[2U]=(mysmb_u8)row;g.ram[6U]=0x20U;g.ram[7U]=6U;
        g.ram[0x3eeU]=(mysmb_u8)slot;calls=0U;expected_slot=(mysmb_u8)slot;
        address=(mysmb_u16)(0x620U+(mysmb_u8)(row-16U));g.ram[address]=kind?0x51U:0U;
        memcpy(expected,g.ram,2048U);if(row) expected[2U]=(mysmb_u8)(row-16U);
        mysmb_blocks_check_top(&g,0U,0x20U,(mysmb_u8)row);
        if(calls || memcmp(g.ram,expected,2048U)!=0) ++failures;
    }
    for(slot=0U;slot<2U;++slot) {
        memset(&g,0xa5,sizeof(g));g.ram[2U]=0x30U;g.ram[6U]=0x20U;g.ram[7U]=6U;
        g.ram[0x640U]=0xc2U;calls=0U;expected_slot=(mysmb_u8)slot;
        mysmb_blocks_check_top(&g,0U,0x20U,0x30U);
        if(calls!=2U) ++failures;
        memset(&g,0xa5,sizeof(g));g.ram[2U]=0U;g.ram[0x3eeU]=(mysmb_u8)slot;
        calls=0U;mysmb_blocks_shatter(&g,0U);
        if(calls!=1U || g.ram[0xc0U+slot]!=0xa5U) ++failures;
    }
    printf("%u chunk footprints, 64 row paths, 4 child-order cases, %u failures\n",count,failures);
    return failures?1:0;
}
