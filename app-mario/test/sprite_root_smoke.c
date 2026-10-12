#include "core/frame_root.h"

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
    input.buttons2 = 0U;
    input.buttons = 0U;
    (void)mysmb_frame_root_begin(&game, &input, &mode, &task);
    if (game.ram[0x0200U] != expected_first || game.ppu.visible_scroll_x != 0x34U ||
        game.ppu.visible_scroll_y != 0x56U) return 1;
    for (index = 1U; index < 64U; ++index) {
        if (game.ram[(mysmb_u16)(0x0200U + index * 4U)] !=
            (expected_rest == 0xf8U ? expected_rest : (mysmb_u8)(0x20U + index))) return 1;
    }
    return 0;
}

/* Both entry selectors must preserve every tile/attribute/X byte, and
 * clearing CPU OAM must not retroactively change the prior DMA image. */
static int mysmb_sprite_entry_case(mysmb_u8 all)
{
    struct mysmb_game game;
    mysmb_u16 offset;
    mysmb_u8 expected;

    mysmb_game_power_on(&game);
    for (offset = 0U; offset < 0x0100U; ++offset) {
        game.ram[0x0200U + offset] = (mysmb_u8)(offset ^ 0x5aU);
        game.ppu.visible_oam[offset] = (mysmb_u8)(offset ^ 0xa5U);
    }
    if (all != 0U) mysmb_game_move_all_sprites_offscreen(&game);
    else mysmb_game_move_sprites_offscreen(&game);
    for (offset = 0U; offset < 0x0100U; ++offset) {
        expected = (mysmb_u8)(offset ^ 0x5aU);
        if ((offset & 3U) == 0U && (all != 0U || offset != 0U))
            expected = 0xf8U;
        if (game.ram[0x0200U + offset] != expected ||
            game.ppu.visible_oam[offset] != (mysmb_u8)(offset ^ 0xa5U)) return 1;
    }
    return 0;
}

int main(void)
{
    if (mysmb_sprite_entry_case(1U) != 0) return 4;
    if (mysmb_sprite_entry_case(0U) != 0) return 5;
    if (mysmb_sprite_root_case(0U, 0U, 0x20U, 0x21U) != 0) return 1;
    if (mysmb_sprite_root_case(1U, 0U, 0x20U, 0xf8U) != 0) return 2;
    if (mysmb_sprite_root_case(1U, 1U, 0x20U, 0x21U) != 0) return 3;
    return 0;
}