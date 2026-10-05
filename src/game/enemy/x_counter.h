#ifndef MYSMB_GAME_ENEMY_X_COUNTER_H
#define MYSMB_GAME_ENEMY_X_COUNTER_H
#include "core/game.h"

void mysmb_enemy_x_counter_green(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_x_counter_platform(struct mysmb_game *game, mysmb_u8 slot,
                                    mysmb_u8 maximum);
void mysmb_enemy_move_with_x_counters(struct mysmb_game *game, mysmb_u8 slot);
#endif
