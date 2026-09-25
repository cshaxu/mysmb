#ifndef MYSMB_GAME_PPU_FRAME_H
#define MYSMB_GAME_PPU_FRAME_H

#include "game/game.h"

enum {
    /* Source NMI holds scroll at zero until the sprite-0 split. */
    MYSMB_PPU_STATUS_BAR_HEIGHT = 32
};

struct mysmb_ppu_frame {
    /* 2C02 master-palette indices, one complete 256x240 presentation frame. */
    mysmb_u8 pixels[MYSMB_SCREEN_WIDTH * MYSMB_SCREEN_HEIGHT];
};

/* Composes the source PPU-visible state and embedded CHR into one frame.  This
 * is game output: all platform backends receive this same result unchanged. */
void mysmb_ppu_frame_build(const struct mysmb_game *game,
                           struct mysmb_ppu_frame *frame);

#endif