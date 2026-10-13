#ifndef MYSMB_GAME_BLOCKS_HEAD_H
#define MYSMB_GAME_BLOCKS_HEAD_H
#include "core/game.h"
#include "core/blocks/bump.h"

void mysmb_blocks_head_collision(struct mysmb_game *game, mysmb_u8 metatile);
void mysmb_blocks_initialize_position(struct mysmb_game *game, mysmb_u8 slot);
#endif
