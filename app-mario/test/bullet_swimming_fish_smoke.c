#include "core/enemy/frenzy.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game;
static unsigned char expected[2048];
static unsigned long cases;

static int check(unsigned int slot)
{
    static const unsigned char heights[8] = {64U,48U,144U,80U,32U,96U,160U,112U};
    unsigned int bit, filter, seed, species, scan, right;
    memcpy(expected, game.ram, sizeof(expected));
    ++cases;
    if (expected[0x78fU] != 0U) goto compare;
    if (expected[0x74eU] == 0U) {
        if (slot >= 3U) goto compare;
        species = ((expected[0x7a7U + slot] >= 170U ? 1U : 0U) +
            (expected[0x75fU] == 1U ? 0U : 1U)) % 2U + 10U;
    } else {
        for (scan = 0U; scan < 5U; ++scan)
            if (expected[0x0fU + scan] && expected[0x16U + scan] == 8U)
                goto compare;
        expected[0xfeU] |= 8U;
        species = 8U;
    }
    expected[0x16U + slot] = (unsigned char)species;
    filter = expected[0x6ddU] == 255U ? 0U : expected[0x6ddU];
    seed = expected[0x7a7U + slot];
    for (scan = 0U; scan < 8U; ++scan) {
        bit = (seed + scan) % 8U;
        if ((filter & (1U << bit)) == 0U) break;
    }
    expected[0x6ddU] = (unsigned char)(filter | (1U << bit));
    right = expected[0x71dU] + 32U;
    expected[0x87U + slot] = (unsigned char)right;
    expected[0x6eU + slot] = (unsigned char)(expected[0x71bU] + right / 256U);
    expected[0xcfU + slot] = (unsigned char)(heights[bit] + 8U);
    expected[0xb6U + slot] = 1U;
    expected[0x0fU + slot] = 1U;
    expected[0x401U + slot] = 0U;
    expected[0x1eU + slot] = 0U;
    expected[0x417U + slot] = 0U;
    expected[0x78fU] = 32U;
    expected[0x3d8U + slot] = 1U;
    expected[4U] = 0x81U; expected[5U] = 0xc2U;
    expected[6U] = species == 8U ? 0x6bU : 0x75U; expected[7U] = 0xc3U;
    expected[0x46U + slot] = 2U;
    expected[0x49aU + slot] = 9U;
    if (species != 8U) {
        expected[0xa0U + slot] = 0U;
        expected[0x58U + slot] = (unsigned char)(seed & 16U);
        expected[0x434U + slot] = expected[0xcfU + slot];
    }
compare:
    mysmb_enemy_step_bullet_bill_cheep_frenzy(&game, (mysmb_u8)slot);
    return memcmp(expected, game.ram, sizeof(expected)) == 0 ? 0 : 1;
}

static void prepare(unsigned int slot, unsigned int area)
{
    memset(&game, 0, sizeof(game));
    memset(game.ram, 0xa5, sizeof(game.ram));
    game.ram[0x74eU] = (mysmb_u8)area;
    game.ram[0x78fU] = 0U;
    game.ram[0x16U + slot] = 23U;
}

int main(void)
{
    unsigned int slot, world, seed, filter, area, scan, active, id;
    for (slot = 0U; slot < 6U; ++slot)
    for (area = 0U; area < 2U; ++area)
    for (seed = 1U; seed < 256U; ++seed) {
        prepare(slot, area); game.ram[0x78fU] = (mysmb_u8)seed;
        if (check(slot)) return 1;
    }
    for (slot = 0U; slot < 6U; ++slot)
    for (world = 0U; world < 3U; ++world)
    for (seed = 0U; seed < 256U; ++seed)
    for (filter = 0U; filter < 256U; ++filter) {
        prepare(slot, slot < 3U ? 0U : 1U);
        game.ram[0x75fU] = (mysmb_u8)world;
        game.ram[0x7a7U + slot] = (mysmb_u8)seed;
        game.ram[0x6ddU] = (mysmb_u8)filter;
        game.ram[0x71dU] = (mysmb_u8)seed;
        game.ram[0x71bU] = (mysmb_u8)(world == 0U ? 0U : 255U);
        if (check(slot)) return 2;
    }
    for (slot = 0U; slot < 6U; ++slot) {
        prepare(slot, 0U);
        if (check(slot)) return 3;
        for (scan = 0U; scan < 6U; ++scan)
        for (active = 0U; active < 2U; ++active)
        for (id = 0U; id < 2U; ++id) {
            prepare(slot, 1U);
            game.ram[0x0fU + scan] = (mysmb_u8)active;
            game.ram[0x16U + scan] = (mysmb_u8)(id == 0U ? 8U : 9U);
            if (check(slot)) return 4;
        }
    }
    printf("%lu Bullet Bill/swimming-fish footprints match\n", cases);
    return 0;
}
