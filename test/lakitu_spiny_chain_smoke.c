#include "game/enemy/frenzy.h"
#include <stdio.h>
#include <string.h>

/* Caller write-footprint checks. The distance child is separately evaluated
 * on its exact incoming RAM; this does not certify that child's ROM fidelity. */
static struct mysmb_game game, expected;
static unsigned int cases;

static void reset(unsigned int slot)
{
    unsigned int i;
    memset(&game, 0, sizeof(game));
    memset(game.ram, 0xa5, sizeof(game.ram));
    for (i = 0U; i < 6U; ++i) {
        game.ram[0x16U + i] = 0x12U;
        game.ram[0x0fU + i] = 1U;
    }
    game.ram[8U] = (mysmb_u8)slot;
    game.ram[0x78fU] = 0U;
}

static int compare(unsigned int slot, const char *family)
{
    unsigned int i;
    mysmb_enemy_init_lakitu_spiny_frenzy(&game, (mysmb_u8)slot);
    for (i = 0U; i < 2048U; ++i) if (game.ram[i] != expected.ram[i]) {
        printf("%s case=%u slot=%u RAM=%04x expected=%02x actual=%02x\n",
            family, cases, slot, i, (unsigned int)expected.ram[i],
            (unsigned int)game.ram[i]);
        return 1;
    }
    ++cases;
    return 0;
}

int main(void)
{
    static const unsigned char table[3][4] = {
        {0x13U,0x14U,0x15U,0x16U},
        {0x20U,0x22U,0x24U,0x26U},
        {0x26U,0x2cU,0x32U,0x38U}
    };
    unsigned int slot, value, mask, i, selected, lakitu, seed, gate;
    /* No-input gates leave the entire RAM untouched, including timer. */
    for (slot = 0U; slot < 6U; ++slot) for (value = 0U; value < 256U; ++value) {
        if (slot < 5U && value == 0U) continue;
        reset(slot); game.ram[0x78fU] = (mysmb_u8)value;
        expected = game;
        if (compare(slot, "gate")) return 1;
    }
    /* All counter bytes and every occupied/free mask test wrap, threshold,
     * descending allocation and the no-free return, with page carry/wrap. */
    for (value = 0U; value < 256U; ++value) for (mask = 0U; mask < 32U; ++mask) {
        slot = value % 5U;
        reset(slot); game.ram[0x6d1U] = (mysmb_u8)value;
        game.ram[0x71dU] = (mysmb_u8)value;
        game.ram[0x71bU] = 0xffU;
        selected = 5U;
        for (i = 0U; i < 5U; ++i) {
            game.ram[0x0fU + i] = (mask & (1U << i)) ? 1U : 0U;
            if (game.ram[0x0fU + i] == 0U) selected = i;
        }
        expected = game;
        expected.ram[0x78fU] = 0x80U;
        expected.ram[0x6d1U] = (mysmb_u8)(value + 1U);
        if (expected.ram[0x6d1U] >= 7U && selected < 5U) {
            expected.ram[0x6d1U] = 0U;
            expected.ram[0x16U + selected] = 0x11U;
            expected.ram[0x1eU + selected] = 0U;
            expected.ram[0x58U + selected] = 0U;
            expected.ram[0x46U + selected] = 2U;
            expected.ram[0xa0U + selected] = 0U;
            expected.ram[0x434U + selected] = 0U;
            expected.ram[0x49aU + selected] = 8U;
            expected.ram[0xcfU + selected] = 0x20U;
            expected.ram[0x87U + selected] = (mysmb_u8)(value + 32U);
            expected.ram[0x6eU + selected] = value >= 224U ? 0U : 0xffU;
            expected.ram[0xb6U + selected] = 1U;
            expected.ram[0x0fU + selected] = 1U;
            expected.ram[0x401U + selected] = 0U;
        }
        if (compare(slot, "allocation")) return 2;
    }
    for (slot = 0U; slot < 5U; ++slot)
    for (lakitu = 0U; lakitu < 5U; ++lakitu) {
        if (slot == lakitu) continue;
        for (seed = 0U; seed < 4U; ++seed)
        for (value = 0U; value < 256U; ++value)
        for (gate = 0U; gate < 3U; ++gate) {
            reset(slot);
            game.ram[0x16U + lakitu] = 0x11U;
            /* ID search must work even when the Lakitu flag is zero. */
            game.ram[0x0fU + lakitu] = (mysmb_u8)(value & 1U);
            game.ram[0x1eU + lakitu] = gate == 1U ? 1U : 0U;
            game.ram[0xceU] = gate == 2U ? 0x2bU : 0x2cU;
            game.ram[0xcfU + lakitu] = (mysmb_u8)value;
            game.ram[0x57U] = (mysmb_u8)value;
            game.ram[0x7a7U + slot] = (mysmb_u8)seed;
            game.ram[0x7a8U + slot] = (mysmb_u8)(value & 3U);
            expected = game;
            expected.ram[0x78fU] = 0x80U;
            if (gate == 0U) {
                expected.ram[0x6eU + slot] = game.ram[0x6eU + lakitu];
                expected.ram[0x87U + slot] = game.ram[0x87U + lakitu];
                expected.ram[0xb6U + slot] = 1U;
                expected.ram[0xcfU + slot] = (mysmb_u8)(value - 8U);
                for (i = 0U; i < 3U; ++i) expected.ram[1U + i] = table[i][seed];
                (void)mysmb_enemy_player_lakitu_difference(&expected, (mysmb_u8)slot);
                expected.ram[0x49aU + slot] = 9U;
                expected.ram[0x434U + slot] = 0U;
                expected.ram[0x58U + slot] = 0U;
                expected.ram[0x46U + slot] = 1U;
                expected.ram[0xa0U + slot] = 0xfdU;
                expected.ram[0x0fU + slot] = 1U;
                expected.ram[0x1eU + slot] = 5U;
            }
            if (compare(slot, "spiny")) return 3;
        }
    }
    printf("%u Lakitu/Spiny caller footprints match; distance child not certified\n", cases);
    return 0;
}
