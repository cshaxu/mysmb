#include "core/enemy/actor_slots.h"
#include "core/enemy/movement.h"

/* ROM $CAFF-$CB24 ProcMoveRedPTroopa through MovPTDwn.
 * $0401 is the original-height anchor despite the ROM's XPos name. */
void mysmb_objects_step_red_paratroopas_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    if ((game->ram[0x00a0U + slot] | game->ram[0x0434U + slot]) == 0U) {
        game->ram[0x0417U + slot] = 0U;
        if (game->ram[0x00cfU + slot] < game->ram[0x0401U + slot]) {
            if ((game->ram[9U] & 7U) == 0U) ++game->ram[0x00cfU + slot];
            return;
        }
    }
    if (game->ram[0x00cfU + slot] < game->ram[0x0058U + slot])
        mysmb_enemy_move_red_down(game, slot);
    else
        mysmb_enemy_move_red_up(game, slot);
}
