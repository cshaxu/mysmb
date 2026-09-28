#include "game/enemy/init.h"
#include "game/enemy/init_targets.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game game;
static unsigned char expected[2048];

int main(void)
{
    unsigned int kind, value, variant, slot, y, world, hard, area, alignment;
    unsigned long cases;
    cases = 0UL;
    for (kind = 0U; kind < 10U; ++kind)
    for (slot = 0U; slot < 6U; ++slot)
    for (variant = 0U; variant < 16U; ++variant)
    for (value = 0U; value < 256U; ++value) {
        memset(game.ram, 0x39, 2048U);
        hard = variant & 1U; area = (variant / 2U) % 4U;
        y = (value * 37U) & 255U; alignment = (value + variant) & 255U;
        world = (variant & 8U ? 0xff00U : 0U) + value;
        game.ram[0x6ccU] = (unsigned char)hard;
        game.ram[0x74eU] = (unsigned char)area;
        game.ram[0x3a0U] = (unsigned char)alignment;
        game.ram[0xcfU+slot] = (unsigned char)y;
        game.ram[0x87U+slot] = (unsigned char)world;
        game.ram[0x6eU+slot] = (unsigned char)(world >> 8U);
        game.ram[0x16U+slot] = (unsigned char)(kind < 9U ? 36U+kind : 54U);
        memcpy(expected, game.ram, 2048U);
        if (kind == 0U) {
            expected[0xcfU+slot] = (unsigned char)(y-2U);
            expected[0x1eU+slot] = (unsigned char)alignment;
            expected[0x3a0U] = (unsigned char)(alignment < 128U ? 255U : slot);
            expected[0x46U+slot] = 0U;
            if (hard) world = (world+8U) & 65535U;
        }
        if (kind == 1U) {
            expected[0x401U+slot] = (unsigned char)(y < 128U ? y : 256U-y);
            expected[0x58U+slot] = (unsigned char)(y + (y < 128U ? 64U : 192U));
        }
        if (kind == 4U || kind == 6U) expected[0x58U+slot] = 0U;
        if (kind == 0U || kind == 5U) expected[0x3a2U+slot] = 255U;
        if (kind < 9U) {
            expected[0x49aU+slot] = (unsigned char)(area == 3U || hard ? 5U : 6U);
            expected[0xa0U+slot] = 0U; expected[0x434U+slot] = 0U;
        }
        if (kind == 2U || kind == 3U || kind == 7U || kind == 8U) {
            world = (world+12U) & 65535U;
            expected[0xa0U+slot] = (unsigned char)(kind == 2U || kind == 7U ? 255U : 0U);
            expected[0x434U+slot] = (unsigned char)(kind == 2U || kind == 7U ? 16U : 240U);
            if (kind >= 7U) expected[0x49aU+slot] = 4U;
        }
        expected[0x87U+slot] = (unsigned char)world;
        expected[0x6eU+slot] = (unsigned char)(world >> 8U);
        switch (kind) {
        case 0U: mysmb_enemy_init_balance_platform(&game,(mysmb_u8)slot);break;
        case 1U: mysmb_enemy_init_vertical_platform(&game,(mysmb_u8)slot);break;
        case 2U: mysmb_enemy_init_large_lift_up(&game,(mysmb_u8)slot);break;
        case 3U: mysmb_enemy_init_large_lift_down(&game,(mysmb_u8)slot);break;
        case 4U: case 6U: mysmb_enemy_init_horizontal_platform(&game,(mysmb_u8)slot);break;
        case 5U: mysmb_enemy_init_drop_platform(&game,(mysmb_u8)slot);break;
        case 7U: mysmb_enemy_init_small_lift_up(&game,(mysmb_u8)slot);break;
        case 8U: mysmb_enemy_init_small_lift_down(&game,(mysmb_u8)slot);break;
        default:
            /* Verify the empty final vector target with its real caller. */
            expected[4] = 0x81U; expected[5] = 0xc2U;
            expected[6] = 0x81U; expected[7] = 0xc8U;
            mysmb_enemy_checkpoint_loaded(&game,(mysmb_u8)slot);break;
        }
        if (memcmp(expected, game.ram, 2048U)) {
            printf("platform contract kind=%u slot=%u variant=%u value=%u\n",
                   kind,slot,variant,value);
            return 1;
        }
        ++cases;
    }
    printf("platform initialization: %lu full-RAM contracts\n", cases);
    return 0;
}
