#include "game/player.h"
#include "game/frame_root.h"
#include "game/objects.h"
#include "game/fireball/fireball.h"
#include "game/area.h"
#include "game/world/world.h"
#include "game/oam/oam.h"

enum {
    MYSMB_PLAYER_X_SPEED = 0x0057U,
    MYSMB_PLAYER_PAGE = 0x006dU,
    MYSMB_PLAYER_X = 0x0086U,
    /* MoveObjectHorizontally uses SprObject_X_MoveForce,x.  For player
     * offset zero that is $0400; Player_X_MoveForce at $0705 belongs only
     * to ImposeFriction. */
    MYSMB_PLAYER_X_MOVE_FORCE = 0x0400U,
    MYSMB_PLAYER_X_FORCE = 0x0705U,
    MYSMB_JUMPSPRING_FORCE = 0x06dbU,
    MYSMB_JUMPSPRING_ANIM = 0x070eU,
    MYSMB_JUMPSPRING_TIMER = 0x0786U
};

enum {
    MYSMB_PLAYER_Y_SPEED = 0x009fU,
    MYSMB_PLAYER_Y_HIGH = 0x00b5U,
    MYSMB_PLAYER_Y = 0x00ceU,
    MYSMB_PLAYER_Y_DUMMY = 0x0416U,
    MYSMB_PLAYER_Y_FORCE = 0x0433U
};

enum {
    MYSMB_PLAYER_STATE = 0x001dU,
    MYSMB_PLAYER_X_SPEED_ABSOLUTE = 0x0700U,
    MYSMB_SWIMMING = 0x0704U,
    MYSMB_DIFF_HALT_JUMP = 0x0706U,
    MYSMB_JUMP_ORIGIN_HIGH = 0x0707U,
    MYSMB_JUMP_ORIGIN_Y = 0x0708U,
    MYSMB_VERTICAL_FORCE = 0x0709U,
    MYSMB_VERTICAL_FORCE_DOWN = 0x070aU,
    MYSMB_PLAYER_ANIM_TIMER_SET = 0x070cU,
    MYSMB_JUMP_SWIM_TIMER = 0x0782U,
    MYSMB_RUNNING_TIMER = 0x0783U
};

enum {
    MYSMB_TIMER_CONTROL = 0x0747U,
    MYSMB_PLAYER_CHANGE_SIZE = 0x070bU,
    MYSMB_PLAYER_ANIMATION = 0x070dU
};

enum { MYSMB_WHIRLPOOL = 0x047dU };

enum {
    MYSMB_LEFT_RIGHT_BUTTONS = 0x000cU,
    MYSMB_PLAYER_COLLISION_BITS = 0x0490U,
    MYSMB_PLAYER_X_ABSOLUTE = 0x0700U,
    MYSMB_FRICTION_HIGH = 0x0701U,
    MYSMB_FRICTION_LOW = 0x0702U,
    MYSMB_MAX_LEFT = 0x0450U,
    MYSMB_MAX_RIGHT = 0x0456U
};

enum {
    MYSMB_PLAYER_A_B_BUTTONS = 0x000aU,
    MYSMB_PLAYER_UP_DOWN_BUTTONS = 0x000bU,
    MYSMB_PLAYER_LEFT_RIGHT_BUTTONS = 0x000cU,
    MYSMB_PLAYER_CROUCHING = 0x0714U
};

enum { MYSMB_PREVIOUS_A_B_BUTTONS = 0x000dU };

/* ROM PJumpSnd and PipeDwnS write this before SoundEngine runs. */
enum {
    MYSMB_SQUARE2_SOUND_QUEUE = 0x00feU,
    MYSMB_SQUARE1_SOUND_QUEUE = 0x00ffU
};

enum {
    MYSMB_GAME_ENGINE_SUBROUTINE = 0x000eU,
    MYSMB_PLAYER_FACING = 0x0033U,
    MYSMB_PLAYER_ATTRIBUTES = 0x03c4U,
    MYSMB_SCREEN_LEFT_PAGE = 0x071aU,
    MYSMB_PLAYER_ENTRANCE = 0x0710U,
    MYSMB_DISABLE_COLLISION = 0x0716U,
    MYSMB_ALT_ENTRANCE = 0x0752U,
    MYSMB_JOYPAD_OVERRIDE = 0x0758U,
    MYSMB_HALF_WAY_PAGE = 0x075bU,
    MYSMB_AREA_TYPE = 0x074eU
};

enum {
    MYSMB_CLOUD_TYPE_OVERRIDE = 0x0743U,
    MYSMB_DEATH_MUSIC_LOADED = 0x0712U,
    MYSMB_TIMER_EXPIRED = 0x0759U,
    MYSMB_EVENT_MUSIC_QUEUE = 0x00fcU,
    MYSMB_EVENT_MUSIC_BUFFER = 0x07b1U
};

enum {
    MYSMB_FLAGPOLE_COLLISION_Y = 0x070fU,
    MYSMB_FLAGPOLE_SCORE = 0x010fU,
    MYSMB_FLAGPOLE_SOUND_QUEUE = 0x0713U
};

enum {
    MYSMB_GAME_TIMER_SETTING = 0x0715U,
    MYSMB_FETCH_NEW_GAME_TIMER = 0x0757U,
    MYSMB_STAR_INVINCIBLE_TIMER = 0x079fU,
    MYSMB_GAME_TIMER_DISPLAY = 0x07f8U
};

enum {
    MYSMB_PLAYER_X_SCROLL = 0x06ffU,
    MYSMB_PLATFORM_X_SCROLL = 0x03a1U,
    MYSMB_SCROLL_LOCK = 0x0723U,
    MYSMB_SCROLL_THIRTY_TWO = 0x073dU,
    MYSMB_SCREEN_LEFT_X = 0x071cU,
    MYSMB_SCREEN_RIGHT_PAGE = 0x071bU,
    MYSMB_SCREEN_RIGHT_X = 0x071dU,
    MYSMB_PLAYER_POS_FOR_SCROLL = 0x0755U,
    MYSMB_SCROLL_AMOUNT = 0x0775U,
    MYSMB_SIDE_COLLISION_TIMER = 0x0785U,
    MYSMB_CLIMB_SIDE_TIMER = 0x0789U,
    MYSMB_HORIZONTAL_SCROLL = 0x073fU,
    MYSMB_SCROLL_INTERVAL_TIMER = 0x0795U
};

enum { MYSMB_PLAYER_MOVING_DIRECTION = 0x0045U };

enum { MYSMB_PLAYER_SIZE = 0x0754U };
enum {
    MYSMB_PLAYER_RELATIVE_X = 0x03adU,
    MYSMB_PLAYER_RELATIVE_Y = 0x03b8U,
    MYSMB_PLAYER_SPRITE_ATTRIBUTES = 0x03c4U,
    MYSMB_PLAYER_OFFSCREEN_BITS = 0x03d0U,
    MYSMB_PLAYER_GFX_OFFSET = 0x06d5U,
    MYSMB_PLAYER_SPRITE_OFFSET = 0x06e4U,
    MYSMB_PLAYER_INJURY_TIMER = 0x079eU,
    MYSMB_PLAYER_ANIM_TIMER = 0x0781U,
    MYSMB_PLAYER_FRAME_COUNTER = 0x0009U
};
enum {
    /* Owner-local PRG offsets for PlayerGfxTblOffsets and
     * PlayerGraphicsTable.  These map CPU $ee07 and $ee17. */
    MYSMB_PLAYER_GFX_TABLE_OFFSETS = 0x6e07U,
    MYSMB_PLAYER_GRAPHICS_TABLE = 0x6e17U,
    MYSMB_PLAYER_GRAPHICS_TABLE_END = 0x6ee7U
};
enum { MYSMB_PLAYER_BOUND_BOX = 0x0499U, MYSMB_PLAYER_BOUNDING_BOX = 0x04acU };
enum { MYSMB_RUNNING_SPEED = 0x0703U };
enum {
    MYSMB_CHANGE_AREA_TIMER = 0x06deU,
    MYSMB_WARP_ZONE_CONTROL = 0x06d6U,
    MYSMB_DISABLE_SCREEN = 0x0774U,
    MYSMB_OPER_MODE_TASK = 0x0772U
};

