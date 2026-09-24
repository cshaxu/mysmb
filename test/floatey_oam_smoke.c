#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x0110U] = 2U;
    game.ram[0x012cU] = 0x30U;
    game.ram[0x011eU] = 0x40U;
    game.ram[0x0117U] = 0x80U;
    game.ram[0x0016U] = 9U;
    game.ram[0x06e5U] = 0x20U;
    mysmb_objects_step_floatey_numbers(&game);
    if (game.ram[0x011eU] != 0x3fU || game.ram[0x0220U] != 0x37U ||
        game.ram[0x0221U] != 0xf6U || game.ram[0x0222U] != 2U ||
        game.ram[0x0223U] != 0x80U || game.ram[0x0224U] != 0x37U ||
        game.ram[0x0225U] != 0xfbU || game.ram[0x0226U] != 2U ||
        game.ram[0x0227U] != 0x88U) return 1;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x0110U] = 6U;
    game.ram[0x012cU] = 1U;
    game.ram[0x011eU] = 0x10U;
    game.ram[0x0117U] = 0x40U;
    game.ram[0x0016U] = 0U;
    game.ram[0x001eU] = 0U;
    game.ram[0x03eeU] = 1U;
    game.ram[0x06edU] = 0x40U;
    mysmb_objects_step_floatey_numbers(&game);
    return game.ram[0x0240U] == 7U && game.ram[0x0241U] == 0xfaU &&
        game.ram[0x0242U] == 2U && game.ram[0x0243U] == 0x40U &&
        game.ram[0x0244U] == 7U && game.ram[0x0245U] == 0x50U &&
        game.ram[0x0246U] == 2U && game.ram[0x0247U] == 0x48U ? 0 : 2;
}