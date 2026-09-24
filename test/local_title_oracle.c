#include <stdio.h>

#include "game/game.h"
#include "game/area.h"
#include "smb1_local_rom.h"
#include "smb1_local_title.h"

static mysmb_u32 fnv1a(const mysmb_u8 *bytes, mysmb_u16 count,
                       mysmb_u32 value)
{
    mysmb_u16 index;

    for (index = 0U; index < count; ++index) {
        value ^= (mysmb_u32)bytes[index];
        value *= 16777619UL;
    }
    return value;
}

int main(void)
{
    struct mysmb_game game;
    mysmb_u32 hash;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    if (mysmb_game_apply_title_commands(&game, mysmb_local_title_data,
                                        MYSMB_LOCAL_TITLE_DATA_SIZE) == 0U) {
        return 1;
    }
    if (mysmb_game_apply_vram_commands(&game, mysmb_local_title_icon_data,
                                       MYSMB_LOCAL_TITLE_ICON_DATA_SIZE) == 0U) {
        return 1;
    }
    hash = fnv1a(game.name_table[0], 0x0400U, 2166136261UL);
    hash = fnv1a(game.name_table[1], 0x0400U, hash);
    printf("native_ciram_fnv1a=%08lx\n", hash);
    hash = fnv1a(game.palette, 0x20U, 2166136261UL);
    printf("native_palette_fnv1a=%08lx\n", hash);
    return hash == 0xacd0d644UL ? 0 : 1;
}
