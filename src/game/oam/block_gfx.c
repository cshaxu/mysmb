#include "game/oam/oam.h"
#include "game/game.h"

enum {
    MYSMB_AREA_TYPE = 0x074eU,
    MYSMB_BLOCK_ORIGINAL_X = 0x03f1U,
    MYSMB_BLOCK_METATILE = 0x03e8U,
    MYSMB_BLOCK_PAGE = 0x0076U,
    MYSMB_BLOCK_X = 0x008fU,
    MYSMB_BLOCK_Y_HIGH = 0x00beU,
    MYSMB_BLOCK_Y = 0x00d7U,
    MYSMB_BLOCK_SPRITE_OFFSET = 0x06ecU,
    MYSMB_SCREEN_EDGE_PAGE = 0x071aU,
    MYSMB_SCREEN_EDGE_X = 0x071cU,
    MYSMB_FRAME_COUNTER = 0x0009U
};

static mysmb_u8 mysmb_block_relative_x(const struct mysmb_game *game,
                                       mysmb_u8 slot)
{
    mysmb_u16 world;
    mysmb_u16 left;

    world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_BLOCK_PAGE + slot] << 8U) |
                         game->ram[MYSMB_BLOCK_X + slot]);
    left = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_SCREEN_EDGE_PAGE] << 8U) |
                        game->ram[MYSMB_SCREEN_EDGE_X]);
    return (mysmb_u8)(world - left);
}

static void mysmb_block_hide_columns(struct mysmb_game *game, mysmb_u8 offset,
                                     mysmb_u8 slot)
{
    mysmb_u16 world;
    mysmb_u16 left;
    mysmb_u16 right;

    world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_BLOCK_PAGE + slot] << 8U) |
                         game->ram[MYSMB_BLOCK_X + slot]);
    left = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_SCREEN_EDGE_PAGE] << 8U) |
                        game->ram[MYSMB_SCREEN_EDGE_X]);
    right = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_SCREEN_EDGE_PAGE + 1U] << 8U) |
                         game->ram[MYSMB_SCREEN_EDGE_X + 1U]);
    if (world < left) {
        game->ram[0x0200U + offset] = 0xf8U;
        game->ram[0x0208U + offset] = 0xf8U;
    }
    if (world >= right) {
        game->ram[0x0204U + offset] = 0xf8U;
        game->ram[0x020cU + offset] = 0xf8U;
    }
}

void mysmb_objects_draw_bouncing_block(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 offset;
    mysmb_u8 x;
    mysmb_u8 y;
    mysmb_u8 attributes;
    mysmb_u8 tile0;
    mysmb_u8 tile1;

    offset = game->ram[MYSMB_BLOCK_SPRITE_OFFSET + slot];
    x = mysmb_block_relative_x(game, slot);
    y = game->ram[MYSMB_BLOCK_Y + slot];
    tile0 = 0x85U;
    tile1 = 0x86U;
    if (game->ram[MYSMB_AREA_TYPE] != 1U) tile0 = 0x86U;
    attributes = 3U;
    if (game->ram[MYSMB_BLOCK_METATILE + slot] == 0xc4U) {
        tile0 = 0x87U;
        tile1 = 0x87U;
        attributes = game->ram[MYSMB_AREA_TYPE] == 1U ? 3U : 1U;
    }
    game->ram[0x0200U + offset] = y;
    game->ram[0x0204U + offset] = y;
    game->ram[0x0208U + offset] = (mysmb_u8)(y + 8U);
    game->ram[0x020cU + offset] = (mysmb_u8)(y + 8U);
    game->ram[0x0201U + offset] = tile0;
    game->ram[0x0205U + offset] = tile0;
    game->ram[0x0209U + offset] = tile1;
    game->ram[0x020dU + offset] = tile1;
    game->ram[0x0202U + offset] = attributes;
    game->ram[0x0206U + offset] = (mysmb_u8)(attributes | 0x40U);
    game->ram[0x020aU + offset] = (mysmb_u8)(attributes | 0x80U);
    game->ram[0x020eU + offset] = (mysmb_u8)(attributes | 0xc0U);
    game->ram[0x0203U + offset] = x;
    game->ram[0x0207U + offset] = (mysmb_u8)(x + 8U);
    game->ram[0x020bU + offset] = x;
    game->ram[0x020fU + offset] = (mysmb_u8)(x + 8U);
    mysmb_block_hide_columns(game, offset, slot);
}

void mysmb_objects_draw_brick_chunks(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 offset;
    mysmb_u8 attributes;
    mysmb_u8 x0;
    mysmb_u8 x1;
    mysmb_u8 y0;
    mysmb_u8 y1;
    mysmb_u8 original_x;

    offset = game->ram[MYSMB_BLOCK_SPRITE_OFFSET + slot];
    attributes = (mysmb_u8)(((game->ram[MYSMB_FRAME_COUNTER] << 4U) & 0xc0U) |
        (game->ram[MYSMB_AREA_TYPE] == 5U ? 2U : 3U));
    x0 = mysmb_block_relative_x(game, slot);
    x1 = mysmb_block_relative_x(game, (mysmb_u8)(slot + 2U));
    original_x = (mysmb_u8)(game->ram[MYSMB_BLOCK_ORIGINAL_X + slot] -
        game->ram[MYSMB_SCREEN_EDGE_X]);
    y0 = game->ram[MYSMB_BLOCK_Y + slot];
    y1 = game->ram[MYSMB_BLOCK_Y + slot + 2U];
    game->ram[0x0200U + offset] = y0;
    game->ram[0x0204U + offset] = y0;
    game->ram[0x0208U + offset] = y1;
    game->ram[0x020cU + offset] = y1;
    game->ram[0x0201U + offset] = game->ram[MYSMB_AREA_TYPE] == 5U ? 0x75U : 0x84U;
    game->ram[0x0205U + offset] = game->ram[0x0201U + offset];
    game->ram[0x0209U + offset] = game->ram[0x0201U + offset];
    game->ram[0x020dU + offset] = game->ram[0x0201U + offset];
    game->ram[0x0202U + offset] = attributes;
    game->ram[0x0206U + offset] = attributes;
    game->ram[0x020aU + offset] = attributes;
    game->ram[0x020eU + offset] = attributes;
    game->ram[0x0203U + offset] = x0;
    game->ram[0x0207U + offset] = (mysmb_u8)(original_x - x0 + original_x + 6U);
    game->ram[0x020bU + offset] = x1;
    game->ram[0x020fU + offset] = (mysmb_u8)(original_x - x1 + original_x + 6U);
    mysmb_block_hide_columns(game, offset, slot);
}



