#include "game/objects.h"

enum {
    MYSMB_CHEEP_FLAG = 0x000fU,
    MYSMB_CHEEP_ID = 0x0016U,
    MYSMB_CHEEP_STATE = 0x001eU,
    MYSMB_CHEEP_DIRECTION = 0x0046U,
    MYSMB_CHEEP_X = 0x0087U,
    MYSMB_CHEEP_Y = 0x00cfU,
    MYSMB_CHEEP_REL_X = 0x03aeU,
    MYSMB_CHEEP_REL_Y = 0x03b9U,
    MYSMB_CHEEP_OFFSCREEN = 0x03d1U,
    MYSMB_CHEEP_ATTRIBUTES = 0x03c5U,
    MYSMB_CHEEP_SPRITE = 0x06e5U,
    MYSMB_CHEEP_TIMER_CONTROL = 0x0747U,
    MYSMB_CHEEP_FRAME = 0x0009U,
    MYSMB_CHEEP_SCREEN_X = 0x071cU
};

/* ROM EnemyGfxHandler/DrawEnemyObject Cheep-Cheep branch. */
mysmb_u8 mysmb_objects_draw_cheep_cheep(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 first_frame[6] =
        { 0xfcU, 0xfcU, 0xb2U, 0xb3U, 0xb4U, 0xb5U };
    static const mysmb_u8 second_frame[6] =
        { 0xfcU, 0xfcU, 0xb6U, 0xb3U, 0xb7U, 0xb5U };
    const mysmb_u8 *tiles;
    mysmb_u8 id;
    mysmb_u8 attributes;
    mysmb_u8 direction;
    mysmb_u8 offscreen;
    mysmb_u8 oam;
    mysmb_u8 row;
    mysmb_u8 row_offset;
    mysmb_u8 y;
    mysmb_u8 left;
    mysmb_u8 right;

    if (game->ram[MYSMB_CHEEP_FLAG + slot] == 0U) return 0U;
    id = game->ram[MYSMB_CHEEP_ID + slot];
    if (id != 10U && id != 11U) return 0U;
    /* RunNormalEnemies clears this before EnemyGfxHandler. */
    game->ram[MYSMB_CHEEP_ATTRIBUTES + slot] = 0U;
    game->ram[MYSMB_CHEEP_REL_X + slot] = (mysmb_u8)(
        game->ram[MYSMB_CHEEP_X + slot] - game->ram[MYSMB_CHEEP_SCREEN_X]);
    game->ram[MYSMB_CHEEP_REL_Y + slot] = game->ram[MYSMB_CHEEP_Y + slot];
    offscreen = mysmb_objects_get_enemy_x_offscreen_bits(game, slot);
    game->ram[MYSMB_CHEEP_OFFSCREEN + slot] = offscreen;
    /* CheckToAnimateEnemy advances six table bytes when frame bit 3 is clear
     * and neither the object state nor TimerControl suppresses animation. */
    tiles = first_frame;
    if ((game->ram[MYSMB_CHEEP_FRAME] & 8U) == 0U &&
        (game->ram[MYSMB_CHEEP_STATE + slot] & 0xa0U) == 0U &&
        game->ram[MYSMB_CHEEP_TIMER_CONTROL] == 0U) {
        tiles = second_frame;
    }
    attributes = (mysmb_u8)((id == 10U ? 1U : 2U) |
                             game->ram[MYSMB_CHEEP_ATTRIBUTES + slot]);
    direction = game->ram[MYSMB_CHEEP_DIRECTION + slot];
    oam = game->ram[MYSMB_CHEEP_SPRITE + slot];
    for (row = 0U; row < 3U; ++row) {
        row_offset = (mysmb_u8)(oam + row * 8U);
        y = (mysmb_u8)(game->ram[MYSMB_CHEEP_REL_Y + slot] + row * 8U);
        if ((offscreen & 0x80U) != 0U ||
            ((offscreen & 0x40U) != 0U && row >= 1U) ||
            ((offscreen & 0x20U) != 0U && row == 2U)) y = 0xf8U;
        left = tiles[row * 2U];
        right = tiles[row * 2U + 1U];
        if ((direction & 2U) != 0U) {
            game->ram[0x0201U + row_offset] = right;
            game->ram[0x0205U + row_offset] = left;
            attributes = (mysmb_u8)(attributes | 0x40U);
        }
        else {
            game->ram[0x0201U + row_offset] = left;
            game->ram[0x0205U + row_offset] = right;
        }
        game->ram[0x0200U + row_offset] =
            (offscreen & 8U) != 0U ? 0xf8U : y;
        game->ram[0x0202U + row_offset] = attributes;
        game->ram[0x0203U + row_offset] = game->ram[MYSMB_CHEEP_REL_X + slot];
        game->ram[0x0204U + row_offset] =
            (offscreen & 4U) != 0U ? 0xf8U : y;
        game->ram[0x0206U + row_offset] = attributes;
        game->ram[0x0207U + row_offset] =
            (mysmb_u8)(game->ram[MYSMB_CHEEP_REL_X + slot] + 8U);
    }
    return 1U;
}
