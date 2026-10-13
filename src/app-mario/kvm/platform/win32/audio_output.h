#ifndef MYSMB_PLATFORM_WIN32_AUDIO_OUTPUT_H
#define MYSMB_PLATFORM_WIN32_AUDIO_OUTPUT_H

#include <windows.h>
#include <mmsystem.h>
#include "win32/pcm_session.h"

#include "platform/win32/audio_renderer.h"

#define MYSMB_WIN32_AUDIO_RATE 44100U
#define MYSMB_WIN32_AUDIO_FRAME_SAMPLES 735U
#define MYSMB_WIN32_AUDIO_BUFFERS 8U

struct mysmb_win32_audio_output {
    struct mygames_win32_pcm_session *session;
    LONG recovery;
    struct mysmb_win32_audio_renderer renderer;
};

int mysmb_win32_audio_open(struct mysmb_win32_audio_output *output);
void mysmb_win32_audio_submit(struct mysmb_win32_audio_output *output,
    const struct mysmb_io_audio_frame *frame);
int mysmb_win32_audio_close(struct mysmb_win32_audio_output *output);
int mysmb_win32_audio_available(struct mysmb_win32_audio_output *output);
/* Discard device buffers only;keep renderer state under its own owner. */
LONG mysmb_win32_audio_reset_queue(struct mysmb_win32_audio_output *output);

#endif
