#include "game/game.h"
#include "game/area.h"
#include "smb1_local_rom.h"
#include "smb1_local_title.h"

static unsigned long mysmb_title_table_hash(const struct mysmb_game *game)
{
    unsigned short index;
    unsigned long value;

    value = 2166136261UL;
    for (index = 0U; index < 0x0400U; ++index) {
        value ^= (unsigned long)game->name_table[0][index];
        value *= 16777619UL;
    }
    return value;
}

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    unsigned short index;
    unsigned char saw_title_transfer;
    unsigned char saw_icon_queue;
    unsigned char saw_title_palette_queue;
    unsigned char saw_menu_game_core;
    unsigned char saw_primary_setup;
    unsigned short menu_frame;
    unsigned long title_hash;

    mysmb_game_initialize(&game);
    game.ram[0x07d7U] = 0U;
    game.ram[0x07d8U] = 1U;
    game.ram[0x07d9U] = 2U;
    game.ram[0x07daU] = 3U;
    game.ram[0x07dbU] = 4U;
    game.ram[0x07dcU] = 5U;
    if (mysmb_area_queue_title_score(&game) == 0U ||
        game.ram[0x0300U] != 9U || game.ram[0x0301U] != 0x22U ||
        game.ram[0x0302U] != 0xf0U || game.ram[0x0303U] != 6U ||
        game.ram[0x0304U] != 0x24U || game.ram[0x0309U] != 5U ||
        game.ram[0x030aU] != 0U) return 1;
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_title_source(&game, mysmb_local_title_data,
                                 MYSMB_LOCAL_TITLE_DATA_SIZE,
                                 mysmb_local_title_icon_data,
                                 MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
    if (mysmb_game_begin_title_bootstrap(&game) == 0U) return 1;
    if (game.ram[0x00fbU] != 0x80U) return 1;
    input.buttons = 0U;
    saw_title_transfer = 0U;
    saw_icon_queue = 0U;
    saw_title_palette_queue = 0U;
    saw_menu_game_core = 0U;
    saw_primary_setup = 0U;
    menu_frame = 0xffffU;
    title_hash = 0UL;
    for (index = 0U; index < 80U; ++index) {
        if (game.ram[0x0773U] == 5U) title_hash = mysmb_title_table_hash(&game);
        if (game.ram[0x0300U] == 7U) saw_icon_queue = 1U;
        mysmb_game_tick(&game, &input, &frame);
        if (menu_frame == 0xffffU && game.ram[0x0770U] == 0U &&
            game.ram[0x0772U] == 3U) menu_frame = index;
        if (game.ram[0x0770U] == 0U && game.ram[0x0772U] == 3U &&
            game.ram[0x000eU] != 0U) saw_menu_game_core = 1U;
        if (game.ram[0x0770U] == 0U && game.ram[0x0772U] == 3U &&
            game.ram[0x0754U] == 1U && game.ram[0x0756U] == 0U && game.ram[0x075aU] == 2U &&
            game.ram[0x0761U] == 2U) saw_primary_setup = 1U;
        if (game.ram[0x073cU] == 11U && game.ram[0x0300U] == 7U &&
            game.ram[0x0301U] == 0x3fU && game.ram[0x0302U] == 0x10U &&
            game.ram[0x0304U] == 0x22U) saw_title_palette_queue = 1U;
        if (title_hash != 0UL && mysmb_title_table_hash(&game) != title_hash)
            saw_title_transfer = 1U;
    }
    if (game.ram[0x0770U] != 0U || game.ram[0x0772U] != 3U) return 1;
    if (menu_frame >= 40U) return 1;
    if (game.ram[0x073cU] != 14U) return 1;
    if (saw_title_transfer == 0U || saw_icon_queue == 0U ||
        saw_menu_game_core == 0U || saw_primary_setup == 0U ||
        saw_title_palette_queue == 0U) return 1;
    return 0;
}
