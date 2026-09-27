#include <string.h>
#include "game/area.h"

static void setup(struct mysmb_game *game, mysmb_u8 *prg,
                  mysmb_u8 kind, mysmb_u8 type, mysmb_u8 cloud)
{
    memset(prg, 0, 256U);
    prg[0x40U] = 5U;
    prg[0x41U] = (mysmb_u8)((kind << 4U) | 2U);
    prg[0x42U] = 0xfdU;
    mysmb_game_initialize(game);
    mysmb_game_bind_area_source(game, prg, 256U);
    game->ram[0xe7U] = 0x40U;
    game->ram[0xe8U] = 0x80U;
    game->ram[0x725U] = 0U;
    game->ram[0x726U] = 0U;
    game->ram[0x728U] = 0U;
    game->ram[0x72aU] = 0U;
    game->ram[0x72bU] = 0U;
    game->ram[0x72cU] = 0U;
    game->ram[0x730U] = 0xffU;
    game->ram[0x731U] = 0xffU;
    game->ram[0x732U] = 0xffU;
    game->ram[0x74eU] = type;
    game->ram[0x743U] = cloud;
    memset(&game->ram[0x6a1U], 0, 13U);
}

int main(void)
{
    static const mysmb_u8 kinds[4] = {2U, 3U, 5U, 6U};
    static const mysmb_u8 bricks[4] = {0x22U, 0x51U, 0x52U, 0x52U};
    static const mysmb_u8 solids[4] = {0x69U, 0x61U, 0x61U, 0x62U};
    static mysmb_u8 prg[256];
    struct mysmb_game game;
    mysmb_u8 k, type, cloud, row, tile, extent, column;
    for (k = 0U; k < 4U; ++k) {
        for (type = 0U; type < 4U; ++type) {
            for (cloud = 0U; cloud < 2U; ++cloud) {
                setup(&game, prg, kinds[k], type, cloud);
                tile = (k == 0U || k == 2U) ? bricks[type] : solids[type];
                if (k == 0U && cloud != 0U) tile = 0x88U;
                extent = k < 2U ? 0U : 2U;
                if (!mysmb_area_process_object_state(&game)) return 1;
                if (game.ram[7U] != 5U || game.ram[0x735U] != 0U) return 2;
                for (row = 0U; row < 13U; ++row) {
                    if (game.ram[0x6a1U + row] !=
                        ((row >= 5U && row <= 5U + extent) ? tile : 0U)) return 3;
                }
                if (game.ram[0x732U] != (k < 2U ? 1U : 0xffU)) return 4;
                if (k >= 2U) continue;
                for (column = 1U; column < 4U; ++column) {
                    memset(&game.ram[0x6a1U], 0, 13U);
                    game.ram[0x726U] = column;
                    if (!mysmb_area_process_object_state(&game)) return 5;
                    if (game.ram[0x6a6U] != (column < 3U ? tile : 0U)) return 6;
                    if (game.ram[0x732U] != (column == 1U ? 0U : 0xffU)) return 7;
                }
            }
        }
    }
    return 0;
}
