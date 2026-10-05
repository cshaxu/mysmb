#include "core/player.h"
#include "core/frame_root.h"
#include "core/area.h"

/* ROM $b315-$b328 NextArea/ExitNA. Children read the updated area byte. */
void mysmb_game_next_area(struct mysmb_game *game)
{
    struct mysmb_area_source source;
    ++game->ram[0x0760U];
    source.prg = game->area_prg;
    source.prg_size = game->area_prg_size;
    (void)mysmb_area_load_area_pointer(game, &source);
    ++game->ram[0x0757U];
    mysmb_player_change_area_mode(game);
    game->ram[0x075bU] = 0U;
    game->ram[0x00fcU] = 0x80U;
}

/* ROM $b2a4-$b2c1 FlagpoleSlide/SlidePlayer/NoFPObj. */
void mysmb_player_step_flagpole_slide(struct mysmb_game *game)
{
    mysmb_u8 buttons;
    if (game->ram[0x001bU] != 0x30U) {
        ++game->ram[0x000eU];
        return;
    }
    game->ram[0x00ffU] = game->ram[0x0713U];
    game->ram[0x0713U] = 0U;
    buttons = game->ram[0x00ceU] >= 0x9eU ? 0U : 4U;
    mysmb_player_auto_control(game, buttons);
}

/* ROM $b2ca-$b314 PlayerEndLevel/ChkStop/InCastle/RdyNextA.
 * Hidden1UpCoinAmts is bound at original PRG offset $32c2. */
void mysmb_player_step_end_level(struct mysmb_game *game)
{
    mysmb_u16 threshold;
    mysmb_player_auto_control(game, 1U);
    if (game->ram[0x00ceU] >= 0xaeU && game->ram[0x0723U] != 0U) {
        game->ram[0x00fcU] = 0x20U;
        game->ram[0x0723U] = 0U;
    }
    if ((game->ram[0x0490U] & 1U) == 0U) {
        if (game->ram[0x0746U] == 0U) ++game->ram[0x0746U];
        game->ram[0x03c4U] = 0x20U;
    }
    if (game->ram[0x0746U] != 5U) return;
    ++game->ram[0x075cU];
    if (game->ram[0x075cU] == 3U) {
        threshold = (mysmb_u16)(0x32c2U + game->ram[0x075fU]);
        if (game->area_prg != 0 && threshold < game->area_prg_size &&
            game->ram[0x0748U] >= game->area_prg[threshold])
            ++game->ram[0x075dU];
    }
    mysmb_game_next_area(game);
}
