#include "game/objects.h"
#include "game/oam/oam.h"

static void mysmb_large_platform_fixture(struct mysmb_game *game)
{
    mysmb_game_initialize_memory(game, 0xfeU);
    game->ram[0x071aU] = 0U;
    game->ram[0x071bU] = 1U;
    game->ram[0x071cU] = 0U;
    game->ram[0x071dU] = 0U;
    game->ram[0x06e5U] = 0x20U;
    /* DrawLargePlatform increments the source X slot before GetXOffscreenBits.
     * This ordinary fixture keeps that next slot wholly on screen. */
    game->ram[0x006fU] = 0U;
    game->ram[0x0088U] = 0x30U;
    game->ram[0x03aeU] = 0x30U;
    game->ram[0x03b9U] = 0x40U;
    game->ram[0x03d1U] = 0U;
    game->ram[0x074eU] = 0U;
    game->ram[0x06ccU] = 0U;
    game->ram[0x0743U] = 0U;
}

static int mysmb_check_six_rows(const struct mysmb_game *game,
                                 mysmb_u8 offscreen, mysmb_u8 y,
                                 mysmb_u8 tile)
{
    mysmb_u8 column;

    for (column = 0U; column < 6U; ++column) {
        mysmb_u16 address;
        mysmb_u8 expected_y;

        address = (mysmb_u16)(0x0220U + column * 4U);
        expected_y = (offscreen & (mysmb_u8)(0x80U >> column)) != 0U
            ? 0xf8U : y;
        if (game->ram[address] != expected_y ||
            game->ram[address + 1U] != tile ||
            game->ram[address + 2U] != 2U ||
            game->ram[address + 3U] != (mysmb_u8)(0x30U + column * 8U))
            return 1;
    }
    return 0;
}

static int mysmb_check_first_four_rows(const struct mysmb_game *game,
                                       mysmb_u8 tile)
{
    mysmb_u8 column;

    for (column = 0U; column < 4U; ++column) {
        mysmb_u16 address;

        address = (mysmb_u16)(0x0220U + column * 4U);
        if (game->ram[address] != 0x40U ||
            game->ram[address + 1U] != tile ||
            game->ram[address + 2U] != 2U ||
            game->ram[address + 3U] != (mysmb_u8)(0x30U + column * 8U))
            return 1;
    }
    return 0;
}

static int mysmb_check_column_masks(void)
{
    mysmb_u8 page;
    mysmb_u8 x;
    mysmb_u8 covered;

    covered = 0U;
    for (page = 0U; page < 2U; ++page) {
        for (x = 0U; x < 0x40U; x = (mysmb_u8)(x + 8U)) {
            struct mysmb_game game;
            mysmb_u8 bits;

            mysmb_large_platform_fixture(&game);
            game.ram[0x006fU] = page;
            game.ram[0x0088U] = x;
            bits = mysmb_oam_get_x_offscreen_bits(&game, page, x);
            mysmb_objects_draw_large_platform(&game, 0U);
            if (mysmb_check_six_rows(&game, bits, 0x40U, 0x5bU) != 0)
                return 1;
            covered = (mysmb_u8)(covered | (bits & 0xfcU));
        }
    }
    return covered == 0xfcU ? 0 : 2;
}

int main(void)
{
    struct mysmb_game game;
    mysmb_u8 row;

    if (mysmb_check_column_masks() != 0) return 1;

    mysmb_large_platform_fixture(&game);
    /* The ordinary SetLast2Platform path must overwrite stale tail rows. */
    game.ram[0x0230U] = 0xf8U;
    game.ram[0x0234U] = 0xf8U;
    mysmb_objects_draw_large_platform(&game, 0U);
    if (mysmb_check_six_rows(&game, 0U, 0x40U, 0x5bU) != 0) return 2;

    mysmb_large_platform_fixture(&game);
    game.ram[0x074eU] = 3U;
    mysmb_objects_draw_large_platform(&game, 0U);
    if (mysmb_check_first_four_rows(&game, 0x5bU) != 0 ||
        game.ram[0x0230U] != 0xf8U || game.ram[0x0234U] != 0xf8U)
        return 3;

    mysmb_large_platform_fixture(&game);
    game.ram[0x06ccU] = 1U;
    game.ram[0x0743U] = 1U;
    mysmb_objects_draw_large_platform(&game, 0U);
    if (mysmb_check_first_four_rows(&game, 0x75U) != 0 ||
        game.ram[0x0230U] != 0xf8U || game.ram[0x0234U] != 0xf8U)
        return 4;

    mysmb_large_platform_fixture(&game);
    game.ram[0x03d1U] = 0x80U;
    mysmb_objects_draw_large_platform(&game, 0U);
    for (row = 0U; row < 6U; ++row) {
        if (game.ram[0x0220U + row * 4U] != 0xf8U) return 5;
    }
    return 0;
}
