#include <string.h>

#include "game/area.h"
#include "game/game.h"

static void mysmb_set_object(struct mysmb_game *game, mysmb_u8 prg[0x100U],
                             mysmb_u8 first, mysmb_u8 second)
{
    memset(prg, 0, 0x100U);
    prg[0x40U] = first;
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
    mysmb_u8 column;

    /* Row 13 selector 2: AxeObj writes control eight, falls through to
     * ChainObj, selects C_Object[0], and ColObj emits one metatile at row 6. */
    mysmb_set_object(&game, prg, 0x0dU, 0x42U);
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x0773U] != 8U || game.ram[0x06a7U] != 0xc5U ||
        game.ram[0x0732U] != 0xffU) return 1;

    /* Selector 3 enters ChainObj directly and selects index one. */
    mysmb_set_object(&game, prg, 0x0dU, 0x43U);
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a8U] != 0x0cU || game.ram[0x0732U] != 0xffU) return 2;

    /* Selector 4 initializes CastleBridgeObj's fixed length 12, then uses
     * the third table entry; ProcessAreaData subsequently decrements it. */
    mysmb_set_object(&game, prg, 0x0dU, 0x44U);
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a9U] != 0x89U || game.ram[0x0732U] != 11U) return 3;
    for (column = 1U; column <= 12U; ++column) {
        game.ram[0x0726U] = column;
        memset(&game.ram[0x06a1U], 0, 13U);
        if (mysmb_area_process_object_state(&game) == 0U ||
            game.ram[0x06a9U] != 0x89U ||
            game.ram[0x0732U] != (mysmb_u8)(11U - column)) return 5;
    }
    game.ram[0x0726U] = 13U;
    memset(&game.ram[0x06a1U], 0, 13U);
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a9U] != 0U) return 6;

    /* Normal small-object selector 10 reaches EmptyBlock.  Its decoded row
     * is the GetLrgObjAttrib result supplied to the shared ColObj tail. */
    mysmb_set_object(&game, prg, 0x05U, 0x0aU);
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a6U] != 0xc4U || game.ram[0x0732U] != 0xffU ||
        game.ram[0x0007U] != 5U || game.ram[0x0735U] != 0U) return 4;
    /* ColObj must use RenderUnderPart's overwrite rules. */
    mysmb_set_object(&game, prg, 0x05U, 0x0aU);
    game.ram[0x06a6U] = 0xc1U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a6U] != 0xc1U) return 7;
    mysmb_set_object(&game, prg, 0x05U, 0x0aU);
    game.ram[0x06a6U] = 0xc0U;
    if (mysmb_area_process_object_state(&game) == 0U ||
        game.ram[0x06a6U] != 0xc4U) return 8;

    /* FlagpoleObject only directly stores its ball and base.  Its shaft
     * tail-calls RenderUnderPart, so an existing protected foreground tile
     * survives while $c0 is replaced and the helper leaves height zero. */
    mysmb_set_object(&game, prg, 0x0dU, 0x41U);
    game.ram[0x06a2U] = 0xc1U;
    game.ram[0x06a3U] = 0xc0U;
    if (mysmb_area_process_object_state(&game) == 0U) return 9;
    if (game.ram[0x06a1U] != 0x24U) return 10;
    if (game.ram[0x06a2U] != 0xc1U) return 11;
    if (game.ram[0x06a3U] != 0x25U) return 12;
    if (game.ram[0x06abU] != 0x61U) return 13;
    if (game.ram[0x0735U] != 0U) return 14;
    if (game.ram[0x001bU] != 48U) return 15;
    if (game.ram[0x008cU] != 0xf8U) return 16;
    if (game.ram[0x0073U] != 0xffU) return 17;
    if (game.ram[0x00d4U] != 0x30U) return 18;
    if (game.ram[0x010dU] != 0xb0U) return 19;
    if (game.ram[0x0014U] != 1U) return 20;
    return 0;
}
