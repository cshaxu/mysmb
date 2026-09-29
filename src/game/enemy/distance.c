#include "game/enemy/distance.h"

/* ROM $E143 PlayerEnemyDiff.  Preserve the low-byte subtraction borrow for
 * the page subtraction and retain the low result in source scratch $00. */
mysmb_u8 mysmb_enemy_player_difference(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 borrow;
    borrow = game->ram[0x0087U + slot] < game->ram[0x0086U] ? 1U : 0U;
    game->ram[0U] = (mysmb_u8)(game->ram[0x0087U + slot] - game->ram[0x0086U]);
    return (mysmb_u8)(game->ram[0x006eU + slot] - game->ram[0x006dU] - borrow);
}
