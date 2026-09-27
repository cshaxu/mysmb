#include "game/objects.h"

int main(void)
{
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x0110U] = 2U;
    game.ram[0x012cU] = 0x30U;
    game.ram[0x011eU] = 0x40U;
    game.ram[0x0117U] = 0x80U;
    game.ram[0x0016U] = 9U;
    game.ram[0x06e5U] = 0x20U;
    mysmb_objects_step_floatey_numbers(&game);
    if (game.ram[0x011eU] != 0x3fU || game.ram[0x0220U] != 0x37U ||
        game.ram[0x0221U] != 0xf7U || game.ram[0x0222U] != 2U ||
        game.ram[0x0223U] != 0x80U || game.ram[0x0224U] != 0x37U ||
        game.ram[0x0225U] != 0xfbU || game.ram[0x0226U] != 2U ||
        game.ram[0x0227U] != 0x88U) return 1;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x0110U] = 0x0bU;
    game.ram[0x012cU] = 0x2bU;
    game.ram[0x011eU] = 0x40U;
    game.ram[0x0117U] = 0x80U;
    game.ram[0x0016U] = 18U;
    game.ram[0x06e5U] = 0x20U;
    game.ram[0x06ecU] = 0x40U;
    game.ram[0x075aU] = 2U;
    mysmb_objects_step_floatey_number(&game, 0U);
    if (game.ram[0x075aU] != 3U || game.ram[0x00feU] != 0x40U ||
        game.ram[0x0220U] != 0x37U || game.ram[0x0221U] != 0xfdU ||
        game.ram[0x0223U] != 0x80U || game.ram[0x0240U] != 0U) return 2;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x0110U] = 6U;
    game.ram[0x012cU] = 1U;
    game.ram[0x011eU] = 0x10U;
    game.ram[0x0117U] = 0x40U;
    game.ram[0x0016U] = 0U;
    game.ram[0x001eU] = 0U;
    game.ram[0x03eeU] = 1U;
    game.ram[0x06edU] = 0x40U;
    mysmb_objects_step_floatey_numbers(&game);
    if (game.ram[0x0240U] != 7U || game.ram[0x0241U] != 0xf6U ||
        game.ram[0x0242U] != 2U || game.ram[0x0243U] != 0x40U ||
        game.ram[0x0244U] != 7U || game.ram[0x0245U] != 0x50U ||
        game.ram[0x0246U] != 2U || game.ram[0x0247U] != 0x48U) return 3;

    /* Controls above $0a clamp to 1-UP before the timer path.  The same
     * source call decrements Y, preserves CMP carry for the final SBC, and
     * uses the two $fd/$fe tile bytes. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x0110U] = 0x0cU;
    game.ram[0x012cU] = 1U;
    game.ram[0x011eU] = 0x18U;
    game.ram[0x0117U] = 0x40U;
    game.ram[0x0016U] = 9U;
    game.ram[0x06e5U] = 0x20U;
    mysmb_objects_step_floatey_number(&game, 0U);
    return game.ram[0x0110U] == 0x0bU && game.ram[0x012cU] == 0U &&
        game.ram[0x011eU] == 0x17U && game.ram[0x0220U] == 0x0eU &&
        game.ram[0x0221U] == 0xfdU && game.ram[0x0225U] == 0xfeU ? 0 : 4;
}
