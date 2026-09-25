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
