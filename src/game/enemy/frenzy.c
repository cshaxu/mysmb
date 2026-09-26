#include "game/enemy/frenzy.h"
#include "game/enemy/movement.h"
#include "game/world/world.h"

enum {
    MYSMB_ENEMY_FLAG = 0x000fU,
    MYSMB_ENEMY_ID = 0x0016U,
    MYSMB_ENEMY_STATE = 0x001eU,
    MYSMB_ENEMY_MOVING_DIRECTION = 0x0046U,
    MYSMB_ENEMY_X_SPEED = 0x0058U,
    MYSMB_ENEMY_PAGE = 0x006eU,
    MYSMB_ENEMY_X = 0x0087U,
    MYSMB_ENEMY_Y_SPEED = 0x00a0U,
    MYSMB_ENEMY_Y_HIGH = 0x00b6U,
    MYSMB_ENEMY_Y = 0x00cfU,
    MYSMB_ENEMY_Y_FORCE = 0x0434U,
    MYSMB_ENEMY_BOUND_BOX = 0x049aU,
    MYSMB_PLAYER_PAGE = 0x006dU,
    MYSMB_PLAYER_X = 0x0086U,
    MYSMB_PLAYER_Y = 0x00ceU,
    MYSMB_PLAYER_X_SPEED = 0x0057U,
    MYSMB_SCROLL_AMOUNT = 0x0775U,
    MYSMB_SCREEN_RIGHT_PAGE = 0x071bU,
    MYSMB_SCREEN_RIGHT_X = 0x071dU,
    MYSMB_ENEMY_FRENZY_BUFFER = 0x06cbU,
    MYSMB_LAKITU_REAPPEAR_TIMER = 0x06d1U,
    MYSMB_FRENZY_ENEMY_TIMER = 0x078fU,
    MYSMB_SECONDARY_HARD = 0x06ccU,
    MYSMB_ENEMY_X_FORCE = 0x0401U,
    MYSMB_ENEMY_Y_DUMMY = 0x0417U
};
/* ROM PlayerLakituDiff.  The 6502 compares the signed page difference
 * and then intentionally retains only the low byte for its speed table. */
static mysmb_u8 mysmb_enemy_player_lakitu_difference(struct mysmb_game *game,
                                                        mysmb_u8 slot)
{
    static const mysmb_u8 lakitu_adjustment[3] = { 0x15U, 0x30U, 0x40U };
    mysmb_u16 player_world;
    mysmb_u16 enemy_world;
    mysmb_u16 difference;
    mysmb_u8 distance;
    mysmb_u8 direction;
    mysmb_u8 adjustment_index;

    player_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_PLAYER_PAGE] << 8U) |
                                game->ram[MYSMB_PLAYER_X]);
    enemy_world = (mysmb_u16)(((mysmb_u16)game->ram[MYSMB_ENEMY_PAGE + slot] << 8U) |
                               game->ram[MYSMB_ENEMY_X + slot]);
    difference = (mysmb_u16)(enemy_world - player_world);
    direction = 0U;
    distance = (mysmb_u8)difference;
    if (difference >= 0x8000U) {
        direction = 1U;
        distance = (mysmb_u8)(0U - distance);
    }
    if (distance >= 0x3cU) {
        distance = 0x3cU;
        if (game->ram[MYSMB_ENEMY_ID + slot] == 17U &&
            direction != game->ram[MYSMB_ENEMY_Y_SPEED + slot]) {
            if (game->ram[MYSMB_ENEMY_Y_SPEED + slot] != 0U) {
                game->ram[MYSMB_ENEMY_X_SPEED + slot]--;
                if (game->ram[MYSMB_ENEMY_X_SPEED + slot] != 0U) return 0U;
            }
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = direction;
        }
    }
    distance = (mysmb_u8)((distance & 0x3cU) >> 2U);
    adjustment_index = 0U;
    if (game->ram[MYSMB_PLAYER_X_SPEED] != 0U &&
        game->ram[MYSMB_SCROLL_AMOUNT] != 0U) {
        adjustment_index = 1U;
        if (game->ram[MYSMB_PLAYER_X_SPEED] >= 0x19U &&
            game->ram[MYSMB_SCROLL_AMOUNT] >= 2U) adjustment_index = 2U;
    }
    if (game->ram[MYSMB_ENEMY_ID + slot] == 18U &&
        game->ram[MYSMB_PLAYER_X_SPEED] == 0U &&
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] == 0U) {
        adjustment_index = 0U;
    }
    /* SPixelLak subtracts once before decrementing Y, hence distance + 1. */
    return (mysmb_u8)(lakitu_adjustment[adjustment_index] - distance - 1U);
}

