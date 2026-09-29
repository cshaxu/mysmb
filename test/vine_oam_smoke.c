#include "game/game.h"
#include "game/objects.h"
#include <string.h>

int main(void)
{
    struct mysmb_game game;

    memset(&game, 0, sizeof(game));
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU + 5U] = 1U;
    game.ram[0x0016U + 5U] = 0x2fU;
    game.ram[0x0087U + 5U] = 0x40U;
    game.ram[0x00cfU + 5U] = 0x80U;
    game.ram[0x0009U] = 0U;
    game.ram[0x0398U] = 1U;
    game.ram[0x0399U] = 8U;
    game.ram[0x039aU] = 5U;
    game.ram[0x039dU] = 0x80U;
    game.ram[0x06e5U + 5U] = 0x20U;
    mysmb_objects_step_vine(&game, 5U);
    if (game.ram[0x0220U] != 0x80U || game.ram[0x0221U] != 0xe0U ||
        game.ram[0x0222U] != 0x21U || game.ram[0x0223U] != 0x40U ||
        game.ram[0x0224U] != 0xf8U || game.ram[0x0225U] != 0xe1U ||
        game.ram[0x0226U] != 0x61U || game.ram[0x0227U] != 0x46U ||
        game.ram[0x0234U] != 0xf8U || game.ram[0x0235U] != 0xe1U ||
        game.ram[0x0236U] != 0x61U || game.ram[0x0237U] != 0x46U) return 1;
    game.ram[0x0398U] = 2U;
    game.ram[0x039aU] = 5U;
    game.ram[0x039aU + 1U] = 5U;
    game.ram[0x03aeU] = 0x40U;
    game.ram[0x03b9U] = 0x20U;
    mysmb_objects_draw_vine(&game, 1U);
    if (game.ram[0x0220U] != 0x50U || game.ram[0x0221U] != 0xe1U ||
        game.ram[0x0222U] != 0x21U || game.ram[0x0223U] != 0x40U ||
        game.ram[0x0224U] != 0x58U || game.ram[0x0225U] != 0xe1U ||
        game.ram[0x0226U] != 0x61U || game.ram[0x0227U] != 0x46U) return 2;
    return 0;
}
