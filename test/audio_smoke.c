#include "game/game.h"
#include "game/audio.h"

int main(void)
{
    struct mysmb_game game;

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

    /* Pause preempts active effects and deliberately does not run music. */
    game.ram[0x00f1U] = 0x40U;
    game.ram[0x00f2U] = 0x01U;
    game.ram[0x00f3U] = 0x02U;
    /* Silence is an event selector during PlayerLoseLife and must terminate
     * in its dispatch pass, before the following area initialization. */
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
        game.ram[0x07bbU] != 0x2aU || game.ram[0x00f1U] != 0U ||
        game.ram[0x00f2U] != 0U || game.ram[0x00f3U] != 0U ||
        game.ram[0x07b1U] != 1U || game.ram[0x00fcU] != 0U) return 4;
    return 0;
}
