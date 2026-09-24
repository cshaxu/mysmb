#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.frame_number = 2UL;
    game.ram[0x002aU] = 2U;
    game.ram[0x007aU] = 1U;
    game.ram[0x0093U] = 0x50U;
    game.ram[0x00dbU] = 0x40U;
    game.ram[0x06f3U] = 0x20U;
    game.ram[0x071aU] = 1U;
    game.ram[0x071cU] = 0x10U;
    mysmb_objects_step_misc(&game);
    if (game.ram[0x0220U] != 0x3fU || game.ram[0x0221U] != 0xf7U ||
        game.ram[0x0222U] != 2U || game.ram[0x0223U] != 0x40U ||
        game.ram[0x0224U] != 0x3fU || game.ram[0x0225U] != 0xfbU ||
        game.ram[0x0226U] != 2U || game.ram[0x0227U] != 0x48U) return 1;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.frame_number = 4UL;
    game.ram[0x002aU] = 1U;
    game.ram[0x007aU] = 0U;
    game.ram[0x0093U] = 0x30U;
    game.ram[0x00dbU] = 0x40U;
    game.ram[0x00acU] = 0U;
    game.ram[0x0440U] = 0U;
    game.ram[0x06f3U] = 0x30U;
    mysmb_objects_step_misc(&game);
    return game.ram[0x0230U] == 0x40U && game.ram[0x0231U] == 0x62U &&
        game.ram[0x0232U] == 2U && game.ram[0x0233U] == 0x30U &&
        game.ram[0x0234U] == 0x48U && game.ram[0x0235U] == 0x62U &&
        game.ram[0x0236U] == 0x82U && game.ram[0x0237U] == 0x30U ? 0 : 2;
}