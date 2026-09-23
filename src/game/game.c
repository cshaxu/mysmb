#include "game/game.h"
#include "game/area.h"
#include "game/player.h"
#include "game/objects.h"

enum {
    MYSMB_RAM_GAME_ENGINE_SUBROUTINE = 0x000eU,
    MYSMB_RAM_SAVED_JOYPAD1 = 0x06fcU,
    MYSMB_RAM_JOYPAD_MASK1 = 0x074aU,
    MYSMB_RAM_FETCH_NEW_TIMER = 0x0757U,
    MYSMB_RAM_HIDDEN_1UP = 0x075dU,
    MYSMB_RAM_WORLD = 0x075fU,
    MYSMB_RAM_AREA = 0x0760U,
    MYSMB_RAM_OFFSCREEN_HIDDEN_1UP = 0x0764U,
    MYSMB_RAM_OFFSCREEN_WORLD = 0x0766U,
    MYSMB_RAM_OFFSCREEN_AREA = 0x0767U,
    MYSMB_RAM_PRIMARY_HARD = 0x076aU,
    MYSMB_RAM_NUMBER_OF_PLAYERS = 0x077aU,
    MYSMB_RAM_OPER_MODE = 0x0770U,
    MYSMB_RAM_OPER_MODE_TASK = 0x0772U,
    MYSMB_RAM_TIMER_CONTROL = 0x0747U,
    MYSMB_RAM_PLAYER_Y_HIGH = 0x00b5U,
    MYSMB_RAM_PLAYER_STATUS = 0x0756U,
    MYSMB_RAM_TIMER_EXPIRED = 0x0759U,
    MYSMB_RAM_GAME_TIMER_CONTROL = 0x0787U,
    MYSMB_RAM_GAME_TIMER_HUNDREDS = 0x07f8U,
    MYSMB_RAM_SELECT_TIMER = 0x0780U,
    MYSMB_RAM_INTERVAL_TIMER_CONTROL = 0x077fU,
    MYSMB_RAM_TIMERS = 0x0780U,
    MYSMB_RAM_DEMO_TIMER = 0x07a2U,
    MYSMB_RAM_WORLD_SELECT_ENABLE = 0x07fcU,
    MYSMB_RAM_CONTINUE_WORLD = 0x07fdU,
    MYSMB_RAM_SCORE_AND_COIN_END = 0x07ddU
};

/* ROM NMI DecTimers.  The first 0x15 entries are frame timers; the remaining
 * interval timers run each time IntervalTimerControl rolls under zero. */
static void mysmb_game_tick_player_timers(struct mysmb_game *game)
{
    mysmb_u8 index;
    mysmb_u8 last_timer;

    if (game->ram[MYSMB_RAM_TIMER_CONTROL] != 0U) {
        game->ram[MYSMB_RAM_TIMER_CONTROL]--;
        if (game->ram[MYSMB_RAM_TIMER_CONTROL] != 0U) return;
    }
    game->ram[MYSMB_RAM_INTERVAL_TIMER_CONTROL]--;
    last_timer = 0x14U;
    if (game->ram[MYSMB_RAM_INTERVAL_TIMER_CONTROL] >= 0x80U) {
        game->ram[MYSMB_RAM_INTERVAL_TIMER_CONTROL] = 0x14U;
        last_timer = 0x23U;
    }
    for (index = 0U; index <= last_timer; ++index) {
        if (game->ram[MYSMB_RAM_TIMERS + index] != 0U) {
            game->ram[MYSMB_RAM_TIMERS + index]--;
        }
    }
}

/* ROM RunGameTimer, excluding its status-bar, audio, and death-mode owners. */
static void mysmb_game_run_timer(struct mysmb_game *game)
{
    mysmb_u16 digit;

    if (game->ram[MYSMB_RAM_OPER_MODE] == 0U ||
        game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] < 8U ||
        game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 0x0bU ||
        game->ram[MYSMB_RAM_PLAYER_Y_HIGH] >= 2U ||
        game->ram[MYSMB_RAM_GAME_TIMER_CONTROL] != 0U) return;
    if ((game->ram[MYSMB_RAM_GAME_TIMER_HUNDREDS] |
         game->ram[MYSMB_RAM_GAME_TIMER_HUNDREDS + 1U] |
         game->ram[MYSMB_RAM_GAME_TIMER_HUNDREDS + 2U]) == 0U) {
        game->ram[MYSMB_RAM_PLAYER_STATUS] = 0U;
        game->ram[MYSMB_RAM_TIMER_EXPIRED]++;
        return;
    }
    game->ram[MYSMB_RAM_GAME_TIMER_CONTROL] = 0x18U;
    digit = MYSMB_RAM_GAME_TIMER_HUNDREDS + 2U;
    while (game->ram[digit] == 0U) {
        game->ram[digit] = 9U;
        digit--;
    }
    game->ram[digit]--;
}

