#include "game/enemy/background.h"
#include "game/enemy/platform.h"
#include "game/enemy/core.h"
#include "game/score.h"
#include "game/blocks/head.h"
#include "game/enemy/actor_slots.h"
#include "game/objects.h"
#include "game/status.h"
#include "game/enemy/movement.h"
#include "game/enemy/frenzy.h"
#include "game/oam/oam.h"
#include "game/world/world.h"
#include "game/area.h"

enum {
    MYSMB_VRAM_BUFFER1 = 0x0300U,
    MYSMB_VRAM_BUFFER1_DATA = 0x0301U,
    MYSMB_BLOCK_ORIGINAL_Y = 0x03e4U,
    MYSMB_BLOCK_BUFFER_LOW = 0x03e6U,
    MYSMB_BLOCK_METATILE = 0x03e8U,
    MYSMB_BLOCK_REPLACE_FLAG = 0x03ecU,
    MYSMB_BLOCK_STATE = 0x0026U,
    MYSMB_BLOCK_Y_SPEED = 0x00a8U,
    MYSMB_BLOCK_Y_HIGH = 0x00beU,
    MYSMB_BLOCK_Y = 0x00d7U,
    MYSMB_BLOCK_Y_DUMMY = 0x041fU,
    MYSMB_BLOCK_Y_FORCE = 0x043cU,
    MYSMB_BLOCK_X_SPEED = 0x0060U,
    MYSMB_BLOCK_X_FORCE = 0x0409U,
    MYSMB_BLOCK_PAGE = 0x0076U,
    MYSMB_BLOCK_X = 0x008fU,
    MYSMB_BLOCK_PAGE_COPY = 0x03eaU,
    MYSMB_BLOCK_SLOT_CONTROL = 0x03eeU,
    MYSMB_BLOCK_BOUNCE_TIMER = 0x0784U,
    MYSMB_BRICK_COIN_TIMER = 0x079dU,
    MYSMB_BRICK_COIN_TIMER_FLAG = 0x06bcU,
    MYSMB_BLOCK_ORIGINAL_X = 0x03f1U,
    MYSMB_PLAYER_SIZE = 0x0754U,
    MYSMB_PLAYER_CROUCHING = 0x0714U,
    MYSMB_PLAYER_PAGE = 0x006dU,
    MYSMB_PLAYER_X = 0x0086U,
    MYSMB_PLAYER_Y = 0x00ceU,
    MYSMB_PLAYER_Y_HIGH = 0x00b5U,
    MYSMB_PLAYER_Y_SPEED = 0x009fU,
    MYSMB_PLAYER_Y_FORCE = 0x0433U,
    MYSMB_PLAYER_X_SPEED = 0x0057U,
    MYSMB_PLAYER_MOVING_DIRECTION = 0x0045U
};

enum {
    MYSMB_BOWSER_BODY_CONTROLS = 0x0363U,
    MYSMB_BOWSER_FEET_TIMER = 0x0364U,
    MYSMB_BOWSER_FRONT_SLOT = 0x0368U,
    MYSMB_BRIDGE_COLLAPSE_OFFSET = 0x0369U,
    MYSMB_EVENT_MUSIC = 0x00fcU,
    MYSMB_NOISE_SOUND = 0x00fdU,
    MYSMB_SQUARE2_SOUND = 0x00feU,
    MYSMB_SQUARE1_SOUND = 0x00ffU
};

