#include "core/frame_root.h"

int main(void)
{
    struct mysmb_game game;
    mysmb_u8 index;

    mysmb_game_initialize(&game);
    for (index = 0U; index < 6U; ++index) {
        game.ram[0x07d7U + index] = 0U;
        game.ram[0x07ddU + index] = 0U;
        game.ram[0x07e3U + index] = 0U;
    }
    game.ram[0x07d7U + 3U] = 1U;
    game.ram[0x07ddU + 4U] = 9U;
    game.ram[0x07ddU + 5U] = 9U;
    game.ram[0x07e3U + 3U] = 1U;
    game.ram[0x07e3U + 5U] = 1U;
    mysmb_frame_root_update_top_score(&game);
    if (game.ram[0x07d7U + 3U] != 1U) return 1;
    if (game.ram[0x07d7U + 4U] != 0U) return 2;
    if (game.ram[0x07d7U + 5U] != 1U) return 3;

    game.ram[0x07ddU] = 9U;
    game.ram[0x07ddU + 1U] = 9U;
    game.ram[0x07ddU + 2U] = 9U;
    game.ram[0x07ddU + 3U] = 9U;
    game.ram[0x07ddU + 4U] = 9U;
    game.ram[0x07ddU + 5U] = 9U;
    mysmb_frame_root_update_top_score(&game);
    for (index = 0U; index < 6U; ++index) {
        if (game.ram[0x07d7U + index] != 9U) return (int)(4U + index);
    }
    return 0;
}