/* ROM MoveLakitu and PlayerLakituDiff.  Enemy_X_Speed and
 * Enemy_Y_Speed are LakituMoveSpeed and LakituMoveDirection in this route. */
void mysmb_enemy_step_lakitus(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u8 speed;

    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U ||
            game->ram[MYSMB_ENEMY_ID + slot] != 17U) continue;
        if ((game->ram[MYSMB_ENEMY_STATE + slot] & 0x20U) != 0U) {
            mysmb_enemy_move_downward(game, slot, 0x3dU, 3U);
            continue;
        }
        if (game->ram[MYSMB_ENEMY_STATE + slot] != 0U) {
            game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
            game->ram[MYSMB_ENEMY_FRENZY_BUFFER] = 0U;
            speed = 0x10U;
        }
        else {
            game->ram[MYSMB_ENEMY_FRENZY_BUFFER] = 18U;
            speed = mysmb_enemy_player_lakitu_difference(game, slot);
            if (speed == 0U && game->ram[MYSMB_ENEMY_X_SPEED + slot] != 0U &&
                game->ram[MYSMB_ENEMY_Y_SPEED + slot] != 0U) continue;
        }
        game->ram[MYSMB_ENEMY_X_SPEED + slot] = speed;
        game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 1U;
        if ((game->ram[MYSMB_ENEMY_Y_SPEED + slot] & 1U) == 0U) {
            game->ram[MYSMB_ENEMY_X_SPEED + slot] = (mysmb_u8)(0U - speed);
            game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
        }
        mysmb_world_move_enemy_horizontally(game, slot);
    }
}

/* ROM LakituAndSpinyHandler.  EnemyFrenzyBuffer is the persistent request
 * produced by InitEnemyFrenzy and by a living Lakitu's MoveLakitu route. */
void mysmb_enemy_step_lakitu_frenzy(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u8 lakitu_slot;
    mysmb_u8 old_x;

    if (game->ram[MYSMB_ENEMY_FRENZY_BUFFER] != 18U ||
        game->ram[MYSMB_FRENZY_ENEMY_TIMER] != 0U) return;
    game->ram[MYSMB_FRENZY_ENEMY_TIMER] = 0x80U;
    lakitu_slot = 5U;
    for (slot = 5U; slot != 0U; ) {
        slot--;
        if (game->ram[MYSMB_ENEMY_ID + slot] == 17U) {
            lakitu_slot = slot;
            break;
        }
    }
    if (lakitu_slot == 5U) {
        game->ram[MYSMB_LAKITU_REAPPEAR_TIMER]++;
        if (game->ram[MYSMB_LAKITU_REAPPEAR_TIMER] < 7U) return;
        for (slot = 5U; slot != 0U; ) {
            slot--;
            if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U) break;
        }
        if (slot == 0U && game->ram[MYSMB_ENEMY_FLAG] != 0U) return;
        game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
        game->ram[MYSMB_ENEMY_ID + slot] = 17U;
        game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
        game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
        game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
        game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 3U;
        old_x = game->ram[MYSMB_SCREEN_RIGHT_X];
        game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(old_x + 0x20U);
        game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[MYSMB_SCREEN_RIGHT_PAGE];
        if (game->ram[MYSMB_ENEMY_X + slot] < old_x) game->ram[MYSMB_ENEMY_PAGE + slot]++;
        game->ram[MYSMB_ENEMY_Y + slot] = 0x20U;
        game->ram[MYSMB_LAKITU_REAPPEAR_TIMER] = 0U;
        return;
    }
    if (game->ram[MYSMB_PLAYER_Y] < 0x2cU ||
        game->ram[MYSMB_ENEMY_STATE + lakitu_slot] != 0U) return;
    for (slot = 5U; slot != 0U; ) {
        slot--;
        if (game->ram[MYSMB_ENEMY_FLAG + slot] == 0U) break;
    }
    if (slot == 0U && game->ram[MYSMB_ENEMY_FLAG] != 0U) return;
    game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[MYSMB_ENEMY_PAGE + lakitu_slot];
    game->ram[MYSMB_ENEMY_X + slot] = game->ram[MYSMB_ENEMY_X + lakitu_slot];
    game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
    game->ram[MYSMB_ENEMY_Y + slot] =
        (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + lakitu_slot] - 8U);
    game->ram[MYSMB_ENEMY_ID + slot] = 18U;
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0xfdU;
    game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 9U;
    game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
    game->ram[MYSMB_ENEMY_STATE + slot] = 5U;
}

