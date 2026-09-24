#include "game/player.h"
#include "game/objects.h"

enum {
    MYSMB_PLAYER_X_SPEED = 0x0057U,
    MYSMB_PLAYER_PAGE = 0x006dU,
    MYSMB_PLAYER_X = 0x0086U,
    MYSMB_PLAYER_X_FORCE = 0x0705U,
    MYSMB_JUMPSPRING_ANIM = 0x070eU
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
    MYSMB_HORIZONTAL_SCROLL = 0x073fU
};

enum { MYSMB_PLAYER_MOVING_DIRECTION = 0x0045U };

enum { MYSMB_PLAYER_SIZE = 0x0754U };
enum { MYSMB_PLAYER_BOUND_BOX = 0x0499U };
enum { MYSMB_RUNNING_SPEED = 0x0703U };
enum {
    MYSMB_CHANGE_AREA_TIMER = 0x06deU,
    MYSMB_WARP_ZONE_CONTROL = 0x06d6U,
    MYSMB_DISABLE_SCREEN = 0x0774U,
    MYSMB_OPER_MODE_TASK = 0x0772U
};

/* ROM BlockBufferAdderData and the player portion of the coordinate tables.
 * The three bases are normal big, swimming big, and small/crouching. */
static mysmb_u8 mysmb_player_collision_base(const struct mysmb_game *game)
{
    if (game->ram[MYSMB_PLAYER_CROUCHING] != 0U ||
        game->ram[MYSMB_PLAYER_SIZE] != 0U) {
        return 0x0eU;
    }
    return game->ram[MYSMB_SWIMMING] != 0U ? 7U : 0U;
}

/* Translation of ROM MovePlayerHorizontally/MoveObjectHorizontally.
 * X speed is signed 4.4 fixed point; the low nibble accumulates in X force. */
mysmb_u8 mysmb_player_move_horizontally(struct mysmb_game *game)
{
    mysmb_u8 speed;
    mysmb_u8 fraction;
    mysmb_u8 integer;
    mysmb_u8 carry_force;
    mysmb_u8 carry_x;
    mysmb_u8 old_force;
    mysmb_u8 old_x;
    mysmb_u8 page_delta;

    if (game->ram[MYSMB_JUMPSPRING_ANIM] != 0U) {
        return game->ram[MYSMB_JUMPSPRING_ANIM];
    }
    speed = game->ram[MYSMB_PLAYER_X_SPEED];
    fraction = (mysmb_u8)((speed & 0x0fU) << 4U);
    integer = (mysmb_u8)(speed >> 4U);
    if (integer >= 8U) {
        integer = (mysmb_u8)(integer | 0xf0U);
        page_delta = 0xffU;
    }
    else {
        page_delta = 0U;
    }
    old_force = game->ram[MYSMB_PLAYER_X_FORCE];
    game->ram[MYSMB_PLAYER_X_FORCE] = (mysmb_u8)(old_force + fraction);
    carry_force = game->ram[MYSMB_PLAYER_X_FORCE] < old_force ? 1U : 0U;
    old_x = game->ram[MYSMB_PLAYER_X];
    game->ram[MYSMB_PLAYER_X] = (mysmb_u8)(old_x + integer + carry_force);
    carry_x = game->ram[MYSMB_PLAYER_X] < old_x ? 1U : 0U;
    game->ram[MYSMB_PLAYER_PAGE] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_PAGE] + page_delta + carry_x);
    return (mysmb_u8)(integer + carry_force);
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

    old_value = game->ram[MYSMB_PLAYER_Y_DUMMY];
    game->ram[MYSMB_PLAYER_Y_DUMMY] =
        (mysmb_u8)(old_value + game->ram[MYSMB_PLAYER_Y_FORCE]);
    carry_dummy = game->ram[MYSMB_PLAYER_Y_DUMMY] < old_value ? 1U : 0U;
    page_delta = game->ram[MYSMB_PLAYER_Y_SPEED] >= 0x80U ? 0xffU : 0U;
    old_value = game->ram[MYSMB_PLAYER_Y];
    game->ram[MYSMB_PLAYER_Y] =
        (mysmb_u8)(old_value + game->ram[MYSMB_PLAYER_Y_SPEED] + carry_dummy);
    carry_y = game->ram[MYSMB_PLAYER_Y] < old_value ? 1U : 0U;
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
}

/* Translation of ROM ImposeFriction. */
void mysmb_player_impose_friction(struct mysmb_game *game)
{
    mysmb_u8 buttons;
    mysmb_u8 old_force;
    mysmb_u8 carry;
    mysmb_u8 speed;

    buttons = (mysmb_u8)(game->ram[MYSMB_LEFT_RIGHT_BUTTONS] &
                         game->ram[MYSMB_PLAYER_COLLISION_BITS]);
    speed = game->ram[MYSMB_PLAYER_X_SPEED];
    if (buttons == 0U && speed == 0U) {
        game->ram[MYSMB_PLAYER_X_ABSOLUTE] = 0U;
        return;
    }
    if (buttons != 0U && (buttons & MYSMB_BUTTON_RIGHT) != 0U) {
        old_force = game->ram[MYSMB_PLAYER_X_FORCE];
        game->ram[MYSMB_PLAYER_X_FORCE] =
            (mysmb_u8)(old_force + game->ram[MYSMB_FRICTION_LOW]);
        carry = game->ram[MYSMB_PLAYER_X_FORCE] < old_force ? 1U : 0U;
        speed = (mysmb_u8)(speed + game->ram[MYSMB_FRICTION_HIGH] + carry);
        if (speed < 0x80U && speed >= game->ram[MYSMB_MAX_RIGHT]) {
            speed = game->ram[MYSMB_MAX_RIGHT];
        }
    }
    else {
        old_force = game->ram[MYSMB_PLAYER_X_FORCE];
        game->ram[MYSMB_PLAYER_X_FORCE] =
            (mysmb_u8)(old_force - game->ram[MYSMB_FRICTION_LOW]);
        carry = old_force < game->ram[MYSMB_FRICTION_LOW] ? 1U : 0U;
        speed = (mysmb_u8)(speed - game->ram[MYSMB_FRICTION_HIGH] - carry);
        if (speed >= 0x80U && speed < game->ram[MYSMB_MAX_LEFT]) {
            speed = game->ram[MYSMB_MAX_LEFT];
        }
    }
    game->ram[MYSMB_PLAYER_X_SPEED] = speed;
    game->ram[MYSMB_PLAYER_X_ABSOLUTE] = speed >= 0x80U ?
        (mysmb_u8)(0U - speed) : speed;
}

