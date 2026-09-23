#include "game/objects.h"

enum {
    MYSMB_VRAM_BUFFER1 = 0x0301U,
    MYSMB_BLOCK_ORIGINAL_Y = 0x03e4U,
    MYSMB_BLOCK_BUFFER_LOW = 0x03e6U,
    MYSMB_BLOCK_METATILE = 0x03e8U,
    MYSMB_BLOCK_REPLACE_FLAG = 0x03ecU,
    MYSMB_BLOCK_STATE = 0x0026U,
    MYSMB_BLOCK_Y_SPEED = 0x00a8U,
    MYSMB_BLOCK_Y_HIGH = 0x00beU,
    MYSMB_BLOCK_Y = 0x00d7U,
    MYSMB_BLOCK_Y_DUMMY = 0x0420U,
    MYSMB_BLOCK_Y_FORCE = 0x043cU,
    MYSMB_BLOCK_X_SPEED = 0x0060U,
    MYSMB_BLOCK_X_FORCE = 0x0409U,
    MYSMB_BLOCK_PAGE = 0x0076U,
    MYSMB_BLOCK_X = 0x008fU,
    MYSMB_BLOCK_PAGE_COPY = 0x03eaU,
    MYSMB_BLOCK_SLOT_CONTROL = 0x03eeU,
    MYSMB_BLOCK_BOUNCE_TIMER = 0x0784U,
    MYSMB_BLOCK_ORIGINAL_X = 0x03f1U,
    MYSMB_PLAYER_SIZE = 0x0754U,
    MYSMB_PLAYER_CROUCHING = 0x0714U,
    MYSMB_PLAYER_PAGE = 0x006dU,
    MYSMB_PLAYER_X = 0x0086U,
    MYSMB_PLAYER_Y = 0x00ceU,
    MYSMB_PLAYER_Y_HIGH = 0x00b5U,
    MYSMB_PLAYER_Y_SPEED = 0x009fU
};

enum {
    MYSMB_MISC_STATE = 0x002aU,
    MYSMB_MISC_PAGE = 0x007aU,
    MYSMB_MISC_X = 0x0093U,
    MYSMB_MISC_Y_SPEED = 0x00acU,
    MYSMB_MISC_Y_HIGH = 0x00c2U,
    MYSMB_MISC_Y = 0x00dbU,
    MYSMB_MISC_Y_DUMMY = 0x0424U,
    MYSMB_MISC_Y_FORCE = 0x0440U,
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
    MYSMB_ENEMY_ATTRIBUTES = 0x03c5U,
    MYSMB_ENEMY_BOUND_BOX = 0x049aU,
    MYSMB_ENEMY_X_FORCE = 0x0401U,
    MYSMB_PLAYER_BOUND_BOX = 0x0499U,
    MYSMB_PLAYER_OFFSCREEN_BITS = 0x03d0U,
    MYSMB_SCREEN_LEFT_PAGE = 0x071dU,
    MYSMB_SCREEN_LEFT_X = 0x071aU,
    MYSMB_BOUNDING_BOX_PLAYER = 0x04acU,
    MYSMB_BOUNDING_BOX_ENEMY = 0x04b0U,
    MYSMB_PLAYER_STATUS = 0x0756U,
    MYSMB_GAME_ENGINE_SUBROUTINE = 0x000eU,
    MYSMB_PLAYER_STATE = 0x001dU,
    MYSMB_TIMER_CONTROL = 0x0747U,
    MYSMB_STAR_INVINCIBLE_TIMER = 0x079fU,
    MYSMB_VINE_FLAG_OFFSET = 0x0398U,
    MYSMB_VINE_HEIGHT = 0x0399U,
    MYSMB_VINE_OBJECT_OFFSET = 0x039aU,
    MYSMB_VINE_START_Y = 0x039dU
};

static void mysmb_objects_apply_digit_modifier(struct mysmb_game *game,
                                               mysmb_u8 digit_offset);
static void mysmb_objects_move_enemy_horizontally(struct mysmb_game *game,
                                                  mysmb_u8 slot);
