#include "game/frame_root.h"
#include "game/audio.h"
#include "game/area.h"
#include "game/player.h"
#include "game/objects.h"

enum {
    MYSMB_ROOT_FRAME_COUNTER = 0x0009U,
    MYSMB_ROOT_OPERATING_MODE = 0x0770U,
    MYSMB_ROOT_OPERATING_MODE_TASK = 0x0772U,
    MYSMB_ROOT_SPRITE0_HIT = 0x0722U,
    MYSMB_ROOT_SAVED_JOYPAD1 = 0x06fcU,
    MYSMB_ROOT_JOYPAD_MASK1 = 0x074aU,
    MYSMB_ROOT_PAUSE_STATUS = 0x0776U,
    MYSMB_ROOT_PAUSE_TIMER = 0x0777U,
    MYSMB_ROOT_PAUSE_SOUND_QUEUE = 0x00faU,
    MYSMB_ROOT_TOP_SCORE = 0x07d7U,
    MYSMB_ROOT_PLAYER_SCORE = 0x07ddU,
    MYSMB_ROOT_OAM = 0x0200U
};

enum {
    MYSMB_FRAME_GAME_ENGINE_SUBROUTINE = 0x000eU,
    MYSMB_FRAME_PLAYER_A_B_BUTTONS = 0x000aU,
    MYSMB_FRAME_PREVIOUS_A_B_BUTTONS = 0x000dU,
    MYSMB_FRAME_PLAYER_LEFT_RIGHT_BUTTONS = 0x000cU,
    MYSMB_FRAME_SCREEN_ROUTINE_TASK = 0x073cU,
    MYSMB_FRAME_PLAYER_Y = 0x00ceU,
    MYSMB_FRAME_STAR_FLAG_TASK = 0x0746U,
    MYSMB_FRAME_LEVEL = 0x075cU,
    MYSMB_FRAME_ENEMY_FLAG = 0x000fU,
    MYSMB_FRAME_ENEMY_ID = 0x0016U,
    MYSMB_FRAME_TIMER_CONTROL = 0x0747U
};
mysmb_u8 mysmb_frame_root_begin(struct mysmb_game *game,
                            const struct mysmb_input *input,
                            mysmb_u8 *mode_before, mysmb_u8 *task_before)
{
    mysmb_u8 oam_offset;
    mysmb_u8 paused;

    *mode_before = game->ram[MYSMB_ROOT_OPERATING_MODE];
    *task_before = game->ram[MYSMB_ROOT_OPERATING_MODE_TASK];
    game->frame_number++;
    if (game->oam_dma_primed != 0U) mysmb_game_submit_oam(game);
    else game->oam_dma_primed = 1U;
    mysmb_game_commit_vram_buffer(game);
    mysmb_game_commit_display_state(game);
    mysmb_audio_step(game);
    (void)mysmb_frame_root_latch_joypad1(game, input->buttons);
    paused = mysmb_frame_root_pause_step(game);
    mysmb_frame_root_update_top_score(game);
    if (paused == 0U) {
        mysmb_game_tick_player_timers(game);
        game->ram[MYSMB_ROOT_FRAME_COUNTER]++;
    }
    mysmb_game_rotate_pseudorandom(game);
    if (game->ram[MYSMB_ROOT_SPRITE0_HIT] == 0U) return paused;
    if (paused == 0U) {
        oam_offset = 4U;
        do {
            game->ram[(mysmb_u16)(MYSMB_ROOT_OAM + oam_offset)] = 0xf8U;
            oam_offset = (mysmb_u8)(oam_offset + 4U);
        } while (oam_offset != 0U);
        mysmb_game_shuffle_sprite_offsets(game);
    }
    return paused;
}

