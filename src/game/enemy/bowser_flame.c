#include "game/enemy/actor_slots.h"
#include "game/enemy/frenzy.h"
#include "game/oam/oam.h"

/* ROM $D1EB-$D21F ProcBowserFlame / SFlmX; SetGfxF owns the tail. */
void mysmb_enemy_proc_bowser_flame(struct mysmb_game *g, mysmb_u8 slot)
{
    mysmb_u8 force, borrow, x;
    unsigned int distance;
    if (g->ram[0x0747U] == 0U) {
        g->ram[0U] = g->ram[0x06ccU] == 0U ? 0x40U : 0x60U;
        force = g->ram[0x0401U+slot];
        borrow = force < g->ram[0U] ? 1U : 0U;
        g->ram[0x0401U+slot] = (mysmb_u8)(force-g->ram[0U]);
        x = g->ram[0x0087U+slot];
        distance = 1U+borrow;
        g->ram[0x0087U+slot] = (mysmb_u8)(x-distance);
        g->ram[0x006eU+slot] = (mysmb_u8)(g->ram[0x006eU+slot]-(x<distance?1U:0U));
        if (g->ram[0x00cfU+slot] != mysmb_enemy_flame_y_positions[g->ram[0x0417U+slot]])
            g->ram[0x00cfU+slot] = (mysmb_u8)(g->ram[0x00cfU+slot]+g->ram[0x0434U+slot]);
    }
    mysmb_objects_draw_bowser_flame(g,slot);
}
