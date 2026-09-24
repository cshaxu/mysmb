#ifndef MYSMB_PLATFORM_VGA_FRAME_H
#define MYSMB_PLATFORM_VGA_FRAME_H

#include "game/render.h"

enum {
    MYSMB_VGA_WIDTH = 320,
    MYSMB_VGA_HEIGHT = 200,
    MYSMB_VGA_PAGE_COUNT = 4,
    MYSMB_VGA_PAGE_SIZE = (MYSMB_VGA_WIDTH * MYSMB_VGA_HEIGHT) / MYSMB_VGA_PAGE_COUNT,
    MYSMB_VGA_COLOR_SKY = 1,
    MYSMB_VGA_COLOR_GROUND = 2,
    MYSMB_VGA_COLOR_BLOCK = 6,
    MYSMB_VGA_COLOR_PLAYER = 4,
    MYSMB_VGA_COLOR_ENEMY = 14
};

struct mysmb_vga_frame {
    mysmb_u8 *pages[MYSMB_VGA_PAGE_COUNT];
};

void mysmb_vga_frame_initialize(struct mysmb_vga_frame *vga_frame,
                                mysmb_u8 *page0, mysmb_u8 *page1,
                                mysmb_u8 *page2, mysmb_u8 *page3);
void mysmb_vga_frame_build(const struct mysmb_render_frame *render_frame,
                           struct mysmb_vga_frame *vga_frame);

#endif
