#include "game/world/world.h"

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
    return 0;
}
