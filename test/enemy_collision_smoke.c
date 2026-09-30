#include "game/game.h"
#include "game/objects.h"
#include "game/world/world.h"
#include <string.h>

int main(void)
{
    struct mysmb_game game;

    memset(&game, 0, sizeof game);
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
    game.ram[0x00b6U] = 1U;
    game.ram[0x00d0U] = 0x50U;
    game.ram[0x049aU] = 0U;
    game.ram[0x049bU] = 0U;
    game.ram[0x0046U] = 2U;
    game.ram[0x0047U] = 1U;
    game.ram[0x0058U] = 0xf0U;
    game.ram[0x0059U] = 0x10U;
    game.frame_number = 1U;
    game.ram[0x0009U] = (mysmb_u8)(1U);
    mysmb_world_set_bounding_box(&game, 0x04b0U, game.ram[0x0058U], 0x40U, 0x50U);
    mysmb_world_set_bounding_box(&game, 0x04b4U, game.ram[0x0059U], 0x40U, 0x50U);
    game.ram[0x0491U] = 0U;
    mysmb_objects_step_enemy_collisions_current(&game, 1U);
    if (game.ram[0x0058U] != 0x10U || game.ram[0x0059U] != 0xf0U ||
        game.ram[0x0046U] != 1U || game.ram[0x0047U] != 2U) return 1;
    game.ram[0x0017U] = 5U;
    game.ram[0x0058U] = 0xf0U;
    game.ram[0x0059U] = 0x10U;
    game.ram[0x0046U] = 2U;
    game.ram[0x0047U] = 1U;
    game.ram[0x0491U] = 0U;
    mysmb_objects_step_enemy_collisions_current(&game, 1U);
    if (game.ram[0x0058U] != 0x10U || game.ram[0x0059U] != 0x10U ||
        game.ram[0x0046U] != 1U || game.ram[0x0047U] != 1U) return 2;
    game.ram[0x0017U] = 0U;
    game.ram[0x001fU] = 6U;
    game.ram[0x001eU] = 0U;
    game.ram[0x0126U] = 0U;
    game.ram[0x0491U] = 0U;
    mysmb_objects_step_enemy_collisions_current(&game, 1U);
    if ((game.ram[0x001eU] & 0x20U) == 0U || game.ram[0x0110U] != 4U ||
        game.ram[0x0126U] != 1U) return 3;
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x0747U] = 1U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 6U;
    game.ram[0x006eU] = 1U;
    game.ram[0x0087U] = 0x5fU;
    game.ram[0x00cfU] = 0xb8U;
    game.ram[0x00b6U] = 1U;
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
    game.ram[0x00b6U] = 1U;
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
    /* ROM GetXOffscreenBits: an object in the left page of a screen that
     * crosses a page boundary is not right-offscreen.  The right probe
     * loads XOffscreenBitsData[$07] and continues to the left probe. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071cU] = 0x80U;
    game.ram[0x071dU] = 0x7fU;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x90U;
    if (mysmb_objects_get_enemy_x_offscreen_bits(&game, 0U) != 0U) return 7;
    /* DividePDiff uses difference / 8 exactly.  At each eight-pixel
     * boundary the source selects the next XOffscreenBitsData entry. */
    game.ram[0x006eU] = 1U;
    game.ram[0x0087U] = 0x70U;
    if (mysmb_objects_get_enemy_x_offscreen_bits(&game, 0U) != 3U) return 8;
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0x78U;
    if (mysmb_objects_get_enemy_x_offscreen_bits(&game, 0U) != 0x0cU) return 9;
    /* RunOffscrBitsSubs stores GetXOffscreenBits after shifting it into
     * the horizontal low nibble.  An enemy one complete page left of the
     * screen supplies $0f, not $ff; $ff would fabricate vertical offscreen
     * bits and make a power-up uncollectable. */
    game.ram[0x006eU] = 0U;
    game.ram[0x0087U] = 0U;
    if (mysmb_objects_get_enemy_x_offscreen_bits(&game, 0U) != 0x0fU) return 10;
    return 0;
}
