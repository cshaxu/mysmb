#include "game/enemy/init_targets.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game;
static unsigned char expected[2048];

/* Expected contract deliberately preserves every unrelated sentinel byte. */
static void duplicate_contract(unsigned int slot, unsigned int target)
{
    expected[0x6cfU] = (unsigned char)target;
    expected[0x0fU + target] = (unsigned char)(0x80U | slot);
    expected[0x6eU + target] = expected[0x6eU + slot];
    expected[0x87U + target] = expected[0x87U + slot];
    expected[0x0fU + slot] = 1U;
    expected[0xb6U + target] = 1U;
    expected[0xcfU + target] = expected[0xcfU + slot];
}

int main(void)
{
    static const unsigned char speed[5] = {40U,56U,40U,56U,40U};
    static const unsigned char direction[5] = {0U,0U,16U,16U,0U};
    unsigned int id, slot, value, i, target, cases;
    cases = 0U;
    for (id = 0U; id < 5U; ++id) for (slot = 0U; slot < 6U; ++slot)
    for (value = 0U; value < 256U; ++value) {
        memset(&game, 0, sizeof(game));
        memset(game.ram, 0xa5, sizeof(game.ram));
        for (i = 0U; i < 7U; ++i) game.ram[0x0fU + i] = 1U;
        target = (slot + 1U + value % 5U) % 6U;
        game.ram[0x0fU + target] = 0U;
        game.ram[0x16U + slot] = (mysmb_u8)(id + 27U);
        game.ram[0x87U + slot] = (mysmb_u8)value;
        game.ram[0xcfU + slot] = (mysmb_u8)(255U - value);
        game.ram[0x6eU + slot] = 255U;
        memcpy(expected, game.ram, sizeof(expected));
        if (id == 4U) duplicate_contract(slot, target);
        expected[0x58U + slot] = 0U;
        expected[0x388U + slot] = speed[id];
        expected[0x34U + slot] = direction[id];
        expected[0xcfU + slot] = (unsigned char)(259U - value);
        expected[0x87U + slot] = (unsigned char)(value + 4U);
        expected[0x6eU + slot] = value >= 252U ? 0U : 255U;
        expected[0x49aU + slot] = 3U;
        mysmb_enemy_init_firebar_entry(&game, (mysmb_u8)slot, (mysmb_u8)(id == 4U));
        if (memcmp(expected, game.ram, sizeof(expected))) {
            printf("firebar id=%u slot=%u coordinate=%u mismatch\n",id+27U,slot,value);
            return 1;
        }
        ++cases;
    }
    /* The original scan has no invented five/six-slot limit. Direct child
     * tests cover the full byte index and source-order aliasing on writes. */
    for (slot = 0U; slot < 6U; ++slot) for (target = 0U; target < 256U; ++target) {
        memset(&game, 0, sizeof(game));
        memset(game.ram, 0xa5, sizeof(game.ram));
        for (i = 0U; i < target; ++i) game.ram[0x0fU + i] = 1U;
        game.ram[0x0fU + target] = 0U;
        memcpy(expected, game.ram, sizeof(expected));
        duplicate_contract(slot, target);
        mysmb_enemy_duplicate_object(&game, (mysmb_u8)slot);
        if (memcmp(expected, game.ram, sizeof(expected))) {
            printf("duplicate parent=%u target=%u mismatch\n",slot,target);
            return 2;
        }
        ++cases;
    }
    printf("%u firebar and duplicate footprints match\n",cases);
    return 0;
}
