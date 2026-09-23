#ifndef MYSMB_GAME_AREA_H
#define MYSMB_GAME_AREA_H

#include "game/game.h"

/* ROM $92b0/$93fc, GameMode task 0 before area data parsing. */
void mysmb_area_initialize(struct mysmb_game *game);

#endif
