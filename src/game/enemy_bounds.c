#include "game/objects.h"

enum {
    MYSMB_SCREEN_LEFT_X = 0x071cU,
    MYSMB_SCREEN_LEFT_PAGE = 0x071aU,
    MYSMB_ENEMY_X = 0x0087U,
    MYSMB_ENEMY_PAGE = 0x006eU,
    MYSMB_ENEMY_Y_HIGH = 0x00b6U,
    MYSMB_ENEMY_Y = 0x00cfU,
    MYSMB_ENEMY_BOUND_BOX = 0x049aU,
    MYSMB_ENEMY_OFFSCREEN_BITS = 0x03d1U,
    MYSMB_ENEMY_OFFSCREEN_BITS_MASKED = 0x03d8U,
    MYSMB_BOUNDING_BOX_ENEMY = 0x04b0U
};

/* ROM GetXOffscreenBits, restricted to the enemy coordinate arrays.  The
 * source divides the distance from each horizontal screen edge into eight
 * pixel bands and uses XOffscreenBitsData to hide only the affected sprite
 * columns. */
mysmb_u8 mysmb_objects_get_enemy_x_offscreen_bits(
    const struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 right_bits[4] = { 0x07U, 0x03U, 0x01U, 0x00U };
    /* RunOffscrBitsSubs shifts GetXOffscreenBits right four places before
     * GetOffScreenBitsSet combines it with the vertical nybble. */
    static const mysmb_u8 left_bits[8] = {
        0x08U, 0x0cU, 0x0eU, 0x0fU, 0x0fU, 0x0fU, 0x0fU, 0x0fU
    };
    mysmb_u8 difference;
    mysmb_u8 page_difference;
    mysmb_u8 borrow;
    mysmb_u8 index;

    /* First pass: the ROM begins at ScreenRight. */
    difference = (mysmb_u8)(game->ram[0x071dU] - game->ram[MYSMB_ENEMY_X + slot]);
    borrow = game->ram[0x071dU] < game->ram[MYSMB_ENEMY_X + slot] ? 1U : 0U;
    page_difference = (mysmb_u8)(game->ram[0x071bU] -
                                  game->ram[MYSMB_ENEMY_PAGE + slot] - borrow);
    /* GetXOffscreenBits returns the source table byte; RunOffscrBitsSubs
     * shifts its right-edge high nibble into the final low nibble. */
    /* GetXOffscreenBits uses the right edge first.  A positive page
     * difference means this object lies a page to its left: the ROM loads
     * XOffscreenBitsData[$07] (zero) and continues with the left edge.
     * Only a negative difference is beyond the right edge. */
    if ((page_difference & 0x80U) != 0U) return 0x0fU;
    if (page_difference == 0U) {
        index = (mysmb_u8)(difference >> 3U);
        if (index <= 3U && right_bits[index] != 0U) return right_bits[index];
    }

    /* The source only evaluates the left boundary when the right pass is
     * fully onscreen. */
    difference = (mysmb_u8)(game->ram[MYSMB_SCREEN_LEFT_X] -
                             game->ram[MYSMB_ENEMY_X + slot]);
    borrow = game->ram[MYSMB_SCREEN_LEFT_X] < game->ram[MYSMB_ENEMY_X + slot] ? 1U : 0U;
    page_difference = (mysmb_u8)(game->ram[MYSMB_SCREEN_LEFT_PAGE] -
                                  game->ram[MYSMB_ENEMY_PAGE + slot] - borrow);
    if ((page_difference & 0x80U) != 0U) return 0U;
    if (page_difference != 0U) return 0xffU;
    index = (mysmb_u8)(difference >> 3U);
    if (index > 7U) index = 7U;
    return left_bits[index];
}

/* ROM GetEnemyOffscreenBits / GetOffScreenBitsSet.  The object RAM stores
 * horizontal edge bits in the low nybble and vertical edge bits in the high
 * nybble.  Rendering callers intentionally keep using the X-only helper. */
