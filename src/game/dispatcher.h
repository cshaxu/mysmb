#ifndef MYSMB_GAME_DISPATCHER_H
#define MYSMB_GAME_DISPATCHER_H

#include "game/game.h"

void mysmb_game_mode(struct mysmb_game *game);
void mysmb_game_core_routine(struct mysmb_game *game);

/* Existing shared child bodies; their interior proofs belong to later chains. */
void mysmb_game_routines(struct mysmb_game *game);
void mysmb_game_engine(struct mysmb_game *game);

#endif
