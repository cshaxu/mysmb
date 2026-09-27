#include "game/game.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;

    mysmb_game_power_on(&game);
    if (game.visible_ppu_control_0 != 0x10U || game.ppu_control_0 != 0U ||
        game.ram[0x0770U] != 0U || game.oam_dma_primed != 0U) return 1;
    mysmb_game_reset(&game);
    if (game.ram[0x0770U] != 0U || game.ram[0x0772U] != 0U ||
        game.ram[0x0774U] != 1U || game.ram[0x0200U] != 0xf8U ||
        game.oam_dma_primed != 1U || game.frame_number != 0UL) return 1;
    input.buttons2 = 0U;
    input.buttons2 = 0U;
    input.buttons = 0U;
    mysmb_game_tick(&game, &input, &frame);
    /* With no owner-local title inputs, retain the fixture fallback while
     * proving that only the NMI root, rather than construction, advances it. */
    if (game.frame_number != 1UL || game.ram[0x0772U] != 1U ||
        game.visible_oam[0U] != 0xf8U || game.ram[0x0779U] != 0U ||
        game.ppu_mask != 0U || game.visible_ppu_mask != 0U) return 1;
    return 0;
}
