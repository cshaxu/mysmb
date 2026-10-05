#include "core/enemy/actor_slots.h"
#include "core/enemy/movement.h"
#include "core/world/world.h"

/* ROM $CC36-$CC45 MoveBulletBill / NotDefB. This is the frenzy Bullet
 * Bill movement entry; cannon allocation and timing belong to its callers. */
void mysmb_objects_step_bullet_bills_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    if ((game->ram[0x001eU + slot] & 0x20U) != 0U) {
        mysmb_enemy_move_j_vertically(game, slot);
        return;
    }
    game->ram[0x0058U + slot] = 0xe8U;
    (void)mysmb_world_move_enemy_horizontally(game, slot);
}
