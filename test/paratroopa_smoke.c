#include "core/game.h"
#include "game/objects.h"
#include <string.h>

int main(void)
{
    struct mysmb_game game;

    /* InitializeMemory clears selected NES RAM, not the host C structure. */
    memset(&game, 0, sizeof(game));
    mysmb_game_initialize_memory(&game, 0U);
    game.frame_number = 0UL;
    game.ram[0x000eU] = 8U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x009fU] = 1U;
    game.ram[0x03d0U] = 0U;
    game.ram[0x0499U] = 0U;
    /* PlayerCtrlRoutine already produced this box; PlayerEnemyCollision consumes it. */
    game.ram[0x04acU] = 0x42U;
    game.ram[0x04adU] = 0x68U;
    game.ram[0x04aeU] = 0x4eU;
    game.ram[0x04afU] = 0x80U;
    game.ram[0x0491U] = 0U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 14U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x049aU] = 9U;
    /* HandlePECollisions takes the injury tail in water; this is a land stomp. */
    game.ram[0x074eU] = 1U;
    mysmb_objects_check_paratroopa_stomp(&game);
    if (game.ram[0x0016U] != 0U || game.ram[0x001eU] != 0U ||
        game.ram[0x00a0U] != 0U || game.ram[0x0434U] != 0U ||
        game.ram[0x0401U] != 0U || game.ram[0x0046U] != 1U ||
        game.ram[0x0058U] != 8U || game.ram[0x009fU] != 0xfcU ||
        game.ram[0x0110U] != 3U || game.ram[0x012cU] != 0x30U ||
        game.ram[0x0491U] != 1U || game.ram[0x04acU] != 0x42U ||
        game.ram[0x04aeU] != 0x4eU) return 1;
    /* InitializeMemory clears selected NES RAM, not the host C structure. */
    memset(&game, 0, sizeof(game));
    mysmb_game_initialize_memory(&game, 0U);
    game.frame_number = 0UL;
    game.ram[0x000eU] = 8U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x009fU] = 1U;
    game.ram[0x03d0U] = 0U;
    game.ram[0x0499U] = 0U;
    /* PlayerCtrlRoutine already produced this box; PlayerEnemyCollision consumes it. */
    game.ram[0x04acU] = 0x42U;
    game.ram[0x04adU] = 0x68U;
    game.ram[0x04aeU] = 0x4eU;
    game.ram[0x04afU] = 0x80U;
    game.ram[0x0491U] = 0U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 15U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x049aU] = 9U;
    /* HandlePECollisions takes the injury tail in water; this is a land stomp. */
    game.ram[0x074eU] = 1U;
    mysmb_objects_check_paratroopa_stomp(&game);
    if (game.ram[0x0016U] != 1U) return 3;
    if (game.ram[0x001eU] != 0U) return 4;
    if (game.ram[0x0046U] != 1U) return 5;
    if (game.ram[0x0058U] != 8U) return 6;
    if (game.ram[0x009fU] != 0xfcU) return 7;
    return 0;
}
