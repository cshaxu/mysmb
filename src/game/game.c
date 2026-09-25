#include "game/game.h"
#include "game/area.h"
#include "game/audio.h"
#include "game/player.h"
#include "game/objects.h"

enum {
    MYSMB_RAM_GAME_ENGINE_SUBROUTINE = 0x000eU,
    MYSMB_RAM_PLAYER_LEFT_RIGHT_BUTTONS = 0x000cU,
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
    MYSMB_RAM_PLAYER_SIZE = 0x0754U,
    MYSMB_RAM_PLAYER_STATUS = 0x0756U,
    MYSMB_RAM_TIMER_EXPIRED = 0x0759U,
    MYSMB_RAM_GAME_TIMER_CONTROL = 0x0787U,
    MYSMB_RAM_GAME_TIMER_HUNDREDS = 0x07f8U,
    MYSMB_RAM_SELECT_TIMER = 0x0780U,
    MYSMB_RAM_INTERVAL_TIMER_CONTROL = 0x077fU,
    MYSMB_RAM_TIMERS = 0x0780U,
    MYSMB_RAM_DEMO_TIMER = 0x07a2U,
    MYSMB_RAM_PSEUDORANDOM = 0x07a7U,
    MYSMB_RAM_WARM_BOOT_VALIDATION = 0x07ffU,
    MYSMB_RAM_WORLD_SELECT_ENABLE = 0x07fcU,
    MYSMB_RAM_CONTINUE_WORLD = 0x07fdU,
    MYSMB_RAM_SCORE_AND_COIN_END = 0x07ddU,
    MYSMB_RAM_FRAME_COUNTER = 0x0009U,
    MYSMB_RAM_PLAYER_SPRITE_ATTRIBUTES = 0x03c4U,
    MYSMB_RAM_STAR_INVINCIBLE_TIMER = 0x079fU,
    MYSMB_RAM_VRAM_BUFFER1_OFFSET = 0x0300U,
    MYSMB_RAM_VRAM_BUFFER1 = 0x0301U,
    MYSMB_RAM_VRAM_BUFFER2_OFFSET = 0x0340U,
    MYSMB_RAM_VRAM_BUFFER2 = 0x0341U,
    MYSMB_RAM_VRAM_ADDRESS_CONTROL = 0x0773U,
    MYSMB_RAM_PPU_CONTROL_MIRROR = 0x0778U,
    MYSMB_RAM_PPU_MASK_MIRROR = 0x0779U,
    MYSMB_RAM_PARSER_TASK = 0x071fU,
    MYSMB_RAM_SCROLL_THIRTY_TWO = 0x073dU,
    MYSMB_RAM_HORIZONTAL_SCROLL = 0x073fU,
    MYSMB_RAM_VERTICAL_SCROLL = 0x0740U,
    MYSMB_RAM_BACKGROUND_COLOR = 0x0744U,
    MYSMB_RAM_AREA_TYPE = 0x074eU,
    MYSMB_RAM_PLAYER_ENTRANCE = 0x0710U,
    MYSMB_RAM_CLOUD_OVERRIDE = 0x0743U,
    MYSMB_RAM_ALT_ENTRANCE = 0x0769U,
    MYSMB_RAM_AREA_MUSIC_QUEUE = 0x00fbU,
    MYSMB_RAM_DEMO_ACTION = 0x0717U,
    MYSMB_RAM_DEMO_ACTION_TIMER = 0x0718U
};

enum {
    MYSMB_RAM_SCREEN_ROUTINE_TASK = 0x073cU,
    MYSMB_RAM_SPRITE0_HIT = 0x0722U,
    MYSMB_RAM_DISABLE_SCREEN = 0x0774U,
    MYSMB_RAM_EVENT_MUSIC = 0x00fcU,
    MYSMB_RAM_SCREEN_TIMER = 0x07a0U,
    MYSMB_RAM_NUMBER_OF_LIVES = 0x075aU,
    MYSMB_RAM_HALFWAY_PAGE = 0x075bU,
    MYSMB_RAM_LEVEL = 0x075cU,
    MYSMB_RAM_STAR_FLAG_TASK = 0x0746U,
    MYSMB_RAM_PLAYER_Y = 0x00ceU,
    MYSMB_RAM_PLAYER_X = 0x0086U,
    MYSMB_RAM_PLAYER_PAGE = 0x006dU,
    MYSMB_RAM_ENEMY_FLAG = 0x000fU,
    MYSMB_RAM_SCREEN_RIGHT_PAGE = 0x071bU,
    MYSMB_RAM_DESTINATION_PAGE = 0x0034U,
    MYSMB_RAM_VICTORY_WALK = 0x0035U,
    MYSMB_RAM_PRIMARY_MESSAGE = 0x0719U,
    MYSMB_RAM_SECONDARY_MESSAGE = 0x0749U,
    MYSMB_RAM_WORLD_END_TIMER = 0x07a1U,
    MYSMB_RAM_CURRENT_PLAYER = 0x0753U,
    MYSMB_RAM_OFFSCREEN_LIVES = 0x0761U,
    MYSMB_RAM_SPRITE_SHUFFLE_CONTROL = 0x06e0U,
    MYSMB_RAM_SPRITE_SHUFFLE_AMOUNTS = 0x06e1U,
    MYSMB_RAM_SPRITE_OFFSETS = 0x06e4U,
    MYSMB_RAM_MISC_SPRITE_OFFSETS = 0x06f3U,
    MYSMB_RAM_OAM = 0x0200U
};

static void mysmb_game_continue_game(struct mysmb_game *game);
static mysmb_u8 mysmb_game_transpose_players(struct mysmb_game *game);
static void mysmb_game_lose_life(struct mysmb_game *game);
static void mysmb_game_step_game_over(struct mysmb_game *game);
static void mysmb_game_next_area(struct mysmb_game *game);
static void mysmb_game_step_victory(struct mysmb_game *game);
static void mysmb_game_print_victory_messages(struct mysmb_game *game);
static void mysmb_game_step_screen_routine(struct mysmb_game *game);
static void mysmb_game_primary_setup(struct mysmb_game *game);
static void mysmb_game_secondary_setup(struct mysmb_game *game);
static void mysmb_game_commit_vram_buffer(struct mysmb_game *game);
static void mysmb_game_step_area_parser(struct mysmb_game *game);
static void mysmb_game_commit_display_state(struct mysmb_game *game);
static void mysmb_game_shuffle_sprite_offsets(struct mysmb_game *game);
static void mysmb_game_submit_oam(struct mysmb_game *game);

/* ROM GameEngine: NoChgMus / CyclePlayerPalette / ResetPalStar.
 * PlayerGfxHandler has already consumed this attribute for the current OAM
 * DMA; this tail updates it for the following frame. */
