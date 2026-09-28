#include "game/enemy/actor_slots.h"
#include "game/enemy/frenzy.h"
#include "game/enemy/movement.h"
#include "game/enemy/init.h"
#include "game/enemy/init_targets.h"
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
    MYSMB_ENEMY_Y_DUMMY = 0x0417U,
    MYSMB_AREA_TYPE = 0x074eU,
    MYSMB_WORLD_NUMBER = 0x075fU,
    MYSMB_BITM_FILTER = 0x06ddU,
    MYSMB_SQUARE2_SOUND = 0x00feU,
    MYSMB_FIREWORKS_COUNTER = 0x06d7U
};
/* ROM $C7AB frenzy vector: provenance data for JumpEngine scratch only. */
static const mysmb_u16 frenzy_targets[6] = {
    0xc3a4U, 0xc7b7U, 0xc4a8U, 0xc5a3U, 0xc63dU, 0xc69cU
};

/* ROM $C7A0 InitEnemyFrenzy. All declared selectors are $12 through $17. */
void mysmb_enemy_init_frenzy(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 id;
    mysmb_u16 target;
    id = game->ram[MYSMB_ENEMY_ID + slot];
    game->ram[MYSMB_ENEMY_FRENZY_BUFFER] = id;
    target = frenzy_targets[(mysmb_u8)(id - 0x12U)];
    game->ram[4U] = 0xaaU;
    game->ram[5U] = 0xc7U;
    game->ram[6U] = (mysmb_u8)target;
    game->ram[7U] = (mysmb_u8)(target >> 8U);
    switch (id) {
    case 0x12U:
        mysmb_enemy_init_lakitu_spiny_frenzy(game, slot);
        break;
    case 0x13U: /* NoFrenzyCode: original RTS without further writes. */
        break;
    case 0x14U:
        mysmb_enemy_init_flying_cheep_frenzy(game, slot);
        break;
    case 0x15U:
        mysmb_enemy_init_bowser_flame_frenzy(game, slot);
        break;
    case 0x16U:
        mysmb_enemy_init_fireworks_frenzy(game, slot);
        break;
    case 0x17U:
        mysmb_enemy_step_bullet_bill_cheep_frenzy(game, slot);
        break;
    default:
        break;
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_enemy_step_lakitus(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot) {
        if (game->ram[MYSMB_ENEMY_FLAG + slot] != 0U &&
            game->ram[MYSMB_ENEMY_ID + slot] == 17U)
            mysmb_enemy_step_lakitus_slot(game, slot);
    }
}

/* ROM LakituAndSpinyHandler.  InitEnemyFrenzy enters with the current
 * ObjectOffset.  It only searches for a free slot while recreating Lakitu;
 * CreateSpiny writes back through that original ObjectOffset. */
void mysmb_enemy_init_lakitu_spiny_frenzy(struct mysmb_game *game,
                                          mysmb_u8 current_slot)
{
    static const mysmb_u8 difference_adjustment[12] = {
        0x26U, 0x2cU, 0x32U, 0x38U,
        0x20U, 0x22U, 0x24U, 0x26U,
        0x13U, 0x14U, 0x15U, 0x16U
    };
    mysmb_u8 slot;
    mysmb_u8 lakitu_slot;
    mysmb_u8 seed;
    mysmb_u8 speed;

    if (game->ram[MYSMB_FRENZY_ENEMY_TIMER] != 0U) return;
    if (current_slot >= 5U) return;
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
        mysmb_enemy_setup_lakitu(game, slot);
        mysmb_enemy_put_at_right_extent(game, slot, 0x20U);
        return;
    }
    if (game->ram[MYSMB_PLAYER_Y] < 0x2cU ||
        game->ram[MYSMB_ENEMY_STATE + lakitu_slot] != 0U) return;
    slot = current_slot;
    game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[MYSMB_ENEMY_PAGE + lakitu_slot];
    game->ram[MYSMB_ENEMY_X + slot] = game->ram[MYSMB_ENEMY_X + lakitu_slot];
    game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
    game->ram[MYSMB_ENEMY_Y + slot] =
        (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + lakitu_slot] - 8U);
    seed = (mysmb_u8)(game->ram[0x07a7U + slot] & 3U);
    game->ram[3U] = difference_adjustment[seed];
    game->ram[2U] = difference_adjustment[seed + 4U];
    game->ram[1U] = difference_adjustment[seed + 8U];
    /* DifLoop uses X for the table loop, then reloads ObjectOffset. */
    slot = game->ram[0x0008U];
    speed = mysmb_enemy_player_lakitu_difference(game, slot);
    if (game->ram[MYSMB_PLAYER_X_SPEED] < 8U &&
        (game->ram[0x07a8U + slot] & 3U) != 0U) {
        speed = (mysmb_u8)(0U - speed);
    }
    /* SetSpSpd calls SmallBBox, whose InitVStf tail returns A = zero.
     * This intentionally discards the preceding computed speed, as in ROM. */
    (void)speed;
    mysmb_enemy_init_small_box(game, slot);
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 1U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0xfdU;
    game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
    game->ram[MYSMB_ENEMY_STATE + slot] = 5U;
}

