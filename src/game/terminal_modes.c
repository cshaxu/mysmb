#include "game/game.h"
#include "game/frame_root.h"
#include "game/area.h"
#include "game/player.h"
#include "game/objects.h"
#include "game/terminal_modes.h"

/* CPU-RAM addresses owned by the ROM terminal-mode labels. */
enum {
    MYSMB_RAM_GAME_ENGINE_SUBROUTINE = 0x000eU,
    MYSMB_RAM_SAVED_JOYPAD1 = 0x06fcU,
    MYSMB_RAM_SAVED_JOYPAD2 = 0x06fdU,
    MYSMB_RAM_SCREEN_ROUTINE_TASK = 0x073cU,
    MYSMB_RAM_SPRITE0_HIT = 0x0722U,
    MYSMB_RAM_TIMER_CONTROL = 0x0747U,
    MYSMB_RAM_SECONDARY_MESSAGE = 0x0749U,
    MYSMB_RAM_CURRENT_PLAYER = 0x0753U,
    MYSMB_RAM_PLAYER_SIZE = 0x0754U,
    MYSMB_RAM_PLAYER_STATUS = 0x0756U,
    MYSMB_RAM_FETCH_NEW_TIMER = 0x0757U,
    MYSMB_RAM_NUMBER_OF_LIVES = 0x075aU,
    MYSMB_RAM_HALFWAY_PAGE = 0x075bU,
    MYSMB_RAM_LEVEL = 0x075cU,
    MYSMB_RAM_WORLD = 0x075fU,
    MYSMB_RAM_AREA = 0x0760U,
    MYSMB_RAM_OFFSCREEN_LIVES = 0x0761U,
    MYSMB_RAM_OPER_MODE = 0x0770U,
    MYSMB_RAM_OPER_MODE_TASK = 0x0772U,
    MYSMB_RAM_VRAM_ADDRESS_CONTROL = 0x0773U,
    MYSMB_RAM_DISABLE_SCREEN = 0x0774U,
    MYSMB_RAM_NUMBER_OF_PLAYERS = 0x077aU,
    MYSMB_RAM_SCREEN_TIMER = 0x07a0U,
    MYSMB_RAM_WORLD_END_TIMER = 0x07a1U,
    MYSMB_RAM_WORLD_SELECT_ENABLE = 0x07fcU,
    MYSMB_RAM_CONTINUE_WORLD = 0x07fdU,
    MYSMB_RAM_SCREEN_LEFT_PAGE = 0x071aU,
    MYSMB_RAM_SCREEN_RIGHT_PAGE = 0x071bU,
    MYSMB_RAM_PRIMARY_MESSAGE = 0x0719U,
    MYSMB_RAM_DESTINATION_PAGE = 0x0034U,
    MYSMB_RAM_VICTORY_WALK = 0x0035U,
    MYSMB_RAM_PLAYER_PAGE = 0x006dU,
    MYSMB_RAM_PLAYER_X = 0x0086U,
    MYSMB_RAM_SCROLL_FRACTION = 0x0768U,
    MYSMB_RAM_EVENT_MUSIC = 0x00fcU
};

static void mysmb_game_print_victory_messages(struct mysmb_game *game);

/* ROM HalfwayPageNybbles.  It is adjacent to PlayerLoseLife in PRG and is
 * consumed only by that state transition. */
static const mysmb_u8 mysmb_game_halfway_page_nybbles[16] = {
    0x56U, 0x40U, 0x65U, 0x70U, 0x66U, 0x40U, 0x66U, 0x40U,
    0x66U, 0x40U, 0x66U, 0x60U, 0x65U, 0x70U, 0x00U, 0x00U
};

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

/* ROM LoadAreaPointer call sites in ContinueGame, NextArea, and
 * PlayerEndWorld.  The bound PRG is owner-local; ROM-free unit routes retain
 * their source behavior by making this no-op when no cartridge data exists. */
static void mysmb_game_load_area_pointer(struct mysmb_game *game)
{
    struct mysmb_area_source source;

    if (game->area_prg == 0) return;
    source.prg = game->area_prg;
    source.prg_size = game->area_prg_size;
    (void)mysmb_area_load_area_pointer(game, &source);
}

/* ROM StillInGame, GetHalfway, MaskHPNyb and SetHalfway's selected value.
 * The caller owns the following TransposePlayers and ContinueGame calls. */
