#include "core/game.h"
#include "game/objects.h"
#include <string.h>

int main(void)
{
    struct mysmb_game game;

    memset(&game, 0, sizeof(game));
    mysmb_objects_step_flagpole(&game);
    if (game.ram[0x0008U] != 5U) return 12;

    memset(&game, 0, sizeof(game));
    mysmb_objects_start_flagpole(&game, 1U, 0x80U);
    if (game.ram[0x0087U + 5U] != 0x78U || game.ram[0x006eU + 5U] != 1U ||
        game.ram[0x00cfU + 5U] != 0x30U || game.ram[0x0016U + 5U] != 48U ||
        game.ram[0x000fU + 5U] != 1U || game.ram[0x010dU] != 0xb0U) return 1;
    game.ram[0x071aU] = 1U; game.ram[0x071cU] = 0x20U;
    game.ram[0x071bU] = 2U; game.ram[0x071dU] = 0x20U;
    /* FlagpoleObject leaves Enemy_Y_HighPos intact; the real slot-five
     * caller has already established its in-screen high byte. */
    game.ram[0x00b6U + 5U] = 1U;
    game.ram[0x06e5U + 5U] = 0x80U; game.ram[0x000eU] = 4U;
    game.ram[0x001dU] = 3U; game.ram[0x00ceU] = 0x20U;
    game.ram[0x010fU] = 2U; game.ram[0x070fU] = 0x20U;
    mysmb_objects_step_flagpole(&game);
    if (game.ram[0x0008U] != 5U) return 21;
    if (game.ram[0x03aeU] != 0x58U) return 22;
    if (game.ram[0x03b9U] != 0x31U) return 23;
    if (game.ram[0x03d1U] != 0U) return 24;
    if (game.ram[0x00cfU + 5U] != 0x31U) return 25;
    if (game.ram[0x0417U + 5U] != 0xffU) return 26;
    if (game.ram[0x010dU] != 0xaeU) return 27;
    if (game.ram[0x010eU] != 1U) return 28;
    if (game.ram[0x0280U] != 0x31U || game.ram[0x0281U] != 0x7eU ||
        game.ram[0x0282U] != 1U || game.ram[0x0283U] != 0x58U ||
        game.ram[0x0284U] != 0x31U || game.ram[0x0285U] != 0x7fU ||
        game.ram[0x0287U] != 0x60U || game.ram[0x0288U] != 0x39U ||
        game.ram[0x0289U] != 0x7eU || game.ram[0x028bU] != 0x60U) return 3;
    if (game.ram[0x028cU] != 0xaeU || game.ram[0x028dU] != 0xfaU ||
        game.ram[0x028fU] != 0x6cU || game.ram[0x0290U] != 0xaeU ||
        game.ram[0x0291U] != 0xfbU || game.ram[0x0293U] != 0x74U) return 4;

    /* FPGfx calls GetEnemyOffscreenBits, retaining the vertical nibble. */
    game.ram[0x00b6U + 5U] = 2U;
    mysmb_objects_step_flagpole(&game);
    if (game.ram[0x03d1U] != 0xf0U) return 13;

    memset(&game, 0, sizeof(game));
    mysmb_objects_start_flagpole(&game, 0U, 0x80U);
    game.ram[0x000eU] = 4U; game.ram[0x001dU] = 3U;
    game.ram[0x00ceU] = 0x20U; game.ram[0x00cfU + 5U] = 0xaaU;
    game.ram[0x0770U] = 1U;
    game.ram[0x010fU] = 2U;
    mysmb_objects_step_flagpole(&game);
    if (game.ram[0x000eU] != 5U || game.ram[0x07e1U] != 8U) return 10;
    mysmb_objects_step_flagpole(&game);
    return game.ram[0x07e1U] == 8U ? 0 : 11;
}
