#include "game/enemy/movement.h"
#include "game/objects.h"
#include "game/world/world.h"

enum {
    MYSMB_ENEMY_Y_SPEED = 0x00a0U,
    MYSMB_ENEMY_Y_HIGH = 0x00b6U,
    MYSMB_ENEMY_Y = 0x00cfU,
    MYSMB_ENEMY_Y_DUMMY = 0x0417U,
    MYSMB_ENEMY_Y_FORCE = 0x0434U
};

/* ROM $ca77-$caf8 MoveNormalEnemy, with $c9d0/$c9d4 source tables.
 * The caller owns the timer gate, collisions, and final offscreen check. */
void mysmb_enemy_move_normal(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 speed_adder[4] = {0U,0xe8U,0U,0x18U};
    static const mysmb_u8 revived_speed[4] = {8U,0xf8U,12U,0xf4U};
    mysmb_u8 state;
    mysmb_u8 index;
    mysmb_u8 speed;
    mysmb_u8 timer;

    index = 0U;
    state = game->ram[0x001eU + slot];
    if ((state & 0x40U) != 0U) goto fall;
    if ((state & 0x80U) != 0U) goto steady;
    if ((state & 0x20U) != 0U) {
        mysmb_enemy_move_d_vertically(game, slot);
        mysmb_world_move_enemy_horizontally(game, slot);
        return;
    }
    state &= 7U;
    if (state == 0U) goto steady;
    if (state == 5U) goto fall;
    if (state >= 3U) {
        timer = game->ram[0x0796U + slot];
        if (timer != 0U) {
            if (timer == 0x0eU && game->ram[0x0016U + slot] == 6U)
                mysmb_objects_erase_enemy(game, slot);
            return;
        }
        game->ram[0x001eU + slot] = 0U;
        index = (mysmb_u8)(game->ram[9U] & 1U);
        game->ram[0x0046U + slot] = (mysmb_u8)(index + 1U);
        if (game->ram[0x076aU] != 0U) index += 2U;
        game->ram[0x0058U + slot] = revived_speed[index];
        return;
    }

fall:
    mysmb_enemy_move_d_vertically(game, slot);
    state = game->ram[0x001eU + slot];
    if (state == 2U) {
        mysmb_world_move_enemy_horizontally(game, slot);
        return;
    }
    if ((state & 0x40U) != 0U && game->ram[0x0016U + slot] != 0x2eU)
        index = 1U;
steady:
    speed = game->ram[0x0058U + slot];
    if ((speed & 0x80U) != 0U) index += 2U;
    game->ram[0x0058U + slot] = (mysmb_u8)(speed + speed_adder[index]);
    mysmb_world_move_enemy_horizontally(game, slot);
    game->ram[0x0058U + slot] = speed;
}

/* ROM MoveD_EnemyVertically falls through MoveFallingPlatform only for
 * exact state five; other low-bit matches keep the ordinary force. */
void mysmb_enemy_move_d_vertically(struct mysmb_game *game, mysmb_u8 slot)
{
    if (game->ram[0x001eU + slot] == 5U)
        mysmb_enemy_move_falling_platform(game, slot);
    else
        mysmb_enemy_move_downward(game, slot, 0x3dU, 3U);
}

/* ROM MoveFallingPlatform / ContVMove supplies force $20 to SetHiMax. */
void mysmb_enemy_move_falling_platform(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_move_downward(game, slot, 0x20U, 3U);
}

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
