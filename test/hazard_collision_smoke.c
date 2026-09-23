#include "game/game.h"
#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0U);
    game.frame_number = 0UL;
    game.ram[0x000eU] = 8U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x03d0U] = 0U;
    game.ram[0x0499U] = 0U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x0756U] = 1U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 12U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x049aU] = 9U;
    mysmb_objects_check_hazard_enemy_collision(&game);
    if (game.ram[0x0756U] != 0U || game.ram[0x079eU] != 8U ||
        game.ram[0x000eU] != 10U || game.ram[0x001dU] != 1U ||
        game.ram[0x0747U] != 0xffU || game.ram[0x0491U] != 1U) return 1;
    mysmb_game_initialize_memory(&game, 0U);
    game.frame_number = 0UL;
    game.ram[0x000eU] = 8U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x00ceU] = 0x60U;
    game.ram[0x03d0U] = 0U;
    game.ram[0x0499U] = 0U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x0756U] = 1U;
    game.ram[0x079eU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 12U;
    game.ram[0x006eU] = 1U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x00cfU] = 0x70U;
    game.ram[0x049aU] = 9U;
    mysmb_objects_check_hazard_enemy_collision(&game);
    if (game.ram[0x0756U] != 1U || game.ram[0x079eU] != 0U || game.ram[0x0491U] != 0U) return 1;
    return 0;
}
