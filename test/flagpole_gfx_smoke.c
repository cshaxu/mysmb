#include "game/game.h"
#include "game/objects.h"
#include <string.h>

static const mysmb_u8 score_tiles[10] = {
    0xf9U, 0x50U, 0xf7U, 0x50U, 0xfaU,
    0xfbU, 0xf8U, 0xfbU, 0xf6U, 0xfbU
};

int main(void)
{
    struct mysmb_game game;
    mysmb_u8 score;
    mysmb_u8 row;

    memset(&game, 0, sizeof(game));
    game.ram[0x0008U] = 5U;
    game.ram[0x06e5U + 5U] = 0x80U;
    game.ram[0x03aeU] = 0x40U;
    game.ram[0x00cfU + 5U] = 0x30U;
    game.ram[0x010dU] = 0x60U;
    mysmb_objects_draw_flagpole_graphics(&game);
    if (game.ram[0x0002U] != 0x60U || game.ram[0x0003U] != 1U ||
        game.ram[0x0004U] != 1U) return 1;

    for (score = 0U; score < 5U; ++score) {
        memset(&game, 0, sizeof(game));
        game.ram[0x0008U] = 5U;
        game.ram[0x06e5U + 5U] = 0x80U;
        game.ram[0x03aeU] = 0x40U;
        game.ram[0x00cfU + 5U] = 0x30U;
        game.ram[0x010dU] = 0x60U;
        game.ram[0x070fU] = 1U;
        game.ram[0x010fU] = score;
        mysmb_objects_draw_flagpole_graphics(&game);
        if (game.ram[0x0280U] != 0x30U || game.ram[0x0284U] != 0x30U ||
            game.ram[0x0288U] != 0x38U || game.ram[0x0281U] != 0x7eU ||
            game.ram[0x0285U] != 0x7fU || game.ram[0x0289U] != 0x7eU ||
            game.ram[0x0283U] != 0x40U || game.ram[0x0287U] != 0x48U ||
            game.ram[0x028bU] != 0x48U) return 1;
        if (game.ram[0x028cU] != 0x60U || game.ram[0x0290U] != 0x60U ||
            game.ram[0x028dU] != score_tiles[score * 2U] ||
            game.ram[0x0291U] != score_tiles[score * 2U + 1U] ||
            game.ram[0x028fU] != 0x54U || game.ram[0x0293U] != 0x5cU ||
            game.ram[0x0000U] != score_tiles[score * 2U] ||
            game.ram[0x0002U] != 0x60U || game.ram[0x0003U] != 1U ||
            game.ram[0x0004U] != 1U || game.ram[0x0005U] != 0x54U) return 2;
    }
    game.ram[0x03d1U] = 2U;
    mysmb_objects_draw_flagpole_graphics(&game);
    for (row = 0U; row < 6U; ++row)
        if (game.ram[0x0280U + row * 4U] != 0xf8U) return 3;
    return 0;
}
