#ifndef MYSMB_GAME_GAME_H
#define MYSMB_GAME_GAME_H

/*
 * Deliberately small until the original RAM map has been admitted.  The game
 * module must stay independent of all host APIs and pointer-width assumptions.
 */
typedef struct mysmb_game mysmb_game;

void mysmb_game_initialize(mysmb_game *game);

#endif
