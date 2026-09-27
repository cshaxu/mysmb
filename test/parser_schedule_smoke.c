#include "game/area.h"
#include "game/game.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    static mysmb_u8 prg[0x1600U];
    unsigned int index;

    for (index = 0U; index < sizeof(prg); ++index) prg[index] = 0U;
    prg[0x0040U] = 0xfdU;
    prg[0x0b0cU] = 0x80U;
    prg[0x0b0dU] = 0x80U;
    prg[0x0b0eU] = 0x80U;
    prg[0x0b0fU] = 0x80U;
    prg[0x13d8U + 1U] = 0x69U;
    prg[0x13dcU + 2U] = 0U;
    prg[0x13dcU + 3U] = 0x18U;
    prg[0x1504U] = 0x10U;
    prg[0x1504U + 1U] = 0x51U;
    prg[0x1504U + 2U] = 0x88U;
    prg[0x1504U + 3U] = 0xc0U;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    input.buttons2 = 0U;
    input.buttons = 0U;
    game.ram[0x0770U] = 1U;
    game.ram[0x0772U] = 3U;
    game.ram[0x000eU] = 12U;
    game.ram[0x074eU] = 1U;
    game.ram[0x00e7U] = 0x40U;
    game.ram[0x00e8U] = 0x80U;
    game.ram[0x0725U] = 0U;
    game.ram[0x0726U] = 0U;
    game.ram[0x072aU] = 0U;
    game.ram[0x072bU] = 0U;
    game.ram[0x072cU] = 0U;
    game.ram[0x0730U] = 0xffU;
    game.ram[0x0731U] = 0xffU;
    game.ram[0x0732U] = 0xffU;
    game.ram[0x0720U] = 0x20U;
    game.ram[0x0721U] = 0x80U;
    game.ram[0x073dU] = 0x20U;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x073dU] != 0U || game.ram[0x071fU] != 7U ||
        game.ram[0x06a0U] != 0U || game.ram[0x0773U] != 0U) return 1;
    mysmb_game_tick(&game, &input, &frame);
    if (game.ram[0x071fU] != 6U || game.ram[0x0340U] != 29U ||
        game.ram[0x0341U] != 0x20U || game.ram[0x0342U] != 0x80U ||
        game.ram[0x0773U] != 6U) return 1;
    return 0;
}
