#include "core/game.h"
#include <string.h>

int main(void)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    mysmb_u8 saved_ram[0x0800U];
    unsigned int index;

    mysmb_game_power_on(&game);
    if (game.ppu.visible_ppu_control_0 != 0x10U || game.ppu.ppu_control_0 != 0x10U ||
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
        game.ppu.visible_oam[0U] != 0xf8U || game.ram[0x0779U] != 0U ||
        game.ppu.ppu_mask != 0U || game.ppu.visible_ppu_mask != 0U) return 1;
    /* Source Start preserves a supplied warm RAM image. Poll failures in
     * either VBlank barrier must leave it untouched and never advance NMI. */
    mysmb_game_power_on(&game);
    for (index = 0U; index < 0x0800U; ++index)
        game.ram[index] = (mysmb_u8)(index * 37U);
    for (index = 0U; index < 6U; ++index)
        game.ram[0x07d7U + index] = (mysmb_u8)(index + 1U);
    game.ram[0x07ffU] = 0xa5U;
    memcpy(saved_ram, game.ram, sizeof(saved_ram));
    mysmb_game_begin_startup(&game);
    if (memcmp(saved_ram, game.ram, sizeof(saved_ram)) != 0 ||
        game.ppu.ppu_control_0 != 0x10U) return 2;
    for (index = 0U; index < 3U; ++index)
        if (mysmb_game_startup_step(&game, 0U) != 0U) return 3;
    if (mysmb_game_startup_step(&game, 1U) != 0U ||
        memcmp(saved_ram, game.ram, sizeof(saved_ram)) != 0) return 4;
    for (index = 0U; index < 3U; ++index)
        if (mysmb_game_startup_step(&game, 0U) != 0U) return 5;
    if (mysmb_game_startup_step(&game, 1U) != 0U ||
        game.frame_number != 0UL || game.ram[0x07ffU] != 0xa5U) return 7;
    for (index = 0U; index < 6U; ++index)
        if (game.ram[0x07d7U + index] != (mysmb_u8)(index + 1U)) return 8;
    if (mysmb_game_startup_step(&game, 1U) != 1U ||
        game.frame_number != 0UL) return 9;
    return 0;
}
