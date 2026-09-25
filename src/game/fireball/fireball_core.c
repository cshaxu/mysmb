#include "game/fireball/fireball.h"

#include "game/oam/oam.h"
#include "game/world/world.h"

enum {
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
/* ROM GetFireballBoundBox.  GetProperObjOffset makes slot zero/one use
 * controls $04a0/$04a1 and output boxes $04c8/$04cc; the relative source
 * inputs remain the fixed Fireball_Rel_* pair. */
static void mysmb_fireball_get_bounding_box(struct mysmb_game *game,
                                                     mysmb_u8 slot)
{
    mysmb_world_set_bounding_box(
        game, (mysmb_u16)(MYSMB_BOUNDING_BOX_PLAYER + (7U + slot) * 4U),
        game->ram[MYSMB_FIREBALL_BOUND_BOX + slot],
        game->ram[MYSMB_FIREBALL_REL_X], game->ram[MYSMB_FIREBALL_REL_Y]);
}
/* ROM FireballObjCore ($6352), excluding OAM.
 * Both objects use the original fixed slots. */
void mysmb_fireball_step(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u8 state;
    mysmb_u8 old_value;
    mysmb_u8 enemy_slot;

    mysmb_fireball_try_spawn(game);
    for (slot = 0U; slot < 2U; ++slot) {
        state = game->ram[MYSMB_FIREBALL_STATE + slot];
        if (state == 0U) continue;
        if ((state & 0x80U) != 0U) {
            mysmb_u8 explosion_index;

            explosion_index = (mysmb_u8)((state >> 1U) & 7U);
            game->ram[MYSMB_FIREBALL_STATE + slot] = (mysmb_u8)(state + 1U);
            if (explosion_index >= 3U) game->ram[MYSMB_FIREBALL_STATE + slot] = 0U;
            else {
                mysmb_oam_relative_fireball_position(game, slot);
                mysmb_oam_draw_fireball_explosion(game, slot,
                    (mysmb_u8)(0x68U - explosion_index));
            }
            continue;
        }
        if (state == 2U) {
            old_value = game->ram[MYSMB_PLAYER_X];
            game->ram[MYSMB_FIREBALL_X + slot] = (mysmb_u8)(old_value + 4U);
            game->ram[MYSMB_FIREBALL_PAGE + slot] =
                (mysmb_u8)(game->ram[MYSMB_PLAYER_PAGE] +
                            (game->ram[MYSMB_FIREBALL_X + slot] < old_value ? 1U : 0U));
            game->ram[MYSMB_FIREBALL_Y + slot] = game->ram[MYSMB_PLAYER_Y];
            game->ram[MYSMB_FIREBALL_Y_HIGH + slot] = 1U;
            game->ram[MYSMB_FIREBALL_X_SPEED + slot] =
                game->ram[MYSMB_PLAYER_FACING] == MYSMB_BUTTON_RIGHT ? 0x40U : 0xc0U;
            game->ram[MYSMB_FIREBALL_Y_SPEED + slot] = 4U;
            game->ram[MYSMB_FIREBALL_BOUND_BOX + slot] = 7U;
            game->ram[MYSMB_FIREBALL_STATE + slot] = 1U;
        }
        /* ROM FireballObjCore: TXA; ADC #$07 selects this fireball's
         * SprObject fields, then delegates to ImposeGravity and
         * MoveObjectHorizontally before restoring ObjectOffset. */
        mysmb_world_impose_gravity_spr_object(game, (mysmb_u8)(7U + slot),
                                               0x50U, 3U);
        mysmb_world_move_spr_object_horizontally(game, (mysmb_u8)(7U + slot));
        /* FireballObjCore order: relative coordinates, offscreen bits and
         * bounding box precede FireballBGCollision. */
        mysmb_oam_relative_fireball_position(game, slot);
        mysmb_oam_get_fireball_offscreen_bits(game, slot);
        mysmb_fireball_get_bounding_box(game, slot);
        mysmb_world_fireball_background_collision(game, slot);
        if ((game->ram[MYSMB_FIREBALL_OFFSCREEN_BITS] & 0xccU) != 0U) {
            game->ram[MYSMB_FIREBALL_STATE + slot] = 0U;
            continue;
        }
        if (mysmb_world_fireball_enemy_collision(game, slot, &enemy_slot) != 0U) {
            /* ROM FireballEnemyCollision immediately enters HandleEnemyFBallCol
             * after it changes Fireball_State.  The effect owner remains a
             * named cross-slice call until its state/score chain migrates. */
            mysmb_world_handle_fireball_enemy_hit(game, enemy_slot);
        }
        /* FireballObjCore draws only after background and enemy collision. */
        mysmb_oam_draw_fireball(game, slot);
    }
    mysmb_fireball_step_bubbles(game);
}
