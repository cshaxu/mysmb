#include "game/game.h"

int main(void)
{
    struct mysmb_game game;
    mysmb_u8 index;

    mysmb_game_initialize(&game);
    for (index = 0U; index < 6U; ++index)
        game.ram[(mysmb_u16)(0x07d7U + index)] = (mysmb_u8)(index + 1U);
    game.ram[0x07ffU] = 0xa5U;
    game.ram[0x07d6U] = 0x77U;
    game.ram[0x07ddU] = 0x7bU;
    game.ram[0x015fU] = 0x55U;
    game.ram[0x0160U] = 0x55U;
    game.ram[0x0000U] = 0x55U;
    game.ram[0x07a7U] = 0x11U;
    game.ram[0x0774U] = 0U;
    mysmb_game_reset(&game);
    for (index = 0U; index < 6U; ++index) {
        if (game.ram[(mysmb_u16)(0x07d7U + index)] != (mysmb_u8)(index + 1U))
            return 1;
    }
    if (game.ram[0x0000U] != 0U || game.ram[0x015fU] != 0U ||
        game.ram[0x0160U] != 0x55U || game.ram[0x07d6U] != 0U ||
        game.ram[0x07ddU] != 0x7bU || game.ram[0x07ffU] != 0xa5U ||
        game.ram[0x07a7U] != 0xa5U || game.ram[0x0770U] != 0U ||
        game.ram[0x0774U] != 1U || game.ram[0x0200U] != 0xf8U ||
        game.ppu.ppu_mask != 0x06U || game.ppu.visible_ppu_mask != 0x06U ||
        game.ppu.ppu_control_0 != 0x90U || game.ram[0x0778U] != 0x90U ||
        game.ppu.visible_ppu_control_0 != 0x90U || game.oam_dma_primed != 1U ||
        game.apu_delta_counter_load != 0U || game.apu_channel_enable != 0x0fU)
        return 2;
    game.ram[0x07d7U] = 10U;
    game.ram[0x07d8U] = 9U;
    game.ram[0x07ddU] = 0x7bU;
    game.ram[0x015fU] = 0x66U;
    game.ram[0x0160U] = 0x66U;
    game.ram[0x07ffU] = 0xa5U;
    mysmb_game_reset(&game);
    for (index = 0U; index < 6U; ++index) {
        if (game.ram[(mysmb_u16)(0x07d7U + index)] != 0U)
            return 3;
    }
    if (game.ram[0x015fU] != 0U || game.ram[0x0160U] != 0x66U ||
        game.ram[0x07ddU] != 0U || game.ram[0x07ffU] != 0xa5U ||
        game.ram[0x07a7U] != 0xa5U)
        return 4;
    return 0;
}
