#include "game/game.h"
#include "game/ppu_frame.h"

static mysmb_u8 chr[8192U];
int main(void)
{
    struct mysmb_game game;
    struct mysmb_ppu_frame frame;
    mysmb_u16 index;
    mysmb_game_initialize(&game);
    chr[16U] = 0x80U;
    chr[32U] = 0x80U;
    mysmb_game_bind_chr_source(&game, chr, 8192U);
    game.visible_ppu_control_0 = 0U;
    game.visible_ppu_mask = 0x1eU;
    game.visible_ppu_name_table = 1U;
    game.visible_scroll_x = 8U;
    game.palette[0U] = 0x21U;
    game.palette[1U] = 0x16U;
    game.palette[5U] = 0x29U;
    game.name_table[1][0U] = 2U;
    game.name_table[0][0U] = 1U;
    game.name_table[0][1U] = 2U;
    game.name_table[1][4U * 32U] = 1U;
    game.name_table[1][4U * 32U + 1U] = 2U;
    game.name_table[1][0x03c8U] = 1U;
    game.visible_sprite0_split = 1U;
    game.ram[0x0722U] = 0U;
    mysmb_ppu_frame_build(&game, &frame);
    if (frame.pixels[0U] != 0x16U) return 1;
    if (frame.pixels[32U * MYSMB_SCREEN_WIDTH] != 0x29U) return 2;
    /* The no-wait phase scrolls row zero, even if mode code has already
     * requested a split in the next frame's live RAM. */
    game.visible_sprite0_split = 0U;
    game.ram[0x0722U] = 1U;
    mysmb_ppu_frame_build(&game, &frame);
    if (frame.pixels[0U] != 0x21U) return 3;
    if (frame.pixels[32U * MYSMB_SCREEN_WIDTH] != 0x29U) return 4;
    /* Disabled source rendering must not expose the preparation tiles. */
    game.visible_ppu_mask = 0x06U;
    mysmb_ppu_frame_build(&game, &frame);
    for (index = 0U; index < MYSMB_SCREEN_WIDTH * MYSMB_SCREEN_HEIGHT; ++index)
        if (frame.pixels[index] != 0x21U) return 5;
    game.visible_ppu_mask = 0x08U;
    game.visible_scroll_x = 0U;
    game.visible_ppu_name_table = 0U;
    mysmb_ppu_frame_build(&game, &frame);
    if (frame.pixels[0U] != 0x21U || frame.pixels[8U] != 0x16U) return 6;
    game.visible_ppu_mask = 0x0aU;
    mysmb_ppu_frame_build(&game, &frame);
    if (frame.pixels[0U] != 0x16U) return 7;
    for (index = 0U; index < 256U; ++index) game.visible_oam[index] = 0xffU;
    game.visible_oam[0U] = 0U;
    game.visible_oam[1U] = 2U;
    game.visible_oam[2U] = 0U;
    game.visible_oam[3U] = 0U;
    game.palette[0x11U] = 0x2aU;
    game.visible_ppu_mask = 0x14U;
    mysmb_ppu_frame_build(&game, &frame);
    if (frame.pixels[MYSMB_SCREEN_WIDTH] != 0x2aU) return 8;
    game.visible_ppu_mask = 0x10U;
    mysmb_ppu_frame_build(&game, &frame);
    if (frame.pixels[MYSMB_SCREEN_WIDTH] != 0x21U) return 9;
    game.visible_oam[3U] = 8U;
    mysmb_ppu_frame_build(&game, &frame);
    if (frame.pixels[MYSMB_SCREEN_WIDTH + 8U] != 0x2aU) return 10;
    return 0;
}
