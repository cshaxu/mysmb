#include "game/audio.h"
#include <string.h>

enum {
    PRG_SIZE = 0x8000U,
    NOISE_BUFFER = 0x00f3U,
    NOISE_QUEUE = 0x00fdU,
    NOISE_LENGTH = 0x07bfU
};

static void reset_game(struct mysmb_game *game, mysmb_u8 *prg)
{
    memset(game, 0, sizeof(*game));
    memset(prg, 0, PRG_SIZE);
    game->area_prg = prg;
    game->area_prg_size = PRG_SIZE;
    game->ram[0x0770U] = 1U;

    /* Neutral test data at the original local PRG offsets. */
    prg[0x762bU + 15U] = 0x0cU;
    prg[0x7feaU + 15U] = 0x1fU;
    prg[0x7fcaU + 31U] = 0x14U;
    prg[0x7fcaU] = 0x15U;
}

int main(void)
{
    struct mysmb_game game;
    static mysmb_u8 prg[PRG_SIZE];

    /* NoiseSfxHandler selects brick before flame and PlayBrickShatter's
     * initial even counter only enters DecrementSfx3Length. */
    reset_game(&game, prg);
    game.ram[NOISE_QUEUE] = 0x03U;
    mysmb_audio_step(&game);
    if (game.ram[NOISE_BUFFER] != 0x03U ||
        game.ram[NOISE_LENGTH] != 0x1fU || game.apu_registers[12U] != 0U)
        return 1;

    /* ContinueBrickShatter indexes both tables with length / 2 on odd
     * counters, writes all three noise registers, then decrements. */
    mysmb_audio_step(&game);
    if (game.ram[NOISE_LENGTH] != 0x1eU ||
        game.apu_registers[12U] != 0x1fU ||
        game.apu_registers[14U] != 0x0cU ||
        game.apu_registers[15U] != 0x18U) return 2;

    /* PlayBowserFlame uses BowserFlameEnvData-1,length/2 in its first
     * invocation, with the fixed noise period. */
    reset_game(&game, prg);
    game.ram[NOISE_QUEUE] = 0x02U;
    mysmb_audio_step(&game);
    if (game.ram[NOISE_BUFFER] != 0x02U ||
        game.ram[NOISE_LENGTH] != 0x3fU ||
        game.apu_registers[12U] != 0x14U ||
        game.apu_registers[14U] != 0x0fU ||
        game.apu_registers[15U] != 0x18U) return 3;

    /* CheckNoiseBuffer shifts a copy of $f3.  The brick terminal phase
     * writes $f0 and clears the buffer without inventing a queue change. */
    reset_game(&game, prg);
    game.ram[NOISE_BUFFER] = 0x01U;
    game.ram[NOISE_LENGTH] = 1U;
    mysmb_audio_step(&game);
    if (game.ram[NOISE_BUFFER] != 0U ||
        game.ram[NOISE_LENGTH] != 0U || game.apu_registers[12U] != 0xf0U)
        return 4;

    /* Bits beyond the two source selectors only update the buffer and leave
     * the counter untouched after CheckNoiseBuffer's two failed shifts. */
    reset_game(&game, prg);
    game.ram[NOISE_QUEUE] = 0x04U;
    game.ram[NOISE_LENGTH] = 0x33U;
    mysmb_audio_step(&game);
    if (game.ram[NOISE_BUFFER] != 0x04U ||
        game.ram[NOISE_LENGTH] != 0x33U) return 5;
    return 0;
}
