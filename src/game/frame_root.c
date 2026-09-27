#include "game/frame_root.h"
#include "game/audio.h"
#include "game/area.h"
#include "game/enemy/core.h"
#include "game/player.h"
#include "game/objects.h"
#include "game/enemy/frenzy.h"
#include "game/oam/oam.h"
#include "game/title_modes.h"

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
    MYSMB_ROOT_TIMER_CONTROL = 0x0747U,
    MYSMB_ROOT_INTERVAL_TIMER_CONTROL = 0x077fU,
    MYSMB_ROOT_TIMERS = 0x0780U,
    MYSMB_ROOT_PSEUDORANDOM = 0x07a7U,
    MYSMB_ROOT_SPRITE_SHUFFLE_CONTROL = 0x06e0U,
    MYSMB_ROOT_SPRITE_SHUFFLE_AMOUNTS = 0x06e1U,
    MYSMB_ROOT_SPRITE_OFFSETS = 0x06e4U,
    MYSMB_ROOT_MISC_SPRITE_OFFSETS = 0x06f3U,
    MYSMB_ROOT_VRAM_BUFFER1_OFFSET = 0x0300U,
    MYSMB_ROOT_VRAM_BUFFER1 = 0x0301U,
    MYSMB_ROOT_VRAM_BUFFER2_OFFSET = 0x0340U,
    MYSMB_ROOT_VRAM_BUFFER2 = 0x0341U,
    MYSMB_ROOT_VRAM_ADDRESS_CONTROL = 0x0773U,
    MYSMB_ROOT_PPU_CONTROL_MIRROR = 0x0778U,
    MYSMB_ROOT_PPU_MASK_MIRROR = 0x0779U,
    MYSMB_ROOT_DISABLE_SCREEN = 0x0774U,
    MYSMB_ROOT_HORIZONTAL_SCROLL = 0x073fU,
    MYSMB_ROOT_VERTICAL_SCROLL = 0x0740U
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
    MYSMB_FRAME_TIMER_CONTROL = 0x0747U
};

/* ROM $805a-$8070 VRAM_AddrTable_Low/High and $8071 Buffer_Offset.  These
 * are source CPU addresses, retained because NMI writes the selected pointer
 * to zero page before UpdateScreen consumes it. */
static const mysmb_u8 mysmb_vram_address_low[19] = {
    0x01U, 0xa4U, 0xc8U, 0xecU, 0x10U, 0x00U, 0x41U, 0x41U, 0x4cU,
    0x34U, 0x3cU, 0x44U, 0x54U, 0x68U, 0x7cU, 0xa8U, 0xbfU, 0xdeU,
    0xefU
};
static void mysmb_frame_root_commit_scene_scroll(struct mysmb_game *game);

