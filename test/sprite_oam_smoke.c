#include "game/game.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    static mysmb_u8 prg[1] = { 0U };
    mysmb_u16 offset;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    input.buttons = 0U;
    game.ram[0x0770U] = 1U;
    game.ram[0x0772U] = 2U;
    for (offset = 0x0300U; offset < 0x0400U; ++offset)
        game.ram[offset] = 0x5aU;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x06e1U] != 0x58U || game.ram[0x06e2U] != 0x48U ||
        game.ram[0x06e3U] != 0x38U || game.ram[0x06e4U] != 0x04U ||
        game.ram[0x06f2U] != 0x2cU || game.ram[0x0200U] != 0x18U ||
        game.ram[0x0201U] != 0xffU || game.ram[0x0202U] != 0x23U ||
        game.ram[0x0203U] != 0x58U || game.ram[0x0722U] != 1U ||
        game.ram[0x0300U] != 0U || game.ram[0x0301U] != 0U ||
        game.ram[0x03ffU] != 0U || game.ram[0x03a0U] != 0xffU) return 1;

    game.ram[0x0204U] = 1U;
    game.ram[0x0770U] = 4U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x0200U] != 0x18U || game.ram[0x0204U] != 0xf8U ||
        game.ram[0x06e0U] != 1U || game.ram[0x06e5U] != 0x88U ||
        game.ram[0x06e6U] != 0xa0U || game.ram[0x06e9U] != 0xe8U ||
        game.ram[0x06eaU] != 0x28U || game.ram[0x06ebU] != 0x40U ||
        game.ram[0x06f3U] != 0xe8U || game.ram[0x06f4U] != 0xf0U ||
        game.ram[0x06f5U] != 0xf8U || game.ram[0x06f6U] != 0x28U ||
        game.ram[0x06f7U] != 0x30U || game.ram[0x06f8U] != 0x38U ||
        game.ram[0x06f9U] != 0x40U || game.ram[0x06faU] != 0x48U ||
        game.ram[0x06fbU] != 0x50U) return 1;
    return 0;
}