static void mysmb_objects_set_bounding_box(struct mysmb_game *game,
                                           mysmb_u16 address, mysmb_u8 control,
                                           mysmb_u8 x, mysmb_u8 y);
static mysmb_u8 mysmb_objects_boxes_collide(const struct mysmb_game *game,
                                            mysmb_u16 first, mysmb_u16 second);

/* ROM $bb51 SetupJumpCoin. */
void mysmb_objects_start_jump_coin(struct mysmb_game *game, mysmb_u8 page,
                                   mysmb_u8 x, mysmb_u8 y)
{
    mysmb_u8 slot;

    slot = 8U;
    while (slot > 5U && game->ram[MYSMB_MISC_STATE + slot] != 0U) --slot;
    if (slot == 5U) slot = 8U;
    game->ram[MYSMB_MISC_PAGE + slot] = page;
    game->ram[MYSMB_MISC_X + slot] = x;
    game->ram[MYSMB_MISC_Y + slot] = y;
    game->ram[MYSMB_MISC_Y_SPEED + slot] = 0xfbU;
    game->ram[MYSMB_MISC_Y_HIGH + slot] = 1U;
    game->ram[MYSMB_MISC_Y_DUMMY + slot] = 0U;
    game->ram[MYSMB_MISC_Y_FORCE + slot] = 0U;
    game->ram[MYSMB_MISC_STATE + slot] = 1U;
}

