#include "core/dispatcher.h"
#include "core/frame_root.h"
#include "core/area.h"
#include "core/player.h"
#include "core/objects.h"
#include "core/oam/oam.h"

enum {
    MYSMB_FRAME_GAME_ENGINE_SUBROUTINE = 0x000eU,
    MYSMB_FRAME_PLAYER_A_B_BUTTONS = 0x000aU,
    MYSMB_FRAME_PREVIOUS_A_B_BUTTONS = 0x000dU,
    MYSMB_FRAME_PLAYER_LEFT_RIGHT_BUTTONS = 0x000cU,
    MYSMB_FRAME_SAVED_JOYPAD1 = 0x06fcU,
    MYSMB_FRAME_PLAYER_Y = 0x00ceU,
    MYSMB_FRAME_STAR_FLAG_TASK = 0x0746U,
    MYSMB_FRAME_LEVEL = 0x075cU,
    MYSMB_FRAME_TIMER_CONTROL = 0x0747U
};

void mysmb_game_engine(struct mysmb_game *game)
{
    struct mysmb_area_source area_source;
    area_source.prg = game->area_prg;
    area_source.prg_size = game->area_prg_size;
    mysmb_game_engine_actors(game, &area_source);
    /* ROM GameEngine retains its own three-call player/OAM sequence. */
    mysmb_oam_get_player_offscreen_bits(game);
    mysmb_oam_relative_player_position(game);
    mysmb_oam_render_player(game);
    mysmb_area_apply_block_replacements(game);
    mysmb_game_engine_blocks(game);
    mysmb_objects_step_misc(game);
    mysmb_game_process_cannons(game);
    mysmb_game_process_whirlpools(game);
    /* ROM GameEngine calls FlagpoleRoutine after MiscObjectsCore and
     * before the timer tail, after this frame's player/scroll update. */
    mysmb_objects_step_flagpole(game);
    /* ROM runs the timer before ColorRotation and the palette/music tail. */
    (void)mysmb_game_run_timer(game);
    mysmb_area_step_palette_rotation(game);
    mysmb_game_cycle_player_palette(game);
    game->ram[MYSMB_FRAME_PREVIOUS_A_B_BUTTONS] =
        game->ram[MYSMB_FRAME_PLAYER_A_B_BUTTONS];
    /* ROM GameEngine's SaveAB tail clears the transient directional
     * partition after object collisions.  In particular, a collision
     * that selects PlayerDeath leaves its following physics frame with
     * zero horizontal input and the KillPlayer-cleared speed. */
    game->ram[MYSMB_FRAME_PLAYER_LEFT_RIGHT_BUTTONS] = 0U;
    mysmb_game_step_area_parser(game);
}
