#ifndef MYSMB_GAME_BLOCKS_CHUNKS_H
#define MYSMB_GAME_BLOCKS_CHUNKS_H
#include "core/game.h"
void mysmb_blocks_shatter(struct mysmb_game *game, mysmb_u8 slot);
void mysmb_blocks_check_top(struct mysmb_game *game, mysmb_u8 slot,
                            mysmb_u8 block_low, mysmb_u8 block_row);
void mysmb_blocks_spawn_chunks(struct mysmb_game *game, mysmb_u8 slot);
#endif
