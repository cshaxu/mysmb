#ifndef MYSMB_GAME_ENEMY_INIT_TARGETS_H
#define MYSMB_GAME_ENEMY_INIT_TARGETS_H

#include "game/game.h"

/* Explicit initializer entry boundaries; child conformance is tracked separately. */
void mysmb_enemy_init_piranha_plant(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_normal(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_red_koopa(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_goomba(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_hammer_bro(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_bullet_bill(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_piranha_entry(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_cheep_cheep(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_podoboo(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_bloober(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_jump_green_ptroopa(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_red_ptroopa(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_horizontal_fly_swim(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_lakitu(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_firebar_entry(struct mysmb_game *game, mysmb_u8 slot, mysmb_u8 long_entry);
void mysmb_enemy_init_balance_platform(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_vertical_platform(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_large_lift_up(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_large_lift_down(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_horizontal_platform(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_drop_platform(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_small_lift_up(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_small_lift_down(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_bowser(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_init_retainer(struct mysmb_game *game, mysmb_u8 slot);

#endif
