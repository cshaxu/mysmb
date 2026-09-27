#include "game/game.h"
#include "game/frame_root.h"
#include "game/area.h"
#include "game/title_modes.h"

/* TitleScreenMode and GameMenuRoutine own this complete subtree.  These are
 * CPU-RAM addresses from the source labels, kept local until the remaining
 * mode subtrees move out of game.c. */
enum {
    MYSMB_RAM_SAVED_JOYPAD1 = 0x06fcU,
    MYSMB_RAM_SAVED_JOYPAD2 = 0x06fdU,
    MYSMB_RAM_HIDDEN_1UP = 0x075dU,
    MYSMB_RAM_WORLD = 0x075fU,
    MYSMB_RAM_AREA = 0x0760U,
    MYSMB_RAM_OFFSCREEN_HIDDEN_1UP = 0x0764U,
    MYSMB_RAM_OFFSCREEN_WORLD = 0x0766U,
    MYSMB_RAM_OFFSCREEN_AREA = 0x0767U,
    MYSMB_RAM_PRIMARY_HARD = 0x076aU,
    MYSMB_RAM_WORLD_SELECT_NUMBER = 0x076bU,
    MYSMB_RAM_OPER_MODE = 0x0770U,
    MYSMB_RAM_OPER_MODE_TASK = 0x0772U,
    MYSMB_RAM_DISABLE_SCREEN = 0x0774U,
    MYSMB_RAM_NUMBER_OF_PLAYERS = 0x077aU,
    MYSMB_RAM_SELECT_TIMER = 0x0780U,
    MYSMB_RAM_SCREEN_ROUTINE_TASK = 0x073cU,
    MYSMB_RAM_SPRITE0_HIT = 0x0722U,
    MYSMB_RAM_AREA_MUSIC_QUEUE = 0x00fbU,
    MYSMB_RAM_DEMO_ACTION = 0x0717U,
    MYSMB_RAM_DEMO_ACTION_TIMER = 0x0718U,
    MYSMB_RAM_DEMO_TIMER = 0x07a2U,
    MYSMB_RAM_SOUND_MEMORY = 0x07b0U,
    MYSMB_RAM_FRAME_COUNTER = 0x0009U,
    MYSMB_RAM_WORLD_SELECT_ENABLE = 0x07fcU,
    MYSMB_RAM_CONTINUE_WORLD = 0x07fdU,
    MYSMB_RAM_FETCH_NEW_TIMER = 0x0757U,
    MYSMB_RAM_SCORE_AND_COIN_END = 0x07ddU,
    MYSMB_RAM_VRAM_BUFFER1_OFFSET = 0x0300U
};

/* ROM title ScreenRoutines task 8 renders the title-demo area's lead-in
 * before DrawTitleScreen overlays its own stream.  Keep the title-menu task
 * owner intact after borrowing the shared area-output route. */
static mysmb_u8 mysmb_game_apply_title_area(struct mysmb_game *game)
{
    struct mysmb_area_source source;
    mysmb_u8 mode_task;

    if (game->area_prg == 0) return 0U;
    source.prg = game->area_prg;
    source.prg_size = game->area_prg_size;
    mode_task = game->ram[MYSMB_RAM_OPER_MODE_TASK];
    mysmb_area_initialize(game);
    mysmb_game_move_all_sprites_offscreen(game);
    if (mysmb_area_load_pointers(game, &source) == 0U ||
        mysmb_area_parse_header(game, &source) == 0U) {
        game->ram[MYSMB_RAM_OPER_MODE_TASK] = mode_task;
        return 0U;
    }
    mysmb_area_render_initial_terrain(game);
    mysmb_area_render_initial_objects(game);
    game->ram[MYSMB_RAM_OPER_MODE_TASK] = mode_task;
    return 1U;
}

/* ROM $830e GoContinue.  Return zero for the source's LDX #$00 result. */
static mysmb_u8 mysmb_game_go_continue(struct mysmb_game *game, mysmb_u8 world)
{
    game->ram[MYSMB_RAM_WORLD] = world;
    game->ram[MYSMB_RAM_OFFSCREEN_WORLD] = world;
    game->ram[MYSMB_RAM_AREA] = 0U;
    game->ram[MYSMB_RAM_OFFSCREEN_AREA] = 0U;
    return 0U;
}