/* Translation of PlayerCtrlRoutine's input partition and ground crouch gate. */
void mysmb_player_latch_input(struct mysmb_game *game, mysmb_u8 buttons)
{
    mysmb_u8 left_right;
    mysmb_u8 up_down;

    if (game->ram[MYSMB_AREA_TYPE] == 0U &&
        (game->ram[MYSMB_PLAYER_Y_HIGH] != 1U ||
         game->ram[MYSMB_PLAYER_Y] >= 0xd0U)) {
        buttons = 0U;
    }
    game->ram[MYSMB_PLAYER_A_B_BUTTONS] =
        (mysmb_u8)(buttons & (MYSMB_BUTTON_A | MYSMB_BUTTON_B));
    left_right = (mysmb_u8)(buttons & (MYSMB_BUTTON_LEFT | MYSMB_BUTTON_RIGHT));
    up_down = (mysmb_u8)(buttons & (MYSMB_BUTTON_UP | MYSMB_BUTTON_DOWN));
    if ((up_down & MYSMB_BUTTON_DOWN) != 0U &&
        game->ram[MYSMB_PLAYER_STATE] == 0U && left_right != 0U) {
        left_right = 0U;
        up_down = 0U;
    }
    game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS] = left_right;
    game->ram[MYSMB_PLAYER_UP_DOWN_BUTTONS] = up_down;
    game->ram[MYSMB_PLAYER_CROUCHING] =
        game->ram[MYSMB_PLAYER_SIZE] == 0U && game->ram[MYSMB_PLAYER_STATE] == 0U &&
        (up_down & MYSMB_BUTTON_DOWN) != 0U ? 4U : 0U;
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
    game->ram[MYSMB_PLAYER_ANIM_TIMER_SET] = speed[index] >= 0x80U ? 4U : 8U;
}

/* Translation of ClimbingSub.  Timer decrement remains in the shared timer
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

    old_value = game->ram[MYSMB_PLAYER_Y_DUMMY];
    game->ram[MYSMB_PLAYER_Y_DUMMY] =
        (mysmb_u8)(old_value + game->ram[MYSMB_PLAYER_Y_FORCE]);
    carry_dummy = game->ram[MYSMB_PLAYER_Y_DUMMY] < old_value ? 1U : 0U;
    page_delta = game->ram[MYSMB_PLAYER_Y_SPEED] >= 0x80U ? 0xffU : 0U;
    old_value = game->ram[MYSMB_PLAYER_Y];
    game->ram[MYSMB_PLAYER_Y] =
        (mysmb_u8)(old_value + game->ram[MYSMB_PLAYER_Y_SPEED] + carry_dummy);
    carry_y = game->ram[MYSMB_PLAYER_Y] < old_value ? 1U : 0U;
    game->ram[MYSMB_PLAYER_Y_HIGH] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_Y_HIGH] + page_delta + carry_y);
    if ((game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS] &
         game->ram[MYSMB_PLAYER_COLLISION_BITS]) == 0U) {
        game->ram[MYSMB_CLIMB_SIDE_TIMER] = 0U;
        return;
    }
    if (game->ram[MYSMB_CLIMB_SIDE_TIMER] != 0U) return;
    game->ram[MYSMB_CLIMB_SIDE_TIMER] = 0x18U;
    facing = game->ram[MYSMB_PLAYER_FACING];
    if ((facing & MYSMB_BUTTON_RIGHT) != 0U) {
        index = 0U;
    }
    else index = 3U;
    old_value = game->ram[MYSMB_PLAYER_X];
    game->ram[MYSMB_PLAYER_X] = (mysmb_u8)(old_value + x_low[index]);
    carry_y = game->ram[MYSMB_PLAYER_X] < old_value ? 1U : 0U;
    game->ram[MYSMB_PLAYER_PAGE] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_PAGE] + x_high[index] + carry_y);
    game->ram[MYSMB_PLAYER_FACING] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS] ^ 3U);
}

/* Translation of the X_Physics parameter route in ROM $b50b-$b5cb.
 * Player animation timing is owned by GetPlayerAnimSpeed. */