static void mysmb_game_cycle_player_palette(struct mysmb_game *game)
{
    mysmb_u8 color;

    if (game->ram[MYSMB_RAM_PLAYER_Y_HIGH] < 2U &&
        game->ram[MYSMB_RAM_STAR_INVINCIBLE_TIMER] == 0U) {
        game->ram[MYSMB_RAM_PLAYER_SPRITE_ATTRIBUTES] &= 0xfcU;
        return;
    }

    color = game->ram[MYSMB_RAM_FRAME_COUNTER];
    if (game->ram[MYSMB_RAM_STAR_INVINCIBLE_TIMER] < 8U) {
        color = (mysmb_u8)(color >> 2U);
    }
    color = (mysmb_u8)((color >> 1U) & 3U);
    game->ram[MYSMB_RAM_PLAYER_SPRITE_ATTRIBUTES] =
        (mysmb_u8)((game->ram[MYSMB_RAM_PLAYER_SPRITE_ATTRIBUTES] & 0xfcU) |
                   color);
}
/* DrawTitleScreen copies this many bytes into CPU RAM $0300-$0439. */
enum {
    MYSMB_TITLE_BUFFER_SIZE = 0x013aU,
    MYSMB_TITLE_ICON_BUFFER_OFFSET = 0x0301U
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

/* The 2C02 mirrors sprite entries $3f10/$14/$18/$1c onto the matching
 * universal/background entries.  The portable snapshot deliberately keeps
 * all 32 backing bytes, so the four mirrored source slots remain untouched. */
static mysmb_u8 mysmb_game_palette_offset(mysmb_u16 address)
{
    mysmb_u8 offset;

    offset = (mysmb_u8)(address & 0x001fU);
    if (offset == 0x10U || offset == 0x14U || offset == 0x18U ||
        offset == 0x1cU) {
        offset = (mysmb_u8)(offset - 0x10U);
    }
    return offset;
}

/* ROM NMI RotPRandomBit.  The carry derives from d1 of the first two
 * registers, then propagates through seven consecutive ROR instructions. */
static void mysmb_game_rotate_pseudorandom(struct mysmb_game *game)
{
    mysmb_u8 index;
    mysmb_u8 carry;
    mysmb_u8 next_carry;
    mysmb_u8 value;

    carry = ((game->ram[MYSMB_RAM_PSEUDORANDOM] & 2U) ^ (game->ram[0x07a8U] & 2U)) != 0U ?
        1U : 0U;
    for (index = 0U; index < 7U; ++index) {
        value = game->ram[(mysmb_u16)(MYSMB_RAM_PSEUDORANDOM + index)];
        next_carry = value & 1U;
        game->ram[(mysmb_u16)(MYSMB_RAM_PSEUDORANDOM + index)] = (mysmb_u8)((value >> 1U) |
            (carry != 0U ? 0x80U : 0U));
        carry = next_carry;
    }
}
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

/* ROM RunGameTimer.  The audio subsystem consumes its queue on a following
 * frame; ForceInjury retains collision's single death-state owner. */
static mysmb_u8 mysmb_game_run_timer(struct mysmb_game *game)
{
    mysmb_u16 digit;

    if (game->ram[MYSMB_RAM_OPER_MODE] == 0U ||
        game->ram[MYSMB_RAM_OPER_MODE_TASK] < 2U ||
        game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] < 8U ||
        game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 0x0bU ||
        game->ram[MYSMB_RAM_PLAYER_Y_HIGH] >= 2U ||
        game->ram[MYSMB_RAM_GAME_TIMER_CONTROL] != 0U) return 0U;
    if ((game->ram[MYSMB_RAM_GAME_TIMER_HUNDREDS] |
         game->ram[MYSMB_RAM_GAME_TIMER_HUNDREDS + 1U] |
         game->ram[MYSMB_RAM_GAME_TIMER_HUNDREDS + 2U]) == 0U) {
        game->ram[MYSMB_RAM_PLAYER_STATUS] = 0U;
        mysmb_objects_force_injury(game);
        game->ram[MYSMB_RAM_TIMER_EXPIRED]++;
        return 0U;
    }
    if (game->ram[MYSMB_RAM_GAME_TIMER_HUNDREDS] == 1U &&
        game->ram[MYSMB_RAM_GAME_TIMER_HUNDREDS + 1U] == 0U &&
        game->ram[MYSMB_RAM_GAME_TIMER_HUNDREDS + 2U] == 0U) {
        game->ram[MYSMB_RAM_EVENT_MUSIC] = 0x40U;
    }
    game->ram[MYSMB_RAM_GAME_TIMER_CONTROL] = 0x18U;
    digit = MYSMB_RAM_GAME_TIMER_HUNDREDS + 2U;
    while (game->ram[digit] == 0U) {
        game->ram[digit] = 9U;
        digit--;
    }
    game->ram[digit]--;
    return 1U;
}

/* ROM TransposePlayers.  The seven-byte player records deliberately include
 * life, checkpoint, level, coin tally, world, and area as one transaction. */
static mysmb_u8 mysmb_game_transpose_players(struct mysmb_game *game)
{
    mysmb_u8 offset;
    mysmb_u8 saved;

    if (game->ram[MYSMB_RAM_NUMBER_OF_PLAYERS] == 0U ||
        game->ram[MYSMB_RAM_OFFSCREEN_LIVES] >= 0x80U) return 0U;
    game->ram[MYSMB_RAM_CURRENT_PLAYER] ^= 1U;
    for (offset = 0U; offset < 7U; ++offset) {
        saved = game->ram[MYSMB_RAM_NUMBER_OF_LIVES + offset];
        game->ram[MYSMB_RAM_NUMBER_OF_LIVES + offset] =
            game->ram[MYSMB_RAM_OFFSCREEN_LIVES + offset];
        game->ram[MYSMB_RAM_OFFSCREEN_LIVES + offset] = saved;
    }
    return 1U;
}

/* ROM ContinueGame.  Area initialization remains the existing mode-task zero
 * owner, so this routine only restores the original preserved game state. */
static void mysmb_game_continue_game(struct mysmb_game *game)
{
    game->ram[0x0754U] = 1U;
    game->ram[MYSMB_RAM_FETCH_NEW_TIMER]++;
    game->ram[MYSMB_RAM_TIMER_CONTROL] = 0U;
    game->ram[MYSMB_RAM_PLAYER_STATUS] = 0U;
    game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] = 0U;
    game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
    game->ram[MYSMB_RAM_OPER_MODE] = 1U;
}

