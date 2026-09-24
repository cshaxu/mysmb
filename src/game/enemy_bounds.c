#include "game/objects.h"

enum {
    MYSMB_SCREEN_LEFT_X = 0x071cU,
    MYSMB_SCREEN_LEFT_PAGE = 0x071aU,
    MYSMB_ENEMY_X = 0x0087U,
    MYSMB_ENEMY_PAGE = 0x006eU,
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
    static const mysmb_u8 left_bits[8] = {
        0x80U, 0xc0U, 0xe0U, 0xf0U, 0xf8U, 0xfcU, 0xfeU, 0xffU
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
    if ((page_difference & 0x80U) != 0U || page_difference != 0U) return 0x0fU;
    index = difference == 0U ? 0U : (mysmb_u8)((difference - 1U) >> 3U);
    if (index > 3U) index = 3U;
    if (right_bits[index] != 0U) return right_bits[index];

    /* The source only evaluates the left boundary when the right pass is
     * fully onscreen. */
    difference = (mysmb_u8)(game->ram[MYSMB_SCREEN_LEFT_X] -
                             game->ram[MYSMB_ENEMY_X + slot]);
    borrow = game->ram[MYSMB_SCREEN_LEFT_X] < game->ram[MYSMB_ENEMY_X + slot] ? 1U : 0U;
    page_difference = (mysmb_u8)(game->ram[MYSMB_SCREEN_LEFT_PAGE] -
                                  game->ram[MYSMB_ENEMY_PAGE + slot] - borrow);
    if ((page_difference & 0x80U) != 0U) return 0U;
    if (page_difference != 0U) return 0xffU;
    index = difference == 0U ? 0U : (mysmb_u8)((difference - 1U) >> 3U);
    if (index > 7U) index = 7U;
    return left_bits[index];
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
}
