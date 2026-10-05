#include "core/frame_root.h"
#include "game/objects.h"
#include "core/status.h"

/* ROM $B74F-$B7A3 RunGameTimer/ResGTCtrl/TimeUpOn/ExGTimer.  The audio subsystem consumes its queue on a following
 * frame; ForceInjury retains collision's single death-state owner. */
mysmb_u8 mysmb_game_run_timer(struct mysmb_game *game)
{
    if (game->ram[0x0770U] == 0U ||
        game->ram[0x000eU] < 8U ||
        game->ram[0x000eU] == 0x0bU ||
        game->ram[0x00b5U] >= 2U ||
        game->ram[0x0787U] != 0U) return 0U;
    if ((game->ram[0x07f8U] |
         game->ram[0x07f8U + 1U] |
         game->ram[0x07f8U + 2U]) == 0U) {
        game->ram[0x0756U] = 0U;
        mysmb_objects_force_injury_entry(game, 0U);
        game->ram[0x0759U]++;
        return 0U;
    }
    if (game->ram[0x07f8U] == 1U &&
        game->ram[0x07f8U + 1U] == 0U &&
        game->ram[0x07f8U + 2U] == 0U) {
        game->ram[0x00fcU] = 0x40U;
    }
    game->ram[0x0787U] = 0x18U;
    game->ram[0x0139U] = 0xffU;
    mysmb_status_apply_digit_modifier(game, 0x23U);
    (void)mysmb_status_queue_timer(game);
    return 1U;
}

