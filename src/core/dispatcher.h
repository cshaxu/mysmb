#ifndef MYSMB_GAME_DISPATCHER_H
#define MYSMB_GAME_DISPATCHER_H

#include "core/game.h"

void mysmb_game_mode(struct mysmb_game *game);
void mysmb_game_core_routine(struct mysmb_game *game);

/* Existing shared child bodies; their interior proofs belong to later chains. */
void mysmb_game_routines(struct mysmb_game *game);
void mysmb_game_engine(struct mysmb_game *game);
struct mysmb_area_source;
void mysmb_game_engine_actors(struct mysmb_game *game,
                               const struct mysmb_area_source *source);
void mysmb_game_engine_blocks(struct mysmb_game *game);
void mysmb_game_process_whirlpools(struct mysmb_game *game);
void mysmb_game_process_cannons(struct mysmb_game *game);
void mysmb_game_handle_cannon_bullet(struct mysmb_game *game, mysmb_u8 slot);

#endif
