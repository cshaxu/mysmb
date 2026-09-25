#include "game/objects.h"

static int test_bytes(const struct mysmb_game *game, const mysmb_u8 *expected)
{
    mysmb_u8 i;

    for (i = 0U; i < 24U; ++i) {
        if (game->ram[0x0220U + i] != expected[i]) return 1;
    }
    return 0;
}

static void setup_bloober(struct mysmb_game *game)
{
    mysmb_game_initialize_memory(game, 0xfeU);
    game->ram[0x071aU] = 0U;
    game->ram[0x071bU] = 1U;
    game->ram[0x071cU] = 0U;
    game->ram[0x071dU] = 0U;
    game->ram[0x0747U] = 0U;
    game->ram[0x000fU] = 1U;
    game->ram[0x0016U] = 7U;
    game->ram[0x0046U] = 2U;
    game->ram[0x0087U] = 0x40U;
    game->ram[0x00cfU] = 0x50U;
    game->ram[0x06e5U] = 0x20U;
}

int main(void)
{
    static const mysmb_u8 expected_swim[24] = {
        0x53U, 0xdcU, 0x03U, 0x40U, 0x53U, 0xdcU, 0x43U, 0x48U,
        0x5bU, 0xddU, 0x03U, 0x40U, 0x5bU, 0xddU, 0x43U, 0x48U,
        0x63U, 0xdeU, 0x03U, 0x40U, 0x63U, 0xdeU, 0x43U, 0x48U
    };
    static const mysmb_u8 expected_rest[24] = {
        0x50U, 0xfcU, 0x03U, 0x40U, 0x50U, 0xfcU, 0x43U, 0x48U,
        0x58U, 0xdcU, 0x03U, 0x40U, 0x58U, 0xdcU, 0x43U, 0x48U,
        0x60U, 0xdfU, 0x03U, 0x40U, 0x60U, 0xdfU, 0x43U, 0x48U
    };
    static const mysmb_u8 expected_defeated[24] = {
        0x53U, 0xfcU, 0x83U, 0x40U, 0x53U, 0xfcU, 0xc3U, 0x48U,
        0x5bU, 0xdfU, 0x83U, 0x40U, 0x5bU, 0xdfU, 0xc3U, 0x48U,
        0x63U, 0xdcU, 0x83U, 0x40U, 0x63U, 0xdcU, 0xc3U, 0x48U
    };
    struct mysmb_game game;

    setup_bloober(&game);
    if (mysmb_objects_draw_bloober(&game, 0U) != 1U ||
        test_bytes(&game, expected_swim) != 0) return 1;
    setup_bloober(&game);
    game.ram[0x0796U] = 5U;
    if (mysmb_objects_draw_bloober(&game, 0U) != 1U ||
        test_bytes(&game, expected_rest) != 0) return 2;
    setup_bloober(&game);
    game.ram[0x001eU] = 0x20U;
    if (mysmb_objects_draw_bloober(&game, 0U) != 1U ||
        test_bytes(&game, expected_defeated) != 0) return 3;
    return 0;
}