/* ROM $bb96-$bbd0 ProcJumpCoin, excluding draw and score presentation. */
void mysmb_objects_step_misc(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u8 old_value;
    mysmb_u8 carry;

    for (slot = 6U; slot <= 8U; ++slot) {
        if (game->ram[MYSMB_MISC_STATE + slot] == 0U) continue;
        if (game->ram[MYSMB_MISC_STATE + slot] == 1U) {
            old_value = game->ram[MYSMB_MISC_Y_DUMMY + slot];
            game->ram[MYSMB_MISC_Y_DUMMY + slot] =
                (mysmb_u8)(old_value + game->ram[MYSMB_MISC_Y_FORCE + slot]);
            carry = game->ram[MYSMB_MISC_Y_DUMMY + slot] < old_value ? 1U : 0U;
            old_value = game->ram[MYSMB_MISC_Y + slot];
            game->ram[MYSMB_MISC_Y + slot] = (mysmb_u8)(old_value +
                game->ram[MYSMB_MISC_Y_SPEED + slot] + carry);
            if (game->ram[MYSMB_MISC_Y + slot] < old_value &&
                game->ram[MYSMB_MISC_Y_SPEED + slot] >= 0x80U) --game->ram[MYSMB_MISC_Y_HIGH + slot];
            old_value = game->ram[MYSMB_MISC_Y_FORCE + slot];
            game->ram[MYSMB_MISC_Y_FORCE + slot] = (mysmb_u8)(old_value + 0x50U);
            if (game->ram[MYSMB_MISC_Y_FORCE + slot] < old_value) game->ram[MYSMB_MISC_Y_SPEED + slot]++;
            if (game->ram[MYSMB_MISC_Y_SPEED + slot] >= 6U && game->ram[MYSMB_MISC_Y_SPEED + slot] < 0x80U) game->ram[MYSMB_MISC_STATE + slot]++;
        }
        else {
            game->ram[MYSMB_MISC_STATE + slot]++;
            game->ram[MYSMB_MISC_X + slot] = (mysmb_u8)(game->ram[MYSMB_MISC_X + slot] + game->ram[MYSMB_SCROLL_AMOUNT]);
            if (game->ram[MYSMB_MISC_STATE + slot] == 0x30U) game->ram[MYSMB_MISC_STATE + slot] = 0U;
        }
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
}

/* ROM $bbef-$bc15 GrowThePowerUp and $dc96 MoveObjectHorizontally.  Terrain
 * response remains in the later EnemyToBGCollisionDet route. */
void mysmb_objects_step_power_up(struct mysmb_game *game)
{
    const mysmb_u8 slot = 5U;
    mysmb_u8 state;

    state = game->ram[MYSMB_ENEMY_STATE + slot];
    if (state == 0U) return;
    if ((state & 0x80U) != 0U) {
        if (game->ram[MYSMB_TIMER_CONTROL] != 0U &&
            (game->ram[MYSMB_POWER_UP_TYPE] == 0U ||
             game->ram[MYSMB_POWER_UP_TYPE] == 3U)) {
            mysmb_objects_move_enemy_horizontally(game, slot);
        }
        return;
    }
    if (((mysmb_u8)game->frame_number & 3U) != 0U) return;
    game->ram[MYSMB_ENEMY_Y + slot]--;
    game->ram[MYSMB_ENEMY_STATE + slot]++;
    if (state >= 0x11U) {
        game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0x10U;
        game->ram[MYSMB_ENEMY_STATE + slot] = 0x80U;
        game->ram[MYSMB_ENEMY_ATTRIBUTES + slot] = 0U;
        game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 1U;
    }
}

/* ROM $dcfd-$ddcb PlayerEnemyCollision, narrowed to the reserved power-up
 * slot.  The original uses screen-relative one-byte boxes; the same entries
 * are retained in RAM so later enemy-object routes can share them. */
void mysmb_objects_check_power_up_collision(struct mysmb_game *game)
{
    const mysmb_u8 slot = 5U;
    mysmb_u16 player_world;
    mysmb_u16 enemy_world;
    mysmb_u16 screen_world;

    if (((mysmb_u8)game->frame_number & 1U) != 0U ||
        game->ram[MYSMB_ENEMY_ID + slot] != 0x2eU ||
        (game->ram[MYSMB_ENEMY_STATE + slot] & 0x80U) == 0U ||
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 8U ||
        game->ram[MYSMB_PLAYER_OFFSCREEN_BITS] >= 0xf0U ||
        game->ram[MYSMB_PLAYER_Y_HIGH] != 1U ||
        game->ram[MYSMB_PLAYER_Y] >= 0xd0U) return;

    player_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_PLAYER_PAGE] << 8U) |
                                game->ram[MYSMB_PLAYER_X]);
    enemy_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_PAGE + slot] << 8U) |
                               game->ram[MYSMB_ENEMY_X + slot]);
    screen_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_SCREEN_LEFT_PAGE] << 8U) |
                                game->ram[MYSMB_SCREEN_LEFT_X]);
    if (player_world < screen_world || enemy_world < screen_world ||
        (mysmb_u16)(player_world - screen_world) >= 0x100U ||
        (mysmb_u16)(enemy_world - screen_world) >= 0x100U) return;

    mysmb_objects_set_bounding_box(game, MYSMB_BOUNDING_BOX_PLAYER,
                                   game->ram[MYSMB_PLAYER_BOUND_BOX],
                                   (mysmb_u8)(player_world - screen_world),
                                   game->ram[MYSMB_PLAYER_Y]);
    mysmb_objects_set_bounding_box(game,
                                   (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + slot * 4U),
                                   game->ram[MYSMB_ENEMY_BOUND_BOX + slot],
                                   (mysmb_u8)(enemy_world - screen_world),
                                   game->ram[MYSMB_ENEMY_Y + slot]);
    if (mysmb_objects_boxes_collide(game, MYSMB_BOUNDING_BOX_PLAYER,
                                    (mysmb_u16)(MYSMB_BOUNDING_BOX_ENEMY + slot * 4U))) {
        mysmb_objects_collect_power_up(game);
    }
}

/* ROM $ddcd HandlePowerUpCollision.  The Floatey-number visual and delayed
 * 1-up award remain with the later enemy/floatey route; its pending type is
 * deliberately retained rather than converted to an immediate life. */
