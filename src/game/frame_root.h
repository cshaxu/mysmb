#ifndef MYSMB_GAME_FRAME_ROOT_H
#define MYSMB_GAME_FRAME_ROOT_H

#include "game/game.h"

void mysmb_frame_root_begin(struct mysmb_game *game,
                            const struct mysmb_input *input,
                            mysmb_u8 *mode_before,
                            mysmb_u8 *task_before);
mysmb_u8 mysmb_frame_root_latch_joypad1(struct mysmb_game *game, mysmb_u8 buttons);
mysmb_u8 mysmb_frame_root_pause_step(struct mysmb_game *game);
void mysmb_frame_root_finish(const struct mysmb_game *game,
                             struct mysmb_frame *frame);
void mysmb_game_submit_oam(struct mysmb_game *game);
void mysmb_game_commit_vram_buffer(struct mysmb_game *game);
void mysmb_game_commit_display_state(struct mysmb_game *game);
void mysmb_game_tick_player_timers(struct mysmb_game *game);
void mysmb_game_rotate_pseudorandom(struct mysmb_game *game);
void mysmb_game_shuffle_sprite_offsets(struct mysmb_game *game);

#endif
