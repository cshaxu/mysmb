#ifndef MYSMB_GAME_FRAME_ROOT_H
#define MYSMB_GAME_FRAME_ROOT_H

#include "game/game.h"

void mysmb_frame_root_step(struct mysmb_game *game,
                           const struct mysmb_input *input,
                           struct mysmb_frame *frame);
void mysmb_game_step_victory(struct mysmb_game *game);
void mysmb_game_step_game_over(struct mysmb_game *game);
void mysmb_game_step_screen_routine(struct mysmb_game *game);
void mysmb_game_primary_setup(struct mysmb_game *game);
void mysmb_game_secondary_setup(struct mysmb_game *game);
void mysmb_game_lose_life(struct mysmb_game *game);
void mysmb_game_next_area(struct mysmb_game *game);
mysmb_u8 mysmb_game_run_timer(struct mysmb_game *game);
void mysmb_game_cycle_player_palette(struct mysmb_game *game);
void mysmb_game_step_area_parser(struct mysmb_game *game);
mysmb_u8 mysmb_frame_root_begin(struct mysmb_game *game,
                            const struct mysmb_input *input,
                            mysmb_u8 *mode_before,
                            mysmb_u8 *task_before);
void mysmb_frame_root_read_joypads(struct mysmb_game *game,
                                   mysmb_u8 buttons1, mysmb_u8 buttons2);
mysmb_u8 mysmb_frame_root_pause_step(struct mysmb_game *game);
void mysmb_frame_root_update_top_score(struct mysmb_game *game);
void mysmb_frame_root_finish(const struct mysmb_game *game,
                             struct mysmb_frame *frame);
void mysmb_game_submit_oam(struct mysmb_game *game);
void mysmb_game_commit_vram_buffer(struct mysmb_game *game);
void mysmb_game_commit_display_state(struct mysmb_game *game);
void mysmb_game_tick_player_timers(struct mysmb_game *game);
void mysmb_game_rotate_pseudorandom(struct mysmb_game *game);
void mysmb_game_shuffle_sprite_offsets(struct mysmb_game *game);

#endif
