#include "game/oam/oam.h"

enum {
    MYSMB_SPR_OBJECT_X = 0x0086U,
    MYSMB_SPR_OBJECT_Y = 0x00ceU,
    MYSMB_SPR_OBJECT_PAGE = 0x006dU,
    MYSMB_SPR_OBJECT_Y_HIGH = 0x00b5U,
    MYSMB_SPR_OBJECT_RELATIVE_X = 0x03adU,
    MYSMB_SPR_OBJECT_RELATIVE_Y = 0x03b8U,
    MYSMB_SPR_OBJECT_OFFSCREEN = 0x03d0U,
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

/* Immutable owner-ROM tables in source order.  S4 binds their PRG bytes
 * directly and the actor routes below exercise their consumers. */
static const mysmb_u8 mysmb_obj_offset_data[3] = { 0x07U, 0x16U, 0x0dU };
static const mysmb_u8 mysmb_x_offscreen_bits_data[16] = {
    0x7fU, 0x3fU, 0x1fU, 0x0fU, 0x07U, 0x03U, 0x01U, 0x00U,
    0x80U, 0xc0U, 0xe0U, 0xf0U, 0xf8U, 0xfcU, 0xfeU, 0xffU
};
static const mysmb_u8 mysmb_default_x_onscreen_ofs[3] = {
    0x07U, 0x0fU, 0x07U
};
static const mysmb_u8 mysmb_y_offscreen_bits_data[9] = {
    0x00U, 0x08U, 0x0cU, 0x0eU, 0x0fU, 0x07U, 0x03U, 0x01U, 0x00U
};
static const mysmb_u8 mysmb_default_y_onscreen_ofs[3] = {
    0x04U, 0x00U, 0x04U
};
static const mysmb_u8 mysmb_high_pos_unit_data[2] = { 0xffU, 0x00U };

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

/* ROM ObjOffsetData / GetProperObjOffset.  The three owner-ROM table bytes
 * select the fireball, bubble and misc SprObject array displacements. */
static mysmb_u8 mysmb_oam_proper_source_offset(mysmb_u8 slot,
                                                mysmb_u8 object_type)
{
    return (mysmb_u8)(slot + mysmb_obj_offset_data[object_type]);
}

/* RelativeBubblePosition and RelativeFireballPosition use the original
 * SprObject RAM layout and fixed relative-result cells. */
void mysmb_oam_relative_bubble_position(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_get_obj_relative_position(game,
        mysmb_oam_proper_source_offset(slot, 1U), 3U);
}

void mysmb_oam_relative_fireball_position(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_get_obj_relative_position(game,
        mysmb_oam_proper_source_offset(slot, 0U), 2U);
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
/* ROM DividePDiff / SetOscrO / ExDivPD.  Both X/Y loops set $06 before
 * entering; the routine always writes $05, even on its early exit. */
static mysmb_u8 mysmb_oam_divide_pixel_diff(struct mysmb_game *game,
                                            mysmb_u8 edge,
                                            mysmb_u8 adder,
                                            mysmb_u8 current_offset)
{
    mysmb_u8 next_offset;
    game->ram[5U] = adder;
    if (game->ram[7U] >= game->ram[6U]) return current_offset;
    next_offset = (mysmb_u8)((game->ram[7U] >> 3U) & 7U);
    if (edge == 0U) next_offset = (mysmb_u8)(next_offset + adder);
    return next_offset;
}

/* ROM GetXOffscreenBits.  Returns the source table byte before
 * RunOffscrBitsSubs moves its high nybble to the final low nybble. */
mysmb_u8 mysmb_oam_get_x_offscreen_bits(struct mysmb_game *game,
                                        mysmb_u8 source_offset,
                                        mysmb_u8 page, mysmb_u8 x)
{
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
        index = mysmb_default_x_onscreen_ofs[edge];
        if ((page_difference & 0x80U) == 0U) {
            index = mysmb_default_x_onscreen_ofs[(mysmb_u8)(edge + 1U)];
            if (page_difference == 0U) {
                game->ram[6U] = 0x38U;
                index = mysmb_oam_divide_pixel_diff(game, edge, 8U, index);
            }
        }
        bits = mysmb_x_offscreen_bits_data[index];
        if (bits != 0U || edge == 0U) return bits;
        edge = 0U;
    }
}

/* ROM GetYOffscreenBits. */
static mysmb_u8 mysmb_oam_get_y_offscreen_bits(struct mysmb_game *game,
                                              mysmb_u8 source_offset)
{
    mysmb_u8 edge;
    mysmb_u8 difference;
    mysmb_u8 borrow;
    mysmb_u8 page_difference;
    mysmb_u8 index;
    mysmb_u8 bits;
    mysmb_u8 high;
    mysmb_u8 y;

    game->ram[4U] = source_offset;
    high = game->ram[MYSMB_SPR_OBJECT_Y_HIGH + source_offset];
    y = game->ram[MYSMB_SPR_OBJECT_Y + source_offset];
    edge = 1U;
    for (;;) {
        difference = (mysmb_u8)(mysmb_high_pos_unit_data[edge] - y);
        game->ram[7U] = difference;
        borrow = mysmb_high_pos_unit_data[edge] < y ? 1U : 0U;
        page_difference = (mysmb_u8)(1U - high - borrow);
        index = mysmb_default_y_onscreen_ofs[edge];
        if ((page_difference & 0x80U) == 0U) {
            index = mysmb_default_y_onscreen_ofs[(mysmb_u8)(edge + 1U)];
            if (page_difference == 0U) {
                game->ram[6U] = 0x20U;
                index = mysmb_oam_divide_pixel_diff(game, edge, 4U, index);
            }
        }
        bits = mysmb_y_offscreen_bits_data[index];
        if (bits != 0U || edge == 0U) return bits;
        edge = 0U;
    }
}

/* ROM RunOffscrBitsSubs: X table high nibble becomes the low result
 * nibble in $00 before the Y helper takes over. */
static mysmb_u8 mysmb_oam_run_offscreen_bits_subs(struct mysmb_game *game,
                                                  mysmb_u8 source_offset)
{
    mysmb_u8 x_bits;
    x_bits = mysmb_oam_get_x_offscreen_bits(game, source_offset,
        game->ram[MYSMB_SPR_OBJECT_PAGE + source_offset],
        game->ram[MYSMB_SPR_OBJECT_X + source_offset]);
    game->ram[0U] = (mysmb_u8)(x_bits >> 4U);
    return mysmb_oam_get_y_offscreen_bits(game, source_offset);
}

/* ROM GetOffScreenBitsSet: save destination Y, call shared X/Y subchain,
 * combine nibbles and restore X from ObjectOffset (register only). */
void mysmb_oam_get_offscreen_bits_set(struct mysmb_game *game,
                                     mysmb_u8 source_offset,
                                     mysmb_u8 destination_offset)
{
    mysmb_u8 y_bits;
    y_bits = mysmb_oam_run_offscreen_bits_subs(game, source_offset);
    game->ram[0U] = (mysmb_u8)(game->ram[0U] | (mysmb_u8)(y_bits << 4U));
    game->ram[MYSMB_SPR_OBJECT_OFFSCREEN + destination_offset] = game->ram[0U];
}

/* ROM SetOffscrBitsOffset: enemy/block A displacement, incoming X slot
 * stored in $00 before the shared result overwrites it. */
static void mysmb_oam_set_offscreen_bits_offset(struct mysmb_game *game,
                                                mysmb_u8 slot,
                                                mysmb_u8 displacement,
                                                mysmb_u8 destination_offset)
{
    game->ram[0U] = slot;
    mysmb_oam_get_offscreen_bits_set(game,
        (mysmb_u8)(slot + displacement), destination_offset);
}

/* ROM GetEnemyOffscreenBits -> SetOffscrBitsOffset. */
void mysmb_oam_get_enemy_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_set_offscreen_bits_offset(game, slot, 1U, 1U);
}

/* ROM GetFireballOffscreenBits -> GetProperObjOffset ->
 * GetOffScreenBitsSet.  The source slot selects the SprObject inputs, but
 * FBall_OffscreenBits is one fixed scratch byte. */
void mysmb_oam_get_fireball_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_get_offscreen_bits_set(game,
        mysmb_oam_proper_source_offset(slot, 0U), 2U);
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
    mysmb_oam_set_offscreen_bits_offset(game, slot, 9U, 4U);
}




/* ROM RelativeMiscPosition -> GetProperObjOffset -> GetObjRelativePosition. */
void mysmb_oam_relative_misc_position(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_get_obj_relative_position(game,
        mysmb_oam_proper_source_offset(slot, 2U), 6U);
}

/* ROM GetMiscOffscreenBits -> GetOffScreenBitsSet. */
void mysmb_oam_get_misc_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_get_offscreen_bits_set(game,
        mysmb_oam_proper_source_offset(slot, 2U), 6U);
}

void mysmb_oam_get_bubble_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_get_offscreen_bits_set(game,
        mysmb_oam_proper_source_offset(slot, 1U), 3U);
}