mysmb_u8 mysmb_objects_get_enemy_offscreen_bits(
    const struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 data[9] = { 0U,8U,12U,14U,15U,7U,3U,1U,0U };
    static const mysmb_u8 defaults[3] = { 4U,0U,4U };
    static const mysmb_u8 high_units[2] = { 0xffU,0U };
    mysmb_u8 edge;
    mysmb_u8 difference;
    mysmb_u8 page_difference;
    mysmb_u8 borrow;
    mysmb_u8 index;
    mysmb_u8 bits;

    for (edge = 1U;; --edge) {
        difference = (mysmb_u8)(high_units[edge] -
                                 game->ram[MYSMB_ENEMY_Y + slot]);
        borrow = high_units[edge] < game->ram[MYSMB_ENEMY_Y + slot] ?
            1U : 0U;
        page_difference = (mysmb_u8)(1U -
            game->ram[MYSMB_ENEMY_Y_HIGH + slot] - borrow);
        index = defaults[edge];
        if ((page_difference & 0x80U) == 0U) {
            index = defaults[(mysmb_u8)(edge + 1U)];
            if (page_difference == 0U && difference < 0x20U) {
                index = (mysmb_u8)(difference >> 3U);
                if (edge == 0U) index = (mysmb_u8)(index + 4U);
            }
        }
        bits = data[index];
        if (bits != 0U || edge == 0U) {
            return (mysmb_u8)(mysmb_objects_get_enemy_x_offscreen_bits(game,
                                                                          slot) |
                             (mysmb_u8)(bits << 4U));
        }
    }
}
/* ROM GetEnemyBoundBox / GetMaskedOffScrBits.  It is kept in a separate
 * compilation unit so the 16-bit OpenNT compiler can retain objects.c below
 * its per-segment code limit. */
void mysmb_objects_update_enemy_bounding_box(struct mysmb_game *game,
                                             mysmb_u8 slot)
{
    mysmb_u8 x_difference;
    mysmb_u8 page_difference;
    mysmb_u8 borrow;
    mysmb_u8 mask;
    mysmb_u8 masked;
    mysmb_u16 address;

    x_difference = (mysmb_u8)(game->ram[MYSMB_ENEMY_X + slot] -
                               game->ram[MYSMB_SCREEN_LEFT_X]);
    borrow = 0U;
    if (game->ram[MYSMB_ENEMY_X + slot] < game->ram[MYSMB_SCREEN_LEFT_X]) {
        borrow = 1U;
    }
    page_difference = (mysmb_u8)(game->ram[MYSMB_ENEMY_PAGE + slot] -
                                  game->ram[MYSMB_SCREEN_LEFT_PAGE] - borrow);
    mask = 0x44U;
    if (page_difference < 0x80U && (page_difference != 0U || x_difference != 0U)) {
        mask = 0x48U;
    }
    masked = (mysmb_u8)(mask & game->ram[MYSMB_ENEMY_OFFSCREEN_BITS + slot]);
    game->ram[MYSMB_ENEMY_OFFSCREEN_BITS_MASKED + slot] = masked;
    address = (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + slot * 4U);
    if (masked != 0U) {
        game->ram[address] = 0xffU;
        game->ram[address + 1U] = 0xffU;
        game->ram[address + 2U] = 0xffU;
        game->ram[address + 3U] = 0xffU;
        return;
    }
    mysmb_objects_set_bounding_box(game, address,
        game->ram[MYSMB_ENEMY_BOUND_BOX + slot],
        game->ram[0x03aeU + slot], game->ram[0x03b9U + slot]);

    /* ROM CheckRightScreenBBox / CheckLeftScreenBBox clips the two
     * horizontal collision corners after BoundingBoxCore. */
    x_difference = (mysmb_u8)(game->ram[MYSMB_SCREEN_LEFT_X] + 0x80U);
    borrow = game->ram[MYSMB_SCREEN_LEFT_X] >= 0x80U ? 1U : 0U;
    page_difference = (mysmb_u8)(game->ram[MYSMB_SCREEN_LEFT_PAGE] + borrow);
    if (((mysmb_u16)game->ram[MYSMB_ENEMY_PAGE + slot] << 8U |
         game->ram[MYSMB_ENEMY_X + slot]) >=
        ((mysmb_u16)page_difference << 8U | x_difference)) {
        if ((game->ram[address + 2U] & 0x80U) == 0U) {
            if ((game->ram[address] & 0x80U) == 0U) {
                game->ram[address] = 0xffU;
            }
            game->ram[address + 2U] = 0xffU;
        }
    }
    else if ((game->ram[address] & 0x80U) != 0U &&
             game->ram[address] >= 0xa0U) {
        if ((game->ram[address + 2U] & 0x80U) != 0U) {
            game->ram[address + 2U] = 0U;
        }
        game->ram[address] = 0U;
    }
}

