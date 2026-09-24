#ifndef MYSMB_PLATFORM_TEXT_FRAME_H
#define MYSMB_PLATFORM_TEXT_FRAME_H

#include "game/render.h"

enum {
    MYSMB_TEXT_COLUMNS = 80,
    MYSMB_TEXT_ROWS = 25,
    MYSMB_TEXT_COLOR_SKY = 0x1f,
    MYSMB_TEXT_COLOR_GROUND = 0x2e,
    MYSMB_TEXT_COLOR_BLOCK = 0x6e,
    MYSMB_TEXT_COLOR_ACTOR = 0x4f,
    MYSMB_TEXT_COLOR_ENEMY = 0x6f
};

struct mysmb_text_cell {
    mysmb_u8 character;
    mysmb_u8 color;
};

struct mysmb_text_frame {
    struct mysmb_text_cell cells[MYSMB_TEXT_ROWS * MYSMB_TEXT_COLUMNS];
};

void mysmb_text_frame_build(const struct mysmb_render_frame *render_frame,
                            struct mysmb_text_frame *text_frame);

#endif
