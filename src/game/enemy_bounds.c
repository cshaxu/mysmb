#include "game/enemy/platform.h"
#include "game/objects.h"
#include "game/world/world.h"

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

/* Original horizontal table byte. LargePlatformBoundBox consumes the raw
 * byte; the ordinary offscreen composition consumes its high nibble.
 * This value helper retains the existing const ABI; original scratch writes
 * remain the separately tracked GetXOffscreenBits obligation. */
static mysmb_u8 enemy_x_offscreen_raw(const struct mysmb_game *game,
                                     mysmb_u8 slot)
{
    static const mysmb_u8 bits[16] = {
        0x7fU,0x3fU,0x1fU,0x0fU,7U,3U,1U,0U,
        0x80U,0xc0U,0xe0U,0xf0U,0xf8U,0xfcU,0xfeU,0xffU
    };
    static const mysmb_u8 defaults[3] = {7U,15U,7U};
    mysmb_u8 edge, difference, page, borrow, index, value;
    for (edge = 1U;; --edge) {
        difference = (mysmb_u8)(game->ram[0x071cU + edge] -
                                  game->ram[MYSMB_ENEMY_X + slot]);
        borrow = game->ram[0x071cU + edge] <
                 game->ram[MYSMB_ENEMY_X + slot] ? 1U : 0U;
        page = (mysmb_u8)(game->ram[0x071aU + edge] -
                            game->ram[MYSMB_ENEMY_PAGE + slot] - borrow);
        index = defaults[edge];
        if ((page & 0x80U) == 0U) {
            index = defaults[(mysmb_u8)(edge + 1U)];
            if (page == 0U && difference < 0x38U) {
                index = (mysmb_u8)(difference >> 3U);
                if (edge == 0U) index = (mysmb_u8)(index + 8U);
            }
        }
        value = bits[index];
        if (value != 0U || edge == 0U) return value;
    }
}

mysmb_u8 mysmb_objects_get_enemy_x_offscreen_bits(
    const struct mysmb_game *game, mysmb_u8 slot)
{
    return (mysmb_u8)(enemy_x_offscreen_raw(game, slot) >> 4U);
}

/* ROM GetEnemyOffscreenBits / GetOffScreenBitsSet.  The object RAM stores
 * horizontal edge bits in the low nybble and vertical edge bits in the high
 * nybble; callers select this complete result when their source path does. */
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
static void enemy_masked_box(struct mysmb_game *game, mysmb_u8 slot,
                              mysmb_u8 left_mask, mysmb_u8 right_mask)
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
    mask = left_mask;
    if (page_difference < 0x80U && (page_difference != 0U || x_difference != 0U)) {
        mask = right_mask;
    }
    masked = (mysmb_u8)(mask & game->ram[MYSMB_ENEMY_OFFSCREEN_BITS]);
    game->ram[MYSMB_ENEMY_OFFSCREEN_BITS_MASKED + slot] = masked;
    address = (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + slot * 4U);
    if (masked != 0U) {
        game->ram[address] = 0xffU;
        game->ram[address + 1U] = 0xffU;
        game->ram[address + 2U] = 0xffU;
        game->ram[address + 3U] = 0xffU;
        return;
    }
    mysmb_world_set_bounding_box(game, address,
        game->ram[MYSMB_ENEMY_BOUND_BOX + slot],
        game->ram[0x03aeU], game->ram[0x03b9U]);

    mysmb_world_clip_bounding_box_to_screen(game, address,
        game->ram[MYSMB_ENEMY_PAGE + slot], game->ram[MYSMB_ENEMY_X + slot]);
}

/* Existing common box/clip children retain their own conformance status. */
void mysmb_objects_update_enemy_bounding_box(struct mysmb_game *game,
                                             mysmb_u8 slot)
{
    enemy_masked_box(game, slot, 0x44U, 0x48U);
}

/* SmallPlatformBoundBox selects the original horizontal-only masks. */
void mysmb_platform_box_small(struct mysmb_game *game, mysmb_u8 slot)
{
    enemy_masked_box(game, slot, 4U, 8U);
}

/* LargePlatformBoundBox uses the raw horizontal byte, never the composed
 * nibble: $F0/$F8/$FC are still partial visibility, while $FE/$FF hide the box. */
void mysmb_platform_box_large(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u16 address;
    address = (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + slot * 4U);
    if (enemy_x_offscreen_raw(game, slot) >= 0xfeU) {
        game->ram[address] = 0xffU;
        game->ram[address + 1U] = 0xffU;
        game->ram[address + 2U] = 0xffU;
        game->ram[address + 3U] = 0xffU;
        return;
    }
    mysmb_world_set_bounding_box(game, address,
        game->ram[MYSMB_ENEMY_BOUND_BOX + slot],
        game->ram[0x03aeU], game->ram[0x03b9U]);
    mysmb_world_clip_bounding_box_to_screen(game, address,
        game->ram[MYSMB_ENEMY_PAGE + slot], game->ram[MYSMB_ENEMY_X + slot]);
}

/* ROM $d91e OffscreenBoundsCheck / EraseEnemyObject.  The source uses the
 * processor carry from its byte-wise ADC/SBC sequence; retain that sequence
 * here instead of comparing host-width world coordinates. */