enum {
    MYSMB_MISC_STATE = 0x002aU,
    MYSMB_MISC_PAGE = 0x007aU,
    MYSMB_MISC_X = 0x0093U,
    MYSMB_MISC_Y_SPEED = 0x00acU,
    MYSMB_MISC_Y_HIGH = 0x00c2U,
    MYSMB_MISC_Y = 0x00dbU,
    MYSMB_MISC_X_SPEED = 0x0064U,
    MYSMB_MISC_X_FORCE = 0x040dU,
    MYSMB_MISC_Y_DUMMY = 0x0423U,
    MYSMB_MISC_Y_FORCE = 0x0440U,
    MYSMB_MISC_BOUND_BOX = 0x04a2U,
    MYSMB_MISC_COLLISION_FLAG = 0x06beU,
    MYSMB_MISC_SPRITE_OFFSET = 0x06f3U,
    MYSMB_HAMMER_ENEMY_OFFSET = 0x06aeU,
    MYSMB_HAMMER_THROWING_TIMER = 0x03a2U,
    MYSMB_SCROLL_AMOUNT = 0x0775U,
    MYSMB_OPERATING_MODE = 0x0770U,
    MYSMB_DISPLAY_DIGITS = 0x07d7U,
    MYSMB_DIGIT_MODIFIER = 0x0134U,
    MYSMB_CURRENT_PLAYER = 0x0753U,
    MYSMB_COIN_TALLY_FOR_1UPS = 0x0748U,
    MYSMB_COIN_TALLY = 0x075eU,
    MYSMB_NUMBER_OF_LIVES = 0x075aU,
    MYSMB_POWER_UP_TYPE = 0x0039U,
    MYSMB_ENEMY_FLAG = 0x000fU,
    MYSMB_ENEMY_ID = 0x0016U,
    MYSMB_ENEMY_STATE = 0x001eU,
    MYSMB_ENEMY_MOVING_DIRECTION = 0x0046U,
    MYSMB_ENEMY_X_SPEED = 0x0058U,
    MYSMB_ENEMY_PAGE = 0x006eU,
    MYSMB_ENEMY_X = 0x0087U,
    MYSMB_ENEMY_Y_HIGH = 0x00b6U,
    MYSMB_ENEMY_Y = 0x00cfU,
    MYSMB_ENEMY_Y_SPEED = 0x00a0U,
    MYSMB_ENEMY_Y_DUMMY = 0x0417U,
    MYSMB_ENEMY_Y_FORCE = 0x0434U,
    MYSMB_ENEMY_ATTRIBUTES = 0x03c5U,
    MYSMB_ENEMY_BOUND_BOX = 0x049aU,
    MYSMB_ENEMY_COLLISION_BITS = 0x0491U,
    MYSMB_ENEMY_OFFSCREEN_BITS_MASKED = 0x03d8U,
    MYSMB_ENEMY_X_FORCE = 0x0401U,
    MYSMB_PLAYER_BOUND_BOX = 0x0499U,
    MYSMB_PLAYER_OFFSCREEN_BITS = 0x03d0U,
    MYSMB_SCREEN_LEFT_PAGE = 0x071aU,
    MYSMB_SCREEN_LEFT_X = 0x071cU,
    MYSMB_BOUNDING_BOX_PLAYER = 0x04acU,
    MYSMB_BOUNDING_BOX_ENEMY = 0x04b0U,
    MYSMB_PLAYER_STATUS = 0x0756U,
    MYSMB_GAME_ENGINE_SUBROUTINE = 0x000eU,
    MYSMB_PLAYER_STATE = 0x001dU,
    MYSMB_TIMER_CONTROL = 0x0747U,
    MYSMB_FRAME_COUNTER = 0x0009U,
    MYSMB_STAR_INVINCIBLE_TIMER = 0x079fU,
    MYSMB_INJURY_TIMER = 0x079eU,
    MYSMB_STOMP_CHAIN_COUNTER = 0x0484U,
    MYSMB_STOMP_TIMER = 0x0791U,
    MYSMB_ENEMY_INTERVAL_TIMER = 0x0796U,
    MYSMB_SHELL_CHAIN_COUNTER = 0x0125U,
    MYSMB_AREA_TYPE = 0x074eU,
    MYSMB_ENEMY_FRENZY_BUFFER = 0x06cbU,
    MYSMB_LAKITU_REAPPEAR_TIMER = 0x06d1U,
    MYSMB_FRENZY_ENEMY_TIMER = 0x078fU,
    MYSMB_SCREEN_RIGHT_PAGE = 0x071bU,
    MYSMB_SCREEN_RIGHT_X = 0x071dU,
    MYSMB_PRIMARY_HARD = 0x076aU,
    MYSMB_SECONDARY_HARD = 0x06ccU,
    MYSMB_VINE_FLAG_OFFSET = 0x0398U,
    MYSMB_VINE_HEIGHT = 0x0399U,
    MYSMB_VINE_OBJECT_OFFSET = 0x039aU,
    MYSMB_VINE_START_Y = 0x039dU,
    MYSMB_FIREBALL_STATE = 0x0024U,
    MYSMB_FIREBALL_X_SPEED = 0x005eU,
    MYSMB_FIREBALL_PAGE = 0x0074U,
    MYSMB_FIREBALL_X = 0x008dU,
    MYSMB_FIREBALL_Y_SPEED = 0x00a6U,
    MYSMB_FIREBALL_Y_HIGH = 0x00bcU,
    MYSMB_FIREBALL_Y = 0x00d5U,
    MYSMB_FIREBALL_X_FORCE = 0x0407U,
    MYSMB_FIREBALL_Y_DUMMY = 0x041dU,
    MYSMB_FIREBALL_Y_FORCE = 0x043aU,
    MYSMB_FIREBALL_BOUNCE = 0x003aU,
    MYSMB_FIREBALL_COUNTER = 0x06ceU,
    MYSMB_FIREBALL_BOUND_BOX = 0x04a0U,
    MYSMB_FIREBALL_REL_X = 0x03afU,
    MYSMB_FIREBALL_REL_Y = 0x03baU,
    MYSMB_FIREBALL_OFFSCREEN_BITS = 0x03d2U,
    MYSMB_FIREBALL_SPRITE_OFFSET = 0x06f1U,
    MYSMB_PLAYER_A_B = 0x000aU,
    MYSMB_PREVIOUS_A_B = 0x000dU,
    MYSMB_PLAYER_FACING = 0x0033U,
    MYSMB_PLAYER_ANIM_TIMER_SET = 0x070cU,
    MYSMB_PLAYER_ANIMATION = 0x070dU,
    MYSMB_FLOATEY_NUM_CONTROL = 0x0110U,
    MYSMB_FLOATEY_NUM_X = 0x0117U,
    MYSMB_FLOATEY_NUM_Y = 0x011eU,
    MYSMB_FLOATEY_NUM_TIMER = 0x012cU,
    MYSMB_ENEMY_SPRITE_OFFSET = 0x06e5U,
    MYSMB_ALT_SPRITE_OFFSET = 0x06ecU,
    MYSMB_SPRITE_OFFSET_CONTROL = 0x03eeU
};