/* ROM PlayerBGCollision selects BlockBufferAdderData before entering the
 * head, feet, and side probes.  The bases are normal big=$00, swimming
 * big=$07, and small or crouching=$0e.  The $0e selection is required for
 * small Mario's shorter collision body; using $07 makes his head probe the
 * swimming-big one and lets him pass through bricks, including hidden $5f
 * blocks. */
static mysmb_u8 mysmb_player_collision_base(const struct mysmb_game *game)
{
    if (game->ram[MYSMB_PLAYER_CROUCHING] != 0U ||
        game->ram[MYSMB_PLAYER_SIZE] != 0U) return 0x0eU;
    return game->ram[MYSMB_SWIMMING] != 0U ? 7U : 0U;
}

/* ROM $BF09-$BF0E MovePlayerHorizontally. The blocked path returns the
 * animation control unchanged; the fallthrough shares MoveObjectHorizontally. */
mysmb_u8 mysmb_player_move_horizontally(struct mysmb_game *game)
{
    if (game->ram[MYSMB_JUMPSPRING_ANIM] != 0U)
        return game->ram[MYSMB_JUMPSPRING_ANIM];
    return mysmb_world_move_spr_object_horizontally(game, 0U);
}

/* Translation of ROM ImposeGravity for player offset zero. */
void mysmb_player_impose_gravity(struct mysmb_game *game, mysmb_u8 downward,
                                 mysmb_u8 upward, mysmb_u8 maximum,
                                 mysmb_u8 apply_upward)
{
    mysmb_u8 old_value;
    mysmb_u8 carry_dummy;
    mysmb_u8 carry_y;
    mysmb_u8 page_delta;
    mysmb_u8 lower_limit;
    mysmb_u8 borrow;
    mysmb_u16 y_sum;

    old_value = game->ram[MYSMB_PLAYER_Y_DUMMY];
    game->ram[MYSMB_PLAYER_Y_DUMMY] =
        (mysmb_u8)(old_value + game->ram[MYSMB_PLAYER_Y_FORCE]);
    carry_dummy = game->ram[MYSMB_PLAYER_Y_DUMMY] < old_value ? 1U : 0U;
    page_delta = game->ram[MYSMB_PLAYER_Y_SPEED] >= 0x80U ? 0xffU : 0U;
    old_value = game->ram[MYSMB_PLAYER_Y];
    /* The carry into ADC Player_Y_Position comes from the fractional
     * addition above.  Comparing the byte result with old_value loses that
     * carry when the signed speed and fractional carry return to old_value
     * (for example $6f + $ff + 1 = $16f). */
    y_sum = (mysmb_u16)old_value + game->ram[MYSMB_PLAYER_Y_SPEED] +
        carry_dummy;
    game->ram[MYSMB_PLAYER_Y] = (mysmb_u8)y_sum;
    carry_y = y_sum > 0xffU ? 1U : 0U;
    game->ram[MYSMB_PLAYER_Y_HIGH] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_Y_HIGH] + page_delta + carry_y);
    old_value = game->ram[MYSMB_PLAYER_Y_FORCE];
    game->ram[MYSMB_PLAYER_Y_FORCE] = (mysmb_u8)(old_value + downward);
    carry_dummy = game->ram[MYSMB_PLAYER_Y_FORCE] < old_value ? 1U : 0U;
    game->ram[MYSMB_PLAYER_Y_SPEED] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_Y_SPEED] + carry_dummy);
    if (game->ram[MYSMB_PLAYER_Y_SPEED] < 0x80U &&
        game->ram[MYSMB_PLAYER_Y_SPEED] >= maximum &&
        game->ram[MYSMB_PLAYER_Y_FORCE] >= 0x80U) {
        game->ram[MYSMB_PLAYER_Y_SPEED] = maximum;
        game->ram[MYSMB_PLAYER_Y_FORCE] = 0U;
    }
    if (apply_upward == 0U) {
        return;
    }
    lower_limit = (mysmb_u8)(0U - maximum);
    old_value = game->ram[MYSMB_PLAYER_Y_FORCE];
    game->ram[MYSMB_PLAYER_Y_FORCE] = (mysmb_u8)(old_value - upward);
    borrow = old_value < upward ? 1U : 0U;
    game->ram[MYSMB_PLAYER_Y_SPEED] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_Y_SPEED] - borrow);
    if (game->ram[MYSMB_PLAYER_Y_SPEED] >= 0x80U &&
        game->ram[MYSMB_PLAYER_Y_SPEED] < lower_limit &&
        game->ram[MYSMB_PLAYER_Y_FORCE] < 0x80U) {
        game->ram[MYSMB_PLAYER_Y_SPEED] = lower_limit;
        game->ram[MYSMB_PLAYER_Y_FORCE] = 0xffU;
    }
}

/* Translation of PlayerPhysicsSub ProcJumping/InitJS, with source force data. */
void mysmb_player_start_jump(struct mysmb_game *game, mysmb_u8 whirlpool)
{
    static const mysmb_u8 jump_force[7] = { 0x20U, 0x20U, 0x1eU, 0x28U,
                                             0x28U, 0x0dU, 0x04U };
    static const mysmb_u8 fall_force[7] = { 0x70U, 0x70U, 0x60U, 0x90U,
                                             0x90U, 0x0aU, 0x09U };
    static const mysmb_u8 initial_force[7] = { 0U, 0U, 0U, 0U, 0U, 0x80U, 0U };
    static const mysmb_u8 initial_speed[7] = { 0xfcU, 0xfcU, 0xfcU, 0xfbU,
                                                0xfbU, 0xfeU, 0xffU };
    mysmb_u8 index;

    index = 0U;
    if (game->ram[MYSMB_PLAYER_X_SPEED_ABSOLUTE] >= 9U) index++;
    if (game->ram[MYSMB_PLAYER_X_SPEED_ABSOLUTE] >= 0x10U) index++;
    if (game->ram[MYSMB_PLAYER_X_SPEED_ABSOLUTE] >= 0x19U) index++;
    if (game->ram[MYSMB_PLAYER_X_SPEED_ABSOLUTE] >= 0x1cU) index++;
    if (game->ram[MYSMB_SWIMMING] != 0U) {
        index = whirlpool != 0U ? 6U : 5U;
    }
    game->ram[MYSMB_JUMP_SWIM_TIMER] = 0x20U;
    game->ram[MYSMB_PLAYER_Y_DUMMY] = 0U;
    game->ram[MYSMB_PLAYER_Y_FORCE] = 0U;
    game->ram[MYSMB_JUMP_ORIGIN_HIGH] = game->ram[MYSMB_PLAYER_Y_HIGH];
    game->ram[MYSMB_JUMP_ORIGIN_Y] = game->ram[MYSMB_PLAYER_Y];
    game->ram[MYSMB_PLAYER_STATE] = 1U;
    game->ram[MYSMB_DIFF_HALT_JUMP] = 1U;
    game->ram[MYSMB_VERTICAL_FORCE] = jump_force[index];
    game->ram[MYSMB_VERTICAL_FORCE_DOWN] = fall_force[index];
    game->ram[MYSMB_PLAYER_Y_FORCE] = initial_force[index];
    game->ram[MYSMB_PLAYER_Y_SPEED] = initial_speed[index];
    /* ROM PJumpSnd: PlayerSize=$01 is small Mario; dry jumps select small/big.
     * SoundEngine consumes the queue later in this same frame. */
    if (game->ram[MYSMB_SWIMMING] != 0U) {
        game->ram[MYSMB_SQUARE1_SOUND_QUEUE] = 0x04U;
        /* GetYPhy: the swim sound remains queued even when the surface
         * gate clears vertical speed before X_Physics. */
        if (game->ram[MYSMB_PLAYER_Y] < 0x14U)
            game->ram[MYSMB_PLAYER_Y_SPEED] = 0U;
    } else {
        game->ram[MYSMB_SQUARE1_SOUND_QUEUE] =
            game->ram[MYSMB_PLAYER_SIZE] != 0U ? 0x80U : 0x01U;
    }
}

