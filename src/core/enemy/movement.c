#include "core/enemy/movement.h"
#include "core/objects.h"
#include "core/world/world.h"

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
        mysmb_enemy_move_defeated(game, slot);
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

/* ROM $CAE5 MoveDefeatedEnemy: shared defeated tail, irrespective of
 * other state bits that MoveNormalEnemy would examine first. */
void mysmb_enemy_move_defeated(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_move_d_vertically(game, slot);
    mysmb_world_move_enemy_horizontally(game, slot);
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

/* ROM $BF94-$BF9F SetHiMax/SetXMoveAmt. The existing gravity child
 * receives the original A maximum and X=enemy slot+1; it remains S9-owned. */
void mysmb_enemy_move_downward(struct mysmb_game *game, mysmb_u8 slot,
                               mysmb_u8 amount, mysmb_u8 maximum_speed)
{
    game->ram[0U] = amount;
    mysmb_world_impose_gravity_spr_object(game, (mysmb_u8)(slot + 1U),
                                         amount, maximum_speed);
}

/* ROM $BF88-$BF91 MoveDropPlatform, MoveEnemySlowVert and SetMdMax. */
void mysmb_enemy_move_drop_platform(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_move_downward(game, slot, 0x7fU, 2U);
}
void mysmb_enemy_move_slow_vertically(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_move_downward(game, slot, 0x0fU, 2U);
}
/* ROM $BF92-$BF94 MoveJ_EnemyVertically / SetHiMax. */
void mysmb_enemy_move_j_vertically(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_move_downward(game, slot, 0x1cU, 3U);
}

/* ROM $BF77-$BF87 MoveRedPTroopa. Direction is original Y/A. */
static void mysmb_enemy_move_red_vertically(struct mysmb_game *game,
                                           mysmb_u8 slot, mysmb_u8 direction)
{
    game->ram[0U] = 3U;
    game->ram[1U] = 6U;
    game->ram[2U] = 2U;
    mysmb_world_red_gravity(game, (mysmb_u8)(slot + 1U), direction);
}
/* ROM $BF70 / $BF75: distinct down/up entries into the shared adapter. */
void mysmb_enemy_move_red_down(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_move_red_vertically(game, slot, 0U);
}
void mysmb_enemy_move_red_up(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_move_red_vertically(game, slot, 1U);
}

/* ROM $CAF9 MoveJumpingEnemy. Existing gravity and horizontal child
 * algorithms are shared unchanged by the star and paratroopa callers. */
void mysmb_enemy_move_jumping(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_move_j_vertically(game, slot);
    mysmb_world_move_enemy_horizontally(game, slot);
}
