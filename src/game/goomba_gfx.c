#include "game/game.h"

enum {
    MYSMB_ENEMY_ID = 0x0016U,
    MYSMB_ENEMY_STATE = 0x001eU,
    MYSMB_ENEMY_FLAG = 0x000fU,
    MYSMB_ENEMY_DIRECTION = 0x0046U,
    MYSMB_ENEMY_PAGE = 0x006eU,
    MYSMB_ENEMY_X = 0x0087U,
    MYSMB_ENEMY_Y = 0x00cfU,
    MYSMB_ENEMY_RELATIVE_X = 0x03aeU,
    MYSMB_ENEMY_RELATIVE_Y = 0x03b9U,
    MYSMB_ENEMY_OFFSCREEN = 0x03d1U,
    MYSMB_ENEMY_ATTRIBUTES = 0x03c5U,
    MYSMB_ENEMY_SPRITE_OFFSET = 0x06e5U,
    MYSMB_SCREEN_PAGE = 0x071aU,
    MYSMB_SCREEN_X = 0x071cU,
    MYSMB_TIMER_CONTROL = 0x0747U,
    MYSMB_FRAME_COUNTER = 0x0009U
};

void mysmb_objects_draw_goombas_mask(struct mysmb_game *game,
                                          mysmb_u8 suppress_mask)
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
    mysmb_u8 offscreen;
    mysmb_u8 left_y;
    mysmb_u8 right_y;
    mysmb_u8 defeated;
    const mysmb_u8 *tiles;

    for (slot = 0U; slot < 5U; ++slot) {
        if ((suppress_mask & (mysmb_u8)(1U << slot)) != 0U ||
            game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
            game->ram[MYSMB_ENEMY_ID + slot] != 6U) continue;
        world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_PAGE + slot] << 8U) |
                              game->ram[MYSMB_ENEMY_X + slot]);
        screen = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_SCREEN_PAGE] << 8U) |
                               game->ram[MYSMB_SCREEN_X]);
        x = (mysmb_u8)(world - screen);
        y = game->ram[MYSMB_ENEMY_Y + slot];
        /* RunNormalEnemies preserves these pre-movement coordinates for the
         * delayed portable OAM phase.  Direct OAM unit calls retain the raw
         * world-coordinate fallback when no graphics phase has run. */
        if (game->ram[MYSMB_ENEMY_RELATIVE_Y + slot] != 0U) {
            x = game->ram[MYSMB_ENEMY_RELATIVE_X + slot];
            y = game->ram[MYSMB_ENEMY_RELATIVE_Y + slot];
            offscreen = game->ram[MYSMB_ENEMY_OFFSCREEN + slot];
        }
        else {
            offscreen = world < screen || world >= (mysmb_u16)(screen + 0x0100U) ?
                0x0fU : 0U;
        }
        state = game->ram[MYSMB_ENEMY_STATE + slot];
        tiles = normal_tiles;
        defeated = (mysmb_u8)(((state & 0x1fU) >= 2U &&
                               (state & 0x20U) == 0U) ? 1U : 0U);
        if (defeated != 0U) {
            tiles = defeated_tiles;
            /* EnemyGfxHandler selects the defeated-Goomba row then vertically
             * mirrors it.  Its surviving rows start one pixel below Enemy_Y. */
            y++;
        }
        offset = game->ram[MYSMB_ENEMY_SPRITE_OFFSET + slot];
        direction = game->ram[MYSMB_ENEMY_DIRECTION + slot];
        if ((state & 0x20U) == 0U &&
            game->ram[MYSMB_TIMER_CONTROL] == 0U &&
            (game->ram[MYSMB_FRAME_COUNTER] & 8U) == 0U) direction ^= 3U;
        attributes = (mysmb_u8)(3U | game->ram[MYSMB_ENEMY_ATTRIBUTES + slot]);
        for (row = 0U; row < 3U; ++row) {
            left = tiles[(mysmb_u8)(row * 2U)];
            right = tiles[(mysmb_u8)(row * 2U + 1U)];
            row_offset = (mysmb_u8)(offset + row * 8U);
            if (defeated != 0U) {
                game->ram[0x0201U + row_offset] = left;
                game->ram[0x0205U + row_offset] = right;
                game->ram[0x0202U + row_offset] =
                    (mysmb_u8)(attributes | (row == 0U ? 0U : 0x80U));
                game->ram[0x0206U + row_offset] =
                    (mysmb_u8)(attributes | 0x40U | (row == 0U ? 0U : 0x80U));
            }
            else if ((direction & 2U) != 0U) {
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
            if ((offscreen & 0x80U) != 0U ||
                ((offscreen & 0x40U) != 0U && row >= 1U) ||
                ((offscreen & 0x20U) != 0U && row == 2U)) {
                left_y = 0xf8U;
                right_y = 0xf8U;
            }
            else {
                if ((offscreen & 0x08U) != 0U) left_y = 0xf8U;
                if ((offscreen & 0x04U) != 0U) right_y = 0xf8U;
            }
            game->ram[0x0200U + row_offset] = left_y;
            game->ram[0x0204U + row_offset] = right_y;
            game->ram[0x0203U + row_offset] = x;
            game->ram[0x0207U + row_offset] = (mysmb_u8)(x + 8U);
        }
    }
}

void mysmb_objects_draw_goombas(struct mysmb_game *game)
{
    mysmb_objects_draw_goombas_mask(game, 0U);
}