/* Translation of ROM ImposeFriction. */
void mysmb_player_impose_friction(struct mysmb_game *game)
{
    mysmb_u8 buttons;
    mysmb_u8 old_force;
    mysmb_u8 carry;
    mysmb_u8 speed;
    mysmb_u8 use_additive;
    buttons = (mysmb_u8)(game->ram[MYSMB_LEFT_RIGHT_BUTTONS] &
                         game->ram[MYSMB_PLAYER_COLLISION_BITS]);
    speed = game->ram[MYSMB_PLAYER_X_SPEED];
    if (buttons == 0U && speed == 0U) {
        game->ram[MYSMB_PLAYER_X_ABSOLUTE] = 0U;
        return;
    }
    /* ROM ImposeFriction first separates released directions by the sign of
     * Player_X_Speed. Rightward motion enters RghtFrict (subtract), while
     * leftward motion enters LeftFrict (add), so either released direction
     * decelerates toward zero. Only a held direction selects acceleration. */
    if (buttons == 0U) {
        use_additive = speed >= 0x80U ? 1U : 0U;
    }
    else {
        /* LSR in the ROM gives Right precedence if both bits are present. */
        use_additive = (buttons & MYSMB_BUTTON_RIGHT) != 0U ? 1U : 0U;
    }
    if (use_additive != 0U) {
        old_force = game->ram[MYSMB_PLAYER_X_FORCE];
        game->ram[MYSMB_PLAYER_X_FORCE] =
            (mysmb_u8)(old_force + game->ram[MYSMB_FRICTION_LOW]);
        carry = game->ram[MYSMB_PLAYER_X_FORCE] < old_force ? 1U : 0U;
        speed = (mysmb_u8)(speed + game->ram[MYSMB_FRICTION_HIGH] + carry);
        /* CMP/BMI observes bit 7 of the wrapped subtraction, not an
         * overflow-corrected signed comparison. The clamp jumps directly
         * to SetAbsSpd, bypassing XSpdSign. */
        if (((mysmb_u8)(speed - game->ram[MYSMB_MAX_RIGHT]) & 0x80U) == 0U) {
            speed = game->ram[MYSMB_MAX_RIGHT];
            game->ram[MYSMB_PLAYER_X_SPEED] = speed;
            game->ram[MYSMB_PLAYER_X_ABSOLUTE] = speed;
            return;
        }
    }
    else {
        old_force = game->ram[MYSMB_PLAYER_X_FORCE];
        game->ram[MYSMB_PLAYER_X_FORCE] =
            (mysmb_u8)(old_force - game->ram[MYSMB_FRICTION_LOW]);
        carry = old_force < game->ram[MYSMB_FRICTION_LOW] ? 1U : 0U;
        speed = (mysmb_u8)(speed - game->ram[MYSMB_FRICTION_HIGH] - carry);
        if (((mysmb_u8)(speed - game->ram[MYSMB_MAX_LEFT]) & 0x80U) != 0U) {
            speed = game->ram[MYSMB_MAX_LEFT];
        }
    }
    game->ram[MYSMB_PLAYER_X_SPEED] = speed;
    game->ram[MYSMB_PLAYER_X_ABSOLUTE] = speed >= 0x80U ?
        (mysmb_u8)(0U - speed) : speed;
}

/* Translation of PlayerPhysicsSub's Player_State == $03 branch. */
void mysmb_player_configure_climb(struct mysmb_game *game)
{
    static const mysmb_u8 move_force[3] = { 0U, 0x20U, 0xffU };
    static const mysmb_u8 speed[3] = { 0U, 0xffU, 1U };
    mysmb_u8 index;
    mysmb_u8 vertical;

    index = 0U;
    vertical = (mysmb_u8)(game->ram[MYSMB_PLAYER_UP_DOWN_BUTTONS] &
                          game->ram[MYSMB_PLAYER_COLLISION_BITS]);
    if (vertical != 0U) {
        index = (vertical & MYSMB_BUTTON_UP) != 0U ? 1U : 2U;
    }
    game->ram[MYSMB_PLAYER_Y_FORCE] = move_force[index];
    game->ram[MYSMB_PLAYER_Y_SPEED] = speed[index];
    /* BMI retains eight for negative speed; LSR selects four otherwise. */
    game->ram[MYSMB_PLAYER_ANIM_TIMER_SET] = speed[index] >= 0x80U ? 8U : 4U;
}

/* ClimbAdderLow/High and ClimbingSub, ROM $b3c7-$b423.
 * Timer decrement remains in the shared timer
 * owner; this routine only observes and reloads ClimbSideTimer. */
void mysmb_player_climb(struct mysmb_game *game)
{
    static const mysmb_u8 x_low[4] = { 0x0eU, 0x04U, 0xfcU, 0xf2U };
    static const mysmb_u8 x_high[4] = { 0U, 0U, 0xffU, 0xffU };
    mysmb_u8 old_value;
    mysmb_u8 carry_dummy;
    mysmb_u8 carry_y;
    mysmb_u8 page_delta;
    mysmb_u8 index;
    mysmb_u8 facing;
    mysmb_u8 allowed_direction;
    mysmb_u16 y_sum;

    old_value = game->ram[MYSMB_PLAYER_Y_DUMMY];
    game->ram[MYSMB_PLAYER_Y_DUMMY] =
        (mysmb_u8)(old_value + game->ram[MYSMB_PLAYER_Y_FORCE]);
    carry_dummy = game->ram[MYSMB_PLAYER_Y_DUMMY] < old_value ? 1U : 0U;
    page_delta = game->ram[MYSMB_PLAYER_Y_SPEED] >= 0x80U ? 0xffU : 0U;
    old_value = game->ram[MYSMB_PLAYER_Y];
    y_sum = (mysmb_u16)old_value + game->ram[MYSMB_PLAYER_Y_SPEED] +
        carry_dummy;
    game->ram[MYSMB_PLAYER_Y] = (mysmb_u8)y_sum;
    carry_y = y_sum > 0xffU ? 1U : 0U;
    game->ram[MYSMB_PLAYER_Y_HIGH] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_Y_HIGH] + page_delta + carry_y);
    allowed_direction = (mysmb_u8)(game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS] &
                                   game->ram[MYSMB_PLAYER_COLLISION_BITS]);
    if (allowed_direction == 0U) {
        game->ram[MYSMB_CLIMB_SIDE_TIMER] = 0U;
        return;
    }
    if (game->ram[MYSMB_CLIMB_SIDE_TIMER] != 0U) return;
    game->ram[MYSMB_CLIMB_SIDE_TIMER] = 0x18U;
    facing = game->ram[MYSMB_PLAYER_FACING];
    /* LSR tests collision-filtered right, then DEY tests facing == 1.
     * Direction and facing are independent selectors for all four entries. */
    index = (allowed_direction & MYSMB_BUTTON_RIGHT) != 0U ? 0U : 2U;
    if (facing != 1U) ++index;
    old_value = game->ram[MYSMB_PLAYER_X];
    game->ram[MYSMB_PLAYER_X] = (mysmb_u8)(old_value + x_low[index]);
    carry_y = game->ram[MYSMB_PLAYER_X] < old_value ? 1U : 0U;
    game->ram[MYSMB_PLAYER_PAGE] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_PAGE] + x_high[index] + carry_y);
    game->ram[MYSMB_PLAYER_FACING] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS] ^ 3U);
}

