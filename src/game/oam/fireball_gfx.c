#include "game/oam/oam.h"

/* ROM $ecde DrawFireball enters the shared DrawFirebar after Y and X. */
void mysmb_oam_draw_fireball(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 oam;
    oam = game->ram[0x06f1U + slot];
    game->ram[0x0200U + oam] = game->ram[0x03baU];
    game->ram[0x0203U + oam] = game->ram[0x03afU];
    (void)mysmb_oam_draw_firebar(game, oam);
    mysmb_text_observer_record(game, MYSMB_TEXT_OBSERVE_FIREBALL,
        0U, slot, (mysmb_u8)((game->ram[9U] >> 2U) & 1U), 1U, oam, 1U, 0U);
}

/* ROM $ed09 DrawExplosion_Fireball: load Y before incrementing state,
 * then enter the same explosion body as fireworks or KillFireBall. */
void mysmb_oam_draw_fireball_explosion(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 oam;
    mysmb_u8 state;
    mysmb_u8 index;
    oam = game->ram[0x06ecU + slot];
    state = game->ram[0x0024U + slot];
    game->ram[0x0024U + slot] = (mysmb_u8)(state + 1U);
    index = (mysmb_u8)((state >> 1U) & 7U);
    if (index >= 3U) {
        game->ram[0x0024U + slot] = 0U;
        return;
    }
    mysmb_oam_draw_fireworks_explosion(game, index, oam);
}
