#include "core/enemy/actor_slots.h"
#include "core/enemy/movement.h"
#include <string.h>

static unsigned char expected[2048];
static unsigned int calls,bad;
static mysmb_u8 active_slot,want_direction;
static void child(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 direction)
{
    if(s!=active_slot || direction!=want_direction ||
       memcmp(g->ram,expected,2048U)) ++bad;
    ++calls;g->ram[0x1eU+s]=0x63U;expected[0x1eU+s]=0x63U;
}
void mysmb_enemy_move_red_down(struct mysmb_game *g,mysmb_u8 s)
{child(g,s,0U);}
void mysmb_enemy_move_red_up(struct mysmb_game *g,mysmb_u8 s)
{child(g,s,1U);}
int main(void)
{
    static struct mysmb_game g;
    unsigned int slot,phase,motion,y,anchor,center,sentinel,early;
    for(slot=0U;slot<6U;++slot) for(phase=0U;phase<8U;++phase)
    for(motion=0U;motion<4U;++motion) for(y=0x7fU;y<=0x81U;++y)
    for(anchor=0x7fU;anchor<=0x81U;++anchor)
    for(center=0x7fU;center<=0x81U;++center)
    for(sentinel=0U;sentinel<2U;++sentinel) {
        memset(g.ram,0xa5,2048U);active_slot=(mysmb_u8)slot;
        g.ram[9U]=(mysmb_u8)phase;g.ram[0xcfU+slot]=(mysmb_u8)y;
        g.ram[0x401U+slot]=(mysmb_u8)anchor;g.ram[0x58U+slot]=(mysmb_u8)center;
        g.ram[0xa0U+slot]=(mysmb_u8)(motion&1U?0xffU:0U);
        g.ram[0x434U+slot]=(mysmb_u8)(motion&2U?0x80U:0U);
        g.ram[0x417U+slot]=(mysmb_u8)(sentinel?0xffU:0U);
        memcpy(expected,g.ram,2048U);calls=bad=0U;
        if(motion==0U) expected[0x417U+slot]=0U;
        early=motion==0U && y<anchor;
        if(early && phase==0U) ++expected[0xcfU+slot];
        want_direction=(mysmb_u8)(y>=center);
        mysmb_objects_step_red_paratroopas_slot(&g,(mysmb_u8)slot);
        if(bad || calls!=(early?0U:1U) || memcmp(g.ram,expected,2048U)) return 1;
    }
    return 0;
}
