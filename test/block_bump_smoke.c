#include "core/blocks/bump.h"
#include "core/objects.h"
#include <stdio.h>
#include <string.h>
static unsigned int failures,calls,route;
/* This call-order unit checks the dispatch ABI. Full-ROM routes exercise
 * the actual JumpEngine state helper and vector bytes separately. */
void mysmb_game_jump_engine_state(struct mysmb_game *g,mysmb_u16 ret,mysmb_u8 selector)
{
    if(ret!=0xbdbfU || selector>8U) ++failures;
    g->ram[4U]=(mysmb_u8)ret;g->ram[5U]=(mysmb_u8)(ret>>8U);
}
static mysmb_u8 after_tile,after_slot;
void mysmb_blocks_check_top(struct mysmb_game *g,mysmb_u8 slot,mysmb_u8 low,mysmb_u8 row)
{
    if(calls++!=0U || slot!=0U || low!=0x20U || row!=0x30U ||
       g->ram[0xffU]!=0xa5U || g->ram[0x60U+after_slot]!=0xa5U ||
       g->ram[0x43cU+after_slot]!=0xa5U || g->ram[0x9fU]!=0xa5U ||
       g->ram[0xa8U+after_slot]!=0xa5U) ++failures;
    g->ram[5U]=after_tile;g->ram[0x3eeU]=after_slot;
}
static void check_dispatch(struct mysmb_game *g,mysmb_u8 slot,unsigned int kind)
{
    if(calls++!=1U || slot!=after_slot || g->ram[0xffU]!=2U ||
       g->ram[0x60U+slot]!=0U || g->ram[0x43cU+slot]!=0U ||
       g->ram[0x9fU]!=0U || g->ram[0xa8U+slot]!=0xfeU) ++failures;
    route=kind;
}
void mysmb_objects_start_power_up(struct mysmb_game *g,mysmb_u8 slot)
{ check_dispatch(g,slot,1U); }
void mysmb_objects_coin_block(struct mysmb_game *g,mysmb_u8 slot,mysmb_u8 carry)
{ if(carry!=0U) ++failures;check_dispatch(g,slot,2U); }
void mysmb_objects_start_vine(struct mysmb_game *g,mysmb_u8 enemy,mysmb_u8 slot)
{ if(enemy!=5U) ++failures;check_dispatch(g,slot,3U); }
int main(void)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    static const unsigned char tiles[14]={0xc1U,0xc0U,0x5fU,0x60U,0x55U,0x56U,0x57U,0x58U,0x59U,0x5aU,0x5bU,0x5cU,0x5dU,0x5eU};
    static const unsigned char targets[14]={1,2,2,1,1,3,1,2,1,1,3,1,2,1};
    static const unsigned char types[14]={0,0,0,3,0,0,2,0,3,0,0,2,0,3};
    unsigned int tile,slot,k,index,want,count;
    count=0U;
    for(tile=0U;tile<256U;++tile) {
        index=255U;
        for(k=0U;k<14U;++k) if(tile==tiles[k]) index=k;
        if(mysmb_blocks_bumped_index((mysmb_u8)tile)!=index) ++failures;
        for(slot=0U;slot<2U;++slot) {
            memset(&g,0xa5,sizeof(g));g.ram[6U]=0x20U;g.ram[2U]=0x30U;
            after_slot=(mysmb_u8)slot;after_tile=(mysmb_u8)tile;
            memcpy(expected,g.ram,2048U);expected[5U]=(mysmb_u8)tile;
            expected[0x3eeU]=(mysmb_u8)slot;expected[0xffU]=2U;
            expected[0x60U+slot]=0U;expected[0x43cU+slot]=0U;
            expected[0x9fU]=0U;expected[0xa8U+slot]=0xfeU;
            want=index==255U?0U:targets[index];
            if(want) {expected[4U]=0xbfU;expected[5U]=0xbdU;}
            if(want==1U) expected[0x39U]=types[index];
            route=0U;calls=0U;mysmb_blocks_bump(&g,0U);
            if(route!=want || calls!=(want?2U:1U) || memcmp(g.ram,expected,2048U)!=0) ++failures;
            ++count;
        }
    }
    printf("256 lookup inputs, %u dispatch/write cases, %u failures\n",count,failures);
    return failures?1:0;
}
