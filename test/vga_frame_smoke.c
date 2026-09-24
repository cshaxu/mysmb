#include "game/game.h"
#include "game/render.h"
#include "platform/vga/vga_frame.h"

static mysmb_u8 page0[MYSMB_VGA_PAGE_SIZE];
static mysmb_u8 page1[MYSMB_VGA_PAGE_SIZE];
static mysmb_u8 page2[MYSMB_VGA_PAGE_SIZE];
static mysmb_u8 page3[MYSMB_VGA_PAGE_SIZE];

static mysmb_u8 mysmb_vga_test_pixel(const struct mysmb_vga_frame *frame,
                                     mysmb_u16 offset)
{
    return frame->pages[offset / MYSMB_VGA_PAGE_SIZE][offset % MYSMB_VGA_PAGE_SIZE];
}

int main(void)
{
    struct mysmb_game game;
    struct mysmb_render_frame render_frame;
    struct mysmb_vga_frame vga_frame;

    mysmb_game_initialize(&game);
    game.name_table[0][0U] = 0x24U;
    game.name_table[0][31U] = 0x52U;
    game.name_table[0][32U] = 0x82U;
    game.ram[0x0770U] = 1U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00ceU] = 0xb0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 6U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x60U;
    game.ram[0x00cfU] = 0xb8U;
    mysmb_render_build(&game, &render_frame);
    mysmb_vga_frame_initialize(&vga_frame, page0, page1, page2, page3);
    mysmb_vga_frame_build(&render_frame, &vga_frame);
    if (mysmb_vga_test_pixel(&vga_frame, 0U) != MYSMB_VGA_COLOR_SKY ||
        mysmb_vga_test_pixel(&vga_frame, 319U) != MYSMB_VGA_COLOR_BLOCK ||
        mysmb_vga_test_pixel(&vga_frame, 7U * MYSMB_VGA_WIDTH) != MYSMB_VGA_COLOR_GROUND) return 1;
    if (mysmb_vga_test_pixel(&vga_frame, 146U * MYSMB_VGA_WIDTH + 80U) != MYSMB_VGA_COLOR_PLAYER ||
        mysmb_vga_test_pixel(&vga_frame, 153U * MYSMB_VGA_WIDTH + 120U) != MYSMB_VGA_COLOR_ENEMY) {
        return 1;
    }
    return 0;
}
