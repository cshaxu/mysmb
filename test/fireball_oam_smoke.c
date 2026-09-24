#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.frame_number = 4UL;
    game.ram[0x0024U] = 1U;
    game.ram[0x0074U] = 0U;
    game.ram[0x008dU] = 0x40U;
    game.ram[0x00d5U] = 0x40U;
    game.ram[0x00bcU] = 1U;
    game.ram[0x005eU] = 0U;
    game.ram[0x00a6U] = 0U;
    game.ram[0x06f1U] = 0x20U;
    mysmb_objects_step_fireballs(&game);
    if (game.ram[0x0220U] != 0x40U || game.ram[0x0221U] != 0x65U ||
        game.ram[0x0222U] != 2U || game.ram[0x0223U] != 0x40U) return 1;

    game.frame_number = 0x10UL;
    game.ram[0x0024U] = 1U;
    game.ram[0x008dU] = 0x50U;
    game.ram[0x00d5U] = 0x50U;
    mysmb_objects_step_fireballs(&game);
    return game.ram[0x0220U] == 0x50U && game.ram[0x0221U] == 0x64U &&
        game.ram[0x0222U] == 0xc2U && game.ram[0x0223U] == 0x50U ? 0 : 2;
}