void mysmb_objects_collect_power_up(struct mysmb_game *game)
{
    const mysmb_u8 slot = 5U;
    mysmb_u8 type;

    type = game->ram[MYSMB_POWER_UP_TYPE];
    game->ram[MYSMB_ENEMY_FLAG + slot] = 0U;
    game->ram[MYSMB_ENEMY_ID + slot] = 0U;
    game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
    game->ram[MYSMB_ENEMY_ATTRIBUTES + slot] = 0U;
    game->ram[MYSMB_DIGIT_MODIFIER + 3U] = 1U;
    mysmb_objects_apply_digit_modifier(game,
                                       game->ram[MYSMB_CURRENT_PLAYER] == 0U ?
                                       0x0bU : 0x11U);
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
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 12U;
    }
    else return;
    game->ram[MYSMB_PLAYER_STATE] = 0U;
    game->ram[MYSMB_TIMER_CONTROL] = 0xffU;
    game->ram[MYSMB_SCROLL_AMOUNT] = 0U;
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
    if (vine_slot < 2U) {
        game->ram[MYSMB_VINE_OBJECT_OFFSET + vine_slot] = slot;
        game->ram[MYSMB_VINE_FLAG_OFFSET]++;
    }
}

/* ROM $ba71 VineObjectHandler.  This retains growth and the authoritative
 * block-buffer metatile write; OAM drawing/offscreen retirement are renderer
 * responsibilities. */
void mysmb_objects_step_vine(struct mysmb_game *game)
{
    static const mysmb_u8 maximum_height[2] = { 0x30U, 0x60U };
    const mysmb_u8 slot = 5U;
    mysmb_u8 vine_slot;
    mysmb_u8 x;
    mysmb_u8 page;
    mysmb_u8 row;
    mysmb_u16 address;

    if (game->ram[MYSMB_ENEMY_ID + slot] != 0x2fU ||
        game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
        game->ram[MYSMB_VINE_FLAG_OFFSET] == 0U) return;
    vine_slot = (mysmb_u8)(game->ram[MYSMB_VINE_FLAG_OFFSET] - 1U);
    if (vine_slot > 1U) vine_slot = 1U;
    if (game->ram[MYSMB_VINE_HEIGHT] != maximum_height[vine_slot] &&
        (((mysmb_u8)game->frame_number & 2U) != 0U)) {
        game->ram[MYSMB_ENEMY_Y + slot]--;
        game->ram[MYSMB_VINE_HEIGHT]++;
    }
    if (game->ram[MYSMB_VINE_HEIGHT] < 0x20U) return;
    x = (mysmb_u8)(game->ram[MYSMB_ENEMY_X + slot] + 4U);
    page = (mysmb_u8)(game->ram[MYSMB_ENEMY_PAGE + slot] +
                      (x < game->ram[MYSMB_ENEMY_X + slot] ? 1U : 0U));
    row = (mysmb_u8)(((game->ram[MYSMB_ENEMY_Y + slot] + 0x10U) & 0xf0U) -
                      0x20U);
    if (row >= 0xd0U) return;
    address = (mysmb_u16)((page & 1U) != 0U ? 0x05d0U : 0x0500U);
    address = (mysmb_u16)(address + (x >> 4U) + row);
    if (address < 0x0800U && game->ram[address] == 0U) game->ram[address] = 0x26U;
}

/* ROM $dc96 MoveObjectHorizontally, with the enemy-object offset applied. */
static void mysmb_objects_move_enemy_horizontally(struct mysmb_game *game,
                                                  mysmb_u8 slot)
{
    mysmb_u8 speed;
    mysmb_u8 fraction;
    mysmb_u8 integer;
    mysmb_u8 old_force;
    mysmb_u8 old_x;
    mysmb_u8 carry;
    mysmb_u8 page_delta;

    speed = game->ram[MYSMB_ENEMY_X_SPEED + slot];
    fraction = (mysmb_u8)(speed << 4U);
    integer = (mysmb_u8)(speed >> 4U);
    if (integer >= 8U) integer = (mysmb_u8)(integer | 0xf0U);
    page_delta = integer >= 0x80U ? 0xffU : 0U;
    old_force = game->ram[MYSMB_ENEMY_X_FORCE + slot];
    game->ram[MYSMB_ENEMY_X_FORCE + slot] = (mysmb_u8)(old_force + fraction);
    carry = game->ram[MYSMB_ENEMY_X_FORCE + slot] < old_force ? 1U : 0U;
    old_x = game->ram[MYSMB_ENEMY_X + slot];
    game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(old_x + integer + carry);
    if (game->ram[MYSMB_ENEMY_X + slot] < old_x) {
        game->ram[MYSMB_ENEMY_PAGE + slot] =
            (mysmb_u8)(game->ram[MYSMB_ENEMY_PAGE + slot] + page_delta + 1U);
    }
    else {
        game->ram[MYSMB_ENEMY_PAGE + slot] =
            (mysmb_u8)(game->ram[MYSMB_ENEMY_PAGE + slot] + page_delta);
    }
}

