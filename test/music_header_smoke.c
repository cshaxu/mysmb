#include "game/game.h"
#include "game/area.h"
#include "game/audio.h"

int main(void)
{
    static mysmb_u8 prg[0x8000U];
    struct mysmb_game game;

    /* Ground music's first layout selector is MusicHeaderData+$10. */
    prg[0x791dU] = 0x40U;
    prg[0x794dU] = 0x18U;
    prg[0x794eU] = 0x01U;
    prg[0x794fU] = 0xfaU;
    prg[0x7950U] = 0x2dU;
    prg[0x7951U] = 0x1cU;
    prg[0x7952U] = 0xb8U;
    prg[0x7a01U] = 0x81U;
    prg[0x7a02U] = 0x34U;
    prg[0x7f7fU] = 9U;
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    game.ram[0x0770U] = 1U;
    game.ram[0x00fbU] = 1U;
    mysmb_audio_step(&game);
    if (game.ram[0x00f4U] != 1U || game.ram[0x00f0U] != 0x18U ||
        game.ram[0x00f5U] != 1U || game.ram[0x00f6U] != 0xfaU ||
        game.ram[0x00f7U] != 2U || game.ram[0x00f8U] != 0x1cU ||
        game.ram[0x00f9U] != 0x2dU || game.ram[0x07b0U] != 0xb8U ||
        game.ram[0x07b3U] != 9U || game.ram[0x07b4U] != 9U ||
        game.ram[0x07b6U] != 1U ||
        game.ram[0x07b9U] != 1U || game.ram[0x07baU] != 1U ||
        game.ram[0x07c1U] != 0xb8U || game.ram[0x07c7U] != 0x11U ||
        game.ram[0x07caU] != 0U || game.ram[0x00fbU] != 0U) return 1;
    return 0;
}