void mysmb_player_configure_horizontal(struct mysmb_game *game)
{
    static const mysmb_u8 max_left[3] = { 0xd8U, 0xe8U, 0xf0U };
    static const mysmb_u8 max_right[4] = { 0x28U, 0x18U, 0x10U, 0x0cU };
    static const mysmb_u8 friction[3] = { 0xe4U, 0x98U, 0xd0U };
    mysmb_u8 speed_index;
    mysmb_u8 friction_index;
    mysmb_u8 friction_value;

    speed_index = 0U;
    friction_index = 0U;
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
    }
    else if (game->ram[MYSMB_PLAYER_X_SPEED_ABSOLUTE] < 0x19U) {
        speed_index++;
        friction_index++;
    }
    if (game->ram[MYSMB_RUNNING_SPEED] != 0U ||
        game->ram[MYSMB_PLAYER_X_SPEED_ABSOLUTE] >= 0x21U) {
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

/* GameEngine's RelativePlayerPosition supplies ScrollHandler on the next
 * frame. */
static void mysmb_player_update_relative_position(struct mysmb_game *game)
{
    game->ram[MYSMB_PLAYER_POS_FOR_SCROLL] =
        (mysmb_u8)(game->ram[MYSMB_PLAYER_X] - game->ram[MYSMB_SCREEN_LEFT_X]);
}

/* PlayerCtrlRoutine -> PlayerMovementSubs ground/jump path currently admitted. */
void mysmb_player_step(struct mysmb_game *game, mysmb_u8 buttons)
{
    mysmb_u8 a_b;
    mysmb_u8 a_held;
    mysmb_u8 jump_height;

    /* PlayerDeath jumps into PlayerCtrlRoutine after its engine-$0b guard,
     * which deliberately skips the controller partition.  Death motion uses
     * the input latched by the collision frame rather than a new host sample. */
    if (game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 0x0bU) {
        mysmb_player_latch_input(game, buttons);
    }
    a_b = game->ram[MYSMB_PLAYER_A_B_BUTTONS];
    if (game->ram[MYSMB_PLAYER_STATE] == 3U) {
        mysmb_player_configure_climb(game);
        mysmb_player_climb(game);
        if (game->ram[MYSMB_DISABLE_COLLISION] == 0U &&
            game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] >= 4U &&
            game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] != 0x0bU) {
            (void)mysmb_player_check_head(game);
            (void)mysmb_player_check_feet(game);
            (void)mysmb_player_check_sides(game);
        }
        mysmb_player_update_relative_position(game);
        game->ram[MYSMB_PREVIOUS_A_B_BUTTONS] = a_b;
        return;
    }
    /* PlayerMovementSubs reloads this before dispatching every non-climbing
     * state.  A later HandleClimbing therefore begins with the delay active. */
    game->ram[MYSMB_CLIMB_SIDE_TIMER] = 0x18U;
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
    if (game->ram[MYSMB_PLAYER_STATE] == 0U &&
        game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS] != 0U) {
        game->ram[MYSMB_PLAYER_FACING] = game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS];
    }
    /* PlayerCtrlRoutine assigns Player_MovingDir only after
     * PlayerMovementSubs returns.  Horizontal physics therefore observes
     * the prior frame's direction while it selects friction. */
    mysmb_player_configure_horizontal(game);
    if (game->ram[MYSMB_PLAYER_STATE] == 0U || game->ram[MYSMB_SWIMMING] != 0U) {
        mysmb_player_update_animation_speed(game, buttons);
    }
    if (game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS] != 0U ||
        game->ram[MYSMB_PLAYER_X_SPEED] != 0U) {
        mysmb_player_impose_friction(game);
        game->ram[MYSMB_PLAYER_X_SCROLL] = mysmb_player_move_horizontally(game);
    }
    else {
        game->ram[MYSMB_PLAYER_X_SCROLL] = 0U;
    }
    if (game->ram[MYSMB_PLAYER_STATE] != 0U) {
        if (game->ram[MYSMB_PLAYER_STATE] == 2U ||
            game->ram[MYSMB_PLAYER_Y_SPEED] < 0x80U) {
            /* FallingSub and JumpSwimSub's non-rising branch both select
             * the downward force before vertical movement. */
            game->ram[MYSMB_VERTICAL_FORCE] =
                game->ram[MYSMB_VERTICAL_FORCE_DOWN];
        }
        else {
            /* JumpSwimSub switches after a released A button has carried
             * the player beyond the minimum jump height. */
            a_held = (mysmb_u8)(a_b & game->ram[MYSMB_PREVIOUS_A_B_BUTTONS] &
                                 MYSMB_BUTTON_A);
            if (a_held == 0U) {
                jump_height = (mysmb_u8)(game->ram[MYSMB_JUMP_ORIGIN_Y] -
                                          game->ram[MYSMB_PLAYER_Y]);
                if (jump_height >= game->ram[MYSMB_DIFF_HALT_JUMP]) {
                    game->ram[MYSMB_VERTICAL_FORCE] =
                        game->ram[MYSMB_VERTICAL_FORCE_DOWN];
                }
            }
        }
        if (game->ram[MYSMB_SWIMMING] != 0U) {
            if (game->ram[MYSMB_PLAYER_Y] < 0x14U) {
                game->ram[MYSMB_VERTICAL_FORCE] = 0x18U;
            }
            if (game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS] != 0U) {
                game->ram[MYSMB_PLAYER_FACING] =
                    game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS];
            }
        }
        /* MovePlayerVertically enters ImposeGravity through
         * ImposeGravitySprObj: VerticalForce is the downward force and the
         * generic upward-force branch is disabled. */
        mysmb_player_impose_gravity(game, game->ram[MYSMB_VERTICAL_FORCE],
                                    0U, 4U, 0U);
    }
    game->ram[MYSMB_PLAYER_BOUND_BOX] = 1U;
    if (game->ram[MYSMB_PLAYER_SIZE] == 0U) {
        game->ram[MYSMB_PLAYER_BOUND_BOX] =
            game->ram[MYSMB_PLAYER_CROUCHING] != 0U ? 2U : 0U;
    }
    /* PlayerCtrlRoutine updates movement direction and then invokes
     * ScrollHandler, after both horizontal and vertical movement have run. */
    game->ram[MYSMB_PLAYER_MOVING_DIRECTION] =
        game->ram[MYSMB_PLAYER_X_SPEED] >= 0x80U ? 2U : 1U;
    mysmb_player_update_scroll(game);
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
        (void)mysmb_player_check_head(game);
        (void)mysmb_player_check_feet(game);
        (void)mysmb_player_check_sides(game);
    }
    mysmb_player_update_relative_position(game);
    game->ram[MYSMB_PREVIOUS_A_B_BUTTONS] = a_b;
}

