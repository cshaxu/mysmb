#include "game/game.h"
#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;

    /* ROM MoveFlyingCheepCheep: live fish moves horizontally and uses the
     * lighter $0d downward gravity. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 20U;
    game.ram[0x001eU] = 0U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x0058U] = 0x10U;
    game.ram[0x0401U] = 0U;
    game.ram[0x0417U] = 0U;
    game.ram[0x0434U] = 0U;
    game.ram[0x0747U] = 0U;
    mysmb_objects_step_flying_cheep_cheeps(&game);
    if (game.ram[0x0087U] != 0x41U || game.ram[0x0434U] != 0x0dU ||
        game.ram[0x00cfU] != 0x70U) return 1;

    /* TimerControl freezes a live fish before either axis advances. */
    game.ram[0x0747U] = 1U;
    mysmb_objects_step_flying_cheep_cheeps(&game);
    if (game.ram[0x0087U] != 0x41U || game.ram[0x0434U] != 0x0dU) return 2;

    /* Defeated fish follows the shared falling-object gravity instead. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 20U;
    game.ram[0x001eU] = 0x20U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x0058U] = 0x10U;
    mysmb_objects_step_flying_cheep_cheeps(&game);
    if (game.ram[0x0087U] != 0x40U || game.ram[0x0434U] != 0x1cU ||
        game.ram[0x00cfU] != 0x70U) return 3;
    return 0;
}
