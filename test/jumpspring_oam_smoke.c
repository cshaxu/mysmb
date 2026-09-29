#include "game/game.h"
#include "game/objects.h"

#include <string.h>

int main(void)
{
    struct mysmb_game game;

    memset(&game, 0, sizeof(game));
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 50U;
    game.ram[0x006eU] = 1U;
    game.ram[0x0087U] = 0x70U;
    game.ram[0x00cfU] = 0xa0U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x0058U] = 0xa0U;
    game.ram[0x071aU] = 1U;
    game.ram[0x071cU] = 0x20U;
    game.ram[0x071bU] = 2U;
    game.ram[0x071dU] = 0x20U;
    game.ram[0x06e5U] = 0x40U;
    game.ram[0x03c5U] = 0x20U;

    mysmb_objects_step_jumpspring(&game, 0U);
    if (game.ram[0x0240U] != 0xa0U || game.ram[0x0241U] != 0xf2U ||
        game.ram[0x0245U] != 0xf2U || game.ram[0x0249U] != 0xf3U ||
        game.ram[0x0242U] != 0x22U || game.ram[0x024aU] != 0x82U ||
        game.ram[0x024eU] != 0xc2U || game.ram[0x0252U] != 0x82U ||
        game.ram[0x0256U] != 0xc2U) {
        return 1;
    }

    game.ram[0x070eU] = 2U;
    game.ram[0x00ceU] = 0x80U;
    mysmb_objects_step_jumpspring(&game, 0U);
    if (game.ram[0x00ceU] != 0x82U || game.ram[0x00cfU] != 0xb0U ||
        game.ram[0x0241U] != 0xf0U || game.ram[0x0245U] != 0xf0U ||
        game.ram[0x0786U] != 4U || game.ram[0x070eU] != 3U) {
        return 2;
    }

    return 0;
}
