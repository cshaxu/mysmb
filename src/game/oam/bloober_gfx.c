#include "game/oam/oam.h"
#include "game/objects.h"

enum {
    MYSMB_BLOOBER_FLAG = 0x000fU,
    MYSMB_BLOOBER_ID = 0x0016U,
    MYSMB_BLOOBER_STATE = 0x001eU,
    MYSMB_BLOOBER_DIRECTION = 0x0046U,
    MYSMB_BLOOBER_X = 0x0087U,
    MYSMB_BLOOBER_Y_HIGH = 0x00b6U,
    MYSMB_BLOOBER_Y = 0x00cfU,
    MYSMB_BLOOBER_REL_X = 0x03aeU,
    MYSMB_BLOOBER_REL_Y = 0x03b9U,
    MYSMB_BLOOBER_OFFSCREEN = 0x03d1U,
    MYSMB_BLOOBER_ATTRIBUTES = 0x03c5U,
    MYSMB_BLOOBER_SPRITE = 0x06e5U,
    MYSMB_BLOOBER_INTERVAL = 0x0796U,
    MYSMB_BLOOBER_TIMER_CONTROL = 0x0747U,
    MYSMB_BLOOBER_FRAME = 0x0009U,
    MYSMB_BLOOBER_SCREEN_X = 0x071cU
};

static void mysmb_bloober_hide_offscreen_rows(struct mysmb_game *game,
                                                mysmb_u8 oam,
                                                mysmb_u8 offscreen)
{
    mysmb_u8 row;

    for (row = 0U; row < 3U; ++row) {
        mysmb_u8 offset;
        if ((offscreen & 0x80U) == 0U &&
            !((offscreen & 0x40U) != 0U && row >= 1U) &&
            !((offscreen & 0x20U) != 0U && row == 2U)) continue;
        offset = (mysmb_u8)(oam + row * 8U);
        game->ram[0x0200U + offset] = 0xf8U;
        game->ram[0x0204U + offset] = 0xf8U;
    }
    for (row = 0U; row < 3U; ++row) {
        mysmb_u8 offset = (mysmb_u8)(oam + row * 8U);
        if ((offscreen & 8U) != 0U) game->ram[0x0200U + offset] = 0xf8U;
        if ((offscreen & 4U) != 0U) game->ram[0x0204U + offset] = 0xf8U;
    }
}

/* ROM EnemyGfxHandler/DrawEnemyObject Bloober branch. */
mysmb_u8 mysmb_objects_draw_bloober(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 first_frame[6] =
        { 0xfcU, 0xfcU, 0xdcU, 0xdcU, 0xdfU, 0xdfU };
    static const mysmb_u8 second_frame[6] =
        { 0xdcU, 0xdcU, 0xddU, 0xddU, 0xdeU, 0xdeU };
    const mysmb_u8 *tiles;
    mysmb_u8 state;
    mysmb_u8 direction;
    mysmb_u8 offscreen;
    mysmb_u8 oam;
    mysmb_u8 row;
    mysmb_u8 offset;
    mysmb_u8 y;
    mysmb_u8 left;
    mysmb_u8 right;
    mysmb_u8 attributes;

    if (game->ram[MYSMB_BLOOBER_FLAG + slot] == 0U ||
        game->ram[MYSMB_BLOOBER_ID + slot] != 7U) return 0U;
    /* RunNormalEnemies initializes this before EnemyGfxHandler. */
    game->ram[MYSMB_BLOOBER_ATTRIBUTES + slot] = 0U;
    state = game->ram[MYSMB_BLOOBER_STATE + slot];
    game->ram[MYSMB_BLOOBER_REL_X + slot] = (mysmb_u8)(
        game->ram[MYSMB_BLOOBER_X + slot] - game->ram[MYSMB_BLOOBER_SCREEN_X]);
    y = game->ram[MYSMB_BLOOBER_Y + slot];
    tiles = first_frame;
    if (game->ram[MYSMB_BLOOBER_INTERVAL + slot] < 5U &&
        game->ram[MYSMB_BLOOBER_INTERVAL + slot] != 1U) {
        y = (mysmb_u8)(y + 3U);
        if ((state & 0xa0U) == 0U &&
            game->ram[MYSMB_BLOOBER_TIMER_CONTROL] == 0U) {
            tiles = second_frame;
        }
    }
    game->ram[MYSMB_BLOOBER_REL_Y + slot] = y;
    offscreen = mysmb_objects_get_enemy_x_offscreen_bits(game, slot);
    game->ram[MYSMB_BLOOBER_OFFSCREEN + slot] = offscreen;
    direction = game->ram[MYSMB_BLOOBER_DIRECTION + slot];
    oam = game->ram[MYSMB_BLOOBER_SPRITE + slot];
    attributes = 3U;
    for (row = 0U; row < 3U; ++row) {
        offset = (mysmb_u8)(oam + row * 8U);
        left = tiles[row * 2U];
        right = tiles[row * 2U + 1U];
        if ((direction & 2U) != 0U) {
            game->ram[0x0201U + offset] = right;
            game->ram[0x0205U + offset] = left;
        }
        else {
            game->ram[0x0201U + offset] = left;
            game->ram[0x0205U + offset] = right;
        }
        y = (mysmb_u8)(game->ram[MYSMB_BLOOBER_REL_Y + slot] + row * 8U);
        game->ram[0x0200U + offset] = y;
        game->ram[0x0204U + offset] = y;
        game->ram[0x0202U + offset] = attributes;
        game->ram[0x0206U + offset] = attributes;
        game->ram[0x0203U + offset] = game->ram[MYSMB_BLOOBER_REL_X + slot];
        game->ram[0x0207U + offset] =
            (mysmb_u8)(game->ram[MYSMB_BLOOBER_REL_X + slot] + 8U);
    }
    if ((state & 0x20U) != 0U) {
        for (row = 0U; row < 3U; ++row) {
            offset = (mysmb_u8)(oam + row * 8U);
            game->ram[0x0202U + offset] |= 0x80U;
            game->ram[0x0206U + offset] |= 0x80U;
        }
        left = game->ram[0x0209U + oam];
        right = game->ram[0x020dU + oam];
        game->ram[0x0209U + oam] = game->ram[0x0211U + oam];
        game->ram[0x020dU + oam] = game->ram[0x0215U + oam];
        game->ram[0x0211U + oam] = left;
        game->ram[0x0215U + oam] = right;
    }
    attributes = (mysmb_u8)(game->ram[0x0202U + oam] & 0xa3U);
    for (row = 0U; row < 3U; ++row) {
        offset = (mysmb_u8)(oam + row * 8U);
        game->ram[0x0202U + offset] = attributes;
        game->ram[0x0206U + offset] = (mysmb_u8)(attributes | 0x40U);
    }
    mysmb_bloober_hide_offscreen_rows(game, oam, offscreen);
    if ((offscreen & 0x80U) != 0U &&
        game->ram[MYSMB_BLOOBER_Y_HIGH + slot] == 2U) {
        game->ram[MYSMB_BLOOBER_FLAG + slot] = 0U;
    }
    return 1U;
}

/* Shared RunNormalEnemies graphics dispatch for water enemies. */
mysmb_u8 mysmb_objects_draw_aquatic_enemy(struct mysmb_game *game, mysmb_u8 slot)
{
    if (mysmb_objects_draw_cheep_cheep(game, slot) != 0U) return 1U;
    return mysmb_objects_draw_bloober(game, slot);
}


