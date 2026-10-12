#include "core/objects.h"
#include "core/world/world.h"

/* ROM $e0fe-$e123 DoEnemySideCheck through ExESdeC. $eb is the source
 * direction counter; a solid hit preserves it for the bump successor. */
void mysmb_objects_check_enemy_side(struct mysmb_game *game, mysmb_u8 slot)
{
    struct mysmb_enemy_terrain terrain;
    mysmb_u8 index;
    mysmb_u8 tile;

    if (game->ram[0x00cfU + slot] < 0x20U) return;
    index = 0x16U;
    game->ram[0x00ebU] = 2U;
    do {
        if (game->ram[0x00ebU] == game->ram[0x0046U + slot]) {
            tile = mysmb_world_query_enemy_block(game, slot, index, 1U,
                &terrain) != 0U ? terrain.metatile : 0U;
            if (tile != 0U && mysmb_objects_is_solid_terrain(tile) != 0U) {
                mysmb_objects_bump_enemy(game, slot);
                return;
            }
        }
        --game->ram[0x00ebU];
        ++index;
    } while (index < 0x18U);
}
