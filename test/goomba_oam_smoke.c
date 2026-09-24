#include "game/objects.h"

void mysmb_objects_draw_goombas(struct mysmb_game *game);

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
    struct mysmb_game game;
    const mysmb_u8 *expected;
    mysmb_u8 pass;
    mysmb_u8 i;

    for (pass = 0U; pass < 2U; ++pass) {
        mysmb_game_initialize_memory(&game, 0U);
        game.ram[0x000fU] = 1U;
        game.ram[0x0016U] = 6U;
        game.ram[0x0046U] = 1U;
        game.ram[0x0087U] = 0x40U;
        game.ram[0x00cfU] = 0x50U;
        game.ram[0x06e5U] = 0x20U;
        game.frame_number = pass == 0U ? 0UL : 8UL;
        mysmb_objects_draw_goombas(&game);
        expected = pass == 0U ? expected_flipped : expected_normal;
        for (i = 0U; i < 24U; ++i) {
            if (game.ram[0x0220U + i] != expected[i]) return 1;
        }
    }
    return 0;
}