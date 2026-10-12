#include "core/enemy/actor_slots.h"
#include "core/enemy/movement.h"
#include "core/world/world.h"

/* ROM $CED5-$CF24: PRandomSubtracter/FlyCCBPriority and their movement
 * consumer. Original high-nibble indices also read table-adjacent bytes.
 * The immutable PRG view supplies data only; no instructions are executed. */
void mysmb_objects_step_flying_cheep_cheeps_slot(struct mysmb_game *game,
                                               mysmb_u8 slot)
{
    mysmb_u8 index, difference;
    if ((game->ram[0x001eU + slot] & 0x20U) != 0U) {
        game->ram[0x03c5U + slot] = 0U;
        mysmb_enemy_move_j_vertically(game, slot);
        return;
    }
    (void)mysmb_world_move_enemy_horizontally(game, slot);
    mysmb_enemy_move_downward(game, slot, 0x0dU, 5U);
    /* Resource binding is required for the original indexed data tail. */
    if (game->area_prg == 0 || game->area_prg_size < 0x4eeaU) return;
    index = (mysmb_u8)(game->ram[0x0434U + slot] >> 4U);
    difference = (mysmb_u8)(game->ram[0x00cfU + slot] -
        game->area_prg[0x4ed5U + index]);
    if ((difference & 0x80U) != 0U)
        difference = (mysmb_u8)(0U - difference);
    if (difference < 8U) {
        game->ram[0x0434U + slot] =
            (mysmb_u8)(game->ram[0x0434U + slot] + 0x10U);
        index = (mysmb_u8)(game->ram[0x0434U + slot] >> 4U);
    }
    game->ram[0x03c5U + slot] = game->area_prg[0x4edaU + index];
}
