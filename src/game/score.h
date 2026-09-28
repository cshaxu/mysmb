#ifndef MYSMB_GAME_SCORE_H
#define MYSMB_GAME_SCORE_H

#include "game/game.h"

/* ROM $BBF8-$BC48. Return values expose the final source X reload. */
extern const mysmb_u8 mysmb_score_coin_offsets[2];
extern const mysmb_u8 mysmb_score_offsets[2];
extern const mysmb_u8 mysmb_score_status_nybbles[2];
mysmb_u8 mysmb_score_update_number(struct mysmb_game *game, mysmb_u8 nybbles);
mysmb_u8 mysmb_score_get_status(struct mysmb_game *game);
mysmb_u8 mysmb_score_add(struct mysmb_game *game);

#endif
