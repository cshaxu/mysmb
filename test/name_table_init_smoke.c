#include "core/game.h"

int main(void)
{
    struct mysmb_game game;
    mysmb_u8 table;
    mysmb_u16 offset;

    mysmb_game_initialize(&game);
    game.ram[0x0778U] = 0xb3U;
    for (table = 0U; table < 2U; ++table)
        for (offset = 0U; offset < 0x0400U; ++offset)
            game.ppu.name_table[table][offset] = 0x7eU;
    game.ram[0x0300U] = 0x55U;
    game.ram[0x0301U] = 0x66U;
    game.ram[0x073fU] = 0x77U;
    game.ram[0x0740U] = 0x88U;
    mysmb_game_initialize_name_tables(&game);
    if (game.ram[0x0778U] != 0xb0U || game.ppu.ppu_control_0 != 0xb0U ||
        game.ppu.visible_ppu_control_0 != 0xb0U || game.ppu.ppu_name_table != 0U ||
        game.ppu.scroll_x != 0U || game.ppu.scroll_y != 0U ||
        game.ppu.visible_scroll_x != 0U || game.ppu.visible_scroll_y != 0U ||
        game.ram[0x0300U] != 0U || game.ram[0x0301U] != 0U) return 1;
    for (table = 0U; table < 2U; ++table) {
        for (offset = 0U; offset < 0x03c0U; ++offset)
            if (game.ppu.name_table[table][offset] != 0x24U) return 1;
        for (offset = 0x03c0U; offset < 0x0400U; ++offset)
            if (game.ppu.name_table[table][offset] != 0U) return 1;
    }
    return 0;
}
