#include "game/oam/oam.h"

enum {
    MYSMB_SPR_OBJECT_X = 0x0086U,
    MYSMB_SPR_OBJECT_Y = 0x00ceU,
    MYSMB_SPR_OBJECT_RELATIVE_X = 0x03adU,
    MYSMB_SPR_OBJECT_RELATIVE_Y = 0x03b8U,
    MYSMB_SCREEN_EDGE_PAGE = 0x071aU,
    MYSMB_SCREEN_EDGE_X = 0x071cU,
    MYSMB_BLOCK_PAGE = 0x0076U,
    MYSMB_BLOCK_X = 0x008fU,
    MYSMB_BLOCK_Y_HIGH = 0x00beU,
    MYSMB_BLOCK_Y = 0x00d7U,
    MYSMB_BLOCK_OFFSCREEN_BITS = 0x03d4U,
    MYSMB_MISC_PAGE = 0x007aU,
    MYSMB_MISC_X = 0x0093U,
    MYSMB_MISC_Y_HIGH = 0x00c2U,
    MYSMB_MISC_Y = 0x00dbU,
    MYSMB_MISC_OFFSCREEN_BITS = 0x03d6U,
    MYSMB_FIREBALL_PAGE = 0x0074U,
    MYSMB_FIREBALL_X = 0x008dU,
    MYSMB_FIREBALL_Y_HIGH = 0x00bcU,
    MYSMB_FIREBALL_Y = 0x00d5U,
    MYSMB_FIREBALL_OFFSCREEN_BITS = 0x03d2U,
    MYSMB_ENEMY_X = 0x0087U,
    MYSMB_ENEMY_PAGE = 0x006eU,
    MYSMB_ENEMY_Y_HIGH = 0x00b6U,
    MYSMB_ENEMY_Y = 0x00cfU,
    MYSMB_ENEMY_OFFSCREEN_BITS = 0x03d1U
};

/* GetObjRelativePosition: all actor wrappers select source X and
 * destination Y, then execute the same two source-coordinate loads and
 * relative stores.  The 6502 X register itself is not game RAM. */
static void mysmb_oam_get_obj_relative_position(struct mysmb_game *game,
                                                 mysmb_u8 source,
                                                 mysmb_u8 destination)
{
    game->ram[MYSMB_SPR_OBJECT_RELATIVE_Y + destination] =
        game->ram[MYSMB_SPR_OBJECT_Y + source];
    game->ram[MYSMB_SPR_OBJECT_RELATIVE_X + destination] =
        (mysmb_u8)(game->ram[MYSMB_SPR_OBJECT_X + source] -
                   game->ram[MYSMB_SCREEN_EDGE_X]);
}

/* RelativePlayerPosition enters RelWOfs with X=Y=0.  The later
 * RenderPlayerSub, not this routine, writes Player_Pos_ForScroll. */
void mysmb_oam_relative_player_position(struct mysmb_game *game)
{
    mysmb_oam_get_obj_relative_position(game, 0U, 0U);
}

/* The original GetProperObjOffset adds a fixed SprObject array displacement.
 * For the owner SMB1 ROM these three immutable table values are exactly the
 * distances between the corresponding X arrays and SprObject_X_Position.
 * Keep the call edge here; its PRG table/data-node binding remains T47 S4. */
static mysmb_u8 mysmb_oam_proper_source_offset(mysmb_u8 slot,
                                                mysmb_u16 origin_x)
{
    return (mysmb_u8)(slot + (origin_x - MYSMB_SPR_OBJECT_X));
}

/* RelativeBubblePosition and RelativeFireballPosition use the original
 * SprObject RAM layout and fixed relative-result cells. */
void mysmb_oam_relative_bubble_position(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_get_obj_relative_position(game,
        mysmb_oam_proper_source_offset(slot, 0x009cU), 3U);
}

void mysmb_oam_relative_fireball_position(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_get_obj_relative_position(game,
        mysmb_oam_proper_source_offset(slot, MYSMB_FIREBALL_X), 2U);
}

/* VariableObjOfsRelPos first stores the incoming X in $00, then adds
 * the object's RAM-array displacement and calls GetObjRelativePosition. */
static void mysmb_oam_variable_obj_relative_position(struct mysmb_game *game,
                                                      mysmb_u8 slot,
                                                      mysmb_u8 displacement,
                                                      mysmb_u8 destination)
{
    game->ram[0U] = slot;
    mysmb_oam_get_obj_relative_position(game,
        (mysmb_u8)(slot + displacement), destination);
}

void mysmb_oam_relative_enemy_position(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_variable_obj_relative_position(game, slot, 1U, 1U);
}
/* ROM GetXOffscreenBits.  Returns the source table byte before
 * RunOffscrBitsSubs moves its high nybble to the final low nybble. */
mysmb_u8 mysmb_oam_get_x_offscreen_bits(struct mysmb_game *game,
                                        mysmb_u8 source_offset,
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

    game->ram[4U] = source_offset;
    edge = 1U;
    for (;;) {
        difference = (mysmb_u8)(game->ram[MYSMB_SCREEN_EDGE_X + edge] - x);
        game->ram[7U] = difference;
        borrow = game->ram[MYSMB_SCREEN_EDGE_X + edge] < x ? 1U : 0U;
        page_difference = (mysmb_u8)(game->ram[MYSMB_SCREEN_EDGE_PAGE + edge] -
                                     page - borrow);
        index = default_on_screen[edge];
        if ((page_difference & 0x80U) == 0U) {
            index = default_on_screen[(mysmb_u8)(edge + 1U)];
            if (page_difference == 0U && difference < 0x38U) {
                game->ram[6U] = 0x38U;
                game->ram[5U] = 8U;
                index = (mysmb_u8)(difference >> 3U);
                if (edge == 0U) index = (mysmb_u8)(index + 8U);
            } else if (page_difference == 0U) {
                game->ram[6U] = 0x38U;
                game->ram[5U] = 8U;
            }
        }
        bits = data[index];
        if (bits != 0U || edge == 0U) return bits;
        edge = 0U;
    }
}

