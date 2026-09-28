#include "game/enemy/actor_slots.h"
#include "game/objects.h"
#include "game/status.h"
#include "game/enemy/movement.h"
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

static void mysmb_objects_apply_digit_modifier(struct mysmb_game *game,
                                               mysmb_u8 digit_offset);
void mysmb_objects_step_normal_enemy_terrain(struct mysmb_game *game,
                                            mysmb_u8 slot);
static mysmb_u8 mysmb_objects_set_player_enemy_collision_boxes(struct mysmb_game *game,
                                                                mysmb_u8 slot);
static void mysmb_objects_setup_floatey_number(struct mysmb_game *game,
                                               mysmb_u8 slot,
                                               mysmb_u8 control);
static void mysmb_objects_draw_jump_coin(struct mysmb_game *game, mysmb_u8 slot);
static void mysmb_objects_move_misc_horizontally(struct mysmb_game *game,
                                                 mysmb_u8 slot);
static mysmb_u8 mysmb_objects_spawn_hammer(struct mysmb_game *game,
                                           mysmb_u8 enemy_slot);
static void mysmb_objects_step_hammer(struct mysmb_game *game, mysmb_u8 slot);
static void mysmb_objects_check_hammer_collision(struct mysmb_game *game,
                                                 mysmb_u8 slot);
static void mysmb_objects_defeat_by_shell(struct mysmb_game *game,
                                          mysmb_u8 enemy_slot);
static void mysmb_objects_turn_enemy(struct mysmb_game *game, mysmb_u8 slot);
static mysmb_u8 mysmb_objects_is_coin_block(mysmb_u8 metatile);
static void mysmb_objects_check_top_of_block(struct mysmb_game *game,
                                             mysmb_u8 slot,
                                             mysmb_u8 block_low,
                                             mysmb_u8 block_row);

/* ROM InjurePlayer/ForceInjury/KillPlayer.  Every object collision converges
 * here so a small player enters the death route rather than becoming immune. */
void mysmb_objects_force_injury(struct mysmb_game *game)
{
    if (game->ram[MYSMB_INJURY_TIMER] != 0U) return;
    if (game->ram[MYSMB_PLAYER_STATUS] == 0U) {
        game->ram[MYSMB_PLAYER_X_SPEED] = 0U;
        game->ram[0x00fcU] = 1U;
        game->ram[MYSMB_PLAYER_Y_SPEED] = 0xfcU;
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 11U;
    }
    else {
        game->ram[MYSMB_PLAYER_STATUS] = 0U;
        game->ram[MYSMB_INJURY_TIMER] = 8U;
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 10U;
    }
    game->ram[MYSMB_PLAYER_STATE] = 1U;
    game->ram[MYSMB_TIMER_CONTROL] = 0xffU;
    game->ram[MYSMB_SCROLL_AMOUNT] = 0U;
}

/* ROM $dcfd-$dd4b PlayerEnemyCollision direct-injury branches: Podoboo,
 * Piranha Plant, and Spiny.  The ROM literal #$15 is hexadecimal: the
 * Paratroopas and Lakitu below it still reach the stomp path. */
static mysmb_u8 mysmb_objects_check_hazard_enemy_collision_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u16 enemy_box;

    if ((game->ram[MYSMB_FRAME_COUNTER] & 1U) != 0U || game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 8U ||
        game->ram[MYSMB_PLAYER_OFFSCREEN_BITS] >= 0xf0U || game->ram[MYSMB_PLAYER_Y_HIGH] != 1U ||
        game->ram[MYSMB_PLAYER_Y] >= 0xd0U || game->ram[MYSMB_INJURY_TIMER] != 0U) return 0U;
    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        (game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U ||
        (game->ram[MYSMB_ENEMY_ID + slot] != 10U && game->ram[MYSMB_ENEMY_ID + slot] != 11U &&
         game->ram[MYSMB_ENEMY_ID + slot] != 12U && game->ram[MYSMB_ENEMY_ID + slot] != 13U &&
         game->ram[MYSMB_ENEMY_ID + slot] != 18U) ||
        mysmb_objects_set_player_enemy_collision_boxes(game, slot) == 0U) return 0U;
    enemy_box = (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + slot * 4U);
    if (mysmb_world_boxes_collide(game, MYSMB_BOUNDING_BOX_PLAYER, enemy_box) == 0U) {
        game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] &= 0xfeU;
        return 0U;
    }
    if ((game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] & 1U) != 0U) return 0U;
    game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] |= 1U;
    mysmb_objects_force_injury(game);
    return 1U;
    return 0U;
}

/* Legacy aggregate interface; production uses the current-slot boundary. */
void mysmb_objects_check_hazard_enemy_collision(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (mysmb_objects_check_hazard_enemy_collision_slot(game, slot) != 0U) return;
    }
}

/* ROM $dcfd PlayerEnemyCollision and $e069 SetStun, bounded to ID 8. */
static mysmb_u8 mysmb_objects_check_bullet_bill_stomp_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u16 enemy_box;

    if ((game->ram[MYSMB_FRAME_COUNTER] & 1U) != 0U || game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 8U ||
        game->ram[MYSMB_PLAYER_OFFSCREEN_BITS] >= 0xf0U || game->ram[MYSMB_PLAYER_Y_HIGH] != 1U ||
        game->ram[MYSMB_PLAYER_Y] >= 0xd0U || game->ram[MYSMB_PLAYER_Y_SPEED] == 0U ||
        game->ram[MYSMB_PLAYER_Y_SPEED] >= 0x80U) return 0U;
    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U || game->ram[MYSMB_ENEMY_ID + slot] != 8U ||
        (game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U ||
        mysmb_objects_set_player_enemy_collision_boxes(game, slot) == 0U) return 0U;
    enemy_box = (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + slot * 4U);
    if (mysmb_world_boxes_collide(game, MYSMB_BOUNDING_BOX_PLAYER, enemy_box) == 0U) {
        game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] &= 0xfeU;
        return 0U;
    }
    if ((game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] & 1U) != 0U) return 0U;
    game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] |= 1U;
    game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - 2U);
    game->ram[MYSMB_ENEMY_STATE + slot] = 0x20U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
    game->ram[MYSMB_PLAYER_Y_SPEED] = 0xfdU;
    return 1U;
    return 0U;
}

/* Legacy aggregate interface; production uses the current-slot boundary. */
void mysmb_objects_check_bullet_bill_stomp(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (mysmb_objects_check_bullet_bill_stomp_slot(game, slot) != 0U) return;
    }
}

/* ROM $dcfd PlayerEnemyCollision and $e069 EnemyStomped, bounded to ID 7. */
static mysmb_u8 mysmb_objects_check_bloober_stomp_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u16 enemy_box;

    if ((game->ram[MYSMB_FRAME_COUNTER] & 1U) != 0U || game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 8U ||
        game->ram[MYSMB_PLAYER_OFFSCREEN_BITS] >= 0xf0U || game->ram[MYSMB_PLAYER_Y_HIGH] != 1U ||
        game->ram[MYSMB_PLAYER_Y] >= 0xd0U || game->ram[MYSMB_PLAYER_Y_SPEED] == 0U ||
        game->ram[MYSMB_PLAYER_Y_SPEED] >= 0x80U) return 0U;
    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U || game->ram[MYSMB_ENEMY_ID + slot] != 7U ||
        (game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U ||
        mysmb_objects_set_player_enemy_collision_boxes(game, slot) == 0U) return 0U;
    enemy_box = (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + slot * 4U);
    if (mysmb_world_boxes_collide(game, MYSMB_BOUNDING_BOX_PLAYER, enemy_box) == 0U) {
        game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] &= 0xfeU;
        return 0U;
    }
    if ((game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] & 1U) != 0U) return 0U;
    game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] |= 1U;
    game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - 2U);
    game->ram[MYSMB_ENEMY_STATE + slot] = 0x20U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
    game->ram[MYSMB_PLAYER_Y_SPEED] = 0xfdU;
    return 1U;
    return 0U;
}

/* Legacy aggregate interface; production uses the current-slot boundary. */
void mysmb_objects_check_bloober_stomp(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (mysmb_objects_check_bloober_stomp_slot(game, slot) != 0U) return;
    }
}

/* ROM $dcfd-$ddcb PlayerEnemyCollision and EnemyStomped, bounded to Lakitu.
 * EnemyStomped preserves Lakitu's direction, calls SetStun, then replaces its
 * state with d5 and clears movement physics through InitVStf. */
static mysmb_u8 mysmb_objects_check_lakitu_stomp_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u16 enemy_box;

    if ((game->ram[MYSMB_FRAME_COUNTER] & 1U) != 0U ||
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 8U ||
        game->ram[MYSMB_PLAYER_OFFSCREEN_BITS] >= 0xf0U ||
        game->ram[MYSMB_PLAYER_Y_HIGH] != 1U || game->ram[MYSMB_PLAYER_Y] >= 0xd0U ||
        game->ram[MYSMB_PLAYER_Y_SPEED] == 0U || game->ram[MYSMB_PLAYER_Y_SPEED] >= 0x80U) return 0U;
    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U || game->ram[MYSMB_ENEMY_ID + slot] != 17U ||
        (game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U ||
        mysmb_objects_set_player_enemy_collision_boxes(game, slot) == 0U) return 0U;
    enemy_box = (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + slot * 4U);
    if (mysmb_world_boxes_collide(game, MYSMB_BOUNDING_BOX_PLAYER, enemy_box) == 0U) {
        game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] &= 0xfeU;
        return 0U;
    }
    if ((game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] & 1U) != 0U) return 0U;
    game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] |= 1U;
    mysmb_objects_setup_floatey_number(game, slot, 5U);
    game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - 2U);
    game->ram[MYSMB_ENEMY_STATE + slot] = 0x20U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
    game->ram[MYSMB_PLAYER_Y_SPEED] = 0xfdU;
    return 1U;
    return 0U;
}

/* Legacy aggregate interface; production uses the current-slot boundary. */
void mysmb_objects_check_lakitu_stomp(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (mysmb_objects_check_lakitu_stomp_slot(game, slot) != 0U) return;
    }
}

/* ROM $dcfd-$ddcb EnemyStomped, bounded to Hammer Bro (ID $05). */
static mysmb_u8 mysmb_objects_check_hammer_bro_stomp_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u16 enemy_box;

    if ((game->ram[MYSMB_FRAME_COUNTER] & 1U) != 0U ||
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 8U ||
        game->ram[MYSMB_PLAYER_OFFSCREEN_BITS] >= 0xf0U ||
        game->ram[MYSMB_PLAYER_Y_HIGH] != 1U || game->ram[MYSMB_PLAYER_Y] >= 0xd0U ||
        game->ram[MYSMB_PLAYER_Y_SPEED] == 0U || game->ram[MYSMB_PLAYER_Y_SPEED] >= 0x80U) return 0U;
    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U || game->ram[MYSMB_ENEMY_ID + slot] != 5U ||
        (game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U ||
        mysmb_objects_set_player_enemy_collision_boxes(game, slot) == 0U) return 0U;
    enemy_box = (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + slot * 4U);
    if (mysmb_world_boxes_collide(game, MYSMB_BOUNDING_BOX_PLAYER, enemy_box) == 0U) {
        game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] &= 0xfeU;
        return 0U;
    }
    if ((game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] & 1U) != 0U) return 0U;
    game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] |= 1U;
    mysmb_objects_setup_floatey_number(game, slot, 6U);
    game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - 2U);
    game->ram[MYSMB_ENEMY_STATE + slot] = 0x20U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
    game->ram[MYSMB_PLAYER_Y_SPEED] = 0xfdU;
    return 1U;
    return 0U;
}

/* Legacy aggregate interface; production uses the current-slot boundary. */
void mysmb_objects_check_hammer_bro_stomp(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (mysmb_objects_check_hammer_bro_stomp_slot(game, slot) != 0U) return;
    }
}

/* ROM $dcfd-$ddcb PlayerEnemyCollision and $e06a ChkForDemoteKoopa. */
static mysmb_u8 mysmb_objects_check_paratroopa_stomp_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u16 player_world;
    mysmb_u16 enemy_world;
    mysmb_u16 screen_world;
    mysmb_u16 enemy_box;

    if ((game->ram[MYSMB_FRAME_COUNTER] & 1U) != 0U ||
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 8U ||
        game->ram[MYSMB_PLAYER_OFFSCREEN_BITS] >= 0xf0U ||
        game->ram[MYSMB_PLAYER_Y_HIGH] != 1U || game->ram[MYSMB_PLAYER_Y] >= 0xd0U ||
        game->ram[MYSMB_PLAYER_Y_SPEED] == 0U || game->ram[MYSMB_PLAYER_Y_SPEED] >= 0x80U) return 0U;
    player_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_PLAYER_PAGE] << 8U) |
                                game->ram[MYSMB_PLAYER_X]);
    screen_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_SCREEN_LEFT_PAGE] << 8U) |
                                game->ram[MYSMB_SCREEN_LEFT_X]);
    if (player_world < screen_world || (mysmb_u16)(player_world - screen_world) >= 0x100U) return 0U;
    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        (game->ram[MYSMB_ENEMY_ID + slot] != 14U &&
         game->ram[MYSMB_ENEMY_ID + slot] != 15U &&
         game->ram[MYSMB_ENEMY_ID + slot] != 16U) ||
        (game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U) return 0U;
    enemy_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_PAGE + slot] << 8U) |
                               game->ram[MYSMB_ENEMY_X + slot]);
    if (enemy_world < screen_world || (mysmb_u16)(enemy_world - screen_world) >= 0x100U) return 0U;
    enemy_box = (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + slot * 4U);
    mysmb_world_set_bounding_box(game, enemy_box, game->ram[MYSMB_ENEMY_BOUND_BOX + slot],
        (mysmb_u8)(enemy_world - screen_world), game->ram[MYSMB_ENEMY_Y + slot]);
    if (mysmb_world_boxes_collide(game, MYSMB_BOUNDING_BOX_PLAYER, enemy_box) == 0U) {
        game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] &= 0xfeU;
        return 0U;
    }
    if ((game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] & 1U) != 0U) return 0U;
    game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] |= 1U;
    game->ram[MYSMB_ENEMY_ID + slot] &= 1U;
    game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
    game->ram[MYSMB_ENEMY_X_FORCE + slot] = 0U;
    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] =
        enemy_world >= player_world ? 1U : 2U;
    game->ram[MYSMB_ENEMY_X_SPEED + slot] =
        game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] == 1U ? 8U : 0xf8U;
    mysmb_objects_setup_floatey_number(game, slot, 3U);
    game->ram[MYSMB_PLAYER_Y_SPEED] = 0xfcU;
    return 1U;
    return 0U;
}

/* Legacy aggregate interface; production uses the current-slot boundary. */
void mysmb_objects_check_paratroopa_stomp(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (mysmb_objects_check_paratroopa_stomp_slot(game, slot) != 0U) return;
    }
}

