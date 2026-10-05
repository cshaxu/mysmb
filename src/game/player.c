#include "game/player.h"
#include "game/player/terrain_children.h"
#include "core/frame_root.h"
#include "game/objects.h"
#include "game/fireball/fireball.h"
#include "core/area.h"
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
    game->ram[0U] = downward;
    game->ram[1U] = upward;
    game->ram[2U] = maximum;
    mysmb_world_impose_gravity(game, 0U, apply_upward);
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
    /* MoveOnVine stores its sign extension before the position ADCs. */
    game->ram[0U] = page_delta;
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
    mysmb_u8 friction_value;
    mysmb_u8 check_fast_friction;

    speed_index = 0U;
    game->ram[0U] = 0U;
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
        game->ram[0U]++;
        check_fast_friction = 1U;
    }
    else if (game->ram[MYSMB_PLAYER_X_SPEED_ABSOLUTE] < 0x19U) {
        speed_index++;
        game->ram[0U]++;
        check_fast_friction = 1U;
    }
    /* X_Physics reaches FastXSp only through ChkRFast.  An airborne player
     * already at $19 or faster branches directly to GetXPhy and retains
     * FrictionData[0], even when its absolute speed is at least $21. */
    if (check_fast_friction != 0U &&
        (game->ram[MYSMB_RUNNING_SPEED] != 0U ||
         game->ram[MYSMB_PLAYER_X_SPEED_ABSOLUTE] >= 0x21U)) {
        game->ram[0U]++;
    }
configure_limits:
    game->ram[MYSMB_MAX_LEFT] = max_left[speed_index];
    if (game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] == 7U) speed_index = 3U;
    game->ram[MYSMB_MAX_RIGHT] = max_right[speed_index];
    friction_value = friction[game->ram[0U]];
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

/* ROM $BF4D-$BF62 MovePlayerVertically / NoJSChk. */
void mysmb_player_move_vertically(struct mysmb_game *game)
{
    if (game->ram[0x0747U] == 0U && game->ram[0x070eU] != 0U) return;
    game->ram[0U] = game->ram[MYSMB_VERTICAL_FORCE];
    mysmb_world_impose_gravity_spr_object(game, 0U, game->ram[0U], 4U);
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
     * colors already match the committed palette. Its returned X is the
     * original VRAM buffer offset, used by the later SetupBubble call. */
    bubble_slot = game->ram[0x0300U];
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
    if (game->ram[MYSMB_AREA_TYPE] == 0U) {
        mysmb_fireball_setup_bubble(game, bubble_slot);
    }
    game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 7U;
}
