#include "core/oam/oam.h"
#include "core/game.h"

/* ROM helper inputs are prepared by GetMiscOffscreenBits and
 * RelativeMiscPosition; DrawHammer itself is $e4dc-$e540. */
enum {
    MYSMB_HAMMER_MISC_STATE = 0x002aU,
    MYSMB_HAMMER_MISC_PAGE = 0x007aU,
    MYSMB_HAMMER_MISC_X = 0x0093U,
    MYSMB_HAMMER_MISC_Y_HIGH = 0x00c2U,
    MYSMB_HAMMER_MISC_Y = 0x00dbU,
    MYSMB_HAMMER_REL_X = 0x03b3U,
    MYSMB_HAMMER_REL_Y = 0x03beU,
    MYSMB_HAMMER_OFFSCREEN = 0x03d6U,
    MYSMB_HAMMER_SPRITE_OFFSET = 0x06f3U,
    MYSMB_HAMMER_FRAME_COUNTER = 0x0009U,
    MYSMB_HAMMER_TIMER_CONTROL = 0x0747U,
    MYSMB_HAMMER_OBJECT_OFFSET = 0x0008U,
    MYSMB_HAMMER_SCREEN_LEFT_PAGE = 0x071aU,
    MYSMB_HAMMER_SCREEN_RIGHT_PAGE = 0x071bU,
    MYSMB_HAMMER_SCREEN_LEFT_X = 0x071cU,
    MYSMB_HAMMER_SCREEN_RIGHT_X = 0x071dU
};

static mysmb_u8 mysmb_hammer_x_offscreen(const struct mysmb_game *game,
                                         mysmb_u8 slot)
{
    static const mysmb_u8 bits[16] = {
        0x7fU, 0x3fU, 0x1fU, 0x0fU, 0x07U, 0x03U, 0x01U, 0x00U,
        0x80U, 0xc0U, 0xe0U, 0xf0U, 0xf8U, 0xfcU, 0xfeU, 0xffU
    };
    mysmb_u8 edge;
    mysmb_u8 low_diff;
    mysmb_u8 borrow;
    mysmb_u8 index;
    signed char page_diff;

    for (edge = 1U;; --edge) {
        low_diff = (mysmb_u8)(game->ram[MYSMB_HAMMER_SCREEN_LEFT_X + edge] -
                               game->ram[MYSMB_HAMMER_MISC_X + slot]);
        borrow = game->ram[MYSMB_HAMMER_SCREEN_LEFT_X + edge] <
                 game->ram[MYSMB_HAMMER_MISC_X + slot] ? 1U : 0U;
        page_diff = (signed char)((mysmb_u8)(
            game->ram[MYSMB_HAMMER_SCREEN_LEFT_PAGE + edge] -
            game->ram[MYSMB_HAMMER_MISC_PAGE + slot] - borrow));
        index = edge != 0U ? 15U : 7U;
        if (page_diff >= 0) {
            index = edge != 0U ? 7U : 15U;
            if (page_diff < 1 && low_diff < 0x38U) {
                index = (mysmb_u8)(low_diff >> 3U);
                if (edge == 0U) index = (mysmb_u8)(index + 8U);
            }
        }
        if (bits[index] != 0U || edge == 0U) return bits[index];
    }
}

static mysmb_u8 mysmb_hammer_y_offscreen(const struct mysmb_game *game,
                                         mysmb_u8 slot)
{
    static const mysmb_u8 bits[9] = {
        0x00U, 0x08U, 0x0cU, 0x0eU, 0x0fU, 0x07U, 0x03U, 0x01U, 0x00U
    };
    mysmb_u8 edge;
    mysmb_u8 edge_y;
    mysmb_u8 low_diff;
    mysmb_u8 borrow;
    mysmb_u8 index;
    signed char unit_diff;

    for (edge = 1U;; --edge) {
        edge_y = edge != 0U ? 0U : 0xffU;
        low_diff = (mysmb_u8)(edge_y - game->ram[MYSMB_HAMMER_MISC_Y + slot]);
        borrow = edge_y < game->ram[MYSMB_HAMMER_MISC_Y + slot] ? 1U : 0U;
        unit_diff = (signed char)((mysmb_u8)(1U -
            game->ram[MYSMB_HAMMER_MISC_Y_HIGH + slot] - borrow));
        index = edge != 0U ? 0U : 4U;
        if (unit_diff >= 0) {
            index = 0U;
            if (unit_diff < 1 && low_diff < 0x20U) {
                index = (mysmb_u8)(low_diff >> 3U);
                if (edge == 0U) index = (mysmb_u8)(index + 4U);
            }
        }
        if (bits[index] != 0U || edge == 0U) return bits[index];
    }
}