/* ROM $bb28 MoveD_EnemyVertically, selected by Enemy_State=$05 for eggs. */
void mysmb_enemy_step_spiny_eggs_slot(struct mysmb_game *game, mysmb_u8 slot)
{
    struct mysmb_enemy_terrain terrain;
    mysmb_u8 tile;

    if (game->ram[MYSMB_ENEMY_FLAG + slot] != 0U &&
        game->ram[MYSMB_ENEMY_ID + slot] == 18U &&
        game->ram[MYSMB_ENEMY_STATE + slot] == 5U) {
        /* EnemyToBGCollisionDet -> LandEnemyProperly ->
         * ProcEnemyDirection.  A landed egg is reset to ordinary Spiny
         * state before RunNormalEnemies takes ownership next frame. */
        tile = mysmb_world_query_enemy_block(game, slot, 0x15U, 0U,
                                               &terrain) != 0U ?
            terrain.metatile : 0U;
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
            return;
        }
        mysmb_enemy_move_downward(game, slot, 0x20U, 3U);
    }
}

/* Temporary bulk caller while the engine vector is migrated. */
void mysmb_enemy_step_spiny_eggs(struct mysmb_game *game)
{
    mysmb_u8 slot;
    for (slot = 0U; slot < 5U; ++slot)
        mysmb_enemy_step_spiny_eggs_slot(game, slot);
}

/* ROM InitEnemyFrenzy -> InitFlyingCheepCheep.  It receives the current
 * ObjectOffset directly from CheckpointEnemyID; the stream owns retries
 * through CheckFrenzyBuffer and never performs a fabricated slot scan. */
void mysmb_enemy_init_flying_cheep_frenzy(struct mysmb_game *game, mysmb_u8 slot)
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
    mysmb_u8 timer_index;
    mysmb_u8 speed_index;
    mysmb_u8 position_index;
    mysmb_u8 player_speed_bias;
    mysmb_u8 old_x;

    if (game->ram[MYSMB_FRENZY_ENEMY_TIMER] != 0U) return;
    mysmb_enemy_init_small_box(game, slot);
    timer_index = (mysmb_u8)(game->ram[0x07a8U + slot] & 3U);
    game->ram[MYSMB_FRENZY_ENEMY_TIMER] = timer[timer_index];
    game->ram[0U] = game->ram[MYSMB_SECONDARY_HARD] != 0U ? 4U : 3U;
    if (slot >= game->ram[0U]) return;

    game->ram[0U] = (mysmb_u8)(game->ram[0x07a7U + slot] & 3U);
    game->ram[1U] = game->ram[0U];
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0xfbU;
    player_speed_bias = 0U;
    if (game->ram[MYSMB_PLAYER_X_SPEED] != 0U) {
        player_speed_bias = game->ram[MYSMB_PLAYER_X_SPEED] < 0x19U ? 4U : 8U;
    }
    game->ram[0U] = (mysmb_u8)(player_speed_bias + game->ram[0U]);
    if ((game->ram[0x07a8U + slot] & 3U) != 0U) {
        game->ram[0U] = (mysmb_u8)(game->ram[0x07a9U + slot] & 0x0fU);
    }
    speed_index = (mysmb_u8)(player_speed_bias + game->ram[1U]);
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = x_speed[speed_index];
    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 1U;
    /* RSeed leaves Y at the speed-table index. Only the stationary-player
     * path reloads Y from scratch $00 before the D2XPos1 position lookup. */
    position_index = game->ram[MYSMB_PLAYER_X_SPEED] == 0U ?
        game->ram[0U] : speed_index;
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

/* Existing FinishFlame tail, shared by both positioning entries. */
static void mysmb_enemy_finish_flame(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 8U;
    game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
    game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
    game->ram[MYSMB_ENEMY_X_FORCE + slot] = 0U;
    game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
}

