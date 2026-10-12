#ifndef MYSMB_GAME_BLOCKS_BUMP_H
#define MYSMB_GAME_BLOCKS_BUMP_H
#include "core/game.h"
#include "core/blocks/chunks.h"
/* Original Y result: 0..13 means carry set; $ff means carry clear. */
mysmb_u8 mysmb_blocks_bumped_index(mysmb_u8 metatile);
void mysmb_blocks_bump(struct mysmb_game *game, mysmb_u8 slot);
#endif