/* ROM NextArea.  LoadAreaPointer remains the following mode-task zero owner. */
static void mysmb_game_next_area(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_AREA]++;
    game->ram[MYSMB_RAM_FETCH_NEW_TIMER]++;
    game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
    game->ram[MYSMB_RAM_HALFWAY_PAGE] = 0U;
    game->ram[MYSMB_RAM_EVENT_MUSIC] = 0U;
    game->ram[MYSMB_RAM_DISABLE_SCREEN]++;
    game->ram[MYSMB_RAM_SPRITE0_HIT] = 0U;
}

/* ROM PlayerLoseLife.  The half-way table stays here because it is game-mode
 * ownership, not an area renderer concern. */
static void mysmb_game_lose_life(struct mysmb_game *game)
{
    static const mysmb_u8 halfway_nybbles[16] = {
        0x56U, 0x40U, 0x65U, 0x70U, 0x66U, 0x40U, 0x66U, 0x40U,
        0x66U, 0x40U, 0x66U, 0x60U, 0x65U, 0x70U, 0x00U, 0x00U
    };
    mysmb_u8 index;
    mysmb_u8 checkpoint;

    game->ram[MYSMB_RAM_DISABLE_SCREEN]++;
    game->ram[MYSMB_RAM_SPRITE0_HIT] = 0U;
    game->ram[MYSMB_RAM_EVENT_MUSIC] = 0U;
    game->ram[MYSMB_RAM_NUMBER_OF_LIVES]--;
    if (game->ram[MYSMB_RAM_NUMBER_OF_LIVES] >= 0x80U) {
        game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
        game->ram[MYSMB_RAM_OPER_MODE] = 3U;
        return;
    }
    index = (mysmb_u8)(game->ram[MYSMB_RAM_WORLD] << 1U);
    if ((game->ram[MYSMB_RAM_LEVEL] & 2U) != 0U) index++;
    checkpoint = halfway_nybbles[index];
    if ((game->ram[MYSMB_RAM_LEVEL] & 1U) == 0U) checkpoint >>= 4U;
    checkpoint &= 0x0fU;
    if (checkpoint > game->ram[0x071aU]) checkpoint = 0U;
    game->ram[MYSMB_RAM_HALFWAY_PAGE] = checkpoint;
    (void)mysmb_game_transpose_players(game);
    mysmb_game_continue_game(game);
}

/* ROM SetupGameOver, ScreenRoutines, and RunGameOver. */
static void mysmb_game_step_game_over(struct mysmb_game *game)
{
    if (game->ram[MYSMB_RAM_OPER_MODE_TASK] == 0U) {
        game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 0U;
        game->ram[MYSMB_RAM_SPRITE0_HIT] = 0U;
        game->ram[MYSMB_RAM_EVENT_MUSIC] = 2U;
        game->ram[MYSMB_RAM_DISABLE_SCREEN]++;
        game->ram[MYSMB_RAM_OPER_MODE_TASK] = 1U;
        return;
    }
    if (game->ram[MYSMB_RAM_OPER_MODE_TASK] == 1U) {
        mysmb_game_step_screen_routine(game);
        return;
    }
    game->ram[MYSMB_RAM_DISABLE_SCREEN] = 0U;
    if ((game->ram[MYSMB_RAM_SAVED_JOYPAD1] & MYSMB_BUTTON_START) == 0U &&
        game->ram[MYSMB_RAM_SCREEN_TIMER] != 0U) return;
    game->ram[MYSMB_RAM_EVENT_MUSIC] = 0U;
    if (mysmb_game_transpose_players(game) != 0U) {
        mysmb_game_continue_game(game);
        return;
    }
    game->ram[MYSMB_RAM_CONTINUE_WORLD] = game->ram[MYSMB_RAM_WORLD];
    game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
    game->ram[MYSMB_RAM_SCREEN_TIMER] = 0U;
    game->ram[MYSMB_RAM_OPER_MODE] = 0U;
}

/* ROM VictoryModeSubroutines.  The bridge's tile/OAM presentation is outside
 * this core; mode ownership starts with the same setup task after it falls. */
static void mysmb_game_step_victory(struct mysmb_game *game)
{
    if (game->ram[MYSMB_RAM_OPER_MODE_TASK] == 0U) {
        if (mysmb_objects_step_bridge_collapse(game) != 0U)
            game->ram[MYSMB_RAM_OPER_MODE_TASK] = 1U;
        return;
    }
    if (game->ram[MYSMB_RAM_OPER_MODE_TASK] == 1U) {
        game->ram[MYSMB_RAM_DESTINATION_PAGE] =
            (mysmb_u8)(game->ram[MYSMB_RAM_SCREEN_RIGHT_PAGE] + 1U);
        game->ram[MYSMB_RAM_EVENT_MUSIC] = 8U;
        game->ram[MYSMB_RAM_OPER_MODE_TASK] = 2U;
        return;
    }
    if (game->ram[MYSMB_RAM_OPER_MODE_TASK] == 2U) {
        game->ram[MYSMB_RAM_VICTORY_WALK] = 0U;
        if (game->ram[MYSMB_RAM_PLAYER_PAGE] != game->ram[MYSMB_RAM_DESTINATION_PAGE] ||
            game->ram[MYSMB_RAM_PLAYER_X] < 0x60U) {
            game->ram[MYSMB_RAM_VICTORY_WALK] = 1U;
            mysmb_player_step(game, MYSMB_BUTTON_RIGHT);
            return;
        }
        game->ram[MYSMB_RAM_OPER_MODE_TASK] = 3U;
        return;
    }
    if (game->ram[MYSMB_RAM_OPER_MODE_TASK] == 3U) {
        mysmb_game_print_victory_messages(game);
        return;
    }
    if (game->ram[MYSMB_RAM_WORLD_END_TIMER] != 0U) {
        game->ram[MYSMB_RAM_WORLD_END_TIMER]--;
        return;
    }
    if (game->ram[MYSMB_RAM_WORLD] < 7U) {
        game->ram[MYSMB_RAM_AREA] = 0U;
        game->ram[MYSMB_RAM_LEVEL] = 0U;
        game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
        game->ram[MYSMB_RAM_WORLD]++;
        game->ram[MYSMB_RAM_FETCH_NEW_TIMER]++;
        game->ram[MYSMB_RAM_OPER_MODE] = 1U;
    }
    else if ((game->ram[MYSMB_RAM_SAVED_JOYPAD1] & MYSMB_BUTTON_B) != 0U) {
        game->ram[MYSMB_RAM_WORLD_SELECT_ENABLE] = 1U;
        game->ram[MYSMB_RAM_NUMBER_OF_LIVES] = 0xffU;
        if (mysmb_game_transpose_players(game) != 0U) mysmb_game_continue_game(game);
        else {
            game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
            game->ram[MYSMB_RAM_OPER_MODE] = 0U;
        }
    }
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
    struct mysmb_area_source source;

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
    /* ChkContinue falls through InitializeGame, which calls
     * LoadAreaPointer before the first later InitializeArea frame. */
    if (game->area_prg != 0) {
        source.prg = game->area_prg;
        source.prg_size = game->area_prg_size;
        (void)mysmb_area_load_pointers(game, &source);
    }
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
    for (index = 0U; index < 0x0020U; ++index) {
        game->palette[index] = 0U;
    }
    /* Cold boot supplies the initial display state.  Later
     * InitializeNameTables calls must retain the NMI-owned $2001 mirror. */
    game->ppu_mask = 0U;
    mysmb_game_initialize_memory(game, 0xfeU);
    mysmb_game_move_all_sprites_offscreen(game);
    /* Cold boot has already made the initial $4014 transfer before the
     * first recorder-visible NMI. */
    mysmb_game_submit_oam(game);
    game->oam_dma_primed = 0U;
    mysmb_game_initialize_name_tables(game);
    game->visible_ppu_control_0 = 0x90U;
    game->visible_ppu_mask = 0U;
    game->visible_ppu_name_table = 0U;
    game->visible_scroll_x = 0U;
    game->visible_scroll_y = 0U;
    game->area_prg = 0;
    game->area_prg_size = 0U;
    game->title_data = 0;
    game->title_data_size = 0U;
    game->title_icon_data = 0;
    game->title_icon_data_size = 0U;
    game->area_command_count = 0U;
    /* InitializeGame has completed before GameMenuRoutine becomes task 3. */
    game->ram[MYSMB_RAM_OPER_MODE] = 0U;
    game->ram[MYSMB_RAM_OPER_MODE_TASK] = 3U;
    game->ram[MYSMB_RAM_WARM_BOOT_VALIDATION] = 0xa5U;
    game->ram[MYSMB_RAM_PSEUDORANDOM] = 0xa5U;
    /* The first recorder-visible title NMI follows InitializeGame before the
     * native tick decrements the title countdown. */
    game->ram[MYSMB_RAM_DEMO_TIMER] = 0x19U;
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
        game->ram[(mysmb_u16)(MYSMB_RAM_OAM + offset)] = 0xf8U;
        offset = (mysmb_u8)(offset + 4U);
    } while (offset != 0U);
}

