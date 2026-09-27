#include "game/game.h"
#include "game/frame_root.h"

static int verify_case(mysmb_u8 control, const mysmb_u8 *expected_offsets,
    const mysmb_u8 *expected_misc)
{
    static const mysmb_u8 initial_offsets[15] = {
        0x20U, 0x27U, 0xf0U, 0x28U, 0x30U, 0x38U, 0x40U, 0x48U,
        0x50U, 0x58U, 0x60U, 0x68U, 0x70U, 0x78U, 0x80U
    };
    struct mysmb_game game;
    mysmb_u8 index;

    mysmb_game_initialize(&game);
    game.ram[0x06e0U] = control;
    game.ram[0x06e1U] = 0x10U;
    game.ram[0x06e2U] = 0x20U;
    game.ram[0x06e3U] = 0x30U;
    for (index = 0U; index < 15U; ++index)
        game.ram[0x06e4U + index] = initial_offsets[index];

    mysmb_game_shuffle_sprite_offsets(&game);

    if (game.ram[0x06e0U] != (mysmb_u8)((control + 1U) % 3U)) return 1;
    for (index = 0U; index < 15U; ++index)
        if (game.ram[0x06e4U + index] != expected_offsets[index]) return 2;
    for (index = 0U; index < 9U; ++index)
        if (game.ram[0x06f3U + index] != expected_misc[index]) return 3;
    return 0;
}

int main(void)
{
    static const mysmb_u8 offsets0[15] = {
        32U, 39U, 40U, 56U, 64U, 72U, 80U, 88U,
        96U, 104U, 112U, 120U, 128U, 136U, 144U
    };
    static const mysmb_u8 misc0[9] = {
        72U, 80U, 88U, 80U, 88U, 96U, 88U, 96U, 104U
    };
    static const mysmb_u8 offsets1[15] = {
        32U, 39U, 56U, 72U, 80U, 88U, 96U, 104U,
        112U, 120U, 128U, 136U, 144U, 152U, 160U
    };
    static const mysmb_u8 misc1[9] = {
        88U, 96U, 104U, 96U, 104U, 112U, 104U, 112U, 120U
    };
    static const mysmb_u8 offsets2[15] = {
        32U, 39U, 72U, 88U, 96U, 104U, 112U, 120U,
        128U, 136U, 144U, 152U, 160U, 168U, 176U
    };
    static const mysmb_u8 misc2[9] = {
        104U, 112U, 120U, 112U, 120U, 128U, 120U, 128U, 136U
    };
    int result;

    result = verify_case(0U, offsets0, misc0);
    if (result != 0) return result;
    result = verify_case(1U, offsets1, misc1);
    if (result != 0) return result + 3;
    result = verify_case(2U, offsets2, misc2);
    if (result != 0) return result + 6;
    return 0;
}
