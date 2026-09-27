#include <string.h>
#include "game/area.h"

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 prg[256];
    static const mysmb_u8 backgrounds[8] = {
        0U, 0x17U, 0x1aU, 0xc0U, 0xc1U, 0x54U, 0x50U, 0x61U
    };
    mysmb_u8 length, variant, column, row, top, expected;
    for (length = 0U; length < 9U; ++length) {
        for (variant = 0U; variant < 8U; ++variant) {
            memset(prg, 0, sizeof(prg));
            prg[0x40U] = 0x0fU;
            prg[0x41U] = (mysmb_u8)(0x30U | length);
            prg[0x42U] = 0xfdU;
            mysmb_game_initialize(&game);
            mysmb_game_bind_area_source(&game, prg, sizeof(prg));
            game.ram[0xe7U] = 0x40U;
            game.ram[0xe8U] = 0x80U;
            game.ram[0x730U] = 0xffU;
            game.ram[0x731U] = 0xffU;
            game.ram[0x732U] = 0xffU;
            game.ram[0x734U] = 0xa5U;
            for (column = 0U; column <= length + 1U; ++column) {
                memset(&game.ram[0x6a1U], backgrounds[variant], 13U);
                game.ram[0x726U] = column;
                game.ram[0x735U] = 0xa5U;
                game.ram[7U] = 0xa5U;
                if (!mysmb_area_process_object_state(&game)) return 1;
                if (column <= length) {
                    if (game.ram[0x734U] != 8U - column) return 2;
                    if (game.ram[7U] != 15U || game.ram[0x735U] != 0U) return 3;
                    if (game.ram[0x732U] !=
                        (column == length ? 0xffU : length - column - 1U)) return 4;
                } else {
                    if (game.ram[0x734U] != 8U - length) return 5;
                    if (game.ram[0x735U] != 0xa5U) return 6;
                }
                top = column < 8U ? (mysmb_u8)(10U - column) : 3U;
                for (row = 0U; row < 13U; ++row) {
                    expected = backgrounds[variant];
                    if (column <= length && row >= top && row <= 10U &&
                        variant != 1U && variant != 2U && variant != 4U)
                        expected = 0x61U;
                    if (game.ram[0x6a1U + row] != expected) return 7;
                }
            }
        }
    }
    return 0;
}