/* ROM NMI $4014 transfer after PPU_SPR_ADDR is reset to zero. */
static void mysmb_game_submit_oam(struct mysmb_game *game)
{
    mysmb_u16 offset;

    for (offset = 0U; offset < 0x0100U; ++offset)
        game->visible_oam[offset] = game->ram[(mysmb_u16)(MYSMB_RAM_OAM + offset)];
}

/* ROM $81c6-$81f9 SpriteShuffler. */
static void mysmb_game_shuffle_sprite_offsets(struct mysmb_game *game)
{
    mysmb_u8 index;
    mysmb_u16 offset;
    mysmb_u8 value;
    mysmb_u16 sum;

    for (index = 15U; index != 0U; --index) {
        offset = (mysmb_u8)(index - 1U);
        value = game->ram[(mysmb_u16)(MYSMB_RAM_SPRITE_OFFSETS + offset)];
        if (value >= 0x28U) {
            sum = (mysmb_u16)value + game->ram[(mysmb_u16)(
                MYSMB_RAM_SPRITE_SHUFFLE_AMOUNTS +
                game->ram[MYSMB_RAM_SPRITE_SHUFFLE_CONTROL])];
            value = (mysmb_u8)sum;
            if (sum > 0xffU) value = (mysmb_u8)(value + 0x28U);
            game->ram[(mysmb_u16)(MYSMB_RAM_SPRITE_OFFSETS + offset)] = value;
        }
    }
    game->ram[MYSMB_RAM_SPRITE_SHUFFLE_CONTROL]++;
    if (game->ram[MYSMB_RAM_SPRITE_SHUFFLE_CONTROL] == 3U)
        game->ram[MYSMB_RAM_SPRITE_SHUFFLE_CONTROL] = 0U;
    for (index = 0U; index < 3U; ++index) {
        value = game->ram[(mysmb_u16)(MYSMB_RAM_SPRITE_OFFSETS + 5U + index)];
        offset = (mysmb_u16)(MYSMB_RAM_MISC_SPRITE_OFFSETS + index * 3U);
        game->ram[offset] = value;
        value = (mysmb_u8)(value + 8U);
        game->ram[(mysmb_u16)(offset + 1U)] = value;
        game->ram[(mysmb_u16)(offset + 2U)] = (mysmb_u8)(value + 8U);
    }
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
    /* InitializeNameTables sets the PPU pattern-table arrangement then
     * InitScroll commits zero scroll.  Palette values remain the domain of
     * ScreenRoutines/ColorRotation and are initialized separately by T10. */
    game->ppu_control_0 = 0x10U;
    game->ram[MYSMB_RAM_PPU_CONTROL_MIRROR] = 0x10U;
    game->ppu_name_table = 0U;
    game->scroll_x = 0U;
    game->scroll_y = 0U;
}

/* ROM $83c9-$8426 PrintVictoryMessages.  Its secondary counter is a frame
 * divider: a message is selected only when it is zero, then the add-four
 * carries into the primary counter every 64 calls. */
static void mysmb_game_print_victory_messages(struct mysmb_game *game)
{
    mysmb_u8 primary;
    mysmb_u8 secondary;
    mysmb_u8 message;
    mysmb_u8 carry;

    secondary = game->ram[MYSMB_RAM_SECONDARY_MESSAGE];
    primary = game->ram[MYSMB_RAM_PRIMARY_MESSAGE];
    if (secondary == 0U) {
        if (primary == 0U) {
            message = game->ram[MYSMB_RAM_CURRENT_PLAYER] == 0U ? 0U : 1U;
            game->ram[0x0773U] = (mysmb_u8)(message + 12U);
        }
        else if (primary < 9U) {
            if (game->ram[MYSMB_RAM_WORLD] == 7U) {
                if (primary >= 3U) {
                    message = primary;
                    if (message == 3U) game->ram[MYSMB_RAM_EVENT_MUSIC] = 4U;
                    game->ram[0x0773U] = (mysmb_u8)(message + 12U);
                }
            }
            else if (primary == 2U) {
                game->ram[0x0773U] = 14U;
            }
            else if (primary >= 4U) {
                game->ram[MYSMB_RAM_WORLD_END_TIMER] = 6U;
                game->ram[MYSMB_RAM_OPER_MODE_TASK]++;
                return;
            }
        }
    }
    carry = secondary >= 0xfcU ? 1U : 0U;
    game->ram[MYSMB_RAM_SECONDARY_MESSAGE] = (mysmb_u8)(secondary + 4U);
    primary = (mysmb_u8)(primary + carry);
    game->ram[MYSMB_RAM_PRIMARY_MESSAGE] = primary;
    if (primary >= 7U) {
        game->ram[MYSMB_RAM_WORLD_END_TIMER] = 6U;
        game->ram[MYSMB_RAM_OPER_MODE_TASK]++;
    }
}