/* ROM $bb51 SetupJumpCoin. */
void mysmb_objects_start_jump_coin(struct mysmb_game *game, mysmb_u8 page,
                                   mysmb_u8 x, mysmb_u8 y)
{
    mysmb_u8 slot;

    slot = 8U;
    while (slot > 5U && game->ram[MYSMB_MISC_STATE + slot] != 0U) --slot;
    if (slot == 5U) slot = 8U;
    game->ram[0x06b7U] = slot;
    game->ram[MYSMB_MISC_PAGE + slot] = page;
    game->ram[MYSMB_MISC_X + slot] = x;
    game->ram[MYSMB_MISC_Y + slot] = y;
    game->ram[MYSMB_MISC_Y_SPEED + slot] = 0xfbU;
    game->ram[MYSMB_MISC_Y_HIGH + slot] = 1U;
    game->ram[MYSMB_MISC_Y_DUMMY + slot] = 0U;
    game->ram[MYSMB_MISC_Y_FORCE + slot] = 0U;
    game->ram[MYSMB_MISC_STATE + slot] = 1U;
    /* ROM JCoinC queues Sfx_CoinGrab after activating the misc object. */
    game->ram[MYSMB_SQUARE2_SOUND] = 1U;
}

/* ROM JCoinGfxHandler / DrawFloateyNumber_Coin. */
static void mysmb_objects_draw_jump_coin(struct mysmb_game *game, mysmb_u8 slot)
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
/* ROM $bb96-$bbd0 ProcJumpCoin and $bac4 ProcHammerObj, excluding OAM.
 * Misc_State d7 selects the hammer route exactly as MiscObjectsCore does. */
void mysmb_objects_step_misc(struct mysmb_game *game)
{
    mysmb_u8 slot;

    /* ROM MiscObjectsCore starts with X=$08 and decrements through zero.
     * Relative/offscreen results are fixed scratch cells, so the final active
     * object must be the lowest occupied slot. */
    for (slot = 8U;; --slot) {
        if (game->ram[MYSMB_MISC_STATE + slot] == 0U) {
            if (slot == 0U) break;
            continue;
        }
        if ((game->ram[MYSMB_MISC_STATE + slot] & 0x80U) != 0U) {
            mysmb_objects_step_hammer(game, slot);
            if (slot == 0U) break;
            continue;
        }
        if (game->ram[MYSMB_MISC_STATE + slot] == 1U) {
            mysmb_world_impose_gravity_misc(game, slot, 0x50U, 6U);
            if (game->ram[MYSMB_MISC_Y_SPEED + slot] == 5U) game->ram[MYSMB_MISC_STATE + slot]++;
        }
        else {
            mysmb_u8 old_x;
            mysmb_u8 scroll_amount;

            game->ram[MYSMB_MISC_STATE + slot]++;
            old_x = game->ram[MYSMB_MISC_X + slot];
            scroll_amount = game->ram[MYSMB_SCROLL_AMOUNT];
            game->ram[MYSMB_MISC_X + slot] =
                (mysmb_u8)(old_x + scroll_amount);
            /* ROM ProcJumpCoin: carry from X + ScrollAmount advances page. */
            if (game->ram[MYSMB_MISC_X + slot] < old_x)
                game->ram[MYSMB_MISC_PAGE + slot]++;
            if (game->ram[MYSMB_MISC_STATE + slot] == 0x30U) game->ram[MYSMB_MISC_STATE + slot] = 0U;
        }
        if (game->ram[MYSMB_MISC_STATE + slot] != 0U) {
            mysmb_oam_relative_misc_position(game, slot);
            mysmb_oam_get_misc_offscreen_bits(game, slot);
            mysmb_world_set_bounding_box(game,
                (mysmb_u16)(0x04d0U + slot * 4U),
                game->ram[MYSMB_MISC_BOUND_BOX + slot],
                game->ram[0x03b3U], game->ram[0x03beU]);
            mysmb_world_clip_bounding_box_to_screen(game,
                (mysmb_u16)(0x04d0U + slot * 4U),
                game->ram[MYSMB_MISC_PAGE + slot],
                game->ram[MYSMB_MISC_X + slot]);
            mysmb_objects_draw_jump_coin(game, slot);
        }
        if (slot == 0U) break;
    }
}

/* ROM $bbc5 SetupPowerUp.  Slot five is reserved by the original object
 * buffer for the one active power-up. */
void mysmb_objects_start_power_up(struct mysmb_game *game, mysmb_u8 block_slot,
                                  mysmb_u8 power_up_type)
{
    const mysmb_u8 slot = 5U;

    game->ram[MYSMB_ENEMY_ID + slot] = 0x2eU;
    game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[MYSMB_BLOCK_PAGE + block_slot];
    game->ram[MYSMB_ENEMY_X + slot] = game->ram[MYSMB_BLOCK_X + block_slot];
    game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
    game->ram[MYSMB_ENEMY_Y + slot] =
        (mysmb_u8)(game->ram[MYSMB_BLOCK_Y + block_slot] - 8U);
    game->ram[MYSMB_ENEMY_STATE + slot] = 1U;
    game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
    game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 3U;
    game->ram[MYSMB_POWER_UP_TYPE] = power_up_type;
    if (power_up_type < 2U) {
        if (game->ram[MYSMB_PLAYER_STATUS] < 2U) {
            game->ram[MYSMB_POWER_UP_TYPE] = game->ram[MYSMB_PLAYER_STATUS];
        }
        else {
            game->ram[MYSMB_POWER_UP_TYPE] = 1U;
        }
    }
    game->ram[MYSMB_ENEMY_ATTRIBUTES + slot] = 0x20U;
    /* ROM SetupPowerUp queues Sfx_GrowPowerUp for the next audio pass. */
    game->ram[MYSMB_SQUARE2_SOUND] = 2U;
}

/* ROM RunPUSubs: once the object has emerged at least six pixels, this
 * runs every frame, including the three GrowThePowerUp frames that do not
 * decrement its Y coordinate. */
static void mysmb_objects_prepare_power_up_subs(struct mysmb_game *game)
{
    const mysmb_u8 slot = 5U;

    game->ram[0x03aeU] = (mysmb_u8)(game->ram[MYSMB_ENEMY_X + slot] -
                                      game->ram[MYSMB_SCREEN_LEFT_X]);
    game->ram[0x03b9U] = game->ram[MYSMB_ENEMY_Y + slot];
    game->ram[0x03d1U] =
        mysmb_objects_get_enemy_offscreen_bits(game, slot);
    mysmb_objects_update_enemy_bounding_box(game, slot);
    mysmb_objects_draw_power_up(game);
}

/* ROM $bbef-$bc15 GrowThePowerUp through the admitted PowerUpObjHandler
 * movement and EnemyToBGCollisionDet state paths. */
void mysmb_objects_step_power_up(struct mysmb_game *game)
{
    const mysmb_u8 slot = 5U;
    mysmb_u8 state;
    mysmb_u8 tile;
    state = game->ram[MYSMB_ENEMY_STATE + slot];
    if (state == 0U) return;
    if ((state & 0x80U) != 0U) {
        if (game->ram[MYSMB_TIMER_CONTROL] == 0U &&
            (game->ram[MYSMB_POWER_UP_TYPE] == 0U ||
             game->ram[MYSMB_POWER_UP_TYPE] == 2U ||
             game->ram[MYSMB_POWER_UP_TYPE] == 3U)) {
            if (game->ram[MYSMB_POWER_UP_TYPE] == 2U ||
                (state & 0x40U) != 0U) {
                /* ROM MoveJ_EnemyVertically / MoveD_EnemyVertically both
                 * enter the same ImposeGravitySprObj actor-array primitive. */
                mysmb_enemy_move_downward(game, slot,
                    game->ram[MYSMB_POWER_UP_TYPE] == 2U ? 0x1cU : 0x3dU, 3U);
            }
            mysmb_world_move_enemy_horizontally(game, slot);
            if (game->ram[MYSMB_POWER_UP_TYPE] == 2U) {
                mysmb_objects_step_enemy_jump_terrain(game, slot);
            }
            else {
                struct mysmb_enemy_terrain terrain;
                tile = mysmb_world_query_enemy_block(game, slot, 0x15U, 0U, &terrain) != 0U ?
                    terrain.metatile : 0U;
                if (game->ram[MYSMB_ENEMY_Y + slot] >= 6U &&
                    mysmb_objects_is_solid_terrain(tile) != 0U) {
                    /* LandEnemyProperly first routes Y low nybbles D-F to
                     * ChkForRedKoopa, which gives active objects the d6
                     * falling bit.  It can align to Y|8 only on 8-C after
                     * that bit was already set. */
                    if ((game->ram[MYSMB_ENEMY_Y + slot] & 0x0fU) >= 0x0dU) {
                        game->ram[MYSMB_ENEMY_STATE + slot] |= 0x40U;
                    }
                    else if ((game->ram[MYSMB_ENEMY_STATE + slot] & 0x40U) != 0U &&
                             (game->ram[MYSMB_ENEMY_Y + slot] & 0x0fU) >= 8U) {
                        mysmb_world_land_enemy(game, slot);
                        game->ram[MYSMB_ENEMY_STATE + slot] &= 0xbfU;
                    }
                }
                else {
                    game->ram[MYSMB_ENEMY_STATE + slot] |= 0x40U;
                }
                tile = mysmb_world_query_enemy_block(game, slot,
                    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] == 1U ? 0x17U : 0x16U,
                    1U, &terrain) != 0U ? terrain.metatile : 0U;
                if (mysmb_objects_is_solid_terrain(tile) != 0U) {
                    /* ROM RXSpd: DoEnemySideCheck preserves the movement
                     * magnitude and takes the two's complement of the current
                     * 4.4 speed. */
                    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] ^= 3U;
                    game->ram[MYSMB_ENEMY_X_SPEED + slot] =
                        (mysmb_u8)(0U - game->ram[MYSMB_ENEMY_X_SPEED + slot]);
                }
            }        }
        mysmb_objects_prepare_power_up_subs(game);
        return;
    }
    if ((game->ram[MYSMB_FRAME_COUNTER] & 3U) != 0U) {
        if (state >= 6U) mysmb_objects_prepare_power_up_subs(game);
        return;
    }
    game->ram[MYSMB_ENEMY_Y + slot]--;
    game->ram[MYSMB_ENEMY_STATE + slot]++;
    if (state >= 0x11U) {
        game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0x10U;
        game->ram[MYSMB_ENEMY_STATE + slot] = 0x80U;
        game->ram[MYSMB_ENEMY_ATTRIBUTES + slot] = 0U;
        game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 1U;
    }
    if (game->ram[MYSMB_ENEMY_STATE + slot] >= 6U) {
        mysmb_objects_prepare_power_up_subs(game);
    }
}

/* ROM $dcfd-$ddcb PlayerEnemyCollision and $e069-$e08a EnemyStomped,
 * bounded to ordinary walking enemies. */
mysmb_u8 mysmb_objects_check_normal_enemy_collision(struct mysmb_game *game,
                                                            mysmb_u8 slot,
                                                            mysmb_u8 preserve_collision_boxes)
{
    mysmb_u16 player_world;
    mysmb_u16 enemy_world;
    mysmb_u16 screen_world;
    mysmb_u16 enemy_box;
    mysmb_u8 state;

    if ((game->ram[MYSMB_FRAME_COUNTER] & 1U) != 0U ||
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 8U ||
        game->ram[MYSMB_PLAYER_OFFSCREEN_BITS] >= 0xf0U ||
        game->ram[MYSMB_PLAYER_Y_HIGH] != 1U ||
        game->ram[MYSMB_PLAYER_Y] >= 0xd0U) return 0U;
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
    /* PlayerEnemyCollision consumes the persistent bounding boxes produced
     * by PlayerGfxHandler and GetEnemyBoundBox.  The standalone owner test
     * path has no preceding PlayerGfxHandler, so it initializes its boxes. */
    if (preserve_collision_boxes == 0U) {
        mysmb_world_set_bounding_box(game, MYSMB_BOUNDING_BOX_PLAYER,
                                       game->ram[MYSMB_PLAYER_BOUND_BOX],
                                       (mysmb_u8)(player_world - screen_world),
                                       game->ram[MYSMB_PLAYER_Y]);
        mysmb_world_set_bounding_box(game, enemy_box,
                                       game->ram[MYSMB_ENEMY_BOUND_BOX + slot],
                                       (mysmb_u8)(enemy_world - screen_world),
                                       game->ram[MYSMB_ENEMY_Y + slot]);
    }
    if (mysmb_world_boxes_collide(game, MYSMB_BOUNDING_BOX_PLAYER, enemy_box) == 0U) {
        game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] &= 0xfeU;
        return 0U;
    }
    if ((game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] & 1U) != 0U) return 0U;
    game->ram[MYSMB_ENEMY_COLLISION_BITS + slot] |= 1U;
    if (game->ram[MYSMB_STAR_INVINCIBLE_TIMER] != 0U) {
        game->ram[MYSMB_ENEMY_STATE + slot] =
            (mysmb_u8)((game->ram[MYSMB_ENEMY_STATE + slot] & 0x10U) | 0x22U);
        game->ram[MYSMB_ENEMY_Y + slot] =
            (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - 2U);
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0xfdU;
        game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] =
            enemy_world > player_world ? 1U : 2U;
        game->ram[MYSMB_ENEMY_X_SPEED + slot] =
            game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] == 1U ? 0x10U : 0xf0U;
        mysmb_objects_setup_floatey_number(game, slot,
            game->ram[MYSMB_ENEMY_ID + slot] == 6U ? 1U : 2U);
        return 1U;
    }
    state = (mysmb_u8)(game->ram[MYSMB_ENEMY_STATE + slot] & 7U);
    if (state >= 2U && game->ram[MYSMB_ENEMY_ID + slot] != 6U) {
        /* ROM HandlePECollisions: a defeated Goomba has no shell to kick. */
        if (game->ram[MYSMB_ENEMY_ID + slot] == 0U) return 1U;
        game->ram[MYSMB_ENEMY_STATE + slot] |= 0x80U;
        game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] =
            enemy_world > player_world ? 2U : 1U;
        game->ram[MYSMB_ENEMY_X_SPEED + slot] =
            game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] == 1U ? 0x30U : 0xd0U;
        mysmb_objects_setup_floatey_number(game, slot,
            (mysmb_u8)(game->ram[MYSMB_STOMP_CHAIN_COUNTER] + 3U));
        return 1U;
    }
    if (game->ram[MYSMB_PLAYER_Y_SPEED] != 0U &&
        game->ram[MYSMB_PLAYER_Y_SPEED] < 0x80U) {
        /* ROM EnemyStomped queues Sfx_EnemyStomp before it changes the
         * defeated object state or allocates its floatey score. */
        game->ram[MYSMB_SQUARE1_SOUND] = 4U;
        game->ram[MYSMB_ENEMY_STATE + slot] = 4U;
        game->ram[MYSMB_ENEMY_INTERVAL_TIMER + slot] =
            game->ram[MYSMB_PRIMARY_HARD] == 0U ? 0x10U : 0x0bU;
        game->ram[MYSMB_STOMP_CHAIN_COUNTER]++;
        mysmb_objects_setup_floatey_number(game, slot,
            (mysmb_u8)(game->ram[MYSMB_STOMP_CHAIN_COUNTER] + game->ram[MYSMB_STOMP_TIMER]));
        game->ram[MYSMB_STOMP_TIMER]++;
        game->ram[MYSMB_PLAYER_Y_SPEED] = 0xfcU;
        return 1U;
    }
    mysmb_objects_force_injury(game);
    return 1U;
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