/* ROM $82d8 ChkContinue.  The caller has already made the source's exact
 * Start/A+Start comparison.  A set A bit is therefore the ASL carry path. */
static mysmb_u8 mysmb_game_chk_continue(struct mysmb_game *game,
                                        mysmb_u8 buttons)
{
    if (game->ram[MYSMB_RAM_DEMO_TIMER] == 0U) {
        mysmb_game_reset_title(game);
        return 0U;
    }
    if ((buttons & MYSMB_BUTTON_A) != 0U) {
        (void)mysmb_game_go_continue(game,
                                     game->ram[MYSMB_RAM_CONTINUE_WORLD]);
    }
    return 1U;
}

/* ROM $8307 InitScores.  The source enters it by fallthrough from
 * StartWorld1; keep its score clear separate from the preceding mode entry. */
static void mysmb_game_init_scores(struct mysmb_game *game)
{
    mysmb_u8 offset;

    offset = 0x17U;
    do {
        game->ram[(mysmb_u16)(MYSMB_RAM_SCORE_AND_COIN_END - offset)] = 0U;
        offset--;
    } while (offset != 0xffU);
}

/* ROM $830d ExitMenu is an RTS with no state write. */
static void mysmb_game_exit_menu(void)
{
}

/* ROM $82e6 StartWorld1.  Pointer loading is owned by M2 T3; this boundary
 * deliberately has no title-input decision. */
static void mysmb_game_start_world1(struct mysmb_game *game)
{
    struct mysmb_area_source source;

    /* The ROM calls LoadAreaPointer before every StartWorld1 mode write. */
    if (game->area_prg != 0) {
        source.prg = game->area_prg;
        source.prg_size = game->area_prg_size;
        (void)mysmb_area_load_area_pointer(game, &source);
    }
    game->ram[MYSMB_RAM_HIDDEN_1UP]++;
    game->ram[MYSMB_RAM_OFFSCREEN_HIDDEN_1UP]++;
    game->ram[MYSMB_RAM_FETCH_NEW_TIMER]++;
    game->ram[MYSMB_RAM_OPER_MODE]++;
    game->ram[MYSMB_RAM_PRIMARY_HARD] =
        game->ram[MYSMB_RAM_WORLD_SELECT_ENABLE];
    game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
    game->ram[MYSMB_RAM_DEMO_TIMER] = 0U;
    mysmb_game_init_scores(game);
    mysmb_game_exit_menu();
}

/* ROM $8255 StartGame is the direct jump into ChkContinue. */
static void mysmb_game_start_from_title(struct mysmb_game *game, mysmb_u8 buttons)
{
    if (mysmb_game_chk_continue(game, buttons) != 0U) {
        mysmb_game_start_world1(game);
    }
}

mysmb_u8 mysmb_game_apply_title_commands(struct mysmb_game *game,
                                         const mysmb_u8 *commands,
                                         mysmb_u16 command_size)
{
    /* Title ScreenRoutines writes the fixed status line before it transfers
     * DrawTitleScreen's owner-local command stream. */
    if (game->area_prg != 0) {
        if (mysmb_area_queue_top_status_line(game) == 0U) return 0U;
        mysmb_game_commit_vram_buffer(game);
        if (mysmb_game_apply_title_area(game) == 0U) return 0U;
        if (mysmb_area_queue_bottom_status_line(game) == 0U) return 0U;
        mysmb_game_commit_vram_buffer(game);
    }
    if (mysmb_game_apply_vram_commands(game, commands, command_size) == 0U) {
        return 0U;
    }
    /* Title ScreenRoutines reaches the ground palette then GetPlayerColors
     * before DrawTitleScreen.  The explicit title loader presents their
     * committed state, matching the first visible title frame. */
    if (game->area_prg == 0) {
        game->ram[MYSMB_RAM_DISABLE_SCREEN] = 0U;
        mysmb_game_commit_display_state(game);
        return 1U;
    }
    if (mysmb_area_apply_palette(game, 1U) == 0U ||
        mysmb_area_queue_player_palette(game) == 0U) {
        return 0U;
    }
    mysmb_game_commit_vram_buffer(game);
    /* The title route has completed its name-table and palette transfers.
     * Its next NMI restores the normal visible mask before Start can begin
     * the game-area sequence. */
    game->ram[MYSMB_RAM_DISABLE_SCREEN] = 0U;
    mysmb_game_commit_display_state(game);
    return 1U;
}