/* ROM $e2a5 BoundBoxCtrlData and $dc71 BoundingBoxCore. */
static void mysmb_objects_set_bounding_box(struct mysmb_game *game,
                                           mysmb_u16 address, mysmb_u8 control,
                                           mysmb_u8 x, mysmb_u8 y)
{
    static const mysmb_u8 bounds[48] = {
        0x02U, 0x08U, 0x0eU, 0x20U, 0x03U, 0x14U, 0x0dU, 0x20U,
        0x02U, 0x14U, 0x0eU, 0x20U, 0x02U, 0x09U, 0x0eU, 0x15U,
        0x00U, 0x00U, 0x18U, 0x06U, 0x00U, 0x00U, 0x20U, 0x0dU,
        0x00U, 0x00U, 0x30U, 0x0dU, 0x00U, 0x00U, 0x08U, 0x08U,
        0x06U, 0x04U, 0x0aU, 0x08U, 0x03U, 0x0eU, 0x0dU, 0x14U,
        0x00U, 0x02U, 0x10U, 0x15U, 0x04U, 0x04U, 0x0cU, 0x1cU
    };
    mysmb_u8 offset;

    if (control >= 12U) control = 0U;
    offset = (mysmb_u8)(control * 4U);
    game->ram[address] = (mysmb_u8)(x + bounds[offset]);
    game->ram[address + 1U] = (mysmb_u8)(y + bounds[offset + 1U]);
    game->ram[address + 2U] = (mysmb_u8)(x + bounds[offset + 2U]);
    game->ram[address + 3U] = (mysmb_u8)(y + bounds[offset + 3U]);
}

/* ROM $dcf6 PlayerCollisionCore, for same-screen power-up boxes. */
static mysmb_u8 mysmb_objects_boxes_collide(const struct mysmb_game *game,
                                            mysmb_u16 first, mysmb_u16 second)
{
    if (game->ram[first] > game->ram[second + 2U] ||
        game->ram[first + 2U] < game->ram[second] ||
        game->ram[first + 1U] > game->ram[second + 3U] ||
        game->ram[first + 3U] < game->ram[second + 1U]) return 0U;
    return 1U;
}
/* ROM $8f6f DigitsMathRoutine.  DisplayDigits holds one decimal digit per
 * byte; the modifier is cleared after every calculation exactly as the ROM
 * routine does. */
static void mysmb_objects_apply_digit_modifier(struct mysmb_game *game,
                                               mysmb_u8 digit_offset)
{
    mysmb_u8 index;
    mysmb_u8 value;

    if (game->ram[MYSMB_OPERATING_MODE] != 0U) {
        index = 5U;
        while (1) {
            value = (mysmb_u8)(game->ram[MYSMB_DIGIT_MODIFIER + index] +
                               game->ram[MYSMB_DISPLAY_DIGITS + digit_offset]);
            if (value >= 0x80U) {
                game->ram[MYSMB_DIGIT_MODIFIER + index - 1U]--;
                value = 9U;
            }
            else if (value >= 10U) {
                value = (mysmb_u8)(value - 10U);
                game->ram[MYSMB_DIGIT_MODIFIER + index - 1U]++;
            }
            game->ram[MYSMB_DISPLAY_DIGITS + digit_offset] = value;
            if (index == 0U) break;
            --index;
            --digit_offset;
        }
    }
    for (index = 0U; index <= 6U; ++index) {
        game->ram[MYSMB_DIGIT_MODIFIER + index] = 0U;
    }
}

