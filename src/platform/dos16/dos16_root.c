#include "platform/dos16/dos16_root.h"
#ifdef MYSMB_DOS16_TARGET
#include <malloc.h>
static mysmb_u8 MYSMB_VGA_FAR *mysmb_dos16_ppu_pixels;
#endif

mysmb_u8 mysmb_dos16_decode_bios_key(mysmb_u8 scan_code, mysmb_u8 shift_status, mysmb_u8 *text_mode)
{
    mysmb_u8 buttons;
    buttons = (shift_status & 3U) != 0U ? MYSMB_BUTTON_SELECT : 0U;
    switch (scan_code) {
    case 0x3bU: if (text_mode != 0) *text_mode = *text_mode == 0U ? 1U : 0U; break;
    case 0x1eU: case 0x4bU: buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_LEFT); break;
    case 0x20U: case 0x4dU: buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_RIGHT); break;
    case 0x1fU: case 0x50U: buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_DOWN); break;
    case 0x11U: case 0x48U: buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_UP); break;
    case 0x1cU: buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_START); break;
    case 0x24U: buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_B); break;
    case 0x25U: buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_A); break;
    default: break;
    }
    return buttons;
}

static void mysmb_dos16_compose_and_present(struct mysmb_dos16_root *root)
{
    mysmb_ppu_frame_build(&root->game, &root->ppu_frame);
    mysmb_text_frame_build(&root->ppu_frame, &root->text_frame);
    mysmb_vga_frame_build(&root->ppu_frame, &root->vga_frame);
}

void mysmb_dos16_root_initialize(struct mysmb_dos16_root *root, const struct mysmb_dos16_hooks *hooks, mysmb_u8 MYSMB_VGA_FAR *page0, mysmb_u8 MYSMB_VGA_FAR *page1, mysmb_u8 MYSMB_VGA_FAR *page2, mysmb_u8 MYSMB_VGA_FAR *page3)
{
#ifdef MYSMB_DOS16_TARGET
    if (mysmb_dos16_ppu_pixels == 0) {
        mysmb_dos16_ppu_pixels = (mysmb_u8 MYSMB_VGA_FAR *)_fmalloc(
            MYSMB_SCREEN_WIDTH * MYSMB_SCREEN_HEIGHT);
    }
    mysmb_ppu_frame_bind_pixels(&root->ppu_frame, mysmb_dos16_ppu_pixels);
#endif
    root->hooks = *hooks;
    mysmb_game_power_on(&root->game);
    mysmb_game_frame_initialize(&root->game_frame);
    mysmb_vga_frame_initialize(&root->vga_frame, page0, page1, page2, page3);
}

void mysmb_dos16_root_step(struct mysmb_dos16_root *root)
{
    struct mysmb_input input;

    if (mysmb_game_startup_step(&root->game, 1U) == 0U) return;
    input.buttons = root->hooks.read_buttons(root->hooks.context);
    input.buttons2 = 0U;
    mysmb_game_tick(&root->game, &input, &root->game_frame);
    mysmb_dos16_compose_and_present(root);
    root->hooks.present_vga(root->hooks.context, &root->vga_frame);
    root->hooks.present_text(root->hooks.context, &root->text_frame);
}
