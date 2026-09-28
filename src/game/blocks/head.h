#ifndef MYSMB_GAME_BLOCKS_HEAD_H
#define MYSMB_GAME_BLOCKS_HEAD_H
#include "game/game.h"

void mysmb_blocks_head_collision(struct mysmb_game *game, mysmb_u8 metatile);
void mysmb_blocks_initialize_position(struct mysmb_game *game, mysmb_u8 slot);
/* Existing child algorithms; S3/S4 retain implementation responsibility. */
mysmb_u8 mysmb_blocks_is_bumpable(mysmb_u8 metatile);
void mysmb_blocks_bump(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_blocks_shatter(struct mysmb_game *game, mysmb_u8 slot);
#endif
