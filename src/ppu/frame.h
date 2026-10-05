#ifndef MYSMB_PPU_FRAME_H
#define MYSMB_PPU_FRAME_H

#include "ppu/state.h"
#include "io/video.h"

enum {
    /* Source NMI holds scroll at zero until the sprite-0 split. */
    MYSMB_PPU_STATUS_BAR_HEIGHT = 32,
    MYSMB_PPU_FRAME_WIDTH = MYSMB_IO_VIDEO_WIDTH,
    MYSMB_PPU_FRAME_HEIGHT = MYSMB_IO_VIDEO_HEIGHT
};

#define MYSMB_PPU_FRAME_FAR MYSMB_IO_FAR

struct mysmb_ppu_frame {
#ifdef MYSMB_DOS16_TARGET
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *pixels;
#else
    mysmb_io_u8 pixels[MYSMB_PPU_FRAME_WIDTH * MYSMB_PPU_FRAME_HEIGHT];
#endif
};
#ifdef MYSMB_DOS16_TARGET
void mysmb_ppu_frame_bind_pixels(struct mysmb_ppu_frame *frame,
                                 mysmb_io_u8 MYSMB_PPU_FRAME_FAR *pixels);
#endif

/* Composes the source PPU-visible state and embedded CHR into one frame.  This
 * is a read-only PPU projection:all backends receive the same pixel result. */
void mysmb_ppu_frame_build(const struct mysmb_ppu_state *state,
                           struct mysmb_ppu_frame *frame);

#endif