/* Translation of the game-mode portion of ScreenRoutines.  The original
 * advances one task per main-loop frame; command-producing tasks wait for
 * the following NMI to consume VRAM_Buffer1 before writing another stream. */
static void mysmb_game_step_screen_routine(struct mysmb_game *game)
{
    mysmb_u16 index;
    mysmb_u8 saved_background_color;
    mysmb_u8 saved_player_status;

    switch (game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK]) {
    case 0U:
        mysmb_game_move_all_sprites_offscreen(game);
        mysmb_game_initialize_name_tables(game);
        /* ROM InitScreen selects the initial static palette through the
         * $0773 address-control table; the following NMI owns its transfer. */
        if (game->ram[MYSMB_RAM_OPER_MODE] != 0U)
            game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] = 3U;
        game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 1U;
        break;
    case 1U:
        /* ROM SetupIntermediate temporarily uses the standard player colors
         * and background-color control 2 before restoring title/area state. */
        saved_background_color = game->ram[MYSMB_RAM_BACKGROUND_COLOR];
        saved_player_status = game->ram[MYSMB_RAM_PLAYER_STATUS];
        game->ram[MYSMB_RAM_BACKGROUND_COLOR] = 2U;
        game->ram[MYSMB_RAM_PLAYER_STATUS] = 0U;
        (void)mysmb_area_queue_player_palette(game);
        game->ram[MYSMB_RAM_PLAYER_STATUS] = saved_player_status;
        game->ram[MYSMB_RAM_BACKGROUND_COLOR] = saved_background_color;
        game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 2U;
        break;
    case 2U:
        if (mysmb_area_queue_top_status_line(game) != 0U)
            game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 3U;
        break;
    case 3U:
        if (mysmb_area_queue_bottom_status_line(game) != 0U)
            game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 4U;
        break;
    case 4U:
        if (game->ram[MYSMB_RAM_TIMER_EXPIRED] != 0U) {
            if (mysmb_area_queue_game_text(game, 2U) != 0U) {
                game->ram[MYSMB_RAM_TIMER_EXPIRED] = 0U;
                game->ram[MYSMB_RAM_SCREEN_TIMER] = 7U;
                game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 5U;
            }
        }
        else {
            game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 6U;
        }
        break;
    case 5U:
        if (game->ram[MYSMB_RAM_SCREEN_TIMER] == 0U) {
            mysmb_game_move_all_sprites_offscreen(game);
            game->ram[MYSMB_RAM_SCREEN_TIMER] = 7U;
            game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 6U;
        }
        break;
    case 6U:
        /* ROM DisplayIntermediate: title mode skips the intermediate-lives
         * text/timer path and immediately continues at AreaParserTaskControl. */
        if (game->ram[MYSMB_RAM_OPER_MODE] == 3U) {
            game->ram[MYSMB_RAM_SCREEN_TIMER] = 0x12U;
            if (mysmb_area_queue_game_text(game, 3U) != 0U)
                game->ram[MYSMB_RAM_OPER_MODE_TASK] = 2U;
        }
        else if (game->ram[MYSMB_RAM_OPER_MODE] == 0U ||
            game->ram[0x0752U] != 0U || game->ram[0x0769U] != 0U) {
            game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 8U;
        }
        else if (mysmb_area_queue_game_text(game, 1U) != 0U) {
            mysmb_player_draw_intermediate_oam(game);
            game->ram[MYSMB_RAM_SCREEN_TIMER] = 7U;
            game->ram[MYSMB_RAM_DISABLE_SCREEN] = 0U;
            game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 7U;
        }
        break;
    case 7U:
        if (game->ram[MYSMB_RAM_SCREEN_TIMER] == 0U) {
            mysmb_game_move_all_sprites_offscreen(game);
            game->ram[MYSMB_RAM_SCREEN_TIMER] = 7U;
            game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 8U;
        }
        break;
    case 8U:
        if (mysmb_area_parser_task_control(game) != 0U) {
            game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 9U;
        }
        break;
    case 9U:
        /* ROM GetAreaPalette selects the final area stream for the next
         * NMI after AreaParserTaskControl has completed. */
        game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] =
            (mysmb_u8)(game->ram[MYSMB_RAM_AREA_TYPE] + 1U);
        game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 10U;
        break;
    case 10U:
        if (game->ram[MYSMB_RAM_BACKGROUND_COLOR] >= 4U &&
            game->ram[MYSMB_RAM_BACKGROUND_COLOR] <= 7U) {
            static const mysmb_u8 background_controls[4] = { 0U, 9U, 10U, 4U };
            game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] = background_controls[
                game->ram[MYSMB_RAM_BACKGROUND_COLOR] - 4U];
        }
        else {
            /* GetAreaPalette's ground stream has just reached the PPU.  The
             * following NMI restores GetPlayerColors through Buffer1, so the
             * universal entry becomes the source-selected $3f00 color before
             * title draw or the game-mode setup handoff. */
            (void)mysmb_area_sync_player_palette(game);
        }
        game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 11U;
        break;
    case 11U:
        if (game->ram[0x0733U] == 1U)
            game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] = 11U;
        game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 12U;
        break;
    case 12U:
        if (game->ram[MYSMB_RAM_OPER_MODE] != 0U) {
            game->ram[MYSMB_RAM_OPER_MODE_TASK] = 2U;
            break;
        }
        if (game->title_data == 0 ||
            game->title_data_size != MYSMB_TITLE_BUFFER_SIZE) {
            break;
        }
        for (index = 0U; index < MYSMB_TITLE_BUFFER_SIZE; ++index)
            game->ram[(mysmb_u16)(0x0300U + index)] = game->title_data[index];
        game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] = 5U;
        game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 13U;
        break;
    case 13U:
        if (game->ram[MYSMB_RAM_OPER_MODE] != 0U) {
            game->ram[MYSMB_RAM_OPER_MODE_TASK] = 2U;
            break;
        }
        if (game->title_icon_data == 0 || game->title_icon_data_size == 0U ||
            game->title_icon_data_size > 0x00ffU) {
            break;
        }
        for (index = 0U; index < 0x0200U; ++index)
            game->ram[(mysmb_u16)(0x0300U + index)] = 0U;
        game->ram[MYSMB_RAM_VRAM_BUFFER1_OFFSET] = game->title_icon_data_size;
        for (index = 0U; index < game->title_icon_data_size; ++index)
            game->ram[(mysmb_u16)(MYSMB_TITLE_ICON_BUFFER_OFFSET + index)] =
                game->title_icon_data[index];
        game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 14U;
        break;
    case 14U:
        if (game->ram[MYSMB_RAM_OPER_MODE] == 0U) {
            (void)mysmb_area_queue_title_score(game);
            game->ram[MYSMB_RAM_OPER_MODE_TASK] = 2U;
        }
        else
            game->ram[MYSMB_RAM_OPER_MODE_TASK] = 2U;
        break;
    default:
        game->ram[MYSMB_RAM_OPER_MODE_TASK] = 2U;
        break;
    }
}

