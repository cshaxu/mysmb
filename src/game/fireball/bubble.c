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

/* Original $B74B/$B74D movement-force and timer data, indexed by $07. */
static const mysmb_u8 mysmb_bubble_force[2] = { 0xffU, 0x50U };
static const mysmb_u8 mysmb_bubble_timer[2] = { 0x40U, 0x20U };

/* An entrance caller's X can alias the zero-page random selector. Preserve
 * the original absolute-Y read beyond the two normal random-bit entries
 * through the already-bound full PRG, rather than indexing a two-byte C array. */
static mysmb_u8 mysmb_bubble_lookup(const struct mysmb_game *game,
                                  mysmb_u16 base, const mysmb_u8 *normal)
{
    mysmb_u8 index;
    index = game->ram[0x0007U];
    if (index < 2U) return normal[index];
    if (game->area_prg != 0 && game->area_prg_size > base + index)
        return game->area_prg[base + index];
    return 0U;
}

/* Original bubble position arrays use zero-page indexed operands, so their
 * base plus caller X wraps within page zero even on the entrance path. */

/* MoveBubl/Y_Bubl: SetupBubble falls through here even if initial Y is F8. */
static void mysmb_bubble_move(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 force;
    mysmb_u8 old_value;
    mysmb_u8 y;
    force = mysmb_bubble_lookup(game, 0x374bU, mysmb_bubble_force);
    old_value = game->ram[MYSMB_BUBBLE_Y_DUMMY + slot];
    game->ram[MYSMB_BUBBLE_Y_DUMMY + slot] = (mysmb_u8)(old_value - force);
    y = (mysmb_u8)(game->ram[(mysmb_u8)(MYSMB_BUBBLE_Y + slot)] -
                   (old_value < force ? 1U : 0U));
    game->ram[(mysmb_u8)(MYSMB_BUBBLE_Y + slot)] = y < 0x20U ? 0xf8U : y;
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
    game->ram[(mysmb_u8)(MYSMB_BUBBLE_X + slot)] = (mysmb_u8)(old_x + x_adder);
    game->ram[(mysmb_u8)(MYSMB_BUBBLE_PAGE + slot)] = (mysmb_u8)(
        game->ram[MYSMB_BUBBLE_PLAYER_PAGE] +
        (game->ram[(mysmb_u8)(MYSMB_BUBBLE_X + slot)] < old_x ? 1U : 0U));
    game->ram[(mysmb_u8)(MYSMB_BUBBLE_Y + slot)] =
        (mysmb_u8)(game->ram[MYSMB_BUBBLE_PLAYER_Y] + 8U);
    game->ram[(mysmb_u8)(MYSMB_BUBBLE_Y_HIGH + slot)] = 1U;
    game->ram[MYSMB_BUBBLE_TIMER] = mysmb_bubble_lookup(game, 0x374dU,
                                                    mysmb_bubble_timer);
    mysmb_bubble_move(game, slot);
}

void mysmb_fireball_check_bubble(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 random_bit;
    random_bit = (mysmb_u8)(game->ram[MYSMB_BUBBLE_RANDOM + 1U + slot] & 1U);
    game->ram[0x0007U] = random_bit;
    if (game->ram[(mysmb_u8)(MYSMB_BUBBLE_Y + slot)] != 0xf8U)
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
    mysmb_oam_get_bubble_offscreen_bits(game, slot);
}

void mysmb_fireball_draw_bubble(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 oam;
    if (game->ram[MYSMB_BUBBLE_PLAYER_Y_HIGH] == 1U &&
        (game->ram[MYSMB_BUBBLE_OFFSCREEN] & 8U) == 0U) {
        oam = game->ram[MYSMB_BUBBLE_SPRITE_OFFSET + slot];
        /* ROM DrawBubble stores X, Y, tile and attributes in that order. */
        game->ram[0x0203U + oam] = game->ram[MYSMB_BUBBLE_REL_X];
        game->ram[0x0200U + oam] = game->ram[MYSMB_BUBBLE_REL_Y];
        game->ram[0x0201U + oam] = 0x74U;
        game->ram[0x0202U + oam] = 2U;
        mysmb_text_observer_record(game, MYSMB_TEXT_OBSERVE_BUBBLE,
            0U, slot, 0U, 1U, oam, 1U, 0U);
    }
}
