#include "game/objects.h"

enum {
    MYSMB_VINE_ENEMY_X = 0x0087U,
    MYSMB_VINE_ENEMY_Y = 0x00cfU,
    MYSMB_VINE_ENEMY_SPRITE_OFFSET = 0x06e5U,
    MYSMB_VINE_OBJECT_OFFSET = 0x039aU,
    MYSMB_VINE_START_Y = 0x039dU,
    MYSMB_VINE_SCREEN_LEFT_X = 0x071cU
};

/* ROM DrawVine ($d69f-$d6fc).  Each active vine stack owns six consecutive
 * OAM entries.  The top stack has the distinct $e0 cap; the remaining leaves
 * are $e1 with the original alternating horizontal position and flip bit. */
void mysmb_objects_draw_vine(struct mysmb_game *game, mysmb_u8 vine_index)
{
    static const mysmb_u8 y_adder[2] = { 0U, 0x30U };
    mysmb_u8 sprite_slot;
    mysmb_u8 oam;
    mysmb_u8 x;
    mysmb_u8 y;
    mysmb_u8 row;

    if (vine_index >= 2U) return;
    sprite_slot = game->ram[MYSMB_VINE_OBJECT_OFFSET + vine_index];
    if (sprite_slot >= 6U) return;
    oam = game->ram[MYSMB_VINE_ENEMY_SPRITE_OFFSET + sprite_slot];
    x = (mysmb_u8)(game->ram[MYSMB_VINE_ENEMY_X + 5U] -
                    game->ram[MYSMB_VINE_SCREEN_LEFT_X]);
    y = (mysmb_u8)(game->ram[MYSMB_VINE_ENEMY_Y + 5U] + y_adder[vine_index]);

    for (row = 0U; row < 6U; ++row) {
        mysmb_u8 row_oam;
        mysmb_u8 row_y;

        row_oam = (mysmb_u8)(oam + row * 4U);
        row_y = (mysmb_u8)(y + row * 8U);
        if (row_y <= game->ram[MYSMB_VINE_START_Y] &&
            (mysmb_u8)(game->ram[MYSMB_VINE_START_Y] - row_y) >= 0x64U) {
            row_y = 0xf8U;
        }
        game->ram[(mysmb_u16)(0x0200U + row_oam)] = row_y;
        game->ram[(mysmb_u16)(0x0201U + row_oam)] =
            vine_index == 0U && row == 0U ? 0xe0U : 0xe1U;
        game->ram[(mysmb_u16)(0x0202U + row_oam)] =
            (mysmb_u8)((row & 1U) == 0U ? 0x21U : 0x61U);
        game->ram[(mysmb_u16)(0x0203U + row_oam)] =
            (mysmb_u8)(x + ((row & 1U) == 0U ? 0U : 6U));
    }
}