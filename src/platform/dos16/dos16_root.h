#ifndef MYSMB_PLATFORM_DOS16_ROOT_H
#define MYSMB_PLATFORM_DOS16_ROOT_H
#include "app/game_io.h"
/* Composition root: device consumers receive only neutral IO views. */
struct mysmb_dos16_hooks {
    void *context;
    void (*read_input)(void *context, struct mysmb_io_input *input);
    void (*present_video)(void *context, const struct mysmb_io_video_frame *frame);
};
struct mysmb_dos16_root {
    struct mysmb_game game;
    struct mysmb_frame game_frame;
    struct mysmb_ppu_frame ppu_frame;
    struct mysmb_dos16_hooks hooks;
    mysmb_io_u8 initialized;
};
int mysmb_dos16_root_initialize(struct mysmb_dos16_root *root,
                                const struct mysmb_dos16_hooks *hooks);
void mysmb_dos16_root_step(struct mysmb_dos16_root *root);
void mysmb_dos16_root_shutdown(struct mysmb_dos16_root *root);
#endif