void mysmb_objects_step_normal_enemy_terrain(struct mysmb_game *game,
                                            mysmb_u8 slot);
static mysmb_u8 mysmb_objects_set_player_enemy_collision_boxes(struct mysmb_game *game,
                                                                mysmb_u8 slot);
void mysmb_objects_kill_enemy_above_block(struct mysmb_game *game,
                                          mysmb_u8 enemy_slot);
void mysmb_objects_turn_enemy(struct mysmb_game *game, mysmb_u8 slot);


/* Retained aggregate test adapters. Production enters PlayerEnemyCollision
 * with one current slot and prepared boxes. These adapters only prepare
 * legacy test inputs; every response goes through that same shared owner. */
static void legacy_player_contact(struct mysmb_game *game, mysmb_u8 slot)
{
    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        mysmb_objects_set_player_enemy_collision_boxes(game, slot) == 0U) return;
    game->ram[8U] = slot;
    mysmb_oam_relative_enemy_position(game, slot);
    mysmb_objects_player_enemy_current(game, slot, 1U);
}

void mysmb_objects_check_hazard_enemy_collision(struct mysmb_game *game)
{
    mysmb_u8 slot, id;
    for (slot = 0U; slot < 5U; ++slot) {
        id = game->ram[MYSMB_ENEMY_ID + slot];
        if (id == 10U || id == 11U || id == 12U || id == 13U || id == 18U) legacy_player_contact(game, slot);
    }
}

void mysmb_objects_check_bullet_bill_stomp(struct mysmb_game *game)
{
    mysmb_u8 slot, id;
    for (slot = 0U; slot < 5U; ++slot) {
        id = game->ram[MYSMB_ENEMY_ID + slot];
        if (id == 8U) legacy_player_contact(game, slot);
    }
}

