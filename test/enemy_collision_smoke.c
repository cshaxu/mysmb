#include "game/game.h"
#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x074eU] = 1U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0010U] = 1U;
    game.ram[0x0016U] = 0U;
    game.ram[0x0017U] = 0U;
    game.ram[0x001eU] = 0U;
    game.ram[0x001fU] = 0U;
    game.ram[0x006eU] = 0U;
    game.ram[0x006fU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x0088U] = 0x40U;
    game.ram[0x00cfU] = 0x50U;
    game.ram[0x00d0U] = 0x50U;
    game.ram[0x049aU] = 0U;
    game.ram[0x049bU] = 0U;
    game.ram[0x0046U] = 2U;
    game.ram[0x0047U] = 1U;
    game.ram[0x0058U] = 0xf0U;
    game.ram[0x0059U] = 0x10U;
    game.frame_number = 1U;
    mysmb_objects_step_enemy_collisions(&game);
    if (game.ram[0x0058U] != 0x10U || game.ram[0x0059U] != 0xf0U ||
        game.ram[0x0046U] != 1U || game.ram[0x0047U] != 2U) return 1;
    game.ram[0x0017U] = 5U;
    game.ram[0x0058U] = 0xf0U;
    game.ram[0x0059U] = 0x10U;
    game.ram[0x0046U] = 2U;
    game.ram[0x0047U] = 1U;
    mysmb_objects_step_enemy_collisions(&game);
    if (game.ram[0x0058U] != 0x10U || game.ram[0x0059U] != 0x10U ||
        game.ram[0x0046U] != 1U || game.ram[0x0047U] != 1U) return 2;
    game.ram[0x0017U] = 0U;
    game.ram[0x001fU] = 6U;
    game.ram[0x001eU] = 0U;
    game.ram[0x0126U] = 0U;
    mysmb_objects_step_enemy_collisions(&game);
    if ((game.ram[0x001eU] & 0x20U) == 0U || game.ram[0x0110U] != 4U ||
        game.ram[0x0126U] != 1U) return 3;
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x0747U] = 1U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 6U;
    game.ram[0x006eU] = 1U;
    game.ram[0x0087U] = 0x5fU;
    game.ram[0x00cfU] = 0xb8U;
    game.ram[0x049aU] = 9U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0x31U;
    mysmb_objects_step_normal_enemies(&game);
    if (game.ram[0x03d8U] != 8U || game.ram[0x04b0U] != 0xffU ||
        game.ram[0x04b1U] != 0xffU || game.ram[0x04b2U] != 0xffU ||
        game.ram[0x04b3U] != 0xffU) return 4;
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x0747U] = 1U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 6U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0xf6U;
    game.ram[0x00cfU] = 0xb8U;
    game.ram[0x049aU] = 9U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0xffU;
    mysmb_objects_step_normal_enemies(&game);
    if (game.ram[0x03d1U] != 3U || game.ram[0x04b2U] != 0xffU) return 5;
    game.ram[0x0087U] = 0xeeU;
    mysmb_objects_step_normal_enemies(&game);
    if (game.ram[0x03d1U] != 1U) return 6;
    return 0;
}
