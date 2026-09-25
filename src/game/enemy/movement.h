#ifndef MYSMB_GAME_ENEMY_MOVEMENT_H
#define MYSMB_GAME_ENEMY_MOVEMENT_H

#include "game/game.h"

/* ROM SetHiMax/ImposeGravitySprObj and MoveD_EnemyVertically.  Actor routes
 * supply their original amount and maximum-speed literals. */
void mysmb_enemy_move_downward(struct mysmb_game *game, mysmb_u8 slot,
                               mysmb_u8 amount, mysmb_u8 maximum_speed);

#endif
