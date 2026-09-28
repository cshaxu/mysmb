#ifndef MYSMB_GAME_ENEMY_MOVEMENT_H
#define MYSMB_GAME_ENEMY_MOVEMENT_H

#include "game/game.h"

/* ROM MoveNormalEnemy and its state/temporary-speed/revival branches. */
/* ROM $CAF9 MoveJumpingEnemy: shared star/paratroopa child. */
void mysmb_enemy_move_jumping(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_move_normal(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_move_d_vertically(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_move_falling_platform(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_move_drop_platform(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_move_slow_vertically(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_move_j_vertically(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_move_red_down(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_move_red_up(struct mysmb_game *game, mysmb_u8 slot);

/* ROM SetHiMax/ImposeGravitySprObj and MoveD_EnemyVertically.  Actor routes
 * supply their original amount and maximum-speed literals. */
void mysmb_enemy_move_downward(struct mysmb_game *game, mysmb_u8 slot,
                               mysmb_u8 amount, mysmb_u8 maximum_speed);

#endif
