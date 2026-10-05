#include "core/objects.h"

static mysmb_u8 mysmb_enemy_bounds_sbc(mysmb_u8 value, mysmb_u8 subtrahend,
                                       mysmb_u8 carry_in, mysmb_u8 *carry_out)
{
    mysmb_u16 operand;

    operand = (mysmb_u16)subtrahend + (carry_in != 0U ? 0U : 1U);
    *carry_out = value >= operand ? 1U : 0U;
    return (mysmb_u8)(value - operand);
}

/* ROM $D67A-$D6D5 OffscreenBoundsCheck through ExScrnBd. */
void mysmb_objects_check_enemy_offscreen_bounds(struct mysmb_game *game,
                                                mysmb_u8 slot)
{
    mysmb_u8 id;
    mysmb_u8 carry;
    mysmb_u16 sum;
    mysmb_u8 left_x;
    mysmb_u8 left_page;
    mysmb_u8 right_x;
    mysmb_u8 right_page;
    mysmb_u8 difference;

    id = game->ram[0x0016U + slot];
    if (id == 20U) return; /* FlyingCheepCheep */

    /* Carry after CPY #HammerBro / CPY #PiranhaPlant. */
    carry = id >= 5U ? 1U : 0U;
    if (id != 5U) carry = id >= 13U ? 1U : 0U;
    left_x = game->ram[0x071cU];
    if (id == 5U || id == 13U) {
        sum = (mysmb_u16)left_x + 0x38U + carry;
        left_x = (mysmb_u8)sum;
        carry = sum > 0xffU ? 1U : 0U;
    }
    left_x = mysmb_enemy_bounds_sbc(left_x, 0x48U, carry, &carry);
    game->ram[1U] = left_x;
    left_page = mysmb_enemy_bounds_sbc(game->ram[0x071aU],
                                       0U, carry, &carry);

    game->ram[0U] = left_page;

    /* The carry leaving the preceding SBC is also the carry consumed by
     * the source's ADC #$48 for ScreenRight_X_Pos. */
    sum = (mysmb_u16)game->ram[0x071dU] + 0x48U + carry;
    right_x = (mysmb_u8)sum;
    game->ram[3U] = right_x;
    carry = sum > 0xffU ? 1U : 0U;
    sum = (mysmb_u16)game->ram[0x071bU] + carry;
    right_page = (mysmb_u8)sum;
    game->ram[2U] = right_page;

    carry = game->ram[0x0087U + slot] >= left_x ? 1U : 0U;
    difference = mysmb_enemy_bounds_sbc(game->ram[0x006eU + slot],
                                        left_page, carry, &carry);
    if ((difference & 0x80U) != 0U) goto erase;

    carry = game->ram[0x0087U + slot] >= right_x ? 1U : 0U;
    difference = mysmb_enemy_bounds_sbc(game->ram[0x006eU + slot],
                                        right_page, carry, &carry);
    if ((difference & 0x80U) != 0U) return;
    if (game->ram[0x001eU + slot] == 5U || id == 13U || id == 48U ||
        id == 49U || id == 50U) return;

erase:
    mysmb_objects_erase_enemy(game, slot);
}
