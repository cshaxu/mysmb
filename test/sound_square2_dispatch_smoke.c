#include "game/audio.h"
#include <string.h>

static void reset_game(struct mysmb_game *game)
{
    memset(game, 0, sizeof(*game));
    game->ram[0x0770U] = 1U;
}

int main(void)
{
    struct mysmb_game game;

    /* Square2SfxHandler's first LSR selects coin before lower-priority bits. */
    reset_game(&game);
    game.ram[0x00feU] = 0x03U;
    mysmb_audio_step(&game);
    if (game.ram[0x00f2U] != 0x03U || game.ram[0x07bdU] != 0x34U)
        return 1;
    if (game.apu_registers[4U] != 0x8dU ||
        game.apu_registers[5U] != 0x7fU) return 2;

    /* An active 1-up takes priority over a newly queued coin.  With length
     * one, the later ContinueExtraLife path reaches the shared stop tail. */
    reset_game(&game);
    game.ram[0x00f2U] = 0x41U;
    game.ram[0x00feU] = 0x01U;
    game.ram[0x07bdU] = 1U;
    mysmb_audio_step(&game);
    if (game.ram[0x00f2U] != 0U || game.ram[0x00feU] != 0U ||
        game.apu_registers[21U] != 0x0fU) return 3;

    /* CheckSfx2Buffer's empty branch returns without touching its counter. */
    reset_game(&game);
    game.ram[0x07bdU] = 0x23U;
    mysmb_audio_step(&game);
    if (game.ram[0x00f2U] != 0U || game.ram[0x07bdU] != 0x23U) return 4;

    /* The coin/timer branches converge at Cont_CGrab_TTick. */
    reset_game(&game);
    game.ram[0x00f2U] = 0x10U;
    game.ram[0x07bdU] = 0x30U;
    mysmb_audio_step(&game);
    if (game.ram[0x07bdU] != 0x2fU || game.apu_registers[6U] != 0x54U)
        return 5;
    return 0;
}
