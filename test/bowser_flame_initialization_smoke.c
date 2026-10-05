#include "core/enemy/init_targets.h"
#include "core/enemy/frenzy.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game;
static unsigned char expected[2048];

static void finish(unsigned int slot)
{
    expected[0x49aU + slot] = 8U;
    expected[0xb6U + slot] = 1U;
    expected[0x0fU + slot] = 1U;
    expected[0x401U + slot] = 0U;
    expected[0x1eU + slot] = 0U;
}

int main(void)
{
    static const unsigned char timers[8] = {191U,64U,191U,191U,191U,64U,64U,191U};
    static const unsigned char heights[4] = {144U,128U,112U,144U};
    unsigned int slot, value, random, index, hard, i, target, cases;
    cases = 0U;
    for (slot = 0U; slot < 6U; ++slot) for (value = 0U; value < 256U; ++value) {
        memset(&game, 0, sizeof(game)); memset(game.ram, 0xa5, sizeof(game.ram));
        for (i = 0U; i < 7U; ++i) game.ram[0x0fU + i] = 1U;
        target = (slot + 1U + value % 5U) % 6U;
        game.ram[0x0fU + target] = 0U;
        game.ram[0x87U + slot] = (mysmb_u8)value;
        game.ram[0xcfU + slot] = (mysmb_u8)(255U - value);
        memcpy(expected, game.ram, sizeof(expected));
        expected[0x6cfU] = (unsigned char)target;
        expected[0x0fU + target] = (unsigned char)(0x80U | slot);
        expected[0x6eU + target] = expected[0x6eU + slot];
        expected[0x87U + target] = expected[0x87U + slot];
        expected[0x0fU + slot] = 1U;
        expected[0xb6U + target] = 1U;
        expected[0xcfU + target] = expected[0xcfU + slot];
        expected[0x368U] = (unsigned char)slot;
        expected[0x363U] = 0U; expected[0x369U] = 0U;
        expected[0x366U] = (unsigned char)value;
        expected[0x790U] = 0xdfU; expected[0x46U + slot] = 0xdfU;
        expected[0x364U] = 0x20U; expected[0x78aU + slot] = 0x20U;
        expected[0x483U] = 5U; expected[0x365U] = 2U;
        mysmb_enemy_init_bowser(&game, (mysmb_u8)slot);
        if (memcmp(expected, game.ram, sizeof(expected))) return 1;
        ++cases;
    }
    for (index = 0U; index < 8U; ++index) {
        memset(&game, 0, sizeof(game)); memset(game.ram, 0xa5, sizeof(game.ram));
        game.ram[0x367U] = (mysmb_u8)index;
        memcpy(expected, game.ram, sizeof(expected));
        expected[0x367U] = (unsigned char)((index + 1U) % 8U);
        if (mysmb_enemy_set_flame_timer(&game) != timers[index] ||
            memcmp(expected, game.ram, sizeof(expected))) return 2;
        ++cases;
    }
    for (slot = 0U; slot < 6U; ++slot) for (value = 1U; value < 256U; ++value) {
        memset(&game, 0, sizeof(game)); memset(game.ram, 0xa5, sizeof(game.ram));
        game.ram[0x78fU] = (mysmb_u8)value;
        memcpy(expected, game.ram, sizeof(expected));
        mysmb_enemy_init_bowser_flame_frenzy(&game, (mysmb_u8)slot);
        if (memcmp(expected, game.ram, sizeof(expected))) return 3;
        ++cases;
    }
    for (slot = 0U; slot < 6U; ++slot) for (random = 0U; random < 4U; ++random)
    for (value = 0U; value < 256U; ++value) {
        memset(&game, 0, sizeof(game)); memset(game.ram, 0xa5, sizeof(game.ram));
        target = (slot + 1U) % 6U;
        game.ram[0x368U] = (mysmb_u8)target; game.ram[0x16U + target] = 45U;
        game.ram[0x78fU] = 0U; game.ram[0x7a7U + slot] = (mysmb_u8)random;
        game.ram[0x87U + target] = (mysmb_u8)value;
        game.ram[0xcfU + target] = (mysmb_u8)value;
        memcpy(expected, game.ram, sizeof(expected));
        expected[0xfdU] |= 2U;
        expected[0x87U + slot] = (unsigned char)(value - 14U);
        expected[0x6eU + slot] = expected[0x6eU + target];
        expected[0xcfU + slot] = (unsigned char)(value + 8U);
        expected[0x417U + slot] = (unsigned char)random;
        expected[0x434U + slot] = heights[random] < expected[0xcfU + slot] ? 255U : 1U;
        expected[0x6cbU] = 0U; finish(slot);
        mysmb_enemy_init_bowser_flame_frenzy(&game, (mysmb_u8)slot);
        if (memcmp(expected, game.ram, sizeof(expected))) return 4;
        ++cases;
    }
    for (slot = 0U; slot < 6U; ++slot) for (index = 0U; index < 8U; ++index)
    for (random = 0U; random < 4U; ++random) for (hard = 0U; hard < 2U; ++hard)
    for (value = 0U; value < 256U; ++value) {
        memset(&game, 0, sizeof(game)); memset(game.ram, 0xa5, sizeof(game.ram));
        game.ram[0x368U] = 0U; game.ram[0x16U] = 21U;
        game.ram[0x78fU] = 0U; game.ram[0x367U] = (mysmb_u8)index;
        game.ram[0x6ccU] = (mysmb_u8)hard;
        game.ram[0x7a7U + slot] = (mysmb_u8)random;
        game.ram[0x71dU] = (mysmb_u8)value; game.ram[0x71bU] = 255U;
        memcpy(expected, game.ram, sizeof(expected));
        expected[0xfdU] |= 2U; expected[0x434U + slot] = 0U;
        expected[0x367U] = (unsigned char)((index + 1U) % 8U);
        expected[0x78fU] = (unsigned char)(timers[index] + 32U - hard * 16U);
        expected[0x417U + slot] = (unsigned char)random;
        expected[0xcfU + slot] = heights[random];
        expected[0x87U + slot] = (unsigned char)(value + 32U);
        expected[0x6eU + slot] = value >= 224U ? 0U : 255U;
        finish(slot);
        mysmb_enemy_init_bowser_flame_frenzy(&game, (mysmb_u8)slot);
        if (memcmp(expected, game.ram, sizeof(expected))) return 5;
        ++cases;
    }
    printf("%u Bowser/flame initializer footprints match\n", cases);
    return 0;
}