/* ROM $C5D8: extracted existing positioning/finish body; child credit separate. */
void mysmb_enemy_put_at_right_extent(struct mysmb_game *game, mysmb_u8 slot,
                                    mysmb_u8 y)
{
    mysmb_u8 old_x;
    old_x = game->ram[MYSMB_SCREEN_RIGHT_X];
    game->ram[MYSMB_ENEMY_Y + slot] = y;
    game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(old_x + 0x20U);
    game->ram[MYSMB_ENEMY_PAGE + slot] =
        (mysmb_u8)(game->ram[MYSMB_SCREEN_RIGHT_PAGE] +
        (game->ram[MYSMB_ENEMY_X + slot] < old_x ? 1U : 0U));
    mysmb_enemy_finish_flame(game, slot);
}

/* ROM FlameTimerData / SetFlameTimer / ExFl. Original initialization and
 * this masked increment constrain the incoming timer counter to 0..7. */
mysmb_u8 mysmb_enemy_set_flame_timer(struct mysmb_game *game)
{
    static const mysmb_u8 timer_data[8] = {
        0xbfU, 0x40U, 0xbfU, 0xbfU, 0xbfU, 0x40U, 0x40U, 0xbfU
    };
    mysmb_u8 index;
    index = game->ram[0x0367U];
    game->ram[0x0367U] = (mysmb_u8)((index + 1U) & 7U);
    return timer_data[index];
}

/* ROM InitEnemyFrenzy -> InitBowserFlame.  The controller is the current
 * ObjectOffset supplied by CheckFrenzyBuffer, never a frame-root free-slot
 * search. */
void mysmb_enemy_init_bowser_flame_frenzy(struct mysmb_game *game,
                                          mysmb_u8 slot)
{
    static const mysmb_u8 target_y[4] = { 0x90U, 0x80U, 0x70U, 0x90U };
    static const mysmb_u8 y_force[2] = { 0xffU, 1U };
    mysmb_u8 bowser_slot;
    mysmb_u8 random;

    if (game->ram[MYSMB_FRENZY_ENEMY_TIMER] != 0U) return;
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
    game->ram[0x00fdU] |= 0x02U;
    bowser_slot = game->ram[0x0368U];
    if (game->ram[MYSMB_ENEMY_ID + bowser_slot] == 45U) {
        game->ram[MYSMB_ENEMY_X + slot] =
            (mysmb_u8)(game->ram[MYSMB_ENEMY_X + bowser_slot] - 0x0eU);
        game->ram[MYSMB_ENEMY_PAGE + slot] = game->ram[MYSMB_ENEMY_PAGE + bowser_slot];
        game->ram[MYSMB_ENEMY_Y + slot] =
            (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + bowser_slot] + 8U);
        random = (mysmb_u8)(game->ram[0x07a7U + slot] & 3U);
        game->ram[MYSMB_ENEMY_Y_DUMMY + slot] = random;
        game->ram[MYSMB_ENEMY_Y_FORCE + slot] =
            y_force[target_y[random] < game->ram[MYSMB_ENEMY_Y + slot] ? 0U : 1U];
        game->ram[MYSMB_ENEMY_FRENZY_BUFFER] = 0U;
    }
    else {
        game->ram[MYSMB_FRENZY_ENEMY_TIMER] =
            (mysmb_u8)(mysmb_enemy_set_flame_timer(game) + 0x20U);
        if (game->ram[0x06ccU] != 0U) {
            game->ram[MYSMB_FRENZY_ENEMY_TIMER] =
                (mysmb_u8)(game->ram[MYSMB_FRENZY_ENEMY_TIMER] - 0x10U);
        }
        random = (mysmb_u8)(game->ram[0x07a7U + slot] & 3U);
        game->ram[MYSMB_ENEMY_Y_DUMMY + slot] = random;
        mysmb_enemy_put_at_right_extent(game, slot, target_y[random]);
        return;
    }
    mysmb_enemy_finish_flame(game, slot);
}

/* ROM $C7B8 EndFrenzy: set every Lakitu state, including inactive slots,
 * then clear the request and only the controller's own flag. */
void mysmb_enemy_end_frenzy(struct mysmb_game *game, mysmb_u8 controller_slot)
{
    mysmb_u8 slot;

    for (slot = 6U; slot != 0U; ) {
        --slot;
        if (game->ram[MYSMB_ENEMY_ID + slot] == 17U) {
            game->ram[MYSMB_ENEMY_STATE + slot] = 1U;
        }
    }
    game->ram[MYSMB_ENEMY_FRENZY_BUFFER] = 0U;
    game->ram[MYSMB_ENEMY_FLAG + controller_slot] = 0U;
}
/* ROM BulletBillCheepCheep.  The controller slot becomes the spawned actor;
 * water picks a unique height bit and land refuses a second frenzy bill. */
