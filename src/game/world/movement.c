#include "game/world/world.h"

enum {
    MYSMB_BLOCK_Y_SPEED = 0x00a8U,
    MYSMB_BLOCK_Y_HIGH = 0x00beU,
    MYSMB_BLOCK_Y = 0x00d7U,
    MYSMB_BLOCK_Y_DUMMY = 0x041fU,
    MYSMB_BLOCK_Y_FORCE = 0x043cU,    MYSMB_MISC_Y_SPEED = 0x00acU,
    MYSMB_MISC_Y_HIGH = 0x00c2U,
    MYSMB_MISC_Y = 0x00dbU,
    MYSMB_MISC_Y_DUMMY = 0x0423U,
    MYSMB_MISC_Y_FORCE = 0x0440U
};
/* ROM $bfa4 ImposeGravityBlock / ImposeGravity for a block-object slot.
 * Block objects use downward force $50 and maximum speed $08. */
void mysmb_world_impose_gravity_block(struct mysmb_game *game,
                                               mysmb_u8 slot)
{
    mysmb_u8 old_value;
    mysmb_u8 carry_dummy;
    mysmb_u8 carry_y;
    mysmb_u8 page_delta;
    mysmb_u16 low_sum;

    old_value = game->ram[MYSMB_BLOCK_Y_DUMMY + slot];
    game->ram[MYSMB_BLOCK_Y_DUMMY + slot] =
        (mysmb_u8)(old_value + game->ram[MYSMB_BLOCK_Y_FORCE + slot]);
    carry_dummy = game->ram[MYSMB_BLOCK_Y_DUMMY + slot] < old_value ? 1U : 0U;
    page_delta = game->ram[MYSMB_BLOCK_Y_SPEED + slot] >= 0x80U ? 0xffU : 0U;
    old_value = game->ram[MYSMB_BLOCK_Y + slot];
    low_sum = (mysmb_u16)old_value + game->ram[MYSMB_BLOCK_Y_SPEED + slot] +
        carry_dummy;
    game->ram[MYSMB_BLOCK_Y + slot] = (mysmb_u8)low_sum;
    carry_y = low_sum > 0xffU ? 1U : 0U;
    game->ram[MYSMB_BLOCK_Y_HIGH + slot] =
        (mysmb_u8)(game->ram[MYSMB_BLOCK_Y_HIGH + slot] + page_delta + carry_y);
    old_value = game->ram[MYSMB_BLOCK_Y_FORCE + slot];
    game->ram[MYSMB_BLOCK_Y_FORCE + slot] = (mysmb_u8)(old_value + 0x50U);
    if (game->ram[MYSMB_BLOCK_Y_FORCE + slot] < old_value) {
        game->ram[MYSMB_BLOCK_Y_SPEED + slot]++;
    }
    if (game->ram[MYSMB_BLOCK_Y_SPEED + slot] < 0x80U &&
        game->ram[MYSMB_BLOCK_Y_SPEED + slot] >= 8U &&
        game->ram[MYSMB_BLOCK_Y_FORCE + slot] >= 0x80U) {
        game->ram[MYSMB_BLOCK_Y_SPEED + slot] = 8U;
        game->ram[MYSMB_BLOCK_Y_FORCE + slot] = 0U;
    }
}

/* ROM $bb28 ImposeGravity with the misc-object array layout. */
void mysmb_world_impose_gravity_misc(struct mysmb_game *game,
                                             mysmb_u8 slot, mysmb_u8 amount,
                                             mysmb_u8 maximum_speed)
{
    mysmb_u8 old_value;
    mysmb_u8 carry;
    mysmb_u16 low_sum;

    old_value = game->ram[MYSMB_MISC_Y_DUMMY + slot];
    game->ram[MYSMB_MISC_Y_DUMMY + slot] =
        (mysmb_u8)(old_value + game->ram[MYSMB_MISC_Y_FORCE + slot]);
    carry = game->ram[MYSMB_MISC_Y_DUMMY + slot] < old_value ? 1U : 0U;
    old_value = game->ram[MYSMB_MISC_Y + slot];
    low_sum = (mysmb_u16)old_value + game->ram[MYSMB_MISC_Y_SPEED + slot] + carry;
    game->ram[MYSMB_MISC_Y + slot] = (mysmb_u8)low_sum;
    if (game->ram[MYSMB_MISC_Y_SPEED + slot] >= 0x80U) game->ram[MYSMB_MISC_Y_HIGH + slot]--;
    if (low_sum > 0xffU) game->ram[MYSMB_MISC_Y_HIGH + slot]++;
    old_value = game->ram[MYSMB_MISC_Y_FORCE + slot];
    game->ram[MYSMB_MISC_Y_FORCE + slot] = (mysmb_u8)(old_value + amount);
    carry = game->ram[MYSMB_MISC_Y_FORCE + slot] < old_value ? 1U : 0U;
    game->ram[MYSMB_MISC_Y_SPEED + slot] =
        (mysmb_u8)(game->ram[MYSMB_MISC_Y_SPEED + slot] + carry);
    if (game->ram[MYSMB_MISC_Y_SPEED + slot] >= maximum_speed &&
        game->ram[MYSMB_MISC_Y_SPEED + slot] < 0x80U &&
        game->ram[MYSMB_MISC_Y_FORCE + slot] >= 0x80U) {
        game->ram[MYSMB_MISC_Y_SPEED + slot] = maximum_speed;
        game->ram[MYSMB_MISC_Y_FORCE + slot] = 0U;
    }
}

