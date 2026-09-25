#include "game/oam/oam.h"
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
/* ROM DrawLargePlatform.  GetXOffscreenBits is repeated here because this
 * owner consumes its unshifted six-column mask directly. */
static mysmb_u8 mysmb_large_platform_x_offscreen(const struct mysmb_game *game,
                                                  mysmb_u8 slot)
{
    static const mysmb_u8 bits[16] = {
        0x7fU, 0x3fU, 0x1fU, 0x0fU, 0x07U, 0x03U, 0x01U, 0x00U,
        0x80U, 0xc0U, 0xe0U, 0xf0U, 0xf8U, 0xfcU, 0xfeU, 0xffU
    };
    mysmb_u8 edge;
    mysmb_u8 difference;
    mysmb_u8 borrow;
    mysmb_u8 page_difference;
    mysmb_u8 index;

    edge = 1U;
    for (;;) {
        difference = (mysmb_u8)(game->ram[MYSMB_SMALL_PLATFORM_SCREEN_LEFT_X + edge] -
                                game->ram[MYSMB_SMALL_PLATFORM_ENEMY_X + slot]);
        borrow = game->ram[MYSMB_SMALL_PLATFORM_SCREEN_LEFT_X + edge] <
            game->ram[MYSMB_SMALL_PLATFORM_ENEMY_X + slot] ? 1U : 0U;
        page_difference = (mysmb_u8)(game->ram[0x071aU + edge] -
            game->ram[0x006eU + slot] - borrow);
        index = edge != 0U ? 15U : 7U;
        if ((page_difference & 0x80U) == 0U) {
            index = edge != 0U ? 7U : 15U;
            if (page_difference == 0U && difference < 0x38U) {
                index = (mysmb_u8)(difference >> 3U);
                if (edge == 0U) index = (mysmb_u8)(index + 8U);
            }
        }
        if (bits[index] != 0U || edge == 0U) return bits[index];
        edge = 0U;
    }
}

void mysmb_objects_draw_large_platform(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 oam;
    mysmb_u8 x;
    mysmb_u8 y;
    mysmb_u8 tile;
    mysmb_u8 offscreen;
    mysmb_u8 column;

    game->ram[MYSMB_SMALL_PLATFORM_REL_X + slot] = (mysmb_u8)(
        game->ram[MYSMB_SMALL_PLATFORM_ENEMY_X + slot] -
        game->ram[MYSMB_SMALL_PLATFORM_SCREEN_LEFT_X]);
    game->ram[MYSMB_SMALL_PLATFORM_REL_Y + slot] =
        game->ram[MYSMB_SMALL_PLATFORM_ENEMY_Y + slot];
    oam = game->ram[MYSMB_SMALL_PLATFORM_SPRITE_OFFSET + slot];
    x = game->ram[MYSMB_SMALL_PLATFORM_REL_X + slot];
    y = game->ram[MYSMB_SMALL_PLATFORM_REL_Y + slot];
    tile = game->ram[0x0743U] != 0U ? 0x75U : 0x5bU;
    offscreen = mysmb_large_platform_x_offscreen(game, slot);

    for (column = 0U; column < 6U; ++column) {
        mysmb_u8 row_offset;
        mysmb_u8 column_y;

        row_offset = (mysmb_u8)(oam + column * 4U);
        column_y = y;
        if (column >= 4U &&
            (game->ram[0x074eU] == 3U || game->ram[0x06ccU] != 0U)) {
            column_y = 0xf8U;
        }
        if ((offscreen & (mysmb_u8)(0x80U >> column)) != 0U) column_y = 0xf8U;
        game->ram[0x0200U + row_offset] = column_y;
        game->ram[0x0201U + row_offset] = tile;
        game->ram[0x0202U + row_offset] = 2U;
        game->ram[0x0203U + row_offset] = (mysmb_u8)(x + column * 8U);
    }
}


