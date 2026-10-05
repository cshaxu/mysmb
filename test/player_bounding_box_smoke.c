#include "core/game.h"
#include "game/player.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize(&game);
    game.ram[0x000eU] = 8U;
    game.ram[0x001dU] = 0U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x28U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0xb0U;
    game.ram[0x0716U] = 1U;
    game.ram[0x0754U] = 1U;
    /* InitializeArea calls GetScreenPosition before PlayerCtrlRoutine.
     * The shared clamp route reads both derived right-edge bytes. */
    mysmb_player_get_screen_position(&game);
    mysmb_player_step(&game, 0U);
    if (game.ram[0x0499U] != 1U || game.ram[0x04acU] != 0x2bU ||
        game.ram[0x04adU] != 0xc4U || game.ram[0x04aeU] != 0x35U ||
        game.ram[0x04afU] != 0xd0U) return 1;
    return 0;
}