/* ROM GetYOffscreenBits. */
static mysmb_u8 mysmb_oam_get_y_offscreen_bits(struct mysmb_game *game,
                                              mysmb_u8 high, mysmb_u8 y)
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
        game->ram[7U] = difference;
        borrow = high_position[edge] < y ? 1U : 0U;
        page_difference = (mysmb_u8)(1U - high - borrow);
        index = default_on_screen[edge];
        if ((page_difference & 0x80U) == 0U) {
            index = default_on_screen[(mysmb_u8)(edge + 1U)];
            if (page_difference == 0U) {
                game->ram[6U] = 0x20U;
                game->ram[5U] = 4U;
            }
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

/* ROM GetEnemyOffscreenBits -> GetOffScreenBitsSet.  The value-only helper
 * remains for callers not yet migrated to the source scratch contract. */
void mysmb_oam_get_enemy_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 x_bits;
    mysmb_u8 y_bits;

    x_bits = mysmb_oam_get_x_offscreen_bits(game, (mysmb_u8)(slot + 1U),
        game->ram[MYSMB_ENEMY_PAGE + slot], game->ram[MYSMB_ENEMY_X + slot]);
    game->ram[0U] = (mysmb_u8)(x_bits >> 4U);
    y_bits = mysmb_oam_get_y_offscreen_bits(game,
        game->ram[MYSMB_ENEMY_Y_HIGH + slot],
        game->ram[MYSMB_ENEMY_Y + slot]);
    game->ram[0U] = (mysmb_u8)(game->ram[0U] | (mysmb_u8)(y_bits << 4U));
    game->ram[MYSMB_ENEMY_OFFSCREEN_BITS] = game->ram[0U];
}

/* ROM GetFireballOffscreenBits -> GetProperObjOffset ->
 * GetOffScreenBitsSet.  The source slot selects the SprObject inputs, but
 * FBall_OffscreenBits is one fixed scratch byte. */
void mysmb_oam_get_fireball_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 x_bits;
    mysmb_u8 y_bits;

    x_bits = mysmb_oam_get_x_offscreen_bits(game, (mysmb_u8)(slot + 7U),
        game->ram[MYSMB_FIREBALL_PAGE + slot],
        game->ram[MYSMB_FIREBALL_X + slot]);
    y_bits = mysmb_oam_get_y_offscreen_bits(game,
        game->ram[MYSMB_FIREBALL_Y_HIGH + slot],
        game->ram[MYSMB_FIREBALL_Y + slot]);
    game->ram[MYSMB_FIREBALL_OFFSCREEN_BITS] =
        (mysmb_u8)((x_bits >> 4U) | (y_bits << 4U));
}
/* ROM RelativeBlockPosition -> VariableObjOfsRelPos -> GetObjRelativePosition.
 * ObjectOffset chooses the source-coordinate slots.  The two relative output
 * cells are fixed Block_Rel_XPos/Block_Rel_XPos+1 (and Y counterparts), not
 * indexed by ObjectOffset. */
void mysmb_oam_relative_block_position(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_variable_obj_relative_position(game, slot, 9U, 4U);
    mysmb_oam_variable_obj_relative_position(game,
        (mysmb_u8)(slot + 2U), 9U, 5U);
}
/* ROM GetBlockOffscreenBits -> GetOffScreenBitsSet. */
void mysmb_oam_get_block_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 x_bits;
    mysmb_u8 y_bits;

    x_bits = mysmb_oam_get_x_offscreen_bits(game, (mysmb_u8)(slot + 9U),
        game->ram[MYSMB_BLOCK_PAGE + slot], game->ram[MYSMB_BLOCK_X + slot]);
    y_bits = mysmb_oam_get_y_offscreen_bits(game,
        game->ram[MYSMB_BLOCK_Y_HIGH + slot],
        game->ram[MYSMB_BLOCK_Y + slot]);
    game->ram[MYSMB_BLOCK_OFFSCREEN_BITS] =
        (mysmb_u8)((x_bits >> 4U) | (y_bits << 4U));
}




/* ROM RelativeMiscPosition -> GetProperObjOffset -> GetObjRelativePosition. */
void mysmb_oam_relative_misc_position(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_get_obj_relative_position(game,
        mysmb_oam_proper_source_offset(slot, MYSMB_MISC_X), 6U);
}

/* ROM GetMiscOffscreenBits -> GetOffScreenBitsSet. */
void mysmb_oam_get_misc_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 x_bits;
    mysmb_u8 y_bits;

    x_bits = mysmb_oam_get_x_offscreen_bits(game, (mysmb_u8)(slot + 13U),
        game->ram[MYSMB_MISC_PAGE + slot], game->ram[MYSMB_MISC_X + slot]);
    y_bits = mysmb_oam_get_y_offscreen_bits(game,
        game->ram[MYSMB_MISC_Y_HIGH + slot],
        game->ram[MYSMB_MISC_Y + slot]);
    game->ram[MYSMB_MISC_OFFSCREEN_BITS] =
        (mysmb_u8)((x_bits >> 4U) | (y_bits << 4U));
}