/* ROM $befc ImposeGravity when its A input is zero: fireballs and ordinary
 * downward-moving SprObject arrays use this path.  `offset` is the source X
 * register after the caller's GetProperObjOffset arithmetic. */
void mysmb_world_impose_gravity_spr_object(struct mysmb_game *game,
                                           mysmb_u8 offset,
                                           mysmb_u8 downward_force,
                                           mysmb_u8 maximum_speed)
{
    mysmb_u8 old_value;
    mysmb_u8 carry;
    mysmb_u8 page_delta;
    mysmb_u16 low_sum;

    old_value = game->ram[(mysmb_u16)(0x0416U + offset)];
    game->ram[(mysmb_u16)(0x0416U + offset)] =
        (mysmb_u8)(old_value + game->ram[(mysmb_u16)(0x0433U + offset)]);
    carry = game->ram[(mysmb_u16)(0x0416U + offset)] < old_value ? 1U : 0U;
    page_delta = game->ram[(mysmb_u16)(0x009fU + offset)] >= 0x80U ? 0xffU : 0U;
    old_value = game->ram[(mysmb_u16)(0x00ceU + offset)];
    low_sum = (mysmb_u16)old_value + game->ram[(mysmb_u16)(0x009fU + offset)] + carry;
    game->ram[(mysmb_u16)(0x00ceU + offset)] = (mysmb_u8)low_sum;
    carry = low_sum > 0xffU ? 1U : 0U;
    game->ram[(mysmb_u16)(0x00b5U + offset)] =
        (mysmb_u8)(game->ram[(mysmb_u16)(0x00b5U + offset)] + page_delta + carry);
    old_value = game->ram[(mysmb_u16)(0x0433U + offset)];
    game->ram[(mysmb_u16)(0x0433U + offset)] = (mysmb_u8)(old_value + downward_force);
    carry = game->ram[(mysmb_u16)(0x0433U + offset)] < old_value ? 1U : 0U;
    game->ram[(mysmb_u16)(0x009fU + offset)] =
        (mysmb_u8)(game->ram[(mysmb_u16)(0x009fU + offset)] + carry);
    if (game->ram[(mysmb_u16)(0x009fU + offset)] >= maximum_speed &&
        game->ram[(mysmb_u16)(0x009fU + offset)] < 0x80U &&
        game->ram[(mysmb_u16)(0x0433U + offset)] >= 0x80U) {
        game->ram[(mysmb_u16)(0x009fU + offset)] = maximum_speed;
        game->ram[(mysmb_u16)(0x0433U + offset)] = 0U;
    }
}

/* ROM $BF0F-$BF4C MoveObjectHorizontally, SaveXSpd, UseAdder and
 * ExXMove. The byte return is the original A displacement. */
mysmb_u8 mysmb_world_move_spr_object_horizontally(struct mysmb_game *game,
                                               mysmb_u8 offset)
{
    mysmb_u8 speed;
    mysmb_u8 fraction;
    mysmb_u8 integer;
    mysmb_u8 page_delta;
    mysmb_u8 old_value;
    mysmb_u8 carry;
    mysmb_u8 carry_force;
    mysmb_u16 x_sum;

    speed = game->ram[(mysmb_u16)(0x0057U + offset)];
    fraction = (mysmb_u8)(speed << 4U);
    game->ram[1U] = fraction;
    integer = (mysmb_u8)(speed >> 4U);
    if (integer >= 8U) integer = (mysmb_u8)(integer | 0xf0U);
    game->ram[0U] = integer;
    page_delta = integer >= 0x80U ? 0xffU : 0U;
    game->ram[2U] = page_delta;
    old_value = game->ram[(mysmb_u16)(0x0400U + offset)];
    game->ram[(mysmb_u16)(0x0400U + offset)] = (mysmb_u8)(old_value + fraction);
    carry = game->ram[(mysmb_u16)(0x0400U + offset)] < old_value ? 1U : 0U;
    carry_force = carry;
    old_value = game->ram[(mysmb_u16)(0x0086U + offset)];
    x_sum = (mysmb_u16)old_value + integer + carry;
    game->ram[(mysmb_u16)(0x0086U + offset)] = (mysmb_u8)x_sum;
    /* ROM ADC sets carry from bit 8 even when the low result equals its
     * input (for example $22 + $ff + carry = $22). */
    carry = x_sum > 0xffU ? 1U : 0U;
    game->ram[(mysmb_u16)(0x006dU + offset)] =
        (mysmb_u8)(game->ram[(mysmb_u16)(0x006dU + offset)] + page_delta + carry);
    return (mysmb_u8)(integer + carry_force);
}

/* ROM MoveEnemyHorizontally: X is ObjectOffset, INX selects the
 * enemy arrays that follow the player at shared SprObject offset zero. */
mysmb_u8 mysmb_world_move_enemy_horizontally(struct mysmb_game *game, mysmb_u8 slot)
{
    return mysmb_world_move_spr_object_horizontally(game, (mysmb_u8)(slot + 1U));
}