void mysmb_objects_step_normal_enemy_terrain(struct mysmb_game *game,
                                            mysmb_u8 slot)
{
    struct mysmb_enemy_terrain terrain;
    static const mysmb_u8 collision_state_data[6] = { 1U, 1U, 2U, 2U, 2U, 5U };
    mysmb_u8 tile;
    mysmb_u8 state;
    mysmb_u8 direction;
    mysmb_u8 id;
    mysmb_u8 relative_x;
    mysmb_u16 difference;

    /* EnemyToBGCollisionDet: d5 actors and objects above the source gate
     * never enter any terrain probe. */
    state = game->ram[MYSMB_ENEMY_STATE + slot];
    if ((state & 0x20U) != 0U ||
        (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] + 0x3eU) < 0x44U) return;

    /* ChkUnderEnemy / HandleEToBGCollision / LandEnemyProperly. */
    tile = mysmb_world_query_enemy_block(game, slot, 0x15U, 0U, &terrain) != 0U ?
        terrain.metatile : 0U;
    if (tile == 0x23U) {
        /* HandleEToBGCollision: a block that was bumped beneath this actor
         * is consumed before the original defeat/score/stun chain. */
        game->ram[terrain.block_address] = 0U;
        id = game->ram[MYSMB_ENEMY_ID + slot];
        if (id < 0x15U) {
            if (id == 6U) mysmb_objects_defeat_by_shell(game, slot);
            mysmb_objects_setup_floatey_from_relative(game, slot, 1U);
            relative_x = game->ram[0x03aeU]; /* Enemy_Rel_XPos */
        }
        else relative_x = id;
        /* ChkToStunEnemies uses the accumulator left by SetupFloateyNumber
         * (Enemy_Rel_XPos), including its unusual $09/$0d-$10 demotion.
         */
        if (relative_x == 9U || (relative_x >= 13U && relative_x < 17U)) {
            game->ram[MYSMB_ENEMY_ID + slot] &= 1U;
        }
        game->ram[MYSMB_ENEMY_STATE + slot] =
            (mysmb_u8)((game->ram[MYSMB_ENEMY_STATE + slot] & 0xf0U) | 2U);
        game->ram[MYSMB_ENEMY_Y + slot] =
            (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - 2U);
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] =
            game->ram[MYSMB_AREA_TYPE] == 0U ? 0xffU : 0xfdU;
        difference = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_PAGE + slot] << 8U) |
                                 game->ram[MYSMB_ENEMY_X + slot]);
        difference = (mysmb_u16)(difference -
            (((mysmb_u16)game->ram[MYSMB_PLAYER_PAGE] << 8U) |
             game->ram[MYSMB_PLAYER_X]));
        direction = (difference & 0x8000U) != 0U ? 2U : 1U;
        game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = direction;
        game->ram[MYSMB_ENEMY_X_SPEED + slot] = direction == 1U ? 0x10U : 0xf0U;
        return;
    }
    if (mysmb_objects_is_solid_terrain(tile) != 0U && tile != 0x23U &&
        terrain.contact_low_nibble < 0x0dU) {
        if ((state & 0x40U) != 0U) {
            mysmb_world_land_enemy(game, slot);
            state = game->ram[MYSMB_ENEMY_STATE + slot];
            if ((state & 0x80U) == 0U) {
                game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
                return;
            }
            game->ram[MYSMB_ENEMY_STATE + slot] = (mysmb_u8)(state & 0xbfU);
            return;
        }
        if ((state & 0x80U) == 0U) {
            if (state == 0U) goto side_check;
            if (state >= 3U) return;
            if (state == 2U) {
                game->ram[MYSMB_ENEMY_INTERVAL_TIMER + slot] = 0x10U;
                game->ram[MYSMB_ENEMY_STATE + slot] = 3U;
                mysmb_world_land_enemy(game, slot);
                return;
            }
            /* ProcEnemyDirection.  Goombas land immediately; the other
             * ordinary actors first face the player as the source does. */
            if (game->ram[MYSMB_ENEMY_ID + slot] != 6U) {
                difference = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_PAGE + slot] << 8U) |
                                         game->ram[MYSMB_ENEMY_X + slot]);
                difference = (mysmb_u16)(difference -
                    (((mysmb_u16)game->ram[MYSMB_PLAYER_PAGE] << 8U) |
                     game->ram[MYSMB_PLAYER_X]));
                direction = (difference & 0x8000U) != 0U ? 2U : 1U;
                if (direction == game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot]) {
                    game->ram[MYSMB_ENEMY_X_SPEED + slot] =
                        (mysmb_u8)(0U - game->ram[MYSMB_ENEMY_X_SPEED + slot]);
                    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] ^= 3U;
                }
            }
            mysmb_world_land_enemy(game, slot);
            game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
            return;
        }
        /* d7 set and d6 clear: LandEnemyProperly falls into DoEnemySideCheck. */
        goto side_check;
    }

    /* ChkForRedKoopa runs both after an empty/non-solid bottom sample and
     * after a solid sample outside the landing low-nibble interval. */
    state = game->ram[MYSMB_ENEMY_STATE + slot];
    if (game->ram[MYSMB_ENEMY_ID + slot] == 3U && state == 0U) goto bump;
    if ((state & 0x80U) != 0U) {
        game->ram[MYSMB_ENEMY_STATE + slot] = (mysmb_u8)(state | 0x40U);
    }
    else if (state < 6U) {
        game->ram[MYSMB_ENEMY_STATE + slot] = collision_state_data[state];
    }

side_check:
    mysmb_objects_check_enemy_side(game, slot);
    return;
bump:
    mysmb_objects_bump_enemy(game, slot);
}





/* Current-slot seam for the existing collision implementations. Source
 * PlayerEnemyCollision is one caller boundary; these legacy specialized
 * bodies remain explicitly uncertified, without frame-wide scans. */
void mysmb_objects_player_enemy_current(struct mysmb_game *game, mysmb_u8 slot,
                                        mysmb_u8 preserve_collision_boxes)
{
    switch (game->ram[MYSMB_ENEMY_ID + slot]) {
    case 5U: (void)mysmb_objects_check_hammer_bro_stomp_slot(game, slot); break;
    case 7U: (void)mysmb_objects_check_bloober_stomp_slot(game, slot); break;
    case 8U: (void)mysmb_objects_check_bullet_bill_stomp_slot(game, slot); break;
    case 10U: case 11U: case 12U: case 13U: case 18U:
        (void)mysmb_objects_check_hazard_enemy_collision_slot(game, slot); break;
    case 14U: case 15U: case 16U:
        (void)mysmb_objects_check_paratroopa_stomp_slot(game, slot); break;
    case 17U: (void)mysmb_objects_check_lakitu_stomp_slot(game, slot); break;
    default:
        (void)mysmb_objects_check_normal_enemy_collision(game, slot,
                                                         preserve_collision_boxes);
        break;
    }
}

/* Legacy regular bullet movement; original MoveBulletBill body still pending. */
void mysmb_objects_step_bullet_bills_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u16 player_world;
    mysmb_u16 enemy_world;

    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        game->ram[MYSMB_ENEMY_ID + slot] != 8U) return;
    if ((game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U) {
        mysmb_enemy_move_downward(game, slot, 0x3dU, 3U);
    } else if (game->ram[MYSMB_TIMER_CONTROL] == 0U &&
        game->ram[MYSMB_ENEMY_STATE + slot] == 0U) {
        player_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_PLAYER_PAGE] << 8U) |
                                    game->ram[MYSMB_PLAYER_X]);
        enemy_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_PAGE + slot] << 8U) |
                                   game->ram[MYSMB_ENEMY_X + slot]);
        game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] =
            enemy_world < player_world ? 1U : 2U;
        game->ram[MYSMB_ENEMY_X_SPEED + slot] =
            game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] == 1U ? 0x18U : 0xe8U;
        game->ram[MYSMB_ENEMY_STATE + slot] = 1U;
        game->ram[0x078aU + slot] = 0x0aU;
    }
    if (game->ram[MYSMB_TIMER_CONTROL] == 0U &&
        (game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) == 0U) {
        mysmb_world_move_enemy_horizontally(game, slot);
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_bullet_bills(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        mysmb_objects_step_bullet_bills_slot(game, slot);
        mysmb_objects_draw_bullet_bill(game, slot);
    }
}

/* ROM $aa9f-$aae8 InitPiranhaPlant/MovePiranhaPlant.  Its dedicated arrays
 * alias the normal enemy X-speed/Y-speed and vertical-physics arrays. */
void mysmb_objects_step_piranha_plants_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 distance;
    mysmb_u8 target;

    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        game->ram[MYSMB_ENEMY_ID + slot] != 13U ||
        game->ram[MYSMB_ENEMY_STATE + slot] != 0U ||
        game->ram[0x078aU + slot] != 0U) return;
    if (game->ram[MYSMB_ENEMY_Y_SPEED + slot] == 0U &&
        game->ram[MYSMB_ENEMY_X_SPEED + slot] < 0x80U) {
        distance = game->ram[MYSMB_ENEMY_X + slot] > game->ram[MYSMB_PLAYER_X] ?
            (mysmb_u8)(game->ram[MYSMB_ENEMY_X + slot] - game->ram[MYSMB_PLAYER_X]) :
            (mysmb_u8)(game->ram[MYSMB_PLAYER_X] - game->ram[MYSMB_ENEMY_X + slot]);
        if (distance < 0x21U) return;
        game->ram[MYSMB_ENEMY_X_SPEED + slot] =
            (mysmb_u8)(0U - game->ram[MYSMB_ENEMY_X_SPEED + slot]);
        game->ram[MYSMB_ENEMY_Y_SPEED + slot]++;
    }
    if ((game->ram[MYSMB_FRAME_COUNTER] & 1U) == 0U ||
        game->ram[MYSMB_TIMER_CONTROL] != 0U) return;
    target = game->ram[MYSMB_ENEMY_X_SPEED + slot] >= 0x80U ?
        game->ram[MYSMB_ENEMY_Y_DUMMY + slot] :
        game->ram[MYSMB_ENEMY_Y_FORCE + slot];
    game->ram[MYSMB_ENEMY_Y + slot] =
        (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] + game->ram[MYSMB_ENEMY_X_SPEED + slot]);
    if (game->ram[MYSMB_ENEMY_Y + slot] == target) {
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
        game->ram[0x078aU + slot] = 0x40U;
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_piranha_plants(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        mysmb_objects_draw_piranha(game, slot);
        mysmb_objects_step_piranha_plants_slot(game, slot);
    }
}

/* ROM $ad7b-$ae04 InitCheepCheep/MoveSwimmingCheepCheep. */
void mysmb_objects_step_swimming_cheep_cheeps_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 old_value;
    mysmb_u8 carry;
    mysmb_u8 difference;
    mysmb_u8 amount;

    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        (game->ram[MYSMB_ENEMY_ID + slot] != 10U &&
         game->ram[MYSMB_ENEMY_ID + slot] != 11U)) return;
    if ((game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U) {
        /* ROM MoveSwimmingCheepCheep -> MoveEnemySlowVert. */
        mysmb_enemy_move_downward(game, slot, 0x0fU, 2U);
        return;
    }
    amount = game->ram[MYSMB_ENEMY_ID + slot] == 10U ? 0x40U : 0x80U;
    old_value = game->ram[MYSMB_ENEMY_X_FORCE + slot];
    game->ram[MYSMB_ENEMY_X_FORCE + slot] = (mysmb_u8)(old_value - amount);
    carry = old_value < amount ? 1U : 0U;
    old_value = game->ram[MYSMB_ENEMY_X + slot];
    game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(old_value - carry);
    carry = old_value < carry ? 1U : 0U;
    game->ram[MYSMB_ENEMY_PAGE + slot] =
        (mysmb_u8)(game->ram[MYSMB_ENEMY_PAGE + slot] - carry);
    if (slot < 2U) return;
    if (game->ram[MYSMB_ENEMY_X_SPEED + slot] < 0x10U) {
        old_value = game->ram[MYSMB_ENEMY_Y_DUMMY + slot];
        game->ram[MYSMB_ENEMY_Y_DUMMY + slot] = (mysmb_u8)(old_value - 0x20U);
        carry = old_value < 0x20U ? 1U : 0U;
        amount = (mysmb_u8)(carry + game->ram[MYSMB_ENEMY_STATE + slot]);
        old_value = game->ram[MYSMB_ENEMY_Y + slot];
        game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(old_value - amount);
        if (old_value < amount) game->ram[MYSMB_ENEMY_Y_HIGH + slot]--;
    }
    else {
        old_value = game->ram[MYSMB_ENEMY_Y_DUMMY + slot];
        game->ram[MYSMB_ENEMY_Y_DUMMY + slot] = (mysmb_u8)(old_value + 0x20U);
        carry = game->ram[MYSMB_ENEMY_Y_DUMMY + slot] < old_value ? 1U : 0U;
        amount = (mysmb_u8)(carry + game->ram[MYSMB_ENEMY_STATE + slot]);
        old_value = game->ram[MYSMB_ENEMY_Y + slot];
        game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(old_value + amount);
        if (game->ram[MYSMB_ENEMY_Y + slot] < old_value) game->ram[MYSMB_ENEMY_Y_HIGH + slot]++;
    }
    difference = game->ram[MYSMB_ENEMY_Y + slot] > game->ram[MYSMB_ENEMY_Y_FORCE + slot] ?
        (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - game->ram[MYSMB_ENEMY_Y_FORCE + slot]) :
        (mysmb_u8)(game->ram[MYSMB_ENEMY_Y_FORCE + slot] - game->ram[MYSMB_ENEMY_Y + slot]);
    if (difference >= 0x0fU) {
        game->ram[MYSMB_ENEMY_X_SPEED + slot] =
            game->ram[MYSMB_ENEMY_Y + slot] >= game->ram[MYSMB_ENEMY_Y_FORCE + slot] ? 0x10U : 0U;
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_swimming_cheep_cheeps(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot)
        mysmb_objects_step_swimming_cheep_cheeps_slot(game, slot);
}

/* ROM $af13-$af25 MovePodoboo through $bb38 ImposeGravitySprObj.  The
 * original uses enemy slot plus one as the shared sprite vertical arrays;
 * the translated RAM aliases already use the enemy slot directly. */
void mysmb_objects_step_podoboos_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 random_value;

    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        game->ram[MYSMB_ENEMY_ID + slot] != 12U) return;
    if (game->ram[MYSMB_ENEMY_INTERVAL_TIMER + slot] == 0U) {
        game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 2U;
        game->ram[MYSMB_ENEMY_Y + slot] = 2U;
        game->ram[MYSMB_ENEMY_INTERVAL_TIMER + slot] = 1U;
        game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
        game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
        game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 9U;
        random_value = game->ram[0x07a8U + slot];
        game->ram[MYSMB_ENEMY_Y_FORCE + slot] = (mysmb_u8)(random_value | 0x80U);
        game->ram[MYSMB_ENEMY_INTERVAL_TIMER + slot] =
            (mysmb_u8)((random_value & 0x0fU) | 6U);
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0xf9U;
    }
    mysmb_enemy_move_downward(game, slot, 0x1cU, 3U);
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_podoboos(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot)
        mysmb_objects_step_podoboos_slot(game, slot);
}

