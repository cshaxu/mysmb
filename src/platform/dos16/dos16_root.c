#include "platform/dos16/dos16_root.h"

void mysmb_dos16_root_initialize(struct mysmb_dos16_root *root,
                                 const struct mysmb_dos16_hooks *hooks,
                                 mysmb_u8 *vga_page0, mysmb_u8 *vga_page1,
                                 mysmb_u8 *vga_page2, mysmb_u8 *vga_page3)
{
    mysmb_game_initialize(&root->game);
    root->game_frame.sprite0_x = 0U;
    root->game_frame.sprite0_y = 0U;
    root->game_frame.start_pressed = 0U;
    root->game_frame.operating_mode = 0U;
    root->game_frame.operating_mode_task = 0U;
    root->hooks = *hooks;
    mysmb_vga_frame_initialize(&root->vga_frame, vga_page0, vga_page1,
                               vga_page2, vga_page3);
    mysmb_render_build(&root->game, &root->render_frame);
    mysmb_text_frame_build(&root->render_frame, &root->text_frame);
    mysmb_vga_frame_build(&root->render_frame, &root->vga_frame);
}

void mysmb_dos16_root_step(struct mysmb_dos16_root *root)
{
    struct mysmb_input input;

    input.buttons = root->hooks.read_buttons(root->hooks.context);
    mysmb_game_tick(&root->game, &input, &root->game_frame);
    mysmb_render_build(&root->game, &root->render_frame);
    mysmb_text_frame_build(&root->render_frame, &root->text_frame);
    mysmb_vga_frame_build(&root->render_frame, &root->vga_frame);
    root->hooks.present_vga(root->hooks.context, &root->vga_frame);
    root->hooks.present_text(root->hooks.context, &root->text_frame);
}
