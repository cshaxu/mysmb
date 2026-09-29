#include "game/objects.h"
#include "game/world/world.h"

/* ROM $D7C4-$D7FF PlayerHammerCollision/ClHCol/ExPHC. Geometry and
 * injury retain their own owners; the original misc slot is reloaded
 * after geometry, on both its carry-set and carry-clear returns. */
void mysmb_objects_check_hammer_collision(struct mysmb_game *game,
                                           mysmb_u8 slot)
{
    mysmb_u8 box;
    mysmb_u8 hit;
    if ((game->ram[9U] & 1U) == 0U ||
        (game->ram[0x0747U] | game->ram[0x03d6U]) != 0U) return;
    box = (mysmb_u8)(slot * 4U + 0x24U);
    hit = mysmb_world_boxes_collide(game, 0x04acU,
        (mysmb_u16)(0x04acU + box));
    slot = game->ram[8U];
    if (hit == 0U) {
        game->ram[0x06beU + slot] = 0U;
        return;
    }
    if (game->ram[0x06beU + slot] != 0U) return;
    game->ram[0x06beU + slot] = 1U;
    game->ram[0x0064U + slot] = (mysmb_u8)(0U - game->ram[0x0064U + slot]);
    if (game->ram[0x079fU] != 0U) return;
    mysmb_objects_force_injury(game);
}