static mysmb_u8 mysmb_game_get_halfway_page(const struct mysmb_game *game)
{
    mysmb_u8 index;
    mysmb_u8 checkpoint;

    index = (mysmb_u8)(game->ram[MYSMB_RAM_WORLD] << 1U);
    if ((game->ram[MYSMB_RAM_LEVEL] & 2U) != 0U) index++;
    checkpoint = mysmb_game_halfway_page_nybbles[index];
    if ((game->ram[MYSMB_RAM_LEVEL] & 1U) == 0U) checkpoint >>= 4U;
    checkpoint &= 0x0fU;
    if (checkpoint > game->ram[MYSMB_RAM_SCREEN_LEFT_PAGE]) checkpoint = 0U;
    return checkpoint;
}

/* ROM ContinueGame. */
static void mysmb_game_continue_game(struct mysmb_game *game)
{
    /* ROM ContinueGame calls LoadAreaPointer before it resets the game-mode
     * task, so the restart frame itself carries the next area pointer. */
    mysmb_game_load_area_pointer(game);
    game->ram[MYSMB_RAM_PLAYER_SIZE] = 1U;
    game->ram[MYSMB_RAM_FETCH_NEW_TIMER]++;
    game->ram[MYSMB_RAM_TIMER_CONTROL] = 0U;
    game->ram[MYSMB_RAM_PLAYER_STATUS] = 0U;
    game->ram[MYSMB_RAM_GAME_ENGINE_SUBROUTINE] = 0U;
    game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
    game->ram[MYSMB_RAM_OPER_MODE] = 1U;
}


/* ROM PlayerLoseLife.  The half-way table stays here because it is game-mode
 * ownership, not an area renderer concern. */
void mysmb_game_lose_life(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_DISABLE_SCREEN]++;
    game->ram[MYSMB_RAM_SPRITE0_HIT] = 0U;
    /* ROM PlayerLoseLife queues Silence before it transfers control to
     * ContinueGame.  The following InitializeArea queues the same selector
     * through AreaMusicQueue, but this event-side pass clears the previous
     * area-music state first. */
    game->ram[MYSMB_RAM_EVENT_MUSIC] = 0x80U;
    game->ram[MYSMB_RAM_NUMBER_OF_LIVES]--;
    if (game->ram[MYSMB_RAM_NUMBER_OF_LIVES] >= 0x80U) {
        game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
        game->ram[MYSMB_RAM_OPER_MODE] = 3U;
        return;
    }
    game->ram[MYSMB_RAM_HALFWAY_PAGE] = mysmb_game_get_halfway_page(game);
    (void)mysmb_game_transpose_players(game);
    mysmb_game_continue_game(game);
}

/* ROM SetupGameOver.  ScreenRoutines is a separately admitted output owner. */
static void mysmb_game_setup_game_over(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 0U;
    game->ram[MYSMB_RAM_SPRITE0_HIT] = 0U;
    game->ram[MYSMB_RAM_EVENT_MUSIC] = 2U;
    game->ram[MYSMB_RAM_DISABLE_SCREEN]++;
    game->ram[MYSMB_RAM_OPER_MODE_TASK] = 1U;
}

/* ROM TerminateGame, including its TransposePlayers result branch. */
static void mysmb_game_terminate_game(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_EVENT_MUSIC] = 0x80U;
    if (mysmb_game_transpose_players(game) != 0U) {
        mysmb_game_continue_game(game);
        return;
    }
    game->ram[MYSMB_RAM_CONTINUE_WORLD] = game->ram[MYSMB_RAM_WORLD];
    game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
    game->ram[MYSMB_RAM_SCREEN_TIMER] = 0U;
    game->ram[MYSMB_RAM_OPER_MODE] = 0U;
}

/* ROM RunGameOver and its GameIsOn return. */
static void mysmb_game_run_game_over(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_DISABLE_SCREEN] = 0U;
    if ((game->ram[MYSMB_RAM_SAVED_JOYPAD1] & MYSMB_BUTTON_START) == 0U &&
        game->ram[MYSMB_RAM_SCREEN_TIMER] != 0U) return;
    mysmb_game_terminate_game(game);
}

/* ROM GameOverMode JumpEngine dispatch. */
void mysmb_game_step_game_over(struct mysmb_game *game)
{
    if (game->ram[MYSMB_RAM_OPER_MODE_TASK] == 0U) {
        mysmb_game_setup_game_over(game);
        return;
    }
    if (game->ram[MYSMB_RAM_OPER_MODE_TASK] == 1U) {
        mysmb_game_step_screen_routine(game);
        return;
    }
    mysmb_game_run_game_over(game);
}

