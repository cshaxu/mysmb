#ifndef MYSMB_GAME_PPU_FRAME_H
#define MYSMB_GAME_PPU_FRAME_H

#include "game/game.h"

enum {
    /* Source NMI holds scroll at zero until the sprite-0 split. */
    MYSMB_PPU_STATUS_BAR_HEIGHT = 32
};

#ifdef MYSMB_DOS16_TARGET
#define MYSMB_PPU_FRAME_FAR __far
#else
#define MYSMB_PPU_FRAME_FAR
#endif

struct mysmb_ppu_frame {
#ifdef MYSMB_DOS16_TARGET
    mysmb_u8 MYSMB_PPU_FRAME_FAR *pixels;
#else
    mysmb_u8 pixels[MYSMB_SCREEN_WIDTH * MYSMB_SCREEN_HEIGHT];
#endif
};
#ifdef MYSMB_DOS16_TARGET
void mysmb_ppu_frame_bind_pixels(struct mysmb_ppu_frame *frame,
                                 mysmb_u8 MYSMB_PPU_FRAME_FAR *pixels);
#endif

/* Composes the source PPU-visible state and embedded CHR into one frame.  This
 * is game output: all platform backends receive this same result unchanged. */
void mysmb_ppu_frame_build(const struct mysmb_game *game,
                           struct mysmb_ppu_frame *frame);

#endif
