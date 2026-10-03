#include "game/enemy/init.h"
#include "game/objects.h"
#include "game/enemy/init_targets.h"

enum {
    MYSMB_AREA_SCREEN_RIGHT_PAGE = 0x071bU,
    MYSMB_AREA_SCREEN_RIGHT_X = 0x071dU,
    MYSMB_AREA_POINTER = 0x0750U,
    MYSMB_AREA_ENTRANCE_PAGE = 0x0751U,
    MYSMB_AREA_TYPE = 0x074eU,
    MYSMB_ENEMY_DATA_LOW = 0x00e9U,
    MYSMB_ENEMY_DATA_HIGH = 0x00eaU,
    MYSMB_WORLD_NUMBER = 0x075fU,
    MYSMB_ENEMY_DATA_OFFSET = 0x0739U,
    MYSMB_ENEMY_OBJECT_PAGE = 0x073aU,
    MYSMB_ENEMY_OBJECT_PAGE_SELECT = 0x073bU,
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
    MYSMB_ENEMY_X_FORCE = 0x0401U,
    MYSMB_ENEMY_Y_DUMMY = 0x0417U,
    MYSMB_ENEMY_Y_FORCE = 0x0434U,
    MYSMB_ENEMY_BOUND_BOX = 0x049aU,
    MYSMB_FIREBAR_SPIN_SPEED = 0x0388U,
    MYSMB_FIREBAR_SPIN_DIRECTION = 0x0034U,
    MYSMB_BOWSER_BODY_CONTROLS = 0x0363U,
    MYSMB_BOWSER_FEET_TIMER = 0x0364U,
    MYSMB_BOWSER_MOVE_SPEED = 0x0365U,
    MYSMB_BOWSER_ORIGIN_X = 0x0366U,
    MYSMB_BRIDGE_COLLAPSE_OFFSET = 0x0369U,
    MYSMB_BOWSER_BREATH_TIMER = 0x0790U,
    MYSMB_BOWSER_FRONT_SLOT = 0x0368U,
    MYSMB_BOWSER_HIT_POINTS = 0x0483U,
    MYSMB_ENEMY_FRAME_TIMER = 0x078aU,
    MYSMB_BALANCE_PLATFORM_ALIGNMENT = 0x03a0U,
    MYSMB_PLATFORM_COLLISION_FLAG = 0x03a2U,
    MYSMB_PLATFORM_TOP_Y = 0x0401U,
    MYSMB_PLATFORM_CENTER_Y = 0x0058U,
    MYSMB_PRIMARY_HARD = 0x076aU,
    MYSMB_SECONDARY_HARD = 0x06ccU,
    MYSMB_ENEMY_FRENZY_BUFFER = 0x06cbU
};

/* ROM $C7DB SetBBox2: shared one-write tail. */
static void mysmb_enemy_init_box_only(struct mysmb_game *game, mysmb_u8 slot,
                                     mysmb_u8 box)
{
    game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = box;
}

/* ROM $C787 InitPiranhaPlant, followed by SetBBox2. */
void mysmb_enemy_init_piranha_plant(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = 1U;
    game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = game->ram[MYSMB_ENEMY_Y + slot];
    game->ram[MYSMB_ENEMY_Y_DUMMY + slot] =
        (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - 0x18U);
    mysmb_enemy_init_box_only(game, slot, 9U);
}
/* ROM $C30C/$C326: indexed by original primary/secondary hard-mode state. */
static const mysmb_u8 normal_x_speed[2] = { 0xf8U, 0xf4U };
static const mysmb_u8 hammer_walking_timer[2] = { 0x80U, 0x50U };

/* ROM $C363 InitVStf. */
void mysmb_enemy_init_vertical_state(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0U;
}

/* ROM $C35C SetBBox, then InitVStf. */
static void mysmb_enemy_init_box(struct mysmb_game *game, mysmb_u8 slot, mysmb_u8 box)
{
    game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = box;
    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
    mysmb_enemy_init_vertical_state(game, slot);
}

/* ROM $C35A TallBBox, selecting the shared SetBBox tail. */
static void mysmb_enemy_init_tall_box(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_init_box(game, slot, 3U);
}

/* ROM $C346 SmallBBox, selecting the shared SetBBox tail. */
void mysmb_enemy_init_small_box(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_init_box(game, slot, 9U);
}