/* ROM $8e5c-$8e90: controller-one latch and Start/Select debounce. */
mysmb_u8 mysmb_frame_root_latch_joypad1(struct mysmb_game *game,
                                        mysmb_u8 buttons)
{
    mysmb_u8 select_start;

    select_start = (mysmb_u8)(buttons &
        (MYSMB_BUTTON_SELECT | MYSMB_BUTTON_START));
    if ((select_start & game->ram[MYSMB_ROOT_JOYPAD_MASK1]) != 0U) {
        buttons = (mysmb_u8)(buttons &
            ~(MYSMB_BUTTON_SELECT | MYSMB_BUTTON_START));
    }
    else game->ram[MYSMB_ROOT_JOYPAD_MASK1] = buttons;
    game->ram[MYSMB_ROOT_SAVED_JOYPAD1] = buttons;
    return buttons;
}
/* ROM $8a4f-$8a6c UpdateTopScore / TopScoreCheck. */
static void mysmb_frame_root_top_score_check(struct mysmb_game *game,
                                             mysmb_u8 player_offset)
{
    mysmb_u8 index;
    mysmb_u8 borrow;
    mysmb_u8 player;
    mysmb_u8 top;

    borrow = 0U;
    for (index = 6U; index != 0U; --index) {
        player = game->ram[MYSMB_ROOT_PLAYER_SCORE + player_offset + index - 1U];
        top = game->ram[MYSMB_ROOT_TOP_SCORE + index - 1U];
        borrow = player < (mysmb_u8)(top + borrow) ? 1U : 0U;
    }
    if (borrow != 0U) return;
    for (index = 0U; index < 6U; ++index) {
        game->ram[MYSMB_ROOT_TOP_SCORE + index] =
            game->ram[MYSMB_ROOT_PLAYER_SCORE + player_offset + index];
    }
}

void mysmb_frame_root_update_top_score(struct mysmb_game *game)
{
    mysmb_frame_root_top_score_check(game, 0U);
    mysmb_frame_root_top_score_check(game, 6U);
}
/* ROM $821c-$8244 PauseRoutine.  T14 later invokes this at its NMI site. */
mysmb_u8 mysmb_frame_root_pause_step(struct mysmb_game *game)
{
    mysmb_u8 status;

    if (game->ram[MYSMB_ROOT_OPERATING_MODE] != 2U &&
        (game->ram[MYSMB_ROOT_OPERATING_MODE] != 1U ||
         game->ram[MYSMB_ROOT_OPERATING_MODE_TASK] != 3U)) {
        return (mysmb_u8)(game->ram[MYSMB_ROOT_PAUSE_STATUS] & 1U);
    }
    if (game->ram[MYSMB_ROOT_PAUSE_TIMER] != 0U) {
        game->ram[MYSMB_ROOT_PAUSE_TIMER]--;
        return (mysmb_u8)(game->ram[MYSMB_ROOT_PAUSE_STATUS] & 1U);
    }
    if ((game->ram[MYSMB_ROOT_SAVED_JOYPAD1] & MYSMB_BUTTON_START) != 0U) {
        status = game->ram[MYSMB_ROOT_PAUSE_STATUS];
        if ((status & 0x80U) != 0U) return (mysmb_u8)(status & 1U);
        game->ram[MYSMB_ROOT_PAUSE_TIMER] = 0x2bU;
        game->ram[MYSMB_ROOT_PAUSE_SOUND_QUEUE] = (mysmb_u8)(status + 1U);
        status = (mysmb_u8)((status ^ 1U) | 0x80U);
        game->ram[MYSMB_ROOT_PAUSE_STATUS] = status;
        return (mysmb_u8)(status & 1U);
    }
    game->ram[MYSMB_ROOT_PAUSE_STATUS] &= 0x7fU;
    return (mysmb_u8)(game->ram[MYSMB_ROOT_PAUSE_STATUS] & 1U);
}
void mysmb_frame_root_step(struct mysmb_game *game, const struct mysmb_input *input,
                     struct mysmb_frame *frame)
{
    mysmb_u8 mode_before;
    mysmb_u8 task_before;
    mysmb_u8 enemy_slot;
    struct mysmb_area_source area_source;
    mysmb_u8 paused;

