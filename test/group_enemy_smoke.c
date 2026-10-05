#include "core/enemy/group.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game;
static unsigned char expected[2048];

int main(void)
{
    unsigned int group, hard, occupied, x, variant, slot, species, count;
    unsigned int position, y, made;
    unsigned long cases;
    cases = 0UL;
    for (group = 0U; group < 8U; ++group)
    for (hard = 0U; hard < 2U; ++hard)
    for (occupied = 0U; occupied < 32U; ++occupied)
    for (variant = 0U; variant < 2U; ++variant)
    for (x = 0U; x < 256U; ++x) {
        memset(&game, 0, sizeof(game));
        memset(game.ram, 0xa5, sizeof(game.ram));
        game.ram[8U] = 5U;
        game.ram[0x71bU] = variant == 0U ? 0U : 255U;
        game.ram[0x71dU] = (mysmb_u8)x;
        game.ram[0x76aU] = (mysmb_u8)hard;
        game.ram[0x739U] = (mysmb_u8)x;
        for (slot = 0U; slot < 5U; ++slot)
            game.ram[0x0fU + slot] = (occupied & (1U << slot)) ? 0x81U : 0U;
        game.ram[0x14U] = 0U;
        memcpy(expected, game.ram, sizeof(expected));
        species = group < 4U ? (hard ? 2U : 6U) : 0U;
        count = group % 2U + 2U;
        y = (group & 2U) ? 0x70U : 0xb0U;
        expected[0U] = (unsigned char)y;
        expected[1U] = (unsigned char)species;
        position = (unsigned int)expected[0x71bU] * 256U + x;
        made = 0U;
        for (slot = 0U; slot < 5U && made < count; ++slot) {
            if (occupied & (1U << slot)) continue;
            expected[0x16U + slot] = (unsigned char)species;
            expected[0x6eU + slot] = (unsigned char)(position / 256U);
            expected[0x87U + slot] = (unsigned char)position;
            position = (position + 24U) & 0xffffU;
            expected[0xcfU + slot] = (unsigned char)(y + 8U);
            expected[0xb6U + slot] = 1U;
            expected[0x0fU + slot] = 1U;
            expected[0x3d8U + slot] = 1U;
            expected[4U] = 0x81U; expected[5U] = 0xc2U;
            expected[6U] = species == 6U ? 0xf1U : 0x0eU;
            expected[7U] = species == 6U ? 0xc2U : 0xc3U;
            expected[0x58U + slot] = hard ? 0xf4U : 0xf8U;
            expected[0x49aU + slot] = species == 6U ? 9U : 3U;
            expected[0x46U + slot] = 2U;
            expected[0xa0U + slot] = 0U;
            expected[0x434U + slot] = 0U;
            ++made;
        }
        expected[2U] = (unsigned char)(position / 256U);
        expected[3U] = (unsigned char)position;
        expected[0x6d3U] = (unsigned char)(count - made);
        expected[0x739U] = (unsigned char)(x + 2U);
        expected[0x73bU] = 0U;
        mysmb_enemy_stream_handle_group(&game, (mysmb_u8)(group + 0x37U));
        if (memcmp(expected, game.ram, sizeof(expected))) return 1;
        ++cases;
    }
    printf("%lu grouped-enemy footprints match\n", cases);
    return 0;
}
