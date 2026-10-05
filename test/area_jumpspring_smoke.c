#include <string.h>
#include "core/area.h"

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 prg[256];
    static const mysmb_u16 fields[7] = {
        0x87U, 0x6eU, 0xcfU, 0x58U, 0x16U, 0xb6U, 0x0fU
    };
    mysmb_u8 row, column, scenario, slot, i, field, expected;
    for (row = 0U; row < 12U; ++row) {
        for (column = 0U; column < 16U; ++column) {
            for (scenario = 0U; scenario < 8U; ++scenario) {
                slot = scenario < 5U ? scenario : 5U;
                memset(prg, 0, sizeof(prg));
                prg[0x40U] = (mysmb_u8)((column << 4U) | row);
                prg[0x41U] = 11U;
                prg[0x42U] = 0xfdU;
                mysmb_game_initialize(&game);
                mysmb_game_bind_area_source(&game, prg, sizeof(prg));
                game.ram[0xe7U] = 0x40U;
                game.ram[0xe8U] = 0x80U;
                game.ram[0x725U] = 0xfeU;
                game.ram[0x726U] = column;
                game.ram[0x72aU] = 0xfeU;
                game.ram[0x730U] = 0xffU;
                game.ram[0x731U] = 0xffU;
                game.ram[0x732U] = 0xffU;
                for (i = 0U; i < 6U; ++i) {
                    for (field = 0U; field < 6U; ++field)
                        game.ram[fields[field] + i] = 0xa5U;
                    game.ram[0x0fU + i] = i < slot ? 1U : 0U;
                }
                if (scenario == 6U) game.ram[0x14U] = 1U;
                if (scenario == 7U) game.ram[0x14U] = 0xffU;
                memset(&game.ram[0x6a1U], 0xc1, 13U);
                if (!mysmb_area_process_object_state(&game)) return 1;
                if (game.ram[7U] != row) return 2;
                for (i = 0U; i < 6U; ++i) {
                    for (field = 0U; field < 7U; ++field) {
                        expected = 0xa5U;
                        if (field == 6U) expected = i < slot ? 1U : 0U;
                        if (i == slot) {
                            if (field == 0U) expected = (mysmb_u8)(column << 4U);
                            if (field == 1U) expected = 0xfeU;
                            if (field == 2U || field == 3U)
                                expected = (mysmb_u8)(row * 16U + 32U);
                            if (field == 4U) expected = 0x32U;
                            if (field == 5U) expected = 1U;
                            if (field == 6U) expected = scenario == 7U ? 0U :
                                (scenario == 6U ? 2U : 1U);
                        }
                        if (game.ram[fields[field] + i] != expected) return 3;
                    }
                }
                for (i = 0U; i < 13U; ++i) {
                    expected = i == row ? 0x67U : (i == row + 1U ? 0x68U : 0xc1U);
                    if (game.ram[0x6a1U + i] != expected) return 4;
                }
                if (game.ram[0x732U] != 0xffU) return 5;
            }
        }
    }
    return 0;
}