void mysmb_objects_check_bloober_stomp(struct mysmb_game *game)
{
    mysmb_u8 slot, id;
    for (slot = 0U; slot < 5U; ++slot) {
        id = game->ram[MYSMB_ENEMY_ID + slot];
        if (id == 7U) legacy_player_contact(game, slot);
    }
}

void mysmb_objects_check_lakitu_stomp(struct mysmb_game *game)
{
    mysmb_u8 slot, id;
    for (slot = 0U; slot < 5U; ++slot) {
        id = game->ram[MYSMB_ENEMY_ID + slot];
        if (id == 17U) legacy_player_contact(game, slot);
    }
}

void mysmb_objects_check_hammer_bro_stomp(struct mysmb_game *game)
{
    mysmb_u8 slot, id;
    for (slot = 0U; slot < 5U; ++slot) {
        id = game->ram[MYSMB_ENEMY_ID + slot];
        if (id == 5U) legacy_player_contact(game, slot);
    }
}

void mysmb_objects_check_paratroopa_stomp(struct mysmb_game *game)
{
    mysmb_u8 slot, id;
    for (slot = 0U; slot < 5U; ++slot) {
        id = game->ram[MYSMB_ENEMY_ID + slot];
        if (id == 14U || id == 15U || id == 16U) legacy_player_contact(game, slot);
    }
}

/* ROM JCoinGfxHandler / DrawFloateyNumber_Coin. */
void mysmb_objects_draw_jump_coin(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 oam_offset;
    mysmb_u8 relative_x;
    mysmb_u8 state;

    oam_offset = game->ram[MYSMB_MISC_SPRITE_OFFSET + slot];
    relative_x = game->ram[0x03b3U];
    state = game->ram[MYSMB_MISC_STATE + slot];
    if (state >= 2U) {
        if ((game->ram[MYSMB_FRAME_COUNTER] & 1U) == 0U) game->ram[MYSMB_MISC_Y + slot]--;
        game->ram[(mysmb_u16)(0x0200U + oam_offset)] = game->ram[MYSMB_MISC_Y + slot];
        game->ram[(mysmb_u16)(0x0204U + oam_offset)] = game->ram[MYSMB_MISC_Y + slot];
        game->ram[(mysmb_u16)(0x0201U + oam_offset)] = 0xf7U;
        game->ram[(mysmb_u16)(0x0205U + oam_offset)] = 0xfbU;
        game->ram[(mysmb_u16)(0x0202U + oam_offset)] = 2U;
        game->ram[(mysmb_u16)(0x0206U + oam_offset)] = 2U;
        game->ram[(mysmb_u16)(0x0203U + oam_offset)] = relative_x;
        game->ram[(mysmb_u16)(0x0207U + oam_offset)] = (mysmb_u8)(relative_x + 8U);
        return;
    }
    game->ram[(mysmb_u16)(0x0200U + oam_offset)] = game->ram[MYSMB_MISC_Y + slot];
    game->ram[(mysmb_u16)(0x0204U + oam_offset)] =
        (mysmb_u8)(game->ram[MYSMB_MISC_Y + slot] + 8U);
    game->ram[(mysmb_u16)(0x0201U + oam_offset)] =
        (mysmb_u8)(0x60U + ((game->ram[MYSMB_FRAME_COUNTER] >> 1U) & 3U));
    game->ram[(mysmb_u16)(0x0205U + oam_offset)] =
        game->ram[(mysmb_u16)(0x0201U + oam_offset)];
    game->ram[(mysmb_u16)(0x0202U + oam_offset)] = 2U;
    game->ram[(mysmb_u16)(0x0206U + oam_offset)] = 0x82U;
    game->ram[(mysmb_u16)(0x0203U + oam_offset)] = relative_x;
    game->ram[(mysmb_u16)(0x0207U + oam_offset)] = relative_x;
}
/* Existing clipped GetMiscBoundBox path used by jumping coins.
 * Exposing this boundary does not certify or alter its child algorithms. */