static const mysmb_u8 mysmb_vram_address_high[19] = {
    0x03U, 0x8cU, 0x8cU, 0x8cU, 0x8dU, 0x03U, 0x03U, 0x03U, 0x8dU,
    0x8dU, 0x8dU, 0x8dU, 0x8dU, 0x8dU, 0x8dU, 0x8dU, 0x8dU, 0x8dU,
    0x8dU
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
    if (game->ram[MYSMB_ROOT_SPRITE0_HIT] != 0U && paused == 0U) {
        oam_offset = 4U;
        do {
            game->ram[(mysmb_u16)(MYSMB_ROOT_OAM + oam_offset)] = 0xf8U;
            oam_offset = (mysmb_u8)(oam_offset + 4U);
        } while (oam_offset != 0U);
        mysmb_game_shuffle_sprite_offsets(game);
    }
    mysmb_frame_root_commit_scene_scroll(game);
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
    struct mysmb_area_source area_source;
    mysmb_u8 paused;
    mysmb_u8 run_title_demo;

    paused = mysmb_frame_root_begin(game, input, &mode_before, &task_before);
    run_title_demo = 0U;
    if (paused != 0U) {
        mysmb_frame_root_finish(game, frame);
        return;
    }
    /* ROM OperModeExecutionTree loads OperMode then JumpEngine selects one
     * of its four inline vector entries.  Do not call a title leaf before
     * that selector: non-title modes never enter TitleScreenMode. */
    if (mode_before == 2U) {
        mysmb_game_step_victory(game);
        /* ROM $8471 VictoryMode: after the selected victory leaf, task zero
         * branches directly to AutoPlayer.  Every other task resets
         * ObjectOffset to zero and runs exactly one EnemiesAndLoopsCore
         * turn.  It is not GameEngine's fireball/six-slot/floatey schedule. */
        if (game->ram[MYSMB_ROOT_OPERATING_MODE_TASK] != 0U &&
            game->area_prg != 0) {
            area_source.prg = game->area_prg;
            area_source.prg_size = game->area_prg_size;
            mysmb_enemy_core_step_slot(game, &area_source, 0U);
        }
        /* ROM VictoryMode always ends at RelativePlayerPosition and
         * PlayerGfxHandler, including bridge-collapse task zero.  It does
         * not call GameEngine's GetPlayerOffscreenBits predecessor here. */
        mysmb_oam_relative_player_position(game);
        mysmb_oam_render_player(game);
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
        /* Source reaches InitializeGame only after the NMI prologue.  The
         * title owner preserves the existing subordinate body; absent local
         * data keeps the compatibility fixture's prior task advance. */
        if (mysmb_game_begin_title_bootstrap(game) == 0U)
            game->ram[MYSMB_ROOT_OPERATING_MODE_TASK] = 1U;
    }
    else if (mode_before == 0U && task_before == 3U) {
        /* GameMenuRoutine reaches GameCoreRoutine only via RunDemo. */
        run_title_demo = mysmb_game_title_step(game, input);
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
             (run_title_demo != 0U)) {
        if (game->ram[MYSMB_FRAME_SCREEN_ROUTINE_TASK] == 3U &&
            mysmb_area_queue_bottom_status_line(game) != 0U) {
            game->ram[MYSMB_FRAME_SCREEN_ROUTINE_TASK] = 4U;
        }
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
    /* RunDemo returns from GameCoreRoutine to this immediate source check.
     * A lose-life subroutine returns through ResetTitle before the timer tail. */
    if (run_title_demo != 0U &&
        game->ram[MYSMB_FRAME_GAME_ENGINE_SUBROUTINE] == 6U) {
        mysmb_game_reset_title(game);
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

/* ROM NMI RotPRandomBit.  The carry derives from d1 of the first two
 * registers, then propagates through seven consecutive ROR instructions. */
void mysmb_game_rotate_pseudorandom(struct mysmb_game *game)
{
    mysmb_u8 index;
    mysmb_u8 carry;
    mysmb_u8 next_carry;
    mysmb_u8 value;

    carry = ((game->ram[MYSMB_ROOT_PSEUDORANDOM] & 2U) ^ (game->ram[0x07a8U] & 2U)) != 0U ?
        1U : 0U;
    for (index = 0U; index < 7U; ++index) {
        value = game->ram[(mysmb_u16)(MYSMB_ROOT_PSEUDORANDOM + index)];
        next_carry = value & 1U;
        game->ram[(mysmb_u16)(MYSMB_ROOT_PSEUDORANDOM + index)] = (mysmb_u8)((value >> 1U) |
            (carry != 0U ? 0x80U : 0U));
        carry = next_carry;
    }
}
/* ROM NMI DecTimers.  The first 0x15 entries are frame timers; the remaining
 * interval timers run each time IntervalTimerControl rolls under zero. */
void mysmb_game_tick_player_timers(struct mysmb_game *game)
{
    mysmb_u8 index;
    mysmb_u8 last_timer;

    if (game->ram[MYSMB_ROOT_TIMER_CONTROL] != 0U) {
        game->ram[MYSMB_ROOT_TIMER_CONTROL]--;
        if (game->ram[MYSMB_ROOT_TIMER_CONTROL] != 0U) return;
    }
    game->ram[MYSMB_ROOT_INTERVAL_TIMER_CONTROL]--;
    last_timer = 0x14U;
    if (game->ram[MYSMB_ROOT_INTERVAL_TIMER_CONTROL] >= 0x80U) {
        game->ram[MYSMB_ROOT_INTERVAL_TIMER_CONTROL] = 0x14U;
        last_timer = 0x23U;
    }
    index = last_timer;
    for (;;) {
        if (game->ram[MYSMB_ROOT_TIMERS + index] != 0U) {
            game->ram[MYSMB_ROOT_TIMERS + index]--;
        }
        if (index == 0U) break;
        --index;
    }
}

/* ROM $81c6-$81f9 SpriteShuffler. */
void mysmb_game_shuffle_sprite_offsets(struct mysmb_game *game)
{
    mysmb_u8 index;
    mysmb_u16 offset;
    mysmb_u8 value;
    mysmb_u16 sum;

    for (index = 15U; index != 0U; --index) {
        offset = (mysmb_u8)(index - 1U);
        value = game->ram[(mysmb_u16)(MYSMB_ROOT_SPRITE_OFFSETS + offset)];
        if (value >= 0x28U) {
            sum = (mysmb_u16)value + game->ram[(mysmb_u16)(
                MYSMB_ROOT_SPRITE_SHUFFLE_AMOUNTS +
                game->ram[MYSMB_ROOT_SPRITE_SHUFFLE_CONTROL])];
            value = (mysmb_u8)sum;
            if (sum > 0xffU) value = (mysmb_u8)(value + 0x28U);
            game->ram[(mysmb_u16)(MYSMB_ROOT_SPRITE_OFFSETS + offset)] = value;
        }
    }
    game->ram[MYSMB_ROOT_SPRITE_SHUFFLE_CONTROL]++;
    if (game->ram[MYSMB_ROOT_SPRITE_SHUFFLE_CONTROL] == 3U)
        game->ram[MYSMB_ROOT_SPRITE_SHUFFLE_CONTROL] = 0U;
    /* ROM SetMiscOffset enters with Y=2 and X=8, then decrements both
     * counters.  Preserve that group write order rather than merely its
     * eventual byte image. */
    index = 3U;
    do {
        index--;
        value = game->ram[(mysmb_u16)(MYSMB_ROOT_SPRITE_OFFSETS + 5U + index)];
        offset = (mysmb_u16)(MYSMB_ROOT_MISC_SPRITE_OFFSETS + index * 3U);
        game->ram[offset] = value;
        value = (mysmb_u8)(value + 8U);
        game->ram[(mysmb_u16)(offset + 1U)] = value;
        game->ram[(mysmb_u16)(offset + 2U)] = (mysmb_u8)(value + 8U);
    } while (index != 0U);
}

/* ROM $8e92-$8eb6 UpdateScreen/WriteBufferToScreen at the NMI boundary.
 * The buffer is owned by game routines during the preceding frame and is
 * cleared only after its terminal command has reached PPU-visible state. */
void mysmb_game_commit_vram_buffer(struct mysmb_game *game)
{
    mysmb_u8 selector;

    selector = game->ram[MYSMB_ROOT_VRAM_ADDRESS_CONTROL];
    if (selector < 19U) {
        game->ram[0x0000U] = mysmb_vram_address_low[selector];
        game->ram[0x0001U] = mysmb_vram_address_high[selector];
    }
    if (selector >= 1U && selector <= 4U) {
        (void)mysmb_area_apply_palette(game, (mysmb_u8)(
            selector - 1U));
    }
    else if (selector >= 8U && selector <= 11U) {
        (void)mysmb_area_apply_special_palette(game,
            selector);
    }
    else if (selector >= 12U && selector <= 18U) {
        (void)mysmb_area_apply_message(game,
            selector);
    }
    else if (selector == 6U || selector == 7U) {
        (void)mysmb_game_apply_vram_commands(game,
            &game->ram[MYSMB_ROOT_VRAM_BUFFER2], 0x00c0U);
    }
    else if (selector == 5U) {
        (void)mysmb_game_apply_vram_commands(game, &game->ram[0x0300U],
                                              0x013aU);
    }
    else {
        (void)mysmb_game_apply_vram_commands(game,
            &game->ram[MYSMB_ROOT_VRAM_BUFFER1], 0x0100U);
    }
    /* InitBuffer selects Buffer_Offset[1] only when X is exactly six.  Entry
     * seven transfers $0341 but still clears the ordinary $0300/$0301 header. */
    if (selector == 6U) {
        game->ram[MYSMB_ROOT_VRAM_BUFFER2_OFFSET] = 0U;
        game->ram[MYSMB_ROOT_VRAM_BUFFER2] = 0U;
    }
    else {
        game->ram[MYSMB_ROOT_VRAM_BUFFER1_OFFSET] = 0U;
        game->ram[MYSMB_ROOT_VRAM_BUFFER1] = 0U;
    }
    game->ram[MYSMB_ROOT_VRAM_ADDRESS_CONTROL] = 0U;
}

/* ROM NonMaskableInterrupt ($740-$842) restores the selected display mask,
 * commits scroll/name-table state, then re-enables NMI on $2000.  Gameplay
 * has already changed the source-owned scroll fields when this is called. */
static void mysmb_frame_root_commit_scene_scroll(struct mysmb_game *game)
{
    game->visible_scroll_x = game->ram[MYSMB_ROOT_HORIZONTAL_SCROLL];
    game->visible_scroll_y = game->ram[MYSMB_ROOT_VERTICAL_SCROLL];
}

void mysmb_game_commit_display_state(struct mysmb_game *game)
{
    mysmb_u8 mask_mirror;

    /* NMI saves the pre-command $2000 mirror without d7.  A VRAM command
     * may have selected d2 in that mirror, whereas the physical register at
     * RTI is restored from the pre-command value with NMI enabled. */
    game->ppu_control_0 &= 0x7fU;
    game->ram[MYSMB_ROOT_PPU_CONTROL_MIRROR] = game->ppu_control_0;
    /* ScreenOff reads the $2001 mirror, never the ColdBoot's earlier direct
     * physical $2001 write.  The first NMI therefore turns physical $06 into
     * the cleared mirror value $00 while DisableScreenFlag remains set. */
    mask_mirror = game->ram[MYSMB_ROOT_PPU_MASK_MIRROR];
    if (game->ram[MYSMB_ROOT_DISABLE_SCREEN] != 0U)
        mask_mirror &= 0xe6U;
    else
        mask_mirror |= 0x1eU;
    game->ram[MYSMB_ROOT_PPU_MASK_MIRROR] = mask_mirror;
    game->ppu_mask = mask_mirror;
    /* The original writes these values before OperModeExecutionTree.  That
     * routine may change the mirrors and scroll variables, but the physical
     * PPU does not show those changes until the following NMI. */
    game->visible_ppu_control_0 = (mysmb_u8)(game->ppu_control_0 | 0x80U);
    game->visible_ppu_mask = game->ppu_mask;
    game->visible_ppu_name_table = (mysmb_u8)(game->ppu_control_0 & 3U);
}
