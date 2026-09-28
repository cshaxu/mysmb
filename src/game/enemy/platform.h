#ifndef MYSMB_GAME_ENEMY_PLATFORM_H
#define MYSMB_GAME_ENEMY_PLATFORM_H
#include "game/game.h"

/* Original child boundaries; bodies retain their individual proof status. */
void mysmb_platform_collision_large(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_platform_collision_small(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_platform_move_balance(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_platform_move_y(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_platform_move_large_lift(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_platform_move_small(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_platform_move_x(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_platform_move_right(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_platform_move_drop(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_platform_box_small(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_platform_box_large(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_platform_movement_dispatch(struct mysmb_game *game, mysmb_u8 slot);
#endif
