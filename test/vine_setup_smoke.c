#include "game/objects.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned int slot, block, count, seed, i, cases;
    cases = 0U;
    if (mysmb_vine_height_data[0] != 0x30U ||
        mysmb_vine_height_data[1] != 0x60U) return 1;
    for (slot = 0U; slot < 6U; ++slot)
    for (block = 0U; block < 2U; ++block)
    for (count = 0U; count < 256U; ++count)
    for (seed = 0U; seed < 4U; ++seed) {
        for (i = 0U; i < 2048U; ++i)
            game.ram[i] = (mysmb_u8)(i * 17U + seed * 83U);
        game.ram[0x0398U] = (mysmb_u8)count;
        memcpy(expected, game.ram, sizeof(expected));
        expected[0x16U + slot] = 0x2fU;
        expected[0xfU + slot] = 1U;
        expected[0x6eU + slot] = game.ram[0x76U + block];
        expected[0x87U + slot] = game.ram[0x8fU + block];
        expected[0xcfU + slot] = game.ram[0xd7U + block];
        if (count == 0U) expected[0x39dU] = game.ram[0xd7U + block];
        expected[0x39aU + count] = (mysmb_u8)slot;
        expected[0x398U] = (mysmb_u8)(count + 1U);
        expected[0xfeU] = 4U;
        mysmb_objects_start_vine(&game, (mysmb_u8)slot, (mysmb_u8)block);
        if (memcmp(game.ram, expected, sizeof(expected)) != 0) {
            printf("vine mismatch slot=%u block=%u count=%u seed=%u\n",
                   slot, block, count, seed);
            return 1;
        }
        ++cases;
    }
    printf("vine setup: %u cases, complete RAM write footprint preserved\n", cases);
    return 0;
}