/* Translation of ROM $b069-$b07c Vine_AutoClimb.  The vine object's growth
 * and drawing are owned by the object route; this is only the player-side
 * forced-up input and the area-transition handoff after reaching its top. */
void mysmb_player_step_auto_climb(struct mysmb_game *game)
{
    if (game->ram[MYSMB_PLAYER_Y_HIGH] == 0U &&
        game->ram[MYSMB_PLAYER_Y] < 0xe4U) {
        game->ram[MYSMB_ALT_ENTRANCE] = 2U;
        game->ram[MYSMB_DISABLE_SCREEN]++;
        game->ram[MYSMB_OPER_MODE_TASK] = 0U;
        return;
    }
    game->ram[MYSMB_PLAYER_STATE] = 3U;
    mysmb_player_step(game, MYSMB_BUTTON_UP);
}

/* ROM $b0f4-$b113 PlayerChangeSize. */
void mysmb_player_step_change_size(struct mysmb_game *game)
{
    if (game->ram[MYSMB_TIMER_CONTROL] == 0xf8U) {
        if (game->ram[MYSMB_PLAYER_CHANGE_SIZE] == 0U) {
            game->ram[MYSMB_PLAYER_ANIMATION] = 0U;
            game->ram[MYSMB_PLAYER_CHANGE_SIZE] = 1U;
            game->ram[MYSMB_PLAYER_SIZE] ^= 1U;
        }
        return;
    }
    if (game->ram[MYSMB_TIMER_CONTROL] == 0xc4U) {
        game->ram[MYSMB_TIMER_CONTROL] = 0U;
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 8U;
    }
}

/* ROM $b114-$b138 PlayerInjuryBlink.  The palette cycle is a renderer-owned
 * effect; the player-control and timer handoff are native gameplay state. */
void mysmb_player_step_injury_blink(struct mysmb_game *game, mysmb_u8 buttons)
{
    if (game->ram[MYSMB_TIMER_CONTROL] >= 0xf0U) return;
    if (game->ram[MYSMB_TIMER_CONTROL] == 0xc8U) {
        game->ram[MYSMB_TIMER_CONTROL] = 0U;
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 8U;
        return;
    }
    mysmb_player_step(game, buttons);
}