/* ROM $bb28 MoveD_EnemyVertically, selected by Enemy_State=$05 for eggs. */
void mysmb_enemy_step_spiny_eggs(struct mysmb_game *game)
{
    mysmb_u8 slot;
    mysmb_u8 x;
    mysmb_u8 page;
    mysmb_u8 row;
    mysmb_u16 address;
    mysmb_u8 tile;

    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_ENEMY_FLAG + slot] != 0U &&
            game->ram[MYSMB_ENEMY_ID + slot] == 18U &&
            game->ram[MYSMB_ENEMY_STATE + slot] == 5U) {
            /* EnemyToBGCollisionDet -> LandEnemyProperly ->
             * ProcEnemyDirection.  A landed egg is reset to ordinary Spiny
             * state before RunNormalEnemies takes ownership next frame. */
            x = (mysmb_u8)(game->ram[MYSMB_ENEMY_X + slot] + 8U);
            page = mysmb_world_collision_page(game->ram[MYSMB_ENEMY_PAGE + slot],
                game->ram[MYSMB_ENEMY_X + slot], x);
            row = (mysmb_u8)(((game->ram[MYSMB_ENEMY_Y + slot] + 0x18U) &
                               0xf0U) - 0x20U);
            address = (mysmb_u16)(((page & 1U) != 0U ?
                                   0x05d0U : 0x0500U) + (x >> 4U) + row);
            tile = address < 0x0800U ? game->ram[address] : 0U;
            if (game->ram[MYSMB_ENEMY_Y + slot] >= 0x25U &&
                tile != 0U && tile != 0x26U && tile != 0xc2U &&
                tile != 0xc3U && tile != 0x5fU && tile != 0x60U &&
                (game->ram[MYSMB_ENEMY_Y + slot] & 0x0fU) <= 0x0cU) {
                game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
                game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
                game->ram[MYSMB_ENEMY_Y + slot] =
                    (mysmb_u8)((game->ram[MYSMB_ENEMY_Y + slot] & 0xf0U) | 8U);
                game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 1U;
                game->ram[MYSMB_ENEMY_X_SPEED + slot] = 8U;
                game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
                continue;
            }
            mysmb_enemy_move_downward(game, slot, 0x20U, 3U);
        }
    }
}

/* ROM InitEnemyFrenzy and InitFlyingCheepCheep.  The area stream holds the
 * persistent $14 controller request; each expiration chooses the first free
 * ordinary slot, just as the original enemy-loader path did. */
