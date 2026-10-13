#include <string.h>

#include "core/area.h"
#include "core/game.h"

static void mysmb_set_coin_row(struct mysmb_game *game, mysmb_u8 prg[0x100U],
                               mysmb_u8 area_type)
{
    memset(prg, 0, 0x100U);
    /* Row five, normal-object selector four, source length three. */
    prg[0x40U] = 0x05U;
    prg[0x41U] = 0x43U;
    prg[0x42U] = 0xfdU;
    mysmb_game_initialize(game);
    mysmb_game_bind_area_source(game, prg, 0x100U);
    game->ram[0x00e7U] = 0x40U;
    game->ram[0x00e8U] = 0x80U;
    game->ram[0x0725U] = 0U;
    game->ram[0x0726U] = 0U;
    game->ram[0x072aU] = 0U;
    game->ram[0x072bU] = 0U;
    game->ram[0x072cU] = 0U;
    game->ram[0x0730U] = 0xffU;
    game->ram[0x0731U] = 0xffU;
    game->ram[0x0732U] = 0xffU;
    game->ram[0x074eU] = area_type;
}

int main(void)
{
    static const mysmb_u8 expected[4] = { 0xc3U, 0xc2U, 0xc2U, 0xc2U };
    struct mysmb_game game;
    static mysmb_u8 prg[0x100U];
    mysmb_u8 area_type;

    for (area_type = 0U; area_type != 4U; ++area_type) {
        mysmb_set_coin_row(&game, prg, area_type);
        if (mysmb_area_process_object_state(&game) == 0U) return 1;
        if (game.ram[0x06a6U] != expected[area_type]) return 2;
        /* GetRow initializes the low-nibble length, and ProcessAreaData's
         * post-handler ChkLength decrement owns the resulting value. */
        if (game.ram[0x0732U] != 2U || game.ram[0x0735U] != 0U) return 3;
    }
    return 0;
}
