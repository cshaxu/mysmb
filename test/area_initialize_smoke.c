#include "game/area.h"
#include "game/game.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize(&game);
    mysmb_area_initialize(&game);
    if (game.ram[0x071aU] != 0U || game.ram[0x0725U] != 0U ||
        game.ram[0x0728U] != 0U || game.ram[0x071bU] != 0U ||
        game.ram[0x071cU] != 0U || game.ram[0x071dU] != 0xffU ||
        game.ram[0x0720U] != 0x20U || game.ram[0x06a0U] != 0U ||
        game.ram[0x00fbU] != 0x80U) return 1;

    mysmb_game_initialize(&game);
    game.ram[0x075bU] = 3U;
    mysmb_area_initialize(&game);
    if (game.ram[0x071aU] != 3U || game.ram[0x0725U] != 3U ||
        game.ram[0x0728U] != 3U || game.ram[0x071bU] != 3U ||
        game.ram[0x071dU] != 0xffU || game.ram[0x0720U] != 0x24U ||
        game.ram[0x06a0U] != 0x30U || game.ram[0x0710U] != 2U) return 1;

    mysmb_game_initialize(&game);
    game.ram[0x075bU] = 3U;
    game.ram[0x0752U] = 1U;
    game.ram[0x0751U] = 2U;
    game.ram[0x076aU] = 1U;
    mysmb_area_initialize(&game);
    if (game.ram[0x071aU] != 2U || game.ram[0x071bU] != 2U ||
        game.ram[0x0720U] != 0x20U || game.ram[0x06a0U] != 0x20U ||
        game.ram[0x06ccU] != 1U) return 1;
    return 0;
}
