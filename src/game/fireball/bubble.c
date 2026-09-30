#include "game/fireball/fireball.h"
#include "game/oam/oam.h"

/* ROM $B6F9-$B74E: BubbleCheck, SetupBubble, PosBubl, MoveBubl,
 * Y_Bubl, ExitBubl and their two data tables.
 * The later relative-position/offscreen/OAM leaves consume these fixed bubble
 * arrays without introducing a platform-specific game path. */
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

/* Original $B74B/$B74D movement-force and timer data, indexed by $07. */
static const mysmb_u8 mysmb_bubble_force[2] = { 0xffU, 0x50U };
static const mysmb_u8 mysmb_bubble_timer[2] = { 0x40U, 0x20U };

/* MoveBubl/Y_Bubl: SetupBubble falls through here even if initial Y is F8. */
static void mysmb_bubble_move(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 force;
    mysmb_u8 old_value;
    mysmb_u8 y;
    force = mysmb_bubble_force[game->ram[0x0007U]];
    old_value = game->ram[MYSMB_BUBBLE_Y_DUMMY + slot];
    game->ram[MYSMB_BUBBLE_Y_DUMMY + slot] = (mysmb_u8)(old_value - force);
    y = (mysmb_u8)(game->ram[MYSMB_BUBBLE_Y + slot] -
                   (old_value < force ? 1U : 0U));
    game->ram[MYSMB_BUBBLE_Y + slot] = y < 0x20U ? 0xf8U : y;
}

/* Direct entry used by Entrance_GameTimerSetup and by BubbleCheck after the
 * timer permits a new bubble. The caller supplies the ROM X register slot;
 * RAM $07 remains the exact random-bit input selected by BubbleCheck. */
void mysmb_fireball_setup_bubble(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 x_adder;
    mysmb_u8 old_x;

    /* LSR PlayerFacing leaves its former bit 0 in carry.  The following
     * TYA preserves it, so the source ADC contributes nine pixels while
     * facing right (Y = 8 plus carry = 1), and zero while facing left. */
    x_adder = (game->ram[MYSMB_BUBBLE_PLAYER_FACING] & 1U) != 0U ? 9U : 0U;
    old_x = game->ram[MYSMB_BUBBLE_PLAYER_X];
    game->ram[MYSMB_BUBBLE_X + slot] = (mysmb_u8)(old_x + x_adder);
    game->ram[MYSMB_BUBBLE_PAGE + slot] = (mysmb_u8)(
        game->ram[MYSMB_BUBBLE_PLAYER_PAGE] +
        (game->ram[MYSMB_BUBBLE_X + slot] < old_x ? 1U : 0U));
    game->ram[MYSMB_BUBBLE_Y + slot] =
        (mysmb_u8)(game->ram[MYSMB_BUBBLE_PLAYER_Y] + 8U);
    game->ram[MYSMB_BUBBLE_Y_HIGH + slot] = 1U;
    game->ram[MYSMB_BUBBLE_TIMER] = mysmb_bubble_timer[game->ram[0x0007U]];
    mysmb_bubble_move(game, slot);
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

/* Original BubbleCheck: always publish the selected random bit, then either
 * move, return while the creation timer is live, or enter SetupBubble. */
void mysmb_fireball_check_bubble(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 random_bit;
    random_bit = (mysmb_u8)(game->ram[MYSMB_BUBBLE_RANDOM + 1U + slot] & 1U);
    game->ram[0x0007U] = random_bit;
    if (game->ram[MYSMB_BUBBLE_Y + slot] != 0xf8U)
        mysmb_bubble_move(game, slot);
    else if (game->ram[MYSMB_BUBBLE_TIMER] == 0U)
        mysmb_fireball_setup_bubble(game, slot);
}

void mysmb_fireball_relative_bubble_position(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_relative_bubble_position(game, slot);
}

void mysmb_fireball_get_bubble_offscreen_bits(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_BUBBLE_OFFSCREEN] = (mysmb_u8)(
        (mysmb_bubble_y_offscreen(game, slot) << 4U) |
        (mysmb_bubble_x_offscreen(game, slot) >> 4U));
}

void mysmb_fireball_draw_bubble(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 oam;
    if (game->ram[MYSMB_BUBBLE_PLAYER_Y_HIGH] == 1U &&
        (game->ram[MYSMB_BUBBLE_OFFSCREEN] & 8U) == 0U) {
        oam = game->ram[MYSMB_BUBBLE_SPRITE_OFFSET + slot];
        game->ram[0x0200U + oam] = game->ram[MYSMB_BUBBLE_REL_Y];
        game->ram[0x0201U + oam] = 0x74U;
        game->ram[0x0202U + oam] = 2U;
        game->ram[0x0203U + oam] = game->ram[MYSMB_BUBBLE_REL_X];
    }
}