/* ROM $dedd HandleCoinMetatile and $bbb6 GiveOneCoin.  Presentation and
 * sound-buffer writes belong to the renderer/audio owners; this routine
 * preserves the block-buffer, decimal score, tally, and life state. */
void mysmb_objects_collect_coin(struct mysmb_game *game, mysmb_u8 block_low,
                                mysmb_u8 block_row)
{
    mysmb_u16 address;
    mysmb_u8 player;

    address = (mysmb_u16)(0x0500U + block_low + block_row);
    if (address < 0x0800U) game->ram[address] = 0U;
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
}

/* ROM $bdf6 BlockBumpedChk's reviewed metatile table. */
static mysmb_u8 mysmb_objects_is_bumpable(mysmb_u8 metatile)
{
    static const mysmb_u8 bumpable[14] = {
        0xc1U, 0xc0U, 0x5fU, 0x60U, 0x55U, 0x56U, 0x57U,
        0x58U, 0x59U, 0x5aU, 0x5bU, 0x5cU, 0x5dU, 0x5eU
    };
    mysmb_u8 index;

    for (index = 0U; index < sizeof(bumpable); ++index) {
        if (metatile == bumpable[index]) return 1U;
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

    is_bumpable = mysmb_objects_is_bumpable(metatile);
    if (is_bumpable == 0U && game->ram[MYSMB_PLAYER_SIZE] != 0U) return 0U;
    slot = (mysmb_u8)(game->ram[MYSMB_BLOCK_SLOT_CONTROL] & 1U);
    game->ram[MYSMB_BLOCK_STATE + slot] = is_bumpable != 0U ? 0x11U : 0x12U;
    game->ram[MYSMB_BLOCK_ORIGINAL_Y + slot] = block_row;
    game->ram[MYSMB_BLOCK_BUFFER_LOW + slot] = block_low;
    game->ram[MYSMB_BLOCK_METATILE + slot] = is_bumpable != 0U ? 0xc4U : 0U;
    if (is_bumpable != 0U && (metatile == 0x58U || metatile == 0x5dU)) {
        game->ram[MYSMB_BLOCK_METATILE + slot] = metatile;
    }
    address = (mysmb_u16)(0x0500U + block_low + block_row);
    if (address >= 0x0800U) return 0U;
    game->ram[address] = 0x23U;
    old_x = game->ram[MYSMB_PLAYER_X];
    game->ram[MYSMB_BLOCK_X + slot] = (mysmb_u8)((old_x + 8U) & 0xf0U);
    game->ram[MYSMB_BLOCK_PAGE + slot] = game->ram[MYSMB_PLAYER_PAGE];
    if (game->ram[MYSMB_BLOCK_X + slot] < old_x) {
        game->ram[MYSMB_BLOCK_PAGE + slot]++;
    }
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
    if (is_bumpable == 0U) {
        mysmb_objects_start_brick_chunks(game, slot);
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

/* ROM $bfa4 ImposeGravityBlock / ImposeGravity for a block-object slot.
 * Block objects use downward force $50 and maximum speed $08. */
static void mysmb_objects_impose_block_gravity(struct mysmb_game *game,
                                               mysmb_u8 slot)
{
    mysmb_u8 old_value;
    mysmb_u8 carry_dummy;
    mysmb_u8 carry_y;
    mysmb_u8 page_delta;

    old_value = game->ram[MYSMB_BLOCK_Y_DUMMY + slot];
    game->ram[MYSMB_BLOCK_Y_DUMMY + slot] =
        (mysmb_u8)(old_value + game->ram[MYSMB_BLOCK_Y_FORCE + slot]);
    carry_dummy = game->ram[MYSMB_BLOCK_Y_DUMMY + slot] < old_value ? 1U : 0U;
    page_delta = game->ram[MYSMB_BLOCK_Y_SPEED + slot] >= 0x80U ? 0xffU : 0U;
    old_value = game->ram[MYSMB_BLOCK_Y + slot];
    game->ram[MYSMB_BLOCK_Y + slot] =
        (mysmb_u8)(old_value + game->ram[MYSMB_BLOCK_Y_SPEED + slot] + carry_dummy);
    carry_y = game->ram[MYSMB_BLOCK_Y + slot] < old_value ? 1U : 0U;
    game->ram[MYSMB_BLOCK_Y_HIGH + slot] =
        (mysmb_u8)(game->ram[MYSMB_BLOCK_Y_HIGH + slot] + page_delta + carry_y);
    old_value = game->ram[MYSMB_BLOCK_Y_FORCE + slot];
    game->ram[MYSMB_BLOCK_Y_FORCE + slot] = (mysmb_u8)(old_value + 0x50U);
    if (game->ram[MYSMB_BLOCK_Y_FORCE + slot] < old_value) {
        game->ram[MYSMB_BLOCK_Y_SPEED + slot]++;
    }
    if (game->ram[MYSMB_BLOCK_Y_SPEED + slot] < 0x80U &&
        game->ram[MYSMB_BLOCK_Y_SPEED + slot] >= 8U &&
        game->ram[MYSMB_BLOCK_Y_FORCE + slot] >= 0x80U) {
        game->ram[MYSMB_BLOCK_Y_SPEED + slot] = 8U;
        game->ram[MYSMB_BLOCK_Y_FORCE + slot] = 0U;
    }
}

/* Translation of ROM $be70 BlockObjectsCore's bouncing-block and brick-chunk
 * branches, excluding relative positioning and drawing. */
void mysmb_objects_step_blocks(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u8 state;

    for (slot = 0U; slot < 2U; ++slot) {
        state = game->ram[MYSMB_BLOCK_STATE + slot];
        if ((state & 0x0fU) == 1U) {
            mysmb_objects_impose_block_gravity(game, slot);
            if ((game->ram[MYSMB_BLOCK_Y + slot] & 0x0fU) < 5U) {
                game->ram[MYSMB_BLOCK_REPLACE_FLAG + slot] = 1U;
                game->ram[MYSMB_BLOCK_STATE + slot] = 0U;
            }
        }
        else {
            mysmb_objects_impose_block_gravity(game, slot);
            mysmb_objects_move_block_horizontally(game, slot);
            mysmb_objects_impose_block_gravity(game, (mysmb_u8)(slot + 2U));
            mysmb_objects_move_block_horizontally(game, (mysmb_u8)(slot + 2U));
            if (game->ram[MYSMB_BLOCK_Y_HIGH + slot] != 0U) {
                if (game->ram[MYSMB_BLOCK_Y + slot + 2U] >= 0xf0U) {
                    game->ram[MYSMB_BLOCK_Y + slot + 2U] = 0xf0U;
                }
                if (game->ram[MYSMB_BLOCK_Y + slot] >= 0xf0U) {
                    game->ram[MYSMB_BLOCK_STATE + slot] = 0U;
                }
            }
        }
    }
}

/* Translation of ROM $bed4 BlockObjMT_Updater's two block-object replacement slots.
 * ReplaceBlockMetatile's name-table write belongs to the later renderer. */
void mysmb_objects_apply_block_replacements(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u16 address;

    for (slot = 2U; slot != 0U; --slot) {
        mysmb_u8 index = (mysmb_u8)(slot - 1U);
        if (game->ram[MYSMB_VRAM_BUFFER1] != 0U) continue;
        if (game->ram[MYSMB_BLOCK_REPLACE_FLAG + index] == 0U) continue;
        address = (mysmb_u16)(0x0500U + game->ram[MYSMB_BLOCK_BUFFER_LOW + index] +
                              game->ram[MYSMB_BLOCK_ORIGINAL_Y + index]);
        if (address < 0x0800U) game->ram[address] =
            game->ram[MYSMB_BLOCK_METATILE + index];
        game->ram[MYSMB_BLOCK_REPLACE_FLAG + index] = 0U;
    }
}
