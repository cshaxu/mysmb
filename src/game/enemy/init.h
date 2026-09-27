#ifndef MYSMB_GAME_ENEMY_INIT_H
#define MYSMB_GAME_ENEMY_INIT_H

#include "game/game.h"

/* ROM InitEnemyObject -> CheckpointEnemyID -> InitEnemyRoutines. */
void mysmb_enemy_checkpoint_loaded(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_enemy_initialize_loaded(struct mysmb_game *game, mysmb_u8 slot,
                                   mysmb_u8 row, mysmb_u8 id);
/* ROM InitPiranhaPlant: callers have already installed the actor position. */
void mysmb_enemy_init_piranha_plant(struct mysmb_game *game, mysmb_u8 slot);

#endif
