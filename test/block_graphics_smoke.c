#include <string.h>

#include "game/area.h"
#include "game/game.h"
#include "smb1_local_rom.h"

static int verify_block(mysmb_u8 metatile, mysmb_u8 block_low)
{
    struct mysmb_game game;
    mysmb_u8 graphics_index;
    mysmb_u8 index;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    memset(&game.ram[0x0300U], 0, 0x40U);
    game.ram[0x03e4U] = 0x20U;
    game.ram[0x03e6U] = block_low;
    game.ram[0x03e8U] = metatile;
    game.ram[0x03ecU] = 1U;
    mysmb_area_apply_block_replacements(&game);
    if (game.ram[0x0300U] != 10U || game.ram[0x03ecU] != 0U) return 1;
    if (metatile == 0U) graphics_index = 3U;
    else if (metatile == 0x58U || metatile == 0x51U) graphics_index = 0U;
    else if (metatile == 0x5dU || metatile == 0x52U) graphics_index = 1U;
    else graphics_index = 2U;
    for (index = 0U; index < 4U; ++index) {
        mysmb_u8 command_offset = index < 2U ? (mysmb_u8)(3U + index) :
            (mysmb_u8)(8U + index - 2U);
        if (game.ram[0x0301U + command_offset] !=
            mysmb_local_prg[0x0a39U + (mysmb_u16)graphics_index * 4U + index]) return 1;
    }
    if (game.ram[0x0301U] != (block_low < 0xd0U ? 0x21U : 0x25U)) return 1;
    return 0;
}

int main(void)
{
    int result;

    result = verify_block(0x51U, 0x04U);
    if (result != 0) return result;
    result = verify_block(0x52U, 0xd2U);
    if (result != 0) return result;
    result = verify_block(0x61U, 0x04U);
    if (result != 0) return result;
    return verify_block(0U, 0xd2U);
}
