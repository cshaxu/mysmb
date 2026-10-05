#include "core/game.h"
#include "core/player.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x070eU] = 0U;
    game.ram[0x0086U] = 0x27U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0057U] = 0xffU;
    game.ram[0x0400U] = 0x10U;
    (void)mysmb_player_move_horizontally(&game);
    if (game.ram[0x0086U] != 0x27U || game.ram[0x006dU] != 0U) return 1;
    return 0;
}