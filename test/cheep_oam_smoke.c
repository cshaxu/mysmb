#include "game/objects.h"

int main(void)
{
    static const mysmb_u8 expected_flipped[24] = {
        0x50U, 0xfcU, 0x41U, 0x40U, 0x50U, 0xfcU, 0x41U, 0x48U,
        0x58U, 0xb3U, 0x41U, 0x40U, 0x58U, 0xb6U, 0x41U, 0x48U,
        0x60U, 0xb5U, 0x41U, 0x40U, 0x60U, 0xb7U, 0x41U, 0x48U
    };
    static const mysmb_u8 expected_normal[24] = {
        0x50U, 0xfcU, 0x02U, 0x40U, 0x50U, 0xfcU, 0x02U, 0x48U,
        0x58U, 0xb2U, 0x02U, 0x40U, 0x58U, 0xb3U, 0x02U, 0x48U,
        0x60U, 0xb4U, 0x02U, 0x40U, 0x60U, 0xb5U, 0x02U, 0x48U
    };
    struct mysmb_game game;
    const mysmb_u8 *expected;
    mysmb_u8 pass;
    mysmb_u8 i;

    for (pass = 0U; pass < 2U; ++pass) {
        mysmb_game_initialize_memory(&game, 0xfeU);
        game.ram[0x071aU] = 0U;
        game.ram[0x071bU] = 1U;
        game.ram[0x071cU] = 0U;
        game.ram[0x071dU] = 0U;
        game.ram[0x0747U] = 0U;
        game.ram[0x000fU] = 1U;
        game.ram[0x006eU] = 0U;
        game.ram[0x0016U] = pass == 0U ? 10U : 11U;
        game.ram[0x0046U] = pass == 0U ? 2U : 1U;
        game.ram[0x0087U] = 0x40U;
        game.ram[0x00cfU] = 0x50U;
    game.ram[0x00b6U] = 1U;
        game.ram[0x06e5U] = 0x20U;
        game.ram[0x0009U] = pass == 0U ? 0U : 8U;
        mysmb_objects_draw_cheep_cheep(&game, 0U);
        expected = pass == 0U ? expected_flipped : expected_normal;
        for (i = 0U; i < 24U; ++i) {
            if (game.ram[0x0220U + i] != expected[i]) return 11;
        }
    }
    /* RunNormalEnemies clears the transient attribute byte before the
     * graphics handler; its rendering phase precedes Cheep movement. */
    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x071aU] = 0U;
    game.ram[0x071bU] = 1U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071dU] = 0U;
    game.ram[0x0747U] = 0U;
    game.ram[0x000fU] = 1U;
        game.ram[0x006eU] = 0U;
    game.ram[0x0016U] = 10U;
    game.ram[0x0046U] = 2U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00cfU] = 0x50U;
    game.ram[0x00b6U] = 1U;
    game.ram[0x06e5U] = 0x20U;
    game.ram[0x03c5U] = 0xfeU;
    mysmb_objects_step_normal_enemy(&game, 0U);
    if (game.ram[0x0222U] != 0x41U || game.ram[0x03c5U] != 0U) return 12;
    return 0;
}
