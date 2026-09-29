#include "game/dispatcher.h"
#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0U;
    game.ram[0x0026U] = 1U;
    game.ram[0x008fU] = 0x40U;
    game.ram[0x00d7U] = 0x20U;
    game.ram[0x03e8U] = 0xc4U;
    game.ram[0x06ecU] = 0x20U;
    game.ram[0x074eU] = 1U;
    mysmb_game_engine_blocks(&game);
    if (game.ram[0x0220U] != 0x20U || game.ram[0x0221U] != 0x87U ||
        game.ram[0x0222U] != 3U || game.ram[0x0223U] != 0x40U ||
        game.ram[0x0224U] != 0x20U || game.ram[0x0225U] != 0x87U ||
        game.ram[0x0226U] != 0x43U || game.ram[0x0227U] != 0x48U ||
        game.ram[0x0228U] != 0x28U || game.ram[0x0229U] != 0x87U ||
        game.ram[0x022aU] != 0x83U || game.ram[0x022eU] != 0xc3U) return 1;

    /* ROM DrawBlock leaves all four ordinary-block attributes at palette 3.
     * Flip bits are only assigned by its used-block ($c4) branch. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x0026U] = 1U;
    game.ram[0x008fU] = 0x40U;
    game.ram[0x00d7U] = 0x20U;
    game.ram[0x03e8U] = 0x51U;
    game.ram[0x06ecU] = 0x20U;
    game.ram[0x074eU] = 1U;
    mysmb_game_engine_blocks(&game);
    if (game.ram[0x0222U] != 3U || game.ram[0x0226U] != 3U ||
        game.ram[0x022aU] != 3U || game.ram[0x022eU] != 3U) return 2;

    mysmb_game_initialize_memory(&game, 0U);
    game.frame_number = 4UL;
    game.ram[0x0009U] = (mysmb_u8)(4UL);
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0U;
    game.ram[0x0026U] = 2U;
    game.ram[0x008fU] = 0x40U;
    game.ram[0x0091U] = 0x40U;
    game.ram[0x00d7U] = 0x20U;
    game.ram[0x00d9U] = 0x28U;
    game.ram[0x03f1U] = 0x40U;
    game.ram[0x06ecU] = 0x20U;
    mysmb_game_engine_blocks(&game);
    /* DrawBrickChunks applies d7 to the first two sprite Y entries. */
    if (game.ram[0x0220U] != 0xf8U || game.ram[0x0224U] != 0xf8U ||
        game.ram[0x0221U] != 0x84U ||
        game.ram[0x0222U] != 0x43U || game.ram[0x0223U] != 0x40U ||
        game.ram[0x0227U] != 0x47U || game.ram[0x0228U] != 0x28U ||
        game.ram[0x022bU] != 0x40U || game.ram[0x022fU] != 0x47U) return 3;

    /* ImposeGravity reaches Block_YMF_Dummy through generic offset $09:
     * $0416+$09=$041f.  A carry from slot zero affects Block Y and OAM. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x0026U] = 1U;
    game.ram[0x00d7U] = 0x40U;
    game.ram[0x00a8U] = 0U;
    game.ram[0x043cU] = 0x50U;
    game.ram[0x041fU] = 0xb0U;
    game.ram[0x0420U] = 0U;
    game.ram[0x06ecU] = 0x20U;
    mysmb_game_engine_blocks(&game);
    /* The original left-column d3 mask still applies after gravity. */
    return game.ram[0x00d7U] == 0x41U && game.ram[0x041fU] == 0U &&
        game.ram[0x03bcU] == 0x41U && game.ram[0x0220U] == 0xf8U &&
        game.ram[0x0224U] == 0x41U ? 0 : 4;
}
