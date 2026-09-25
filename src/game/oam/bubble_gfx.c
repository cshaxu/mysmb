#include "game/game.h"

/* ROM $98?? ProcAirBubbles, BubbleCheck, RelativeBubblePosition,
 * GetBubbleOffscreenBits and DrawBubble.  This stays separate from the
 * fireball motion owner so both the 16-bit core and frame OAM writer use the
 * original fixed bubble arrays. */
enum {
    MYSMB_BUBBLE_AREA_TYPE = 0x074eU,
    MYSMB_BUBBLE_TIMER = 0x0792U,
    MYSMB_BUBBLE_RANDOM = 0x07a7U,
    MYSMB_BUBBLE_PLAYER_FACING = 0x0033U,
    MYSMB_BUBBLE_PLAYER_PAGE = 0x006dU,
    MYSMB_BUBBLE_PLAYER_X = 0x0086U,
    MYSMB_BUBBLE_PLAYER_Y = 0x00ceU,
    MYSMB_BUBBLE_PLAYER_Y_HIGH = 0x00b5U,
    MYSMB_BUBBLE_PAGE = 0x0083U,
    MYSMB_BUBBLE_X = 0x009cU,
    MYSMB_BUBBLE_Y_HIGH = 0x00cbU,
    MYSMB_BUBBLE_Y = 0x00e4U,
    MYSMB_BUBBLE_Y_DUMMY = 0x042cU,
    MYSMB_BUBBLE_REL_X = 0x03b0U,
    MYSMB_BUBBLE_REL_Y = 0x03bbU,
    MYSMB_BUBBLE_OFFSCREEN = 0x03d3U,
    MYSMB_BUBBLE_SPRITE_OFFSET = 0x06eeU,
    MYSMB_BUBBLE_SCREEN_LEFT_PAGE = 0x071aU,
    MYSMB_BUBBLE_SCREEN_LEFT_X = 0x071cU,
    MYSMB_BUBBLE_SCREEN_RIGHT_PAGE = 0x071bU,
    MYSMB_BUBBLE_SCREEN_RIGHT_X = 0x071dU
};

static mysmb_u8 mysmb_bubble_x_offscreen(const struct mysmb_game *game,
                                          mysmb_u8 slot)
{
    static const mysmb_u8 bits[16] = {
        0x7fU, 0x3fU, 0x1fU, 0x0fU, 0x07U, 0x03U, 0x01U, 0x00U,
        0x80U, 0xc0U, 0xe0U, 0xf0U, 0xf8U, 0xfcU, 0xfeU, 0xffU
    };
    mysmb_u8 edge;
    mysmb_u8 difference;
    mysmb_u8 borrow;
    mysmb_u8 page_difference;
    mysmb_u8 index;

    edge = 1U;
    for (;;) {
        difference = (mysmb_u8)(game->ram[MYSMB_BUBBLE_SCREEN_LEFT_X + edge] -
                                game->ram[MYSMB_BUBBLE_X + slot]);
        borrow = game->ram[MYSMB_BUBBLE_SCREEN_LEFT_X + edge] <
            game->ram[MYSMB_BUBBLE_X + slot] ? 1U : 0U;
        page_difference = (mysmb_u8)(
            game->ram[MYSMB_BUBBLE_SCREEN_LEFT_PAGE + edge] -
            game->ram[MYSMB_BUBBLE_PAGE + slot] - borrow);
        index = edge != 0U ? 15U : 7U;
        if ((page_difference & 0x80U) == 0U) {
            index = edge != 0U ? 7U : 15U;
            if (page_difference == 0U && difference < 0x38U) {
                index = (mysmb_u8)(difference >> 3U);
                if (edge == 0U) index = (mysmb_u8)(index + 8U);
            }
        }
        if (bits[index] != 0U || edge == 0U) return bits[index];
        edge = 0U;
    }
}