/* ROM VictoryModeSubroutines. */
void mysmb_game_step_victory(struct mysmb_game *game)
{
    mysmb_u8 auto_buttons;
    mysmb_u8 scroll_amount;
    mysmb_u16 fractional_sum;

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
        auto_buttons = 0U;
        if (game->ram[MYSMB_RAM_PLAYER_PAGE] != game->ram[MYSMB_RAM_DESTINATION_PAGE] ||
            game->ram[MYSMB_RAM_PLAYER_X] < 0x60U) {
            game->ram[MYSMB_RAM_VICTORY_WALK] = 1U;
            auto_buttons = MYSMB_BUTTON_RIGHT;
        }
        /* ROM PlayerVictoryWalk always enters AutoControlPlayer, including
         * the no-walk case after Mario has reached x=$60. */
        mysmb_player_step(game, auto_buttons);
        if (game->ram[MYSMB_RAM_SCREEN_LEFT_PAGE] !=
            game->ram[MYSMB_RAM_DESTINATION_PAGE]) {
            fractional_sum = (mysmb_u16)game->ram[MYSMB_RAM_SCROLL_FRACTION] +
                             0x80U;
            game->ram[MYSMB_RAM_SCROLL_FRACTION] = (mysmb_u8)fractional_sum;
            scroll_amount = (mysmb_u8)(1U +
                (fractional_sum > 0xffU ? 1U : 0U));
            mysmb_player_scroll_screen(game, scroll_amount);
            mysmb_game_step_area_parser(game);
            game->ram[MYSMB_RAM_VICTORY_WALK]++;
        }
        if (game->ram[MYSMB_RAM_VICTORY_WALK] == 0U)
            game->ram[MYSMB_RAM_OPER_MODE_TASK]++;
        return;
    }
    if (game->ram[MYSMB_RAM_OPER_MODE_TASK] == 3U) {
        mysmb_game_print_victory_messages(game);
        return;
    }
    /* ROM PlayerEndWorld only observes WorldEndTimer.  DecTimers has already
     * run in the NMI root before VictoryModeSubroutines reaches this leaf. */
    if (game->ram[MYSMB_RAM_WORLD_END_TIMER] != 0U) return;
    if (game->ram[MYSMB_RAM_WORLD] < 7U) {
        game->ram[MYSMB_RAM_AREA] = 0U;
        game->ram[MYSMB_RAM_LEVEL] = 0U;
        game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
        game->ram[MYSMB_RAM_WORLD]++;
        mysmb_game_load_area_pointer(game);
        game->ram[MYSMB_RAM_FETCH_NEW_TIMER]++;
        game->ram[MYSMB_RAM_OPER_MODE] = 1U;
    }
    else if (((game->ram[MYSMB_RAM_SAVED_JOYPAD1] |
               game->ram[MYSMB_RAM_SAVED_JOYPAD2]) & MYSMB_BUTTON_B) != 0U) {
        game->ram[MYSMB_RAM_WORLD_SELECT_ENABLE] = 1U;
        game->ram[MYSMB_RAM_NUMBER_OF_LIVES] = 0xffU;
        /* EndChkBButton enters ROM TerminateGame, including its silence and
         * title-return writes when no other player's record can be resumed. */
        game->ram[MYSMB_RAM_EVENT_MUSIC] = 0x80U;
        if (mysmb_game_transpose_players(game) != 0U) mysmb_game_continue_game(game);
        else {
            game->ram[MYSMB_RAM_CONTINUE_WORLD] = game->ram[MYSMB_RAM_WORLD];
            game->ram[MYSMB_RAM_OPER_MODE_TASK] = 0U;
            game->ram[MYSMB_RAM_SCREEN_TIMER] = 0U;
            game->ram[MYSMB_RAM_OPER_MODE] = 0U;
        }
    }
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
            game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] = (mysmb_u8)(message + 12U);
        }
        else if (primary < 9U) {
            if (game->ram[MYSMB_RAM_WORLD] == 7U) {
                if (primary >= 3U) {
                    message = primary;
                    if (message == 3U) game->ram[MYSMB_RAM_EVENT_MUSIC] = 4U;
                    game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] = (mysmb_u8)(message + 12U);
                }
            }
            else if (primary == 2U) {
                game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] = 14U;
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

