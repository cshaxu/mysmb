#include "game/objects.h"

static mysmb_u8 mysmb_test_oam(const struct mysmb_game *game,
                               const mysmb_u8 *expected)
{
    mysmb_u8 i;

    for (i = 0U; i < 24U; ++i) {
        if (game->ram[0x0220U + i] != expected[i]) return 0U;
    }
    return 1U;
}

int main(void)
{
    static const mysmb_u8 koopa_frame1[24] = {
        0x50U, 0xfcU, 0x01U, 0x40U, 0x50U, 0xa5U, 0x01U, 0x48U,
        0x58U, 0xa6U, 0x01U, 0x40U, 0x58U, 0xa7U, 0x01U, 0x48U,
        0x60U, 0xa8U, 0x01U, 0x40U, 0x60U, 0xa9U, 0x01U, 0x48U
    };
    static const mysmb_u8 buzzy_upside[24] = {
        0x51U, 0xfcU, 0x03U, 0x40U, 0x51U, 0xfcU, 0x03U, 0x48U,
        0x59U, 0xf5U, 0x03U, 0x40U, 0x59U, 0xf5U, 0x03U, 0x48U,
        0x61U, 0xf4U, 0x03U, 0x40U, 0x61U, 0xf4U, 0x03U, 0x48U
    };
    static const mysmb_u8 koopa_upright[24] = {
        0x52U, 0xfcU, 0x42U, 0x40U, 0x52U, 0xfcU, 0x42U, 0x48U,
        0x5aU, 0x6fU, 0x42U, 0x40U, 0x5aU, 0x6fU, 0x42U, 0x48U,
        0x62U, 0x6dU, 0x42U, 0x40U, 0x62U, 0x6dU, 0x42U, 0x48U
    };
    struct mysmb_game game;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071bU] = 0U;
    game.ram[0x071dU] = 0xf0U;
    game.ram[0x0747U] = 0U;
    game.ram[0x006eU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 0U;
    game.ram[0x001eU] = 0U;
    game.ram[0x0046U] = 1U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00cfU] = 0x50U;
    game.ram[0x00b6U] = 0U;
    game.ram[0x06e5U] = 0x20U;
    game.ram[0x0009U] = 8U;
    mysmb_objects_step_normal_enemy(&game, 0U);
    if (mysmb_test_oam(&game, koopa_frame1) == 0U) return 1;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071bU] = 0U;
    game.ram[0x071dU] = 0xf0U;
    game.ram[0x0747U] = 0U;
    game.ram[0x006eU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 2U;
    game.ram[0x001eU] = 2U;
    game.ram[0x0046U] = 1U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00cfU] = 0x50U;
    game.ram[0x00b6U] = 0U;
    game.ram[0x06e5U] = 0x20U;
    game.ram[0x0009U] = 8U;
    if (mysmb_objects_draw_koopa_buzzy(&game, 0U) == 0U ||
        mysmb_test_oam(&game, buzzy_upside) == 0U) return 1;

    mysmb_game_initialize_memory(&game, 0xfeU);
    game.ram[0x071aU] = 0U;
    game.ram[0x071cU] = 0U;
    game.ram[0x071bU] = 0U;
    game.ram[0x071dU] = 0xf0U;
    game.ram[0x0747U] = 0U;
    game.ram[0x006eU] = 0U;
    game.ram[0x000fU] = 1U;
    game.ram[0x0016U] = 3U;
    game.ram[0x001eU] = 4U;
    game.ram[0x0046U] = 2U;
    game.ram[0x0087U] = 0x40U;
    game.ram[0x00cfU] = 0x50U;
    game.ram[0x00b6U] = 0U;
    game.ram[0x06e5U] = 0x20U;
    game.ram[0x0009U] = 0U;
    if (mysmb_objects_draw_koopa_buzzy(&game, 0U) == 0U ||
        mysmb_test_oam(&game, koopa_upright) == 0U) return 1;
    return 0;
}
