#include "game/objects.h"

/* ROM DrawSmallPlatform.  The caller invokes this after the source-equivalent
 * collision phase and before MoveSmallPlatform changes the world position. */
enum {
    MYSMB_SMALL_PLATFORM_ENEMY_X = 0x0087U,
    MYSMB_SMALL_PLATFORM_ENEMY_Y = 0x00cfU,
    MYSMB_SMALL_PLATFORM_REL_X = 0x03aeU,
    MYSMB_SMALL_PLATFORM_REL_Y = 0x03b9U,
    MYSMB_SMALL_PLATFORM_OFFSCREEN = 0x03d1U,
    MYSMB_SMALL_PLATFORM_SPRITE_OFFSET = 0x06e5U,
    MYSMB_SMALL_PLATFORM_SCREEN_LEFT_X = 0x071cU
};

void mysmb_objects_draw_small_platform(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 oam;
    mysmb_u8 x;
    mysmb_u8 y;
    mysmb_u8 offscreen;
    mysmb_u8 column;

    game->ram[MYSMB_SMALL_PLATFORM_REL_X + slot] = (mysmb_u8)(
        game->ram[MYSMB_SMALL_PLATFORM_ENEMY_X + slot] -
        game->ram[MYSMB_SMALL_PLATFORM_SCREEN_LEFT_X]);
    game->ram[MYSMB_SMALL_PLATFORM_REL_Y + slot] =
        game->ram[MYSMB_SMALL_PLATFORM_ENEMY_Y + slot];
    game->ram[MYSMB_SMALL_PLATFORM_OFFSCREEN + slot] =
        mysmb_objects_get_enemy_x_offscreen_bits(game, slot);
    oam = game->ram[MYSMB_SMALL_PLATFORM_SPRITE_OFFSET + slot];
    x = game->ram[MYSMB_SMALL_PLATFORM_REL_X + slot];
    y = game->ram[MYSMB_SMALL_PLATFORM_REL_Y + slot];
    offscreen = game->ram[MYSMB_SMALL_PLATFORM_OFFSCREEN + slot];

    for (column = 0U; column < 3U; ++column) {
        mysmb_u8 row_offset;
        mysmb_u8 column_x;
        mysmb_u8 first_y;
        mysmb_u8 second_y;

        row_offset = (mysmb_u8)(oam + column * 4U);
        column_x = (mysmb_u8)(x + column * 8U);
        first_y = y < 0x20U ? 0xf8U : y;
        second_y = (mysmb_u8)(y + 0x80U);
        if (second_y < 0x20U) second_y = 0xf8U;
        if ((offscreen & (mysmb_u8)(8U >> column)) != 0U) {
            first_y = 0xf8U;
            second_y = 0xf8U;
        }
        game->ram[0x0200U + row_offset] = first_y;
        game->ram[0x0201U + row_offset] = 0x5bU;
        game->ram[0x0202U + row_offset] = 2U;
        game->ram[0x0203U + row_offset] = column_x;
        row_offset = (mysmb_u8)(oam + 12U + column * 4U);
        game->ram[0x0200U + row_offset] = second_y;
        game->ram[0x0201U + row_offset] = 0x5bU;
        game->ram[0x0202U + row_offset] = 2U;
        game->ram[0x0203U + row_offset] = column_x;
    }
}