/* ROM GetAreaMusic.  SecondaryGameSetup and the invincibility-expiry path
 * queue the source area tune; SoundEngine owns its later header expansion. */
static void mysmb_game_get_area_music(struct mysmb_game *game)
{
    static const mysmb_u8 music_select_data[6] = {
        0x02U, 0x01U, 0x04U, 0x08U, 0x10U, 0x20U
    };
    mysmb_u8 selection;

    if (game->ram[MYSMB_RAM_OPER_MODE] == 0U) return;
    selection = game->ram[MYSMB_RAM_AREA_TYPE];
    if (game->ram[MYSMB_RAM_ALT_ENTRANCE] != 2U) {
        if (game->ram[MYSMB_RAM_PLAYER_ENTRANCE] == 6U ||
            game->ram[MYSMB_RAM_PLAYER_ENTRANCE] == 7U) {
            selection = 5U;
        }
    }
    if (game->ram[MYSMB_RAM_CLOUD_OVERRIDE] != 0U) selection = 4U;
    if (selection < 6U)
        game->ram[MYSMB_RAM_AREA_MUSIC_QUEUE] = music_select_data[selection];
}

/* ROM PrimaryGameSetup immediately falls through to SecondaryGameSetup. */
static void mysmb_game_primary_setup(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_FETCH_NEW_TIMER] = 1U;
    game->ram[MYSMB_RAM_PLAYER_SIZE] = 1U;
    game->ram[MYSMB_RAM_NUMBER_OF_LIVES] = 2U;
    game->ram[MYSMB_RAM_OFFSCREEN_LIVES] = 2U;
}

/* Translation of SecondaryGameSetup's game-mode fields.  OAM shuffle data
 * remains T11 ownership, while this task establishes the original transition
 * from ScreenRoutines to GameCoreRoutine. */
static void mysmb_game_secondary_setup(struct mysmb_game *game)
{
    static const mysmb_u8 default_offsets[15] = {
        0x04U, 0x30U, 0x48U, 0x60U, 0x78U, 0x90U, 0xa8U, 0xc0U,
        0xd8U, 0xe8U, 0x24U, 0xf8U, 0xfcU, 0x28U, 0x2cU
    };
    static const mysmb_u8 sprite0_data[4] = { 0x18U, 0xffU, 0x23U, 0x58U };
    mysmb_u8 index;
    mysmb_u16 buffer_offset;

    /* ROM SecondaryGameSetup ClearVRLoop clears the complete VRAM command
     * buffer page before it enables the game route.  This is distinct from
     * UpdateScreen's per-command terminator clear: title data remains here
     * until the setup transition, then cannot become incidental input to
     * game-mode producers. */
    for (buffer_offset = 0x0300U; buffer_offset < 0x0400U; ++buffer_offset)
        game->ram[buffer_offset] = 0U;

    game->ram[MYSMB_RAM_DISABLE_SCREEN] = 0U;
    mysmb_game_get_area_music(game);
    game->ram[MYSMB_RAM_TIMER_EXPIRED] = 0U;
    game->ram[0x0769U] = 0U;
    game->ram[0x0728U] = 0U;
    game->ram[0x03a0U] = 0xffU;
    game->ram[0x06c9U] = 0xffU;
    game->ram[MYSMB_RAM_SPRITE_SHUFFLE_AMOUNTS] = 0x58U;
    game->ram[(mysmb_u16)(MYSMB_RAM_SPRITE_SHUFFLE_AMOUNTS + 1U)] = 0x48U;
    game->ram[(mysmb_u16)(MYSMB_RAM_SPRITE_SHUFFLE_AMOUNTS + 2U)] = 0x38U;
    for (index = 0U; index < 15U; ++index)
        game->ram[(mysmb_u16)(MYSMB_RAM_SPRITE_OFFSETS + index)] = default_offsets[index];
    for (index = 0U; index < 4U; ++index)
        game->ram[(mysmb_u16)(MYSMB_RAM_OAM + index)] = sprite0_data[index];
    game->ram[MYSMB_RAM_SPRITE0_HIT]++;
    game->ram[MYSMB_RAM_OPER_MODE_TASK] = 3U;
}

/* Translation of the name-table portion of ROM $8e92-$8eec. */
mysmb_u8 mysmb_game_apply_vram_commands(struct mysmb_game *game,
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
        if ((address < 0x2000U || address >= 0x2800U) &&
            (address < 0x3f00U || address >= 0x3f20U)) {
            return 0U;
        }
        table = 0U;
        offset = 0U;
        if (address < 0x2800U) {
            table = (mysmb_u8)((address - 0x2000U) / 0x0400U);
            offset = (mysmb_u16)(address & 0x03ffU);
        }
        else {
            offset = (mysmb_u16)(address & 0x001fU);
        }
        value = commands[(mysmb_u16)(cursor + 3U)];
        /* WriteBufferToScreen ($2457-$2478) selects the PPU address
         * increment before each command: d7 means 32, otherwise one.  The
         * portable field records the same $2000 d2 state for the snapshot. */
        if ((control & 0x80U) != 0U)
            game->ppu_control_0 |= 0x04U;
        else
            game->ppu_control_0 &= (mysmb_u8)~0x04U;
        for (index = 0U; index < count; ++index) {
            if (address >= 0x3f00U) {
                if (offset >= 0x20U) return 0U;
                game->palette[mysmb_game_palette_offset(offset)] = value;
            }
            else {
                if (offset >= 0x0400U) return 0U;
                game->name_table[table][offset] = value;
            }
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

/* ROM $8e92-$8eb6 UpdateScreen/WriteBufferToScreen at the NMI boundary.
 * The buffer is owned by game routines during the preceding frame and is
 * cleared only after its terminal command has reached PPU-visible state. */
static void mysmb_game_commit_vram_buffer(struct mysmb_game *game)
{
    if (game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] >= 1U &&
        game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] <= 4U) {
        (void)mysmb_area_apply_palette(game, (mysmb_u8)(
            game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] - 1U));
        game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] = 0U;
        return;
    }
    if (game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] >= 8U &&
        game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] <= 11U) {
        (void)mysmb_area_apply_special_palette(game,
            game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL]);
        game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] = 0U;
        return;
    }
    if (game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] >= 12U &&
        game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] <= 18U) {
        (void)mysmb_area_apply_message(game,
            game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL]);
        game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] = 0U;
        return;
    }
    /* VRAM_AddrTable entries 6 and 7 both select VRAM_Buffer2.  The source
     * parser guard distinguishes only 6; NMI transfer itself does not. */
    if (game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] == 6U ||
        game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] == 7U) {
        if (game->ram[MYSMB_RAM_VRAM_BUFFER2_OFFSET] != 0U) {
            (void)mysmb_game_apply_vram_commands(game,
                &game->ram[MYSMB_RAM_VRAM_BUFFER2], 0x00c0U);
            game->ram[MYSMB_RAM_VRAM_BUFFER2_OFFSET] = 0U;
            game->ram[MYSMB_RAM_VRAM_BUFFER2] = 0U;
        }
        game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] = 0U;
        return;
    }
    if (game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] == 5U) {
        (void)mysmb_game_apply_vram_commands(game, &game->ram[0x0300U],
                                              MYSMB_TITLE_BUFFER_SIZE);
        game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] = 0U;
        return;
    }
    if (game->ram[MYSMB_RAM_VRAM_BUFFER1_OFFSET] == 0U) return;
    (void)mysmb_game_apply_vram_commands(game,
        &game->ram[MYSMB_RAM_VRAM_BUFFER1], 0x0100U);
    game->ram[MYSMB_RAM_VRAM_BUFFER1_OFFSET] = 0U;
    game->ram[MYSMB_RAM_VRAM_BUFFER1] = 0U;
}