/* ROM $C319 SetESpd, then TallBBox. */
static void mysmb_enemy_init_speed(struct mysmb_game *game, mysmb_u8 slot, mysmb_u8 speed)
{
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = speed;
    mysmb_enemy_init_tall_box(game, slot);
}

/* ROM $C30E InitNormalEnemy/GetESpd: no flag or state write. */
void mysmb_enemy_init_normal(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 index;
    index = game->ram[MYSMB_PRIMARY_HARD] != 0U ? 1U : 0U;
    mysmb_enemy_init_speed(game, slot, normal_x_speed[index]);
}

/* ROM $C7D9 TallBBox2, selecting the shared SetBBox2 tail. */
static void mysmb_enemy_init_tall_box_only(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_init_box_only(game, slot, 3U);
}

/* Original InitRedKoopa entry $C31E. */
void mysmb_enemy_init_red_koopa(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_init_normal(game, slot);
    game->ram[MYSMB_ENEMY_STATE + slot] = 1U;
}

/* Original target entry $C2F1. */
void mysmb_enemy_init_goomba(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_init_normal(game, slot);
    mysmb_enemy_init_small_box(game, slot);
}

/* Original target entry $C328. */
void mysmb_enemy_init_hammer_bro(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 index;
    game->ram[0x03a2U + slot] = 0U;
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
    index = game->ram[MYSMB_SECONDARY_HARD];
    /* Source producers constrain SecondaryHardMode to zero or one. */
    game->ram[0x0796U + slot] = hammer_walking_timer[index];
    mysmb_enemy_init_box(game, slot, 0x0bU);
}

/* Original target entry $C36B. */
void mysmb_enemy_init_bullet_bill(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
    game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 9U;
}

/* Original target entry $C375. */
void mysmb_enemy_init_cheep_cheep(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_init_small_box(game, slot);
    game->ram[MYSMB_ENEMY_X_SPEED + slot] =
        (mysmb_u8)(game->ram[0x07a7U + slot] & 0x10U);
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = game->ram[MYSMB_ENEMY_Y + slot];
}

/* Original target entry $C2F7. */
void mysmb_enemy_init_podoboo(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_ENEMY_Y_HIGH + slot] = 2U;
    game->ram[MYSMB_ENEMY_Y + slot] = 2U;
    game->ram[0x0796U + slot] = 1U;
    game->ram[MYSMB_ENEMY_STATE + slot] = 0U;
    mysmb_enemy_init_small_box(game, slot);
}

/* Original target entry $C342. */
void mysmb_enemy_init_bloober(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
    mysmb_enemy_init_small_box(game, slot);
}

/* ROM $C7D1 InitJumpGPTroopa, followed by TallBBox2. */
void mysmb_enemy_init_jump_green_ptroopa(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 2U;
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0xf8U;
    mysmb_enemy_init_tall_box_only(game, slot);
}

/* Original target entry $C34A. */
void mysmb_enemy_init_red_ptroopa(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 adder;
    adder = game->ram[MYSMB_ENEMY_Y + slot] < 0x80U ? 0x30U : 0xe0U;
    game->ram[MYSMB_ENEMY_X_FORCE + slot] = game->ram[MYSMB_ENEMY_Y + slot];
    /* The initializer vector's ASL leaves carry clear for all declared IDs. */
    game->ram[MYSMB_ENEMY_X_SPEED + slot] =
        (mysmb_u8)(adder + game->ram[MYSMB_ENEMY_Y + slot]);
    mysmb_enemy_init_tall_box(game, slot);
}

/* Original target entry $C33D. */
void mysmb_enemy_init_horizontal_fly_swim(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_init_speed(game, slot, 0U);
}

/* ROM $C38A SetupLakitu is also a direct entry for the frenzy producer. */
void mysmb_enemy_setup_lakitu(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[0x06d1U] = 0U;
    mysmb_enemy_init_horizontal_fly_swim(game, slot);
    mysmb_enemy_init_tall_box_only(game, slot);
}

/* ROM $C385 InitLakitu / $C395 KillLakitu. */
void mysmb_enemy_init_lakitu(struct mysmb_game *game, mysmb_u8 slot)
{
    if (game->ram[MYSMB_ENEMY_FRENZY_BUFFER] != 0U) {
        mysmb_objects_erase_enemy(game, slot);
        return;
    }
    mysmb_enemy_setup_lakitu(game, slot);
}

/* ROM $C575-$C59C DuplicateEnemyObj / FSLoop / FlmEx. The source uses
 * byte-sized Y and scans RAM until zero, without a six-slot clamp. */