/* ROM $b004-$b09a MoveBloober and ProcSwimmingB.  BlooberMoveSpeed aliases
 * Enemy_X_Speed, BlooberMoveCounter aliases Enemy_Y_Speed, and its vertical
 * swim amount aliases Enemy_Y_MoveForce in the original RAM layout. */
void mysmb_objects_step_bloobers_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 random_value;
    mysmb_u8 counter;
    mysmb_u8 old_value;
    mysmb_u8 speed;
    mysmb_u8 direction;

    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        game->ram[MYSMB_ENEMY_ID + slot] != 7U) return;
    if ((game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U) {
        /* ROM MoveDefeatedBloober -> MoveEnemySlowVert. */
        mysmb_enemy_move_downward(game, slot, 0x0fU, 2U);
        return;
    }
    random_value = (mysmb_u8)(game->ram[0x07a8U + slot] &
        (game->ram[0x06ccU] != 0U ? 3U : 0x3fU));
    if (random_value == 0U) {
        if ((slot & 1U) != 0U) {
            game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] =
                game->ram[MYSMB_PLAYER_MOVING_DIRECTION];
        }
        else {
            direction = 2U;
            if (game->ram[MYSMB_ENEMY_PAGE + slot] < game->ram[MYSMB_PLAYER_PAGE] ||
                (game->ram[MYSMB_ENEMY_PAGE + slot] == game->ram[MYSMB_PLAYER_PAGE] &&
                 game->ram[MYSMB_ENEMY_X + slot] < game->ram[MYSMB_PLAYER_X])) direction = 1U;
            game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = direction;
        }
    }
    counter = game->ram[MYSMB_ENEMY_Y_SPEED + slot];
    if ((counter & 2U) != 0U) {
        if (game->ram[MYSMB_ENEMY_INTERVAL_TIMER + slot] != 0U) {
            if ((game->ram[MYSMB_FRAME_COUNTER] & 1U) == 0U) game->ram[MYSMB_ENEMY_Y + slot]++;
        }
        else if ((mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] + 0x10U) >=
                 game->ram[MYSMB_PLAYER_Y]) {
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
        }
    }
    else if ((game->ram[MYSMB_FRAME_COUNTER] & 7U) == 0U) {
        if ((counter & 1U) == 0U) {
            game->ram[MYSMB_ENEMY_Y_FORCE + slot]++;
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = game->ram[MYSMB_ENEMY_Y_FORCE + slot];
            if (game->ram[MYSMB_ENEMY_Y_FORCE + slot] == 2U) game->ram[MYSMB_ENEMY_Y_SPEED + slot]++;
        }
        else {
            game->ram[MYSMB_ENEMY_Y_FORCE + slot]--;
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = game->ram[MYSMB_ENEMY_Y_FORCE + slot];
            if (game->ram[MYSMB_ENEMY_Y_FORCE + slot] == 0U) {
                game->ram[MYSMB_ENEMY_Y_SPEED + slot]++;
                game->ram[MYSMB_ENEMY_INTERVAL_TIMER + slot] = 2U;
            }
        }
    }
    speed = game->ram[MYSMB_ENEMY_Y_FORCE + slot];
    if (game->ram[MYSMB_ENEMY_Y + slot] >= speed &&
        (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - speed) >= 0x20U) {
        game->ram[MYSMB_ENEMY_Y + slot] =
            (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - speed);
    }
    speed = game->ram[MYSMB_ENEMY_X_SPEED + slot];
    if (game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] == 1U) {
        old_value = game->ram[MYSMB_ENEMY_X + slot];
        game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(old_value + speed);
        if (game->ram[MYSMB_ENEMY_X + slot] < old_value) game->ram[MYSMB_ENEMY_PAGE + slot]++;
    }
    else {
        old_value = game->ram[MYSMB_ENEMY_X + slot];
        game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(old_value - speed);
        if (old_value < speed) game->ram[MYSMB_ENEMY_PAGE + slot]--;
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_bloobers(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot)
        mysmb_objects_step_bloobers_slot(game, slot);
}

/* ROM $dcfd EnemiesCollision/ProcEnemyCollisions.  RunNormalEnemies invokes
 * this after GetEnemyBoundBox and EnemyToBGCollisionDet for its current
 * ObjectOffset.  Candidate boxes belong to earlier slots' prior turns; this
 * function must never manufacture or refresh either box. */
void mysmb_objects_step_enemy_collisions_current(struct mysmb_game *game,
                                                 mysmb_u8 slot)
{
    mysmb_u8 second;
    mysmb_u8 mask;
    mysmb_u16 first_box;
    mysmb_u16 second_box;

    if ((game->ram[MYSMB_FRAME_COUNTER] & 1U) == 0U ||
        game->ram[MYSMB_AREA_TYPE] == 0U || slot > 5U ||
        game->ram[MYSMB_ENEMY_ID + slot] >= 0x15U ||
        game->ram[MYSMB_ENEMY_ID + slot] == 17U ||
        game->ram[MYSMB_ENEMY_ID + slot] == 13U ||
        game->ram[MYSMB_ENEMY_OFFSCREEN_BITS_MASKED + slot] != 0U) return;

    first_box = (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + slot * 4U);
    mask = (mysmb_u8)(0x80U >> slot);
    second = slot;
    while (second != 0U) {
        --second;
        if (game->ram[MYSMB_ENEMY_FLAG + second] == 0U ||
            game->ram[MYSMB_ENEMY_ID + second] >= 0x15U ||
            game->ram[MYSMB_ENEMY_ID + second] == 17U ||
            game->ram[MYSMB_ENEMY_ID + second] == 13U ||
            game->ram[MYSMB_ENEMY_OFFSCREEN_BITS_MASKED + second] != 0U) continue;
        second_box = (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + second * 4U);
        if (mysmb_world_boxes_collide(game, first_box, second_box) == 0U) {
            game->ram[MYSMB_ENEMY_COLLISION_BITS + second] &= (mysmb_u8)~mask;
            continue;
        }
        if ((game->ram[MYSMB_ENEMY_STATE + slot] & 0x80U) == 0U &&
            (game->ram[MYSMB_ENEMY_STATE + second] & 0x80U) == 0U) {
            if ((game->ram[MYSMB_ENEMY_COLLISION_BITS + second] & mask) != 0U) continue;
            game->ram[MYSMB_ENEMY_COLLISION_BITS + second] |= mask;
        }
        /* ProcEnemyCollisions: x is current ObjectOffset, y is the earlier
         * candidate.  d5 suppresses the reaction after the collision bit
         * work, exactly as the ROM does. */
        if ((game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U ||
            (game->ram[MYSMB_ENEMY_STATE + second] & 0x20U) != 0U) continue;
        if (game->ram[MYSMB_ENEMY_STATE + slot] >= 6U) {
            if (game->ram[MYSMB_ENEMY_ID + slot] == 5U) continue;
            if ((game->ram[MYSMB_ENEMY_STATE + second] & 0x80U) != 0U) {
                mysmb_objects_setup_floatey_number(game, slot, 6U);
                mysmb_objects_defeat_by_shell(game, slot);
            }
            mysmb_objects_defeat_by_shell(game, second);
            mysmb_objects_setup_floatey_number(game, second,
                (mysmb_u8)(game->ram[MYSMB_SHELL_CHAIN_COUNTER + slot] + 4U));
            game->ram[MYSMB_SHELL_CHAIN_COUNTER + slot]++;
        }
        else if (game->ram[MYSMB_ENEMY_STATE + second] >= 6U) {
            if (game->ram[MYSMB_ENEMY_ID + second] == 5U) continue;
            mysmb_objects_defeat_by_shell(game, slot);
            mysmb_objects_setup_floatey_number(game, slot,
                (mysmb_u8)(game->ram[MYSMB_SHELL_CHAIN_COUNTER + second] + 4U));
            game->ram[MYSMB_SHELL_CHAIN_COUNTER + second]++;
        }
        else {
            mysmb_objects_turn_enemy(game, second);
            mysmb_objects_turn_enemy(game, slot);
        }
    }
}
/* ROM $c12d ProcHammerBro through MoveHammerBroXDir. */
void mysmb_objects_step_hammer_bros_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u16 player_world;
    mysmb_u16 enemy_world;
    mysmb_u8 jump_choice;

    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        game->ram[MYSMB_ENEMY_ID + slot] != 5U) return;
    if ((game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U) {
        mysmb_enemy_move_downward(game, slot, 0x3dU, 3U);
        return;
    }
    if (game->ram[0x003cU + slot] != 0U) {
        game->ram[0x003cU + slot]--;
        if (game->ram[MYSMB_HAMMER_THROWING_TIMER + slot] == 0U) {
            game->ram[MYSMB_HAMMER_THROWING_TIMER + slot] =
                game->ram[MYSMB_PRIMARY_HARD] == 0U ? 0x30U : 0x1cU;
            if (mysmb_objects_spawn_hammer(game, slot) != 0U) {
                game->ram[MYSMB_ENEMY_STATE + slot] |= 8U;
            }
        }
        else game->ram[MYSMB_HAMMER_THROWING_TIMER + slot]--;
    }
    else if ((game->ram[MYSMB_ENEMY_STATE + slot] & 7U) != 1U) {
        jump_choice = 0U;
        if (game->ram[MYSMB_ENEMY_Y + slot] < 0x80U) {
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0xfdU;
            if (game->ram[MYSMB_ENEMY_Y + slot] < 0x70U) jump_choice = 1U;
            else if ((game->ram[0x07a8U + slot] & 1U) == 0U) {
                game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0xfaU;
            }
        }
        else game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0xfaU;
        game->ram[MYSMB_ENEMY_STATE + slot] |= 1U;
        if (game->ram[MYSMB_PRIMARY_HARD] == 0U) jump_choice = 0U;
        game->ram[0x078aU + slot] = jump_choice != 0U ? 0x37U : 0x20U;
        game->ram[0x003cU + slot] = (mysmb_u8)(game->ram[0x07a8U + slot] | 0xc0U);
    }
    if (game->ram[MYSMB_TIMER_CONTROL] != 0U) return;
    game->ram[MYSMB_ENEMY_X_SPEED + slot] =
        (game->ram[MYSMB_FRAME_COUNTER] & 0x40U) != 0U ? 0xfcU : 4U;
    player_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_PLAYER_PAGE] << 8U) |
                                game->ram[MYSMB_PLAYER_X]);
    enemy_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_PAGE + slot] << 8U) |
                               game->ram[MYSMB_ENEMY_X + slot]);
    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] =
        enemy_world < player_world ? 1U : 2U;
    if (enemy_world >= player_world && game->ram[MYSMB_ENEMY_INTERVAL_TIMER + slot] == 0U) {
        game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0xf8U;
    }
    if ((game->ram[MYSMB_ENEMY_STATE + slot] & 0x40U) != 0U ||
        (((game->ram[MYSMB_ENEMY_STATE + slot] & 7U) != 0U) &&
         ((game->ram[MYSMB_ENEMY_STATE + slot] & 7U) < 3U))) {
        mysmb_enemy_move_downward(game, slot, 0x3dU, 3U);
    }
    mysmb_world_move_enemy_horizontally(game, slot);
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_hammer_bros(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 6U; ++slot) {
        if (game->ram[MYSMB_ENEMY_FLAG + slot] != 0U &&
            game->ram[MYSMB_ENEMY_ID + slot] == 5U &&
            (game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) == 0U)
            mysmb_objects_step_hammer_terrain(game, slot);
        mysmb_objects_step_hammer_bros_slot(game, slot);
    }
}

/* ROM $afbd MoveJumpingEnemy via $bb28 MoveJ_EnemyVertically. */
void mysmb_objects_step_jumping_paratroopas_slot(struct mysmb_game *game, mysmb_u8 slot)
{

    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        game->ram[MYSMB_ENEMY_ID + slot] != 14U) return;
    mysmb_enemy_move_downward(game, slot, 0x1cU, 3U);
    mysmb_world_move_enemy_horizontally(game, slot);
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_jumping_paratroopas(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot)
        mysmb_objects_step_jumping_paratroopas_slot(game, slot);
}

/* ROM $afc3 ProcMoveRedPTroopa through $bb5f RedPTroopaGrav. */
void mysmb_objects_step_red_paratroopas_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 old_value;
    mysmb_u8 carry;
    mysmb_u8 moving_up;

    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        game->ram[MYSMB_ENEMY_ID + slot] != 15U) return;
    if (game->ram[MYSMB_ENEMY_Y_SPEED + slot] == 0U &&
        game->ram[MYSMB_ENEMY_Y_FORCE + slot] == 0U &&
        game->ram[MYSMB_ENEMY_Y + slot] < game->ram[MYSMB_ENEMY_X_FORCE + slot]) {
        game->ram[MYSMB_ENEMY_Y_DUMMY + slot] = 0U;
        if ((game->ram[MYSMB_FRAME_COUNTER] & 7U) == 0U) game->ram[MYSMB_ENEMY_Y + slot]++;
        return;
    }
    moving_up = game->ram[MYSMB_ENEMY_Y + slot] >= game->ram[MYSMB_ENEMY_X_SPEED + slot] ? 1U : 0U;
    old_value = game->ram[MYSMB_ENEMY_Y_DUMMY + slot];
    game->ram[MYSMB_ENEMY_Y_DUMMY + slot] =
        (mysmb_u8)(old_value + game->ram[MYSMB_ENEMY_Y_FORCE + slot]);
    carry = game->ram[MYSMB_ENEMY_Y_DUMMY + slot] < old_value ? 1U : 0U;
    old_value = game->ram[MYSMB_ENEMY_Y + slot];
    game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(old_value +
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] + carry);
    if (game->ram[MYSMB_ENEMY_Y_SPEED + slot] >= 0x80U) game->ram[MYSMB_ENEMY_Y_HIGH + slot]--;
    if (game->ram[MYSMB_ENEMY_Y + slot] < old_value) game->ram[MYSMB_ENEMY_Y_HIGH + slot]++;
    old_value = game->ram[MYSMB_ENEMY_Y_FORCE + slot];
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = (mysmb_u8)(old_value + 3U);
    carry = game->ram[MYSMB_ENEMY_Y_FORCE + slot] < old_value ? 1U : 0U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] =
        (mysmb_u8)(game->ram[MYSMB_ENEMY_Y_SPEED + slot] + carry);
    if (game->ram[MYSMB_ENEMY_Y_SPEED + slot] >= 2U &&
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] < 0x80U &&
        game->ram[MYSMB_ENEMY_Y_FORCE + slot] >= 0x80U) {
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 2U;
        game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
    }
    if (moving_up != 0U) {
        old_value = game->ram[MYSMB_ENEMY_Y_FORCE + slot];
        game->ram[MYSMB_ENEMY_Y_FORCE + slot] = (mysmb_u8)(old_value - 6U);
        carry = old_value < 6U ? 1U : 0U;
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] =
            (mysmb_u8)(game->ram[MYSMB_ENEMY_Y_SPEED + slot] - carry);
        if (game->ram[MYSMB_ENEMY_Y_SPEED + slot] < 0xfeU &&
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] >= 0x80U &&
            game->ram[MYSMB_ENEMY_Y_FORCE + slot] < 0x80U) {
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0xfeU;
            game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0xffU;
        }
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_red_paratroopas(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot)
        mysmb_objects_step_red_paratroopas_slot(game, slot);
}

