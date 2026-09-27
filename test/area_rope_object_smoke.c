#include <string.h>

#include "game/area.h"
#include "game/game.h"

static void mysmb_set_row_fifteen_object(struct mysmb_game *game,
                                         mysmb_u8 prg[0x100U],
                                         mysmb_u8 second)
{
    memset(prg, 0, 0x100U);
    prg[0x40U] = 0x0fU;
    prg[0x41U] = second;
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
}

int main(void)
{
    struct mysmb_game game;
    static mysmb_u8 prg[0x100U];
    mysmb_u8 row;

    /* EndlessRope: row-15 selector zero tail-enters DrawRope with X=0,
     * Y=15.  RenderUnderPart reaches the staging bottom and leaves its
     * decremented height in the shared RAM location. */
    mysmb_set_row_fifteen_object(&game, prg, 0x03U);
    if (mysmb_area_process_object_state(&game) == 0U) return 1;
    for (row = 0U; row != 13U; ++row)
        if (game.ram[0x06a1U + row] != 0x40U) return 2;
    if (game.ram[0x0732U] != 0xffU) return 3;
    if (game.ram[0x0735U] != 3U) return 4;

    /* BalancePlatRope: X is restored after blanking rows 1 through 12;
     * GetLrgObjAttrib then reloads the low nibble and DrawRope replaces
     * exactly that many top rows with rope. */
    mysmb_set_row_fifteen_object(&game, prg, 0x13U);
    if (mysmb_area_process_object_state(&game) == 0U) return 5;
    if (game.ram[0x06a1U] != 0U || game.ram[0x06a2U] != 0x40U ||
        game.ram[0x06a3U] != 0x40U || game.ram[0x06a4U] != 0x40U ||
        game.ram[0x06a5U] != 0x40U) return 6;
    for (row = 5U; row != 13U; ++row)
        if (game.ram[0x06a1U + row] != 0x44U) return 7;
    if (game.ram[0x0732U] != 0xffU) return 8;
    if (game.ram[0x0735U] != 0U) return 9;
    return 0;
}
