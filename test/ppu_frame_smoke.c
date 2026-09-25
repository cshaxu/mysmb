#include "game/game.h"
#include "game/ppu_frame.h"

static mysmb_u8 chr[8192U];
int main(void)
{
    struct mysmb_game game;
    struct mysmb_ppu_frame frame;
    mysmb_game_initialize(&game);
    chr[16U] = 0x80U;
    chr[32U] = 0x80U;
    mysmb_game_bind_chr_source(&game, chr, 8192U);
    game.visible_ppu_control_0 = 0U;
    game.visible_ppu_name_table = 0U;
    game.visible_scroll_x = 8U;
    game.palette[0U] = 0x21U;
    game.palette[1U] = 0x16U;
    game.palette[5U] = 0x29U;
    game.name_table[0][0U] = 1U;
    game.name_table[0][1U] = 2U;
    game.name_table[0][4U * 32U] = 1U;
    game.name_table[0][4U * 32U + 1U] = 2U;
    game.name_table[0][0x03c8U] = 1U;
    mysmb_ppu_frame_build(&game, &frame);
    if (frame.pixels[0U] != 0x16U) return 1;
    if (frame.pixels[32U * MYSMB_SCREEN_WIDTH] != 0x29U) return 2;
    return 0;
}