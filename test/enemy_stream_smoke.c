#include "game/area.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_area_source source;
    static mysmb_u8 prg[0x0100U];

    mysmb_game_initialize(&game);
    source.prg = prg;
    source.prg_size = (mysmb_u16)sizeof(prg);
    prg[0x20U] = 0x0eU;
    prg[0x21U] = 0xc2U;
    prg[0x22U] = 0x51U;
    prg[0x23U] = 0xffU;
    game.ram[0x00e9U] = 0x20U;
    game.ram[0x00eaU] = 0x80U;
    game.ram[0x0739U] = 0U;
    game.ram[0x073bU] = 1U;
    game.ram[0x0750U] = 0x25U;
    game.ram[0x0751U] = 0U;
    game.ram[0x075fU] = 2U;
    if (mysmb_area_spawn_next_enemy(&game, &source) != 0U ||
        game.ram[0x0750U] != 0xc2U || game.ram[0x0751U] != 0x11U ||
        game.ram[0x0739U] != 3U || game.ram[0x073bU] != 0U) return 1;

    game.ram[0x0739U] = 0U;
    game.ram[0x073bU] = 1U;
    game.ram[0x0750U] = 0x25U;
    game.ram[0x0751U] = 0U;
    game.ram[0x075fU] = 1U;
    if (mysmb_area_spawn_next_enemy(&game, &source) != 0U ||
        game.ram[0x0750U] != 0x25U || game.ram[0x0751U] != 0U ||
        game.ram[0x0739U] != 3U || game.ram[0x073bU] != 0U) return 1;

    prg[0x20U] = 0x8bU;
    prg[0x21U] = 0x86U;
    game.ram[0x0739U] = 0U;
    game.ram[0x073aU] = 1U;
    game.ram[0x073bU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071dU] = 0x30U;
    if (mysmb_area_spawn_next_enemy(&game, &source) != 0U ||
        game.ram[0x0739U] != 0U || game.ram[0x073aU] != 2U ||
        game.ram[0x073bU] != 1U) return 1;
    if (mysmb_area_spawn_next_enemy(&game, &source) != 0U ||
        game.ram[0x0739U] != 0U || game.ram[0x073aU] != 2U ||
        game.ram[0x073bU] != 1U) return 1;
    return 0;
}
