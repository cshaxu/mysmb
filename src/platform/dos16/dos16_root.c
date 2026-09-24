#include "platform/dos16/dos16_root.h"

/* INT 16h function 2 reports bit 0 for right Shift and bit 1 for left Shift.
 * The ordinary scan codes are invariant across DOS keyboard layouts and RDP
 * BIOS forwarding. */
mysmb_u8 mysmb_dos16_decode_bios_key(mysmb_u8 scan_code,
                                      mysmb_u8 shift_status,
                                      mysmb_u8 *text_mode)
{
    mysmb_u8 buttons;

    buttons = (shift_status & 3U) != 0U ? MYSMB_BUTTON_SELECT : 0U;
    switch (scan_code) {
    case 0x3bU:
        if (text_mode != 0) *text_mode = *text_mode == 0U ? 1U : 0U;
        break;
    case 0x1eU: case 0x4bU: buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_LEFT); break;
    case 0x20U: case 0x4dU: buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_RIGHT); break;
    case 0x1fU: case 0x50U: buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_DOWN); break;
    case 0x11U: case 0x48U: buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_UP); break;
    case 0x1cU: buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_START); break;
    case 0x24U: case 0x2cU: buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_A); break;
    case 0x25U: case 0x2dU: buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_B); break;
    default: break;
    }
    return buttons;
}

void mysmb_dos16_root_initialize(struct mysmb_dos16_root *root,
                                 const struct mysmb_dos16_hooks *hooks,
                                 mysmb_u8 MYSMB_VGA_FAR *vga_page0,
                                 mysmb_u8 MYSMB_VGA_FAR *vga_page1,
                                 mysmb_u8 MYSMB_VGA_FAR *vga_page2,
                                 mysmb_u8 MYSMB_VGA_FAR *vga_page3)
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