void mysmb_game_bind_title_source(struct mysmb_game *game,
                                  const mysmb_u8 *title_data,
                                  mysmb_u16 title_data_size,
                                  const mysmb_u8 *icon_data,
                                  mysmb_u16 icon_data_size)
{
    game->title_data = title_data;
    game->title_data_size = title_data_size;
    game->title_icon_data = icon_data;
    game->title_icon_data_size = icon_data_size;
}

mysmb_u8 mysmb_game_begin_title_bootstrap(struct mysmb_game *game)
{
    struct mysmb_area_source source;
    mysmb_u8 index;

    if (game->area_prg == 0 || game->title_data == 0 ||
        game->title_data_size != MYSMB_TITLE_BUFFER_SIZE ||
        game->title_icon_data == 0 || game->title_icon_data_size == 0U) {
        return 0U;
    }
    source.prg = game->area_prg;
    source.prg_size = game->area_prg_size;
    /* ROM InitializeGame falls through to InitializeArea.  Preserve every
     * source step: InitializeMemory($6f), the 32-byte sound clear, DemoTimer,
     * LoadAreaPointer, then InitializeArea.  In particular, InitializeArea's
     * smaller $4b clear deliberately retains the pointer state just loaded. */
    mysmb_game_initialize_memory(game, 0x6fU);
    for (index = 0U; index < 0x20U; ++index) {
        game->ram[(mysmb_u16)(MYSMB_RAM_SOUND_MEMORY + index)] = 0U;
    }
    game->ram[MYSMB_RAM_DEMO_TIMER] = 0x18U;
    if (mysmb_area_load_area_pointer(game, &source) == 0U) {
        return 0U;
    }
    mysmb_area_initialize(game);
    if (mysmb_area_get_data_addresses(game, &source) == 0U ||
        mysmb_area_parse_header(game, &source) == 0U) {
        return 0U;
    }
    return 1U;
}

/* ROM $8325-$8338, DrawMushroomIcon.  The eight-byte source is bound
 * owner-local; its first byte is the Buffer1 offset and the next seven are
 * the transfer command. */
void mysmb_game_draw_mushroom_icon(struct mysmb_game *game)
{
    mysmb_u16 index;

    if (game->title_icon_data == 0 || game->title_icon_data_size != 8U) {
        return;
    }
    /* ROM $8328 IconDataRead copies MushroomIconData[7..0] to
     * VRAM_Buffer1-1[7..0].  Keep the first data byte as the source-owned
     * Buffer1 offset instead of synthesizing it from a payload length. */
    index = 8U;
    do {
        index--;
        game->ram[(mysmb_u16)(MYSMB_RAM_VRAM_BUFFER1_OFFSET + index)] =
            game->title_icon_data[index];
    } while (index != 0U);
    if (game->ram[MYSMB_RAM_NUMBER_OF_PLAYERS] != 0U) {
        game->ram[0x0304U] = 0x24U;
        game->ram[0x0306U] = 0xceU;
    }
}

/* ROM $8224, ResetTitle. */
void mysmb_game_reset_title(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_OPER_MODE] = 0U;
    game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
    game->ram[MYSMB_RAM_SPRITE0_HIT] = 0U;
    game->ram[MYSMB_RAM_DISABLE_SCREEN]++;
}

/* ROM $836b-$838a DemoEngine.  It returns one only after the terminal zero
 * timing byte, which sends GameMenuRoutine back through ResetTitle. */
static mysmb_u8 mysmb_game_step_title_demo(struct mysmb_game *game)
{
    static const mysmb_u8 action_data[21] = {
        0x01U, 0x80U, 0x02U, 0x81U, 0x41U, 0x80U, 0x01U,
        0x42U, 0xc2U, 0x02U, 0x80U, 0x41U, 0xc1U, 0x41U,
        0xc1U, 0x01U, 0xc1U, 0x01U, 0x02U, 0x80U, 0x00U
    };
    static const mysmb_u8 timing_data[22] = {
        0x9bU, 0x10U, 0x18U, 0x05U, 0x2cU, 0x20U, 0x24U,
        0x15U, 0x5aU, 0x10U, 0x20U, 0x28U, 0x30U, 0x20U,
        0x10U, 0x80U, 0x20U, 0x30U, 0x30U, 0x01U, 0xffU,
        0x00U
    };
    mysmb_u8 action;

    action = game->ram[MYSMB_RAM_DEMO_ACTION];
    if (game->ram[MYSMB_RAM_DEMO_ACTION_TIMER] == 0U) {
        action++;
        game->ram[MYSMB_RAM_DEMO_ACTION] = action;
        if (action == 0U || action > 22U) return 1U;
        game->ram[MYSMB_RAM_DEMO_ACTION_TIMER] = timing_data[action - 1U];
        if (game->ram[MYSMB_RAM_DEMO_ACTION_TIMER] == 0U) return 1U;
    }
    game->ram[MYSMB_RAM_SAVED_JOYPAD1] = action_data[action - 1U];
    game->ram[MYSMB_RAM_DEMO_ACTION_TIMER]--;
    return 0U;
}