void mysmb_objects_get_coin_bounding_box(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_world_set_bounding_box(game,
        (mysmb_u16)(0x04d0U + slot * 4U),
        game->ram[MYSMB_MISC_BOUND_BOX + slot],
        game->ram[0x03b3U], game->ram[0x03beU]);
    mysmb_world_clip_bounding_box_to_screen(game,
        (mysmb_u16)(0x04d0U + slot * 4U),
        game->ram[MYSMB_MISC_PAGE + slot],
        game->ram[MYSMB_MISC_X + slot]);
}

/* Legacy ABI used by the cannon caller and aggregate tests. All response
 * logic belongs to the canonical current-slot PlayerEnemyCollision. */
mysmb_u8 mysmb_objects_check_normal_enemy_collision(struct mysmb_game *game,
    mysmb_u8 slot, mysmb_u8 preserve_collision_boxes)
{
    if (preserve_collision_boxes == 0U) legacy_player_contact(game, slot);
    else mysmb_objects_player_enemy_current(game, slot, 1U);
    return (mysmb_u8)(game->ram[0x0491U + game->ram[8U]] & 1U);
}

/* Existing walking-route bump and side-check children, extracted so the
 * admitted background entry shares them with the jumping-enemy route. */
void mysmb_objects_bump_enemy(struct mysmb_game *game, mysmb_u8 slot)
{
    /* ChkForBump_HammerBroJ -> RXSpd for this ordinary route. */
    if (slot != 5U && (game->ram[MYSMB_ENEMY_STATE + slot] & 0x80U) != 0U) {
        game->ram[MYSMB_SQUARE1_SOUND] = 2U;
    }
    game->ram[MYSMB_ENEMY_X_SPEED + slot] =
        (mysmb_u8)(0U - game->ram[MYSMB_ENEMY_X_SPEED + slot]);
    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] ^= 3U;
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_bullet_bills(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_ENEMY_FLAG + slot] != 0U &&
            game->ram[MYSMB_ENEMY_ID + slot] == 8U)
            mysmb_objects_step_bullet_bills_slot(game, slot);
        mysmb_objects_draw_bullet_bill(game, slot);
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_piranha_plants(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        mysmb_objects_draw_piranha(game, slot);
        if (game->ram[MYSMB_ENEMY_FLAG + slot] != 0U &&
            game->ram[MYSMB_ENEMY_ID + slot] == 13U)
            mysmb_objects_step_piranha_plants_slot(game, slot);
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_swimming_cheep_cheeps(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot)
        if (game->ram[MYSMB_ENEMY_FLAG + slot] != 0U &&
            (game->ram[MYSMB_ENEMY_ID + slot] == 10U ||
             game->ram[MYSMB_ENEMY_ID + slot] == 11U))
            mysmb_objects_step_swimming_cheep_cheeps_slot(game, slot);
}

/* Legacy aggregate filter; the source movement entry has no flag/ID gate. */
void mysmb_objects_step_podoboos(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_ENEMY_FLAG + slot] != 0U &&
            game->ram[MYSMB_ENEMY_ID + slot] == 12U)
            mysmb_objects_step_podoboos_slot(game, slot);
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_bloobers(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot)
        if (game->ram[MYSMB_ENEMY_FLAG + slot] != 0U &&
            game->ram[MYSMB_ENEMY_ID + slot] == 7U)
            mysmb_objects_step_bloobers_slot(game, slot);
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_hammer_bros(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 6U; ++slot) {
        if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
            game->ram[MYSMB_ENEMY_ID + slot] != 5U) continue;
        if ((game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) == 0U)
            mysmb_objects_step_hammer_terrain(game, slot);
        mysmb_objects_step_hammer_bros_slot(game, slot);
    }
}

/* Legacy bulk eligibility; source callers use the shared movement entry. */
void mysmb_objects_step_jumping_paratroopas(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_ENEMY_FLAG + slot] != 0U &&
            game->ram[MYSMB_ENEMY_ID + slot] == 14U)
            mysmb_enemy_move_jumping(game, slot);
    }
}

void mysmb_objects_step_red_paratroopas(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_ENEMY_FLAG + slot] != 0U &&
            game->ram[MYSMB_ENEMY_ID + slot] == 15U)
            mysmb_objects_step_red_paratroopas_slot(game, slot);
    }
}