void mysmb_enemy_step_flying_cheep_frenzy(struct mysmb_game *game)
{
    static const mysmb_u8 x_position[16] = {
        0x80U, 0x30U, 0x40U, 0x80U, 0x30U, 0x50U, 0x50U, 0x70U,
        0x20U, 0x40U, 0x80U, 0xa0U, 0x70U, 0x40U, 0x90U, 0x68U
    };
    static const mysmb_u8 x_speed[12] = {
        0x0eU, 0x05U, 0x06U, 0x0eU, 0x1cU, 0x20U,
        0x10U, 0x0cU, 0x1eU, 0x22U, 0x18U, 0x14U
    };
    static const mysmb_u8 timer[4] = { 0x10U, 0x60U, 0x20U, 0x48U };
    mysmb_u8 slot;
    mysmb_u8 timer_index;
    mysmb_u8 speed_index;
    mysmb_u8 position_index;
    mysmb_u8 player_speed_bias;
    mysmb_u8 old_x;

    if (game->ram[MYSMB_ENEMY_FRENZY_BUFFER] != 20U ||
        game->ram[MYSMB_FRENZY_ENEMY_TIMER] != 0U) return;
    for (slot = 0U; slot < 5U && game->ram[MYSMB_ENEMY_FLAG + slot] != 0U; ++slot) {}
    if (slot == 5U) return;

    /* SmallBBox -> SetBBox -> InitVStf. */
    game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 9U;
    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
    timer_index = (mysmb_u8)(game->ram[0x07a9U + slot] & 3U);
    game->ram[MYSMB_FRENZY_ENEMY_TIMER] = timer[timer_index];
    if (slot >= (game->ram[MYSMB_SECONDARY_HARD] != 0U ? 4U : 3U)) return;

    position_index = (mysmb_u8)(game->ram[0x07a8U + slot] & 3U);
    player_speed_bias = 0U;
    if (game->ram[MYSMB_PLAYER_X_SPEED] != 0U) {
        player_speed_bias = game->ram[MYSMB_PLAYER_X_SPEED] < 0x19U ? 4U : 8U;
    }
    speed_index = (mysmb_u8)(player_speed_bias + position_index);
    if ((game->ram[0x07a9U + slot] & 3U) != 0U) {
        position_index = (mysmb_u8)(game->ram[0x07aaU + slot] & 0x0fU);
    }
    game->ram[MYSMB_ENEMY_ID + slot] = 20U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0xfbU;
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = x_speed[speed_index];
    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 1U;
    if (game->ram[MYSMB_PLAYER_X_SPEED] == 0U && (position_index & 2U) != 0U) {
        game->ram[MYSMB_ENEMY_X_SPEED + slot] =
            (mysmb_u8)(0U - game->ram[MYSMB_ENEMY_X_SPEED + slot]);
        game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
    }
    old_x = game->ram[MYSMB_PLAYER_X];
    if ((position_index & 2U) != 0U) {
        game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(old_x + x_position[position_index]);
        game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[MYSMB_PLAYER_PAGE];
        if (game->ram[MYSMB_ENEMY_X + slot] < old_x) game->ram[MYSMB_ENEMY_PAGE + slot]++;
    }
    else {
        game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(old_x - x_position[position_index]);
        game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[MYSMB_PLAYER_PAGE];
        if (old_x < x_position[position_index]) game->ram[MYSMB_ENEMY_PAGE + slot]--;
    }
    game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
    game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
    game->ram[MYSMB_ENEMY_Y + slot] = 0xf8U;
}

/* ROM InitBowserFlame.  A living Bowser opens its mouth and places the new
 * flame in the first free ordinary slot. */
void mysmb_enemy_step_bowser_flame_frenzy(struct mysmb_game *game)
{
    static const mysmb_u8 target_y[4] = { 0x90U, 0x80U, 0x70U, 0x90U };
    mysmb_u8 slot;
    mysmb_u8 bowser_slot;
    mysmb_u8 random;

    if (game->ram[MYSMB_ENEMY_FRENZY_BUFFER] != 21U) return;
    bowser_slot = game->ram[0x0368U];
    if (bowser_slot >= 5U || game->ram[MYSMB_ENEMY_FLAG + bowser_slot] == 0U ||
        game->ram[MYSMB_ENEMY_ID + bowser_slot] != 45U) return;
    for (slot = 0U; slot < 5U && game->ram[MYSMB_ENEMY_FLAG + slot] != 0U; ++slot) {}
    if (slot == 5U) return;
    random = (mysmb_u8)(game->ram[0x07a8U + slot] & 3U);
    game->ram[MYSMB_ENEMY_ID + slot] = 21U;
    game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[MYSMB_ENEMY_PAGE + bowser_slot];
    game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(game->ram[MYSMB_ENEMY_X + bowser_slot] - 0x0eU);
    game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + bowser_slot] + 8U);
    game->ram[MYSMB_ENEMY_Y_DUMMY + slot] = random;
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = target_y[random] < game->ram[MYSMB_ENEMY_Y + slot] ?
        0xffU : 1U;
    game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 8U;
    game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
    game->ram[MYSMB_ENEMY_X_FORCE + slot] = 0U;
    game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
    game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
    game->ram[MYSMB_ENEMY_FRENZY_BUFFER] = 0U;
}
/* ROM EndFrenzy.  The stop controller clears every Lakitu, then clears its
 * persistent request and finally removes the controller object itself. */
void mysmb_enemy_end_frenzy(struct mysmb_game *game, mysmb_u8 controller_slot)
{
    mysmb_u8 slot;

    for (slot = 6U; slot != 0U; ) {
        --slot;
        if (game->ram[MYSMB_ENEMY_ID + slot] == 17U) {
            game->ram[MYSMB_ENEMY_FLAG + slot] = 0U;
        }
    }
    game->ram[MYSMB_ENEMY_FRENZY_BUFFER] = 0U;
    if (controller_slot < 6U) game->ram[MYSMB_ENEMY_FLAG + controller_slot] = 0U;
}
