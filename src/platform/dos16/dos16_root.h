#ifndef MYSMB_PLATFORM_DOS16_ROOT_H
#define MYSMB_PLATFORM_DOS16_ROOT_H

#include "game/game.h"
#include "game/render.h"
#include "platform/text/text_frame.h"
#include "platform/vga/vga_frame.h"

struct mysmb_dos16_hooks {
    void *context;
    mysmb_u8 (*read_buttons)(void *context);
    void (*present_vga)(void *context, const struct mysmb_vga_frame *frame);
    void (*present_text)(void *context, const struct mysmb_text_frame *frame);
};

struct mysmb_dos16_root {
    struct mysmb_game game;
    struct mysmb_frame game_frame;
    struct mysmb_render_frame render_frame;
    struct mysmb_text_frame text_frame;
    struct mysmb_vga_frame vga_frame;
    struct mysmb_dos16_hooks hooks;
};

/* BIOS scan-code decoder shared by the real DOS root and ROM-free tests. */
mysmb_u8 mysmb_dos16_decode_bios_key(mysmb_u8 scan_code,
                                      mysmb_u8 shift_status,
                                      mysmb_u8 *text_mode);

void mysmb_dos16_root_initialize(struct mysmb_dos16_root *root,
                                 const struct mysmb_dos16_hooks *hooks,
                                 mysmb_u8 MYSMB_VGA_FAR *vga_page0,
                                 mysmb_u8 MYSMB_VGA_FAR *vga_page1,
                                 mysmb_u8 MYSMB_VGA_FAR *vga_page2,
                                 mysmb_u8 MYSMB_VGA_FAR *vga_page3);
void mysmb_dos16_root_step(struct mysmb_dos16_root *root);

#endif
