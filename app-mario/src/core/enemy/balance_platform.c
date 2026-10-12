#include "core/enemy/platform.h"
#include "core/enemy/init_targets.h"
#include "core/enemy/movement.h"
#include "core/objects.h"
#include "core/world/world.h"

/* $D5B1 StopPlatforms: InitVStf preserves Y and returns A=0. */
static void stop_platforms(struct mysmb_game *g, mysmb_u8 slot, mysmb_u8 peer)
{
    mysmb_enemy_init_vertical_state(g, slot);
    g->ram[0x00a0U + peer] = 0U;
    g->ram[0x0434U + peer] = 0U;
}

/* $D541-$D597 SetupPlatformRope. In normal difficulty the second CLC
 * discards the first addition's carry, exactly as the source does. */
static mysmb_u8 setup_rope(struct mysmb_game *g, mysmb_u8 slot, mysmb_u8 speed)
{
    mysmb_u16 sum;
    mysmb_u8 x, y, carry, buffer;
    sum = (mysmb_u16)(g->ram[0x0087U + slot] + 8U);
    x = (mysmb_u8)sum;
    carry = sum > 255U ? 1U : 0U;
    if (g->ram[0x06ccU] == 0U) {
        sum = (mysmb_u16)(x + 0x10U);
        x = (mysmb_u8)sum;
        carry = sum > 255U ? 1U : 0U;
    }
    g->ram[2U] = (mysmb_u8)(g->ram[0x006eU + slot] + carry);
    g->ram[0U] = (mysmb_u8)((x & 0xf0U) >> 3U);
    y = g->ram[0x00cfU + slot];
    if ((speed & 0x80U) != 0U) y = (mysmb_u8)(y + 8U);
    buffer = g->ram[0x0300U];
    /* ASL/ROL/ROL yield original Y bits 7/6 in the two low bits. */
    g->ram[1U] = (mysmb_u8)(0x20U | (y >> 6U));
    g->ram[1U] = (mysmb_u8)(g->ram[1U] | ((g->ram[2U] & 1U) << 2U));
    g->ram[0U] = (mysmb_u8)(((y << 2U) & 0xe0U) + g->ram[0U]);
    if (g->ram[0x00cfU + slot] >= 0xe8U) g->ram[0U] &= 0xbfU;
    return buffer;
}

/* $D4BD-$D540 DrawEraseRope through ExitRp. Two source-saved speed
 * copies survive both address calculations; writes use absolute indices. */
static void draw_erase_rope(struct mysmb_game *g)
{
    mysmb_u8 slot, buffer, speed;
    slot = g->ram[8U];
    if ((g->ram[0x00a0U + slot] | g->ram[0x0434U + slot]) == 0U ||
        g->ram[0x0300U] >= 0x20U) return;
    speed = g->ram[0x00a0U + slot];
    buffer = setup_rope(g, slot, speed);
    g->ram[0x0301U + buffer] = g->ram[1U];
    g->ram[0x0302U + buffer] = g->ram[0U];
    g->ram[0x0303U + buffer] = 2U;
    if ((g->ram[0x00a0U + slot] & 0x80U) == 0U) {
        g->ram[0x0304U + buffer] = 0xa2U;
        g->ram[0x0305U + buffer] = 0xa3U;
    } else {
        g->ram[0x0304U + buffer] = 0x24U;
        g->ram[0x0305U + buffer] = 0x24U;
    }
    slot = g->ram[0x001eU + slot];
    buffer = setup_rope(g, slot, (mysmb_u8)(speed ^ 0xffU));
    g->ram[0x0306U + buffer] = g->ram[1U];
    g->ram[0x0307U + buffer] = g->ram[0U];
    g->ram[0x0308U + buffer] = 2U;
    if ((speed & 0x80U) != 0U) {
        g->ram[0x0309U + buffer] = 0xa2U;
        g->ram[0x030aU + buffer] = 0xa3U;
    } else {
        g->ram[0x0309U + buffer] = 0x24U;
        g->ram[0x030aU + buffer] = 0x24U;
    }
    g->ram[0x030bU + buffer] = 0U;
    g->ram[0x0300U] = (mysmb_u8)(g->ram[0x0300U] + 10U);
}

