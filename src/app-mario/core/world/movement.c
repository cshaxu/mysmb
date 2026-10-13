#include "core/world/world.h"

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
