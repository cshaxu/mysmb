#include "game/enemy/actor_slots.h"
#include "game/objects.h"
#include "game/oam/oam.h"

/* ROM $C935 RunBowserFlame: Proc owns motion/drawing; this caller owns
 * offscreen, relative, bounding-box, player collision and terminal bounds. */
void mysmb_objects_step_bowser_flames_slot(struct mysmb_game *game,
                                          mysmb_u8 slot)
{
    mysmb_enemy_proc_bowser_flame(game, slot);
    mysmb_oam_get_enemy_offscreen_bits(game, slot);
    mysmb_oam_relative_enemy_position(game, slot);
    mysmb_objects_update_enemy_bounding_box(game, slot);
    mysmb_objects_player_enemy_current(game, slot, 1U);
    mysmb_objects_check_enemy_offscreen_bounds(game, slot);
}

/* ROM $C947 RunFirebarObj always reaches bounds, even after injury.
 * The returned compatibility signal is used only by the legacy bulk caller;
 * RunEnemyObjectsCore ignores it, as the original caller does. */
mysmb_u8 mysmb_objects_step_firebars_slot(struct mysmb_game *game,
                                         mysmb_u8 slot)
{
    mysmb_u8 legacy_injury;
    legacy_injury = mysmb_enemy_proc_firebar(game, slot);
    mysmb_objects_check_enemy_offscreen_bounds(game, slot);
    return legacy_injury;
}