/* ROM $8231/$8245/$8255 GameMenuRoutine.  The title menu still runs
 * GameCoreRoutine every frame; once DemoTimer expires DemoEngine replaces the
 * latched controller byte before that common route consumes it. */
mysmb_u8 mysmb_game_title_step(struct mysmb_game *game, const struct mysmb_input *input)
{
    static const mysmb_u8 world_select_template[6] = {
        0x04U, 0x20U, 0x73U, 0x01U, 0x00U, 0x00U
    };
    mysmb_u8 buttons;
    mysmb_u8 index;
    mysmb_u8 world;

    (void)input;
    buttons = (mysmb_u8)(game->ram[MYSMB_RAM_SAVED_JOYPAD1] |
        game->ram[MYSMB_RAM_SAVED_JOYPAD2]);
    if (game->ram[MYSMB_RAM_OPER_MODE] != 0U ||
        game->ram[MYSMB_RAM_OPER_MODE_TASK] != 3U) {
        return 0U;
    }
    if (buttons == MYSMB_BUTTON_START ||
        buttons == (MYSMB_BUTTON_A | MYSMB_BUTTON_START)) {
        mysmb_game_start_from_title(game, buttons);
        return 0U;
    }
    if (buttons == MYSMB_BUTTON_SELECT) {
        if (game->ram[MYSMB_RAM_DEMO_TIMER] == 0U) {
            mysmb_game_reset_title(game);
            return 0U;
        }
        game->ram[MYSMB_RAM_DEMO_TIMER] = 0x18U;
        if (game->ram[MYSMB_RAM_SELECT_TIMER] == 0U) {
            game->ram[MYSMB_RAM_SELECT_TIMER] = 0x10U;
            game->ram[MYSMB_RAM_NUMBER_OF_PLAYERS] ^= 1U;
            mysmb_game_draw_mushroom_icon(game);
        }
    }
    else if (game->ram[MYSMB_RAM_WORLD_SELECT_ENABLE] != 0U &&
             buttons == MYSMB_BUTTON_B) {
        if (game->ram[MYSMB_RAM_DEMO_TIMER] == 0U) {
            mysmb_game_reset_title(game);
            return 0U;
        }
        game->ram[MYSMB_RAM_DEMO_TIMER] = 0x18U;
        if (game->ram[MYSMB_RAM_SELECT_TIMER] == 0U) {
            game->ram[MYSMB_RAM_SELECT_TIMER] = 0x10U;
            index = (mysmb_u8)((game->ram[MYSMB_RAM_WORLD_SELECT_NUMBER] +
                                 1U) & 7U);
            game->ram[MYSMB_RAM_WORLD_SELECT_NUMBER] = index;
            index = mysmb_game_go_continue(game, index);
            while (index < 6U) {
                game->ram[(mysmb_u16)(MYSMB_RAM_VRAM_BUFFER1_OFFSET + index)] =
                    world_select_template[index];
                index++;
            }
            world = (mysmb_u8)(game->ram[MYSMB_RAM_WORLD] + 1U);
            game->ram[0x0304U] = world;
        }
    }
    if (game->ram[MYSMB_RAM_DEMO_TIMER] != 0U) {
        game->ram[MYSMB_RAM_SAVED_JOYPAD1] = 0U;
        return 1U;
    }
    game->ram[MYSMB_RAM_SELECT_TIMER] = buttons;
    if (mysmb_game_step_title_demo(game) != 0U) {
        mysmb_game_reset_title(game);
        return 0U;
    }
    return 1U;
}
