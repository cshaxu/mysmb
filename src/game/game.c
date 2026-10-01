#include "game/game.h"
#include "game/frame_root.h"
#include "game/area.h"
#include "game/audio.h"
#include "game/player.h"
#include "game/oam/oam.h"
#include "game/objects.h"
#include "game/title_modes.h"
#include "game/terminal_modes.h"
#include "game/status.h"

enum {
    MYSMB_RAM_GAME_ENGINE_SUBROUTINE = 0x000eU,
    MYSMB_RAM_PLAYER_A_B_BUTTONS = 0x000aU,
    MYSMB_RAM_PREVIOUS_A_B_BUTTONS = 0x000dU,
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
    MYSMB_RAM_ALT_ENTRANCE = 0x0752U,
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
    MYSMB_RAM_ENEMY_ID = 0x0016U,
    MYSMB_RAM_ENEMY_STATE = 0x001eU,
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

void mysmb_game_step_screen_routine(struct mysmb_game *game);
void mysmb_game_primary_setup(struct mysmb_game *game);
void mysmb_game_secondary_setup(struct mysmb_game *game);
void mysmb_game_step_area_parser(struct mysmb_game *game);
void mysmb_game_submit_oam(struct mysmb_game *game);

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

/* Translation of the game-mode portion of ScreenRoutines.  The original
 * advances one task per main-loop frame; command-producing tasks wait for
 * the following NMI to consume VRAM_Buffer1 before writing another stream. */
void mysmb_game_step_screen_routine(struct mysmb_game *game)
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
        /* WriteTopStatusLine always falls through to IncSubtask.  A native
         * source-binding failure may suppress the neutral output safely, but
         * it must not manufacture a ROM-state retry branch. */
        (void)mysmb_area_queue_top_status_line(game);
        game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 3U;
        break;
    case 3U:
        /* WriteBottomStatusLine also ends in IncSubtask unconditionally. */
        (void)mysmb_area_queue_bottom_status_line(game);
        game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 4U;
        break;
    case 4U:
        if (game->ram[MYSMB_RAM_TIMER_EXPIRED] != 0U) {
            /* DisplayTimeUp clears its expiration latch before OutputInter.
             * OutputInter then writes the text, resets the screen timer and
             * reenables output in that source order. */
            game->ram[MYSMB_RAM_TIMER_EXPIRED] = 0U;
            (void)mysmb_area_queue_game_text(game, 2U);
            game->ram[MYSMB_RAM_SCREEN_TIMER] = 7U;
            game->ram[MYSMB_RAM_DISABLE_SCREEN] = 0U;
            game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 5U;
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
            /* GameOverInter calls WriteGameText then jumps to IncModeTask_B;
             * neither source routine branches on a buffer-capacity result. */
            (void)mysmb_area_queue_game_text(game, 3U);
            game->ram[MYSMB_RAM_OPER_MODE_TASK]++;
        }
        else if (game->ram[MYSMB_RAM_OPER_MODE] == 0U ||
                 game->ram[0x0752U] != 0U) {
            /* NoInter: title mode and alternate entrances skip directly to
             * the parser task. */
            game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 8U;
        }
        else if (game->ram[MYSMB_RAM_AREA_TYPE] == 3U ||
                 game->ram[0x0769U] == 0U) {
            /* ROM branches to PlayerInter before DisableIntermediate is
             * consulted for castle areas. */
            /* PlayerInter draws the OAM player before OutputInter writes
             * the lives text command. */
            mysmb_oam_draw_intermediate_player(game);
            (void)mysmb_area_queue_game_text(game, 1U);
            game->ram[MYSMB_RAM_SCREEN_TIMER] = 7U;
            game->ram[MYSMB_RAM_DISABLE_SCREEN] = 0U;
            game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 7U;
        }
        else {
            game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 8U;
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
        /* AreaParserTaskControl owns the source-order final-set transition:
         * it increments ScreenRoutineTask before writing address control 6. */
        (void)mysmb_area_parser_task_control(game);
        break;
    case 9U:
        /* ROM GetAreaPalette selects the final area stream for the next
         * NMI after AreaParserTaskControl has completed. */
        game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] =
            (mysmb_u8)(game->ram[MYSMB_RAM_AREA_TYPE] + 1U);
        game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 10U;
        break;
    case 10U:
        /* ROM GetBackgroundColor increments ScreenRoutineTask before it
         * falls through into GetPlayerColors.  Keep that write visible to
         * the palette producer in the same source order. */
        game->ram[MYSMB_RAM_SCREEN_ROUTINE_TASK] = 11U;
        if (game->ram[MYSMB_RAM_BACKGROUND_COLOR] >= 4U &&
            game->ram[MYSMB_RAM_BACKGROUND_COLOR] <= 7U) {
            static const mysmb_u8 background_controls[4] = { 0U, 9U, 10U, 4U };
            game->ram[MYSMB_RAM_VRAM_ADDRESS_CONTROL] = background_controls[
                game->ram[MYSMB_RAM_BACKGROUND_COLOR] - 4U];
        }
        /* NoBGColor falls directly into GetPlayerColors.  This is an
         * unconditional producer, not a palette-difference optimization. */
        (void)mysmb_area_queue_player_palette(game);
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
        mysmb_game_draw_mushroom_icon(game);
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
void mysmb_game_get_area_music(struct mysmb_game *game)
{
    static const mysmb_u8 music_select_data[6] = {
        0x02U, 0x01U, 0x04U, 0x08U, 0x10U, 0x20U
    };
    mysmb_u8 selection;

    if (game->ram[MYSMB_RAM_OPER_MODE] == 0U) return;
    if (game->ram[MYSMB_RAM_ALT_ENTRANCE] != 2U) {
        selection = 5U;
        if (game->ram[MYSMB_RAM_PLAYER_ENTRANCE] == 6U ||
            game->ram[MYSMB_RAM_PLAYER_ENTRANCE] == 7U) {
            game->ram[MYSMB_RAM_AREA_MUSIC_QUEUE] = music_select_data[selection];
            return;
        }
    }
    selection = game->ram[MYSMB_RAM_AREA_TYPE];
    if (game->ram[MYSMB_RAM_CLOUD_OVERRIDE] != 0U) selection = 4U;
    /* Source area-header parsing restricts AreaType to the first four table
     * entries; the pipe and cloud paths above supply entries five and four. */
    game->ram[MYSMB_RAM_AREA_MUSIC_QUEUE] = music_select_data[selection];
}

/* ROM PrimaryGameSetup immediately falls through to SecondaryGameSetup. */
void mysmb_game_primary_setup(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_FETCH_NEW_TIMER] = 1U;
    game->ram[MYSMB_RAM_PLAYER_SIZE] = 1U;
    game->ram[MYSMB_RAM_NUMBER_OF_LIVES] = 2U;
    game->ram[MYSMB_RAM_OFFSCREEN_LIVES] = 2U;
}

