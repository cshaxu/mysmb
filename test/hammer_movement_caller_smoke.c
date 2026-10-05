#include "core/enemy/actor_slots.h"
#include "core/enemy/distance.h"
#include "core/enemy/movement.h"
#include "core/objects.h"
#include <string.h>

static unsigned int spawn_calls,diff_calls,normal_calls,defeated_calls,bad;
static mysmb_u8 active_slot,carry,page_result,throw_value;
mysmb_u8 mysmb_objects_spawn_hammer(struct mysmb_game *g)
{
    ++spawn_calls;
    if(g->ram[0x3a2U+active_slot]!=throw_value) ++bad;
    /* Source continuation uses current child state/timer and does not
     * re-test eligibility or pause flags after returning. */
    g->ram[0x1eU+active_slot]=0x40U;
    g->ram[0x3a2U+active_slot]=0x10U;
    g->ram[0xfU+active_slot]=0U;g->ram[0x747U]=0xffU;
    return carry;
}
mysmb_u8 mysmb_enemy_player_difference(struct mysmb_game *g,mysmb_u8 s)
{
    if(s!=active_slot) ++bad;
    ++diff_calls;g->ram[0U]=0x93U;
    g->ram[0x796U+s]=0U;
    return page_result;
}
void mysmb_enemy_move_normal(struct mysmb_game *g,mysmb_u8 s)
{ if(s!=active_slot || g->ram[0U]!=0x93U) ++bad;++normal_calls; }
void mysmb_enemy_move_defeated(struct mysmb_game *g,mysmb_u8 s)
{ (void)g;if(s!=active_slot) ++bad;++defeated_calls; }

int main(void)
{
    static struct mysmb_game g;
    unsigned int slot,hard,success,sign,off;
    for(slot=0U;slot<6U;++slot) for(hard=0U;hard<2U;++hard)
    for(success=0U;success<2U;++success) for(sign=0U;sign<256U;++sign)
    for(off=0U;off<2U;++off) {
        memset(g.ram,0,2048U);active_slot=(mysmb_u8)slot;
        carry=(mysmb_u8)success;page_result=(mysmb_u8)sign;
        throw_value=(mysmb_u8)(hard?0x1cU:0x30U);
        g.ram[0x6ccU]=(mysmb_u8)hard;g.ram[0x76aU]=(mysmb_u8)(hard^1U);
        g.ram[0x3cU+slot]=2U;g.ram[0x3d1U]=(mysmb_u8)(off?4U:0U);
        g.ram[0x796U+slot]=1U;
        spawn_calls=diff_calls=normal_calls=defeated_calls=bad=0U;
        mysmb_objects_step_hammer_bros_slot(&g,(mysmb_u8)slot);
        if(bad || diff_calls!=1U || normal_calls!=1U || defeated_calls ||
           spawn_calls!=(off?0U:1U) || g.ram[0x3cU+slot]!=1U) return 1;
        if(g.ram[0x46U+slot]!=(sign&128U?1U:2U) ||
           g.ram[0x58U+slot]!=(sign&128U?4U:0xf8U)) return 2;
        if(!off && (g.ram[0x1eU+slot]!=(success?0x48U:0x40U) ||
           g.ram[0x3a2U+slot]!=(success?0x10U:0x0fU))) return 3;
        if(off && (g.ram[0x1eU+slot]!=0U || g.ram[0x3a2U+slot]!=0U)) return 4;
        g.ram[0x1eU+slot]=0xe0U;
        spawn_calls=diff_calls=normal_calls=defeated_calls=bad=0U;
        mysmb_objects_step_hammer_bros_slot(&g,(mysmb_u8)slot);
        if(bad || spawn_calls || diff_calls || normal_calls || defeated_calls!=1U) return 5;
    }
    return 0;
}
