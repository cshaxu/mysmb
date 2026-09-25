#include "game/oam/oam.h"

enum {
    MYSMB_SCREEN_EDGE_PAGE = 0x071aU,
    MYSMB_SCREEN_EDGE_X = 0x071cU,
    MYSMB_BLOCK_PAGE = 0x0076U,
    MYSMB_BLOCK_X = 0x008fU,
    MYSMB_BLOCK_Y_HIGH = 0x00beU,
    MYSMB_BLOCK_Y = 0x00d7U,
    MYSMB_BLOCK_RELATIVE_X = 0x03b1U,
    MYSMB_BLOCK_RELATIVE_Y = 0x03bcU,
    MYSMB_BLOCK_OFFSCREEN_BITS = 0x03d4U,
    MYSMB_MISC_PAGE = 0x007aU,
    MYSMB_MISC_X = 0x0093U,
    MYSMB_MISC_Y_HIGH = 0x00c2U,
    MYSMB_MISC_Y = 0x00dbU,
    MYSMB_MISC_RELATIVE_X = 0x03b3U,
    MYSMB_MISC_RELATIVE_Y = 0x03beU,
    MYSMB_MISC_OFFSCREEN_BITS = 0x03d6U
};

/* ROM RelativePlayerPosition.  This belongs with the other
 * GetObjRelativePosition outputs: player control calls it, while the
 * source-defined relative scratch remains a single game-owned result. */
void mysmb_oam_relative_player_position(struct mysmb_game *game)
{
    game->ram[0x03adU] = (mysmb_u8)(game->ram[0x0086U] -
                                    game->ram[MYSMB_SCREEN_EDGE_X]);
    game->ram[0x03b8U] = game->ram[0x00ceU];
    game->ram[0x0755U] = game->ram[0x03adU];
}

/* ROM GetXOffscreenBits.  Returns the source table byte before
 * RunOffscrBitsSubs moves its high nybble to the final low nybble. */
static mysmb_u8 mysmb_oam_get_x_offscreen_bits(const struct mysmb_game *game,
                                                mysmb_u8 page, mysmb_u8 x)
{
    static const mysmb_u8 data[16] = {
        0x7fU, 0x3fU, 0x1fU, 0x0fU, 0x07U, 0x03U, 0x01U, 0x00U,
        0x80U, 0xc0U, 0xe0U, 0xf0U, 0xf8U, 0xfcU, 0xfeU, 0xffU
    };
    static const mysmb_u8 default_on_screen[3] = { 0x07U, 0x0fU, 0x07U };
    mysmb_u8 edge;
    mysmb_u8 difference;
    mysmb_u8 borrow;
    mysmb_u8 page_difference;
    mysmb_u8 index;
    mysmb_u8 bits;

    edge = 1U;
    for (;;) {
        difference = (mysmb_u8)(game->ram[MYSMB_SCREEN_EDGE_X + edge] - x);
        borrow = game->ram[MYSMB_SCREEN_EDGE_X + edge] < x ? 1U : 0U;
        page_difference = (mysmb_u8)(game->ram[MYSMB_SCREEN_EDGE_PAGE + edge] -
                                     page - borrow);
        index = default_on_screen[edge];
        if ((page_difference & 0x80U) == 0U) {
            index = default_on_screen[(mysmb_u8)(edge + 1U)];
            if (page_difference == 0U && difference < 0x38U) {
                index = (mysmb_u8)(difference >> 3U);
                if (edge == 0U) index = (mysmb_u8)(index + 8U);
            }
        }
        bits = data[index];
        if (bits != 0U || edge == 0U) return bits;
        edge = 0U;
    }
}