/* ROM $afe2 MoveFlyGreenPTroopa through $b003 MoveWithXMCntrs.  The original
 * aliases the two X movement counters to Enemy_Y_Speed and Enemy_X_Speed. */
void mysmb_objects_step_flying_green_paratroopas_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 primary;
    mysmb_u8 secondary;
    mysmb_u8 effective_speed;

    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        game->ram[MYSMB_ENEMY_ID + slot] != 16U) return;
    primary = game->ram[MYSMB_ENEMY_Y_SPEED + slot];
    secondary = game->ram[MYSMB_ENEMY_X_SPEED + slot];
    if ((game->ram[MYSMB_FRAME_COUNTER] & 3U) == 0U) {
        if ((primary & 1U) == 0U) {
            if (secondary == 0x13U) primary++;
            else secondary++;
        }
        else {
            if (secondary == 0U) primary++;
            else secondary--;
        }
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] = primary;
        game->ram[MYSMB_ENEMY_X_SPEED + slot] = secondary;
    }
    if ((primary & 2U) != 0U) {
        game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 1U;
        effective_speed = secondary;
    }
    else {
        game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
        effective_speed = (mysmb_u8)(0U - secondary);
    }
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = effective_speed;
    mysmb_world_move_enemy_horizontally(game, slot);
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = secondary;
    if ((game->ram[MYSMB_FRAME_COUNTER] & 3U) == 0U) {
        game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] +
            ((game->ram[MYSMB_FRAME_COUNTER] & 0x40U) != 0U ? 1U : 0xffU));
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_flying_green_paratroopas(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot)
        mysmb_objects_step_flying_green_paratroopas_slot(game, slot);
}

/* ROM $dcfd-$ddcb PlayerEnemyCollision, narrowed to the reserved power-up
 * slot.  The original uses screen-relative one-byte boxes; the same entries
 * are retained in RAM so later enemy-object routes can share them. */
void mysmb_objects_check_power_up_collision(struct mysmb_game *game)
{
    const mysmb_u8 slot = 5U;
    mysmb_u16 enemy_box;

    /* ROM PlayerEnemyCollision rejects the source vertical player mask and
     * GetEnemyBoundBox masked result.  It consumes screen-relative RAM boxes,
     * not an invented host world-coordinate visibility range. */
    if ((game->ram[MYSMB_FRAME_COUNTER] & 1U) != 0U ||
        game->ram[MYSMB_ENEMY_ID + slot] != 0x2eU ||
        game->ram[MYSMB_ENEMY_STATE + slot] < 6U ||
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 8U ||
        game->ram[MYSMB_PLAYER_OFFSCREEN_BITS] >= 0xf0U ||
        game->ram[MYSMB_PLAYER_Y_HIGH] != 1U ||
        game->ram[MYSMB_PLAYER_Y] >= 0xd0U ||
        game->ram[MYSMB_ENEMY_OFFSCREEN_BITS_MASKED + slot] != 0U) return;

    enemy_box = (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + slot * 4U);
    if (mysmb_world_boxes_collide(game, MYSMB_BOUNDING_BOX_PLAYER,
                                    enemy_box)) {
        mysmb_objects_collect_power_up(game);
    }
}
/* RunPUSubs continues immediately after DrawPowerUp.  Keep this tail separate
 * from the movement/drawing owner so direct object-unit fixtures can exercise
 * their local transition without inventing screen state; GameEngine invokes it
 * in the same source slot and frame. */
void mysmb_objects_finish_power_up(struct mysmb_game *game)
{
    const mysmb_u8 slot = 5U;

    if (game->ram[MYSMB_ENEMY_ID + slot] != 0x2eU ||
        game->ram[MYSMB_ENEMY_STATE + slot] < 6U) return;
    mysmb_objects_check_power_up_collision(game);
    /* HandlePowerUpCollision tail-jumps out of RunPUSubs. */
    if (game->ram[MYSMB_ENEMY_ID + slot] == 0x2eU) {
        mysmb_objects_check_enemy_offscreen_bounds(game, slot);
    }
}

/* ROM $ddcd HandlePowerUpCollision.  The score or 1-up is deliberately
 * deferred to FloateyNumbersRoutine, as in the original. */
void mysmb_objects_collect_power_up(struct mysmb_game *game)
{
    const mysmb_u8 slot = 5U;
    mysmb_u8 type;

    type = game->ram[MYSMB_POWER_UP_TYPE];
    game->ram[MYSMB_ENEMY_FLAG + slot] = 0U;
    game->ram[MYSMB_ENEMY_ID + slot] = 0U;
    game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
    game->ram[MYSMB_ENEMY_ATTRIBUTES + slot] = 0U;
    mysmb_objects_setup_floatey_number(game, slot,
                                       type == 3U ? 0x0bU : 6U);
    /* ROM HandlePowerUpCollision queues Sfx_PowerUpGrab. */
    game->ram[MYSMB_SQUARE2_SOUND] = 0x20U;
    if (type == 2U) {
        game->ram[MYSMB_STAR_INVINCIBLE_TIMER] = 0x23U;
        return;
    }
    if (type == 3U) return;
    if (game->ram[MYSMB_PLAYER_STATUS] == 0U) {
        game->ram[MYSMB_PLAYER_STATUS] = 1U;
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 9U;
    }
    else if (game->ram[MYSMB_PLAYER_STATUS] == 1U) {
        game->ram[MYSMB_PLAYER_STATUS] = 2U;
        /* ROM HandlePowerUpCollision calls GetPlayerColors immediately
         * after setting fiery status, before UpToFiery/SetPRout. */
        (void)mysmb_area_queue_player_palette(game);
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 12U;
    }
    else return;
    game->ram[MYSMB_PLAYER_STATE] = 0U;
    game->ram[MYSMB_TIMER_CONTROL] = 0xffU;
    game->ram[MYSMB_SCROLL_AMOUNT] = 0U;
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
        mysmb_objects_apply_digit_modifier(game,
            game->ram[MYSMB_CURRENT_PLAYER] == 0U ? 0x0bU : 0x11U);
        (void)mysmb_area_queue_score_coin_status(game);
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

/* ROM $ba55 Setup_Vine.  The original reserves enemy slot five for this
 * object, which is also the power-up slot and therefore cannot coexist. */
void mysmb_objects_start_vine(struct mysmb_game *game, mysmb_u8 block_slot)
{
    const mysmb_u8 slot = 5U;
    mysmb_u8 vine_slot;

    game->ram[MYSMB_ENEMY_ID + slot] = 0x2fU;
    game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
    game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[MYSMB_BLOCK_PAGE + block_slot];
    game->ram[MYSMB_ENEMY_X + slot] = game->ram[MYSMB_BLOCK_X + block_slot];
    game->ram[MYSMB_ENEMY_Y + slot] = game->ram[MYSMB_BLOCK_Y + block_slot];
    vine_slot = game->ram[MYSMB_VINE_FLAG_OFFSET];
    if (vine_slot == 0U) {
        game->ram[MYSMB_VINE_START_Y] = game->ram[MYSMB_ENEMY_Y + slot];
    }
    game->ram[MYSMB_VINE_OBJECT_OFFSET + vine_slot] = slot;
    game->ram[MYSMB_VINE_FLAG_OFFSET]++;
    game->ram[MYSMB_SQUARE2_SOUND] = 4U;
}

/* Translation of ChkOverR's inline caller setup for InitBlock_XY_Pos,
 * followed by Setup_Vine with X=5/Y=0. This remains a shared game-object
 * helper: platform code neither manufactures the block coordinates nor
 * creates the vine. */
void mysmb_objects_start_entrance_vine(struct mysmb_game *game)
{
    mysmb_u16 x_sum;

    x_sum = (mysmb_u16)game->ram[MYSMB_PLAYER_X] + 8U;
    game->ram[MYSMB_BLOCK_X] = (mysmb_u8)(x_sum & 0xf0U);
    game->ram[MYSMB_BLOCK_PAGE] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_PAGE] + (x_sum >> 8U));
    game->ram[MYSMB_BLOCK_PAGE_COPY] = game->ram[MYSMB_BLOCK_PAGE];
    game->ram[MYSMB_BLOCK_Y_HIGH] = game->ram[MYSMB_PLAYER_Y_HIGH];
    game->ram[MYSMB_BLOCK_Y] = 0xf0U;
    mysmb_objects_start_vine(game, 0U);
}

/* ROM $ba71 VineObjectHandler.  This retains growth and the authoritative
 * block-buffer metatile write; OAM drawing/offscreen retirement are renderer
 * responsibilities. */
void mysmb_objects_step_vine(struct mysmb_game *game)
{
    static const mysmb_u8 maximum_height[2] = { 0x30U, 0x60U };
    const mysmb_u8 slot = 5U;
    mysmb_u8 vine_slot;
    struct mysmb_enemy_terrain terrain;

    if (game->ram[MYSMB_ENEMY_ID + slot] != 0x2fU ||
        game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        game->ram[MYSMB_VINE_FLAG_OFFSET] == 0U) return;
    vine_slot = (mysmb_u8)(game->ram[MYSMB_VINE_FLAG_OFFSET] - 1U);
    if (vine_slot > 1U) vine_slot = 1U;
    if (game->ram[MYSMB_VINE_HEIGHT] != maximum_height[vine_slot] &&
        ((game->ram[MYSMB_FRAME_COUNTER] & 2U) != 0U)) {
        game->ram[MYSMB_ENEMY_Y + slot]--;
        game->ram[MYSMB_VINE_HEIGHT]++;
    }
    if (game->ram[MYSMB_VINE_HEIGHT] >= 8U) {
        mysmb_u8 draw_index;
        mysmb_u8 count;

        count = game->ram[MYSMB_VINE_FLAG_OFFSET];
        if (count > 2U) count = 2U;
        for (draw_index = 0U; draw_index < count; ++draw_index) {
            mysmb_u8 vine_slot;

            vine_slot = game->ram[MYSMB_VINE_OBJECT_OFFSET + draw_index];
            if (vine_slot < 6U &&
                game->ram[MYSMB_ENEMY_ID + vine_slot] == 0x2fU) {
                mysmb_objects_draw_vine(game, draw_index);
            }
        }
    }
    if (game->ram[MYSMB_VINE_HEIGHT] < 0x20U) return;
    if (mysmb_world_query_enemy_block(game, slot, 0x1bU, 0U, &terrain) == 0U ||
        terrain.block_row_offset >= 0xd0U) return;
    if (terrain.metatile == 0U) game->ram[terrain.block_address] = 0x26U;
}

/* SetupFloateyNumber.  Rendering later consumes the saved position. */
/* SetupFloateyNumber saves the current source-relative X coordinate. */
static void mysmb_objects_setup_floatey_number(struct mysmb_game *game,
                                               mysmb_u8 slot,
                                               mysmb_u8 control)
{
    mysmb_u16 enemy_world;
    mysmb_u16 screen_world;

    game->ram[MYSMB_FLOATEY_NUM_CONTROL + slot] = control;
    game->ram[MYSMB_FLOATEY_NUM_TIMER + slot] = 0x30U;
    game->ram[MYSMB_FLOATEY_NUM_Y + slot] = game->ram[MYSMB_ENEMY_Y + slot];
    enemy_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_PAGE + slot] << 8U) |
                               game->ram[MYSMB_ENEMY_X + slot]);
    screen_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_SCREEN_LEFT_PAGE] << 8U) |
                                game->ram[MYSMB_SCREEN_LEFT_X]);
    game->ram[MYSMB_FLOATEY_NUM_X + slot] = (mysmb_u8)(enemy_world - screen_world);
}
/* ROM SetupFloateyNumber after RelativeEnemyPosition.  This public cross-
 * owner seam consumes the source fixed scratch pair instead of rebuilding a
 * world coordinate; ordinary legacy callers retain their existing helper. */
void mysmb_objects_setup_floatey_from_relative(struct mysmb_game *game,
                                                mysmb_u8 slot,
                                                mysmb_u8 control)
{
    game->ram[MYSMB_FLOATEY_NUM_CONTROL + slot] = control;
    game->ram[MYSMB_FLOATEY_NUM_TIMER + slot] = 0x30U;
    game->ram[MYSMB_FLOATEY_NUM_Y + slot] = game->ram[MYSMB_ENEMY_Y + slot];
    game->ram[MYSMB_FLOATEY_NUM_X + slot] = game->ram[0x03aeU];
}
/* ROM $b3c2 MoveFlyingCheepCheep, excluding OAM priority output. */
void mysmb_objects_step_flying_cheep_cheeps_slot(struct mysmb_game *game, mysmb_u8 slot)
{

    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        game->ram[MYSMB_ENEMY_ID + slot] != 20U) return;
    if ((game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U) {
        mysmb_enemy_move_downward(game, slot, 0x1cU, 3U);
        return;
    }
    if (game->ram[MYSMB_TIMER_CONTROL] != 0U) return;
    mysmb_world_move_enemy_horizontally(game, slot);
    mysmb_enemy_move_downward(game, slot, 0x0dU, 5U);
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_flying_cheep_cheeps(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot)
        mysmb_objects_step_flying_cheep_cheeps_slot(game, slot);
}

/* ROM InitShortFirebar/InitLongFirebar, FirebarSpin, GetFirebarPosition, and
 * FirebarCollision.  The source's long-firebar duplicate only changes OAM
 * allocation, so every physical ball remains derived from the anchor slot. */
