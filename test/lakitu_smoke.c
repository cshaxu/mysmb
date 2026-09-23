#include "game/game.h"
#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;

    /* PlayerLakituDiff: 64 pixels is capped at $3c, then $15-$10 yields
     * $05.  Direction zero selects the negated horizontal speed. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 17U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x80U;
    game.ram[0x00a0U] = 0U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    mysmb_objects_step_lakitus(&game);
    if (game.ram[0x06cbU] != 18U || game.ram[0x0058U] != 0xfbU ||
        game.ram[0x0046U] != 2U || game.ram[0x0087U] != 0x7fU ||
        game.ram[0x0401U] != 0xb0U) return 1;

    /* Beyond $3c, a left-moving Lakitu decelerates before reversing. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 17U;
    game.ram[0x006eU] = 1U;
    game.ram[0x0087U] = 0U;
    game.ram[0x00a0U] = 1U;
    game.ram[0x0058U] = 2U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x10U;
    mysmb_objects_step_lakitus(&game);
    if (game.ram[0x0058U] != 1U || game.ram[0x00a0U] != 1U ||
        game.ram[0x0087U] != 0U) return 1;

    /* A stomped Lakitu follows MoveD_EnemyVertically's $3d gravity route. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 17U;
    game.ram[0x001eU] = 0x20U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    mysmb_objects_step_lakitus(&game);
    if (game.ram[0x00cfU] != 0x70U || game.ram[0x0417U] != 0U ||
        game.ram[0x0434U] != 0x3dU) return 1;

    /* Spiny eggs select the same routine with the original $20 force. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 18U;
    game.ram[0x001eU] = 5U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    mysmb_objects_step_spiny_eggs(&game);
    if (game.ram[0x00cfU] != 0x70U || game.ram[0x0417U] != 0U ||
        game.ram[0x0434U] != 0x20U) return 1;
    return 0;
}
