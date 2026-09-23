#include "game/game.h"
#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 5U;
    game.ram[0x0087U] = 0x80U;
    game.ram[0x00cfU] = 0x60U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x0796U] = 1U;
    game.ram[0x07a8U] = 0U;
    mysmb_objects_step_hammer_bros(&game);
    if (game.ram[0x001eU] != 1U || game.ram[0x00a0U] != 0xfdU ||
        game.ram[0x078aU] != 0x20U || game.ram[0x003cU] != 0xc0U ||
        game.ram[0x0046U] != 2U || game.ram[0x0058U] != 4U) return 1;
    return 0;
}
