#include "core/game.h"
#include "game/objects.h"

#include <string.h>

int main(void)
{
    struct mysmb_game game;

    memset(&game, 0, sizeof(game));
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 53U;
    game.ram[0x006eU] = 1U;
    game.ram[0x0087U] = 0x70U;
    game.ram[0x00cfU] = 0xb8U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x071cU] = 0x20U;
    game.ram[0x071aU] = 1U;
    game.ram[0x071dU] = 0x20U;
    game.ram[0x071bU] = 2U;
    game.ram[0x06e5U] = 0x40U;
    game.ram[0x03c5U] = 0x20U;

    mysmb_objects_draw_retainer(&game, 0U);
    if (game.ram[0x0240U] != 0xb8U || game.ram[0x0241U] != 0xcdU ||
        game.ram[0x0245U] != 0xcdU || game.ram[0x0249U] != 0xceU ||
        game.ram[0x024dU] != 0xceU || game.ram[0x0251U] != 0xcfU ||
        game.ram[0x0255U] != 0xcfU || game.ram[0x0242U] != 0x22U ||
        game.ram[0x0256U] != 0x62U ||
        game.ram[0x0243U] != 0x50U || game.ram[0x0247U] != 0x58U) {
        return 1;
    }

    game.ram[0x075fU] = 7U;
    mysmb_objects_draw_retainer(&game, 0U);
    if (game.ram[0x0241U] != 0x7aU || game.ram[0x0245U] != 0x7bU ||
        game.ram[0x0249U] != 0xdaU || game.ram[0x024dU] != 0xdbU ||
        game.ram[0x0251U] != 0xd8U || game.ram[0x0255U] != 0xd8U) {
        return 2;
    }

    return 0;
}