mysmb_u8 mysmb_objects_step_firebars_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 position[99] = {
        0U,1U,3U,4U,5U,6U,7U,7U,8U, 0U,3U,6U,9U,11U,13U,14U,15U,16U,
        0U,4U,9U,13U,16U,19U,22U,23U,24U, 0U,6U,12U,18U,22U,26U,29U,31U,32U,
        0U,7U,15U,22U,28U,33U,37U,39U,40U, 0U,9U,18U,27U,33U,39U,44U,47U,48U,
        0U,11U,21U,31U,39U,46U,51U,55U,56U, 0U,12U,24U,36U,45U,51U,59U,62U,64U,
        0U,14U,27U,40U,50U,59U,66U,70U,72U, 0U,15U,31U,45U,56U,66U,74U,78U,80U,
        0U,17U,34U,49U,62U,73U,81U,86U,88U
    };
    static const mysmb_u8 table_offset[12] = {
        0U,9U,18U,27U,36U,45U,54U,63U,72U,81U,90U,99U
    };
    static const mysmb_u8 mirror[4] = { 1U, 3U, 2U, 0U };
    mysmb_u8 phase;
    mysmb_u8 phase_part;
    mysmb_u8 vertical_phase;
    mysmb_u8 ball;
    mysmb_u8 maximum;
    mysmb_u8 horizontal;
    mysmb_u8 vertical;
    mysmb_u8 mirror_bits;
    mysmb_u8 anchor_x;
    mysmb_u8 anchor_y;
    mysmb_u8 ball_x;
    mysmb_u8 ball_y;
    mysmb_u8 player_x;
    mysmb_u8 player_y;
    mysmb_u8 candidate;
    mysmb_u8 old_low;
    mysmb_u8 carry;
    mysmb_u16 enemy_world;
    mysmb_u16 screen_world;

    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        game->ram[MYSMB_ENEMY_ID + slot] < 27U ||
        game->ram[MYSMB_ENEMY_ID + slot] > 31U) return 0U;
    if (game->ram[MYSMB_TIMER_CONTROL] == 0U) {
        old_low = game->ram[MYSMB_ENEMY_X_SPEED + slot];
        if (game->ram[0x0034U + slot] == 0U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] =
                (mysmb_u8)(old_low + game->ram[0x0388U + slot]);
            carry = game->ram[MYSMB_ENEMY_X_SPEED + slot] < old_low ? 1U : 0U;
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] =
                (mysmb_u8)(game->ram[MYSMB_ENEMY_Y_SPEED + slot] + carry);
        }
        else {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] =
                (mysmb_u8)(old_low - game->ram[0x0388U + slot]);
            carry = old_low < game->ram[0x0388U + slot] ? 1U : 0U;
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] =
                (mysmb_u8)(game->ram[MYSMB_ENEMY_Y_SPEED + slot] - carry);
        }
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] &= 0x1fU;
    }
    phase = game->ram[MYSMB_ENEMY_Y_SPEED + slot];
    if (game->ram[MYSMB_ENEMY_ID + slot] == 31U && (phase == 8U || phase == 24U)) {
        phase++;
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] = phase;
    }
    enemy_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_PAGE + slot] << 8U) |
                               game->ram[MYSMB_ENEMY_X + slot]);
    screen_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_SCREEN_LEFT_PAGE] << 8U) |
                                game->ram[MYSMB_SCREEN_LEFT_X]);
    if (enemy_world < screen_world || (mysmb_u16)(enemy_world - screen_world) >= 0x100U) return 0U;
    anchor_x = (mysmb_u8)(enemy_world - screen_world);
    anchor_y = game->ram[MYSMB_ENEMY_Y + slot];
    maximum = game->ram[MYSMB_ENEMY_ID + slot] == 31U ? 11U : 5U;
    for (ball = 0U; ball < maximum; ++ball) {
        phase_part = (mysmb_u8)(phase & 0x0fU);
        if (phase_part >= 9U) phase_part = (mysmb_u8)(16U - phase_part);
        vertical_phase = (mysmb_u8)((phase + 8U) & 0x0fU);
        if (vertical_phase >= 9U) vertical_phase = (mysmb_u8)(16U - vertical_phase);
        horizontal = position[(mysmb_u16)table_offset[ball] + phase_part];
        vertical = position[(mysmb_u16)table_offset[ball] + vertical_phase];
        mirror_bits = mirror[phase >> 3U];
        ball_x = (mysmb_u8)(anchor_x + ((mirror_bits & 1U) != 0U ? horizontal :
                                         (mysmb_u8)(0U - horizontal)));
        ball_y = (mysmb_u8)(anchor_y + ((mirror_bits & 2U) != 0U ? vertical :
                                         (mysmb_u8)(0U - vertical)));
        mysmb_objects_draw_firebar_ball(game, slot, ball, ball_x, ball_y, anchor_y);
        if (game->ram[MYSMB_STAR_INVINCIBLE_TIMER] != 0U ||
            game->ram[MYSMB_TIMER_CONTROL] != 0U || game->ram[MYSMB_PLAYER_Y_HIGH] != 1U ||
            ball_x >= 0xf0U) continue;
        player_x = (mysmb_u8)(game->ram[MYSMB_PLAYER_X] + 4U - game->ram[MYSMB_SCREEN_LEFT_X]);
        if (game->ram[MYSMB_PLAYER_SIZE] == 0U || game->ram[MYSMB_PLAYER_CROUCHING] != 0U) {
            candidate = (mysmb_u8)(game->ram[MYSMB_PLAYER_Y] + 0x18U);
            if ((mysmb_u8)(candidate > ball_y ? candidate - ball_y : ball_y - candidate) >= 8U) continue;
        }
        else {
            player_y = game->ram[MYSMB_PLAYER_Y];
            if ((mysmb_u8)(player_y > ball_y ? player_y - ball_y : ball_y - player_y) >= 8U &&
                ((mysmb_u8)(((mysmb_u8)(player_y + 0x0cU) > ball_y) ?
                 (mysmb_u8)(player_y + 0x0cU) - ball_y : ball_y - (mysmb_u8)(player_y + 0x0cU)) >= 8U) &&
                ((mysmb_u8)(((mysmb_u8)(player_y + 0x18U) > ball_y) ?
                 (mysmb_u8)(player_y + 0x18U) - ball_y : ball_y - (mysmb_u8)(player_y + 0x18U)) >= 8U)) continue;
        }
        if ((mysmb_u8)(player_x > ball_x ? player_x - ball_x : ball_x - player_x) >= 8U) continue;
        game->ram[MYSMB_ENEMY_MOVING_DIRECTION] = player_x >= ball_x ? 1U : 2U;
        mysmb_objects_force_injury(game);
        return 1U;
    }
    return 0U;
}

/* Temporary aggregate caller preserves the legacy injury early exit.
 * The slot result is a compatibility signal, not a ROM return register. */
void mysmb_objects_step_firebars(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (mysmb_objects_step_firebars_slot(game, slot) != 0U) return;
    }
}

/* ROM RunLargePlatform through RunSmallPlatform.  Platforms are ordinary
 * enemy slots in the original program: their Y fraction shares the enemy
 * vertical workspace, while the player receives the resulting deck motion. */
void mysmb_objects_step_platforms_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 id;
    mysmb_u8 old_y;
    mysmb_u8 old_x;
    mysmb_u8 old_player_x;
    mysmb_u8 old_force;
    mysmb_u8 carry;
    mysmb_u8 landed;
    mysmb_u8 peer;

    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U) return;
    id = game->ram[MYSMB_ENEMY_ID + slot];
    if (id < 36U || id > 44U) return;
    landed = 0U;
    if (game->ram[MYSMB_PLAYER_Y_HIGH] == 1U &&
        game->ram[MYSMB_PLAYER_PAGE] == game->ram[MYSMB_ENEMY_PAGE + slot] &&
        game->ram[MYSMB_PLAYER_X] + 16U >= game->ram[MYSMB_ENEMY_X + slot] &&
        game->ram[MYSMB_PLAYER_X] <= game->ram[MYSMB_ENEMY_X + slot] +
                                    (id == 43U || id == 44U ? 16U : 32U) &&
        game->ram[MYSMB_PLAYER_Y_SPEED] < 0x80U &&
        game->ram[MYSMB_PLAYER_Y] + 0x20U >= game->ram[MYSMB_ENEMY_Y + slot] &&
        game->ram[MYSMB_PLAYER_Y] + 0x20U <= game->ram[MYSMB_ENEMY_Y + slot] + 6U) {
        game->ram[MYSMB_PLAYER_Y] = (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - 0x20U);
        game->ram[MYSMB_PLAYER_Y_SPEED] = 0U;
        game->ram[MYSMB_PLAYER_Y_FORCE] = 0U;
        game->ram[MYSMB_PLAYER_STATE] = 0U;
        landed = 1U;
    }
    if (id >= 36U && id <= 42U) mysmb_objects_draw_large_platform(game, slot);
    if (id == 43U || id == 44U) mysmb_objects_draw_small_platform(game, slot);
    if (game->ram[MYSMB_TIMER_CONTROL] != 0U) return;
    if (id == 36U && landed != 0U) {
        /* BalancePlatform: state is the partner slot selected by
         * InitBalPlatform.  The rope is drawing-only; its two decks move
         * oppositely by the shared falling-platform increment. */
        peer = game->ram[MYSMB_ENEMY_STATE + slot];
        game->ram[MYSMB_ENEMY_Y + slot]++;
        if (peer < 5U && game->ram[MYSMB_ENEMY_FLAG + peer] != 0U &&
            game->ram[MYSMB_ENEMY_ID + peer] == 36U) {
            game->ram[MYSMB_ENEMY_Y + peer]--;
        }
    }
    else if (id == 37U) {
        /* YMovingPlatform: wait above its source top, then cycle between
         * top and centre using the native 8-bit vertical integrator. */
        if (game->ram[MYSMB_ENEMY_Y_SPEED + slot] == 0U &&
            game->ram[MYSMB_ENEMY_Y_FORCE + slot] == 0U &&
            game->ram[MYSMB_ENEMY_Y + slot] < game->ram[MYSMB_ENEMY_X_FORCE + slot]) {
            if ((game->ram[MYSMB_FRAME_COUNTER] & 7U) == 0U) game->ram[MYSMB_ENEMY_Y + slot]++;
        }
        else {
            if (game->ram[MYSMB_ENEMY_Y + slot] >= game->ram[MYSMB_ENEMY_X_SPEED + slot]) {
                game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0xffU;
                game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0x10U;
            }
            else {
                game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
                game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0xf0U;
            }
            old_force = game->ram[MYSMB_ENEMY_Y_DUMMY + slot];
            game->ram[MYSMB_ENEMY_Y_DUMMY + slot] = (mysmb_u8)(old_force +
                game->ram[MYSMB_ENEMY_Y_FORCE + slot]);
            carry = game->ram[MYSMB_ENEMY_Y_DUMMY + slot] < old_force ? 1U : 0U;
            old_y = game->ram[MYSMB_ENEMY_Y + slot];
            game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(old_y +
                game->ram[MYSMB_ENEMY_Y_SPEED + slot] + carry);
        }
    }
    else if (id == 38U || id == 39U || id == 43U || id == 44U) {
        /* MoveLiftPlatforms: fractional force plus signed whole speed. */
        old_force = game->ram[MYSMB_ENEMY_Y_DUMMY + slot];
        game->ram[MYSMB_ENEMY_Y_DUMMY + slot] = (mysmb_u8)(old_force +
            game->ram[MYSMB_ENEMY_Y_FORCE + slot]);
        carry = game->ram[MYSMB_ENEMY_Y_DUMMY + slot] < old_force ? 1U : 0U;
        old_y = game->ram[MYSMB_ENEMY_Y + slot];
        game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(old_y +
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] + carry);
        if (landed != 0U) {
            game->ram[MYSMB_PLAYER_Y] = (mysmb_u8)(game->ram[MYSMB_PLAYER_Y] +
                game->ram[MYSMB_ENEMY_Y + slot] - old_y);
        }
    }
    else if (id == 40U || id == 42U) {
        /* XMovingPlatform/RightPlatform: preserve the exact native
         * whole-pixel delta for both player world position and scroll. */
        old_x = game->ram[MYSMB_ENEMY_X + slot];
        old_player_x = game->ram[MYSMB_PLAYER_X];
        mysmb_world_move_enemy_horizontally(game, slot);
        if (landed != 0U) {
            game->ram[MYSMB_PLAYER_X] = (mysmb_u8)(old_player_x +
                game->ram[MYSMB_ENEMY_X + slot] - old_x);
            if (game->ram[MYSMB_PLAYER_X] < old_player_x) game->ram[MYSMB_PLAYER_PAGE]++;
            game->ram[0x03a1U] = (mysmb_u8)(game->ram[MYSMB_ENEMY_X + slot] - old_x);
        }
    }
    else if (id == 41U && landed != 0U) {
        /* DropPlatform switches to its falling route only after contact. */
        game->ram[MYSMB_ENEMY_Y + slot]++;
        game->ram[MYSMB_PLAYER_Y]++;
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_platforms(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot)
        mysmb_objects_step_platforms_slot(game, slot);
}

/* ROM InitBowser/RunBowser.  The rear-half duplicate affects only OAM; the
 * front object owns all collision, movement, hit points, and flame state. */
