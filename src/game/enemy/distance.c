#include "game/enemy/distance.h"

/* ROM $E143 PlayerEnemyDiff dependency boundary. Its node retains its
 * later source-order owner; introducing this seam does not certify it. */
mysmb_u8 mysmb_enemy_player_difference(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 borrow;
    borrow = game->ram[0x0087U + slot] < game->ram[0x0086U] ? 1U : 0U;
    game->ram[0U] = (mysmb_u8)(game->ram[0x0087U + slot] - game->ram[0x0086U]);
    return (mysmb_u8)(game->ram[0x006eU + slot] - game->ram[0x006dU] - borrow);
}
