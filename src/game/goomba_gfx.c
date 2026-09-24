#include "game/game.h"

enum {
    MYSMB_ENEMY_ID = 0x0016U,
    MYSMB_ENEMY_STATE = 0x001eU,
    MYSMB_ENEMY_FLAG = 0x000fU,
    MYSMB_ENEMY_DIRECTION = 0x0046U,
    MYSMB_ENEMY_PAGE = 0x006eU,
    MYSMB_ENEMY_X = 0x0087U,
    MYSMB_ENEMY_Y = 0x00cfU,
    MYSMB_ENEMY_ATTRIBUTES = 0x03c5U,
    MYSMB_ENEMY_SPRITE_OFFSET = 0x06e5U,
    MYSMB_SCREEN_PAGE = 0x071aU,
    MYSMB_SCREEN_X = 0x071cU,
    MYSMB_TIMER_CONTROL = 0x0747U
};

void mysmb_objects_draw_goombas(struct mysmb_game *game)
{
    static const mysmb_u8 normal_tiles[6] = { 0xfcU, 0xfcU, 0x70U, 0x71U, 0x72U, 0x73U };
    static const mysmb_u8 defeated_tiles[6] = { 0xfcU, 0xfcU, 0xfcU, 0xfcU, 0xefU, 0xefU };
    mysmb_u8 slot;
    mysmb_u8 row;
    mysmb_u8 offset;
    mysmb_u8 direction;
    mysmb_u8 attributes;
    mysmb_u8 x;
    mysmb_u8 y;
    mysmb_u16 world;
    mysmb_u16 screen;
    mysmb_u8 left;
    mysmb_u8 right;
    mysmb_u8 row_offset;
    mysmb_u8 state;
    const mysmb_u8 *tiles;

    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
            game->ram[MYSMB_ENEMY_ID + slot] != 6U) continue;
        world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_PAGE + slot] << 8U) |
                              game->ram[MYSMB_ENEMY_X + slot]);
        screen = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_SCREEN_PAGE] << 8U) |
                               game->ram[MYSMB_SCREEN_X]);
        x = (mysmb_u8)(world - screen);
        y = game->ram[MYSMB_ENEMY_Y + slot];
        state = game->ram[MYSMB_ENEMY_STATE + slot];
        tiles = normal_tiles;
        if ((state & 0x1fU) >= 2U && (state & 0x20U) == 0U) {
            tiles = defeated_tiles;
            y--;
        }
        offset = game->ram[MYSMB_ENEMY_SPRITE_OFFSET + slot];
        direction = game->ram[MYSMB_ENEMY_DIRECTION + slot];
        if ((state & 0x20U) == 0U &&
            game->ram[MYSMB_TIMER_CONTROL] == 0U &&
            ((mysmb_u8)game->frame_number & 8U) == 0U) direction ^= 3U;
        attributes = (mysmb_u8)(3U | game->ram[MYSMB_ENEMY_ATTRIBUTES + slot]);
        for (row = 0U; row < 3U; ++row) {
            left = tiles[(mysmb_u8)(row * 2U)];
            right = tiles[(mysmb_u8)(row * 2U + 1U)];
            row_offset = (mysmb_u8)(offset + row * 8U);
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
            game->ram[0x0200U + row_offset] = (mysmb_u8)(y + row * 8U);
            game->ram[0x0204U + row_offset] = (mysmb_u8)(y + row * 8U);
            game->ram[0x0203U + row_offset] = x;
            game->ram[0x0207U + row_offset] = (mysmb_u8)(x + 8U);
        }
    }
}
