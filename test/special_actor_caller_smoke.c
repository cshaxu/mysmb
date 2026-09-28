#include "game/enemy/actor_slots.h"
#include "game/objects.h"
#include "game/oam/oam.h"
#include <string.h>

static unsigned int events[8],count,bad;
static mysmb_u8 expected_slot,injury;
static void record(struct mysmb_game *g,mysmb_u8 s,unsigned int e)
{
    if(s!=expected_slot || count>=8U) {++bad;return;}
    events[count++]=e;
    if(e==1U || e==7U) {
        /* A child may clear the live flag or pause movement. Neither change
         * may truncate this source caller's remaining phases. */
        g->ram[0xfU+s]=0U;g->ram[0x747U]=0xffU;
    }
}
void mysmb_enemy_proc_bowser_flame(struct mysmb_game *g,mysmb_u8 s)
{record(g,s,1U);}
mysmb_u8 mysmb_enemy_proc_firebar(struct mysmb_game *g,mysmb_u8 s)
{record(g,s,7U);return injury;}
mysmb_u8 mysmb_objects_get_enemy_offscreen_bits(const struct mysmb_game *g,mysmb_u8 s)
{record((struct mysmb_game *)g,s,2U);return 0x93U;}
void mysmb_oam_relative_enemy_position(struct mysmb_game *g,mysmb_u8 s)
{if(g->ram[0x3d1U]!=0x93U) ++bad;record(g,s,3U);}
void mysmb_objects_update_enemy_bounding_box(struct mysmb_game *g,mysmb_u8 s)
{record(g,s,4U);}
void mysmb_objects_player_enemy_current(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 preserve)
{if(preserve!=1U) ++bad;record(g,s,5U);}
void mysmb_objects_check_enemy_offscreen_bounds(struct mysmb_game *g,mysmb_u8 s)
{record(g,s,6U);}
int main(void)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned int slot,value,i;
    for(slot=0U;slot<6U;++slot) for(value=0U;value<256U;++value) {
        expected_slot=(mysmb_u8)slot;
        memset(g.ram,(int)value,2048U);memcpy(expected,g.ram,2048U);
        expected[0xfU+slot]=0U;expected[0x747U]=0xffU;
        expected[0x3d1U]=0x93U;count=bad=0U;
        mysmb_objects_step_bowser_flames_slot(&g,(mysmb_u8)slot);
        if(count!=6U || bad || memcmp(expected,g.ram,2048U)) return 1;
        for(i=0U;i<6U;++i) if(events[i]!=i+1U) return 2;
        memset(g.ram,(int)value,2048U);memcpy(expected,g.ram,2048U);
        expected[0xfU+slot]=0U;expected[0x747U]=0xffU;
        count=bad=0U;injury=(mysmb_u8)value;
        if(mysmb_objects_step_firebars_slot(&g,(mysmb_u8)slot)!=injury) return 3;
        if(count!=2U || events[0]!=7U || events[1]!=6U || bad ||
           memcmp(expected,g.ram,2048U)) return 4;
    }
    return 0;
}
