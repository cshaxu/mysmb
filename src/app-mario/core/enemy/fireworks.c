#include "core/enemy/actor_slots.h"
#include "core/objects.h"
#include "core/oam/oam.h"

/* ROM $D295-$D2CC RunFireworks / SetupExpl / FireworksSoundScore. */
void mysmb_objects_step_fireworks_slot(struct mysmb_game *g, mysmb_u8 slot)
{
    --g->ram[0x00a0U+slot];
    if (g->ram[0x00a0U+slot] == 0U) {
        g->ram[0x00a0U+slot] = 8U;
        ++g->ram[0x0058U+slot];
        if (g->ram[0x0058U+slot] >= 3U) {
            g->ram[0x000fU+slot] = 0U;
            g->ram[0x00feU] = 8U;
            g->ram[0x0138U] = 5U;
            mysmb_objects_end_area_points(g);
            return;
        }
    }
    mysmb_oam_relative_enemy_position(g,slot);
    slot = g->ram[8U];
    g->ram[0x03baU] = g->ram[0x03b9U];
    g->ram[0x03afU] = g->ram[0x03aeU];
    mysmb_oam_draw_fireworks_explosion(g,g->ram[0x0058U+slot],g->ram[0x06e5U+slot]);
}