/* ROM $d91e OffscreenBoundsCheck / EraseEnemyObject.  The source uses the
 * processor carry from its byte-wise ADC/SBC sequence; retain that sequence
 * here instead of comparing host-width world coordinates. */
static mysmb_u8 mysmb_enemy_bounds_sbc(mysmb_u8 value, mysmb_u8 subtrahend,
                                       mysmb_u8 carry_in, mysmb_u8 *carry_out)
{
    mysmb_u16 operand;

    operand = (mysmb_u16)subtrahend + (carry_in != 0U ? 0U : 1U);
    *carry_out = value >= operand ? 1U : 0U;
    return (mysmb_u8)(value - operand);
}

void mysmb_objects_check_enemy_offscreen_bounds(struct mysmb_game *game,
                                                mysmb_u8 slot)
{
    mysmb_u8 id;
    mysmb_u8 carry;
    mysmb_u16 sum;
    mysmb_u8 left_x;
    mysmb_u8 left_page;
    mysmb_u8 right_x;
    mysmb_u8 right_page;
    mysmb_u8 difference;

    if (slot >= 6U) return;
    id = game->ram[0x0016U + slot];
    if (id == 20U) return; /* FlyingCheepCheep */

    /* Carry after CPY #HammerBro / CPY #PiranhaPlant. */
    carry = id >= 5U ? 1U : 0U;
    if (id != 5U) carry = id >= 13U ? 1U : 0U;
    left_x = game->ram[MYSMB_SCREEN_LEFT_X];
    if (id == 5U || id == 13U) {
        sum = (mysmb_u16)left_x + 0x38U + carry;
        left_x = (mysmb_u8)sum;
        carry = sum > 0xffU ? 1U : 0U;
    }
    left_x = mysmb_enemy_bounds_sbc(left_x, 0x48U, carry, &carry);
    left_page = mysmb_enemy_bounds_sbc(game->ram[MYSMB_SCREEN_LEFT_PAGE],
                                       0U, carry, &carry);

    /* The carry leaving the preceding SBC is also the carry consumed by
     * the source's ADC #$48 for ScreenRight_X_Pos. */
    sum = (mysmb_u16)game->ram[0x071dU] + 0x48U + carry;
    right_x = (mysmb_u8)sum;
    carry = sum > 0xffU ? 1U : 0U;
    sum = (mysmb_u16)game->ram[0x071bU] + carry;
    right_page = (mysmb_u8)sum;

    carry = game->ram[MYSMB_ENEMY_X + slot] >= left_x ? 1U : 0U;
    difference = mysmb_enemy_bounds_sbc(game->ram[MYSMB_ENEMY_PAGE + slot],
                                        left_page, carry, &carry);
    if ((difference & 0x80U) != 0U) goto erase;

    carry = game->ram[MYSMB_ENEMY_X + slot] >= right_x ? 1U : 0U;
    difference = mysmb_enemy_bounds_sbc(game->ram[MYSMB_ENEMY_PAGE + slot],
                                        right_page, carry, &carry);
    if ((difference & 0x80U) != 0U) return;
    if (game->ram[0x001eU + slot] == 5U || id == 13U || id == 48U ||
        id == 49U || id == 50U) return;

erase:
    game->ram[0x000fU + slot] = 0U;
    game->ram[0x0016U + slot] = 0U;
    game->ram[0x001eU + slot] = 0U;
    game->ram[0x0110U + slot] = 0U;
    game->ram[0x0796U + slot] = 0U;
    game->ram[0x0125U + slot] = 0U;
    game->ram[0x03c5U + slot] = 0U;
    game->ram[0x078eU + slot] = 0U;
}
