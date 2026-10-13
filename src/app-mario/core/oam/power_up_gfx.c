#include "core/oam/oam.h"
#include "core/game.h"

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
        mysmb_oam_draw_one_sprite_row(game,
            graphics[(mysmb_u8)(graphics_offset + 1U)],
            &graphics_offset, &row_offset);
        game->ram[7U]--;
    }
    if (type == 1U || type == 2U) {
        game->ram[0U] = type;
        phase_attributes = (mysmb_u8)(((game->ram[MYSMB_FRAME_COUNTER] >> 1U) & 3U) |
                                       game->ram[MYSMB_ENEMY_ATTRIBUTES + slot]);
        game->ram[(mysmb_u16)(0x0202U + offset)] = phase_attributes;
        game->ram[(mysmb_u16)(0x0206U + offset)] = phase_attributes;
        if (type == 2U) {
            game->ram[(mysmb_u16)(0x020aU + offset)] = phase_attributes;
            game->ram[(mysmb_u16)(0x020eU + offset)] = phase_attributes;
        }
        /* FlipPUpRightSide runs for both flower and star.  For the flower
         * its lower row retains the base palette before this OR, which is
         * why the source still changes that otherwise undrawn-looking byte. */
        game->ram[(mysmb_u16)(0x0206U + offset)] = (mysmb_u8)(
            game->ram[(mysmb_u16)(0x0206U + offset)] | 0x40U);
        game->ram[(mysmb_u16)(0x020eU + offset)] = (mysmb_u8)(
            game->ram[(mysmb_u16)(0x020eU + offset)] | 0x40U);
    }
    /* Original PUpOfs tail enters the shared three-row/erase contract. */
    mysmb_oam_sprite_object_offscreen_check(game, offset);
    mysmb_text_observer_record(game, MYSMB_TEXT_OBSERVE_POWERUP, type, slot,
        (mysmb_u8)(type << 2U), 1U, offset, 4U, 0U);
}
