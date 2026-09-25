#ifndef MYSMB_GAME_TERMINAL_MODES_H
#define MYSMB_GAME_TERMINAL_MODES_H

#include "game/game.h"

/* ROM terminal-mode subtree: ContinueGame, PlayerLoseLife, GameOver,
 * NextArea and VictoryModeSubroutines. */
void mysmb_game_lose_life(struct mysmb_game *game);
void mysmb_game_step_game_over(struct mysmb_game *game);
void mysmb_game_next_area(struct mysmb_game *game);
void mysmb_game_step_victory(struct mysmb_game *game);

#endif
