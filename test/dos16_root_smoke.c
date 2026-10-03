#include "platform/dos16/dos16_root.h"

struct mysmb_dos16_test_host {
    mysmb_u8 buttons;
    mysmb_u8 vga_calls;
    mysmb_u8 text_calls;
};

static mysmb_u8 page0[MYSMB_VGA_PAGE_SIZE];
static mysmb_u8 page1[MYSMB_VGA_PAGE_SIZE];
static mysmb_u8 page2[MYSMB_VGA_PAGE_SIZE];
static mysmb_u8 page3[MYSMB_VGA_PAGE_SIZE];

static mysmb_u8 mysmb_dos16_test_read_buttons(void *context)
{
    return ((struct mysmb_dos16_test_host *)context)->buttons;
}

static void mysmb_dos16_test_present_vga(void *context,
                                         const struct mysmb_vga_frame *frame)
{
    struct mysmb_dos16_test_host *host;

    host = (struct mysmb_dos16_test_host *)context;
    if (frame->pages[0] != page0) host->vga_calls = 0xffU;
    else host->vga_calls++;
}

static void mysmb_dos16_test_present_text(void *context,
                                          const struct mysmb_text_frame *frame)
{
    struct mysmb_dos16_test_host *host;

    host = (struct mysmb_dos16_test_host *)context;
    if (frame->cells[0].color == 0U) host->text_calls = 0xffU;
    else host->text_calls++;
}

int main(void)
{
    struct mysmb_dos16_root root;
    struct mysmb_dos16_test_host host;
    struct mysmb_dos16_hooks hooks;
    mysmb_u8 text_mode;
    text_mode = 0U;
    if (mysmb_dos16_decode_bios_key(0x11U, 0U, &text_mode) != MYSMB_BUTTON_UP ||
        mysmb_dos16_decode_bios_key(0x1fU, 0U, &text_mode) != MYSMB_BUTTON_DOWN ||
        mysmb_dos16_decode_bios_key(0x1eU, 0U, &text_mode) != MYSMB_BUTTON_LEFT ||
        mysmb_dos16_decode_bios_key(0x20U, 0U, &text_mode) != MYSMB_BUTTON_RIGHT ||
        mysmb_dos16_decode_bios_key(0x24U, 0U, &text_mode) != MYSMB_BUTTON_B ||
        mysmb_dos16_decode_bios_key(0x25U, 0U, &text_mode) != MYSMB_BUTTON_A ||
        mysmb_dos16_decode_bios_key(0x1cU, 0U, &text_mode) != MYSMB_BUTTON_START ||
        mysmb_dos16_decode_bios_key(0U, 1U, &text_mode) != MYSMB_BUTTON_SELECT ||
        mysmb_dos16_decode_bios_key(0U, 2U, &text_mode) != MYSMB_BUTTON_SELECT ||
        mysmb_dos16_decode_bios_key(0x3bU, 0U, &text_mode) != 0U || text_mode != 1U) return 1;
    host.buttons = 0U;
    host.vga_calls = 0U;
    host.text_calls = 0U;
    hooks.context = &host;
    hooks.read_buttons = mysmb_dos16_test_read_buttons;
    hooks.present_vga = mysmb_dos16_test_present_vga;
    hooks.present_text = mysmb_dos16_test_present_text;
    mysmb_dos16_root_initialize(&root, &hooks, page0, page1, page2, page3);
    mysmb_dos16_root_step(&root);
    if (root.game.frame_number != 0UL || host.vga_calls != 0U || host.text_calls != 0U) return 1;
    mysmb_dos16_root_step(&root);
    if (root.game.frame_number != 0UL || host.vga_calls != 0U || host.text_calls != 0U) return 1;
    mysmb_dos16_root_step(&root);
    return root.game.frame_number == 1UL && host.vga_calls == 1U &&
           host.text_calls == 1U ? 0 : 1;
}
