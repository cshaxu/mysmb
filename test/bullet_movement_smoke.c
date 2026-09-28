#include "game/enemy/actor_slots.h"
#include "game/enemy/movement.h"
#include "game/world/world.h"
#include <string.h>
static unsigned char expected[2048];
static unsigned int calls, bad, want;
static void child(struct mysmb_game *g, mysmb_u8 slot, unsigned int id)
{
    if (memcmp(g->ram,expected,2048U)!=0 || id!=want || slot!=g->ram[8U]) ++bad;
    ++calls;g->ram[0U]=0x93U;expected[0U]=0x93U;
}
void mysmb_enemy_move_j_vertically(struct mysmb_game *g,mysmb_u8 slot)
{ child(g,slot,1U); }
mysmb_u8 mysmb_world_move_enemy_horizontally(struct mysmb_game *g,mysmb_u8 slot)
{ child(g,slot,2U);return 0xfcU; }
int main(void)
{
    static struct mysmb_game g;
    unsigned int slot,state,gate;
    for(slot=0U;slot<6U;++slot) for(state=0U;state<256U;++state)
    for(gate=0U;gate<2U;++gate) {
        memset(g.ram,0xa5,2048U);g.ram[8U]=(mysmb_u8)slot;
        g.ram[0x1eU+slot]=(mysmb_u8)state;g.ram[0x747U]=(mysmb_u8)gate;
        g.ram[0xfU+slot]=(mysmb_u8)gate;g.ram[0x16U+slot]=0xffU;
        memcpy(expected,g.ram,2048U);want=state&32U?1U:2U;
        if(want==2U) expected[0x58U+slot]=0xe8U;
        calls=bad=0U;mysmb_objects_step_bullet_bills_slot(&g,(mysmb_u8)slot);
        if(bad || calls!=1U || memcmp(g.ram,expected,2048U)) return 1;
    }
    return 0;
}
