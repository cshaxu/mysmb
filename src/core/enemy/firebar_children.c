#include "core/enemy/firebar.h"
#include "core/objects.h"
#include "core/oam/oam.h"

/* Actual original GetEnemyOffscreenBits child owns output and scratch. */
void mysmb_firebar_offscreen(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_get_enemy_offscreen_bits(game, slot);
}
mysmb_u8 mysmb_firebar_relative(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_relative_enemy_position(game, slot);
    return game->ram[0x03aeU];
}

/* ROM $D410-$D431 FirebarSpin / SpinCounterClockwise. Return high spin A;
 * ProcFirebar alone masks/stores it. Source Y=18/08 is not live at the
 * caller boundary. T41 S8 records original RAM/A and arithmetic proof. */
mysmb_u8 mysmb_firebar_spin(struct mysmb_game *game, mysmb_u8 slot, mysmb_u8 speed)
{
    mysmb_u8 low, carry;
    game->ram[7U] = speed;
    low = game->ram[0x0058U + slot];
    if (game->ram[0x0034U + slot] == 0U) {
        game->ram[0x0058U + slot] = (mysmb_u8)(low + game->ram[7U]);
        carry = (unsigned int)low + game->ram[7U] > 255U ? 1U : 0U;
        return (mysmb_u8)(game->ram[0x00a0U + slot] + carry);
    }
    game->ram[0x0058U + slot] = (mysmb_u8)(low - game->ram[7U]);
    carry = low < game->ram[7U] ? 1U : 0U;
    return (mysmb_u8)(game->ram[0x00a0U + slot] - carry);
}
