#include "game/game.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;

    mysmb_game_power_on(&game);
    if (game.ram[0x0770U] != 0U || game.ram[0x0772U] != 0U ||
        game.ram[0x0774U] != 1U || game.ram[0x0200U] != 0xf8U ||
        game.oam_dma_primed != 1U || game.frame_number != 0UL) return 1;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    /* With no owner-local title inputs, retain the fixture fallback while
     * proving that only the NMI root, rather than construction, advances it. */
    if (game.frame_number != 1UL || game.ram[0x0772U] != 1U ||
        game.visible_oam[0U] != 0xf8U) return 1;
    return 0;
}
