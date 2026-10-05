#include "core/game.h"
#include "core/oam/oam.h"
#include <string.h>

static int expect_rows(const struct mysmb_game *game, mysmb_u8 oam,
                       mysmb_u8 rows, mysmb_u8 value)
{
    mysmb_u8 row;

    for (row = 0U; row < rows; ++row)
        if (game->ram[(mysmb_u16)(0x0200U + oam + row * 4U)] != value)
            return 1;
    return 0;
}

int main(void)
{
    struct mysmb_game game;

    memset(&game, 0, sizeof(game));
    mysmb_oam_dump_two_sprites(&game, 0x11U, 0x80U);
    if (expect_rows(&game, 0x80U, 2U, 0x11U) != 0 ||
        game.ram[0x0208U + 0x80U] != 0U) return 1;
    mysmb_oam_dump_three_sprites(&game, 0x22U, 0x80U);
    if (expect_rows(&game, 0x80U, 3U, 0x22U) != 0 ||
        game.ram[0x020cU + 0x80U] != 0U) return 2;
    mysmb_oam_dump_four_sprites(&game, 0x33U, 0x80U);
    if (expect_rows(&game, 0x80U, 4U, 0x33U) != 0 ||
        game.ram[0x0210U + 0x80U] != 0U) return 3;
    mysmb_oam_dump_six_sprites(&game, 0x44U, 0x80U);
    if (expect_rows(&game, 0x80U, 6U, 0x44U) != 0) return 4;
    mysmb_oam_move_six_sprites_offscreen(&game, 0x80U);
    return expect_rows(&game, 0x80U, 6U, 0xf8U);
}
