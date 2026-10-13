#ifndef MYSMB_GAME_AREA_BLOCK_BUFFER_H
#define MYSMB_GAME_AREA_BLOCK_BUFFER_H

#include "core/game.h"

/* ROM $9bdd-$9bf5: callers supply a physical block column, 0..31.
 * Writes the indirect pointer to $07 then $06 and returns that address. */
mysmb_u16 mysmb_area_get_block_buffer_address(struct mysmb_game *game,
                                               mysmb_u8 column);

#endif