/* ROM $b139-$b154 PlayerFireFlower, excluding palette upload. */
void mysmb_player_step_fire_flower(struct mysmb_game *game)
{
    if (game->ram[MYSMB_TIMER_CONTROL] == 0xc0U) {
        game->ram[MYSMB_TIMER_CONTROL] = 0U;
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 8U;
        game->ram[MYSMB_PLAYER_ATTRIBUTES] &= 0xfcU;
        return;
    }
    game->ram[MYSMB_PLAYER_ATTRIBUTES] =
        (mysmb_u8)((game->ram[MYSMB_PLAYER_ATTRIBUTES] & 0xfcU) |
                   ((mysmb_u8)(game->frame_number >> 2U) & 3U));
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

/* Translation of BlockBufferCollision address construction for player offset zero. */
mysmb_u8 mysmb_player_query_block(const struct mysmb_game *game,
                                  mysmb_u8 x_adder, mysmb_u8 y_adder,
                                  mysmb_u8 horizontal_contact,
                                  struct mysmb_player_terrain *terrain)
{
    mysmb_u8 x;
    mysmb_u8 page;
    mysmb_u8 column;
    mysmb_u8 y;
    mysmb_u16 address;

    if (terrain == 0) return 0U;
    x = (mysmb_u8)(game->ram[MYSMB_PLAYER_X] + x_adder);
    page = (mysmb_u8)(game->ram[MYSMB_PLAYER_PAGE] +
                      (x < game->ram[MYSMB_PLAYER_X] ? 1U : 0U));
    column = (mysmb_u8)(((page & 1U) << 4U) | (x >> 4U));
    y = (mysmb_u8)(((game->ram[MYSMB_PLAYER_Y] + y_adder) & 0xf0U) - 0x20U);
    if ((game->ram[MYSMB_PLAYER_Y] + y_adder) < 0x20U || y > 0xc0U) return 0U;
    address = (mysmb_u16)((column & 0x10U) != 0U ? 0x05d0U : 0x0500U);
    address = (mysmb_u16)(address + (column & 0x0fU));
    terrain->block_address_low = (mysmb_u8)(address & 0x00ffU);
    address = (mysmb_u16)(address + y);
    if (address >= 0x0800U) return 0U;
    terrain->metatile = game->ram[address];
    terrain->contact_low_nibble = horizontal_contact != 0U ?
        (mysmb_u8)(game->ram[MYSMB_PLAYER_X] & 0x0fU) :
        (mysmb_u8)(game->ram[MYSMB_PLAYER_Y] & 0x0fU);
    terrain->block_row_offset = y;
    return 1U;
}

/* Translation of CheckForClimbMTiles. */
static mysmb_u8 mysmb_player_is_climbable(mysmb_u8 metatile)
{
    static const mysmb_u8 upper[4] = { 0x24U, 0x6dU, 0x8aU, 0xc6U };

    return metatile >= upper[(mysmb_u8)(metatile >> 6U)] ? 1U : 0U;
}

/* Translation of HandleClimbing through PutPlayerOnVine.  The caller passes
 * the collision helper's $04 and $06 values as terrain metadata. */
static mysmb_u8 mysmb_player_handle_climbing(struct mysmb_game *game,
                                              const struct mysmb_player_terrain *terrain)
{
    static const mysmb_u8 x_adder[2] = { 0xf9U, 0x07U };
    static const mysmb_u8 page_adder[2] = { 0xffU, 0U };
    mysmb_u8 facing_index;
    mysmb_u8 relative_x;

    if (terrain->contact_low_nibble < 6U ||
        terrain->contact_low_nibble >= 0x0aU) {
        return 0U;
    }
    if (terrain->metatile == 0x24U || terrain->metatile == 0x25U) {
        /* Flagpole score, sound, and completion sequencing are owned by M2
         * T6.  Its collision handoff still places Mario on the pole. */
        game->ram[MYSMB_PLAYER_FACING] = MYSMB_BUTTON_RIGHT;
        game->ram[MYSMB_SCROLL_LOCK]++;
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 4U;
    }
    else if (terrain->metatile == 0x26U &&
             game->ram[MYSMB_PLAYER_Y] < 0x20U) {
        game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 1U;
    }
    else if (terrain->metatile != 0x26U) {
        return 0U;
    }
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

/* Translation of CheckForSolidMTiles and LandPlyr's state update. */
mysmb_u8 mysmb_player_land_on_solid(struct mysmb_game *game,
                                    mysmb_u8 metatile, mysmb_u8 contact)
{
    /* ROM LandPlyr follows ChkInvisibleMTiles directly: an ordinary nonzero
     * foot metatile, including the $54 ground terrain, is a landing surface.
     * SolidMTileUpperExt belongs to head/side collision only. */
    if (metatile < 0x10U || mysmb_player_is_climbable(metatile) != 0U ||
        game->ram[MYSMB_PLAYER_Y_SPEED] >= 0x80U ||
        contact >= 5U) {
        return 0U;
    }
    game->ram[MYSMB_PLAYER_Y] = (mysmb_u8)(game->ram[MYSMB_PLAYER_Y] & 0xf0U);
    game->ram[MYSMB_PLAYER_Y_SPEED] = 0U;
    game->ram[MYSMB_PLAYER_Y_FORCE] = 0U;
    game->ram[MYSMB_PLAYER_STATE] = 0U;
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

/* Translation of VerticalPipeEntry through ChgAreaMode, excluding the
 * destination-pointer update that the area-transition owner performs. */
void mysmb_player_step_vertical_pipe(struct mysmb_game *game)
{
    mysmb_u8 entrance;

    game->ram[MYSMB_PLAYER_Y]++;
    mysmb_player_update_scroll(game);
    entrance = 0U;
    if (game->ram[MYSMB_WARP_ZONE_CONTROL] == 0U) {
        entrance = game->ram[MYSMB_AREA_TYPE] == 3U ? 2U : 1U;
    }
    if (game->ram[MYSMB_CHANGE_AREA_TIMER] != 0U) {
        game->ram[MYSMB_CHANGE_AREA_TIMER]--;
    }
    if (game->ram[MYSMB_CHANGE_AREA_TIMER] == 0U) {
        game->ram[MYSMB_ALT_ENTRANCE] = entrance;
        game->ram[MYSMB_DISABLE_SCREEN]++;
        game->ram[MYSMB_OPER_MODE_TASK] = 0U;
    }
}

/* Translation of SideExitPipeEntry/EnterSidePipe. */
void mysmb_player_step_side_pipe(struct mysmb_game *game)
{
    mysmb_u8 forced_buttons;

    game->ram[MYSMB_PLAYER_X_SPEED] = 8U;
    forced_buttons = MYSMB_BUTTON_RIGHT;
    if ((game->ram[MYSMB_PLAYER_X] & 0x0fU) == 0U) {
        game->ram[MYSMB_PLAYER_X_SPEED] = 0U;
        forced_buttons = 0U;
    }
    mysmb_player_step(game, forced_buttons);
    if (game->ram[MYSMB_CHANGE_AREA_TIMER] != 0U) {
        game->ram[MYSMB_CHANGE_AREA_TIMER]--;
    }
    if (game->ram[MYSMB_CHANGE_AREA_TIMER] == 0U) {
        game->ram[MYSMB_ALT_ENTRANCE] = 2U;
        game->ram[MYSMB_DISABLE_SCREEN]++;
        game->ram[MYSMB_OPER_MODE_TASK] = 0U;
    }
}

/* Translation of ROM $dc64-$dd5a PlayerBGCollision's DoFootCheck through LandPlyr.
 * The original selects an adder from size/crouch/swim state, but both feet
 * ultimately use X+3/X+12 and Y+32.  It reads left first for the landing
 * decision after sampling both positions. */
mysmb_u8 mysmb_player_check_feet(struct mysmb_game *game)
{
    static const mysmb_u8 x_adder[22] = {
        8U, 3U, 0x0cU, 2U, 2U, 0x0dU, 0x0dU, 8U, 3U, 0x0cU, 2U,
        2U, 0x0dU, 0x0dU, 8U, 8U, 3U, 0x0cU, 2U, 2U, 0x0dU, 0x0dU
    };
    static const mysmb_u8 y_adder[22] = {
        4U, 0x20U, 0x20U, 8U, 0x18U, 8U, 0x18U, 2U, 0x20U, 0x20U,
        8U, 0x18U, 8U, 0x18U, 0x12U, 0x20U, 0x20U, 0x18U, 0x18U,
        0x18U, 0x18U, 0x18U
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
    have_left = mysmb_player_query_block(game, x_adder[(mysmb_u8)(base + 1U)],
                                         y_adder[(mysmb_u8)(base + 1U)], 0U, &left);
    have_right = mysmb_player_query_block(game, x_adder[(mysmb_u8)(base + 2U)],
                                          y_adder[(mysmb_u8)(base + 2U)], 0U, &right);
    /* ChkFootMTile consumes the left sample when it is nonzero; it visits
     * the right sample only when the left is empty.  A climbable sample
     * hands off to the side route instead of becoming a landing surface. */
    if (have_left != 0U && (left.metatile == 0xc2U || left.metatile == 0xc3U)) {
        mysmb_objects_collect_coin(game, left.block_address_low,
                                   left.block_row_offset);
        return 1U;
    }
    if (have_left != 0U && left.metatile != 0U) {
        if (mysmb_player_is_climbable(left.metatile) != 0U) return 0U;
        /* ROM HandleAxeMetatile runs from the foot sample before ordinary
         * landing.  Its cleared metatile is enough for the C core; the
         * bridge presentation is owned by VictoryMode task zero. */
        if (left.metatile == 0xc5U && game->ram[MYSMB_PLAYER_Y_SPEED] < 0x80U) {
            game->ram[0x0772U] = 0U;
            game->ram[0x0770U] = 2U;
            game->ram[MYSMB_PLAYER_X_SPEED] = 0x18U;
            game->ram[(mysmb_u16)(0x0500U + left.block_address_low +
                                   left.block_row_offset)] = 0U;
            return 1U;
        }
        if (mysmb_player_land_on_solid(game, left.metatile,
                                       left.contact_low_nibble) == 0U) {
            return 0U;
        }
        (void)mysmb_player_handle_vertical_pipe(game, left.metatile,
                                                have_right != 0U ? right.metatile : 0U);
        return 1U;
    }
    if (have_right != 0U && (right.metatile == 0xc2U || right.metatile == 0xc3U)) {
        mysmb_objects_collect_coin(game, right.block_address_low,
                                   right.block_row_offset);
        return 1U;
    }
    if (have_right != 0U && right.metatile != 0U) {
        if (mysmb_player_is_climbable(right.metatile) != 0U) return 0U;
        return mysmb_player_land_on_solid(game, right.metatile,
                                          right.contact_low_nibble);
    }
    return 0U;
}

/* Translation of ROM $9131-$9196 Entrance_GameTimerSetup.  Palette, vine,
 * and bubble work retain their separate output and object owners. */
void mysmb_player_initialize_entrance(struct mysmb_game *game)
{
    static const mysmb_u8 start_x[4] = { 0x28U, 0x18U, 0x38U, 0x28U };
    static const mysmb_u8 alternate_y[2] = { 0x08U, 0x00U };
    static const mysmb_u8 start_y[9] = { 0x00U, 0x20U, 0xb0U, 0x50U,
                                         0x00U, 0x00U, 0xb0U, 0xb0U, 0xf0U };
    static const mysmb_u8 background_priority[8] = {
        0U, 0x20U, 0U, 0U, 0U, 0U, 0U, 0U
    };
    static const mysmb_u8 game_timer_data[4] = { 0x20U, 4U, 3U, 2U };
    mysmb_u8 alternate;
    mysmb_u8 entrance;

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
        if (alternate > 3U) return;
        entrance = alternate_y[(mysmb_u8)(alternate - 2U)];
    }
    if (alternate >= 4U || entrance >= 9U) return;
    game->ram[MYSMB_PLAYER_X] = start_x[alternate];
    game->ram[MYSMB_PLAYER_Y] = start_y[entrance];
    game->ram[MYSMB_PLAYER_ATTRIBUTES] = background_priority[entrance];
    if (game->ram[MYSMB_GAME_TIMER_SETTING] != 0U &&
        game->ram[MYSMB_FETCH_NEW_GAME_TIMER] != 0U) {
        game->ram[MYSMB_GAME_TIMER_DISPLAY] =
            game_timer_data[game->ram[MYSMB_GAME_TIMER_SETTING]];
        game->ram[MYSMB_GAME_TIMER_DISPLAY + 1U] = 0U;
        game->ram[MYSMB_GAME_TIMER_DISPLAY + 2U] = 1U;
        game->ram[MYSMB_FETCH_NEW_GAME_TIMER] = 0U;
        game->ram[MYSMB_STAR_INVINCIBLE_TIMER] = 0U;
    }
    game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 7U;
}

/* Translation of ROM $b069-$b0e5 PlayerEntrance after InitializeArea.  The
 * object-owned alternate entrance 3 waits for vine growth; normal and pipe
 * entrances complete here, while alternate entrance 2 rises from its pipe
 * until the original PlayerRdy threshold. */
void mysmb_player_finish_normal_entrance(struct mysmb_game *game)
{
    if (game->ram[MYSMB_ALT_ENTRANCE] == 3U) {
        return;
    }
    if (game->ram[MYSMB_PLAYER_ENTRANCE] == 6U ||
        game->ram[MYSMB_PLAYER_ENTRANCE] == 7U) {
        /* PlayerEntrance's ChkBehPipe: before the pipe contact has set the
         * priority bit, the original forces a rightward PlayerCtrlRoutine.
         * Once set, its IntroEntr branch uses EnterSidePipe and the timer. */
        if (game->ram[MYSMB_PLAYER_ATTRIBUTES] == 0U) {
            mysmb_player_step(game, MYSMB_BUTTON_RIGHT);
        }
        else {
            mysmb_player_step_side_pipe(game);
        }
        return;
    }
    if (game->ram[MYSMB_ALT_ENTRANCE] == 2U) {
        game->ram[MYSMB_PLAYER_Y]--;
        if (game->ram[MYSMB_PLAYER_Y] >= 0x91U) return;
    }
    game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 8U;
    game->ram[MYSMB_PLAYER_FACING] = 1U;
    game->ram[MYSMB_ALT_ENTRANCE] = 0U;
    game->ram[MYSMB_DISABLE_COLLISION] = 0U;
    game->ram[MYSMB_JOYPAD_OVERRIDE] = 0U;
}

/* Translation of ScrollHandler's ChkPOffscr through KeepOnscr. */
static void mysmb_player_clamp_screen_edge(struct mysmb_game *game)
{
    mysmb_u8 right_x;
    mysmb_u8 right_page;
    mysmb_u8 target_x;
    mysmb_u8 target_page;
    mysmb_u8 buttons;

    right_x = game->ram[MYSMB_SCREEN_RIGHT_X];
    right_page = game->ram[MYSMB_SCREEN_RIGHT_PAGE];
    buttons = game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS];
    if (game->ram[MYSMB_PLAYER_PAGE] < game->ram[MYSMB_SCREEN_LEFT_PAGE] ||
        (game->ram[MYSMB_PLAYER_PAGE] == game->ram[MYSMB_SCREEN_LEFT_PAGE] &&
         game->ram[MYSMB_PLAYER_X] < game->ram[MYSMB_SCREEN_LEFT_X])) {
        game->ram[MYSMB_PLAYER_X] = game->ram[MYSMB_SCREEN_LEFT_X];
        game->ram[MYSMB_PLAYER_PAGE] = game->ram[MYSMB_SCREEN_LEFT_PAGE];
        if (buttons != MYSMB_BUTTON_RIGHT) game->ram[MYSMB_PLAYER_X_SPEED] = 0U;
        return;
    }
    if (game->ram[MYSMB_PLAYER_PAGE] > right_page ||
        (game->ram[MYSMB_PLAYER_PAGE] == right_page &&
         game->ram[MYSMB_PLAYER_X] > right_x)) {
        target_x = (mysmb_u8)(right_x - 0x10U);
        target_page = right_page;
        if (right_x < 0x10U) target_page--;
        game->ram[MYSMB_PLAYER_X] = target_x;
        game->ram[MYSMB_PLAYER_PAGE] = target_page;
        if (buttons != MYSMB_BUTTON_LEFT) game->ram[MYSMB_PLAYER_X_SPEED] = 0U;
    }
}

/* Translation of ROM $af93-$b068 ScrollHandler through GetScreenPosition. */
void mysmb_player_update_scroll(struct mysmb_game *game)
{
    mysmb_u8 force;
    mysmb_u8 amount;
    mysmb_u8 old_x;
    mysmb_u8 relative_x;

    /* ScrollHandler consumes Player_Pos_ForScroll written by the preceding
     * frame's RelativePlayerPosition, not the position just moved here. */
    relative_x = game->ram[MYSMB_PLAYER_POS_FOR_SCROLL];
    force = (mysmb_u8)(game->ram[MYSMB_PLAYER_X_SCROLL] +
                        game->ram[MYSMB_PLATFORM_X_SCROLL]);
    game->ram[MYSMB_PLAYER_X_SCROLL] = force;
    amount = 0U;
    if (game->ram[MYSMB_SCROLL_LOCK] == 0U && relative_x >= 0x50U &&
        game->ram[MYSMB_SIDE_COLLISION_TIMER] == 0U && force != 0U &&
        force < 0x80U) {
        amount = force;
        if (amount >= 2U && relative_x < 0x70U) amount--;
    }
    game->ram[MYSMB_SCROLL_AMOUNT] = amount;
    game->ram[MYSMB_SCROLL_THIRTY_TWO] =
        (mysmb_u8)(game->ram[MYSMB_SCROLL_THIRTY_TWO] + amount);
    old_x = game->ram[MYSMB_SCREEN_LEFT_X];
    game->ram[MYSMB_SCREEN_LEFT_X] = (mysmb_u8)(old_x + amount);
    game->ram[MYSMB_HORIZONTAL_SCROLL] = game->ram[MYSMB_SCREEN_LEFT_X];
    if (game->ram[MYSMB_SCREEN_LEFT_X] < old_x) {
        game->ram[MYSMB_SCREEN_LEFT_PAGE]++;
    }
    game->ram[MYSMB_SCREEN_RIGHT_X] =
        (mysmb_u8)(game->ram[MYSMB_SCREEN_LEFT_X] + 0xffU);
    game->ram[MYSMB_SCREEN_RIGHT_PAGE] = game->ram[MYSMB_SCREEN_LEFT_PAGE];
    if (game->ram[MYSMB_SCREEN_RIGHT_X] < game->ram[MYSMB_SCREEN_LEFT_X]) {
        game->ram[MYSMB_SCREEN_RIGHT_PAGE]++;
    }
    mysmb_player_clamp_screen_edge(game);
    game->ram[MYSMB_PLATFORM_X_SCROLL] = 0U;
    /* ROM $8178 commits HorizontalScroll/VerticalScroll and the active name
     * table during NMI.  Keep that portable output state with the translated
     * scroll owner; host adapters only consume this committed record. */
    game->scroll_x = game->ram[MYSMB_HORIZONTAL_SCROLL];
    game->scroll_y = game->ram[0x0740U];
    game->ppu_name_table = (mysmb_u8)(game->ram[MYSMB_SCREEN_LEFT_PAGE] & 1U);
    game->ppu_control_0 = (mysmb_u8)((game->ppu_control_0 & 0xfcU) |
                                     game->ppu_name_table);
}

/* Translation of ROM $df4b-$df7d ImpedePlayerMove. */
void mysmb_player_impede_move(struct mysmb_game *game, mysmb_u8 moving_direction)
{
    mysmb_u8 speed;
    mysmb_u8 correction;
    mysmb_u8 page_delta;

    speed = game->ram[MYSMB_PLAYER_X_SPEED];
    if (moving_direction == 1U) {
        if (speed >= 0x80U) return;
        correction = 0xffU;
        page_delta = 0xffU;
        game->ram[MYSMB_PLAYER_COLLISION_BITS] &= 0xfeU;
    }
    else if (moving_direction == 2U) {
        if (speed != 0U && speed < 0x80U) return;
        correction = 1U;
        page_delta = 0U;
        game->ram[MYSMB_PLAYER_COLLISION_BITS] &= 0xfdU;
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
}

/* Translation of CheckSideMTiles.  Coins and jumpsprings have their own
 * object route, but they still consume this collision without a wall stop. */
static mysmb_u8 mysmb_player_handle_side_metatile(
    struct mysmb_game *game, const struct mysmb_player_terrain *terrain)
{
    if (terrain->metatile == 0xc2U || terrain->metatile == 0xc3U) {
        mysmb_objects_collect_coin(game, terrain->block_address_low,
                                   terrain->block_row_offset);
        return 1U;
    }
    if (terrain->metatile == 0x5fU || terrain->metatile == 0x60U ||
        terrain->metatile == 0x67U || terrain->metatile == 0x68U) {
        return 1U;
    }
    if (mysmb_player_is_climbable(terrain->metatile) != 0U) {
        (void)mysmb_player_handle_climbing(game, terrain);
        return 1U;
    }
    if ((terrain->metatile == 0x6cU || terrain->metatile == 0x1fU) &&
        game->ram[MYSMB_PLAYER_STATE] == 0U &&
        game->ram[MYSMB_PLAYER_FACING] == MYSMB_BUTTON_RIGHT) {
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
    mysmb_player_impede_move(game, game->ram[MYSMB_PLAYER_MOVING_DIRECTION]);
    return 1U;
}

/* Translation of ROM $dd5e-$de46 SideCheckLoop.  Each upper sample can
 * defer to the lower half, which prevents a thin vine or pipe cap from
 * producing a side collision on its own. */
mysmb_u8 mysmb_player_check_sides(struct mysmb_game *game)
{
    static const mysmb_u8 x_adder[22] = {
        8U, 3U, 0x0cU, 2U, 2U, 0x0dU, 0x0dU, 8U, 3U, 0x0cU, 2U,
        2U, 0x0dU, 0x0dU, 8U, 8U, 3U, 0x0cU, 2U, 2U, 0x0dU, 0x0dU
    };
    static const mysmb_u8 y_adder[22] = {
        4U, 0x20U, 0x20U, 8U, 0x18U, 8U, 0x18U, 2U, 0x20U, 0x20U,
        8U, 0x18U, 8U, 0x18U, 0x12U, 0x20U, 0x20U, 0x18U, 0x18U,
        0x18U, 0x18U, 0x18U
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
            mysmb_player_query_block(game, x_adder[top], y_adder[top], 1U,
                                     &terrain) != 0U && terrain.metatile != 0U &&
            terrain.metatile != 0x1cU && terrain.metatile != 0x6bU &&
            mysmb_player_is_climbable(terrain.metatile) == 0U) {
            return mysmb_player_handle_side_metatile(game, &terrain);
        }
        if (game->ram[MYSMB_PLAYER_Y] < 8U ||
            game->ram[MYSMB_PLAYER_Y] >= 0xd0U) return 0U;
        top++;
        if (mysmb_player_query_block(game, x_adder[top], y_adder[top], 1U,
                                     &terrain) != 0U && terrain.metatile != 0U) {
            return mysmb_player_handle_side_metatile(game, &terrain);
        }
    }
    return 0U;
}

/* Translation of ROM $dcba-$dcf5 HeadChk through NYSpd.  Matched bumpable
 * blocks hand their original collision coordinates to the object owner. */
mysmb_u8 mysmb_player_check_head(struct mysmb_game *game)
{
    static const mysmb_u8 x_adder[22] = {
        8U, 3U, 0x0cU, 2U, 2U, 0x0dU, 0x0dU, 8U, 3U, 0x0cU, 2U,
        2U, 0x0dU, 0x0dU, 8U, 8U, 3U, 0x0cU, 2U, 2U, 0x0dU, 0x0dU
    };
    static const mysmb_u8 y_adder[22] = {
        4U, 0x20U, 0x20U, 8U, 0x18U, 8U, 0x18U, 2U, 0x20U, 0x20U,
        8U, 0x18U, 8U, 0x18U, 0x12U, 0x20U, 0x20U, 0x18U, 0x18U,
        0x18U, 0x18U, 0x18U
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
    if (mysmb_player_query_block(game, x_adder[base], y_adder[base],
                                 0U, &terrain) == 0U || terrain.metatile == 0U) {
        return 0U;
    }
    if (terrain.metatile == 0xc2U || terrain.metatile == 0xc3U) {
        mysmb_objects_collect_coin(game, terrain.block_address_low,
                                   terrain.block_row_offset);
        return 1U;
    }
    if (game->ram[MYSMB_PLAYER_Y_SPEED] < 0x80U ||
        (game->ram[MYSMB_PLAYER_Y] & 0x0fU) < 4U) {
        return 0U;
    }
    group = (mysmb_u8)(terrain.metatile >> 6U);
    if (terrain.metatile >= solid_upper[group]) {
        game->ram[MYSMB_PLAYER_Y_SPEED] = 1U;
        return 1U;
    }
    if (game->ram[0x0784U] == 0U) {
        if (mysmb_objects_start_head_bump(game, terrain.metatile,
                                          terrain.block_address_low,
                                          terrain.block_row_offset) != 0U) {
            return 1U;
        }
    }
    return 0U;
}