/* Translation of SecondaryGameSetup's game-mode fields.  OAM shuffle data
 * remains T11 ownership, while this task establishes the original transition
 * from ScreenRoutines to GameCoreRoutine. */
void mysmb_game_secondary_setup(struct mysmb_game *game)
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
    /* ROM DoNothing2 returns, then DoNothing1 retains this otherwise unused
     * residual store before SecondaryGameSetup continues its own writes. */
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

/* ROM $8e92-$8eec WriteBufferToScreen through InitScroll.  This models PPU
 * command semantics in the shared game output state; platform code never
 * interprets these packets. */
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
        if (address < 0x2000U || address >= 0x4000U) {
            return 0U;
        }
        value = commands[(mysmb_u16)(cursor + 3U)];
        /* WriteBufferToScreen ($2457-$2478) selects the PPU address
         * increment before each command: d7 means 32, otherwise one.  The
         * portable field records the same $2000 d2 state for the snapshot. */
        if ((control & 0x80U) != 0U)
            game->ppu_control_0 |= 0x04U;
        else
            game->ppu_control_0 &= (mysmb_u8)~0x04U;
        /* WritePPUReg1 writes both physical $2000 and $0778 before every
         * packet.  The visible physical state is committed by the NMI tail. */
        game->ram[MYSMB_RAM_PPU_CONTROL_MIRROR] = game->ppu_control_0;
        for (index = 0U; index < count; ++index) {
            if (address >= 0x3f00U) {
                offset = (mysmb_u16)(address & 0x001fU);
                game->palette[mysmb_game_palette_offset(offset)] = value;
            }
            else {
                table = (mysmb_u8)((address & 0x0400U) != 0U ? 1U : 0U);
                offset = (mysmb_u16)(address & 0x03ffU);
                game->name_table[table][offset] = value;
            }
            address = (mysmb_u16)((address +
                ((control & 0x80U) != 0U ? 32U : 1U)) & 0x3fffU);
            if ((control & 0x40U) == 0U && (mysmb_u8)(index + 1U) < count) {
                value = commands[(mysmb_u16)(cursor + 3U + index + 1U)];
            }
        }
        cursor = (mysmb_u16)(cursor + 3U +
                              ((control & 0x40U) != 0U ? 1U : count));
    }
    if (cursor >= command_size) return 0U;
    /* UpdateScreen reaches InitScroll with A=0 after the terminator. */
    game->visible_scroll_x = 0U;
    game->visible_scroll_y = 0U;
    return 1U;
}

void mysmb_game_bind_chr_source(struct mysmb_game *game,
                                 const mysmb_u8 *chr_data, mysmb_u16 chr_data_size)
{
    game->chr_data = chr_data;
    game->chr_data_size = chr_data_size;
}
void mysmb_game_frame_initialize(struct mysmb_frame *frame)
{
    frame->sprite0_x = 0U;
    frame->sprite0_y = 0U;
    frame->start_pressed = 0U;
    frame->operating_mode = 0U;
    frame->operating_mode_task = 0U;
}
void mysmb_game_tick(struct mysmb_game *game, const struct mysmb_input *input,
                     struct mysmb_frame *frame)
{
    mysmb_frame_root_step(game, input, frame);
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
