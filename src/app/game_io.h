#ifndef MYSMB_APP_GAME_IO_H
#define MYSMB_APP_GAME_IO_H

#include "game/game.h"
#include "ppu/frame.h"
#include "io/input.h"
#include "io/video.h"
#include "io/audio.h"

/* Composition glue only: copy public output without game or device policy. */
void mysmb_game_io_input(const struct mysmb_io_input *source,
                         struct mysmb_input *input);
void mysmb_game_io_video(const struct mysmb_ppu_frame *source,
                         struct mysmb_io_video_frame *frame);
void mysmb_game_io_audio(const struct mysmb_game *source,
                         struct mysmb_io_audio_frame *frame);

#endif