void mysmb_enemy_duplicate_object(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 duplicate;
    duplicate = 0U;
    while (game->ram[MYSMB_ENEMY_FLAG + duplicate] != 0U)
        duplicate = (mysmb_u8)(duplicate + 1U);
    game->ram[0x06cfU] = duplicate;
    game->ram[MYSMB_ENEMY_FLAG + duplicate] = (mysmb_u8)(slot | 0x80U);
    /* Source X operands are zero-page indexed; Y destinations are absolute. */
    game->ram[MYSMB_ENEMY_PAGE + duplicate] =
        game->ram[(mysmb_u8)(MYSMB_ENEMY_PAGE + slot)];
    game->ram[MYSMB_ENEMY_X + duplicate] =
        game->ram[(mysmb_u8)(MYSMB_ENEMY_X + slot)];
    game->ram[(mysmb_u8)(MYSMB_ENEMY_FLAG + slot)] = 1U;
    game->ram[MYSMB_ENEMY_Y_HIGH + duplicate] = 1U;
    game->ram[MYSMB_ENEMY_Y + duplicate] =
        game->ram[(mysmb_u8)(MYSMB_ENEMY_Y + slot)];
}

/* ROM $C459/$C45C entries. Long falls through short after the shared child. */
void mysmb_enemy_init_firebar_entry(struct mysmb_game *game, mysmb_u8 slot, mysmb_u8 long_entry)
{
    static const mysmb_u8 spin_speed[5] = { 0x28U, 0x38U, 0x28U, 0x38U, 0x28U };
    static const mysmb_u8 spin_direction[5] = { 0U, 0U, 0x10U, 0x10U, 0U };
    mysmb_u8 old_x;
    mysmb_u8 index;
    if (long_entry != 0U) mysmb_enemy_duplicate_object(game, slot);
    /* FirebarSpinState_Low aliases Enemy_X_Speed. Do not reset high spin
     * state, vertical force, actor state or direction through generic defaults. */
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
    index = (mysmb_u8)(game->ram[MYSMB_ENEMY_ID + slot] - 0x1bU);
    game->ram[MYSMB_FIREBAR_SPIN_SPEED + slot] = spin_speed[index];
    game->ram[MYSMB_FIREBAR_SPIN_DIRECTION + slot] = spin_direction[index];
    game->ram[MYSMB_ENEMY_Y + slot] = (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] + 4U);
    old_x = game->ram[MYSMB_ENEMY_X + slot];
    game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)(old_x + 4U);
    if (game->ram[MYSMB_ENEMY_X + slot] < old_x) game->ram[MYSMB_ENEMY_PAGE + slot]++;
    mysmb_enemy_init_tall_box_only(game, slot);
}

/* ROM $C86B/$C86E: low/high addends consumed by PosPlatform. */
static const mysmb_u8 platform_position_low[3] = { 8U, 12U, 0xf8U };
static const mysmb_u8 platform_position_high[3] = { 0U, 0U, 0xffU };

/* ROM $C871 PosPlatform: the low-byte carry feeds the page addition. */
static void mysmb_enemy_position_platform(struct mysmb_game *game,
                                          mysmb_u8 slot, mysmb_u8 index)
{
    mysmb_u16 sum;
    sum = (mysmb_u16)(game->ram[MYSMB_ENEMY_X + slot] +
                     platform_position_low[index]);
    game->ram[MYSMB_ENEMY_X + slot] = (mysmb_u8)sum;
    game->ram[MYSMB_ENEMY_PAGE + slot] = (mysmb_u8)(
        game->ram[MYSMB_ENEMY_PAGE + slot] + platform_position_high[index] +
        (sum >> 8U));
}

/* ROM $C82B SPBBox / CasPBB: large platform box without other writes. */
static void mysmb_enemy_platform_box(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_ENEMY_BOUND_BOX + slot] =
        game->ram[MYSMB_AREA_TYPE] == 3U ||
        game->ram[MYSMB_SECONDARY_HARD] != 0U ? 5U : 6U;
}

/* ROM $C828 CommonPlatCode; original InitVStf is its only child. */
static void mysmb_enemy_common_platform(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_init_vertical_state(game, slot);
    mysmb_enemy_platform_box(game, slot);
}

/* ROM $C803 InitDropPlatform, also the balance initializer's fallthrough. */
void mysmb_enemy_init_drop_platform(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_PLATFORM_COLLISION_FLAG + slot] = 0xffU;
    mysmb_enemy_common_platform(game, slot);
}