/* ROM GetYOffscreenBits. */
static mysmb_u8 mysmb_oam_get_y_offscreen_bits(mysmb_u8 high, mysmb_u8 y)
{
    static const mysmb_u8 data[9] = { 0U, 8U, 12U, 14U, 15U, 7U, 3U, 1U, 0U };
    static const mysmb_u8 default_on_screen[3] = { 4U, 0U, 4U };
    static const mysmb_u8 high_position[2] = { 0xffU, 0U };
    mysmb_u8 edge;
    mysmb_u8 difference;
    mysmb_u8 borrow;
    mysmb_u8 page_difference;
    mysmb_u8 index;
    mysmb_u8 bits;

    edge = 1U;
    for (;;) {
        difference = (mysmb_u8)(high_position[edge] - y);
        borrow = high_position[edge] < y ? 1U : 0U;
        page_difference = (mysmb_u8)(1U - high - borrow);
        index = default_on_screen[edge];
        if ((page_difference & 0x80U) == 0U) {
            index = default_on_screen[(mysmb_u8)(edge + 1U)];
            if (page_difference == 0U && difference < 0x20U) {
                index = (mysmb_u8)(difference >> 3U);
                if (edge == 0U) index = (mysmb_u8)(index + 4U);
            }
        }
        bits = data[index];
        if (bits != 0U || edge == 0U) return bits;
        edge = 0U;
    }
}

/* ROM RelativeBlockPosition -> VariableObjOfsRelPos -> GetObjRelativePosition.
 * ObjectOffset chooses the source-coordinate slots.  The two relative output
 * cells are fixed Block_Rel_XPos/Block_Rel_XPos+1 (and Y counterparts), not
 * indexed by ObjectOffset. */
void mysmb_oam_relative_block_position(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_BLOCK_RELATIVE_Y] = game->ram[MYSMB_BLOCK_Y + slot];
    game->ram[MYSMB_BLOCK_RELATIVE_X] =
        (mysmb_u8)(game->ram[MYSMB_BLOCK_X + slot] -
                   game->ram[MYSMB_SCREEN_EDGE_X]);
    game->ram[MYSMB_BLOCK_RELATIVE_Y + 1U] =
        game->ram[MYSMB_BLOCK_Y + slot + 2U];
    game->ram[MYSMB_BLOCK_RELATIVE_X + 1U] =
        (mysmb_u8)(game->ram[MYSMB_BLOCK_X + slot + 2U] -
                   game->ram[MYSMB_SCREEN_EDGE_X]);
}
/* ROM GetBlockOffscreenBits -> GetOffScreenBitsSet. */
void mysmb_oam_get_block_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 x_bits;
    mysmb_u8 y_bits;

    x_bits = mysmb_oam_get_x_offscreen_bits(game,
        game->ram[MYSMB_BLOCK_PAGE + slot], game->ram[MYSMB_BLOCK_X + slot]);
    y_bits = mysmb_oam_get_y_offscreen_bits(game->ram[MYSMB_BLOCK_Y_HIGH + slot],
        game->ram[MYSMB_BLOCK_Y + slot]);
    game->ram[MYSMB_BLOCK_OFFSCREEN_BITS] =
        (mysmb_u8)((x_bits >> 4U) | (y_bits << 4U));
}




/* ROM RelativeMiscPosition -> GetProperObjOffset -> GetObjRelativePosition. */
void mysmb_oam_relative_misc_position(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_MISC_RELATIVE_Y] = game->ram[MYSMB_MISC_Y + slot];
    game->ram[MYSMB_MISC_RELATIVE_X] =
        (mysmb_u8)(game->ram[MYSMB_MISC_X + slot] -
                   game->ram[MYSMB_SCREEN_EDGE_X]);
}

/* ROM GetMiscOffscreenBits -> GetOffScreenBitsSet. */
void mysmb_oam_get_misc_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 x_bits;
    mysmb_u8 y_bits;

    x_bits = mysmb_oam_get_x_offscreen_bits(game,
        game->ram[MYSMB_MISC_PAGE + slot], game->ram[MYSMB_MISC_X + slot]);
    y_bits = mysmb_oam_get_y_offscreen_bits(game->ram[MYSMB_MISC_Y_HIGH + slot],
        game->ram[MYSMB_MISC_Y + slot]);
    game->ram[MYSMB_MISC_OFFSCREEN_BITS] =
        (mysmb_u8)((x_bits >> 4U) | (y_bits << 4U));
}
