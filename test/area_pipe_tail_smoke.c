#include <string.h>
#include "game/area.h"

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 prg[128];
    static const mysmb_u8 backgrounds[6] = {0U, 0x17U, 0x1aU, 0xc0U, 0xc1U, 0x54U};
    unsigned int row, height, usage, side, variant, i, count;
    mysmb_u8 top, shaft, expected, stored_height;
    for (row = 0U; row < 12U; ++row)
    for (height = 0U; height < 8U; ++height)
    for (usage = 0U; usage < 2U; ++usage)
    for (side = 0U; side < 2U; ++side)
    for (variant = 0U; variant < 6U; ++variant) {
        mysmb_game_initialize(&game);
        memset(prg, 0xfd, sizeof(prg));
        prg[0x40U] = (mysmb_u8)(0x20U | row);
        prg[0x41U] = (mysmb_u8)(0x70U | (usage << 3U) | height);
        mysmb_game_bind_area_source(&game, prg, sizeof(prg));
        game.ram[0xe7U] = 0x40U;
        game.ram[0xe8U] = 0x80U;
        game.ram[0x726U] = 2U;
        game.ram[0x74eU] = 1U;
        game.ram[0x730U] = 0xffU;
        game.ram[0x731U] = 0xffU;
        game.ram[0x732U] = side == 0U ? 1U : 0U;
        game.ram[0x72fU] = 0U;
        game.ram[0x72cU] = 2U;
        game.ram[0x760U] = 0U;
        game.ram[0x75fU] = 0U;
        memset(&game.ram[0x6a1U], backgrounds[variant], 13U);
        if (!mysmb_area_process_object_state(&game)) return 1;
        top = (mysmb_u8)((usage ? 0x10U : 0x12U) + side);
        shaft = (mysmb_u8)(0x14U + side);
        count = height == 0U ? 1U : height;
        if (count > 12U - row) count = 12U - row;
        stored_height = height == 0U ? 255U : (mysmb_u8)(height - count);
        for (i = 0U; i < 13U; ++i) {
            expected = backgrounds[variant];
            if (i == row) expected = top;
            else if (i > row && i <= row + count && variant != 1U && variant != 2U && variant != 4U)
                expected = shaft;
            if (game.ram[0x6a1U + i] != expected) return 2;
        }
        if (game.ram[0x735U] != stored_height || game.ram[6U] != height || game.ram[7U] != row) return 3;
        if (game.ram[0x732U] != (side == 0U ? 0U : 255U)) return 4;
        if (game.ram[0xfU] != 0U) return 5;
    }
    return 0;
}
