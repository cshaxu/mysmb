#include "core/oam/oam.h"
#include "core/oam/enemy_offscreen_tail.h"
#include "core/objects.h"

enum {
    MYSMB_PODOBOO_FLAG = 0x000fU,
    MYSMB_PODOBOO_ID = 0x0016U,
    MYSMB_PODOBOO_DIRECTION = 0x0046U,
    MYSMB_PODOBOO_X = 0x0087U,
    MYSMB_PODOBOO_Y = 0x00cfU,
    MYSMB_PODOBOO_Y_SPEED = 0x00a0U,
    MYSMB_PODOBOO_REL_X = 0x03aeU,
    MYSMB_PODOBOO_REL_Y = 0x03b9U,
    MYSMB_PODOBOO_OFFSCREEN = 0x03d1U,
    MYSMB_PODOBOO_ATTRIBUTES = 0x03c5U,
    MYSMB_PODOBOO_SPRITE = 0x06e5U,
    MYSMB_PODOBOO_SCREEN_X = 0x071cU
};

static void mysmb_podoboo_apply_offscreen(struct mysmb_game *game,
                                           mysmb_u8 oam, mysmb_u8 bits)
{
    mysmb_oam_enemy_offscreen_tail(game, oam, bits);
}

/* ROM EnemyGfxHandler/DrawEnemyObject Podoboo branch. */
mysmb_u8 mysmb_objects_draw_podoboo(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 tiles[6] =
        { 0xfcU, 0xfcU, 0xd0U, 0xd0U, 0xd7U, 0xd7U };
    mysmb_u8 direction;
    mysmb_u8 offscreen;
    mysmb_u8 oam;
    mysmb_u8 row;
    mysmb_u8 offset;
    mysmb_u8 y;
    mysmb_u8 attributes;
    mysmb_u8 left;
    mysmb_u8 right;

    if (game->ram[MYSMB_PODOBOO_FLAG + slot] == 0U ||
        game->ram[MYSMB_PODOBOO_ID + slot] != 12U) return 0U;
    game->ram[MYSMB_PODOBOO_ATTRIBUTES + slot] = 0U;
    game->ram[MYSMB_PODOBOO_REL_X] = (mysmb_u8)(
        game->ram[MYSMB_PODOBOO_X + slot] - game->ram[MYSMB_PODOBOO_SCREEN_X]);
    game->ram[MYSMB_PODOBOO_REL_Y] = game->ram[MYSMB_PODOBOO_Y + slot];
    offscreen = mysmb_objects_get_enemy_offscreen_bits(game, slot);
    game->ram[MYSMB_PODOBOO_OFFSCREEN] = offscreen;
    direction = game->ram[MYSMB_PODOBOO_DIRECTION + slot];
    oam = game->ram[MYSMB_PODOBOO_SPRITE + slot];
    attributes = 2U;
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
        y = (mysmb_u8)(game->ram[MYSMB_PODOBOO_REL_Y] + row * 8U);
        game->ram[0x0200U + offset] = y;
        game->ram[0x0204U + offset] = y;
        game->ram[0x0202U + offset] = attributes;
        game->ram[0x0206U + offset] = attributes;
        game->ram[0x0203U + offset] = game->ram[MYSMB_PODOBOO_REL_X];
        game->ram[0x0207U + offset] =
            (mysmb_u8)(game->ram[MYSMB_PODOBOO_REL_X] + 8U);
    }
    if (game->ram[MYSMB_PODOBOO_Y_SPEED + slot] < 0x80U) {
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
    mysmb_podoboo_apply_offscreen(game, oam, offscreen);
    mysmb_text_observer_record(game,MYSMB_TEXT_OBSERVE_ENEMY,12U,slot,
        0xccU,direction,oam,6U,255U);
    return 1U;
}

/* Shared RunNormalEnemies graphics dispatch for translated special enemies. */
mysmb_u8 mysmb_objects_draw_special_enemy(struct mysmb_game *game, mysmb_u8 slot)
{
    if (mysmb_objects_draw_aquatic_enemy(game, slot) != 0U) return 1U;
    return mysmb_objects_draw_podoboo(game, slot);
}
