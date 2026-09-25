#include "game/oam/oam.h"
#include "game/objects.h"

enum {
    MYSMB_PIRANHA_FLAG = 0x000fU,
    MYSMB_PIRANHA_ID = 0x0016U,
    MYSMB_PIRANHA_X_SPEED = 0x0058U,
    MYSMB_PIRANHA_X = 0x0087U,
    MYSMB_PIRANHA_Y = 0x00cfU,
    MYSMB_PIRANHA_REL_X = 0x03aeU,
    MYSMB_PIRANHA_REL_Y = 0x03b9U,
    MYSMB_PIRANHA_OFFSCREEN = 0x03d1U,
    MYSMB_PIRANHA_SPRITE = 0x06e5U,
    MYSMB_PIRANHA_TIMER = 0x078aU,
    MYSMB_PIRANHA_FRAME = 0x0009U,
    MYSMB_PIRANHA_SCREEN_X = 0x071cU
};

/* ROM EnemyGfxHandler piranha branch through DrawEnemyObject. */
void mysmb_objects_draw_piranha(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 first_frame[6] =
        { 0xe5U, 0xe5U, 0xe6U, 0xe6U, 0xebU, 0xebU };
    static const mysmb_u8 second_frame[6] =
        { 0xecU, 0xecU, 0xedU, 0xedU, 0xeeU, 0xeeU };
    const mysmb_u8 *tiles;
    mysmb_u8 oam;
    mysmb_u8 row;
    mysmb_u8 y;
    mysmb_u8 offscreen;

    if (game->ram[MYSMB_PIRANHA_FLAG + slot] == 0U ||
        game->ram[MYSMB_PIRANHA_ID + slot] != 13U) return;
    /* The ROM returns while descending and its frame-delay timer is live. */
    if ((game->ram[MYSMB_PIRANHA_X_SPEED + slot] & 0x80U) == 0U &&
        game->ram[MYSMB_PIRANHA_TIMER + slot] != 0U) return;
    game->ram[MYSMB_PIRANHA_REL_X + slot] = (mysmb_u8)(
        game->ram[MYSMB_PIRANHA_X + slot] - game->ram[MYSMB_PIRANHA_SCREEN_X]);
    game->ram[MYSMB_PIRANHA_REL_Y + slot] = game->ram[MYSMB_PIRANHA_Y + slot];
    offscreen = mysmb_objects_get_enemy_x_offscreen_bits(game, slot);
    game->ram[MYSMB_PIRANHA_OFFSCREEN + slot] = offscreen;
    tiles = (game->ram[MYSMB_PIRANHA_FRAME] & 8U) == 0U ?
        second_frame : first_frame;
    oam = game->ram[MYSMB_PIRANHA_SPRITE + slot];
    for (row = 0U; row < 3U; ++row) {
        mysmb_u8 offset;
        y = (mysmb_u8)(game->ram[MYSMB_PIRANHA_REL_Y + slot] + row * 8U);
        if ((offscreen & 0x80U) != 0U ||
            ((offscreen & 0x40U) != 0U && row >= 1U) ||
            ((offscreen & 0x20U) != 0U && row == 2U)) y = 0xf8U;
        offset = (mysmb_u8)(oam + row * 8U);
        game->ram[0x0200U + offset] = (offscreen & 8U) != 0U ? 0xf8U : y;
        game->ram[0x0201U + offset] = tiles[row * 2U];
        game->ram[0x0202U + offset] = 0x21U;
        game->ram[0x0203U + offset] = game->ram[MYSMB_PIRANHA_REL_X + slot];
        game->ram[0x0204U + offset] = (offscreen & 4U) != 0U ? 0xf8U : y;
        game->ram[0x0205U + offset] = tiles[row * 2U + 1U];
        game->ram[0x0206U + offset] = 0x61U;
        game->ram[0x0207U + offset] =
            (mysmb_u8)(game->ram[MYSMB_PIRANHA_REL_X + slot] + 8U);
    }
}