void mysmb_enemy_step_bullet_bill_cheep_frenzy(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 masks[8] = { 1U,2U,4U,8U,16U,32U,64U,128U };
    static const mysmb_u8 heights[8] = { 0x40U,0x30U,0x90U,0x50U,0x20U,0x60U,0xa0U,0x70U };
    static const mysmb_u8 swim_ids[2] = { 0x0aU, 0x0bU };
    mysmb_u8 index;
    mysmb_u8 scan;

    if (game->ram[MYSMB_FRENZY_ENEMY_TIMER] != 0U) return;
    if (game->ram[MYSMB_AREA_TYPE] != 0U) {
        for (scan = 0U; scan < 5U; ++scan) {
            if (game->ram[MYSMB_ENEMY_FLAG + scan] != 0U &&
                game->ram[MYSMB_ENEMY_ID + scan] == 8U) return;
        }
        game->ram[MYSMB_SQUARE2_SOUND] |= 0x08U;
        game->ram[MYSMB_ENEMY_ID + slot] = 8U;
    }
    else {
        if (slot >= 3U) return;
        index = game->ram[0x07a7U + slot] >= 0xaaU ? 1U : 0U;
        if (game->ram[MYSMB_WORLD_NUMBER] != 1U) ++index;
        game->ram[MYSMB_ENEMY_ID + slot] = swim_ids[index & 1U];
    }
    if (game->ram[MYSMB_BITM_FILTER] == 0xffU)
        game->ram[MYSMB_BITM_FILTER] = 0U;
    index = (mysmb_u8)(game->ram[0x07a7U + slot] & 7U);
    while ((game->ram[MYSMB_BITM_FILTER] & masks[index]) != 0U)
        index = (mysmb_u8)((index + 1U) & 7U);
    game->ram[MYSMB_BITM_FILTER] |= masks[index];
    mysmb_enemy_put_at_right_extent(game, slot, heights[index]);
    /* FinishFlame's final LSR leaves A = zero before the checkpoint tail. */
    game->ram[MYSMB_ENEMY_Y_DUMMY + slot] = 0U;
    game->ram[MYSMB_FRENZY_ENEMY_TIMER] = 0x20U;
    mysmb_enemy_checkpoint_loaded(game, slot);
}

/* ROM InitEnemyFrenzy -> InitFireworks. */
void mysmb_enemy_init_fireworks_frenzy(struct mysmb_game *game, mysmb_u8 slot)
{
    static const mysmb_u8 x_data[6] = { 0U, 0x30U, 0x60U, 0x60U, 0U, 0x20U };
    static const mysmb_u8 y_data[6] = { 0x60U, 0x40U, 0x70U, 0x40U, 0x60U, 0x30U };
    mysmb_u8 star;
    mysmb_u8 index;
    mysmb_u8 x_before;

    if (game->ram[MYSMB_FRENZY_ENEMY_TIMER] != 0U) return;
    game->ram[MYSMB_FRENZY_ENEMY_TIMER] = 0x20U;
    game->ram[MYSMB_FIREWORKS_COUNTER]--;
    star = 6U;
    do {
        star = (mysmb_u8)(star - 1U);
    } while (game->ram[MYSMB_ENEMY_ID + star] != 49U);
    x_before = (mysmb_u8)(game->ram[MYSMB_ENEMY_X + star] - 0x30U);
    game->ram[0U] = (mysmb_u8)(game->ram[MYSMB_ENEMY_PAGE + star] -
        (game->ram[MYSMB_ENEMY_X + star] < 0x30U ? 1U : 0U));
    index = (mysmb_u8)(game->ram[MYSMB_FIREWORKS_COUNTER] +
                       game->ram[MYSMB_ENEMY_STATE + star]);
    game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(x_before + x_data[index]);
    game->ram[MYSMB_ENEMY_PAGE + slot] = (mysmb_u8)(game->ram[0U] +
        (game->ram[MYSMB_ENEMY_X + slot] < x_before ? 1U : 0U));
    game->ram[MYSMB_ENEMY_Y + slot] = y_data[index];
    game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 1U;
    game->ram[MYSMB_ENEMY_FLAG + slot] = 1U;
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 8U;
}
