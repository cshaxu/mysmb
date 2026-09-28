#include "game/enemy/firebar.h"

/* ROM $ECED DrawFirebar child entry. The source returns Y unchanged.
 * This seam retains the graphics node's later ownership and proof status. */
mysmb_u8 mysmb_oam_draw_firebar(struct mysmb_game *game, mysmb_u8 oam)
{
    game->ram[0x0201U + oam] =
        (mysmb_u8)(0x64U ^ ((game->ram[9U] >> 2U) & 1U));
    game->ram[0x0202U + oam] = (game->ram[9U] & 8U) != 0U ? 0xc2U : 2U;
    return oam;
}
