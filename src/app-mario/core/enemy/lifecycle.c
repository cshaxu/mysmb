#include "core/objects.h"

/* ROM $c998 EraseEnemyObject. One owner serves movement, bounds and
 * projectile callers; the frame timer is $078a, not $078e. */
void mysmb_objects_erase_enemy(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[0x000fU + slot] = 0U;
    game->ram[0x0016U + slot] = 0U;
    game->ram[0x001eU + slot] = 0U;
    game->ram[0x0110U + slot] = 0U;
    game->ram[0x0796U + slot] = 0U;
    game->ram[0x0125U + slot] = 0U;
    game->ram[0x03c5U + slot] = 0U;
    game->ram[0x078aU + slot] = 0U;
}