void mysmb_objects_prepare_hammer(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 relative_x;
    mysmb_u8 relative_y;
    mysmb_u8 offscreen;

    relative_x = (mysmb_u8)(game->ram[MYSMB_HAMMER_MISC_X + slot] -
                             game->ram[MYSMB_HAMMER_SCREEN_LEFT_X]);
    relative_y = game->ram[MYSMB_HAMMER_MISC_Y + slot];
    game->ram[MYSMB_HAMMER_REL_X] = relative_x;
    game->ram[MYSMB_HAMMER_REL_Y] = relative_y;
    offscreen = (mysmb_u8)((mysmb_hammer_y_offscreen(game, slot) << 4U) |
                            (mysmb_hammer_x_offscreen(game, slot) >> 4U));
    game->ram[MYSMB_HAMMER_OFFSCREEN] = offscreen;
}

void mysmb_objects_draw_hammer(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 first_x[4] = { 4U, 0U, 4U, 0U };
    static const mysmb_u8 first_y[4] = { 0U, 4U, 0U, 4U };
    static const mysmb_u8 second_x[4] = { 0U, 8U, 0U, 8U };
    static const mysmb_u8 second_y[4] = { 8U, 0U, 8U, 0U };
    static const mysmb_u8 first_tile[4] = { 0x80U, 0x82U, 0x81U, 0x83U };
    static const mysmb_u8 second_tile[4] = { 0x81U, 0x83U, 0x80U, 0x82U };
    static const mysmb_u8 attribute[4] = { 3U, 3U, 0xc3U, 0xc3U };
    mysmb_u8 oam;
    mysmb_u8 pose;
    mysmb_u8 relative_x;
    mysmb_u8 relative_y;
    mysmb_u8 offscreen;

    oam = game->ram[MYSMB_HAMMER_SPRITE_OFFSET + slot];
    pose = 0U;
    if (game->ram[MYSMB_HAMMER_TIMER_CONTROL] == 0U &&
        (game->ram[MYSMB_HAMMER_MISC_STATE + slot] & 0x7fU) == 1U) {
        pose = (mysmb_u8)((game->ram[MYSMB_HAMMER_FRAME_COUNTER] >> 2U) & 3U);
    }
    relative_y = game->ram[MYSMB_HAMMER_REL_Y];
    game->ram[(mysmb_u16)(0x0200U + oam)] = (mysmb_u8)(relative_y + first_y[pose]);
    game->ram[(mysmb_u16)(0x0204U + oam)] = (mysmb_u8)(relative_y + first_y[pose] + second_y[pose]);
    relative_x = game->ram[MYSMB_HAMMER_REL_X];
    game->ram[(mysmb_u16)(0x0203U + oam)] = (mysmb_u8)(relative_x + first_x[pose]);
    game->ram[(mysmb_u16)(0x0207U + oam)] = (mysmb_u8)(relative_x + first_x[pose] + second_x[pose]);
    game->ram[(mysmb_u16)(0x0201U + oam)] = first_tile[pose];
    game->ram[(mysmb_u16)(0x0205U + oam)] = second_tile[pose];
    game->ram[(mysmb_u16)(0x0202U + oam)] = attribute[pose];
    game->ram[(mysmb_u16)(0x0206U + oam)] = attribute[pose];
    slot = game->ram[MYSMB_HAMMER_OBJECT_OFFSET];
    offscreen = game->ram[MYSMB_HAMMER_OFFSCREEN];
    if ((offscreen & 0xfcU) != 0U) {
        game->ram[MYSMB_HAMMER_MISC_STATE + slot] = 0U;
        mysmb_oam_dump_two_sprites(game, 0xf8U, oam);
    }
    mysmb_text_observer_record(game, MYSMB_TEXT_OBSERVE_HAMMER,
        0U, slot, pose, 1U, oam, 2U, 0U);
}
