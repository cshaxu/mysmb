#ifndef MYSMB_GAME_RENDER_H
#define MYSMB_GAME_RENDER_H

#include "game/game.h"

enum {
    MYSMB_RENDER_TILE_ROWS = 30,
    MYSMB_RENDER_TILE_COLUMNS = 32,
    MYSMB_RENDER_MAX_ACTORS = 6,
    MYSMB_RENDER_MAX_COMMANDS = MYSMB_RENDER_TILE_ROWS + MYSMB_RENDER_MAX_ACTORS,
    MYSMB_RENDER_COMMAND_TILE_ROW = 1,
    MYSMB_RENDER_COMMAND_ACTOR = 2
};

struct mysmb_render_command {
    mysmb_u8 kind;
    mysmb_u8 x;
    mysmb_u8 y;
    mysmb_u8 length;
    mysmb_u16 data_offset;
    mysmb_u8 identity;
};

struct mysmb_render_frame {
    mysmb_u8 command_count;
    mysmb_u8 tile_data[MYSMB_RENDER_TILE_ROWS * MYSMB_RENDER_TILE_COLUMNS];
    struct mysmb_render_command commands[MYSMB_RENDER_MAX_COMMANDS];
};

void mysmb_render_build(const struct mysmb_game *game,
                        struct mysmb_render_frame *frame);

#endif
