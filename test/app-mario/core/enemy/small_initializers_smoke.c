#include "core/enemy/init_targets.h"
#include "core/enemy/frenzy.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game;
static unsigned char expected[2048];

/* Independent write contracts, including every unmodified RAM byte. */
int main(void)
{
    unsigned int slot, value, kind, i, cases;
    static const unsigned short targets[6] = {
        0xc3a4U,0xc7b7U,0xc4a8U,0xc5a3U,0xc63dU,0xc69cU
    };
    cases = 0U;
    for (slot = 0U; slot < 6U; ++slot) {
        for (value = 0U; value < 256U; ++value) {
            for (kind = 0U; kind < 2U; ++kind) {
                for (i = 0U; i < 2048U; ++i)
                    game.ram[i] = (unsigned char)(i * 37U + value);
                game.ram[0xcfU + slot] = (unsigned char)value;
                memcpy(expected, game.ram, 2048U);
                if (kind == 0U) {
                    expected[0x58U + slot] = 1U;
                    expected[0x1eU + slot] = 0U;
                    expected[0xa0U + slot] = 0U;
                    expected[0x434U + slot] = (unsigned char)value;
                    expected[0x417U + slot] = (unsigned char)(value - 24U);
                    expected[0x49aU + slot] = 9U;
                    mysmb_enemy_init_piranha_plant(&game, (mysmb_u8)slot);
                } else {
                    expected[0x46U + slot] = 2U;
                    expected[0x58U + slot] = 0xf8U;
                    expected[0x49aU + slot] = 3U;
                    mysmb_enemy_init_jump_green_ptroopa(&game, (mysmb_u8)slot);
                }
                if (memcmp(expected, game.ram, 2048U)) return 1;
                ++cases;
            }
        }
        for (value = 0U; value < 64U; ++value) {
            for (kind = 0U; kind < 64U; ++kind) {
                memset(game.ram, 0x39, 2048U);
                for (i = 0U; i < 6U; ++i) {
                    game.ram[0x16U+i] = (value & (1U<<i)) ? 17U : 6U;
                    game.ram[0x0fU+i] = (kind & (1U<<i)) ? 1U : 0U;
                }
                memcpy(expected, game.ram, 2048U);
                for (i = 0U; i < 6U; ++i)
                    if (value & (1U<<i)) expected[0x1eU+i] = 1U;
                expected[0x6cbU] = 0U; expected[0x0fU+slot] = 0U;
                mysmb_enemy_end_frenzy(&game, (mysmb_u8)slot);
                if (memcmp(expected, game.ram, 2048U)) return 2;
                ++cases;
            }
        }
        for (kind = 0U; kind < 6U; ++kind) {
            memset(game.ram, 0x39, 2048U);
            game.ram[0x16U+slot] = (unsigned char)(0x12U+kind);
            game.ram[0x78fU] = 1U;
            memcpy(expected, game.ram, 2048U);
            expected[0x6cbU] = (unsigned char)(0x12U+kind);
            expected[4] = 0xaaU; expected[5] = 0xc7U;
            expected[6] = (unsigned char)targets[kind];
            expected[7] = (unsigned char)(targets[kind]>>8U);
            mysmb_enemy_init_frenzy(&game, (mysmb_u8)slot);
            if (memcmp(expected, game.ram, 2048U)) return 3;
            ++cases;
        }
    }
    printf("small initializer/frenzy contracts: %u cases\n", cases);
    return 0;
}
