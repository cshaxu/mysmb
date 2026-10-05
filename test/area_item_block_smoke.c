#include <string.h>
#include "core/area.h"

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 prg[256];
    static const mysmb_u8 tiles[14] = {
        0xc1U, 0xc0U, 0x5fU, 0x60U, 0x55U, 0x56U, 0x57U,
        0x58U, 0x59U, 0x5aU, 0x5bU, 0x5cU, 0x5dU, 0x5eU
    };
    static const mysmb_u8 background[8] = {
        0U, 0x17U, 0x1aU, 0xc0U, 0xc1U, 0x54U, 0x50U, 0x61U
    };
    mysmb_u8 selector, type, hidden, variant, edge, row, i, index, tile, enabled;
    for (selector = 0U; selector < 9U; ++selector)
    for (type = 0U; type < 4U; ++type)
    for (hidden = 0U; hidden < 2U; ++hidden)
    for (variant = 0U; variant < 8U; ++variant)
    for (edge = 0U; edge < 2U; ++edge) {
        row = edge == 0U ? 0U : 11U;
        memset(prg, 0, sizeof(prg));
        prg[0x40U] = row;
        prg[0x41U] = selector;
        prg[0x42U] = 0xfdU;
        mysmb_game_initialize(&game);
        mysmb_game_bind_area_source(&game, prg, sizeof(prg));
        game.ram[0xe7U] = 0x40U;
        game.ram[0xe8U] = 0x80U;
        game.ram[0x730U] = 0xffU;
        game.ram[0x731U] = 0xffU;
        game.ram[0x732U] = 0xffU;
        game.ram[0x74eU] = type;
        game.ram[0x75dU] = hidden;
        game.ram[0x6bcU] = 0xa5U;
        game.ram[0x735U] = 0xa5U;
        memset(&game.ram[0x6a1U], background[variant], 13U);
        if (!mysmb_area_process_object_state(&game)) return 1;
        enabled = selector != 3U || hidden != 0U;
        index = selector;
        if (selector >= 3U && type != 1U) index += 5U;
        tile = background[variant];
        if (enabled && variant != 1U && variant != 2U && variant != 4U)
            tile = tiles[index];
        for (i = 0U; i < 13U; ++i)
            if (game.ram[0x6a1U + i] != (i == row ? tile : background[variant])) return 2;
        if (game.ram[0x75dU] != (selector == 3U ? 0U : hidden)) return 3;
        if (game.ram[0x6bcU] != (selector == 7U ? 0U : 0xa5U)) return 4;
        if (game.ram[0x735U] != (enabled ? 0U : 0xa5U)) return 5;
        if (game.ram[7U] != (enabled ? row : 0x16U)) return 6;
        if (game.ram[0x732U] != 0xffU) return 7;
    }
    return 0;
}
