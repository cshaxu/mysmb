#include "game/game.h"
#include "game/audio.h"

int main(void)
{
    static mysmb_u8 prg[0x8000U];
    struct mysmb_game game;

    /* Source selector $08 is SilenceHdr; its stream terminates immediately. */
    prg[0x7914U] = 0x40U;
    prg[0x794dU] = 0x08U;
    prg[0x794eU] = 0U;
    prg[0x794fU] = 0x80U;
    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 1U;

    /* Event music wins over area music, retains the interrupted area command,
     * and death music clears only Square1's source buffer. */
    game.ram[0x00f4U] = 4U;
    game.ram[0x00f1U] = 0x80U;
    game.ram[0x00f2U] = 0x01U;
    game.ram[0x00fbU] = 1U;
    game.ram[0x00fcU] = 1U;
    mysmb_audio_step(&game);
    if (game.ram[0x07b1U] != 1U || game.ram[0x00f4U] != 0U ||
        game.ram[0x07c5U] != 4U || game.ram[0x00f1U] != 0U ||
        game.ram[0x00f2U] != 1U || game.ram[0x00fbU] != 0U ||
        game.ram[0x00fcU] != 0U) return 1;

    /* The original priority scan selects the small jump before all lower
     * square-one bits, then consumes a frame of its exact 40-frame counter. */
    game.ram[0x00ffU] = 0x82U;
    mysmb_audio_step(&game);
    if (game.ram[0x00f1U] != 0x82U || game.ram[0x07bbU] != 0x27U ||
        game.ram[0x00ffU] != 0U) return 2;

    /* ROM PlayGrowPowerUp -> ContinueGrowItems: reveal starts with its
     * ordinary length unchanged at $10 while the secondary counter becomes
     * one, then advances independently on the next frame. */
    game.ram[0x00f2U] = 0U;
    game.ram[0x07bdU] = 0U;
    game.ram[0x07beU] = 0U;
    game.ram[0x00feU] = 0x02U;
    mysmb_audio_step(&game);
    if (game.ram[0x00f2U] != 0x02U || game.ram[0x07bdU] != 0x10U ||
        game.ram[0x07beU] != 1U || game.ram[0x00feU] != 0U) return 3;
    mysmb_audio_step(&game);
    if (game.ram[0x07bdU] != 0x10U || game.ram[0x07beU] != 2U) return 4;
    /* A live 1-UP cannot be replaced by a simultaneous square-two request. */
    game.ram[0x00f2U] = 0x40U;
    game.ram[0x07bdU] = 0x30U;
    game.ram[0x00feU] = 0x80U;
    mysmb_audio_step(&game);
    if (game.ram[0x00f2U] != 0x40U || game.ram[0x07bdU] != 0x2fU ||
        game.ram[0x00feU] != 0U) return 3;

    /* ROM pause-start plays its first tone and decrements 0x2a to 0x29
     * in the same SoundEngine pass. Music queues are not cleared when
     * RunSoundSubroutines is skipped. */
    game.ram[0x00f1U] = 0x40U;
    game.ram[0x00f2U] = 0x01U;
    game.ram[0x00f3U] = 0x02U;
    /* Silence is an event selector during PlayerLoseLife and must terminate
     * in its dispatch pass, before the following area initialization. */
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    game.ram[0x00fcU] = 0x80U;
    game.ram[0x07b4U] = 9U;
    game.ram[0x07b7U] = 0x28U;
    mysmb_audio_step(&game);
    if (game.ram[0x07b1U] != 0U || game.ram[0x00fcU] != 0U ||
        game.ram[0x07b4U] != 0U || game.ram[0x07b7U] != 0x28U) return 4;
    game.ram[0x00faU] = 1U;
    game.ram[0x07b1U] = 1U;
    game.ram[0x00fcU] = 8U;
    mysmb_audio_step(&game);
    if (game.ram[0x07b2U] != 1U || game.ram[0x07c6U] != 1U ||
        game.ram[0x07bbU] != 0x29U || game.ram[0x00f1U] != 0U ||
        game.ram[0x00f2U] != 0U || game.ram[0x00f3U] != 0U ||
        game.ram[0x07b1U] != 1U || game.ram[0x00fcU] != 8U) return 4;
    /* A zero beat and zero loopback offset fall through to SilentBeat.
     * The offset is not reread as a new note when BNE is false. */
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    prg[0x7f66U] = 7U;
    game.ram[0x0770U] = 1U;
    game.ram[0x00f4U] = 1U;
    game.ram[0x00f5U] = 0U;
    game.ram[0x00f6U] = 2U;
    game.ram[0x0200U] = 0x11U;
    game.ram[0x0201U] = 0U;
    game.ram[0x07b0U] = 1U;
    game.ram[0x07b4U] = 5U;
    game.ram[0x07b9U] = 5U;
    game.ram[0x07baU] = 1U;
    game.ram[0x07c1U] = 0U;
    mysmb_audio_step(&game);
    if (game.ram[0x07b0U] != 0U || game.ram[0x07baU] != 7U ||
        game.apu_registers[12U] != 0x10U ||
        game.apu_registers[14U] != 0U ||
        game.apu_registers[15U] != 0U) return 5;
    /* Offset writes precede indirect reads even when the RAM stream aliases
     * its own offset byte. These inputs contain no owner music data. */
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, prg, (mysmb_u16)sizeof(prg));
    game.ram[0x0770U] = 1U;
    game.ram[0x00f4U] = 1U;
    game.ram[0x00f5U] = 0xf9U;
    game.ram[0x00f6U] = 0U;
    game.ram[0x07b4U] = 5U;
    game.ram[0x07b8U] = 5U;
    game.ram[0x07b9U] = 1U;
    game.ram[0x07baU] = 5U;
    mysmb_audio_step(&game);
    if (game.ram[0x00f9U] != 1U || game.ram[0x07b9U] != 5U) return 6;
    game.ram[0x00f5U] = 0xb0U;
    game.ram[0x00f6U] = 7U;
    game.ram[0x07b0U] = 0U;
    game.ram[0x07baU] = 1U;
    game.ram[0x07c1U] = 2U;
    game.ram[0x07b2U] = 0x11U;
    mysmb_audio_step(&game);
    if (game.ram[0x07b0U] != 1U || game.apu_registers[12U] != 0x10U ||
        game.apu_registers[14U] != 1U ||
        game.apu_registers[15U] != 4U) return 7;
    /* The first ADC wraps FF+1 and passes carry into the second ADC. */
    prg[0x7f66U] = 7U;
    prg[0x7f67U] = 9U;
    game.ram[0x00f0U] = 0xffU;
    game.ram[0x07c4U] = 0U;
    if (mysmb_audio_process_music_length(&game, 1U) != 9U) return 8;
    game.ram[0x00f5U] = 0U;
    game.ram[0x00f6U] = 2U;
    game.ram[0x0201U] = 0x40U;
    game.ram[0x07b0U] = 1U;
    game.ram[0x07baU] = 1U;
    mysmb_audio_step(&game);
    if (game.ram[0x07baU] != 9U ||
        game.apu_registers[14U] != 0x40U ||
        game.apu_registers[15U] != 1U) return 9;
    return 0;
}
