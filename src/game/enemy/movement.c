#include "game/enemy/movement.h"

enum {
    MYSMB_ENEMY_Y_SPEED = 0x00a0U,
    MYSMB_ENEMY_Y_HIGH = 0x00b6U,
    MYSMB_ENEMY_Y = 0x00cfU,
    MYSMB_ENEMY_Y_DUMMY = 0x0417U,
    MYSMB_ENEMY_Y_FORCE = 0x0434U
};

/* ROM $b11d SetHiMax/ImposeGravitySprObj as called by MoveD_EnemyVertically.
 * This owns only the shared actor-array arithmetic; it does not select actor
 * states, collision branches, rendering, or any platform operation. */
void mysmb_enemy_move_downward(struct mysmb_game *game, mysmb_u8 slot,
                               mysmb_u8 amount, mysmb_u8 maximum_speed)
{
    mysmb_u8 old_value;
    mysmb_u8 carry;
    mysmb_u8 page_delta;
    mysmb_u16 sum;

    old_value = game->ram[MYSMB_ENEMY_Y_DUMMY + slot];
    game->ram[MYSMB_ENEMY_Y_DUMMY + slot] =
        (mysmb_u8)(old_value + game->ram[MYSMB_ENEMY_Y_FORCE + slot]);
    carry = game->ram[MYSMB_ENEMY_Y_DUMMY + slot] < old_value ? 1U : 0U;
    page_delta = game->ram[MYSMB_ENEMY_Y_SPEED + slot] >= 0x80U ? 0xffU : 0U;
    sum = (mysmb_u16)game->ram[MYSMB_ENEMY_Y + slot] +
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] + carry;
    game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)sum;
    carry = sum > 0xffU ? 1U : 0U;
    game->ram[MYSMB_ENEMY_Y_HIGH + slot] =
        (mysmb_u8)(game->ram[MYSMB_ENEMY_Y_HIGH + slot] + page_delta + carry);
    old_value = game->ram[MYSMB_ENEMY_Y_FORCE + slot];
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = (mysmb_u8)(old_value + amount);
    carry = game->ram[MYSMB_ENEMY_Y_FORCE + slot] < old_value ? 1U : 0U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] =
        (mysmb_u8)(game->ram[MYSMB_ENEMY_Y_SPEED + slot] + carry);
    if (game->ram[MYSMB_ENEMY_Y_SPEED + slot] >= maximum_speed &&
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] < 0x80U &&
        game->ram[MYSMB_ENEMY_Y_FORCE + slot] >= 0x80U) {
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] = maximum_speed;
        game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
    }
}
