#include "game/oam/oam.h"

/* ROM $eced DrawFirebar through FireA. The source reads FrameCounter
 * once, writes tile before attributes and returns Y unchanged. */
mysmb_u8 mysmb_oam_draw_firebar(struct mysmb_game *game, mysmb_u8 oam)
{
    mysmb_u8 frame;
    frame = game->ram[0x0009U];
    game->ram[0x0201U + oam] =
        (mysmb_u8)(0x64U ^ ((frame >> 2U) & 1U));
    game->ram[0x0202U + oam] = (frame & 8U) != 0U ? 0xc2U : 2U;
    mysmb_text_observer_record(game, MYSMB_TEXT_OBSERVE_FIREBAR,
        0U, oam, (mysmb_u8)((frame >> 2U) & 1U), 1U, oam, 1U, 0U);
    return oam;
}