/* Translation of the X_Physics parameter route in ROM $b51c-$b58b.
 * Player animation timing is owned by GetPlayerAnimSpeed. */
void mysmb_player_configure_horizontal(struct mysmb_game *game)
{
    static const mysmb_u8 max_left[3] = { 0xd8U, 0xe8U, 0xf0U };
    static const mysmb_u8 max_right[4] = { 0x28U, 0x18U, 0x10U, 0x0cU };
    static const mysmb_u8 friction[3] = { 0xe4U, 0x98U, 0xd0U };
    mysmb_u8 speed_index;
    mysmb_u8 friction_index;
    mysmb_u8 friction_value;
    mysmb_u8 check_fast_friction;

    speed_index = 0U;
    friction_index = 0U;
    check_fast_friction = 0U;
    if (game->ram[MYSMB_PLAYER_STATE] == 0U) {
        speed_index = 1U;
        if (game->ram[MYSMB_AREA_TYPE] != 0U) {
            speed_index = 0U;
            if (game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS] ==
                game->ram[MYSMB_PLAYER_MOVING_DIRECTION]) {
                if ((game->ram[MYSMB_PLAYER_A_B_BUTTONS] & MYSMB_BUTTON_B) != 0U) {
                    game->ram[MYSMB_RUNNING_TIMER] = 0x0aU;
                    goto configure_limits;
                }
                if (game->ram[MYSMB_RUNNING_TIMER] != 0U) {
                    goto configure_limits;
                }
            }
        }
        speed_index++;
        friction_index++;
        check_fast_friction = 1U;
    }
    else if (game->ram[MYSMB_PLAYER_X_SPEED_ABSOLUTE] < 0x19U) {
        speed_index++;
        friction_index++;
        check_fast_friction = 1U;
    }
    /* X_Physics reaches FastXSp only through ChkRFast.  An airborne player
     * already at $19 or faster branches directly to GetXPhy and retains
     * FrictionData[0], even when its absolute speed is at least $21. */
    if (check_fast_friction != 0U &&
        (game->ram[MYSMB_RUNNING_SPEED] != 0U ||
         game->ram[MYSMB_PLAYER_X_SPEED_ABSOLUTE] >= 0x21U)) {
        friction_index++;
    }
configure_limits:
    game->ram[MYSMB_MAX_LEFT] = max_left[speed_index];
    if (game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] == 7U) speed_index = 3U;
    game->ram[MYSMB_MAX_RIGHT] = max_right[speed_index];
    friction_value = friction[friction_index];
    game->ram[MYSMB_FRICTION_LOW] = friction_value;
    game->ram[MYSMB_FRICTION_HIGH] = 0U;
    if (game->ram[MYSMB_PLAYER_FACING] !=
        game->ram[MYSMB_PLAYER_MOVING_DIRECTION]) {
        game->ram[MYSMB_FRICTION_HIGH] = (mysmb_u8)(friction_value >> 7U);
        game->ram[MYSMB_FRICTION_LOW] = (mysmb_u8)(friction_value << 1U);
    }
}

/* Translation of GetPlayerAnimSpeed.  The caller supplies SavedJoypadBits
 * before the original routine partitions controller state. */
void mysmb_player_update_animation_speed(struct mysmb_game *game,
                                         mysmb_u8 buttons)
{
    static const mysmb_u8 timer[3] = { 2U, 4U, 7U };
    mysmb_u8 index;
    mysmb_u8 speed;

    speed = game->ram[MYSMB_PLAYER_X_SPEED_ABSOLUTE];
    index = 0U;
    if (speed >= 0x1cU) {
        game->ram[MYSMB_RUNNING_SPEED] = speed;
        game->ram[MYSMB_PLAYER_ANIM_TIMER_SET] = timer[index];
        return;
    }
    index = 1U;
    if (speed < 0x0eU) index = 2U;
    if ((buttons & 0x7fU) != 0U) {
        if ((buttons & (MYSMB_BUTTON_LEFT | MYSMB_BUTTON_RIGHT)) ==
            game->ram[MYSMB_PLAYER_MOVING_DIRECTION]) {
            game->ram[MYSMB_RUNNING_SPEED] = 0U;
        }
        else if (speed < 0x0bU) {
            game->ram[MYSMB_PLAYER_MOVING_DIRECTION] =
                game->ram[MYSMB_PLAYER_FACING];
            game->ram[MYSMB_PLAYER_X_SPEED] = 0U;
            game->ram[MYSMB_PLAYER_X_FORCE] = 0U;
        }
    }
    game->ram[MYSMB_PLAYER_ANIM_TIMER_SET] = timer[index];
}

/* Existing PlayerPhysicsSub child extracted without certifying interiors.
 * Its source-order table/branch audit belongs to T33 S3. */
void mysmb_player_physics_sub(struct mysmb_game *game)
{
    mysmb_u8 a_b;
    a_b = game->ram[MYSMB_PLAYER_A_B_BUTTONS];
    if (game->ram[MYSMB_PLAYER_STATE] == 3U) {
        mysmb_player_configure_climb(game);
        return;
    }
    if (game->ram[MYSMB_JUMPSPRING_ANIM] == 0U &&
        (a_b & MYSMB_BUTTON_A) != 0U &&
        (game->ram[MYSMB_PREVIOUS_A_B_BUTTONS] & MYSMB_BUTTON_A) == 0U) {
        if (game->ram[MYSMB_PLAYER_STATE] == 0U ||
            (game->ram[MYSMB_SWIMMING] != 0U &&
             (game->ram[MYSMB_JUMP_SWIM_TIMER] != 0U ||
              game->ram[MYSMB_PLAYER_Y_SPEED] < 0x80U))) {
            mysmb_player_start_jump(game, game->ram[MYSMB_WHIRLPOOL]);
        }
    }
    mysmb_player_configure_horizontal(game);
}

/* Existing MovePlayerVertically child; original world movement keeps custody. */
void mysmb_player_move_vertically(struct mysmb_game *game)
{
    mysmb_player_impose_gravity(game, game->ram[MYSMB_VERTICAL_FORCE],
                                0U, 4U, 0U);
}

