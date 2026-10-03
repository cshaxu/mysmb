#include "game/fireball/fireball.h"

#include "game/oam/oam.h"
#include "game/world/world.h"

enum {
    MYSMB_PLAYER_STATUS = 0x0756U,
    MYSMB_PLAYER_X = 0x0086U,
    MYSMB_PLAYER_PAGE = 0x006dU,
    MYSMB_PLAYER_Y = 0x00ceU,
    MYSMB_PLAYER_FACING = 0x0033U,
    MYSMB_PLAYER_ANIMATION = 0x0781U,
    MYSMB_FIREBALL_THROWING_TIMER = 0x0711U,
    MYSMB_PLAYER_ANIM_TIMER_SET = 0x070cU,
    MYSMB_FIREBALL_STATE = 0x0024U,
    MYSMB_FIREBALL_X_SPEED = 0x005eU,
    MYSMB_FIREBALL_PAGE = 0x0074U,
    MYSMB_FIREBALL_X = 0x008dU,
    MYSMB_FIREBALL_Y_SPEED = 0x00a6U,
    MYSMB_FIREBALL_Y_HIGH = 0x00bcU,
    MYSMB_FIREBALL_Y = 0x00d5U,
    MYSMB_FIREBALL_BOUNCE = 0x003aU,
    MYSMB_FIREBALL_COUNTER = 0x06ceU,
    MYSMB_FIREBALL_BOUND_BOX = 0x04a0U,
    MYSMB_FIREBALL_REL_X = 0x03afU,
    MYSMB_FIREBALL_REL_Y = 0x03baU,
    MYSMB_FIREBALL_OFFSCREEN_BITS = 0x03d2U,
    MYSMB_BOUNDING_BOX_PLAYER = 0x04acU,
    MYSMB_SQUARE1_SOUND = 0x00ffU
};
/* ROM $B687 FireballXSpdData; PlayerFacingDir is 1 (right) or 2 (left). */
static const mysmb_u8 mysmb_fireball_x_speed[2] = { 0x40U, 0xc0U };

/* ROM $B689-$B6F8 FireballObjCore/RunFB/EraseFB/NoFBall/FireballExplosion.
 * Children retain their own original-source proof obligations. */
void mysmb_fireball_step_object(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 state;
    mysmb_u8 old_value;
    mysmb_u8 speed_index;
    mysmb_u16 speed_address;
    game->ram[0x0008U] = slot;
    state = game->ram[MYSMB_FIREBALL_STATE + slot];
    if ((state & 0x80U) != 0U) {
        mysmb_oam_relative_fireball_position(game, slot);
        mysmb_oam_draw_fireball_explosion(game, slot);
        return;
    }
    if (state == 0U) return;
    if (state != 1U) {
        old_value = game->ram[MYSMB_PLAYER_X];
        game->ram[MYSMB_FIREBALL_X + slot] = (mysmb_u8)(old_value + 4U);
        game->ram[MYSMB_FIREBALL_PAGE + slot] =
            (mysmb_u8)(game->ram[MYSMB_PLAYER_PAGE] +
                        (game->ram[MYSMB_FIREBALL_X + slot] < old_value ? 1U : 0U));
        game->ram[MYSMB_FIREBALL_Y + slot] = game->ram[MYSMB_PLAYER_Y];
        game->ram[MYSMB_FIREBALL_Y_HIGH + slot] = 1U;
        /* DEY is a byte index into the original ROM, including adjacent
         * bytes when simultaneous directions publish facing value three. */
        speed_index = (mysmb_u8)(game->ram[MYSMB_PLAYER_FACING] - 1U);
        if (speed_index < 2U) {
            game->ram[MYSMB_FIREBALL_X_SPEED + slot] =
                mysmb_fireball_x_speed[speed_index];
        } else {
            speed_address = (mysmb_u16)(0x3687U + speed_index);
            game->ram[MYSMB_FIREBALL_X_SPEED + slot] =
                game->area_prg != 0 && speed_address < game->area_prg_size ?
                game->area_prg[speed_address] : 0U;
        }
        game->ram[MYSMB_FIREBALL_Y_SPEED + slot] = 4U;
        game->ram[MYSMB_FIREBALL_BOUND_BOX + slot] = 7U;
        --game->ram[MYSMB_FIREBALL_STATE + slot];
    }
    /* ROM FireballObjCore: TXA; ADC #$07 selects this fireball's
     * SprObject fields, then delegates to ImposeGravity and
     * MoveObjectHorizontally before restoring ObjectOffset. */
    mysmb_world_impose_gravity_spr_object(game, (mysmb_u8)(7U + slot),
                                           0x50U, 3U);
    mysmb_world_move_spr_object_horizontally(game, (mysmb_u8)(7U + slot));
    slot = game->ram[0x0008U];
    /* FireballObjCore order: relative coordinates, offscreen bits and
     * bounding box precede FireballBGCollision. */
    mysmb_oam_relative_fireball_position(game, slot);
    mysmb_oam_get_fireball_offscreen_bits(game, slot);
    mysmb_world_get_fireball_bounding_box(game, slot);
    mysmb_world_fireball_background_collision(game, slot);
    if ((game->ram[MYSMB_FIREBALL_OFFSCREEN_BITS] & 0xccU) != 0U) {
        game->ram[MYSMB_FIREBALL_STATE + slot] = 0U;
        return;
    }
    mysmb_world_fireball_enemy_collision(game, slot);
    /* FireballObjCore draws only after background and enemy collision. */
    mysmb_oam_draw_fireball(game, slot);
}