void mysmb_objects_step_bowsers_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 random_range[4] = { 0x21U, 0x41U, 0x11U, 0x31U };
    static const mysmb_u8 flame_timer[8] = { 0xbfU, 0x40U, 0xbfU, 0xbfU,
                                              0xbfU, 0x40U, 0x40U, 0xbfU };
    mysmb_u8 difference;
    mysmb_u8 direction;
    mysmb_u8 old_x;
    mysmb_u8 fire_timer_index;
    mysmb_u16 player_world;
    mysmb_u16 enemy_world;

    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        game->ram[MYSMB_ENEMY_ID + slot] != 45U) return;
    game->ram[0x0368U] = slot;
    if ((game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U) {
        mysmb_enemy_move_downward(game, slot, 0x1cU, 3U);
        return;
    }
    game->ram[MYSMB_ENEMY_FRENZY_BUFFER] = 0U;
    if (game->ram[MYSMB_TIMER_CONTROL] == 0U) {
        if ((game->ram[0x0363U] & 0x80U) == 0U) {
            game->ram[0x0364U]--;
            if (game->ram[0x0364U] == 0U) {
                game->ram[0x0364U] = 0x20U;
                game->ram[0x0363U] ^= 1U;
            }
            if ((game->ram[MYSMB_FRAME_COUNTER] & 0x0fU) == 0U) {
                game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
            }
            player_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_PLAYER_PAGE] << 8U) |
                                         game->ram[MYSMB_PLAYER_X]);
            enemy_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_PAGE + slot] << 8U) |
                                        game->ram[MYSMB_ENEMY_X + slot]);
            if (game->ram[0x078aU + slot] != 0U && enemy_world < player_world) {
                game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 1U;
                game->ram[0x0365U] = 2U;
                game->ram[0x078aU + slot] = 0x20U;
                game->ram[0x0790U] = 0x20U;
            }
            if ((game->ram[MYSMB_FRAME_COUNTER] & 3U) == 0U) {
                if (game->ram[MYSMB_ENEMY_X + slot] == game->ram[0x0366U]) {
                    game->ram[0x06dcU] = random_range[game->ram[0x07a8U + slot] & 3U];
                }
                old_x = game->ram[MYSMB_ENEMY_X + slot];
                game->ram[MYSMB_ENEMY_X + slot] =
                    (mysmb_u8)(old_x + game->ram[0x0365U]);
                difference = game->ram[MYSMB_ENEMY_X + slot] >= game->ram[0x0366U] ?
                    (mysmb_u8)(game->ram[MYSMB_ENEMY_X + slot] - game->ram[0x0366U]) :
                    (mysmb_u8)(game->ram[0x0366U] - game->ram[MYSMB_ENEMY_X + slot]);
                direction = game->ram[MYSMB_ENEMY_X + slot] >= game->ram[0x0366U] ? 0xffU : 1U;
                if (game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] != 1U &&
                    difference >= game->ram[0x06dcU]) game->ram[0x0365U] = direction;
            }
            if (game->ram[0x078aU + slot] == 0U) {
                mysmb_enemy_move_downward(game, slot, 0x0fU, 2U);
                if (game->ram[MYSMB_ENEMY_Y + slot] >= 0x80U) {
                    game->ram[0x078aU + slot] = random_range[game->ram[0x07a8U + slot] & 3U];
                }
            }
            else if (game->ram[0x078aU + slot] == 1U) {
                game->ram[MYSMB_ENEMY_Y + slot]--;
                game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0xfeU;
                game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
            }
        }
        if (game->ram[0x075fU] < 6U && game->ram[0x0790U] == 0U) {
            game->ram[0x0790U] = 0x20U;
            game->ram[0x0363U] ^= 0x80U;
            if ((game->ram[0x0363U] & 0x80U) == 0U) {
                fire_timer_index = game->ram[0x0367U] & 7U;
                game->ram[0x0367U] = (mysmb_u8)((game->ram[0x0367U] + 1U) & 7U);
                game->ram[0x0790U] = flame_timer[fire_timer_index];
                if (game->ram[MYSMB_SECONDARY_HARD] != 0U) game->ram[0x0790U] =
                    (mysmb_u8)(game->ram[0x0790U] - 0x10U);
                game->ram[MYSMB_ENEMY_FRENZY_BUFFER] = 21U;
            }
        }
    }
    if (game->ram[MYSMB_PLAYER_Y_HIGH] == 1U &&
        game->ram[MYSMB_PLAYER_PAGE] == game->ram[MYSMB_ENEMY_PAGE + slot] &&
        game->ram[MYSMB_PLAYER_X] + 16U >= game->ram[MYSMB_ENEMY_X + slot] &&
        game->ram[MYSMB_PLAYER_X] <= game->ram[MYSMB_ENEMY_X + slot] + 24U &&
        game->ram[MYSMB_PLAYER_Y] + 24U >= game->ram[MYSMB_ENEMY_Y + slot] &&
        game->ram[MYSMB_PLAYER_Y] <= game->ram[MYSMB_ENEMY_Y + slot] + 24U) {
        mysmb_objects_force_injury(game);
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_bowsers(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot)
        mysmb_objects_step_bowsers_slot(game, slot);
}

/* ROM ProcBowserFlame, excluding OAM. */
void mysmb_objects_step_bowser_flames_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 target_y[4] = { 0x90U, 0x80U, 0x70U, 0x90U };
    mysmb_u8 amount;
    mysmb_u8 old_force;
    mysmb_u8 borrow;

    if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U || game->ram[MYSMB_ENEMY_ID + slot] != 21U) return;
    if (game->ram[MYSMB_TIMER_CONTROL] == 0U) {
        amount = game->ram[MYSMB_SECONDARY_HARD] == 0U ? 0x40U : 0x60U;
        old_force = game->ram[MYSMB_ENEMY_X_FORCE + slot];
        game->ram[MYSMB_ENEMY_X_FORCE + slot] = (mysmb_u8)(old_force - amount);
        borrow = old_force < amount ? 1U : 0U;
        game->ram[MYSMB_ENEMY_X + slot] =
            (mysmb_u8)(game->ram[MYSMB_ENEMY_X + slot] - 1U - borrow);
        if (game->ram[MYSMB_ENEMY_X + slot] > (mysmb_u8)(0xffU - 1U - borrow)) {
            game->ram[MYSMB_ENEMY_PAGE + slot]--;
        }
        if (game->ram[MYSMB_ENEMY_Y + slot] != target_y[game->ram[MYSMB_ENEMY_Y_DUMMY + slot] & 3U]) {
            game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] +
                game->ram[MYSMB_ENEMY_Y_FORCE + slot]);
        }
    }
    mysmb_objects_draw_bowser_flame(game, slot);
    if (game->ram[MYSMB_PLAYER_Y_HIGH] == 1U &&
        game->ram[MYSMB_PLAYER_PAGE] == game->ram[MYSMB_ENEMY_PAGE + slot] &&
        game->ram[MYSMB_PLAYER_X] + 12U >= game->ram[MYSMB_ENEMY_X + slot] &&
        game->ram[MYSMB_PLAYER_X] <= game->ram[MYSMB_ENEMY_X + slot] + 16U &&
        game->ram[MYSMB_PLAYER_Y] + 16U >= game->ram[MYSMB_ENEMY_Y + slot] &&
        game->ram[MYSMB_PLAYER_Y] <= game->ram[MYSMB_ENEMY_Y + slot] + 16U) {
        mysmb_objects_force_injury(game);
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_objects_step_bowser_flames(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot)
        mysmb_objects_step_bowser_flames_slot(game, slot);
}

/* ROM $d7a9 ShellOrBlockDefeat, excluding audio. */
static void mysmb_objects_defeat_by_shell(struct mysmb_game *game,
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

/* ROM $dd04 EnemyTurnAround. */
static void mysmb_objects_turn_enemy(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 id;

    id = game->ram[MYSMB_ENEMY_ID + slot];
    if (id == 5U || (id >= 7U && id != 14U && id != 18U)) return;
    game->ram[MYSMB_ENEMY_X_SPEED + slot] =
        (mysmb_u8)(0U - game->ram[MYSMB_ENEMY_X_SPEED + slot]);
    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] ^= 3U;
}

/* ROM $dc96 MoveObjectHorizontally for the separate misc-object arrays. */
static void mysmb_objects_draw_jump_coin(struct mysmb_game *game, mysmb_u8 slot);
static void mysmb_objects_move_misc_horizontally(struct mysmb_game *game,
                                                 mysmb_u8 slot)
{
    mysmb_u8 speed;
    mysmb_u8 old_force;
    mysmb_u8 old_x;
    mysmb_u8 integer;
    mysmb_u8 page_delta;
    mysmb_u8 carry;

    speed = game->ram[MYSMB_MISC_X_SPEED + slot];
    integer = (mysmb_u8)(speed >> 4U);
    if (integer >= 8U) integer = (mysmb_u8)(integer | 0xf0U);
    page_delta = integer >= 0x80U ? 0xffU : 0U;
    old_force = game->ram[MYSMB_MISC_X_FORCE + slot];
    game->ram[MYSMB_MISC_X_FORCE + slot] =
        (mysmb_u8)(old_force + (mysmb_u8)(speed << 4U));
    carry = game->ram[MYSMB_MISC_X_FORCE + slot] < old_force ? 1U : 0U;
    old_x = game->ram[MYSMB_MISC_X + slot];
    game->ram[MYSMB_MISC_X + slot] = (mysmb_u8)(old_x + integer + carry);
    if (game->ram[MYSMB_MISC_X + slot] < old_x) {
        game->ram[MYSMB_MISC_PAGE + slot] =
            (mysmb_u8)(game->ram[MYSMB_MISC_PAGE + slot] + page_delta + 1U);
    }
    else game->ram[MYSMB_MISC_PAGE + slot] =
        (mysmb_u8)(game->ram[MYSMB_MISC_PAGE + slot] + page_delta);
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

/* ROM $ba81 SpawnHammerObj.  The source's six regular enemy slots make the
 * table entries for offsets six through eight naturally unavailable here. */
static mysmb_u8 mysmb_objects_spawn_hammer(struct mysmb_game *game,
                                           mysmb_u8 enemy_slot)
{
    static const mysmb_u8 hammer_enemy_offsets[9] = {
        4U, 4U, 4U, 5U, 5U, 5U, 6U, 6U, 6U
    };
    mysmb_u8 slot;
    mysmb_u8 random_value;

    random_value = game->ram[0x07a8U + enemy_slot];
    slot = (mysmb_u8)(random_value & 7U);
    if (slot == 0U) slot = (mysmb_u8)(random_value & 8U);
    if (game->ram[MYSMB_MISC_STATE + slot] != 0U ||
        hammer_enemy_offsets[slot] >= 6U ||
        game->ram[MYSMB_ENEMY_FLAG + hammer_enemy_offsets[slot]] != 0U) return 0U;
    game->ram[MYSMB_HAMMER_ENEMY_OFFSET + slot] = enemy_slot;
    game->ram[MYSMB_MISC_STATE + slot] = 0x90U;
    game->ram[MYSMB_MISC_BOUND_BOX + slot] = 7U;
    game->ram[MYSMB_MISC_COLLISION_FLAG + slot] = 0U;
    return 1U;
}

/* ROM $bac4 ProcHammerObj and the player collision path.
 * The 16-frame hand attachment is represented by state $90 through $82. */
static void mysmb_objects_step_hammer(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 state;
    mysmb_u8 enemy_slot;
    mysmb_u8 old_x;

    if (game->ram[MYSMB_TIMER_CONTROL] == 0U) {
        state = (mysmb_u8)(game->ram[MYSMB_MISC_STATE + slot] & 0x7fU);
        enemy_slot = game->ram[MYSMB_HAMMER_ENEMY_OFFSET + slot];
        if (enemy_slot >= 6U || game->ram[MYSMB_ENEMY_FLAG + enemy_slot] == 0U) {
            game->ram[MYSMB_MISC_STATE + slot] = 0U;
            return;
        }
        if (state < 2U) {
            mysmb_world_impose_gravity_misc(game, slot, 0x10U, 4U);
            mysmb_objects_move_misc_horizontally(game, slot);
            mysmb_objects_check_hammer_collision(game, slot);
        }
        else {
            if (state == 2U) {
                game->ram[MYSMB_MISC_Y_SPEED + slot] = 0xfeU;
                game->ram[MYSMB_ENEMY_STATE + enemy_slot] &= 0xf7U;
                game->ram[MYSMB_MISC_X_SPEED + slot] =
                    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + enemy_slot] == 1U ? 0x10U : 0xf0U;
            }
            game->ram[MYSMB_MISC_STATE + slot]--;
            old_x = game->ram[MYSMB_ENEMY_X + enemy_slot];
            game->ram[MYSMB_MISC_X + slot] = (mysmb_u8)(old_x + 2U);
            game->ram[MYSMB_MISC_PAGE + slot] = (mysmb_u8)(game->ram[MYSMB_ENEMY_PAGE + enemy_slot] +
                (game->ram[MYSMB_MISC_X + slot] < old_x ? 1U : 0U));
            game->ram[MYSMB_MISC_Y + slot] = (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + enemy_slot] - 0x0aU);
            game->ram[MYSMB_MISC_Y_HIGH + slot] = 1U;
        }
    }
    /* ROM RunHSubs: offscreen bits and relative coordinates are generated,
     * then GetMiscBoundBox writes this frame's box for the next collision. */
    mysmb_objects_prepare_hammer(game, slot);
    mysmb_world_set_bounding_box(game, (mysmb_u16)(0x04d0U + slot * 4U),
        game->ram[MYSMB_MISC_BOUND_BOX + slot], game->ram[0x03b3U],
        game->ram[0x03beU]);
    mysmb_objects_draw_hammer(game, slot);
}
/* ROM $ceee PlayerHammerCollision.  Misc bounding boxes occupy offsets
 * nine through seventeen after the player box at $04ac. */
