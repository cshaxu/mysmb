#ifndef MYSMB_PLATFORM_VGA_FRAME_H
#define MYSMB_PLATFORM_VGA_FRAME_H

#include "game/render.h"

#ifdef MYSMB_DOS16_TARGET
#define MYSMB_VGA_FAR __far
#else
#define MYSMB_VGA_FAR
#endif

enum {
    MYSMB_VGA_WIDTH = 320,
    MYSMB_VGA_HEIGHT = 200,
    MYSMB_VGA_PAGE_COUNT = 4,
    MYSMB_VGA_PAGE_SIZE = 16000,
    MYSMB_VGA_COLOR_SKY = 1,
    MYSMB_VGA_COLOR_GROUND = 2,
    MYSMB_VGA_COLOR_BLOCK = 6,
    MYSMB_VGA_COLOR_PLAYER = 4,
    MYSMB_VGA_COLOR_ENEMY = 14
};

struct mysmb_vga_frame {
    mysmb_u8 MYSMB_VGA_FAR *pages[MYSMB_VGA_PAGE_COUNT];
};

void mysmb_vga_frame_initialize(struct mysmb_vga_frame *vga_frame,
                                mysmb_u8 MYSMB_VGA_FAR *page0,
                                mysmb_u8 MYSMB_VGA_FAR *page1,
                                mysmb_u8 MYSMB_VGA_FAR *page2,
                                mysmb_u8 MYSMB_VGA_FAR *page3);
void mysmb_vga_frame_build(const struct mysmb_render_frame *render_frame,
                           struct mysmb_vga_frame *vga_frame);

#endif
