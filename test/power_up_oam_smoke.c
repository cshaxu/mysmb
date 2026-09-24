#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.frame_number = 2UL;
    game.ram[0x0747U] = 0xffU;
    game.ram[0x0039U] = 2U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x0073U] = 0U;
    game.ram[0x008cU] = 0x40U;
    game.ram[0x00d4U] = 0x50U;
    game.ram[0x03caU] = 0x20U;
    game.ram[0x0023U] = 0x80U;
    game.ram[0x06eaU] = 0x20U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x0220U] != 0x50U || game.ram[0x0221U] != 0x8dU ||
        game.ram[0x0222U] != 0x21U || game.ram[0x0223U] != 0x40U ||
        game.ram[0x0224U] != 0x50U || game.ram[0x0225U] != 0x8dU ||
        game.ram[0x0226U] != 0x61U || game.ram[0x0227U] != 0x48U ||
        game.ram[0x0228U] != 0x58U || game.ram[0x0229U] != 0xe4U ||
        game.ram[0x022aU] != 0x21U || game.ram[0x022bU] != 0x40U ||
        game.ram[0x022cU] != 0x58U || game.ram[0x022dU] != 0xe4U ||
        game.ram[0x022eU] != 0x61U || game.ram[0x022fU] != 0x48U) return 1;

    game.frame_number = 6UL;
    game.ram[0x0039U] = 1U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x0221U] != 0xd6U || game.ram[0x0225U] != 0xd6U ||
        game.ram[0x0229U] != 0xd9U || game.ram[0x022dU] != 0xd9U ||
        game.ram[0x0222U] != 0x23U || game.ram[0x0226U] != 0x63U ||
        game.ram[0x022aU] != 0x21U || game.ram[0x022eU] != 0x21U) return 2;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.frame_number = 0UL;
    game.ram[0x0747U] = 0U;
    game.ram[0x0039U] = 0U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x0073U] = 0U;
    game.ram[0x008cU] = 0x40U;
    game.ram[0x00d4U] = 0x50U;
    game.ram[0x03caU] = 0x20U;
    game.ram[0x0023U] = 5U;
    game.ram[0x06eaU] = 0x20U;
    mysmb_objects_step_power_up(&game);
    if (game.ram[0x0023U] != 6U) return 3;
    if (game.ram[0x0220U] != 0x4fU || game.ram[0x0221U] != 0x76U ||
        game.ram[0x0222U] != 0x22U || game.ram[0x0223U] != 0x40U) return 4;
    if (game.ram[0x0228U] != 0x57U || game.ram[0x0229U] != 0x78U ||
        game.ram[0x022fU] != 0x48U) return 5;
    return 0;
}
