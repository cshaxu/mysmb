#include "game/enemy/core.h"
#include "game/enemy/actor_slots.h"
#include "game/objects.h"
#include "game/oam/oam.h"
#include <string.h>

static unsigned int calls, failures;
static mysmb_u8 expected_slot;
static void check(mysmb_u8 slot,unsigned int order)
{ if (slot!=expected_slot || ++calls!=order) ++failures; }
void mysmb_oam_get_enemy_offscreen_bits(struct mysmb_game *g,mysmb_u8 s)
{ check(s,1U);g->ram[0x3d1U]=0x63U; }
void mysmb_oam_relative_enemy_position(struct mysmb_game *g,mysmb_u8 s)
{ if (g->ram[0x3d1U]!=0x63U) ++failures;check(s,2U);g->ram[0x3aeU]=0x24U; }
void mysmb_oam_draw_retainer(struct mysmb_game *g,mysmb_u8 s)
{ if (g->ram[0x3aeU]!=0x24U) ++failures;check(s,3U); }
void mysmb_objects_step_platforms_slot(struct mysmb_game *g,mysmb_u8 s)
{ (void)g;(void)s;++failures; }
void mysmb_objects_step_bowsers_slot(struct mysmb_game *g,mysmb_u8 s)
{ (void)g;(void)s;++failures; }
void mysmb_objects_draw_bowsers_slot(struct mysmb_game *g,mysmb_u8 s)
{ (void)g;(void)s;++failures; }
int main(void)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned int slot,value;
    for (slot=0U;slot<6U;++slot) for (value=0U;value<256U;++value) {
        memset(game.ram,(int)value,2048U);memcpy(expected,game.ram,2048U);
        expected[0x3d1U]=0x63U;expected[0x3aeU]=0x24U;
        expected_slot=(mysmb_u8)slot;calls=0U;
        mysmb_objects_draw_retainer(&game,(mysmb_u8)slot);
        if (calls!=3U || memcmp(expected,game.ram,2048U)) ++failures;
    }
    return failures?1:0;
}
