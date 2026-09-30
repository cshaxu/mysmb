#include "game/oam/oam.h"

enum {
    MYSMB_BLOCK_METATILE = 0x03e8U,
    MYSMB_BLOCK_ORIGINAL_X = 0x03f1U,
    MYSMB_BLOCK_RELATIVE_X = 0x03b1U,
    MYSMB_BLOCK_RELATIVE_Y = 0x03bcU,
    MYSMB_BLOCK_OFFSCREEN = 0x03d4U,
    MYSMB_BLOCK_SPRITE = 0x06ecU,
    MYSMB_SCREEN_LEFT_X = 0x071cU,
    MYSMB_AREA_TYPE = 0x074eU,
    MYSMB_ENGINE_SUBROUTINE = 0x000eU,
    MYSMB_FRAME_COUNTER = 0x0009U
};

/* Source SEC/SBC, then two ADC instructions with no intervening CLC.
 * Both carries are observable at wrapped chunk/screen positions. */
static mysmb_u8 mysmb_block_reflected_chunk_x(mysmb_u8 original,
                                               mysmb_u8 current)
{
    mysmb_u16 sum;
    mysmb_u8 carry;
    mysmb_u8 value;

    carry = original >= current ? 1U : 0U;
    value = (mysmb_u8)(original - current);
    sum = (mysmb_u16)value + original + carry;
    carry = sum > 0xffU ? 1U : 0U;
    value = (mysmb_u8)sum;
    sum = (mysmb_u16)value + 6U + carry;
    return (mysmb_u8)sum;
}

/* ROM DrawBlock -> DBlkLoop/ChkRep/BlkOffscr/MoveColOffscreen.
 * DrawOneSpriteRow enters DrawSpriteObject with X=0,2 and Y=base,base+8. */
void mysmb_objects_draw_bouncing_block(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 default_tiles[4] = {0x85U,0x85U,0x86U,0x86U};
    mysmb_u8 oam, row, offset, graphics_index, attributes, bits;

    oam = game->ram[MYSMB_BLOCK_SPRITE + slot];
    game->ram[2U] = game->ram[MYSMB_BLOCK_RELATIVE_Y];
    game->ram[5U] = game->ram[MYSMB_BLOCK_RELATIVE_X];
    game->ram[4U] = 3U;
    game->ram[3U] = 1U;
    offset = oam;
    graphics_index = 0U;
    for (row = 0U; row < 2U; ++row) {
        game->ram[0U] = default_tiles[graphics_index];
        game->ram[1U] = default_tiles[(mysmb_u8)(graphics_index + 1U)];
        mysmb_oam_draw_sprite_object(game, &graphics_index, &offset);
    }
    if (game->ram[MYSMB_AREA_TYPE] != 1U) {
        game->ram[0x0201U + oam] = 0x86U;
        game->ram[0x0205U + oam] = 0x86U;
    }
    if (game->ram[MYSMB_BLOCK_METATILE + slot] == 0xc4U) {
        attributes = game->ram[MYSMB_AREA_TYPE] == 1U ? 3U : 1U;
        for (row = 0U; row < 2U; ++row) {
            offset = (mysmb_u8)(oam + row * 8U);
            game->ram[0x0201U + offset] = 0x87U;
            game->ram[0x0205U + offset] = 0x87U;
        }
        game->ram[0x0202U + oam] = attributes;
        game->ram[0x0206U + oam] = (mysmb_u8)(attributes | 0x40U);
        game->ram[0x020aU + oam] = (mysmb_u8)(attributes | 0x80U);
        game->ram[0x020eU + oam] = (mysmb_u8)(attributes | 0xc0U);
    }
    bits = game->ram[MYSMB_BLOCK_OFFSCREEN];
    if ((bits & 4U) != 0U) {
        game->ram[0x0204U + oam] = 0xf8U;
        game->ram[0x020cU + oam] = 0xf8U;
    }
    if ((bits & 8U) != 0U) {
        game->ram[0x0200U + oam] = 0xf8U;
        game->ram[0x0208U + oam] = 0xf8U;
    }
}

/* ROM DrawBrickChunks -> DChunks/ChkLeftCo/ChnkOfs/ExBCDr. */
void mysmb_objects_draw_brick_chunks(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 oam, tile, attributes, original, first_x, second_x, bits;
    mysmb_u8 row, offset;

    oam = game->ram[MYSMB_BLOCK_SPRITE + slot];
    if (game->ram[MYSMB_ENGINE_SUBROUTINE] == 5U) {
        game->ram[0U] = 2U;
        tile = 0x75U;
    } else {
        game->ram[0U] = 3U;
        tile = 0x84U;
    }
    attributes = (mysmb_u8)(((game->ram[MYSMB_FRAME_COUNTER] << 4U) & 0xc0U) |
                             game->ram[0U]);
    for (row = 0U; row < 2U; ++row) {
        offset = (mysmb_u8)(oam + row * 8U);
        game->ram[0x0201U + offset] = tile;
        game->ram[0x0205U + offset] = tile;
        game->ram[0x0202U + offset] = attributes;
        game->ram[0x0206U + offset] = attributes;
    }
    game->ram[0x0200U + oam] = game->ram[MYSMB_BLOCK_RELATIVE_Y];
    game->ram[0x0204U + oam] = game->ram[MYSMB_BLOCK_RELATIVE_Y];
    game->ram[0x0208U + oam] = game->ram[MYSMB_BLOCK_RELATIVE_Y + 1U];
    game->ram[0x020cU + oam] = game->ram[MYSMB_BLOCK_RELATIVE_Y + 1U];
    first_x = game->ram[MYSMB_BLOCK_RELATIVE_X];
    second_x = game->ram[MYSMB_BLOCK_RELATIVE_X + 1U];
    game->ram[0x0203U + oam] = first_x;
    original = (mysmb_u8)(game->ram[MYSMB_BLOCK_ORIGINAL_X + slot] -
                          game->ram[MYSMB_SCREEN_LEFT_X]);
    game->ram[0U] = original;
    game->ram[0x0207U + oam] =
        mysmb_block_reflected_chunk_x(original, first_x);
    game->ram[0x020bU + oam] = second_x;
    game->ram[0x020fU + oam] =
        mysmb_block_reflected_chunk_x(original, second_x);

    bits = game->ram[MYSMB_BLOCK_OFFSCREEN];
    if ((bits & 8U) != 0U) {
        game->ram[0x0200U + oam] = 0xf8U;
        game->ram[0x0208U + oam] = 0xf8U;
    }
    if ((bits & 0x80U) != 0U) {
        game->ram[0x0200U + oam] = 0xf8U;
        game->ram[0x0204U + oam] = 0xf8U;
    }
    if ((original & 0x80U) != 0U &&
        game->ram[0x0203U + oam] >= game->ram[0x0207U + oam]) {
        game->ram[0x0204U + oam] = 0xf8U;
        game->ram[0x020cU + oam] = 0xf8U;
    }
}
