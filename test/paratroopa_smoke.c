#include "game/game.h"
#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;

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
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 14U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x049aU] = 9U;
    mysmb_objects_check_jumping_paratroopa_stomp(&game);
    if (game.ram[0x0016U] != 0U || game.ram[0x001eU] != 0U ||
        game.ram[0x00a0U] != 0U || game.ram[0x0434U] != 0U ||
        game.ram[0x0401U] != 0U || game.ram[0x0046U] != 2U ||
        game.ram[0x0058U] != 0xf8U || game.ram[0x009fU] != 0xfcU ||
        game.ram[0x0110U] != 3U || game.ram[0x012cU] != 0x30U ||
        game.ram[0x0491U] != 1U) return 1;
    return 0;
}
