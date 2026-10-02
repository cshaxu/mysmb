#include "game/objects.h"
#include "game/enemy/movement.h"
#include "game/oam/oam.h"

/* ROM $BC85-$BCEA PowerUpObjHandler through ExitPUp. The original
 * current-slot dispatcher enters one complete state and child-call chain. */
void mysmb_objects_step_power_up(struct mysmb_game *game)
{
    mysmb_u8 state;
    mysmb_u8 type;

    game->ram[0x0008U] = 5U;
    state = game->ram[0x0023U];
    if (state == 0U) return;
    if ((state & 0x80U) != 0U) {
        if (game->ram[0x0747U] == 0U) {
            type = game->ram[0x0039U];
            if (type == 0U || type == 3U) {
                mysmb_enemy_move_normal(game, 5U);
                mysmb_objects_enemy_background_current(game, 5U);
            } else if (type == 2U) {
                mysmb_enemy_move_jumping(game, 5U);
                mysmb_objects_step_enemy_jump_terrain(game, 5U);
            }
        }
    } else {
        if ((game->ram[0x0009U] & 3U) == 0U) {
            game->ram[0x00d4U]--;
            game->ram[0x0023U]++;
            if (state >= 0x11U) {
                game->ram[0x005dU] = 0x10U;
                game->ram[0x0023U] = 0x80U;
                game->ram[0x03caU] = 0U;
                game->ram[0x004bU] = 1U;
            }
        }
        if (game->ram[0x0023U] < 6U) return;
    }
    /* RunPUSubs has no state/ID gate between any of its six children. */
    mysmb_oam_relative_enemy_position(game, 5U);
    mysmb_oam_get_enemy_offscreen_bits(game, 5U);
    mysmb_objects_update_enemy_bounding_box(game, 5U);
    mysmb_objects_draw_power_up(game);
    mysmb_objects_player_enemy_current(game, 5U, 1U);
    mysmb_objects_check_enemy_offscreen_bounds(game, 5U);
}
