#include "platform/dos16/dos16_root.h"
#ifdef MYSMB_DOS16_TARGET
#include <malloc.h>
#endif
int mysmb_dos16_root_initialize(struct mysmb_dos16_root *root,
                                const struct mysmb_dos16_hooks *hooks)
{
#ifdef MYSMB_DOS16_TARGET
    mysmb_u8 __far *pixels;
#endif
    root->initialized=0U;
    if (hooks==0 || hooks->read_input==0 || hooks->present_video==0) return 0;
#ifdef MYSMB_DOS16_TARGET
    pixels=(mysmb_u8 __far *)_fmalloc(MYSMB_IO_VIDEO_PIXELS);
    if (pixels==0) return 0;
    mysmb_ppu_frame_bind_pixels(&root->ppu_frame,pixels);
#endif
    root->hooks=*hooks;
    mysmb_game_power_on(&root->game);
    mysmb_game_frame_initialize(&root->game_frame);
    root->initialized=1U;
    return 1;
}
void mysmb_dos16_root_step(struct mysmb_dos16_root *root)
{
    struct mysmb_io_input decoded;
    struct mysmb_input input;
    struct mysmb_io_video_frame video;
    if (root->initialized==0U) return;
    if (mysmb_game_startup_step(&root->game,1U)==0U) return;
    root->hooks.read_input(root->hooks.context,&decoded);
    mysmb_game_io_input(&decoded,&input);
    mysmb_game_tick(&root->game,&input,&root->game_frame);
    mysmb_ppu_frame_build(&root->game,&root->ppu_frame);
    mysmb_game_io_video(&root->ppu_frame,&video);
    root->hooks.present_video(root->hooks.context,&video);
}
void mysmb_dos16_root_shutdown(struct mysmb_dos16_root *root)
{
    if (root->initialized==0U) return;
#ifdef MYSMB_DOS16_TARGET
    _ffree(root->ppu_frame.pixels);
    root->ppu_frame.pixels=0;
#endif
    root->initialized=0U;
}