/* $D598 InitPlatformFall: GetEnemyOffscreenBits returns X=ObjectOffset,
 * Y=1. SetupFloateyNumber preserves both, including the Y used by Stop. */
static void init_platform_fall(struct mysmb_game *g, mysmb_u8 peer)
{
    mysmb_u8 slot;
    mysmb_platform_get_offscreen(g, peer);
    slot = g->ram[8U];
    mysmb_objects_setup_floatey_from_relative(g, slot, 6U);
    g->ram[0x0117U + slot] = g->ram[0x03adU];
    g->ram[0x011eU + slot] = g->ram[0x00ceU];
    g->ram[0x0046U + slot] = 1U;
    stop_platforms(g, slot, 1U);
}

/* $D5BB-$D5D2 PlatformFall / ExPF. */
static void platform_fall(struct mysmb_game *g, mysmb_u8 slot, mysmb_u8 peer)
{
    mysmb_enemy_move_falling_platform(g, slot);
    mysmb_enemy_move_falling_platform(g, peer);
    slot = g->ram[8U];
    if ((g->ram[0x03a2U + slot] & 0x80U) == 0U)
        mysmb_platform_position_player_vertical(g, g->ram[0x03a2U + slot]);
}

/* $D432-$D4BC BalancePlatform through DoOtherPlatform; local tails above
 * preserve the source pair, rope and fall graph. No peer eligibility filter. */
void mysmb_platform_move_balance(struct mysmb_game *g, mysmb_u8 slot)
{
    mysmb_u8 peer, old_y, flag, force, speed, carry;
    mysmb_u16 sum;
    if (g->ram[0x00b6U + slot] == 3U) {
        mysmb_objects_erase_enemy(g, slot);
        return;
    }
    peer = g->ram[0x001eU + slot];
    if ((peer & 0x80U) != 0U) return;
    g->ram[0U] = g->ram[0x03a2U + slot];
    if (g->ram[0x0046U + slot] != 0U) {
        platform_fall(g, slot, peer);
        return;
    }
    if (g->ram[0x00cfU + slot] <= 0x2dU) {
        if (peer == g->ram[0U]) init_platform_fall(g, peer);
        else {
            g->ram[0x00cfU + slot] = 0x2fU;
            stop_platforms(g, slot, peer);
        }
        return;
    }
    if (g->ram[0x00cfU + peer] <= 0x2dU) {
        if (slot == g->ram[0U]) init_platform_fall(g, peer);
        else {
            g->ram[0x00cfU + peer] = 0x2fU;
            stop_platforms(g, slot, peer);
        }
        return;
    }
    old_y = g->ram[0x00cfU + slot];
    flag = g->ram[0x03a2U + slot];
    if ((flag & 0x80U) == 0U) {
        mysmb_world_move_platform_vertically(g, slot, flag == g->ram[8U] ? 0U : 1U);
        slot = g->ram[8U];
    } else {
        sum = (mysmb_u16)(g->ram[0x0434U + slot] + 5U);
        force = (mysmb_u8)sum;
        carry = sum > 255U ? 1U : 0U;
        g->ram[0U] = force;
        speed = (mysmb_u8)(g->ram[0x00a0U + slot] + carry);
        if ((speed & 0x80U) != 0U) {
            mysmb_world_move_platform_vertically(g, slot, 0U);
            slot = g->ram[8U];
        } else if (speed != 0U || force >= 0x0bU) {
            mysmb_world_move_platform_vertically(g, slot, 1U);
            slot = g->ram[8U];
        } else stop_platforms(g, slot, peer);
    }
    peer = g->ram[0x001eU + slot];
    g->ram[0x00cfU + peer] = (mysmb_u8)(g->ram[0x00cfU + peer] +
        (mysmb_u8)(old_y - g->ram[0x00cfU + slot]));
    flag = g->ram[0x03a2U + slot];
    if ((flag & 0x80U) == 0U) mysmb_platform_position_player_vertical(g, flag);
    draw_erase_rope(g);
}
