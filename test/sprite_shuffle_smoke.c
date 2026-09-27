#include "game/game.h"
#include "game/frame_root.h"
int main(void)
{
    struct mysmb_game game;
    mysmb_u8 index;
    mysmb_game_initialize(&game);
    game.ram[0x06e0U] = 2U;
    game.ram[0x06e1U] = 0x10U;
    game.ram[0x06e2U] = 0x20U;
    game.ram[0x06e3U] = 0x30U;
    for (index = 0U; index < 15U; ++index) game.ram[0x06e4U + index] = (mysmb_u8)(0x20U + index * 0x10U);
    game.ram[0x06e6U] = 0xf0U;
    mysmb_game_shuffle_sprite_offsets(&game);
    if (game.ram[0x06e0U] != 0U || game.ram[0x06e6U] != 0x48U) return 1;
    if (game.ram[0x06f3U] != game.ram[0x06e9U] || game.ram[0x06f4U] != (mysmb_u8)(game.ram[0x06e9U] + 8U)) return 2;
    if (game.ram[0x06f9U] != game.ram[0x06ebU] || game.ram[0x06fbU] != (mysmb_u8)(game.ram[0x06ebU] + 16U)) return 3;
    return 0;
}
