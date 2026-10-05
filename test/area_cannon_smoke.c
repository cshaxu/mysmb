#include <string.h>
#include "core/area.h"

int main(void)
{
    static mysmb_u8 prg[256];
    static struct mysmb_game game;
    mysmb_u8 row, height, slot, i, last, expected;
    for (row = 0U; row < 12U; ++row) {
        for (height = 0U; height < 16U; ++height) {
            for (slot = 0U; slot < 6U; ++slot) {
                memset(prg, 0, sizeof(prg));
                prg[0x40U] = (mysmb_u8)(0xb0U | row);
                prg[0x41U] = (mysmb_u8)(0x10U | height);
                prg[0x42U] = 0xfdU;
                mysmb_game_initialize(&game);
                mysmb_game_bind_area_source(&game, prg, 256U);
                game.ram[0xe7U] = 0x40U;
                game.ram[0xe8U] = 0x80U;
                game.ram[0x725U] = 3U;
                game.ram[0x726U] = 11U;
                game.ram[0x72aU] = 3U;
                game.ram[0x730U] = 0xffU;
                game.ram[0x731U] = 0xffU;
                game.ram[0x732U] = 0xffU;
                game.ram[0x733U] = 2U;
                game.ram[0x735U] = 0x7eU;
                memset(&game.ram[0x46bU], 0x55, 24U);
                game.ram[0x46aU] = slot;
                memset(&game.ram[0x6a1U], 0, 16U);
                if (!mysmb_area_process_object_state(&game)) return 1;
                if (game.ram[7U] != row) return 2;
                if (game.ram[0x46aU] != (slot == 5U ? 0U : slot + 1U)) return 3;
                for (i = 0U; i < 6U; ++i) {
                    if (game.ram[0x46bU + i] != (i == slot ? 3U : 0x55U)) return 4;
                    if (game.ram[0x471U + i] != (i == slot ? 0xb0U : 0x55U)) return 5;
                    if (game.ram[0x477U + i] !=
                        (i == slot ? (mysmb_u8)(row * 16U + 32U) : 0x55U)) return 6;
                    if (game.ram[0x47dU + i] != 0x55U) return 7;
                }
                last = (mysmb_u8)(row + height);
                if (last > 12U) last = 12U;
                if (row == 11U && height >= 2U) last = 13U;
                for (i = 0U; i < 16U; ++i) {
                    expected = 0U;
                    if (i == row) expected = 0x64U;
                    else if (i > row && i <= last)
                        expected = i == row + 1U ? 0x65U : 0x66U;
                    if (game.ram[0x6a1U + i] != expected) return 8;
                }
                expected = height < 2U ? 0x7eU :
                    (mysmb_u8)(height - (last - row));
                if (game.ram[0x735U] != expected) return 9;
                if (game.ram[0x732U] != 0xffU) return 10;
            }
        }
    }
    return 0;
}
