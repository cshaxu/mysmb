#include "game/game.h"
#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 5U;
    game.ram[0x001eU] = 0U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x80U;
    game.ram[0x00cfU] = 0x60U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x0796U] = 1U;
    game.ram[0x07a8U] = 0U;
    game.ram[0x003cU] = 0U;
    game.ram[0x078aU] = 0U;
    game.ram[0x0747U] = 0U;
    game.ram[0x0417U] = 0U;
    game.ram[0x0434U] = 0U;
    game.ram[0x0558U] = 1U;
    mysmb_objects_step_hammer_bros(&game);
    if (game.ram[0x001eU] != 1U) return 11;
    if (game.ram[0x00a0U] != 0xfdU) return 12;
    if (game.ram[0x078aU] != 0x20U) return 13;
    if (game.ram[0x003cU] != 0xc0U) return 14;
    if (game.ram[0x0046U] != 2U) return 15;
    if (game.ram[0x0058U] != 4U) return 16;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 5U;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x80U;
    game.ram[0x00cfU] = 0x60U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x003cU] = 1U;
    game.ram[0x07a8U] = 1U;
    game.ram[0x001eU] = 0U;
    game.ram[0x078aU] = 0x20U;
    game.ram[0x0747U] = 0U;
    game.ram[0x0013U] = 0U;
    game.ram[0x0014U] = 0U;
    game.ram[0x0558U] = 1U;
    mysmb_objects_step_hammer_bros(&game);
    if (game.ram[0x03a2U] != 0x30U || game.ram[0x001eU] != 8U ||
        game.ram[0x002bU] != 0x90U || game.ram[0x06afU] != 0U ||
        game.ram[0x04a3U] != 7U) return 2;
    mysmb_objects_step_misc(&game);
    if (game.ram[0x002bU] != 0x8fU || game.ram[0x0094U] != 0x81U ||
        game.ram[0x00dcU] != 0x56U || game.ram[0x00c3U] != 1U) return 3;
    game.ram[0x002bU] = 0x82U;
    game.ram[0x0046U] = 1U;
    mysmb_objects_step_misc(&game);
    if (game.ram[0x002bU] != 0x81U || game.ram[0x00adU] != 0xfeU ||
        game.ram[0x0065U] != 0x10U || (game.ram[0x001eU] & 8U) != 0U) return 4;
    mysmb_objects_step_misc(&game);
    if (game.ram[0x002bU] != 0x81U || game.ram[0x0094U] != 0x82U ||
        game.ram[0x00dcU] != 0x54U) return 5;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 5U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00cfU] = 0x80U;
    game.ram[0x006dU] = 0U;
    game.ram[0x0086U] = 0x40U;
    game.ram[0x00ceU] = 0x80U;
    game.ram[0x00b5U] = 1U;
    game.ram[0x0756U] = 1U;
    game.ram[0x000eU] = 8U;
    game.ram[0x0747U] = 0U;
    game.ram[0x002bU] = 0x81U;
    game.ram[0x0065U] = 0x10U;
    game.ram[0x0094U] = 0x40U;
    game.ram[0x00dcU] = 0x80U;
    game.ram[0x00c3U] = 1U;
    game.ram[0x04a3U] = 7U;
    game.ram[0x06afU] = 0U;
    game.frame_number = 1U;
    mysmb_objects_step_misc(&game);
    if (game.ram[0x06bfU] != 1U || game.ram[0x0065U] != 0xf0U ||
        game.ram[0x0756U] != 0U || game.ram[0x079eU] != 8U ||
        game.ram[0x000eU] != 10U || game.ram[0x001dU] != 1U ||
        game.ram[0x0747U] != 0xffU) return 6;
    return 0;
}
