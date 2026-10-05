#include "core/world/world.h"
#include "core/enemy/platform.h"

int main(void)
{
    struct mysmb_game game;

    /* CheckRightScreenBBox: object at the source middle position with both
     * horizontal corners still positive moves both corners offscreen. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x071aU] = 1U;
    game.ram[0x071cU] = 0x90U;
    mysmb_world_set_bounding_box(&game, 0x04c8U, 7U, 0x10U, 0x40U);
    mysmb_world_clip_bounding_box_to_screen(&game, 0x04c8U, 2U, 0x10U);
    if (game.ram[0x04c8U] != 0xffU || game.ram[0x04caU] != 0xffU ||
        game.ram[0x04c9U] != 0x40U || game.ram[0x04cbU] != 0x48U) return 1;

    /* CheckLeftScreenBBox: an object in the left half whose box begins in
     * $a0-$ff is truly beyond the left boundary, so both wrapped corners
     * become zero. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x071aU] = 1U;
    game.ram[0x071cU] = 0x90U;
    mysmb_world_set_bounding_box(&game, 0x04c8U, 7U, 0xf0U, 0x40U);
    mysmb_world_clip_bounding_box_to_screen(&game, 0x04c8U, 1U, 0x80U);
    if (game.ram[0x04c8U] != 0U || game.ram[0x04caU] != 0U ||
        game.ram[0x04c9U] != 0x40U || game.ram[0x04cbU] != 0x48U) return 2;

    /* A near-left wrap from $80-$9f is explicitly retained by the source. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x071aU] = 1U;
    game.ram[0x071cU] = 0x90U;
    mysmb_world_set_bounding_box(&game, 0x04c8U, 7U, 0x90U, 0x40U);
    mysmb_world_clip_bounding_box_to_screen(&game, 0x04c8U, 1U, 0x20U);
    if (game.ram[0x04c8U] != 0x90U || game.ram[0x04caU] != 0x98U) return 3;
    /* LargePlatformBoundBox calls the original horizontal child before its
     * hidden-box exit. Even that exit publishes the child's scratch output. */
    mysmb_game_initialize_memory(&game, 0U);
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0xffU;
    game.ram[0x006eU] = 2U;
    game.ram[0x0087U] = 0x10U;
    game.ram[4U] = 0xa4U;
    game.ram[5U] = 0xa5U;
    game.ram[6U] = 0xa6U;
    game.ram[7U] = 0xa7U;
    mysmb_platform_box_large(&game, 0U);
    if (game.ram[4U] != 1U || game.ram[5U] != 0xa5U ||
        game.ram[6U] != 0xa6U || game.ram[7U] != 0xefU ||
        game.ram[0x04b0U] != 0xffU || game.ram[0x04b1U] != 0xffU ||
        game.ram[0x04b2U] != 0xffU || game.ram[0x04b3U] != 0xffU) return 4;

    /* A partial right-edge box also retains DividePDiff's adder and preset
     * after BoundingBoxCore and screen clipping overwrite only $00-$02. */
    game.ram[0x006eU] = 1U;
    game.ram[0x0087U] = 0xf0U;
    game.ram[0x049aU] = 5U;
    game.ram[0x03aeU] = 0x20U;
    game.ram[0x03b9U] = 0x40U;
    mysmb_platform_box_large(&game, 0U);
    if (game.ram[4U] != 1U || game.ram[5U] != 8U ||
        game.ram[6U] != 0x38U || game.ram[7U] != 0x0fU ||
        game.ram[0x04b0U] != 0xffU || game.ram[0x04b2U] != 0xffU ||
        game.ram[0x04b1U] != 0x40U || game.ram[0x04b3U] != 0x4dU) return 5;
    return 0;
}
