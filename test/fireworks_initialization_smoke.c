#include "game/enemy/frenzy.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game;
static unsigned char expected[2048];

int main(void)
{
    static const unsigned char dx[6] = {0U,48U,96U,96U,0U,32U};
    static const unsigned char ys[6] = {96U,64U,112U,64U,96U,48U};
    unsigned int slot, star, x, index, variant, i, base, page, cases;
    cases = 0U;
    for (slot = 0U; slot < 6U; ++slot) for (x = 1U; x < 256U; ++x) {
        memset(&game, 0, sizeof(game));
        memset(game.ram, 0xa5, sizeof(game.ram));
        game.ram[0x78fU] = (mysmb_u8)x;
        memcpy(expected, game.ram, sizeof(expected));
        mysmb_enemy_init_fireworks_frenzy(&game, (mysmb_u8)slot);
        if (memcmp(expected, game.ram, sizeof(expected))) return 1;
        ++cases;
    }
    for (slot = 0U; slot < 6U; ++slot)
    for (star = 0U; star < 6U; ++star) {
        if (star == slot) continue;
        for (index = 0U; index < 6U; ++index)
        for (variant = 0U; variant < 3U; ++variant)
        for (x = 0U; x < 256U; ++x) {
            memset(&game, 0, sizeof(game));
            memset(game.ram, 0xa5, sizeof(game.ram));
            for (i = 0U; i < 6U; ++i) game.ram[0x16U + i] = 0U;
            game.ram[0x16U + slot] = 22U;
            game.ram[0x16U + star] = 49U;
            /* A lower matching ID must not outrank the descending scan. */
            if (star > 0U && slot != 0U) game.ram[0x16U] = 49U;
            game.ram[0x78fU] = 0U;
            game.ram[0x6d7U] = variant == 0U ? (mysmb_u8)(index + 1U) :
                (variant == 1U ? 1U : 0U);
            game.ram[0x1eU + star] = variant == 0U ? 0U :
                (mysmb_u8)(index + (variant == 2U ? 1U : 0U));
            game.ram[0x87U + star] = (mysmb_u8)x;
            page = variant == 0U ? 0U : (variant == 1U ? 4U : 255U);
            game.ram[0x6eU + star] = (mysmb_u8)page;
            memcpy(expected, game.ram, sizeof(expected));
            expected[0x78fU] = 32U;
            expected[0x6d7U] = (unsigned char)(expected[0x6d7U] - 1U);
            base = (x + 256U - 48U) % 256U;
            expected[0U] = (unsigned char)(page + 256U - (x < 48U ? 1U : 0U));
            expected[0x87U + slot] = (unsigned char)(base + dx[index]);
            expected[0x6eU + slot] = (unsigned char)(expected[0U] + (base + dx[index]) / 256U);
            expected[0xcfU + slot] = ys[index];
            expected[0xb6U + slot] = 1U;
            expected[0x0fU + slot] = 1U;
            expected[0x58U + slot] = 0U;
            expected[0xa0U + slot] = 8U;
            mysmb_enemy_init_fireworks_frenzy(&game, (mysmb_u8)slot);
            if (memcmp(expected, game.ram, sizeof(expected))) return 2;
            ++cases;
        }
    }
    printf("%u fireworks initializer footprints match\n", cases);
    return 0;
}
