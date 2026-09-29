#include "game/game.h"
#include "game/oam/oam.h"
#include "game/objects.h"

enum {
    MYSMB_BULLET_ENEMY_MOVING_DIRECTION = 0x0046,
    MYSMB_BULLET_ENEMY_X = 0x0087,
    MYSMB_BULLET_ENEMY_Y = 0x00cf,
    MYSMB_BULLET_ENEMY_ATTRIBUTES = 0x03c5,
    MYSMB_BULLET_ENEMY_SPRITE_OFFSET = 0x06e5,
    MYSMB_BULLET_SCREEN_LEFT_X = 0x071c
};
/* ROM BulletBillHandler -> EnemyGfxHandler -> DrawEnemyObject. */
void mysmb_objects_draw_bullet_bill(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 tiles[6] = { 0xfcU, 0xfcU, 0xe8U, 0xe7U, 0xeaU, 0xe9U };
    mysmb_u8 row;
    mysmb_u8 offset;
    mysmb_u8 attributes;
    mysmb_u8 direction;
    mysmb_u8 x;
    mysmb_u8 y;
    mysmb_u8 offscreen;
    mysmb_u8 left_y;
    mysmb_u8 right_y;

    offset = game->ram[MYSMB_BULLET_ENEMY_SPRITE_OFFSET + slot];
    x = (mysmb_u8)(game->ram[MYSMB_BULLET_ENEMY_X + slot] - game->ram[MYSMB_BULLET_SCREEN_LEFT_X]);
    y = game->ram[MYSMB_BULLET_ENEMY_Y + slot];
    direction = game->ram[MYSMB_BULLET_ENEMY_MOVING_DIRECTION + slot];
    attributes = (mysmb_u8)(3U | game->ram[MYSMB_BULLET_ENEMY_ATTRIBUTES + slot]);
    if (game->ram[0x0016U + slot] == 0x33U) {
        /* CheckForBulletBillCV/SBBAt: cannon variant reuses graphics ID 8,
         * zero state and its own priority attributes. The enclosing source
         * graphics handoff keeps these working bytes, not just OAM tiles. */
        y = (mysmb_u8)(y - 1U);
        attributes = game->ram[0x078aU + slot] != 0U ? 0x23U : 3U;
        x = game->ram[0x03aeU];
        offscreen = game->ram[0x03d1U];
        game->ram[0x00ebU] = offset;
        game->ram[0x00ecU] = 0U;
        game->ram[0x00edU] = 0U;
        game->ram[0x00efU] = 8U;
        game->ram[0x0109U] = 0U;
    }
    else offscreen = mysmb_objects_get_enemy_x_offscreen_bits(game, slot);
    for (row = 0U; row < 3U; ++row) {
        mysmb_u8 row_offset;
        mysmb_u8 left;
        mysmb_u8 right;

        row_offset = (mysmb_u8)(offset + row * 8U);
        left = tiles[row * 2U];
        right = tiles[row * 2U + 1U];
        if ((direction & 2U) != 0U) {
            game->ram[0x0201U + row_offset] = right;
            game->ram[0x0205U + row_offset] = left;
            game->ram[0x0202U + row_offset] = (mysmb_u8)(attributes | 0x40U);
            game->ram[0x0206U + row_offset] = (mysmb_u8)(attributes | 0x40U);
        } else {
            game->ram[0x0201U + row_offset] = left;
            game->ram[0x0205U + row_offset] = right;
            game->ram[0x0202U + row_offset] = attributes;
            game->ram[0x0206U + row_offset] = attributes;
        }
        left_y = (mysmb_u8)(y + row * 8U);
        right_y = left_y;
        if ((offscreen & (0x80U >> row)) != 0U) {
            left_y = 0xf8U;
            right_y = 0xf8U;
        } else {
            if ((offscreen & 8U) != 0U) left_y = 0xf8U;
            if ((offscreen & 4U) != 0U) right_y = 0xf8U;
        }
        game->ram[0x0200U + row_offset] = left_y;
        game->ram[0x0204U + row_offset] = right_y;
        game->ram[0x0203U + row_offset] = x;
        game->ram[0x0207U + row_offset] = (mysmb_u8)(x + 8U);
    }
}



