#include "game/frame_root.h"
#include "game/audio.h"

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

mysmb_u8 mysmb_frame_root_begin(struct mysmb_game *game,
                            const struct mysmb_input *input,
                            mysmb_u8 *mode_before, mysmb_u8 *task_before)
{
    mysmb_u8 oam_offset;
    mysmb_u8 paused;

    *mode_before = game->ram[MYSMB_ROOT_OPERATING_MODE];
    *task_before = game->ram[MYSMB_ROOT_OPERATING_MODE_TASK];
    game->frame_number++;
    game->ram[MYSMB_ROOT_FRAME_COUNTER]++;
    if (game->oam_dma_primed != 0U) mysmb_game_submit_oam(game);
    else game->oam_dma_primed = 1U;
    mysmb_game_commit_vram_buffer(game);
    mysmb_game_commit_display_state(game);
    mysmb_audio_step(game);
    (void)mysmb_frame_root_latch_joypad1(game, input->buttons);
    paused = mysmb_frame_root_pause_step(game);
    mysmb_frame_root_update_top_score(game);
    if (paused == 0U) mysmb_game_tick_player_timers(game);
    mysmb_game_rotate_pseudorandom(game);
    if (game->ram[MYSMB_ROOT_SPRITE0_HIT] == 0U) return paused;
    oam_offset = 4U;
    do {
        game->ram[(mysmb_u16)(MYSMB_ROOT_OAM + oam_offset)] = 0xf8U;
        oam_offset = (mysmb_u8)(oam_offset + 4U);
    } while (oam_offset != 0U);
    if (paused == 0U) mysmb_game_shuffle_sprite_offsets(game);
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
