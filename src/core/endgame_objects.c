#include "core/enemy/actor_slots.h"
#include "core/objects.h"

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_fireworks(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[0x000fU + slot] != 0U &&
            game->ram[0x0016U + slot] == 22U) {
            game->ram[8U] = slot;
            mysmb_objects_step_fireworks_slot(game, slot);
        }
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_star_flags(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[0x000fU + slot] != 0U &&
            game->ram[0x0016U + slot] == 49U) {
            game->ram[8U] = slot;
            mysmb_objects_step_star_flags_slot(game, slot);
        }
    }
}