#include "core/frame_root.h"
#include "core/area.h"
#include "core/player.h"

/* ROM $af3b-$af66: GameEngine music/palette branch, NoChgMus, CycleTwo,
 * ClrPlrPal. Preserve the CMP/BPL sign result, not an unsigned Y range. */
void mysmb_game_cycle_player_palette(struct mysmb_game *game)
{
    mysmb_u8 color;
    mysmb_u8 y_difference;

    y_difference = (mysmb_u8)(game->ram[0x00b5U] - 2U);
    if ((y_difference & 0x80U) != 0U) {
        if (game->ram[0x079fU] == 0U) {
            mysmb_player_reset_palette(game);
            return;
        }
        if (game->ram[0x079fU] == 4U && game->ram[0x077fU] == 0U)
            mysmb_game_get_area_music(game);
    }
    color = game->ram[0x0009U];
    if (game->ram[0x079fU] < 8U) color = (mysmb_u8)(color >> 2U);
    color = (mysmb_u8)((color >> 1U) & 3U);
    mysmb_player_cycle_palette(game, color);
}

/* ROM $af6f-$af92: UpdScrollVar -> RunParser -> ExitEng. Victory's
 * shared UpdScrollVar entry uses this same caller-owned tail. */
void mysmb_game_step_area_parser(struct mysmb_game *game)
{
    mysmb_u8 difference;

    if (game->ram[0x0773U] == 6U) return;
    if (game->ram[0x071fU] == 0U) {
        difference = (mysmb_u8)(game->ram[0x073dU] - 0x20U);
        /* CMP #$20 / BMI uses the eight-bit difference's sign. On the
         * continuing range $20..$9f, carry is set for the following SBC. */
        if ((difference & 0x80U) != 0U) return;
        game->ram[0x073dU] = difference;
        game->ram[0x0340U] = 0U;
    }
    (void)mysmb_area_parser_task_step(game);
}