/* ROM $8e5c-$8e90, restricted to controller one and select/start debounce. */
static mysmb_u8 mysmb_game_latch_joypad1(struct mysmb_game *game,
                                         mysmb_u8 buttons)
{
    mysmb_u8 select_start;

    select_start = (mysmb_u8)(buttons & (MYSMB_BUTTON_SELECT | MYSMB_BUTTON_START));
    if ((select_start & game->ram[MYSMB_RAM_JOYPAD_MASK1]) != 0U) {
        buttons = (mysmb_u8)(buttons & ~(MYSMB_BUTTON_SELECT | MYSMB_BUTTON_START));
    }
    else {
        game->ram[MYSMB_RAM_JOYPAD_MASK1] = buttons;
    }
    game->ram[MYSMB_RAM_SAVED_JOYPAD1] = buttons;
    return buttons;
}

/* ROM $8255, ChkContinue through StartWorld1; pointer loading is M2 T3. */
static void mysmb_game_start_from_title(struct mysmb_game *game, mysmb_u8 buttons)
{
    mysmb_u8 offset;

    if (game->ram[MYSMB_RAM_DEMO_TIMER] == 0U) {
        game->ram[MYSMB_RAM_OPER_MODE] = 0U;
        game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
        return;
    }
    if ((buttons & MYSMB_BUTTON_A) != 0U) {
        game->ram[MYSMB_RAM_WORLD] = game->ram[MYSMB_RAM_CONTINUE_WORLD];
        game->ram[MYSMB_RAM_OFFSCREEN_WORLD] =
            game->ram[MYSMB_RAM_CONTINUE_WORLD];
        game->ram[MYSMB_RAM_AREA] = 0U;
        game->ram[MYSMB_RAM_OFFSCREEN_AREA] = 0U;
    }
    game->ram[MYSMB_RAM_HIDDEN_1UP]++;
    game->ram[MYSMB_RAM_OFFSCREEN_HIDDEN_1UP]++;
    game->ram[MYSMB_RAM_FETCH_NEW_TIMER]++;
    game->ram[MYSMB_RAM_OPER_MODE]++;
    game->ram[MYSMB_RAM_PRIMARY_HARD] =
        game->ram[MYSMB_RAM_WORLD_SELECT_ENABLE];
    game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
    game->ram[MYSMB_RAM_DEMO_TIMER] = 0U;
    offset = 0x17U;
    do {
        game->ram[(mysmb_u16)(MYSMB_RAM_SCORE_AND_COIN_END - offset)] = 0U;
        offset--;
    } while (offset != 0xffU);
}

void mysmb_game_initialize(struct mysmb_game *game)
{
    mysmb_u16 index;

    for (index = 0U; index < 0x0800U; ++index) {
        game->ram[index] = 0xffU;
    }
    mysmb_game_initialize_memory(game, 0xfeU);
    mysmb_game_move_all_sprites_offscreen(game);
    mysmb_game_initialize_name_tables(game);
    game->area_prg = 0;
    game->area_prg_size = 0U;
    game->area_command_count = 0U;
    /* InitializeGame has completed before GameMenuRoutine becomes task 3. */
    game->ram[MYSMB_RAM_OPER_MODE] = 0U;
    game->ram[MYSMB_RAM_OPER_MODE_TASK] = 3U;
    game->ram[MYSMB_RAM_DEMO_TIMER] = 0x18U;
    game->ram[0x0754U] = 1U;
    game->ram[0x075aU] = 2U;
    game->ram[0x0761U] = 2U;
    game->frame_number = 0UL;
}

