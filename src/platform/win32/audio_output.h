#ifndef MYSMB_PLATFORM_WIN32_AUDIO_OUTPUT_H
#define MYSMB_PLATFORM_WIN32_AUDIO_OUTPUT_H

#include <windows.h>
#include <mmsystem.h>

#include "platform/win32/audio_renderer.h"

#define MYSMB_WIN32_AUDIO_RATE 44100U
#define MYSMB_WIN32_AUDIO_FRAME_SAMPLES 735U
#define MYSMB_WIN32_AUDIO_BUFFERS 8U

struct mysmb_win32_audio_output {
    HWAVEOUT device;
    WAVEHDR headers[MYSMB_WIN32_AUDIO_BUFFERS];
    short samples[MYSMB_WIN32_AUDIO_BUFFERS][MYSMB_WIN32_AUDIO_FRAME_SAMPLES];
    unsigned int prepared;
    unsigned int queued[MYSMB_WIN32_AUDIO_BUFFERS];
    unsigned int next;
    struct mysmb_win32_audio_renderer renderer;
};

int mysmb_win32_audio_open(struct mysmb_win32_audio_output *output);
void mysmb_win32_audio_submit(struct mysmb_win32_audio_output *output,
    const struct mysmb_io_audio_frame *frame);
void mysmb_win32_audio_close(struct mysmb_win32_audio_output *output);
/* Discard device buffers only;keep renderer state under its own owner. */
int mysmb_win32_audio_reset_queue(struct mysmb_win32_audio_output *output);

#endif
