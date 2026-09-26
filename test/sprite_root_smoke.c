#include "game/frame_root.h"

static int mysmb_sprite_root_case(mysmb_u8 flag, mysmb_u8 pause,
                                  mysmb_u8 expected_first,
                                  mysmb_u8 expected_rest)
{
    struct mysmb_game game;
    struct mysmb_input input;
    mysmb_u8 mode;
    mysmb_u8 task;
    mysmb_u8 index;

    mysmb_game_initialize(&game);
    game.ram[0x0770U] = 0U;
    game.ram[0x0772U] = 0U;
    game.ram[0x0776U] = pause;
    game.ram[0x0722U] = flag;
    game.ram[0x073fU] = 0x34U;
    game.ram[0x0740U] = 0x56U;
    for (index = 0U; index < 64U; ++index)
        game.ram[(mysmb_u16)(0x0200U + index * 4U)] = (mysmb_u8)(0x20U + index);
    input.buttons = 0U;
    (void)mysmb_frame_root_begin(&game, &input, &mode, &task);
    if (game.ram[0x0200U] != expected_first || game.visible_scroll_x != 0x34U ||
        game.visible_scroll_y != 0x56U) return 1;
    for (index = 1U; index < 64U; ++index) {
        if (game.ram[(mysmb_u16)(0x0200U + index * 4U)] !=
            (expected_rest == 0xf8U ? expected_rest : (mysmb_u8)(0x20U + index))) return 1;
    }
    return 0;
}

int main(void)
{
    if (mysmb_sprite_root_case(0U, 0U, 0x20U, 0x21U) != 0) return 1;
    if (mysmb_sprite_root_case(1U, 0U, 0x20U, 0xf8U) != 0) return 2;
    if (mysmb_sprite_root_case(1U, 1U, 0x20U, 0x21U) != 0) return 3;
    return 0;
}