/* Translation of ROM $90cc-$90e6 (InitializeMemory). */
void mysmb_game_initialize_memory(struct mysmb_game *game, mysmb_u8 initial_y)
{
    mysmb_u8 page;
    mysmb_u8 offset;

    page = 0x07U;
    offset = initial_y;
    do {
        do {
            if (page != 0x01U || offset < 0x60U) {
                game->ram[(mysmb_u16)((mysmb_u16)page * 0x0100U + offset)] = 0U;
            }
            offset = (mysmb_u8)(offset - 1U);
        } while (offset != 0xffU);
        page = (mysmb_u8)(page - 1U);
    } while (page != 0xffU);
}

/* Translation of ROM $8220-$8230 (MoveAllSpritesOffscreen). */
void mysmb_game_move_all_sprites_offscreen(struct mysmb_game *game)
{
    mysmb_u8 offset;

    offset = 0U;
    do {
        game->ram[(mysmb_u16)(0x0200U + offset)] = 0xf8U;
        offset = (mysmb_u8)(offset + 4U);
    } while (offset != 0U);
}

/* Translation of ROM $8e19-$8e5b (InitializeNameTables). */
void mysmb_game_initialize_name_tables(struct mysmb_game *game)
{
    mysmb_u8 table;
    mysmb_u16 offset;

    for (table = 0U; table < 2U; ++table) {
        for (offset = 0U; offset < 0x03c0U; ++offset) {
            game->name_table[table][offset] = 0x24U;
        }
        for (offset = 0x03c0U; offset < 0x0400U; ++offset) {
            game->name_table[table][offset] = 0U;
        }
    }
    game->ram[0x0300U] = 0U;
    game->ram[0x0301U] = 0U;
    game->ram[0x073fU] = 0U;
    game->ram[0x0740U] = 0U;
}

/* Translation of the name-table portion of ROM $8e92-$8eec. */
mysmb_u8 mysmb_game_apply_title_commands(struct mysmb_game *game,
                                         const mysmb_u8 *commands,
                                         mysmb_u16 command_size)
{
    mysmb_u16 cursor;
    mysmb_u16 address;
    mysmb_u16 offset;
    mysmb_u8 control;
    mysmb_u8 count;
    mysmb_u8 index;
    mysmb_u8 table;
    mysmb_u8 value;

    cursor = 0U;
    while (cursor < command_size && commands[cursor] != 0U) {
        if ((mysmb_u16)(command_size - cursor) < 3U) {
            return 0U;
        }
        address = (mysmb_u16)(((mysmb_u16)commands[cursor] << 8) |
                              commands[(mysmb_u16)(cursor + 1U)]);
        control = commands[(mysmb_u16)(cursor + 2U)];
        count = (mysmb_u8)(control & 0x3fU);
        if (count == 0U || (mysmb_u16)(command_size - cursor) <
            (mysmb_u16)(3U + ((control & 0x40U) != 0U ? 1U : count))) {
            return 0U;
        }
        if (address < 0x2000U || address >= 0x2800U) {
            return 0U;
        }
        table = (mysmb_u8)((address - 0x2000U) / 0x0400U);
        offset = (mysmb_u16)(address & 0x03ffU);
        value = commands[(mysmb_u16)(cursor + 3U)];
        for (index = 0U; index < count; ++index) {
            if (offset >= 0x0400U) {
                return 0U;
            }
            game->name_table[table][offset] = value;
            if ((control & 0x80U) != 0U) {
                offset = (mysmb_u16)(offset + 32U);
            }
            else {
                offset++;
            }
            if ((control & 0x40U) == 0U && (mysmb_u8)(index + 1U) < count) {
                value = commands[(mysmb_u16)(cursor + 3U + index + 1U)];
            }
        }
        cursor = (mysmb_u16)(cursor + 3U +
                              ((control & 0x40U) != 0U ? 1U : count));
    }
    return cursor < command_size ? 1U : 0U;
}

void mysmb_game_tick(struct mysmb_game *game, const struct mysmb_input *input,
                     struct mysmb_frame *frame)
{
    mysmb_u8 mode_before;
    mysmb_u8 task_before;
    struct mysmb_area_source area_source;

