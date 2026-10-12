#include "core/enemy/actor_slots.h"
#include "core/enemy/x_counter.h"

/* ROM $CB25-$CB44 MoveFlyGreenPTroopa, YSway and NoMGPT. */
void mysmb_objects_step_flying_green_paratroopas_slot(struct mysmb_game *game,
                                                    mysmb_u8 slot)
{
    mysmb_enemy_x_counter_green(game, slot);
    mysmb_enemy_move_with_x_counters(game, slot);
    if ((game->ram[9U] & 3U) != 0U) return;
    game->ram[0U] = (game->ram[9U] & 0x40U) != 0U ? 1U : 0xffU;
    game->ram[0x00cfU + slot] = (mysmb_u8)(game->ram[0x00cfU + slot] + game->ram[0U]);
}
