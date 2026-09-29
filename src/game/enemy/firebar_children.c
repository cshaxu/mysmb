#include "game/enemy/firebar.h"
#include "game/objects.h"
#include "game/oam/oam.h"

/* Existing offscreen/relative owners remain dependencies, including their
 * separately recorded missing scratch effects. No caller-side output patch. */
void mysmb_firebar_offscreen(struct mysmb_game *game, mysmb_u8 slot)
{
    game->ram[0x03d1U] = mysmb_objects_get_enemy_offscreen_bits(game, slot);
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