static void mysmb_objects_check_hammer_collision(struct mysmb_game *game,
                                                 mysmb_u8 slot)
{
    mysmb_u16 hammer_box;

    /* ROM PlayerHammerCollision uses only FrameCounter and the prepared
     * TimerControl|Misc_OffscreenBits gate. Its box is from the preceding
     * RunHSubs pass; do not substitute world-coordinate clipping or a box
     * rebuilt from this frame's position. */
    if ((game->ram[MYSMB_FRAME_COUNTER] & 1U) == 0U ||
        game->ram[MYSMB_TIMER_CONTROL] != 0U ||
        game->ram[0x03d6U] != 0U) return;
    hammer_box = (mysmb_u16)(0x04d0U + slot * 4U);
    if (mysmb_world_boxes_collide(game, MYSMB_BOUNDING_BOX_PLAYER, hammer_box) == 0U) {
        game->ram[MYSMB_MISC_COLLISION_FLAG + slot] = 0U;
        return;
    }
    if (game->ram[MYSMB_MISC_COLLISION_FLAG + slot] != 0U) return;
    game->ram[MYSMB_MISC_COLLISION_FLAG + slot] = 1U;
    game->ram[MYSMB_MISC_X_SPEED + slot] =
        (mysmb_u8)(0U - game->ram[MYSMB_MISC_X_SPEED + slot]);
    if (game->ram[MYSMB_STAR_INVINCIBLE_TIMER] != 0U) return;
    mysmb_objects_force_injury(game);
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

/* ROM $8f6f DigitsMathRoutine.  DisplayDigits holds one decimal digit per
 * byte; the modifier is cleared after every calculation exactly as the ROM
 * routine does. */
static void mysmb_objects_apply_digit_modifier(struct mysmb_game *game,
                                               mysmb_u8 digit_offset)
{
    mysmb_status_apply_digit_modifier(game, digit_offset);
}


/* ROM $bbb6 GiveOneCoin.  Coin collection paths share this tally and status
 * command tail; the caller retains ownership of the metatile removal. */
static void mysmb_objects_give_one_coin(struct mysmb_game *game)
{
    mysmb_u8 player;

    game->ram[MYSMB_COIN_TALLY_FOR_1UPS]++;
    player = game->ram[MYSMB_CURRENT_PLAYER];
    game->ram[MYSMB_DIGIT_MODIFIER + 5U] = 1U;
    mysmb_objects_apply_digit_modifier(game, player == 0U ? 0x17U : 0x1dU);
    game->ram[MYSMB_COIN_TALLY]++;
    if (game->ram[MYSMB_COIN_TALLY] == 100U) {
        game->ram[MYSMB_COIN_TALLY] = 0U;
        game->ram[MYSMB_NUMBER_OF_LIVES]++;
    }
    game->ram[MYSMB_DIGIT_MODIFIER + 4U] = 2U;
    mysmb_objects_apply_digit_modifier(game, player == 0U ? 0x0bU : 0x11U);
    (void)mysmb_area_queue_score_coin_status(game);
}

#ifdef MYSMB_DOS16_TARGET
#pragma code_seg("MYSMB_BLOCK")
#endif


/* ROM $dedd HandleCoinMetatile. */
void mysmb_objects_collect_coin(struct mysmb_game *game, mysmb_u8 block_low,
                                mysmb_u8 block_row)
{
    mysmb_u16 address;

    address = (mysmb_u16)(0x0500U + block_low + block_row);
    if (address < 0x0800U) game->ram[address] = 0U;
    mysmb_area_remove_coin_axe(game, block_low, block_row);
    mysmb_objects_give_one_coin(game);
}

void mysmb_objects_remove_axe(struct mysmb_game *game, mysmb_u8 block_low,
                              mysmb_u8 block_row)
{
    mysmb_u16 address;

    address = (mysmb_u16)(0x0500U + block_low + block_row);
    if (address < 0x0800U) game->ram[address] = 0U;
    mysmb_area_remove_coin_axe(game, block_low, block_row);
}
/* ROM $bdf6 BlockBumpedChk's reviewed metatile table. */
static mysmb_u8 mysmb_objects_is_bumpable(mysmb_u8 metatile)
{
    mysmb_u8 index;

    for (index = 0U; index < sizeof(mysmb_brick_question_metatiles); ++index) {
        if (metatile == mysmb_brick_question_metatiles[index]) return 1U;
    }
    return 0U;
}

/* ROM $bd8b BlockCode, restricted to the entries which invoke SetupPowerUp. */
static mysmb_u8 mysmb_objects_power_up_for_block(mysmb_u8 metatile,
                                                  mysmb_u8 *power_up_type)
{
    if (metatile == 0xc1U || metatile == 0x55U || metatile == 0x5aU) {
        *power_up_type = 0U;
        return 1U;
    }
    if (metatile == 0x57U || metatile == 0x5cU) {
        *power_up_type = 2U;
        return 1U;
    }
    if (metatile == 0x60U || metatile == 0x59U || metatile == 0x5eU) {
        *power_up_type = 3U;
        return 1U;
    }
    return 0U;
}

static mysmb_u8 mysmb_objects_is_vine_block(mysmb_u8 metatile)
{
    return metatile == 0x56U || metatile == 0x5bU ? 1U : 0U;
}

/* ROM $bd9b BrickShatter/SpawnBrickChunks, excluding draw and audio output. */
static void mysmb_objects_start_brick_chunks(struct mysmb_game *game,
                                             mysmb_u8 slot)
{
    game->ram[MYSMB_BLOCK_REPLACE_FLAG + slot] = 1U;
    game->ram[MYSMB_BLOCK_ORIGINAL_X + slot] = game->ram[MYSMB_BLOCK_X + slot];
    game->ram[MYSMB_BLOCK_X_SPEED + slot] = 0xf0U;
    game->ram[MYSMB_BLOCK_X_SPEED + slot + 2U] = 0xf0U;
    game->ram[MYSMB_BLOCK_Y_SPEED + slot] = 0xfaU;
    game->ram[MYSMB_BLOCK_Y_SPEED + slot + 2U] = 0xfcU;
    game->ram[MYSMB_BLOCK_Y_FORCE + slot] = 0U;
    game->ram[MYSMB_BLOCK_Y_FORCE + slot + 2U] = 0U;
    game->ram[MYSMB_BLOCK_PAGE + slot + 2U] = game->ram[MYSMB_BLOCK_PAGE + slot];
    game->ram[MYSMB_BLOCK_X + slot + 2U] = game->ram[MYSMB_BLOCK_X + slot];
    game->ram[MYSMB_BLOCK_Y_HIGH + slot + 2U] =
        game->ram[MYSMB_BLOCK_Y_HIGH + slot];
    game->ram[MYSMB_BLOCK_Y + slot + 2U] =
        (mysmb_u8)(game->ram[MYSMB_BLOCK_Y + slot] + 8U);
    game->ram[MYSMB_DIGIT_MODIFIER + 5U] = 5U;
    mysmb_objects_apply_digit_modifier(game,
                                       game->ram[MYSMB_CURRENT_PLAYER] == 0U ?
                                       0x0bU : 0x11U);
    (void)mysmb_area_queue_score_coin_status(game);
    game->ram[MYSMB_PLAYER_Y_SPEED] = 0xfeU;
}

/* Translation of ROM $bced-$bd9b's matched-block path.  The caller retains
 * unmatched bricks for the later brick-chunk route. */
mysmb_u8 mysmb_objects_start_head_bump(struct mysmb_game *game,
                                       mysmb_u8 metatile,
                                       mysmb_u8 block_low,
                                       mysmb_u8 block_row)
{
    mysmb_u8 slot;
    mysmb_u8 old_x;
    mysmb_u8 y_adder;
    mysmb_u8 power_up_type;
    mysmb_u8 is_bumpable;
    mysmb_u16 address;
    mysmb_u16 x_sum;

    is_bumpable = mysmb_objects_is_bumpable(metatile);
    slot = (mysmb_u8)(game->ram[MYSMB_BLOCK_SLOT_CONTROL] & 1U);
    /* PlayerHeadCollision starts every hit as an unbreakable bounce ($11).
     * Only big Mario changes an ordinary, unmatched brick to state $12 for
     * the brick-chunk route.  Small Mario still bounces an ordinary brick;
     * returning early here lets him pass through it. */
    game->ram[MYSMB_BLOCK_STATE + slot] =
        game->ram[MYSMB_PLAYER_SIZE] == 0U ? 0x12U : 0x11U;
    game->ram[MYSMB_BLOCK_ORIGINAL_Y + slot] = block_row;
    game->ram[MYSMB_BLOCK_BUFFER_LOW + slot] = block_low;
    game->ram[MYSMB_BLOCK_METATILE + slot] =
        game->ram[MYSMB_PLAYER_SIZE] == 0U ? 0U : metatile;
    if (is_bumpable != 0U) {
        game->ram[MYSMB_BLOCK_STATE + slot] = 0x11U;
        game->ram[MYSMB_BLOCK_METATILE + slot] = 0xc4U;
        if (metatile == 0x58U || metatile == 0x5dU) {
            /* ROM BlockBumpedChk/StartBTmr: the first multi-coin bump
             * initializes the shared timer and increments its linked flag.
             * Later bumps retain the source metatile only while the timer is
             * nonzero; an expired timer produces the existing $c4. */
            if (game->ram[MYSMB_BRICK_COIN_TIMER_FLAG] == 0U) {
                game->ram[MYSMB_BRICK_COIN_TIMER] = 0x0bU;
                game->ram[MYSMB_BRICK_COIN_TIMER_FLAG]++;
            }
            if (game->ram[MYSMB_BRICK_COIN_TIMER] != 0U) {
                game->ram[MYSMB_BLOCK_METATILE + slot] = metatile;
            }
        }
    }
    address = (mysmb_u16)(0x0500U + block_low + block_row);
    if (address >= 0x0800U) return 0U;
    game->ram[address] = 0x23U;
    /* PlayerHeadCollision always enters DestroyBlockMetatile before it
     * dispatches BumpBlock. This is not coin-specific: the PPU must first
     * receive the two blank tile rows for bricks, question blocks, hidden
     * blocks, and item blocks alike. */
    mysmb_area_destroy_block_metatile(game, slot, block_low, block_row);
    old_x = game->ram[MYSMB_PLAYER_X];
    x_sum = (mysmb_u16)old_x + 8U;
    game->ram[MYSMB_BLOCK_X + slot] = (mysmb_u8)(x_sum & 0xf0U);
    /* InitBlock_XY_Pos preserves ADC's carry from Player_X + 8; the
     * following AND #$f0 does not replace it. */
    game->ram[MYSMB_BLOCK_PAGE + slot] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_PAGE] + (x_sum >> 8U));
    game->ram[MYSMB_BLOCK_PAGE_COPY + slot] = game->ram[MYSMB_BLOCK_PAGE + slot];
    game->ram[MYSMB_BLOCK_Y_HIGH + slot] = game->ram[MYSMB_PLAYER_Y_HIGH];
    y_adder = (game->ram[MYSMB_PLAYER_CROUCHING] != 0U ||
               game->ram[MYSMB_PLAYER_SIZE] != 0U) ? 0x12U : 4U;
    game->ram[MYSMB_BLOCK_Y + slot] =
        (mysmb_u8)((game->ram[MYSMB_PLAYER_Y] + y_adder) & 0xf0U);
    game->ram[MYSMB_BLOCK_Y_FORCE + slot] = 0U;
    game->ram[MYSMB_BLOCK_Y_SPEED + slot] = 0xfeU;
    game->ram[MYSMB_PLAYER_Y_SPEED] = 0U;
    game->ram[MYSMB_BLOCK_BOUNCE_TIMER] = 0x10U;
    game->ram[MYSMB_SQUARE1_SOUND] = 2U;
    mysmb_objects_check_top_of_block(game, slot, block_low, block_row);
    if (game->ram[MYSMB_BLOCK_STATE + slot] == 0x12U) {
        mysmb_objects_start_brick_chunks(game, slot);
    }
    else if (mysmb_objects_is_coin_block(metatile) != 0U) {
        /* CoinBlock reaches SBC #$10 with the carry left by BlockCode.
         * Entries $c0/$5f/$58 branch from CMP #$09 with carry clear and
         * therefore subtract $11; $5d first executes SBC #$05 and retains
         * carry, so it subtracts $10. */
        mysmb_objects_start_jump_coin(game, game->ram[MYSMB_BLOCK_PAGE + slot],
            (mysmb_u8)(game->ram[MYSMB_BLOCK_X + slot] | 5U),
            (mysmb_u8)(game->ram[MYSMB_BLOCK_Y + slot] -
                        (metatile == 0x5dU ? 0x10U : 0x11U)));
        mysmb_objects_give_one_coin(game);
    }
    else if (mysmb_objects_power_up_for_block(metatile, &power_up_type) != 0U) {
        mysmb_objects_start_power_up(game, slot, power_up_type);
    }
    else if (is_bumpable != 0U && mysmb_objects_is_vine_block(metatile) != 0U) {
        mysmb_objects_start_vine(game, slot);
    }
    game->ram[MYSMB_BLOCK_SLOT_CONTROL] ^= 1U;
    return 1U;
}

/* ROM $c076 MoveObjectHorizontally for the block-object array. */
static void mysmb_objects_move_block_horizontally(struct mysmb_game *game,
                                                  mysmb_u8 slot)
{
    mysmb_u8 speed;
    mysmb_u8 old_force;
    mysmb_u8 old_x;
    mysmb_u8 carry_force;
    mysmb_u8 carry_x;
    mysmb_u8 whole;
    mysmb_u8 page_delta;

    speed = game->ram[MYSMB_BLOCK_X_SPEED + slot];
    old_force = game->ram[MYSMB_BLOCK_X_FORCE + slot];
    game->ram[MYSMB_BLOCK_X_FORCE + slot] =
        (mysmb_u8)(old_force + (mysmb_u8)((speed & 0x0fU) << 4U));
    carry_force = game->ram[MYSMB_BLOCK_X_FORCE + slot] < old_force ? 1U : 0U;
    whole = (mysmb_u8)(speed >> 4U);
    page_delta = 0U;
    if (whole >= 8U) {
        whole = (mysmb_u8)(whole | 0xf0U);
        page_delta = 0xffU;
    }
    old_x = game->ram[MYSMB_BLOCK_X + slot];
    game->ram[MYSMB_BLOCK_X + slot] = (mysmb_u8)(old_x + whole + carry_force);
    carry_x = game->ram[MYSMB_BLOCK_X + slot] < old_x ? 1U : 0U;
    game->ram[MYSMB_BLOCK_PAGE + slot] =
        (mysmb_u8)(game->ram[MYSMB_BLOCK_PAGE + slot] + page_delta + carry_x);
}

/* Translation of ROM $be70 BlockObjectsCore's bouncing-block and brick-chunk
 * branches, excluding relative positioning and drawing. */
void mysmb_objects_step_block(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 state;

    state = game->ram[MYSMB_BLOCK_STATE + slot];
    if (state == 0U) return;
    state &= 0x0fU;
    if (state == 1U) {
        mysmb_world_impose_gravity_block(game, slot);
        mysmb_oam_relative_block_position(game, slot);
        mysmb_oam_get_block_offscreen_bits(game, slot);
        mysmb_objects_draw_bouncing_block(game, slot);
        if ((game->ram[MYSMB_BLOCK_Y + slot] & 0x0fU) < 5U) {
            game->ram[MYSMB_BLOCK_REPLACE_FLAG + slot] = 1U;
            state = 0U;
        }
    }
    else {
        mysmb_world_impose_gravity_block(game, slot);
        mysmb_objects_move_block_horizontally(game, slot);
        mysmb_world_impose_gravity_block(game, (mysmb_u8)(slot + 2U));
        mysmb_objects_move_block_horizontally(game, (mysmb_u8)(slot + 2U));
        mysmb_oam_relative_block_position(game, slot);
        mysmb_oam_get_block_offscreen_bits(game, slot);
        mysmb_objects_draw_brick_chunks(game, slot);
        if (game->ram[MYSMB_BLOCK_Y_HIGH + slot] != 0U) {
            if (game->ram[MYSMB_BLOCK_Y + slot + 2U] >= 0xf0U) {
                game->ram[MYSMB_BLOCK_Y + slot + 2U] = 0xf0U;
            }
            if (game->ram[MYSMB_BLOCK_Y + slot] >= 0xf0U) {
                state = 0U;
            }
        }
    }
    game->ram[MYSMB_BLOCK_STATE + slot] = state;
}

static mysmb_u8 mysmb_objects_is_coin_block(mysmb_u8 metatile)
{
    return metatile == 0xc0U || metatile == 0x5fU ||
        metatile == 0x58U || metatile == 0x5dU ? 1U : 0U;
}

/* ROM CheckTopOfBlock.  The source removes a coin directly over a bumped
 * block before it dispatches the bumped block's own CoinBlock behavior. */
static void mysmb_objects_check_top_of_block(struct mysmb_game *game,
                                             mysmb_u8 slot,
                                             mysmb_u8 block_low,
                                             mysmb_u8 block_row)
{
    mysmb_u8 top_row;
    mysmb_u16 address;

    if (block_row == 0U) return;
    top_row = (mysmb_u8)(block_row - 0x10U);
    address = (mysmb_u16)(0x0500U + block_low + top_row);
    if (address >= 0x0800U || game->ram[address] != 0xc2U) return;
    mysmb_objects_start_jump_coin(game,
        game->ram[MYSMB_BLOCK_PAGE_COPY + slot],
        (mysmb_u8)((block_low << 4U) | 5U),
        (mysmb_u8)(top_row + 0x20U));
    mysmb_objects_collect_coin(game, block_low, top_row);
}
