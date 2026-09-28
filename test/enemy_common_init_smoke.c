#include "game/enemy/init_targets.h"
#include <stdio.h>
#include <string.h>

/* Independent full-RAM write-footprint contract for the common entries.
 * Sentinel state deliberately differs from freshly zeroed stream objects. */
typedef void (*initializer)(struct mysmb_game *, mysmb_u8);
static void expected_box(unsigned char *ram, unsigned int slot, unsigned char box)
{
    ram[0x49aU + slot] = box;
    ram[0x46U + slot] = 2U;
    ram[0xa0U + slot] = 0U;
    ram[0x434U + slot] = 0U;
}

int main(void)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    static const unsigned char ids[15] = {
        0U,1U,2U,3U,5U,6U,7U,8U,10U,11U,12U,15U,16U,17U,53U
    };
    static initializer entries[15] = {
        mysmb_enemy_init_normal, mysmb_enemy_init_normal, mysmb_enemy_init_normal,
        mysmb_enemy_init_red_koopa, mysmb_enemy_init_hammer_bro,
        mysmb_enemy_init_goomba, mysmb_enemy_init_bloober,
        mysmb_enemy_init_bullet_bill, mysmb_enemy_init_cheep_cheep,
        mysmb_enemy_init_cheep_cheep, mysmb_enemy_init_podoboo,
        mysmb_enemy_init_red_ptroopa, mysmb_enemy_init_horizontal_fly_swim,
        mysmb_enemy_init_lakitu, mysmb_enemy_init_retainer
    };
    static const unsigned short erase_fields[8] = {
        0x0fU,0x16U,0x1eU,0x110U,0x796U,0x125U,0x3c5U,0x78aU
    };
    unsigned int i, slot, value, j, cases;
    unsigned char id, speed;
    cases = 0U;
    for (i = 0U; i < 15U; ++i) for (slot = 0U; slot < 6U; ++slot)
    for (value = 0U; value < 256U; ++value) {
        memset(&game, 0, sizeof(game));
        memset(game.ram, 0xa5, sizeof(game.ram));
        id = ids[i];
        game.ram[0x16U + slot] = id;
        game.ram[0xcfU + slot] = (mysmb_u8)value;
        game.ram[0x76aU] = (mysmb_u8)(value & 2U);
        game.ram[0x6ccU] = (mysmb_u8)(value & 1U);
        game.ram[0x6cbU] = (mysmb_u8)(value & 0x20U);
        game.ram[0x7a7U + slot] = (mysmb_u8)value;
        memcpy(expected, game.ram, sizeof(expected));
        speed = (value & 2U) ? 0xf4U : 0xf8U;
        switch (id) {
        case 0U: case 1U: case 2U: case 3U: case 6U:
            expected[0x58U + slot] = speed;
            expected_box(expected, slot, id == 6U ? 9U : 3U);
            if (id == 3U) expected[0x1eU + slot] = 1U;
            break;
        case 5U:
            expected[0x3a2U + slot] = 0U;
            expected[0x58U + slot] = 0U;
            expected[0x796U + slot] = (value & 1U) ? 0x50U : 0x80U;
            expected_box(expected, slot, 11U);
            break;
        case 7U:
            expected[0x58U + slot] = 0U;
            expected_box(expected, slot, 9U);
            break;
        case 8U:
            expected[0x46U + slot] = 2U;
            expected[0x49aU + slot] = 9U;
            break;
        case 10U: case 11U:
            expected_box(expected, slot, 9U);
            expected[0x58U + slot] = (unsigned char)(value & 0x10U);
            expected[0x434U + slot] = (unsigned char)value;
            break;
        case 12U:
            expected[0xb6U + slot] = 2U;
            expected[0xcfU + slot] = 2U;
            expected[0x796U + slot] = 1U;
            expected[0x1eU + slot] = 0U;
            expected_box(expected, slot, 9U);
            break;
        case 15U:
            expected[0x401U + slot] = (unsigned char)value;
            expected[0x58U + slot] = (unsigned char)
                (value < 128U ? value + 48U : value - 32U);
            expected_box(expected, slot, 3U);
            break;
        case 16U:
            expected[0x58U + slot] = 0U;
            expected_box(expected, slot, 3U);
            break;
        case 17U:
            if (value & 0x20U) {
                for (j = 0U; j < 8U; ++j) expected[erase_fields[j] + slot] = 0U;
            } else {
                expected[0x6d1U] = 0U;
                expected[0x58U + slot] = 0U;
                expected_box(expected, slot, 3U);
            }
            break;
        case 53U:
            expected[0xcfU + slot] = 0xb8U;
            break;
        }
        entries[i](&game, (mysmb_u8)slot);
        if (memcmp(game.ram, expected, sizeof(expected))) {
            printf("id=%u slot=%u value=%u footprint mismatch\n",
                   (unsigned int)id, slot, value);
            return 1;
        }
        ++cases;
    }
    /* SetupLakitu is a distinct entry: it must bypass the frenzy rejection. */
    for (slot = 0U; slot < 6U; ++slot) {
        memset(&game, 0, sizeof(game));
        memset(game.ram, 0xa5, sizeof(game.ram));
        game.ram[0x6cbU] = 0x11U;
        memcpy(expected, game.ram, sizeof(expected));
        expected[0x6d1U] = 0U;
        expected[0x58U + slot] = 0U;
        expected_box(expected, slot, 3U);
        mysmb_enemy_setup_lakitu(&game, (mysmb_u8)slot);
        if (memcmp(game.ram, expected, sizeof(expected))) return 2;
        ++cases;
    }
    printf("%u common initializer footprints match\n", cases);
    return 0;
}