/* ROM $94a5-$9539 GameEngine's UpdScrollVar/RunParser tail.  NMI has already
 * committed a pending buffer at the start of this tick.  The source performs
 * exactly one parser subtask while one is active, or starts one after each
 * accumulated 32 pixels of scroll. */
static void mysmb_game_step_area_parser(struct mysmb_game *game)
{
    if (game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] == 6U) return;
    if (game->ram[MYSMB_RAM_PARSER_TASK] != 0U) {
        (void)mysmb_area_parser_task_step(game);
        return;
    }
    if (game->ram[MYSMB_RAM_SCROLL_THIRTY_TWO] < 0x20U) return;
    game->ram[MYSMB_RAM_SCROLL_THIRTY_TWO] =
        (mysmb_u8)(game->ram[MYSMB_RAM_SCROLL_THIRTY_TWO] - 0x20U);
    game->ram[MYSMB_RAM_VRAM_BUFFER2_OFFSET] = 0U;
    (void)mysmb_area_parser_task_step(game);
}

/* ROM NonMaskableInterrupt ($740-$842) restores the selected display mask,
 * commits scroll/name-table state, then re-enables NMI on $2000.  Gameplay
 * has already changed the source-owned scroll fields when this is called. */
static void mysmb_game_commit_display_state(struct mysmb_game *game)
{
    /* NMI saves the pre-command $2000 mirror without d7.  A VRAM command
     * may have selected d2 in that mirror, whereas the physical register at
     * RTI is restored from the pre-command value with NMI enabled. */
    game->ppu_control_0 &= 0x7fU;
    game->ram[MYSMB_RAM_PPU_CONTROL_MIRROR] = game->ppu_control_0;
    if (game->ram[MYSMB_RAM_DISABLE_SCREEN] != 0U)
        game->ppu_mask &= 0xe6U;
    else
        game->ppu_mask |= 0x1eU;
    game->ram[MYSMB_RAM_PPU_MASK_MIRROR] = game->ppu_mask;
    /* The original writes these values before OperModeExecutionTree.  That
     * routine may change the mirrors and scroll variables, but the physical
     * PPU does not show those changes until the following NMI. */
    game->visible_ppu_control_0 = (mysmb_u8)(game->ppu_control_0 | 0x80U);
    game->visible_ppu_mask = game->ppu_mask;
    game->visible_ppu_name_table = (mysmb_u8)(game->ppu_control_0 & 3U);
    game->visible_scroll_x = game->ram[MYSMB_RAM_HORIZONTAL_SCROLL];
    game->visible_scroll_y = game->ram[MYSMB_RAM_VERTICAL_SCROLL];
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

    if (game->area_prg == 0 || game->title_data == 0 ||
        game->title_data_size != MYSMB_TITLE_BUFFER_SIZE ||
        game->title_icon_data == 0 || game->title_icon_data_size == 0U) {
        return 0U;
    }
    source.prg = game->area_prg;
    source.prg_size = game->area_prg_size;
    mysmb_area_initialize(game);
    if (mysmb_area_load_pointers(game, &source) == 0U ||
        mysmb_area_parse_header(game, &source) == 0U) {
        return 0U;
    }
    game->ram[MYSMB_RAM_OPER_MODE] = 0U;
    /* The recorder observes the first NMI after its frame-counter increment.
     * Seed the prior byte so the cold-boot snapshot is the ROM's 0x00. */
    game->ram[MYSMB_RAM_FRAME_COUNTER] = 0xffU;
    /* The reference cold boot spends its first NMI in InitializeGame before
     * ScreenRoutines task 0.  Area state is already prepared above, but keep
     * that frame boundary so title VRAM commands have the same phase. */
    game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
    game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 0U;
    game->ram[MYSMB_RAM_AREA_MUSIC_QUEUE] = 0x80U;
    return 1U;
}

void mysmb_game_tick(struct mysmb_game *game, const struct mysmb_input *input,
                     struct mysmb_frame *frame)
{
    mysmb_u8 mode_before;
    mysmb_u8 task_before;
    mysmb_u8 enemy_slot;
    struct mysmb_area_source area_source;

