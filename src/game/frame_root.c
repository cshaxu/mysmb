#include "game/frame_root.h"
#include "game/audio.h"

enum {
    MYSMB_ROOT_FRAME_COUNTER = 0x0009U,
    MYSMB_ROOT_OPERATING_MODE = 0x0770U,
    MYSMB_ROOT_OPERATING_MODE_TASK = 0x0772U,
    MYSMB_ROOT_SPRITE0_HIT = 0x0722U,
    MYSMB_ROOT_SAVED_JOYPAD1 = 0x06fcU,
    MYSMB_ROOT_JOYPAD_MASK1 = 0x074aU,
    MYSMB_ROOT_OAM = 0x0200U
};

void mysmb_frame_root_begin(struct mysmb_game *game, mysmb_u8 *mode_before,
                            mysmb_u8 *task_before)
{
    mysmb_u8 oam_offset;

    *mode_before = game->ram[MYSMB_ROOT_OPERATING_MODE];
    *task_before = game->ram[MYSMB_ROOT_OPERATING_MODE_TASK];
    game->frame_number++;
    game->ram[MYSMB_ROOT_FRAME_COUNTER]++;
    if (game->oam_dma_primed != 0U) mysmb_game_submit_oam(game);
    else game->oam_dma_primed = 1U;
    mysmb_game_commit_vram_buffer(game);
    mysmb_game_commit_display_state(game);
    mysmb_audio_step(game);
    mysmb_game_tick_player_timers(game);
    mysmb_game_rotate_pseudorandom(game);
    if (game->ram[MYSMB_ROOT_SPRITE0_HIT] == 0U) return;
    oam_offset = 4U;
    do {
        game->ram[(mysmb_u16)(MYSMB_ROOT_OAM + oam_offset)] = 0xf8U;
        oam_offset = (mysmb_u8)(oam_offset + 4U);
    } while (oam_offset != 0U);
    mysmb_game_shuffle_sprite_offsets(game);
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
