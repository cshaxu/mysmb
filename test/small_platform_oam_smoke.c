#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;
    static const mysmb_u8 expected[24] = {
        0x40U, 0x5bU, 2U, 0x30U, 0x40U, 0x5bU, 2U, 0x38U,
        0x40U, 0x5bU, 2U, 0x40U, 0xc0U, 0x5bU, 2U, 0x30U,
        0xc0U, 0x5bU, 2U, 0x38U, 0xc0U, 0x5bU, 2U, 0x40U
    };
    mysmb_u8 i;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 43U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x30U;
    game.ram[0x00cfU] = 0x40U;
    game.ram[0x06e5U] = 0x20U;
    mysmb_objects_draw_small_platform(&game, 0U);
    for (i = 0U; i < 24U; ++i) {
        if (game.ram[0x0220U + i] != expected[i]) return 1;
    }
    game.ram[0x0087U] = 0x30U;
    game.ram[0x006eU] = 1U;
    mysmb_objects_draw_small_platform(&game, 0U);
    if (game.ram[0x0220U] != 0xf8U || game.ram[0x0224U] != 0xf8U ||
        game.ram[0x0228U] != 0xf8U || game.ram[0x022cU] != 0xf8U) return 2;
    return 0;
}