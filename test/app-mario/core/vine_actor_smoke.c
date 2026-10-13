#include "core/objects.h"
#include "core/oam/oam.h"
#include "core/world/world.h"
#include <stdio.h>
#include <string.h>
static unsigned int calls,errors,draws,erases,queries,mutation;
static mysmb_u8 offscreen,query_row,erased[2];
void mysmb_oam_relative_enemy_position(struct mysmb_game *g,mysmb_u8 slot)
{
    if(calls++!=0U || slot!=5U) ++errors;
    g->ram[0x3b9U]=g->ram[0xd4U];
}
void mysmb_oam_get_enemy_offscreen_bits(struct mysmb_game *g,mysmb_u8 slot)
{
    if(calls++!=1U || slot!=5U || g->ram[0x3b9U]!=g->ram[0xd4U]) ++errors;
    g->ram[0x3d1U]=offscreen;
}
void mysmb_objects_draw_vine(struct mysmb_game *g,mysmb_u8 index)
{
    if(calls!=2U+draws || index!=draws || g->ram[0x3d1U]!=offscreen) ++errors;
    ++calls;++draws;
    if(mutation==1U) g->ram[0x399U]=0x1fU;
    if(mutation==2U) g->ram[0x398U]=2U;
}
void mysmb_objects_erase_enemy(struct mysmb_game *g,mysmb_u8 slot)
{
    if(calls!=2U+draws+erases || erases>=2U) ++errors;
    else erased[erases]=slot;
    ++calls;++erases;g->ram[0xfU+slot]=0U;
    if(mutation==3U) g->ram[0x399U]=0x40U;
}
mysmb_u8 mysmb_world_query_enemy_block(struct mysmb_game *g,mysmb_u8 slot,
    mysmb_u8 adder,mysmb_u8 horizontal,struct mysmb_enemy_terrain *terrain)
{
    (void)g;
    if(calls!=2U+draws || erases!=0U || slot!=5U || adder!=0x1bU || horizontal!=1U) ++errors;
    ++calls;++queries;terrain->block_row_offset=query_row;terrain->block_address=0x600U;
    /* No metatile output: the caller must read the actual block byte. */
    return query_row<0xd0U?1U:0U;
}
static void reset(struct mysmb_game *g,unsigned int count,mysmb_u8 height)
{
    memset(g,0,sizeof(*g));calls=draws=erases=queries=0U;
    g->ram[0x398U]=(mysmb_u8)count;g->ram[0x399U]=height;
    g->ram[0x39aU]=2U;g->ram[0x39bU]=5U;
}
int main(void)
{
    static struct mysmb_game g;
    static const mysmb_u8 heights[10]={0,7,8,31,32,47,48,95,96,255};
    static const mysmb_u8 masks[4]={0,4,8,1};
    static const mysmb_u8 rows[4]={0,0xc0,0xd0,0xff};
    unsigned int count,h,frame,mask,row,occupied,slot,cases;
    mysmb_u8 height,y,block;
    cases=0U;
    for(count=1U;count<=2U;++count) for(h=0U;h<10U;++h)
    for(frame=0U;frame<4U;++frame) for(mask=0U;mask<4U;++mask)
    for(row=0U;row<4U;++row) for(occupied=0U;occupied<2U;++occupied) {
        reset(&g,count,heights[h]);g.ram[9U]=(mysmb_u8)frame;
        offscreen=masks[mask];query_row=rows[row];block=occupied?0x44U:0U;g.ram[0x600U]=block;
        height=heights[h];y=0U;
        if(height!=(count==1U?0x30U:0x60U) && (frame&2U)) {height=(mysmb_u8)(height+1U);y=0xffU;}
        mysmb_objects_step_vine(&g,5U);
        if(g.ram[0xd4U]!=y) ++errors;
        if(height<8U) {
            if(calls!=0U || g.ram[0x399U]!=height) ++errors;
        } else if((offscreen&0xcU)!=0U) {
            if(draws!=count || erases!=count || queries!=0U || erased[0]!=(count==1U?2U:5U) ||
               (count==2U && erased[1]!=2U) || g.ram[0x398U]!=0U || g.ram[0x399U]!=0U) ++errors;
        } else {
            if(draws!=count || erases!=0U || queries!=(height>=0x20U?1U:0U) || g.ram[0x399U]!=height) ++errors;
            if(height>=0x20U && query_row<0xd0U && occupied==0U) block=0x26U;
        }
        if(g.ram[0x600U]!=block) ++errors;
        ++cases;
    }
    for(slot=0U;slot<5U;++slot) {
        reset(&g,0U,0xffU);mysmb_objects_step_vine(&g,(mysmb_u8)slot);
        if(calls!=0U || g.ram[0x399U]!=0xffU) ++errors;
    }
    for(mutation=1U;mutation<=3U;++mutation) {
        reset(&g,1U,0x20U);offscreen=mutation==3U?4U:0U;query_row=0U;
        mysmb_objects_step_vine(&g,5U);
        if(mutation==1U && (queries!=0U || g.ram[0x399U]!=0x1fU)) ++errors;
        if(mutation==2U && (draws!=2U || queries!=1U)) ++errors;
        if(mutation==3U && (erases!=1U || queries!=0U || g.ram[0x399U]!=0U)) ++errors;
    }
    printf("vine actor: %u combinations, slot gates, post-child reads; errors=%u\n",cases,errors);
    return errors!=0U;
}
