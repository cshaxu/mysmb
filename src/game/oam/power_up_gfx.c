#include "game/oam/oam.h"
#include "game/oam/enemy_offscreen_tail.h"
#include "game/game.h"

enum {
    MYSMB_POWER_UP_TYPE = 0x0039U,
    MYSMB_ENEMY_PAGE = 0x006eU,
    MYSMB_ENEMY_X = 0x0087U,
    MYSMB_ENEMY_Y = 0x00cfU,
    MYSMB_ENEMY_ATTRIBUTES = 0x03c5U,
    MYSMB_ENEMY_SPRITE_OFFSET = 0x06e5U,
    MYSMB_ENEMY_OFFSCREEN = 0x03d1U,
    MYSMB_POWER_UP_SLOT = 5U,
    MYSMB_SCREEN_LEFT_PAGE = 0x071aU,
    MYSMB_SCREEN_LEFT_X = 0x071cU,
    MYSMB_FRAME_COUNTER = 0x0009U
};

/* DrawPowerUp falls through PUpOfs into SprObjectOffscrChk.  That routine
 * has a three-row enemy layout even though this caller draws two rows: its
 * third-row stores still clear stale OAM exactly as the original jump does. */
static void mysmb_power_up_apply_offscreen(struct mysmb_game *game,
                                           mysmb_u8 oam, mysmb_u8 bits)
{
    mysmb_oam_enemy_offscreen_tail(game, oam, bits);
}
/* ROM DrawPowerUp. */
void mysmb_objects_draw_power_up(struct mysmb_game *game)
{
    static const mysmb_u8 graphics[16] = {
        0x76U, 0x77U, 0x78U, 0x79U,
        0xd6U, 0xd6U, 0xd9U, 0xd9U,
        0x8dU, 0x8dU, 0xe4U, 0xe4U,
        0x76U, 0x77U, 0x78U, 0x79U
    };
    static const mysmb_u8 attributes[4] = { 2U, 1U, 2U, 1U };
    const mysmb_u8 slot = MYSMB_POWER_UP_SLOT;
    mysmb_u8 offset;
    mysmb_u8 type;
    mysmb_u8 base_attributes;
    mysmb_u8 phase_attributes;
    mysmb_u8 x;
    mysmb_u8 y;
    mysmb_u8 graphics_offset;
    mysmb_u8 row;
    mysmb_u8 row_offset;

    type = game->ram[MYSMB_POWER_UP_TYPE];
    /* RunPUSubs has just populated the fixed Enemy_Rel_* scratch cells. */
    x = game->ram[0x03aeU];
    y = (mysmb_u8)(game->ram[0x03b9U] + 8U);
    offset = game->ram[MYSMB_ENEMY_SPRITE_OFFSET + slot];
    base_attributes = (mysmb_u8)(attributes[type] | game->ram[MYSMB_ENEMY_ATTRIBUTES + slot]);
    graphics_offset = (mysmb_u8)(type << 2U);
    game->ram[2U] = y;
    game->ram[5U] = x;
    game->ram[4U] = base_attributes;
    game->ram[7U] = 1U;
    game->ram[3U] = 1U;
    row_offset = offset;
    for (row = 0U; row < 2U; ++row) {
        game->ram[0U] = graphics[graphics_offset];
        game->ram[1U] = graphics[(mysmb_u8)(graphics_offset + 1U)];
        mysmb_oam_draw_sprite_object(game, &graphics_offset, &row_offset);
        game->ram[7U]--;
    }
    if (type == 1U || type == 2U) {
        phase_attributes = (mysmb_u8)(((game->ram[MYSMB_FRAME_COUNTER] >> 1U) & 3U) |
                                       game->ram[MYSMB_ENEMY_ATTRIBUTES + slot]);
        game->ram[(mysmb_u16)(0x0202U + offset)] = phase_attributes;
        game->ram[(mysmb_u16)(0x0206U + offset)] = (mysmb_u8)(phase_attributes | 0x40U);
        if (type == 2U) {
            game->ram[(mysmb_u16)(0x020aU + offset)] = phase_attributes;
            game->ram[(mysmb_u16)(0x020eU + offset)] = phase_attributes;
        }
        /* FlipPUpRightSide runs for both flower and star.  For the flower
         * its lower row retains the base palette before this OR, which is
         * why the source still changes that otherwise undrawn-looking byte. */
        game->ram[(mysmb_u16)(0x020eU + offset)] = (mysmb_u8)(
            game->ram[(mysmb_u16)(0x020eU + offset)] | 0x40U);
    }
    mysmb_power_up_apply_offscreen(game, offset,
                                   game->ram[MYSMB_ENEMY_OFFSCREEN]);
}



