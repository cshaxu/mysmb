#ifndef MYSMB_GAME_ENEMY_DISTANCE_H
#define MYSMB_GAME_ENEMY_DISTANCE_H
#include "core/game.h"

/* PlayerEnemyDiff: low result in RAM $00, page result returned as A.
 * The caller uses its sign; carry consumers require their own explicit ABI. */
mysmb_u8 mysmb_enemy_player_difference(struct mysmb_game *game, mysmb_u8 slot);
#endif
