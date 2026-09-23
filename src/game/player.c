#include "game/player.h"

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
    MYSMB_JUMP_SWIM_TIMER = 0x0782U
};

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
    MYSMB_ALT_ENTRANCE = 0x0752U,
    MYSMB_HALF_WAY_PAGE = 0x075bU,
    MYSMB_AREA_TYPE = 0x074eU
};

/* Translation of ROM MovePlayerHorizontally/MoveObjectHorizontally.
 * X speed is signed 4.4 fixed point; the low nibble accumulates in X force. */
void mysmb_player_move_horizontally(struct mysmb_game *game)
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
        return;
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

    game->ram[MYSMB_PLAYER_A_B_BUTTONS] =
        (mysmb_u8)(buttons & (MYSMB_BUTTON_A | MYSMB_BUTTON_B));
    left_right = (mysmb_u8)(buttons & (MYSMB_BUTTON_LEFT | MYSMB_BUTTON_RIGHT));
    up_down = (mysmb_u8)(buttons & 0x0cU);
    if ((up_down & 0x04U) != 0U && game->ram[MYSMB_PLAYER_STATE] == 0U &&
        left_right != 0U) {
        left_right = 0U;
        up_down = 0U;
    }
    game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS] = left_right;
    game->ram[MYSMB_PLAYER_UP_DOWN_BUTTONS] = up_down;
    game->ram[MYSMB_PLAYER_CROUCHING] =
        game->ram[MYSMB_PLAYER_STATE] == 0U && (up_down & 0x04U) != 0U ? 4U : 0U;
}

/* PlayerCtrlRoutine -> PlayerMovementSubs ground/jump path currently admitted. */
void mysmb_player_step(struct mysmb_game *game, mysmb_u8 buttons)
{
    mysmb_u8 a_b;

    mysmb_player_latch_input(game, buttons);
    a_b = game->ram[MYSMB_PLAYER_A_B_BUTTONS];
    if (game->ram[MYSMB_PLAYER_STATE] == 0U && (a_b & MYSMB_BUTTON_A) != 0U &&
        (game->ram[MYSMB_PREVIOUS_A_B_BUTTONS] & MYSMB_BUTTON_A) == 0U) {
        mysmb_player_start_jump(game, 0U);
    }
    if (game->ram[MYSMB_PLAYER_LEFT_RIGHT_BUTTONS] != 0U ||
        game->ram[MYSMB_PLAYER_X_SPEED] != 0U) {
        mysmb_player_impose_friction(game);
        mysmb_player_move_horizontally(game);
    }
    if (game->ram[MYSMB_PLAYER_STATE] != 0U) {
        mysmb_player_impose_gravity(game, game->ram[MYSMB_VERTICAL_FORCE_DOWN],
                                    game->ram[MYSMB_VERTICAL_FORCE], 4U, 1U);
    }
    (void)mysmb_player_check_feet(game);
    game->ram[MYSMB_PREVIOUS_A_B_BUTTONS] = a_b;
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
    address = (mysmb_u16)(address + (column & 0x0fU) + y);
    if (address >= 0x0800U) return 0U;
    terrain->metatile = game->ram[address];
    terrain->contact_low_nibble = horizontal_contact != 0U ?
        (mysmb_u8)(game->ram[MYSMB_PLAYER_X] & 0x0fU) :
        (mysmb_u8)(game->ram[MYSMB_PLAYER_Y] & 0x0fU);
    return 1U;
}

/* Translation of CheckForSolidMTiles and LandPlyr's state update. */
mysmb_u8 mysmb_player_land_on_solid(struct mysmb_game *game,
                                    mysmb_u8 metatile, mysmb_u8 contact)
{
    static const mysmb_u8 solid_upper[4] = { 0x10U, 0x61U, 0x88U, 0xc4U };
    mysmb_u8 group;

    group = (mysmb_u8)(metatile >> 6U);
    if (metatile < solid_upper[group] || game->ram[MYSMB_PLAYER_Y_SPEED] >= 0x80U ||
        contact >= 5U) {
        return 0U;
    }
    game->ram[MYSMB_PLAYER_Y] = (mysmb_u8)(game->ram[MYSMB_PLAYER_Y] & 0xf0U);
    game->ram[MYSMB_PLAYER_Y_SPEED] = 0U;
    game->ram[MYSMB_PLAYER_Y_FORCE] = 0U;
    game->ram[MYSMB_PLAYER_STATE] = 0U;
    return 1U;
}

/* Translation of ROM $dc64-$dd5a PlayerBGCollision's DoFootCheck through LandPlyr.
 * The original selects an adder from size/crouch/swim state, but both feet
 * ultimately use X+3/X+12 and Y+32.  It reads left first for the landing
 * decision after sampling both positions. */
mysmb_u8 mysmb_player_check_feet(struct mysmb_game *game)
{
    struct mysmb_player_terrain left;
    struct mysmb_player_terrain right;
    mysmb_u8 have_left;
    mysmb_u8 have_right;

    if (game->ram[MYSMB_PLAYER_Y_HIGH] != 1U ||
        game->ram[MYSMB_PLAYER_Y] >= 0xcfU) {
        return 0U;
    }
    if (game->ram[MYSMB_PLAYER_STATE] == 0U) {
        game->ram[MYSMB_PLAYER_STATE] =
            game->ram[MYSMB_SWIMMING] != 0U ? 1U : 2U;
    }
    have_left = mysmb_player_query_block(game, 3U, 0x20U, 0U, &left);
    have_right = mysmb_player_query_block(game, 0x0cU, 0x20U, 0U, &right);
    if (have_left != 0U && left.metatile != 0U) {
        return mysmb_player_land_on_solid(game, left.metatile,
                                          left.contact_low_nibble);
    }
    if (have_right != 0U && right.metatile != 0U) {
        return mysmb_player_land_on_solid(game, right.metatile,
                                          right.contact_low_nibble);
    }
    return 0U;
}

/* Translation of ROM $9131-$9196 Entrance_GameTimerSetup, restricted to
 * player state.  Timer digits, palettes, vine setup, and bubbles retain
 * their own owners. */
void mysmb_player_initialize_entrance(struct mysmb_game *game)
{
    static const mysmb_u8 start_x[4] = { 0x28U, 0x18U, 0x38U, 0x28U };
    static const mysmb_u8 alternate_y[2] = { 0x08U, 0x00U };
    static const mysmb_u8 start_y[9] = { 0x00U, 0x20U, 0xb0U, 0x50U,
                                         0x00U, 0x00U, 0xb0U, 0xb0U, 0xf0U };
    static const mysmb_u8 background_priority[8] = {
        0U, 0x20U, 0U, 0U, 0U, 0U, 0U, 0U
    };
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
    game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 7U;
}

/* Translation of the normal PlayerEntrance branch for headers other than
 * side-pipe entry. */
void mysmb_player_finish_normal_entrance(struct mysmb_game *game)
{
    if (game->ram[MYSMB_ALT_ENTRANCE] != 0U ||
        game->ram[MYSMB_PLAYER_ENTRANCE] == 6U ||
        game->ram[MYSMB_PLAYER_ENTRANCE] == 7U) {
        return;
    }
    game->ram[MYSMB_GAME_ENGINE_SUBROUTINE] = 8U;
    game->ram[MYSMB_PLAYER_FACING] = 1U;
    game->ram[MYSMB_ALT_ENTRANCE] = 0U;
}
