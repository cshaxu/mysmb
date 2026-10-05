#include "core/enemy/actor_slots.h"
#include "core/enemy/movement.h"

/* ROM $CC46 SwimCCXMoveData; the last two bytes are residual data.
 * $CC4A-$CCC6 MoveSwimmingCheepCheep through ExSwCC. */
void mysmb_objects_step_swimming_cheep_cheeps_slot(struct mysmb_game *game,
                                                mysmb_u8 slot)
{
    static const mysmb_u8 force_data[4] = {0x40U,0x80U,4U,4U};
    mysmb_u8 value, carry, amount, difference, direction;
    unsigned int sum;

    value = (mysmb_u8)(game->ram[0x001eU + slot] & 0x20U);
    if (value != 0U) {
        mysmb_enemy_move_slow_vertically(game, slot);
        return;
    }
    game->ram[3U] = value;
    amount = force_data[(mysmb_u8)(game->ram[0x0016U + slot] - 10U)];
    game->ram[2U] = amount;
    value = game->ram[0x0401U + slot];
    game->ram[0x0401U + slot] = (mysmb_u8)(value - amount);
    carry = value < amount ? 1U : 0U;
    value = game->ram[0x0087U + slot];
    game->ram[0x0087U + slot] = (mysmb_u8)(value - carry);
    carry = value < carry ? 1U : 0U;
    game->ram[0x006eU + slot] = (mysmb_u8)(game->ram[0x006eU + slot] - carry);
    game->ram[2U] = 0x20U;
    if (slot < 2U) return;

    value = game->ram[0x0417U + slot];
    if (game->ram[0x0058U + slot] >= 0x10U) {
        sum = (unsigned int)value + game->ram[2U];
        game->ram[0x0417U + slot] = (mysmb_u8)sum;
        sum = (unsigned int)game->ram[0x00cfU + slot] + game->ram[3U] + (sum >> 8U);
        game->ram[0x00cfU + slot] = (mysmb_u8)sum;
        game->ram[0x00b6U + slot] = (mysmb_u8)(game->ram[0x00b6U + slot] + (sum >> 8U));
    }
    else {
        game->ram[0x0417U + slot] = (mysmb_u8)(value - game->ram[2U]);
        carry = value < game->ram[2U] ? 1U : 0U;
        sum = (unsigned int)game->ram[3U] + carry;
        value = game->ram[0x00cfU + slot];
        game->ram[0x00cfU + slot] = (mysmb_u8)(value - sum);
        carry = value < sum ? 1U : 0U;
        game->ram[0x00b6U + slot] = (mysmb_u8)(game->ram[0x00b6U + slot] - carry);
    }
    direction = 0U;
    difference = (mysmb_u8)(game->ram[0x00cfU + slot] - game->ram[0x0434U + slot]);
    if ((difference & 0x80U) != 0U) {
        direction = 0x10U;
        difference = (mysmb_u8)(0U - difference);
    }
    if (difference >= 0x0fU) game->ram[0x0058U + slot] = direction;
}
