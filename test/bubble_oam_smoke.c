#include "game/fireball/fireball.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x074eU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x0033U] = 1U;
    game.ram[0x0024U] = 0U;
    game.ram[0x0025U] = 0U;
    game.ram[0x00e4U] = 0xf8U;
    game.ram[0x00e5U] = 0xf8U;
    game.ram[0x00e6U] = 0xf8U;
    game.ram[0x07aaU] = 1U;
    game.ram[0x06eeU] = 0x20U;
    game.ram[0x06efU] = 0x24U;
    game.ram[0x06f0U] = 0x30U;
    mysmb_fireball_step(&game);
    if (game.ram[0x0792U] != 0x20U || game.ram[0x0085U] != 0U ||
        game.ram[0x009eU] != 0x48U || game.ram[0x00e6U] != 0x67U ||
        game.ram[0x03b2U] != 0x48U || game.ram[0x03bdU] != 0x67U ||
        game.ram[0x0230U] != 0x67U || game.ram[0x0231U] != 0x74U ||
        game.ram[0x0232U] != 2U || game.ram[0x0233U] != 0x48U) return 1;

    game.ram[0x00e6U] = 0x20U;
    game.ram[0x042eU] = 0x10U;
    game.ram[0x07aaU] = 1U;
    game.ram[0x0230U] = 0x67U;
    mysmb_fireball_step(&game);
    if (game.ram[0x00e6U] != 0xf8U ||
        (game.ram[0x03d5U] & 0xf0U) == 0U || game.ram[0x0230U] != 0xf8U ||
        game.ram[0x0231U] != 0x74U || game.ram[0x0232U] != 2U ||
        game.ram[0x0233U] != 0x48U) return 2;
    return 0;
}