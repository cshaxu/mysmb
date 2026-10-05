#include <stdio.h>
#include <string.h>
#include "core/world/world.h"

/* Exhaustive byte inputs; ROM execution is a separate verification track. */
static struct mysmb_game game;
static unsigned char before[2048];

int main(void)
{
    unsigned int offscreen, high, low, index, expected;
    mysmb_u8 mask, result;
    unsigned long cases;
    cases = 0UL;
    memset(&game, 0, sizeof(game));
    for (offscreen = 0U; offscreen < 256U; ++offscreen) {
        for (high = 0U; high < 256U; ++high) {
            for (low = 0U; low < 256U; ++low) {
                game.ram[0x3d0U] = (mysmb_u8)offscreen;
                game.ram[0xb5U] = (mysmb_u8)high;
                game.ram[0xceU] = (mysmb_u8)low;
                expected = offscreen >= 240U ? 1U : 0U;
                if (expected == 0U && high == 1U)
                    expected = low >= 208U ? 1U : 0U;
                if (mysmb_world_player_vertical_carry(&game) != expected)
                    return 1;
                ++cases;
            }
        }
    }
    for (offscreen = 0U; offscreen < 256U; ++offscreen) {
        for (index = 0U; index < 256U; ++index) {
            game.ram[8U] = (mysmb_u8)index;
            game.ram[0x3d1U] = (mysmb_u8)offscreen;
            memcpy(before, game.ram, sizeof(before));
            expected = ((index % 64U) * 4U + 4U) % 256U;
            result = mysmb_world_enemy_box_offset_arg(&game,
                (mysmb_u8)index, &mask);
            if (result != expected || mask != offscreen % 16U ||
                mysmb_world_enemy_box_offset(&game) != expected ||
                memcmp(before, game.ram, sizeof(before)) != 0) return 2;
            ++cases;
        }
    }
    printf("preflight cases=%lu passed\n", cases);
    return 0;
}
