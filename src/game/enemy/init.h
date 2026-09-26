#ifndef MYSMB_GAME_ENEMY_INIT_H
#define MYSMB_GAME_ENEMY_INIT_H

#include "game/game.h"

/* ROM InitEnemyObject -> CheckpointEnemyID -> InitEnemyRoutines. */
void mysmb_enemy_initialize_loaded(struct mysmb_game *game, mysmb_u8 slot,
                                   mysmb_u8 row, mysmb_u8 id);

#endif
