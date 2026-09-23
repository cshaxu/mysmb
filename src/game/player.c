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
