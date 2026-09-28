#include "game/blocks/head.h"
#include "game/objects.h"
#include <stdio.h>
#include <string.h>

static unsigned int failures, calls;
static mysmb_u8 replacement_tile, expected_state, expected_replacement;
static mysmb_u8 expected_y, expected_slot, expected_child;

void mysmb_area_destroy_block_metatile(struct mysmb_game *g,
    mysmb_u8 slot, mysmb_u8 low, mysmb_u8 row)
{
    if (calls++ != 0U || slot != 0U || low != 0x20U || row != 0x30U ||
        g->ram[0x26U] != expected_state || g->ram[0x550U] != 0xa5U)
        ++failures;
    /* A child changes control and the buffer: the caller must reload both.
     * The incoming metatile is separately preserved across this call. */
    g->ram[0x3eeU] = expected_slot;
    g->ram[0x550U] = replacement_tile;
}
mysmb_u8 mysmb_blocks_bumped_index(mysmb_u8 tile)
{
    if (calls++ != 1U || tile != replacement_tile) ++failures;
    return tile == 0x51U ? 0xffU : 0U;
}
static void check_child(struct mysmb_game *g, mysmb_u8 slot, mysmb_u8 which)
{
    if (calls++ != 2U || which != expected_child || slot != expected_slot ||
        g->ram[0x3e4U+slot] != 0x30U || g->ram[0x3e6U+slot] != 0x20U ||
        g->ram[0x3e8U+slot] != expected_replacement ||
        g->ram[0x550U] != 0x23U || g->ram[0x784U] != 0x10U ||
        g->ram[5U] != 0xc1U || g->ram[0x8fU+slot] != 0U ||
        g->ram[0x76U+slot] != 0U || g->ram[0x3eaU+slot] != 0U ||
        g->ram[0xbeU+slot] != 1U || g->ram[0xd7U+slot] != expected_y)
        ++failures;
    g->ram[0x3eeU] = 0x80U;
}
void mysmb_blocks_bump(struct mysmb_game *g, mysmb_u8 slot)
{ check_child(g,slot,0U); }
void mysmb_blocks_shatter(struct mysmb_game *g, mysmb_u8 slot)
{ check_child(g,slot,1U); }

int main(void)
{
    static struct mysmb_game g;
    /* size, crouch, read tile, flag, timer, replacement, child, Y, final timer */
    static const unsigned char cases[][9] = {
        {0,0,0x51,0,0,0,1,0x20,0},
        {1,0,0x51,0,0,0x51,0,0x30,0},
        {0,1,0x51,0,0,0,1,0x30,0},
        {0,0,0xc1,0,0,0xc4,0,0x20,0},
        {1,1,0x58,0,0,0x58,0,0x30,0x0b},
        {0,0,0x5d,1,2,0x5d,0,0x20,2},
        {0,0,0x58,1,0,0xc4,0,0x20,0},
        {1,0,0x5d,1,0,0xc4,0,0x30,0}
    };
    unsigned int i,slot,x,page,position_cases;
    mysmb_u16 world;
    position_cases=0U;
    for(slot=0U;slot<2U;++slot) for(page=0U;page<256U;++page)
    for(x=0U;x<256U;++x) {
        memset(&g,0,sizeof(g));g.ram[0x86U]=(mysmb_u8)x;
        g.ram[0x6dU]=(mysmb_u8)page;g.ram[0xb5U]=0xa5U;
        mysmb_blocks_initialize_position(&g,(mysmb_u8)slot);
        world=(mysmb_u16)(((mysmb_u16)page<<8U)+x+8U);
        world=(mysmb_u16)(world & 0xfff0U);
        if (g.ram[0x8fU+slot]!=(mysmb_u8)world ||
            g.ram[0x76U+slot]!=(mysmb_u8)(world>>8U) ||
            g.ram[0x3eaU+slot]!=(mysmb_u8)(world>>8U) ||
            g.ram[0xbeU+slot]!=0xa5U) ++failures;
        ++position_cases;
    }
    for(slot=0U;slot<2U;++slot) for(i=0U;i<sizeof(cases)/sizeof(cases[0]);++i) {
        memset(&g,0,sizeof(g));calls=0U;
        expected_slot=(mysmb_u8)slot;replacement_tile=cases[i][2];
        expected_state=cases[i][0]?0x11U:0x12U;
        expected_replacement=cases[i][5];expected_child=cases[i][6];expected_y=cases[i][7];
        g.ram[0x754U]=cases[i][0];g.ram[0x714U]=cases[i][1];
        g.ram[0x26U+slot]=expected_state;
        g.ram[0x6bcU]=cases[i][3];g.ram[0x79dU]=cases[i][4];
        g.ram[0x550U]=0xa5U;g.ram[0x86U]=0xffU;g.ram[0x6dU]=0xffU;
        g.ram[0xb5U]=1U;g.ram[0xceU]=0x20U;
        if (!mysmb_objects_start_head_bump(&g,0xc1U,0x20U,0x30U)) ++failures;
        if (calls!=3U || g.ram[0x3eeU]!=0x81U || g.ram[0x79dU]!=cases[i][8]) ++failures;
    }
    printf("%u coordinate cases, 16 child-order cases, %u failures\n",position_cases,failures);
    return failures?1:0;
}
