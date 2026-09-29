#include "game/enemy/platform.h"
#include "game/world/world.h"
#include "game/enemy/x_counter.h"
#include "game/enemy/movement.h"

/* $D5FE ChkYPCollision, shared by YMovingPlatform and MoveLargeLiftPlat. */
static void position_large_rider(struct mysmb_game *g, mysmb_u8 slot)
{
    if ((g->ram[0x03a2U + slot] & 0x80U) == 0U)
        mysmb_platform_position_player_vertical(g, slot);
}

/* ROM $D5D3-$D606 YMovingPlatform through ExYPl. Gravity returns
 * X=ObjectOffset; the rest path preserves its incoming enemy slot. */
void mysmb_platform_move_y(struct mysmb_game *g, mysmb_u8 slot)
{
    if ((g->ram[0x00a0U + slot] | g->ram[0x0434U + slot]) == 0U) {
        g->ram[0x0417U + slot] = 0U;
        if (g->ram[0x00cfU + slot] < g->ram[0x0401U + slot]) {
            if ((g->ram[0x0009U] & 7U) == 0U)
                ++g->ram[0x00cfU + slot];
            position_large_rider(g, slot);
            return;
        }
    }
    mysmb_world_move_platform_vertically(g, slot,
        g->ram[0x00cfU + slot] >= g->ram[0x0058U + slot] ? 1U : 0U);
    slot = g->ram[8U];
    position_large_rider(g, slot);
}

/* $D65B-$D670 MoveLiftPlatforms. Only the fractional and low Y bytes
 * change; TimerControl skips motion but not either caller's rider tail. */
static void move_lift(struct mysmb_game *g, mysmb_u8 slot)
{
    mysmb_u16 sum;
    if (g->ram[0x0747U] != 0U) return;
    sum = (mysmb_u16)g->ram[0x0417U + slot] + g->ram[0x0434U + slot];
    g->ram[0x0417U + slot] = (mysmb_u8)sum;
    g->ram[0x00cfU + slot] = (mysmb_u8)(g->ram[0x00cfU + slot] +
        g->ram[0x00a0U + slot] + (sum > 255U ? 1U : 0U));
}

/* $D64F MoveLargeLiftPlat tails into the shared $D5FE collision gate. */
void mysmb_platform_move_large_lift(struct mysmb_game *g, mysmb_u8 slot)
{
    move_lift(g, slot);
    position_large_rider(g, slot);
}

/* $D655 MoveSmallPlatform / $D671 ChkSmallPlatCollision / $D679 ExLiftP.
 * old_y is native compatibility metadata for the uncertified legacy child;
 * the source child argument is the nonzero collision counter. */
void mysmb_platform_move_small(struct mysmb_game *g, mysmb_u8 slot)
{
    mysmb_u8 old_y, collision;
    old_y = g->ram[0x00cfU + slot];
    move_lift(g, slot);
    collision = g->ram[0x03a2U + slot];
    if (collision != 0U)
        mysmb_platform_legacy_position_small(g, slot, collision, old_y);
}

/* $D614-$D630 PositionPlayerOnHPlat / PPHSubt / SetPVar / ExXMP.
 * ADC of a negative byte supplies the carry consumed by SBC #0. */
static void position_player_horizontal(struct mysmb_game *g, mysmb_u8 slot)
{
    mysmb_u16 sum;
    mysmb_u8 delta, carry;
    delta = g->ram[0U];
    sum = (mysmb_u16)g->ram[0x0086U] + delta;
    carry = sum > 255U ? 1U : 0U;
    g->ram[0x0086U] = (mysmb_u8)sum;
    if ((delta & 0x80U) != 0U)
        g->ram[0x006dU] = (mysmb_u8)(g->ram[0x006dU] - (1U - carry));
    else
        g->ram[0x006dU] = (mysmb_u8)(g->ram[0x006dU] + carry);
    g->ram[0x03a1U] = delta;
    mysmb_platform_position_player_vertical(g, slot);
}

/* $D607 XMovingPlatform: original counter, displacement and rider order. */
void mysmb_platform_move_x(struct mysmb_game *g, mysmb_u8 slot)
{
    mysmb_enemy_x_counter_platform(g, slot, 0x0eU);
    mysmb_enemy_move_with_x_counters(g, slot);
    slot = g->ram[8U];
    if ((g->ram[0x03a2U + slot] & 0x80U) == 0U)
        position_player_horizontal(g, slot);
}

/* $D631-$D63C DropPlatform / ExDPl. */
void mysmb_platform_move_drop(struct mysmb_game *g, mysmb_u8 slot)
{
    if ((g->ram[0x03a2U + slot] & 0x80U) != 0U) return;
    mysmb_enemy_move_drop_platform(g, slot);
    mysmb_platform_position_player_vertical(g, g->ram[8U]);
}

/* $D63D-$D64E RightPlatform / ExRPl. Acceleration affects the next move. */
void mysmb_platform_move_right(struct mysmb_game *g, mysmb_u8 slot)
{
    g->ram[0U] = mysmb_world_move_enemy_horizontally(g, slot);
    slot = g->ram[8U];
    if ((g->ram[0x03a2U + slot] & 0x80U) != 0U) return;
    g->ram[0x0058U + slot] = 0x10U;
    position_player_horizontal(g, slot);
}