/* Existing common terrain child; algorithm proof remains terrain-owned. */
void mysmb_player_background_collision(struct mysmb_game *game)
{
    mysmb_u8 collision_result;
    /* PlayerBGCollision is disabled for the control/pipe routines below 4,
     * player death (0x0b), and explicit collision suppression. */
    if (game->ram[MYSMB_DISABLE_COLLISION] == 0U &&
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] >= 4U &&
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 0x0bU) {
        /* PlayerBGCollision establishes falling/swimming before its
         * on-screen guard, so an eligible player leaving the visible
         * vertical range cannot retain the ground state. */
        if (game->ram[MYSMB_SWIMMING] != 0U) {
            game->ram[MYSMB_PLAYER_STATE] = 1U;
        }
        else if (game->ram[MYSMB_PLAYER_STATE] == 0U) {
            game->ram[MYSMB_PLAYER_STATE] = 2U;
        }
        if (game->ram[MYSMB_PLAYER_Y_HIGH] == 1U) {
                game->ram[MYSMB_PLAYER_COLLISION_BITS] = 0xffU;
                if (game->ram[MYSMB_PLAYER_Y] < 0xcfU) {
                    collision_result = mysmb_player_check_head(game);
                    if (collision_result != 2U) {
                        collision_result = mysmb_player_check_feet(game);
                        if (collision_result != 2U && collision_result != MYSMB_PLAYER_FEET_TERMINAL_IMPEDE) {
                            (void)mysmb_player_check_sides(game);
                        }
                    }
                }
            }
    }
}


/* Snapshot only translated RAM state; no platform state participates. */
void mysmb_player_checkpoint(const struct mysmb_game *game,
                             struct mysmb_player_checkpoint *checkpoint)
{
    if (checkpoint == 0) return;
    checkpoint->frame_number = game->frame_number;
    checkpoint->engine_subroutine = game->ram[MYSMB_GAME_ENGINE_SUBROUTINE];
    checkpoint->state = game->ram[MYSMB_PLAYER_STATE];
    checkpoint->page = game->ram[MYSMB_PLAYER_PAGE];
    checkpoint->x = game->ram[MYSMB_PLAYER_X];
    checkpoint->y_high = game->ram[MYSMB_PLAYER_Y_HIGH];
    checkpoint->y = game->ram[MYSMB_PLAYER_Y];
    checkpoint->x_speed = game->ram[MYSMB_PLAYER_X_SPEED];
    checkpoint->y_speed = game->ram[MYSMB_PLAYER_Y_SPEED];
    checkpoint->x_force = game->ram[MYSMB_PLAYER_X_FORCE];
    checkpoint->y_force = game->ram[MYSMB_PLAYER_Y_FORCE];
    checkpoint->screen_left_page = game->ram[MYSMB_SCREEN_LEFT_PAGE];
    checkpoint->screen_left_x = game->ram[MYSMB_SCREEN_LEFT_X];
}

/* ROM CheckForCoinMTiles -> HandleCoinMetatile.  Coins emitted from bumped
 * blocks use their own JumpCoin sound producer; this helper is only for the
 * player head, foot, and side collision paths that reached CheckForCoinMTiles. */
static void mysmb_player_collect_metatile_coin(struct mysmb_game *game,
                                               mysmb_u8 block_low,
                                               mysmb_u8 block_row)
{
    game->ram[MYSMB_SQUARE2_SOUND_QUEUE] = 1U;
    mysmb_objects_collect_coin(game, block_low, block_row);
}

/* Translation of HandleClimbing through PutPlayerOnVine.  The caller passes
 * the collision helper's $04 and $06 values as terrain metadata. */
static mysmb_u8 mysmb_player_handle_climbing(struct mysmb_game *game,
                                              const struct mysmb_player_terrain *terrain)
{
    static const mysmb_u8 x_adder[2] = { 0xf9U, 0x07U };
    static const mysmb_u8 page_adder[2] = { 0xffU, 0U };
    static const mysmb_u8 flagpole_y[5] = { 0x18U, 0x22U, 0x50U, 0x68U, 0x90U };
    mysmb_u8 facing_index;
    mysmb_u8 relative_x;
    mysmb_u8 score_index;
    mysmb_u8 enemy_slot;

    if (terrain->contact_low_nibble < 6U ||
        terrain->contact_low_nibble >= 0x0aU) {
        return 0U;
    }
    if (terrain->metatile == 0x24U || terrain->metatile == 0x25U) {
        if (game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] == 5U) goto put_player_on_vine;
        game->ram[MYSMB_PLAYER_FACING] = MYSMB_BUTTON_RIGHT;
        game->ram[MYSMB_SCROLL_LOCK]++;
        if (game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 4U) {
            /* ROM KillEnemies(BulletBill_CannonVar), slots 0 through 4. */
            for (enemy_slot = 0U; enemy_slot < 5U; ++enemy_slot) {
                if (game->ram[0x0016U + enemy_slot] == 12U)
                    game->ram[0x000fU + enemy_slot] = 0U;
            }
            game->ram[MYSMB_EVENT_MUSIC_QUEUE] = 0x80U;
            game->ram[MYSMB_FLAGPOLE_SOUND_QUEUE] = 0x40U;
            game->ram[MYSMB_FLAGPOLE_COLLISION_Y] = game->ram[MYSMB_PLAYER_Y];
            score_index = 4U;
            while (score_index != 0U && game->ram[MYSMB_PLAYER_Y] < flagpole_y[score_index])
                --score_index;
            game->ram[MYSMB_FLAGPOLE_SCORE] = score_index;
        }
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 4U;
    }
    else if (terrain->metatile == 0x26U &&
             game->ram[MYSMB_PLAYER_Y] < 0x20U) {
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 1U;
    }
    else if (terrain->metatile != 0x26U) {
        return 0U;
    }
put_player_on_vine:
    game->ram[MYSMB_PLAYER_STATE] = 3U;
    game->ram[MYSMB_PLAYER_X_SPEED] = 0U;
    game->ram[MYSMB_PLAYER_X_FORCE] = 0U;
    relative_x = (mysmb_u8)(game->ram[MYSMB_PLAYER_X] -
                            game->ram[MYSMB_SCREEN_LEFT_X]);
    if (relative_x < 0x10U) {
        game->ram[MYSMB_PLAYER_FACING] = MYSMB_BUTTON_LEFT;
    }
    facing_index = game->ram[MYSMB_PLAYER_FACING] == MYSMB_BUTTON_RIGHT ? 0U : 1U;
    game->ram[MYSMB_PLAYER_X] =
        (mysmb_u8)((terrain->block_address_low << 4U) + x_adder[facing_index]);
    if (terrain->block_address_low == 0U) {
        game->ram[MYSMB_PLAYER_PAGE] =
            (mysmb_u8)(game->ram[MYSMB_SCREEN_RIGHT_PAGE] + page_adder[facing_index]);
    }
    return 1U;
}

/* Translation of HandlePipeEntry, excluding the separate warp destination
 * tables owned by the area-transition route. */
