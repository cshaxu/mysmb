#include "game/game.h"
#include "game/area.h"

int main(void)
{
    struct mysmb_game game;
    static mysmb_u8 prg[0x1600U];
    unsigned int index;

    for (index = 0U; index < sizeof(prg); ++index) prg[index] = 0U;
    prg[0x12f7U] = 0U;
    prg[0x12faU + 18U] = 0x32U;
    prg[0x138aU + 3U] = 0x10U;
    prg[0x138aU + 4U] = 0x11U;
    prg[0x138aU + 5U] = 0x12U;
    prg[0x13aeU + 1U] = 13U;
    prg[0x13b1U + 13U + 4U] = 0x55U;
    prg[0x13b1U + 13U + 6U] = 0x50U;
    prg[0x13b1U + 13U + 7U] = 0x51U;
    prg[0x13d8U] = 0x69U;
    prg[0x13d8U + 1U] = 0x54U;
    prg[0x13d8U + 2U] = 0x52U;
    prg[0x13d8U + 3U] = 0x62U;
    prg[0x13dcU + 2U] = 0U;
    prg[0x13dcU + 3U] = 0x18U;
    prg[0x1504U] = 0x10U;
    prg[0x1504U + 1U] = 0x51U;
    prg[0x1504U + 2U] = 0x88U;
    prg[0x1504U + 3U] = 0xc0U;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    game.ram[0x0725U] = 1U;
    game.ram[0x0726U] = 2U;
    game.ram[0x06a0U] = 0U;
    game.ram[0x0742U] = 1U;
    game.ram[0x0741U] = 2U;
    game.ram[0x074eU] = 1U;
    game.ram[0x0727U] = 1U;
    if (mysmb_area_render_scenery_terrain_column(&game) == 0U ||
        game.ram[0x0530U] != 0x10U || game.ram[0x0540U] != 0x55U ||
        game.ram[0x0550U] != 0x12U || game.ram[0x0560U] != 0U ||
        game.ram[0x0570U] != 0x51U || game.ram[0x05b0U] != 0x54U ||
        game.ram[0x05c0U] != 0x54U) return 1;

    game.ram[0x06a0U] = 1U;
    game.ram[0x0742U] = 0U;
    game.ram[0x0741U] = 0U;
    game.ram[0x0743U] = 3U;
    if (mysmb_area_render_scenery_terrain_column(&game) == 0U ||
        game.ram[0x05b1U] != 0x88U || game.ram[0x05c1U] != 0U) return 1;
    return 0;
}