/* ROM $C7DF InitBalPlatform / AlignP / SetBPA. */
void mysmb_enemy_init_balance_platform(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 alignment;
    game->ram[MYSMB_ENEMY_Y + slot] =
        (mysmb_u8)(game->ram[MYSMB_ENEMY_Y + slot] - 2U);
    if (game->ram[MYSMB_SECONDARY_HARD] == 0U)
        mysmb_enemy_position_platform(game, slot, 2U);
    alignment = game->ram[MYSMB_BALANCE_PLATFORM_ALIGNMENT];
    game->ram[MYSMB_ENEMY_STATE + slot] = alignment;
    game->ram[MYSMB_BALANCE_PLATFORM_ALIGNMENT] =
        alignment < 0x80U ? 0xffU : slot;
    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 0U;
    mysmb_enemy_position_platform(game, slot, 0U);
    mysmb_enemy_init_drop_platform(game, slot);
}

/* ROM $C80B InitHoriPlatform: XMoveSecondaryCounter aliases X speed. */
void mysmb_enemy_init_horizontal_platform(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_ENEMY_X_SPEED + slot] = 0U;
    mysmb_enemy_common_platform(game, slot);
}

/* ROM $C812 InitVertPlatform / SetYO; Enemy_Y_Position is preserved. */
void mysmb_enemy_init_vertical_platform(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 y;
    y = game->ram[MYSMB_ENEMY_Y + slot];
    game->ram[MYSMB_PLATFORM_TOP_Y + slot] =
        y < 0x80U ? y : (mysmb_u8)(0U - y);
    game->ram[MYSMB_PLATFORM_CENTER_Y + slot] =
        (mysmb_u8)(y + (y < 0x80U ? 0x40U : 0xc0U));
    mysmb_enemy_common_platform(game, slot);
}

/* ROM $C860 CommonSmallLift: position before selecting box four. */
static void mysmb_enemy_common_small_lift(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_position_platform(game, slot, 1U);
    game->ram[MYSMB_ENEMY_BOUND_BOX + slot] = 4U;
}

/* ROM $C84B PlatLiftUp. */
void mysmb_enemy_init_small_lift_up(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0x10U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0xffU;
    mysmb_enemy_common_small_lift(game, slot);
}

/* ROM $C857 PlatLiftDown. */
void mysmb_enemy_init_small_lift_down(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_ENEMY_Y_FORCE + slot] = 0xf0U;
    game->ram[MYSMB_ENEMY_Y_SPEED + slot] = 0U;
    mysmb_enemy_common_small_lift(game, slot);
}

/* ROM $C83F LargeLiftUp / $C848 LargeLiftBBox. */
void mysmb_enemy_init_large_lift_up(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_init_small_lift_up(game, slot);
    mysmb_enemy_platform_box(game, slot);
}

/* ROM $C845 LargeLiftDown, falling through LargeLiftBBox. */
void mysmb_enemy_init_large_lift_down(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_init_small_lift_down(game, slot);
    mysmb_enemy_platform_box(game, slot);
}

/* ROM $C549 InitBowser: preserve all fields absent from this entry. */
void mysmb_enemy_init_bowser(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_enemy_duplicate_object(game, slot);
    game->ram[MYSMB_BOWSER_FRONT_SLOT] = slot;
    game->ram[MYSMB_BOWSER_BODY_CONTROLS] = 0U;
    game->ram[MYSMB_BRIDGE_COLLAPSE_OFFSET] = 0U;
    game->ram[MYSMB_BOWSER_ORIGIN_X] = game->ram[MYSMB_ENEMY_X + slot];
    game->ram[MYSMB_BOWSER_BREATH_TIMER] = 0xdfU;
    game->ram[MYSMB_ENEMY_MOVING_DIRECTION + slot] = 0xdfU;
    game->ram[MYSMB_BOWSER_FEET_TIMER] = 0x20U;
    game->ram[MYSMB_ENEMY_FRAME_TIMER + slot] = 0x20U;
    game->ram[MYSMB_BOWSER_HIT_POINTS] = 5U;
    game->ram[MYSMB_BOWSER_MOVE_SPEED] = 2U;
}

/* Original target $C307. */
void mysmb_enemy_init_retainer(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[MYSMB_ENEMY_Y + slot] = 0xb8U;
}