static mysmb_u8 mysmb_bubble_y_offscreen(const struct mysmb_game *game,
                                          mysmb_u8 slot)
{
    static const mysmb_u8 bits[9] = {
        0x00U, 0x08U, 0x0cU, 0x0eU, 0x0fU, 0x07U, 0x03U, 0x01U, 0x00U
    };
    mysmb_u8 edge;
    mysmb_u8 edge_y;
    mysmb_u8 difference;
    mysmb_u8 borrow;
    mysmb_u8 unit_difference;
    mysmb_u8 index;

    edge = 1U;
    for (;;) {
        edge_y = edge != 0U ? 0U : 0xffU;
        difference = (mysmb_u8)(edge_y - game->ram[MYSMB_BUBBLE_Y + slot]);
        borrow = edge_y < game->ram[MYSMB_BUBBLE_Y + slot] ? 1U : 0U;
        unit_difference = (mysmb_u8)(1U -
            game->ram[MYSMB_BUBBLE_Y_HIGH + slot] - borrow);
        index = edge != 0U ? 0U : 4U;
        if ((unit_difference & 0x80U) == 0U) {
            index = 0U;
            if (unit_difference == 0U && difference < 0x20U) {
                index = (mysmb_u8)(difference >> 3U);
                if (edge == 0U) index = (mysmb_u8)(index + 4U);
            }
        }
        if (bits[index] != 0U || edge == 0U) return bits[index];
        edge = 0U;
    }
}

void mysmb_objects_step_bubbles(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u8 random_bit;
    mysmb_u8 old_value;
    mysmb_u8 borrow;
    mysmb_u8 x_adder;
    mysmb_u8 oam;

    if (game->ram[MYSMB_BUBBLE_AREA_TYPE] != 0U) return;
    slot = 2U;
    do {
        random_bit = (mysmb_u8)(game->ram[MYSMB_BUBBLE_RANDOM + 1U + slot] & 1U);
        if (game->ram[MYSMB_BUBBLE_Y + slot] == 0xf8U &&
            game->ram[MYSMB_BUBBLE_TIMER] == 0U) {
            x_adder = (game->ram[MYSMB_BUBBLE_PLAYER_FACING] & 1U) != 0U ?
                8U : 0U;
            old_value = game->ram[MYSMB_BUBBLE_PLAYER_X];
            game->ram[MYSMB_BUBBLE_X + slot] = (mysmb_u8)(old_value + x_adder);
            game->ram[MYSMB_BUBBLE_PAGE + slot] = (mysmb_u8)(
                game->ram[MYSMB_BUBBLE_PLAYER_PAGE] +
                (game->ram[MYSMB_BUBBLE_X + slot] < old_value ? 1U : 0U));
            game->ram[MYSMB_BUBBLE_Y + slot] =
                (mysmb_u8)(game->ram[MYSMB_BUBBLE_PLAYER_Y] + 8U);
            game->ram[MYSMB_BUBBLE_Y_HIGH + slot] = 1U;
            game->ram[MYSMB_BUBBLE_TIMER] = random_bit != 0U ? 0x20U : 0x40U;
        }
        if (game->ram[MYSMB_BUBBLE_Y + slot] != 0xf8U) {
            old_value = game->ram[MYSMB_BUBBLE_Y_DUMMY + slot];
            game->ram[MYSMB_BUBBLE_Y_DUMMY + slot] = (mysmb_u8)(old_value -
                (random_bit != 0U ? 0x50U : 0xffU));
            borrow = old_value < (random_bit != 0U ? 0x50U : 0xffU) ? 1U : 0U;
            game->ram[MYSMB_BUBBLE_Y + slot] = (mysmb_u8)(
                game->ram[MYSMB_BUBBLE_Y + slot] - borrow);
            if (game->ram[MYSMB_BUBBLE_Y + slot] < 0x20U) {
                game->ram[MYSMB_BUBBLE_Y + slot] = 0xf8U;
            }
        }
        game->ram[MYSMB_BUBBLE_REL_X + slot] = (mysmb_u8)(
            game->ram[MYSMB_BUBBLE_X + slot] - game->ram[MYSMB_BUBBLE_SCREEN_LEFT_X]);
        game->ram[MYSMB_BUBBLE_REL_Y + slot] = game->ram[MYSMB_BUBBLE_Y + slot];
        game->ram[MYSMB_BUBBLE_OFFSCREEN + slot] = (mysmb_u8)(
            (mysmb_bubble_y_offscreen(game, slot) << 4U) |
            (mysmb_bubble_x_offscreen(game, slot) >> 4U));
        if (game->ram[MYSMB_BUBBLE_PLAYER_Y_HIGH] == 1U &&
            (game->ram[MYSMB_BUBBLE_OFFSCREEN + slot] & 8U) == 0U) {
            oam = game->ram[MYSMB_BUBBLE_SPRITE_OFFSET + slot];
            game->ram[0x0200U + oam] = game->ram[MYSMB_BUBBLE_REL_Y + slot];
            game->ram[0x0201U + oam] = 0x74U;
            game->ram[0x0202U + oam] = 2U;
            game->ram[0x0203U + oam] = game->ram[MYSMB_BUBBLE_REL_X + slot];
        }
        slot--;
    } while (slot != 0xffU);
}