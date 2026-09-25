#include "platform/vga/vga_frame.h"

static mysmb_u8 mysmb_vga_dac_index(mysmb_u8 nes_color)
{
    if (nes_color == 0x21U || nes_color == 0x31U) return 1U;
    if (nes_color == 0x16U || nes_color == 0x26U) return 4U;
    if (nes_color == 0x19U || nes_color == 0x29U) return 2U;
    if (nes_color == 0x27U || nes_color == 0x37U) return 6U;
    return 15U;
}
static void mysmb_vga_set_pixel(struct mysmb_vga_frame *frame, mysmb_u16 offset, mysmb_u8 color)
{ frame->pages[offset / MYSMB_VGA_PAGE_SIZE][offset % MYSMB_VGA_PAGE_SIZE] = color; }
void mysmb_vga_frame_initialize(struct mysmb_vga_frame *frame, mysmb_u8 MYSMB_VGA_FAR *page0, mysmb_u8 MYSMB_VGA_FAR *page1, mysmb_u8 MYSMB_VGA_FAR *page2, mysmb_u8 MYSMB_VGA_FAR *page3)
{ frame->pages[0] = page0; frame->pages[1] = page1; frame->pages[2] = page2; frame->pages[3] = page3; }
void mysmb_vga_frame_build(const struct mysmb_ppu_frame *ppu_frame, struct mysmb_vga_frame *frame)
{
    mysmb_u16 row; mysmb_u16 column; mysmb_u16 source_x; mysmb_u16 source_y;
    for (row = 0U; row < MYSMB_VGA_HEIGHT; ++row) {
        source_y = (mysmb_u16)(row * MYSMB_SCREEN_HEIGHT / MYSMB_VGA_HEIGHT);
        for (column = 0U; column < MYSMB_VGA_WIDTH; ++column) {
            source_x = (mysmb_u16)(column * MYSMB_SCREEN_WIDTH / MYSMB_VGA_WIDTH);
            mysmb_vga_set_pixel(frame, row * MYSMB_VGA_WIDTH + column,
                mysmb_vga_dac_index(ppu_frame->pixels[source_y * MYSMB_SCREEN_WIDTH + source_x]));
        }
    }
}