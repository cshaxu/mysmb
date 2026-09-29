#include "../player.h"

/* ROM $df4b-$df8a: ImpedePlayerMove through ExIPM.
 * collision_side is the caller's RAM $00 value, not a direction enum. */
void mysmb_player_impede_move(struct mysmb_game *game, mysmb_u8 collision_side)
{
    mysmb_u8 speed, correction, mask;
    mysmb_u16 sum;

    speed = game->ram[0x57U];
    if (collision_side == 1U) {
        mask = 0xfeU;
        if (speed >= 0x80U) goto exit_impede;
        correction = 0xffU;
    } else {
        /* RImpd: BPL consumes the sign of the byte CPY #$01 result. */
        mask = 0xfdU;
        if ((mysmb_u8)(speed - 1U) < 0x80U) goto exit_impede;
        correction = 1U;
    }
    /* NXSpd, PlatF: preserve the scratch high adder and low-byte carry. */
    game->ram[0x785U] = 0x10U;
    game->ram[0x57U] = 0U;
    game->ram[0U] = correction == 0xffU ? 0xffU : 0U;
    sum = (mysmb_u16)game->ram[0x86U] + correction;
    game->ram[0x86U] = (mysmb_u8)sum;
    game->ram[0x6dU] = (mysmb_u8)(game->ram[0x6dU] +
        game->ram[0U] + (sum >> 8U));
exit_impede:
    game->ram[0x490U] &= mask;
}
