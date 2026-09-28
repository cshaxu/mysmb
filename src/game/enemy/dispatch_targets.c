#include "game/enemy/core.h"
#include "game/enemy/actor_slots.h"
#include "game/objects.h"
#include "game/oam/oam.h"

/* Original $D065 RunBowser is one actor-vector child. Preserve the existing
 * child interior until its source-order task replaces the legacy behavior. */
void mysmb_enemy_run_bowser(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_objects_step_bowsers_slot(game, slot);
    mysmb_objects_draw_bowsers_slot(game, slot);
}

/* ROM $C8D7 RunRetainerObj: three original child calls in source order. */
void mysmb_objects_draw_retainer(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[0x03d1U] = mysmb_objects_get_enemy_offscreen_bits(game, slot);
    mysmb_oam_relative_enemy_position(game, slot);
    mysmb_oam_draw_retainer(game, slot);
}