mysmb_u8 mysmb_player_handle_vertical_pipe(struct mysmb_game *game,
                                           mysmb_u8 left, mysmb_u8 right)
{
    static const mysmb_u8 warp_zone_numbers[12] = {
        4U, 3U, 2U, 0U, 0x24U, 5U, 0x24U, 0U, 8U, 7U, 6U, 0U
    };
    mysmb_u8 warp_index;

    if ((game->ram[MYSMB_PLAYER_UP_DOWN_BUTTONS] & MYSMB_BUTTON_DOWN) == 0U ||
        left != 0x10U || right != 0x11U) return 0U;
    game->ram[MYSMB_CHANGE_AREA_TIMER] = 0x30U;
    game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 3U;
    game->ram[MYSMB_SQUARE1_SOUND_QUEUE] = 0x10U;
    game->ram[MYSMB_PLAYER_ATTRIBUTES] = 0x20U;
    if (game->ram[MYSMB_WARP_ZONE_CONTROL] != 0U) {
        warp_index = (mysmb_u8)((game->ram[MYSMB_WARP_ZONE_CONTROL] & 3U) << 2U);
        if (game->ram[MYSMB_PLAYER_X] >= 0x60U) warp_index++;
        if (game->ram[MYSMB_PLAYER_X] >= 0xa0U) warp_index++;
        game->ram[0x075fU] = (mysmb_u8)(warp_zone_numbers[warp_index] - 1U);
        game->ram[0x0751U] = 0U;
        game->ram[0x0760U] = 0U;
        game->ram[0x075cU] = 0U;
        game->ram[MYSMB_ALT_ENTRANCE] = 0U;
        game->ram[0x075dU]++;
        game->ram[0x0757U]++;
        game->ram[0x00fcU] = 0U;
    }
    return 1U;
}

/* Translation of ROM $dc64-$dd5a PlayerBGCollision's DoFootCheck through LandPlyr.
 * The original selects an adder from size/crouch/swim state, but both feet
 * ultimately use X+3/X+12 and Y+32.  It reads left first for the landing
 * decision after sampling both positions. */
mysmb_u8 mysmb_player_check_feet(struct mysmb_game *game)
{
    static const mysmb_u8 x_adder[28] = {
        8U, 3U, 0x0cU, 2U, 2U, 0x0dU, 0x0dU, 8U, 3U, 0x0cU, 2U,
        2U, 0x0dU, 0x0dU, 8U, 3U, 0x0cU, 2U, 2U, 0x0dU, 0x0dU, 8U,
        0U, 0x10U, 4U, 0x14U, 4U, 4U
    };
    static const mysmb_u8 y_adder[28] = {
        4U, 0x20U, 0x20U, 8U, 0x18U, 8U, 0x18U, 2U, 0x20U, 0x20U,
        8U, 0x18U, 8U, 0x18U, 0x12U, 0x20U, 0x20U, 0x18U, 0x18U,
        0x18U, 0x18U, 0x18U, 0x14U, 0x14U, 6U, 6U, 8U, 0x10U
    };
    struct mysmb_player_terrain left;
    struct mysmb_player_terrain right;
    mysmb_u8 have_left;
    mysmb_u8 have_right;
    mysmb_u8 base;

    if (game->ram[MYSMB_PLAYER_Y_HIGH] != 1U ||
        game->ram[MYSMB_PLAYER_Y] >= 0xcfU) {
        return 0U;
    }
    if (game->ram[MYSMB_PLAYER_STATE] == 0U) {
        game->ram[MYSMB_PLAYER_STATE] =
            game->ram[MYSMB_SWIMMING] != 0U ? 1U : 2U;
    }
    base = mysmb_player_collision_base(game);
    have_left = mysmb_world_query_player_block(game, x_adder[(mysmb_u8)(base + 1U)],
                                         y_adder[(mysmb_u8)(base + 1U)], 0U, &left);
    have_right = mysmb_world_query_player_block(game, x_adder[(mysmb_u8)(base + 2U)],
                                          y_adder[(mysmb_u8)(base + 2U)], 0U, &right);
    /* ChkFootMTile consumes the left sample when it is nonzero; it visits
     * the right sample only when the left is empty.  A climbable sample
     * hands off to the side route instead of becoming a landing surface. */
    if (have_left != 0U && (left.metatile == 0xc2U || left.metatile == 0xc3U)) {
        mysmb_player_collect_metatile_coin(game, left.block_address_low,
                                   left.block_row_offset);
        return 2U;
    }
    if (have_left != 0U && left.metatile != 0U) {
        if (mysmb_world_is_climbable(left.metatile) != 0U) return 0U;
        if (game->ram[MYSMB_PLAYER_Y_SPEED] >= 0x80U) return 0U;
        /* ChkInvisibleMTiles branches directly to DoPlayerSideCheck.  Hidden
         * coin and 1-up blocks are neither floor nor a landing correction. */
        if (left.metatile == 0x5fU || left.metatile == 0x60U) return 0U;
        /* ROM HandleAxeMetatile runs from the foot sample before ordinary
         * landing, then ErACM/RemoveCoin_Axe updates the shared VRAM list. */
        if (left.metatile == 0xc5U && game->ram[MYSMB_PLAYER_Y_SPEED] < 0x80U) {
            game->ram[0x0772U] = 0U;
            game->ram[0x0770U] = 2U;
            game->ram[MYSMB_PLAYER_X_SPEED] = 0x18U;
            mysmb_objects_remove_axe(game, left.block_address_low,
                                     left.block_row_offset);
            return 2U;
        }
        /* ChkFootMTile reaches InitSteP while JumpspringHandler owns the
         * animation; it resets only Player_State and must not land Mario. */
        if (game->ram[MYSMB_JUMPSPRING_ANIM] != 0U) {
            game->ram[MYSMB_PLAYER_STATE] = 0U;
            return 1U;
        }
        /* At contact nibble $05-$0f, ChkFootMTile calls ImpedePlayerMove
         * with Player_MovingDir instead of taking LandPlyr. */
        if (left.contact_low_nibble >= 5U) {
            mysmb_player_impede_move(game, game->ram[MYSMB_PLAYER_MOVING_DIRECTION]);
            /* ChkFootMTile JMPs to ImpedePlayerMove, which returns from
             * PlayerBGCollision.  Keep that terminal control transfer
             * distinct from an ordinary landed-foot result. */
            return MYSMB_PLAYER_FEET_TERMINAL_IMPEDE;
        }
        /* ChkForLandJumpSpring initializes the object-owned animation before
         * LandPlyr aligns Mario to the metatile boundary. */
        if ((left.metatile == 0x67U || left.metatile == 0x68U) &&
            left.contact_low_nibble < 5U) {
            game->ram[MYSMB_VERTICAL_FORCE] = 0x70U;
            game->ram[MYSMB_JUMPSPRING_FORCE] = 0xf9U;
            game->ram[MYSMB_JUMPSPRING_TIMER] = 3U;
            game->ram[MYSMB_JUMPSPRING_ANIM] = 1U;
        }
        if (mysmb_world_land_player_on_solid(game, left.metatile,
                                       left.contact_low_nibble) == 0U) {
            return 0U;
        }
        (void)mysmb_player_handle_vertical_pipe(game, left.metatile,
                                                have_right != 0U ? right.metatile : 0U);
        return 1U;
    }
    if (have_right != 0U && (right.metatile == 0xc2U || right.metatile == 0xc3U)) {
        mysmb_player_collect_metatile_coin(game, right.block_address_low,
                                   right.block_row_offset);
        return 2U;
    }
    if (have_right != 0U && right.metatile != 0U) {
        if (mysmb_world_is_climbable(right.metatile) != 0U) return 0U;
        if (game->ram[MYSMB_PLAYER_Y_SPEED] >= 0x80U) return 0U;
        if (right.metatile == 0x5fU || right.metatile == 0x60U) return 0U;
        if (game->ram[MYSMB_JUMPSPRING_ANIM] != 0U) {
            game->ram[MYSMB_PLAYER_STATE] = 0U;
            return 1U;
        }
        if (right.contact_low_nibble >= 5U) {
            mysmb_player_impede_move(game, game->ram[MYSMB_PLAYER_MOVING_DIRECTION]);
            /* ChkFootMTile JMPs to ImpedePlayerMove, which returns from
             * PlayerBGCollision.  Keep that terminal control transfer
             * distinct from an ordinary landed-foot result. */
            return MYSMB_PLAYER_FEET_TERMINAL_IMPEDE;
        }
        if ((right.metatile == 0x67U || right.metatile == 0x68U) &&
            right.contact_low_nibble < 5U) {
            game->ram[MYSMB_VERTICAL_FORCE] = 0x70U;
            game->ram[MYSMB_JUMPSPRING_FORCE] = 0xf9U;
            game->ram[MYSMB_JUMPSPRING_TIMER] = 3U;
            game->ram[MYSMB_JUMPSPRING_ANIM] = 1U;
        }
        return mysmb_world_land_player_on_solid(game, right.metatile,
                                          right.contact_low_nibble);
    }
    return 0U;
}

