#include "game/dispatcher.h"
#include "game/area.h"
#include "game/frame_root.h"

/* ROM $aedc-$aee9: GameMode's four-entry JumpEngine table.
 * OperMode_Task is a source-owned selector in the range 0..3. */
void mysmb_game_mode(struct mysmb_game *game)
{
    switch (game->ram[0x0772U]) {
    case 0U: mysmb_area_initialize(game); break;
    case 1U: mysmb_game_step_screen_routine(game); break;
    case 2U: mysmb_game_secondary_setup(game); break;
    case 3U: mysmb_game_core_routine(game); break;
    default: break;
    }
}

/* ROM $aeea-$aefd: controller selection precedes GameRoutines. The child
 * can change OperMode_Task, so the engine gate must reload it afterwards. */
void mysmb_game_core_routine(struct mysmb_game *game)
{
    game->ram[0x06fcU] = game->ram[(mysmb_u16)(0x06fcU + game->ram[0x0753U])];
    mysmb_game_routines(game);
    if (game->ram[0x0772U] >= 3U)
        mysmb_game_engine(game);
}
