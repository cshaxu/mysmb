#include "game/enemy/actor_slots.h"
#include "game/enemy/init_targets.h"
#include "game/enemy/movement.h"

/* ROM $C9B0 MovePodoboo / $C9CB PdbM, ending at $C9CD. Initialization is a real child;
 * the random byte is read after its return. Gravity runs on both paths. */
void mysmb_objects_step_podoboos_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 random_value;
    if (game->ram[0x0796U + slot] == 0U) {
        mysmb_enemy_init_podoboo(game, slot);
        random_value = game->ram[0x07a8U + slot];
        game->ram[0x0434U + slot] = (mysmb_u8)(random_value | 0x80U);
        game->ram[0x0796U + slot] = (mysmb_u8)((random_value & 0x0fU) | 6U);
        game->ram[0x00a0U + slot] = 0xf9U;
    }
    mysmb_enemy_move_j_vertically(game, slot);
}