/* Translation of ROM $9131-$9196 Entrance_GameTimerSetup. */
void mysmb_player_initialize_entrance(struct mysmb_game *game)
{
    static const mysmb_u8 start_x[4] = { 0x28U, 0x18U, 0x38U, 0x28U };
    static const mysmb_u8 alternate_y[2] = { 0x08U, 0x00U };
    static const mysmb_u8 start_y[9] = { 0x00U, 0x20U, 0xb0U, 0x50U,
                                         0x00U, 0x00U, 0xb0U, 0xb0U, 0xf0U };
    /* The ninth source index is GameTimerData's dummy byte, immediately
     * following PlayerBGPriorityData in PRG. Alternate entrance two selects
     * it through X=$08 exactly as the 6502 does. */
    static const mysmb_u8 background_priority[9] = {
        0U, 0x20U, 0U, 0U, 0U, 0U, 0U, 0U, 0x20U
    };
    static const mysmb_u8 game_timer_data[4] = { 0x20U, 4U, 3U, 2U };
    mysmb_u8 alternate;
    mysmb_u8 entrance;
    mysmb_u8 bubble_slot;

    game->ram[MYSMB_PLAYER_PAGE] = game->ram[MYSMB_SCREEN_LEFT_PAGE];
    game->ram[MYSMB_VERTICAL_FORCE_DOWN] = 0x28U;
    game->ram[MYSMB_PLAYER_FACING] = 1U;
    game->ram[MYSMB_PLAYER_Y_HIGH] = 1U;
    game->ram[MYSMB_PLAYER_STATE] = 0U;
    game->ram[MYSMB_PLAYER_COLLISION_BITS]--;
    game->ram[MYSMB_HALF_WAY_PAGE] = 0U;
    game->ram[MYSMB_SWIMMING] = game->ram[MYSMB_AREA_TYPE] == 0U ? 1U : 0U;
    alternate = game->ram[MYSMB_ALT_ENTRANCE];
    entrance = game->ram[MYSMB_PLAYER_ENTRANCE];
    if (alternate > 1U) {
        entrance = alternate_y[(mysmb_u8)(alternate - 2U)];
    }
    game->ram[MYSMB_PLAYER_X] = start_x[alternate];
    game->ram[MYSMB_PLAYER_Y] = start_y[entrance];
    game->ram[MYSMB_PLAYER_ATTRIBUTES] = background_priority[entrance];
    /* ROM Entrance_GameTimerSetup calls GetPlayerColors even when the four
     * colors already match the committed palette. */
    (void)mysmb_area_queue_player_palette(game);
    if (game->ram[MYSMB_GAME_TIMER_SETTING] != 0U &&
        game->ram[MYSMB_FETCH_NEW_GAME_TIMER] != 0U) {
        game->ram[MYSMB_GAME_TIMER_DISPLAY] =
            game_timer_data[game->ram[MYSMB_GAME_TIMER_SETTING]];
        game->ram[MYSMB_GAME_TIMER_DISPLAY + 2U] = 1U;
        game->ram[MYSMB_GAME_TIMER_DISPLAY + 1U] = 0U;
        game->ram[MYSMB_FETCH_NEW_GAME_TIMER] = 0U;
        game->ram[MYSMB_STAR_INVINCIBLE_TIMER] = 0U;
    }
    if (game->ram[MYSMB_JOYPAD_OVERRIDE] != 0U) {
        game->ram[MYSMB_PLAYER_STATE] = 3U;
        mysmb_objects_start_entrance_vine(game);
        bubble_slot = 5U;
    }
    else bubble_slot = entrance;
    if (game->ram[MYSMB_AREA_TYPE] == 0U) {
        mysmb_fireball_setup_bubble(game, bubble_slot);
    }
    game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 7U;
}



/* Translation of ROM $df4b-$df7d ImpedePlayerMove. */
void mysmb_player_impede_move(struct mysmb_game *game, mysmb_u8 collision_side)
{
    mysmb_u8 speed;
    mysmb_u8 correction;
    mysmb_u8 page_delta;
    mysmb_u8 collision_mask;

    /* SideCheckLoop passes its physical counter in $00, while ChkFootMTile
     * passes Player_MovingDir.  Both source paths use the same values:
     * 1 selects the left correction and d0, 2 the right correction and d1.
     * A non-blocking approach still clears the selected input bit at ExIPM. */
    speed = game->ram[MYSMB_PLAYER_X_SPEED];
    if (collision_side == 1U) {
        collision_mask = 0xfeU;
        if (speed >= 0x80U) goto clear_collision_bit;
        correction = 0xffU;
    }
    else if (collision_side == 2U) {
        collision_mask = 0xfdU;
        if (speed != 0U && speed < 0x80U) goto clear_collision_bit;
        correction = 1U;
    }
    else {
        return;
    }
    game->ram[MYSMB_SIDE_COLLISION_TIMER] = 0x10U;
    game->ram[MYSMB_PLAYER_X_SPEED] = 0U;
    if (correction == 0xffU) {
        page_delta = game->ram[MYSMB_PLAYER_X] == 0U ? 0xffU : 0U;
    }
    else {
        page_delta = game->ram[MYSMB_PLAYER_X] == 0xffU ? 1U : 0U;
    }
    game->ram[MYSMB_PLAYER_X] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_X] + correction);
    game->ram[MYSMB_PLAYER_PAGE] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_PAGE] + page_delta);
clear_collision_bit:
    game->ram[MYSMB_PLAYER_COLLISION_BITS] &= collision_mask;
}

/* Translation of CheckSideMTiles.  Coins and jumpsprings have their own
 * object route, but they still consume this collision without a wall stop. */
static mysmb_u8 mysmb_player_handle_side_metatile(
    struct mysmb_game *game, const struct mysmb_player_terrain *terrain,
    mysmb_u8 collision_side)
{
    if (terrain->metatile == 0xc2U || terrain->metatile == 0xc3U) {
        mysmb_player_collect_metatile_coin(game, terrain->block_address_low,
                                   terrain->block_row_offset);
        return 1U;
    }
    if (terrain->metatile == 0x5fU || terrain->metatile == 0x60U) {
        return 1U;
    }
    if (mysmb_world_is_climbable(terrain->metatile) != 0U) {
        (void)mysmb_player_handle_climbing(game, terrain);
        return 1U;
    }
    if (terrain->metatile == 0x67U || terrain->metatile == 0x68U) {
        /* ChkJumpspringMetatiles reaches StopPlayerMove unless animation
         * has already claimed this metatile. */
        if (game->ram[MYSMB_JUMPSPRING_ANIM] != 0U) return 1U;
        mysmb_player_impede_move(game, collision_side);
        return 1U;
    }
    if ((terrain->metatile == 0x6cU || terrain->metatile == 0x1fU) &&
        game->ram[MYSMB_PLAYER_STATE] == 0U &&
        game->ram[MYSMB_PLAYER_FACING] == MYSMB_BUTTON_RIGHT) {
        /* PipeDwnS queues the sound only when Player_SprAttrib was clear. */
        if (game->ram[MYSMB_PLAYER_ATTRIBUTES] == 0U) {
            game->ram[MYSMB_SQUARE1_SOUND_QUEUE] = 0x10U;
        }
        game->ram[MYSMB_PLAYER_ATTRIBUTES] |= 0x20U;
        if ((game->ram[MYSMB_PLAYER_X] & 0x0fU) != 0U) {
            game->ram[MYSMB_CHANGE_AREA_TIMER] =
                game->ram[MYSMB_SCREEN_LEFT_PAGE] == 0U ? 0xa0U : 0x34U;
        }
        if (game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] == 8U) {
            game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 2U;
        }
        return 1U;
    }
    mysmb_player_impede_move(game, collision_side);
    return 1U;
}