/* Legacy bulk eligibility; the source green actor has no flag/ID gate. */
void mysmb_objects_step_flying_green_paratroopas(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_ENEMY_FLAG + slot] != 0U &&
            game->ram[MYSMB_ENEMY_ID + slot] == 16U)
            mysmb_objects_step_flying_green_paratroopas_slot(game, slot);
    }
}

/* Legacy slot-five test entry. PowerUpObjHandler uses the canonical
 * current-slot contact function directly. */
void mysmb_objects_check_power_up_collision(struct mysmb_game *game)
{
    game->ram[8U] = 5U;
    mysmb_objects_player_enemy_current(game, 5U, 1U);
}

/* ROM $84c3 FloateyNumbersRoutine.  GameEngine invokes this once immediately
 * after EnemiesAndLoopsCore for the same ObjectOffset. */
void mysmb_objects_step_floatey_number(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 score_data[12] = {
        0xffU, 0x41U, 0x42U, 0x44U, 0x45U, 0x48U,
        0x31U, 0x32U, 0x34U, 0x35U, 0x38U, 0x00U
    };
    static const mysmb_u8 tile_data[24] = {
        0xffU, 0xffU, 0xf6U, 0xfbU, 0xf7U, 0xfbU,
        0xf8U, 0xfbU, 0xf9U, 0xfbU, 0xfaU, 0xfbU,
        0xf6U, 0x50U, 0xf7U, 0x50U, 0xf8U, 0x50U,
        0xf9U, 0x50U, 0xfaU, 0x50U, 0xfdU, 0xfeU
    };
    mysmb_u8 control;
    mysmb_u8 score;
    mysmb_u8 oam_offset;
    mysmb_u8 enemy_id;
    mysmb_u8 y;

    control = game->ram[MYSMB_FLOATEY_NUM_CONTROL + slot];
    if (control == 0U) return;
    if (control >= 0x0bU) {
        control = 0x0bU;
        game->ram[MYSMB_FLOATEY_NUM_CONTROL + slot] = control;
    }
    if (game->ram[MYSMB_FLOATEY_NUM_TIMER + slot] == 0U) {
        game->ram[MYSMB_FLOATEY_NUM_CONTROL + slot] = 0U;
        return;
    }
    if (game->ram[MYSMB_FLOATEY_NUM_TIMER + slot] == 0x2bU) {
        if (control == 0x0bU) {
            game->ram[MYSMB_NUMBER_OF_LIVES]++;
            game->ram[MYSMB_SQUARE2_SOUND] = 0x40U;
        }
        score = score_data[control];
        game->ram[MYSMB_DIGIT_MODIFIER + (score >> 4U)] =
            (mysmb_u8)(score & 0x0fU);
        (void)mysmb_score_add(game);
    }
    game->ram[MYSMB_FLOATEY_NUM_TIMER + slot]--;
    if (game->ram[MYSMB_FLOATEY_NUM_Y + slot] >= 0x18U) {
        game->ram[MYSMB_FLOATEY_NUM_Y + slot]--;
    }

    /* FloateyNumbersRoutine selects an alternate OAM group for ordinary
     * living enemies, Hammer Bros, and the larger enemy families. */
    oam_offset = game->ram[MYSMB_ENEMY_SPRITE_OFFSET + slot];
    enemy_id = game->ram[MYSMB_ENEMY_ID + slot];
    if (enemy_id == 5U ||
        (enemy_id != 9U && enemy_id != 10U && enemy_id != 11U &&
         enemy_id != 13U && enemy_id != 18U &&
         (enemy_id >= 9U || game->ram[MYSMB_ENEMY_STATE + slot] < 2U))) {
        oam_offset = game->ram[MYSMB_ALT_SPRITE_OFFSET +
            game->ram[MYSMB_SPRITE_OFFSET_CONTROL]];
    }

    /* CMP #$18 supplies the carry to the following SBC #$08: a number
     * in the status region subtracts nine; every other number subtracts
     * eight after its possible one-pixel rise. */
    y = game->ram[MYSMB_FLOATEY_NUM_Y + slot];
    y = (mysmb_u8)(y - (y < 0x18U ? 9U : 8U));
    game->ram[(mysmb_u16)(0x0200U + oam_offset)] = y;
    game->ram[(mysmb_u16)(0x0201U + oam_offset)] =
        tile_data[(mysmb_u8)(control << 1U)];
    game->ram[(mysmb_u16)(0x0202U + oam_offset)] = 2U;
    game->ram[(mysmb_u16)(0x0203U + oam_offset)] =
        game->ram[MYSMB_FLOATEY_NUM_X + slot];
    oam_offset = (mysmb_u8)(oam_offset + 4U);
    game->ram[(mysmb_u16)(0x0200U + oam_offset)] = y;
    game->ram[(mysmb_u16)(0x0201U + oam_offset)] =
        tile_data[(mysmb_u8)((control << 1U) + 1U)];
    game->ram[(mysmb_u16)(0x0202U + oam_offset)] = 2U;
    game->ram[(mysmb_u16)(0x0203U + oam_offset)] =
        (mysmb_u8)(game->ram[MYSMB_FLOATEY_NUM_X + slot] + 8U);
}
/* Direct owner test helper: production GameEngine uses the per-slot entry. */
void mysmb_objects_step_floatey_numbers(struct mysmb_game *game)
{
    mysmb_u8 slot;

    for (slot = 0U; slot < 6U; ++slot) {
        mysmb_objects_step_floatey_number(game, slot);
    }
}

