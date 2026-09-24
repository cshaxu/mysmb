#include "game/objects.h"

int main(void)
{
    static const mysmb_u8 expected_flipped[24] = {
        0x50U, 0xfcU, 0x43U, 0x40U, 0x50U, 0xfcU, 0x43U, 0x48U,
        0x58U, 0x71U, 0x43U, 0x40U, 0x58U, 0x70U, 0x43U, 0x48U,
        0x60U, 0x73U, 0x43U, 0x40U, 0x60U, 0x72U, 0x43U, 0x48U
    };
    static const mysmb_u8 expected_normal[24] = {
        0x50U, 0xfcU, 0x03U, 0x40U, 0x50U, 0xfcU, 0x03U, 0x48U,
        0x58U, 0x70U, 0x03U, 0x40U, 0x58U, 0x71U, 0x03U, 0x48U,
        0x60U, 0x72U, 0x03U, 0x40U, 0x60U, 0x73U, 0x03U, 0x48U
    };
    static const mysmb_u8 expected_defeated[24] = {
        0x4fU, 0xfcU, 0x03U, 0x40U, 0x4fU, 0xfcU, 0x03U, 0x48U,
        0x57U, 0xfcU, 0x03U, 0x40U, 0x57U, 0xfcU, 0x03U, 0x48U,
        0x5fU, 0xefU, 0x03U, 0x40U, 0x5fU, 0xefU, 0x03U, 0x48U
    };
    struct mysmb_game game;
    const mysmb_u8 *expected;
    mysmb_u8 pass;
    mysmb_u8 i;

    for (pass = 0U; pass < 3U; ++pass) {
        mysmb_game_initialize_memory(&game, 0xfeU);
        game.ram[0x071aU] = 0U;
        game.ram[0x071cU] = 0U;
        game.ram[0x000fU] = 1U;
        game.ram[0x0016U] = 6U;
        game.ram[0x0046U] = 1U;
        game.ram[0x0087U] = 0x40U;
        game.ram[0x00cfU] = 0x50U;
        game.ram[0x06e5U] = 0x20U;
        game.frame_number = pass == 0U ? 0UL : 8UL;
        game.ram[0x0009U] = pass == 0U ? 0U : 8U;
        if (pass == 2U) game.ram[0x001eU] = 4U;
        mysmb_objects_draw_goombas(&game);
        expected = pass == 0U ? expected_flipped :
                   (pass == 1U ? expected_normal : expected_defeated);
        for (i = 0U; i < 24U; ++i) {
            if (game.ram[0x0220U + i] != expected[i]) return 1;
        }
    }
    mysmb_game_initialize(&game);
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 6U;
    game.ram[0x0046U] = 2U;
    game.ram[0x006eU] = 1U;
    game.ram[0x0087U] = 0x60U;
    game.ram[0x00cfU] = 0xb8U;
    game.ram[0x03aeU] = 0x2eU;
    game.ram[0x03b9U] = 0xb8U;
    game.ram[0x03d1U] = 0x0fU;
    game.ram[0x03c5U] = 0x24U;
    game.ram[0x06e5U] = 0x20U;
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0x30U;
    mysmb_objects_draw_goombas(&game);
    for (i = 0U; i < 24U; i = (mysmb_u8)(i + 4U)) {
        if (game.ram[0x0220U + i] != 0xf8U) return 1;
    }
    if (game.ram[0x0223U] != 0x2eU || game.ram[0x0227U] != 0x36U ||
        game.ram[0x022bU] != 0x2eU || game.ram[0x022fU] != 0x36U ||
        game.ram[0x0233U] != 0x2eU || game.ram[0x0237U] != 0x36U) return 1;
    game.ram[0x03d1U] = 0x07U;
    mysmb_objects_draw_goombas(&game);
    if (game.ram[0x0220U] != 0xb8U || game.ram[0x0224U] != 0xf8U ||
        game.ram[0x0228U] != 0xc0U || game.ram[0x022cU] != 0xf8U ||
        game.ram[0x0230U] != 0xc8U || game.ram[0x0234U] != 0xf8U) return 1;
    return 0;
}