/* Translation of ROM $dd5e-$de46 SideCheckLoop.  Each upper sample can
 * defer to the lower half, which prevents a thin vine or pipe cap from
 * producing a side collision on its own. */
mysmb_u8 mysmb_player_check_sides(struct mysmb_game *game)
{
    static const mysmb_u8 x_adder[28] = {
        8U, 3U, 0x0cU, 2U, 2U, 0x0dU, 0x0dU, 8U, 3U, 0x0cU, 2U,
        2U, 0x0dU, 0x0dU, 8U, 3U, 0x0cU, 2U, 2U, 0x0dU, 0x0dU, 8U,
        0U, 0x10U, 4U, 0x14U, 4U, 4U
    };
    static const mysmb_u8 y_adder[28] = {
        4U, 0x20U, 0x20U, 8U, 0x18U, 8U, 0x18U, 2U, 0x20U, 0x20U,
        8U, 0x18U, 8U, 0x18U, 0x12U, 0x20U, 0x20U, 0x18U, 0x18U,
        0x18U, 0x18U, 0x18U, 0x14U, 0x14U, 6U, 6U, 8U, 0x10U
    };
    struct mysmb_player_terrain terrain;
    mysmb_u8 index;
    mysmb_u8 base;

    if (game->ram[MYSMB_PLAYER_Y_HIGH] != 1U ||
        game->ram[MYSMB_PLAYER_Y] >= 0xd0U) {
        return 0U;
    }
    game->ram[MYSMB_PLAYER_COLLISION_BITS] = 0xffU;
    base = mysmb_player_collision_base(game);
    for (index = 0U; index < 2U; ++index) {
        mysmb_u8 top;

        top = (mysmb_u8)(base + 3U + index * 2U);
        if (game->ram[MYSMB_PLAYER_Y] >= 0xe4U) return 0U;
        if (game->ram[MYSMB_PLAYER_Y] >= 0x20U &&
            mysmb_world_query_player_block(game, x_adder[top], y_adder[top], 1U,
                                     &terrain) != 0U && terrain.metatile != 0U &&
            terrain.metatile != 0x1cU && terrain.metatile != 0x6bU &&
            mysmb_world_is_climbable(terrain.metatile) == 0U) {
            return mysmb_player_handle_side_metatile(game, &terrain, (mysmb_u8)(2U - index));
        }
        if (game->ram[MYSMB_PLAYER_Y] < 8U ||
            game->ram[MYSMB_PLAYER_Y] >= 0xd0U) return 0U;
        top++;
        if (mysmb_world_query_player_block(game, x_adder[top], y_adder[top], 1U,
                                     &terrain) != 0U && terrain.metatile != 0U) {
            return mysmb_player_handle_side_metatile(game, &terrain, (mysmb_u8)(2U - index));
        }
    }
    return 0U;
}

/* Translation of ROM $dcba-$dcf5 HeadChk through NYSpd.  Matched bumpable
 * blocks hand their original collision coordinates to the object owner. */
mysmb_u8 mysmb_player_check_head(struct mysmb_game *game)
{
    static const mysmb_u8 x_adder[28] = {
        8U, 3U, 0x0cU, 2U, 2U, 0x0dU, 0x0dU, 8U, 3U, 0x0cU, 2U,
        2U, 0x0dU, 0x0dU, 8U, 3U, 0x0cU, 2U, 2U, 0x0dU, 0x0dU, 8U,
        0U, 0x10U, 4U, 0x14U, 4U, 4U
    };
    static const mysmb_u8 y_adder[28] = {
        4U, 0x20U, 0x20U, 8U, 0x18U, 8U, 0x18U, 2U, 0x20U, 0x20U,
        8U, 0x18U, 8U, 0x18U, 0x12U, 0x20U, 0x20U, 0x18U, 0x18U,
        0x18U, 0x18U, 0x18U, 0x14U, 0x14U, 6U, 6U, 8U, 0x10U
    };
    static const mysmb_u8 upper_extent[2] = { 0x20U, 0x10U };
    static const mysmb_u8 solid_upper[4] = { 0x10U, 0x61U, 0x88U, 0xc4U };
    struct mysmb_player_terrain terrain;
    mysmb_u8 extent_index;
    mysmb_u8 group;
    mysmb_u8 base;

    if (game->ram[MYSMB_PLAYER_Y_HIGH] != 1U) return 0U;
    extent_index = game->ram[MYSMB_PLAYER_SIZE] != 0U ? 1U : 0U;
    if (game->ram[MYSMB_PLAYER_CROUCHING] != 0U) extent_index = 1U;
    if (game->ram[MYSMB_PLAYER_Y] < upper_extent[extent_index]) {
        return 0U;
    }
    base = mysmb_player_collision_base(game);
    if (mysmb_world_query_player_block(game, x_adder[base], y_adder[base],
                                 0U, &terrain) == 0U || terrain.metatile == 0U) {
        return 0U;
    }
    if (terrain.metatile == 0xc2U || terrain.metatile == 0xc3U) {
        mysmb_player_collect_metatile_coin(game, terrain.block_address_low,
                                   terrain.block_row_offset);
        return 2U;
    }
    if (game->ram[MYSMB_PLAYER_Y_SPEED] < 0x80U ||
        (game->ram[MYSMB_PLAYER_Y] & 0x0fU) < 4U) {
        return 0U;
    }
    group = (mysmb_u8)(terrain.metatile >> 6U);
    if (terrain.metatile >= solid_upper[group]) {
        /* SolidOrClimb suppresses only the climbing metatile bump sound. */
        if (terrain.metatile != 0x26U) {
            game->ram[MYSMB_SQUARE1_SOUND_QUEUE] = 0x02U;
        }
        game->ram[MYSMB_PLAYER_Y_SPEED] = 1U;
        return 1U;
    }
    /* ROM HeadChk tests AreaType before PlayerHeadCollision.  In water,
     * NYSpd consumes a non-solid head hit without changing the block. */
    if (game->ram[MYSMB_AREA_TYPE] == 0U) {
        game->ram[MYSMB_PLAYER_Y_SPEED] = 1U;
        return 1U;
    }
    if (game->ram[0x0784U] != 0U) {
        /* HeadChk takes NYSpd while a previous block is bouncing. */
        game->ram[MYSMB_PLAYER_Y_SPEED] = 1U;
        return 1U;
    }
    if (mysmb_objects_start_head_bump(game, terrain.metatile,
                                      terrain.block_address_low,
                                      terrain.block_row_offset) != 0U) {
        return 1U;
    }
    return 0U;
}
