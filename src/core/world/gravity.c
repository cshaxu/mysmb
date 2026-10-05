#include "core/world/world.h"

/* ROM $BFD7-$C046 ImposeGravity / AlterYP / ChkUpM / ExVMove.
 * CMP followed by BMI/BPL tests the wrapped subtraction's bit 7, not
 * an unsigned comparison or a host signed ordering. */
void mysmb_world_impose_gravity(struct mysmb_game *game, mysmb_u8 offset,
                                mysmb_u8 upward)
{
    mysmb_u16 sum;
    mysmb_u8 speed, force, carry, difference;
    sum = (mysmb_u16)game->ram[0x0416U + offset] +
        game->ram[0x0433U + offset];
    game->ram[0x0416U + offset] = (mysmb_u8)sum;
    carry = sum > 0xffU ? 1U : 0U;
    speed = game->ram[0x009fU + offset];
    game->ram[7U] = (speed & 0x80U) != 0U ? 0xffU : 0U;
    sum = (mysmb_u16)speed + game->ram[0x00ceU + offset] + carry;
    game->ram[0x00ceU + offset] = (mysmb_u8)sum;
    carry = sum > 0xffU ? 1U : 0U;
    game->ram[0x00b5U + offset] = (mysmb_u8)(
        game->ram[0x00b5U + offset] + game->ram[7U] + carry);
    sum = (mysmb_u16)game->ram[0x0433U + offset] + game->ram[0U];
    force = (mysmb_u8)sum;
    speed = (mysmb_u8)(speed + (sum > 0xffU ? 1U : 0U));
    difference = (mysmb_u8)(speed - game->ram[2U]);
    if ((difference & 0x80U) == 0U && force >= 0x80U) {
        speed = game->ram[2U];
        force = 0U;
    }
    game->ram[0x009fU + offset] = speed;
    game->ram[0x0433U + offset] = force;
    if (upward == 0U) return;
    game->ram[7U] = (mysmb_u8)(0U - game->ram[2U]);
    carry = force < game->ram[1U] ? 1U : 0U;
    force = (mysmb_u8)(force - game->ram[1U]);
    speed = (mysmb_u8)(speed - carry);
    difference = (mysmb_u8)(speed - game->ram[7U]);
    if ((difference & 0x80U) != 0U && force < 0x80U) {
        speed = game->ram[7U];
        force = 0xffU;
    }
    game->ram[0x009fU + offset] = speed;
    game->ram[0x0433U + offset] = force;
}

/* ROM $BFAD: caller arguments represent its force scratch and A input. */
void mysmb_world_impose_gravity_spr_object(struct mysmb_game *game,
    mysmb_u8 offset, mysmb_u8 downward_force, mysmb_u8 maximum_speed)
{
    game->ram[0U] = downward_force;
    game->ram[2U] = maximum_speed;
    mysmb_world_impose_gravity(game, offset, 0U);
}

/* ROM $BF9F table and $BFA1/$BFA4 entries. BIT skips LDY #1 for the
 * residual entry; no natural incoming ROM edge is claimed for that entry. */
static void mysmb_world_block_gravity_entry(struct mysmb_game *game,
    mysmb_u8 slot, mysmb_u8 index)
{
    static const mysmb_u8 max_speed[2] = {6U, 8U};
    mysmb_world_impose_gravity_spr_object(game, (mysmb_u8)(slot + 9U),
                                         0x50U, max_speed[index]);
}
void mysmb_world_impose_gravity_block(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_world_block_gravity_entry(game, slot, 1U);
}
void mysmb_world_residual_gravity(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_world_block_gravity_entry(game, slot, 0U);
}

/* Misc callers use the same SprObject arrays at offset thirteen. */
void mysmb_world_impose_gravity_misc(struct mysmb_game *game,
    mysmb_u8 slot, mysmb_u8 amount, mysmb_u8 maximum_speed)
{
    mysmb_world_impose_gravity_spr_object(game, (mysmb_u8)(slot + 13U),
                                         amount, maximum_speed);
}

/* ROM $BFD1 RedPTroopaGrav consumes the original scratch/direction.
 * Native callers retain their enemy slot instead of exposing CPU X. */
void mysmb_world_red_gravity(struct mysmb_game *game, mysmb_u8 offset,
                             mysmb_u8 moving_up)
{
    mysmb_world_impose_gravity(game, offset, moving_up);
}

/* ROM $BFB4-$BFD0: down's BIT skips LDA #1, both entries share the
 * original ID comparison and SetDplSpd before RedPTroopaGrav. */
void mysmb_world_move_platform_vertically(struct mysmb_game *game,
    mysmb_u8 slot, mysmb_u8 moving_up)
{
    game->ram[0U] = game->ram[0x0016U + slot] == 0x29U ? 9U : 5U;
    game->ram[1U] = 10U;
    game->ram[2U] = 3U;
    mysmb_world_red_gravity(game, (mysmb_u8)(slot + 1U), moving_up);
}