    mode_before = game->ram[MYSMB_RAM_OPER_MODE];
    task_before = game->ram[MYSMB_RAM_OPER_MODE_TASK];
    game->frame_number++;
    game->ram[MYSMB_RAM_FRAME_COUNTER]++;
    if (game->oam_dma_primed != 0U) mysmb_game_submit_oam(game);
    else game->oam_dma_primed = 1U;
    mysmb_game_commit_vram_buffer(game);
    mysmb_game_commit_display_state(game);
    mysmb_audio_step(game);
    mysmb_game_tick_player_timers(game);
    mysmb_game_rotate_pseudorandom(game);
    if (game->ram[MYSMB_RAM_SPRITE0_HIT] != 0U) {
        mysmb_u8 oam_offset;

        oam_offset = 4U;
        do {
            game->ram[(mysmb_u16)(MYSMB_RAM_OAM + oam_offset)] = 0xf8U;
            oam_offset = (mysmb_u8)(oam_offset + 4U);
        } while (oam_offset != 0U);
        mysmb_game_shuffle_sprite_offsets(game);
    }
    mysmb_game_title_step(game, input);
    if (mode_before == 2U) {
        mysmb_game_step_victory(game);
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
        game->ram[MYSMB_RAM_OPER_MODE_TASK] = 1U;
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
             game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 6U) {
        mysmb_game_lose_life(game);
    }
    else if ((mode_before == 1U &&
              (task_before == 3U || (task_before == 1U && game->area_prg == 0))) ||
             (mode_before == 0U && task_before == 3U &&
              game->ram[MYSMB_RAM_OPER_MODE] == 0U &&
              game->ram[MYSMB_RAM_OPER_MODE_TASK] == 3U)) {
        if (game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] == 3U &&
            mysmb_area_queue_bottom_status_line(game) != 0U) {
            game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 4U;
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
        else if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 4U) {
            /* ROM FlagpoleSlide: force Down until the slide reaches $9e. */
            if (game->ram[MYSMB_RAM_PLAYER_Y] < 0x9eU) {
                mysmb_player_step(game, MYSMB_BUTTON_DOWN);
            }
            else {
                game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] = 5U;
            }
        }
        else if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 5U) {
            /* ROM PlayerEndLevel.  The star/flag task is the original
             * object-side completion handoff; the mode route owns NextArea. */
            mysmb_player_step(game, MYSMB_BUTTON_RIGHT);
            if (game->ram[MYSMB_RAM_STAR_FLAG_TASK] == 5U) {
                game->ram[MYSMB_RAM_LEVEL]++;
                mysmb_game_next_area(game);
            }
        }
        else if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 2U) {
            mysmb_player_step_side_pipe(game);
        }
        else if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 8U) {
            mysmb_player_step(game, game->ram[MYSMB_RAM_SAVED_JOYPAD1]);
        }
        else if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 9U) {
            mysmb_player_step_change_size(game);
        }
        else if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 10U) {
            mysmb_player_step_injury_blink(game, game->ram[MYSMB_RAM_SAVED_JOYPAD1]);
        }
        else if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 11U &&
                 game->ram[MYSMB_RAM_TIMER_CONTROL] < 0xf0U) {
            mysmb_player_step(game, game->ram[MYSMB_RAM_SAVED_JOYPAD1]);
        }
        else if (game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] == 12U) {
            mysmb_player_step_fire_flower(game);
        }
        /* ROM $94a5 GameEngine: GameRoutines (above) runs before the
         * object loop, so object collisions see this frame's player state. */
        if (game->area_prg != 0) {
            area_source.prg = game->area_prg;
            area_source.prg_size = game->area_prg_size;
            /* ROM GameEngine enters EnemiesAndLoopsCore once for every
             * ObjectOffset.  Only an empty slot reaches ProcessEnemyData;
             * a stream page-control record can therefore be consumed by a
             * later empty slot in the same frame. */
            for (enemy_slot = 0U; enemy_slot < 6U; ++enemy_slot) {
                if (game->ram[MYSMB_RAM_ENEMY_FLAG + enemy_slot] != 0U) {
                    if (enemy_slot < 5U) {
                        mysmb_objects_step_normal_enemy(game, enemy_slot);
                    }
                }
                else if (enemy_slot < 5U) {
                    if (mysmb_area_spawn_enemy_in_slot(game, &area_source,
                                                       enemy_slot) != 0U &&
                        game->ram[MYSMB_RAM_ENEMY_FLAG + enemy_slot] != 0U) {
                    }
                }
                else {
                    (void)mysmb_area_spawn_next_enemy(game, &area_source);
                }
            }
        }
        mysmb_objects_step_fireballs(game);
        mysmb_objects_step_power_up(game);
        mysmb_objects_check_power_up_collision(game);
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
        mysmb_objects_step_lakitu_frenzy(game);
        mysmb_objects_step_lakitus(game);
        mysmb_objects_step_spiny_eggs(game);
        mysmb_objects_step_hammer_bros(game);
        mysmb_objects_step_floatey_numbers(game);
        mysmb_player_draw_oam(game);
        mysmb_objects_step_vine(game);
        mysmb_objects_apply_block_replacements(game);
        mysmb_objects_step_blocks(game);
        mysmb_objects_step_misc(game);
        mysmb_area_step_palette_rotation(game);
        (void)mysmb_area_sync_player_palette(game);
        mysmb_game_cycle_player_palette(game);
        /* ROM GameEngine's SaveAB tail clears the transient directional
         * partition after object collisions.  In particular, a collision
         * that selects PlayerDeath leaves its following physics frame with
         * zero horizontal input and the KillPlayer-cleared speed. */
        game->ram[MYSMB_RAM_PLAYER_LEFT_RIGHT_BUTTONS] = 0U;
        mysmb_game_step_area_parser(game);
    }
    /* GameEngine may advance the entrance dispatcher to subroutine 8 on this
     * frame.  The ROM's game-timer pass observes that new state, so it can
     * load its first 24-frame interval without an extra frame of delay. */
    if (mysmb_game_run_timer(game) != 0U) {
        (void)mysmb_area_queue_timer_status(game);
    }
    frame->sprite0_y = game->ram[0x0200U];
    frame->sprite0_x = game->ram[0x0203U];
    frame->start_pressed =
        (game->ram[MYSMB_RAM_SAVED_JOYPAD1] & MYSMB_BUTTON_START) != 0U;
    frame->operating_mode = game->ram[MYSMB_RAM_OPER_MODE];
    frame->operating_mode_task = game->ram[MYSMB_RAM_OPER_MODE_TASK];
}

/* ROM $82b3-$82ca DemoEngine.  It returns one only after the terminal zero
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
        return;
    }
    if (buttons == MYSMB_BUTTON_SELECT &&
        game->ram[MYSMB_RAM_DEMO_TIMER] != 0U &&
        game->ram[MYSMB_RAM_SELECT_TIMER] == 0U) {
        game->ram[MYSMB_RAM_DEMO_TIMER] = 0x18U;
        game->ram[MYSMB_RAM_SELECT_TIMER] = 0x10U;
        game->ram[MYSMB_RAM_NUMBER_OF_PLAYERS] ^= 1U;
    }
    if (game->ram[MYSMB_RAM_DEMO_TIMER] != 0U) {
        game->ram[MYSMB_RAM_SAVED_JOYPAD1] = 0U;
        return;
    }
    game->ram[MYSMB_RAM_SELECT_TIMER] = buttons;
    if (mysmb_game_step_title_demo(game) != 0U) {
        game->ram[MYSMB_RAM_OPER_MODE] = 0U;
        game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
        game->ram[MYSMB_RAM_SPRITE0_HIT] = 0U;
        game->ram[MYSMB_RAM_DISABLE_SCREEN]++;
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
