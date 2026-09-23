#ifndef MYSMB_GAME_AREA_H
#define MYSMB_GAME_AREA_H

#include "game/game.h"

/* ROM $92b0/$93fc, GameMode task 0 before area data parsing. */
void mysmb_area_initialize(struct mysmb_game *game);

struct mysmb_area_source {
    const mysmb_u8 *prg;
    mysmb_u16 prg_size;
};

/* ROM $9c03-$9c2b, pointer tables only; caller owns owner-local data binding. */
mysmb_u8 mysmb_area_load_pointers(struct mysmb_game *game,
                                  const struct mysmb_area_source *source);
/* ROM $9c1c-$9c4a, parse and advance exactly one area header. */
mysmb_u8 mysmb_area_parse_header(struct mysmb_game *game,
                                 const struct mysmb_area_source *source);

#endif