/* Translation of ChkOverR's inline caller setup for InitBlock_XY_Pos,
 * followed by Setup_Vine with X=5/Y=0. This remains a shared game-object
 * helper: platform code neither manufactures the block coordinates nor
 * creates the vine. */
void mysmb_objects_start_entrance_vine(struct mysmb_game *game)
{
    mysmb_blocks_initialize_position(game, 0U);
    game->ram[MYSMB_BLOCK_Y] = 0xf0U;
    mysmb_objects_start_vine(game, 5U, 0U);
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_flying_cheep_cheeps(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_ENEMY_FLAG + slot] != 0U &&
            game->ram[MYSMB_ENEMY_ID + slot] == 20U &&
            (game->ram[MYSMB_TIMER_CONTROL] == 0U ||
             (game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U))
            mysmb_objects_step_flying_cheep_cheeps_slot(game, slot);
    }
}

/* Temporary aggregate caller preserves the legacy injury early exit.
 * The slot result is a compatibility signal, not a ROM return register. */
void mysmb_objects_step_firebars(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_ENEMY_FLAG + slot] != 0U &&
            game->ram[MYSMB_ENEMY_ID + slot] >= 27U &&
            game->ram[MYSMB_ENEMY_ID + slot] <= 31U &&
            mysmb_objects_step_firebars_slot(game, slot) != 0U) return;
    }
}

/* Legacy bulk interface selects the same native source caller as GameEngine. */
void mysmb_objects_step_platforms_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 id;
    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U) return;
    id = game->ram[MYSMB_ENEMY_ID + slot];
    if (id >= 36U && id <= 42U) mysmb_enemy_run_large_platform(game, slot);
    else if (id == 43U || id == 44U) mysmb_enemy_run_small_platform(game, slot);
}
void mysmb_objects_step_platforms(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot)
        mysmb_objects_step_platforms_slot(game, slot);
}

/* Legacy bulk caller; eligibility is outside the original RunBowser entry. */
void mysmb_objects_step_bowsers(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_ENEMY_FLAG + slot] != 0U &&
            game->ram[MYSMB_ENEMY_ID + slot] == 45U)
            mysmb_enemy_run_bowser(game, slot);
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_bowser_flames(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot)
        mysmb_objects_step_bowser_flames_slot(game, slot);
}

/* Legacy KillEnemyAboveBlock dependency. This existing approximation is
 * exposed without changing its body; S10 owns its original child semantics. */
