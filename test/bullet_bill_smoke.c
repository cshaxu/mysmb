#include "game/game.h"
#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 8U;
    game.ram[0x001eU] = 0x20U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x00a0U] = 0xfdU;
    game.ram[0x0417U] = 0U;
    game.ram[0x0434U] = 0U;
    mysmb_objects_step_bullet_bills(&game);
    if (game.ram[0x00b6U] != 0U || game.ram[0x00cfU] != 0x6dU ||
        game.ram[0x00a0U] != 0xfdU || game.ram[0x0434U] != 0x1cU) return 1;
    return 0;
}
