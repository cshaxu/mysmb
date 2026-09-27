#ifndef MYSMB_GAME_STATUS_H
#define MYSMB_GAME_STATUS_H

#include "game/game.h"

/* ROM $8ebe-$8fbf: shared status output, digit arithmetic and top score. */
mysmb_u8 mysmb_status_queue_bottom_line(struct mysmb_game *game);
mysmb_u8 mysmb_status_queue_timer(struct mysmb_game *game);
mysmb_u8 mysmb_status_queue_score_coin(struct mysmb_game *game);
mysmb_u8 mysmb_status_queue_title_score(struct mysmb_game *game);
void mysmb_status_apply_digit_modifier(struct mysmb_game *game, mysmb_u8 digit_offset);
void mysmb_status_update_top_score(struct mysmb_game *game);

#endif