void mysmb_objects_kill_enemy_above_block(struct mysmb_game *game,
                                          mysmb_u8 enemy_slot)
{
    if (game->ram[MYSMB_ENEMY_ID + enemy_slot] == 13U) game->ram[MYSMB_ENEMY_Y + enemy_slot] =
        (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + enemy_slot] + 0x18U);
    game->ram[MYSMB_ENEMY_Y_SPEED + enemy_slot] = 0xfdU;
    game->ram[MYSMB_ENEMY_Y_DUMMY + enemy_slot] = 0U;
    game->ram[MYSMB_ENEMY_Y_FORCE + enemy_slot] = 0U;
    game->ram[MYSMB_ENEMY_STATE + enemy_slot] =
        (mysmb_u8)((game->ram[MYSMB_ENEMY_STATE + enemy_slot] & 0x1fU) | 0x20U);
}

/* The admitted background buffer stores these pass-through metatiles as in
 * EnemyToBGCollisionDet. */
mysmb_u8 mysmb_objects_is_solid_terrain(mysmb_u8 tile)
{
    return tile != 0U && tile != 0x26U && tile != 0xc2U && tile != 0xc3U &&
           tile != 0x5fU && tile != 0x60U;
}

/* ROM $d9bd HammerBroBGColl.  This is deliberately run before the Hammer
 * movement route, matching RunNormalEnemies' EnemyToBGCollisionDet order. */
void mysmb_objects_step_hammer_terrain(struct mysmb_game *game,
                                              mysmb_u8 slot)
{
    struct mysmb_enemy_terrain terrain;
    mysmb_u8 tile;

    if ((game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U ||
        game->ram[MYSMB_ENEMY_Y + slot] < 6U) return;
    tile = mysmb_world_query_enemy_block(game, slot, 0x15U, 0U,
                                           &terrain) != 0U ? terrain.metatile : 0U;
    if (mysmb_objects_is_solid_terrain(tile) == 0U) {
        game->ram[MYSMB_ENEMY_STATE + slot] |= 1U;
        return;
    }
    if (game->ram[0x078aU + slot] != 0U) return;
    game->ram[MYSMB_ENEMY_STATE + slot] &= 0x88U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
    game->ram[MYSMB_ENEMY_Y_DUMMY + slot] = 0U;
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
    game->ram[MYSMB_ENEMY_Y + slot] =
        (mysmb_u8)((game->ram[MYSMB_ENEMY_Y + slot] & 0xf0U) | 8U);
}

/* Existing GetMiscBoundBox child seam. Screen-edge clipping remains an
 * independent child obligation; this extraction does not certify it. */
void mysmb_objects_get_hammer_bounding_box(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_world_set_bounding_box(game, (mysmb_u16)(0x04d0U + slot * 4U),
        game->ram[MYSMB_MISC_BOUND_BOX + slot], game->ram[0x03b3U],
        game->ram[0x03beU]);
}
/* ROM PlayerCollisionCore receives relative X coordinates.  Keep every
 * special-object path on the active 256-pixel screen before comparing its
 * one-byte boxes, otherwise equal low bytes on adjacent pages would collide. */
static mysmb_u8 mysmb_objects_set_player_enemy_collision_boxes(struct mysmb_game *game,
                                                                mysmb_u8 slot)
{
    mysmb_u16 player_world;
    mysmb_u16 enemy_world;
    mysmb_u16 screen_world;
    mysmb_u16 enemy_box;

    player_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_PLAYER_PAGE] << 8U) |
                                game->ram[MYSMB_PLAYER_X]);
    enemy_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_PAGE + slot] << 8U) |
                               game->ram[MYSMB_ENEMY_X + slot]);
    screen_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_SCREEN_LEFT_PAGE] << 8U) |
                                game->ram[MYSMB_SCREEN_LEFT_X]);
    if (player_world < screen_world || enemy_world < screen_world ||
        (mysmb_u16)(player_world - screen_world) >= 0x100U ||
        (mysmb_u16)(enemy_world - screen_world) >= 0x100U) return 0U;
    enemy_box = (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + slot * 4U);
    mysmb_world_set_bounding_box(game, enemy_box, game->ram[MYSMB_ENEMY_BOUND_BOX + slot],
        (mysmb_u8)(enemy_world - screen_world), game->ram[MYSMB_ENEMY_Y + slot]);
    return 1U;
}

#ifdef MYSMB_DOS16_TARGET
#pragma code_seg("MYSMB_BLOCK")
#endif