    paused = mysmb_frame_root_begin(game, input, &mode_before, &task_before);
    if (paused != 0U) {
        mysmb_frame_root_finish(game, frame);
        return;
    }
    mysmb_game_title_step(game, input);
    if (mode_before == 2U) {
        mysmb_game_step_victory(game);
        /* ROM VictoryMode invokes EnemiesAndLoopsCore only after task zero.
         * RetainerObject is its reachable source-owned slot-zero OAM route. */
        if (game->ram[MYSMB_ROOT_OPERATING_MODE_TASK] != 0U)
            mysmb_objects_draw_retainer(game, 0U);
        /* ROM VictoryMode always ends at RelativePlayerPosition and
         * PlayerGfxHandler, including bridge-collapse task zero. */
        mysmb_player_draw_oam(game);
    }
    else if (mode_before == 3U) {
        mysmb_game_step_game_over(game);
    }
    else if (mode_before == 1U && task_before == 0U) {
        mysmb_area_initialize(game);
        if (game->area_prg != 0) {
            area_source.prg = game->area_prg;
            area_source.prg_size = game->area_prg_size;
            if (mysmb_area_load_pointers(game, &area_source) != 0U) {
                if (mysmb_area_parse_header(game, &area_source) != 0U) {
                }
            }
        }
    }
    else if (mode_before == 0U && task_before == 0U) {
        game->ram[MYSMB_ROOT_OPERATING_MODE_TASK] = 1U;
    }
    else if (((mode_before == 1U && task_before == 1U) ||
              (mode_before == 0U && task_before == 1U)) &&
             game->area_prg != 0) {
        mysmb_game_step_screen_routine(game);
    }
    else if ((mode_before == 1U || mode_before == 0U) && task_before == 2U &&
             game->area_prg != 0) {
        if (mode_before == 0U) mysmb_game_primary_setup(game);
        mysmb_game_secondary_setup(game);
    }
    else if (mode_before == 1U &&
             (task_before == 3U ||
              (task_before == 1U && game->area_prg == 0)) &&
             game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 6U) {
        mysmb_game_lose_life(game);
    }
    else if ((mode_before == 1U &&
              (task_before == 3U || (task_before == 1U && game->area_prg == 0))) ||
             (mode_before == 0U && task_before == 3U &&
              game->ram[MYSMB_ROOT_OPERATING_MODE] == 0U &&
              game->ram[MYSMB_ROOT_OPERATING_MODE_TASK] == 3U)) {
        if (game->ram[MYSMB_FRAME_SCREEN_ROUTINE_TASK] == 3U &&
            mysmb_area_queue_bottom_status_line(game) != 0U) {
            game->ram[MYSMB_FRAME_SCREEN_ROUTINE_TASK] = 4U;
        }
        mysmb_objects_step_flagpole(game);
        if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 0U) {
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
            mysmb_player_step(game, game->ram[MYSMB_ROOT_SAVED_JOYPAD1]);
        }
        else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 9U) {
            mysmb_player_step_change_size(game);
        }
        else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 10U) {
            mysmb_player_step_injury_blink(game, game->ram[MYSMB_ROOT_SAVED_JOYPAD1]);
        }
        else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 11U &&
                 game->ram[MYSMB_FRAME_TIMER_CONTROL] < 0xf0U) {
            mysmb_player_step(game, game->ram[MYSMB_ROOT_SAVED_JOYPAD1]);
        }
        else if (game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 12U) {
            mysmb_player_step_fire_flower(game);
        }
        /* ROM $94a5 GameEngine: GameRoutines (above) runs before the
         * object loop, so object collisions see this frame's player state. */
        if (game->area_prg != 0) {
            area_source.prg = game->area_prg;
            area_source.prg_size = game->area_prg_size;
            /* ROM GameEngine runs ProcFireball_Bubble before the six
             * EnemiesAndLoopsCore slots. */
            mysmb_objects_step_fireballs(game);
            /* ROM GameEngine enters EnemiesAndLoopsCore once for every
             * ObjectOffset.  Only an empty slot reaches ProcessEnemyData;
             * a stream page-control record can therefore be consumed by a
             * later empty slot in the same frame. */
            for (enemy_slot = 0U; enemy_slot < 6U; ++enemy_slot) {
                if (game->ram[MYSMB_FRAME_ENEMY_FLAG + enemy_slot] != 0U) {
                    if (enemy_slot < 5U) {
                        mysmb_objects_step_normal_enemy(game, enemy_slot);
                    }
                    else if (game->ram[MYSMB_FRAME_ENEMY_ID + enemy_slot] == 0x2eU) {
                        /* PowerUpObjHandler owns its collision and bounds
                         * tail in source slot five. */
                        mysmb_objects_step_power_up(game);
                        mysmb_objects_finish_power_up(game);
                    }
                }
                else if (enemy_slot < 5U) {
                    if (mysmb_area_spawn_enemy_in_slot(game, &area_source,
                                                       enemy_slot) != 0U &&
                        game->ram[MYSMB_FRAME_ENEMY_FLAG + enemy_slot] != 0U) {
                    }
                }
                else {
                    (void)mysmb_area_spawn_next_enemy(game, &area_source);
                }
                /* ROM GameEngine calls FloateyNumbersRoutine before
                 * incrementing ObjectOffset. */
                mysmb_objects_step_floatey_number(game, enemy_slot);
            }
        }
        mysmb_objects_step_enemy_collisions(game);
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
        mysmb_objects_step_flying_cheep_frenzy(game);
        mysmb_objects_step_flying_cheep_cheeps(game);
        mysmb_objects_step_firebars(game);
        mysmb_objects_step_platforms(game);
        mysmb_objects_step_bowsers(game);
        mysmb_objects_draw_bowsers(game);
        mysmb_objects_step_bowser_flame_frenzy(game);
        mysmb_objects_step_bowser_flames(game);
        mysmb_objects_step_star_flags(game);
        mysmb_objects_step_fireworks(game);
        mysmb_objects_step_firework_frenzy(game);
        mysmb_objects_step_lakitu_frenzy(game);
        mysmb_objects_step_lakitus(game);
        mysmb_objects_step_spiny_eggs(game);
        mysmb_objects_step_hammer_bros(game);
        mysmb_player_draw_oam(game);
        mysmb_objects_step_vine(game);
        mysmb_objects_apply_block_replacements(game);
        mysmb_objects_step_blocks(game);
        mysmb_objects_step_misc(game);
        mysmb_area_step_palette_rotation(game);
        (void)mysmb_area_sync_player_palette(game);
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
    /* GameEngine may advance the entrance dispatcher to subroutine 8 on this
     * frame.  The ROM's game-timer pass observes that new state, so it can
     * load its first 24-frame interval without an extra frame of delay. */
    if (mysmb_game_run_timer(game) != 0U) {
        (void)mysmb_area_queue_timer_status(game);
    }
    mysmb_frame_root_finish(game, frame);
}

void mysmb_frame_root_finish(const struct mysmb_game *game,
                             struct mysmb_frame *frame)
{
    frame->sprite0_y = game->ram[MYSMB_ROOT_OAM];
    frame->sprite0_x = game->ram[MYSMB_ROOT_OAM + 3U];
    frame->start_pressed = (game->ram[MYSMB_ROOT_SAVED_JOYPAD1] &
                            MYSMB_BUTTON_START) != 0U ? 1U : 0U;
    frame->operating_mode = game->ram[MYSMB_ROOT_OPERATING_MODE];
    frame->operating_mode_task = game->ram[MYSMB_ROOT_OPERATING_MODE_TASK];
}
