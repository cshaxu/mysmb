#include "game/dispatcher.h"
#include "game/frame_root.h"
#include "game/area.h"
#include "game/player.h"
#include "game/objects.h"
#include "game/enemy/core.h"
#include "game/enemy/frenzy.h"
#include "game/oam/oam.h"

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

/* Existing child implementations extracted from the frame root.
 * GameRoutines vector/body fidelity is pending T31 S4; GameEngine call order
 * and child scheduling are pending T31 S2. Extraction grants no node credit. */
void mysmb_game_routines(struct mysmb_game *game)
{
    if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 6U) {
        mysmb_game_lose_life(game);
    }
    else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 0U) {
        mysmb_player_initialize_entrance(game);
    }
    else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 1U) {
        mysmb_player_step_auto_climb(game);
    }
    else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 7U) {
        mysmb_player_finish_normal_entrance(game);
    }
    else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 3U) {
        mysmb_player_step_vertical_pipe(game);
    }
    else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 4U) {
        /* ROM FlagpoleSlide: force Down until the slide reaches $9e. */
        if (game->ram[MYSMB_FRAME_PLAYER_Y] < 0x9eU) {
            mysmb_player_step(game, MYSMB_BUTTON_DOWN);
        }
        else {
            game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] = 5U;
        }
    }
    else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 5U) {
        /* ROM PlayerEndLevel.  The star/flag task is the original
         * object-side completion handoff; the mode route owns NextArea. */
        mysmb_player_step(game, MYSMB_BUTTON_RIGHT);
        if (game->ram[MYSMB_FRAME_STAR_FLAG_TASK] == 5U) {
            game->ram[MYSMB_FRAME_LEVEL]++;
            mysmb_game_next_area(game);
        }
    }
    else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 2U) {
        mysmb_player_step_side_pipe(game);
    }
    else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 8U) {
        mysmb_player_step(game, game->ram[MYSMB_FRAME_SAVED_JOYPAD1]);
    }
    else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 9U) {
        mysmb_player_step_change_size(game);
    }
    else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 10U) {
        mysmb_player_step_injury_blink(game, game->ram[MYSMB_FRAME_SAVED_JOYPAD1]);
    }
    else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 11U &&
             game->ram[MYSMB_FRAME_TIMER_CONTROL] < 0xf0U) {
        mysmb_player_step(game, game->ram[MYSMB_FRAME_SAVED_JOYPAD1]);
    }
    else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 12U) {
        mysmb_player_step_fire_flower(game);
    }
}

void mysmb_game_engine(struct mysmb_game *game)
{
    struct mysmb_area_source area_source;
    if (game->area_prg != 0) {
        area_source.prg = game->area_prg;
        area_source.prg_size = game->area_prg_size;
        mysmb_enemy_core_step(game, &area_source);
    }
    mysmb_objects_check_hazard_enemy_collision(game);
    mysmb_objects_check_bullet_bill_stomp(game);
    mysmb_objects_check_bloober_stomp(game);
    mysmb_objects_check_lakitu_stomp(game);
    mysmb_objects_check_hammer_bro_stomp(game);
    mysmb_objects_check_paratroopa_stomp(game);
    mysmb_objects_step_bullet_bills(game);
    mysmb_objects_step_piranha_plants(game);
    mysmb_objects_step_swimming_cheep_cheeps(game);
    mysmb_objects_step_podoboos(game);
    mysmb_objects_step_bloobers(game);
    mysmb_objects_step_jumping_paratroopas(game);
    mysmb_objects_step_red_paratroopas(game);
    mysmb_objects_step_flying_green_paratroopas(game);
    mysmb_objects_step_flying_cheep_cheeps(game);
    mysmb_objects_step_firebars(game);
    mysmb_objects_step_platforms(game);
    mysmb_objects_step_bowsers(game);
    mysmb_objects_draw_bowsers(game);
    mysmb_objects_step_bowser_flames(game);
    mysmb_objects_step_star_flags(game);
    mysmb_objects_step_fireworks(game);
    mysmb_enemy_step_lakitus(game);
    mysmb_enemy_step_spiny_eggs(game);
    mysmb_objects_step_hammer_bros(game);
    /* ROM GameEngine retains its own three-call player/OAM sequence. */
    mysmb_oam_get_player_offscreen_bits(game);
    mysmb_oam_relative_player_position(game);
    mysmb_oam_render_player(game);
    mysmb_objects_step_vine(game);
    mysmb_area_apply_block_replacements(game);
    mysmb_objects_step_blocks(game);
    mysmb_objects_step_misc(game);
    /* ROM GameEngine calls FlagpoleRoutine after MiscObjectsCore and
     * before the timer tail, after this frame's player/scroll update. */
    mysmb_objects_step_flagpole(game);
    /* ROM runs the timer before ColorRotation and the palette/music tail. */
    if (mysmb_game_run_timer(game) != 0U)
        (void)mysmb_area_queue_timer_status(game);
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
