#include "game/oam/oam.h"
#include "game/objects.h"

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

static void mysmb_draw_goombas_mask_impl(struct mysmb_game *game,
                                               mysmb_u8 suppress_mask,
                                               mysmb_u8 prepare_scratch)
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
        if (prepare_scratch != 0U) {
            mysmb_oam_relative_enemy_position(game, slot);
            game->ram[MYSMB_ENEMY_OFFSCREEN] =
                mysmb_objects_get_enemy_offscreen_bits(game, slot);
        }
        x = game->ram[MYSMB_ENEMY_RELATIVE_X];
        y = game->ram[MYSMB_ENEMY_RELATIVE_Y];
        offscreen = game->ram[MYSMB_ENEMY_OFFSCREEN];
        state = game->ram[MYSMB_ENEMY_STATE + slot];
        tiles = normal_tiles;
        defeated = (mysmb_u8)(((state & 0x1fU) >= 2U &&
                               (state & 0x20U) == 0U) ? 1U : 0U);
        if (defeated != 0U) {
            tiles = defeated_tiles;
            /* EnemyGfxHandler selects the defeated-Goomba row then vertically
             * mirrors it.  Its surviving rows start one pixel below Enemy_Y. */
            y--;
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
                    attributes;
                game->ram[0x0206U + row_offset] =
                    attributes;
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

void mysmb_objects_draw_goombas_mask(struct mysmb_game *game,
                                     mysmb_u8 suppress_mask)
{
    mysmb_draw_goombas_mask_impl(game, suppress_mask, 1U);
}

void mysmb_objects_draw_goombas(struct mysmb_game *game)
{
    mysmb_objects_draw_goombas_mask(game, 0U);
}

/* One EnemyGfxHandler invocation for the selected Goomba slot. */
void mysmb_objects_draw_goomba(struct mysmb_game *game, mysmb_u8 slot)
{
    if (slot >= 5U) return;
    mysmb_objects_draw_goombas_mask(game,
        (mysmb_u8)(0x1fU ^ (mysmb_u8)(1U << slot)));
}