    mode_before = game->ram[MYSMB_RAM_OPER_MODE];
    task_before = game->ram[MYSMB_RAM_OPER_MODE_TASK];
    game->frame_number++;
    mysmb_game_tick_player_timers(game);
    mysmb_game_run_timer(game);
    mysmb_objects_apply_block_replacements(game);
    mysmb_objects_step_blocks(game);
    mysmb_objects_step_misc(game);
    mysmb_objects_step_fireballs(game);
    mysmb_objects_step_power_up(game);
    mysmb_objects_step_normal_enemies(game);
    mysmb_objects_step_floatey_numbers(game);
    mysmb_objects_step_vine(game);
    mysmb_game_title_step(game, input);
    if (mode_before == 1U && task_before == 0U) {
        mysmb_area_initialize(game);
        if (game->area_prg != 0) {
            area_source.prg = game->area_prg;
            area_source.prg_size = game->area_prg_size;
            if (mysmb_area_load_pointers(game, &area_source) != 0U) {
                (void)mysmb_area_parse_header(game, &area_source);
            }
        }
    }
    else if (mode_before == 1U && task_before == 1U) {
        (void)mysmb_area_emit_next_command(game);
        if (game->area_prg != 0) {
            area_source.prg = game->area_prg;
            area_source.prg_size = game->area_prg_size;
            (void)mysmb_area_spawn_next_enemy(game, &area_source);
        }
        if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 0U) {
            mysmb_player_initialize_entrance(game);
        }
        else if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 1U) {
            mysmb_player_step_auto_climb(game);
        }
        else if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 7U) {
            mysmb_player_finish_normal_entrance(game);
        }
        else if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 3U) {
            mysmb_player_step_vertical_pipe(game);
        }
        else if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 2U) {
            mysmb_player_step_side_pipe(game);
        }
        else if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 8U) {
            mysmb_player_step(game, input->buttons);
        }
        else if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 9U) {
            mysmb_player_step_change_size(game);
        }
        else if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 12U) {
            mysmb_player_step_fire_flower(game);
        }
        mysmb_objects_check_power_up_collision(game);
    }
    frame->sprite0_y = game->ram[0x0200U];
    frame->sprite0_x = game->ram[0x0203U];
    frame->start_pressed =
        (game->ram[MYSMB_RAM_SAVED_JOYPAD1] & MYSMB_BUTTON_START) != 0U;
    frame->operating_mode = game->ram[MYSMB_RAM_OPER_MODE];
    frame->operating_mode_task = game->ram[MYSMB_RAM_OPER_MODE_TASK];
}

/* ROM $8231/$8245/$8255, limited to the admitted title-menu start route. */
void mysmb_game_title_step(struct mysmb_game *game, const struct mysmb_input *input)
{
    mysmb_u8 buttons;

    buttons = mysmb_game_latch_joypad1(game, input->buttons);
    if (game->ram[MYSMB_RAM_OPER_MODE] != 0U ||
        game->ram[MYSMB_RAM_OPER_MODE_TASK] != 3U) {
        return;
    }
    if (buttons == MYSMB_BUTTON_START ||
        buttons == (MYSMB_BUTTON_A | MYSMB_BUTTON_START)) {
        mysmb_game_start_from_title(game, buttons);
    }
    else if (buttons == MYSMB_BUTTON_SELECT &&
             game->ram[MYSMB_RAM_DEMO_TIMER] != 0U &&
             game->ram[MYSMB_RAM_SELECT_TIMER] == 0U) {
        game->ram[MYSMB_RAM_DEMO_TIMER] = 0x18U;
        game->ram[MYSMB_RAM_SELECT_TIMER] = 0x10U;
        game->ram[MYSMB_RAM_NUMBER_OF_PLAYERS] ^= 1U;
    }
}

void mysmb_game_checkpoint(const struct mysmb_game *game,
                           struct mysmb_checkpoint *checkpoint)
{
    checkpoint->frame_number = game->frame_number;
    checkpoint->operating_mode = game->ram[MYSMB_RAM_OPER_MODE];
    checkpoint->operating_mode_task = game->ram[MYSMB_RAM_OPER_MODE_TASK];
    checkpoint->saved_joypad1_bits = game->ram[MYSMB_RAM_SAVED_JOYPAD1];
    checkpoint->demo_timer = game->ram[MYSMB_RAM_DEMO_TIMER];
    checkpoint->world_number = game->ram[MYSMB_RAM_WORLD];
    checkpoint->area_number = game->ram[MYSMB_RAM_AREA];
}
