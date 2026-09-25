#include "game/objects.h"

static int test_bytes(const struct mysmb_game *game, const mysmb_u8 *expected)
{
    mysmb_u8 i;

    for (i = 0U; i < 24U; ++i) {
        if (game->ram[0x0220U + i] != expected[i]) return 1;
    }
    return 0;
}

static void setup_podoboo(struct mysmb_game *game)
{
    mysmb_game_initialize_memory(game, 0xfeU);
    game->ram[0x071aU] = 0U;
    game->ram[0x071bU] = 1U;
    game->ram[0x071cU] = 0U;
    game->ram[0x071dU] = 0U;
    game->ram[0x000fU] = 1U;
    game->ram[0x0016U] = 12U;
    game->ram[0x0046U] = 2U;
    game->ram[0x0087U] = 0x40U;
    game->ram[0x00cfU] = 0x50U;
    game->ram[0x06e5U] = 0x20U;
}

int main(void)
{
    static const mysmb_u8 expected_up[24] = {
        0x50U, 0xfcU, 0x02U, 0x40U, 0x50U, 0xfcU, 0x42U, 0x48U,
        0x58U, 0xd0U, 0x02U, 0x40U, 0x58U, 0xd0U, 0x42U, 0x48U,
        0x60U, 0xd7U, 0x02U, 0x40U, 0x60U, 0xd7U, 0x42U, 0x48U
    };
    static const mysmb_u8 expected_down[24] = {
        0x50U, 0xfcU, 0x82U, 0x40U, 0x50U, 0xfcU, 0xc2U, 0x48U,
        0x58U, 0xd7U, 0x82U, 0x40U, 0x58U, 0xd7U, 0xc2U, 0x48U,
        0x60U, 0xd0U, 0x82U, 0x40U, 0x60U, 0xd0U, 0xc2U, 0x48U
    };
    struct mysmb_game game;

    setup_podoboo(&game);
    game.ram[0x00a0U] = 0xffU;
    if (mysmb_objects_draw_podoboo(&game, 0U) != 1U ||
        test_bytes(&game, expected_up) != 0) return 1;
    setup_podoboo(&game);
    game.ram[0x00a0U] = 0U;
    if (mysmb_objects_draw_podoboo(&game, 0U) != 1U ||
        test_bytes(&game, expected_down) != 0) return 2;
    return 0;
}
