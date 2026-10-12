#include <string.h>

#include "platform/win32/audio_output.h"

int main(void)
{
    struct mysmb_io_audio_frame audio;
    struct mysmb_win32_audio_output output;
    unsigned int frame;
    unsigned int index;
    unsigned int done;
    unsigned int wait;

    if (waveOutGetNumDevs() == 0U) return 77;
    memset(&audio, 0, sizeof(audio));
    audio.channel_enable = 1U;
    audio.registers[0U] = 0x9fU;
    audio.registers[2U] = 253U;
    audio.writes[0U].index = 21U;
    audio.writes[0U].value = 1U;
    audio.writes[1U].index = 0U;
    audio.writes[1U].value = 0x9fU;
    audio.writes[2U].index = 2U;
    audio.writes[2U].value = 253U;
    audio.writes[3U].index = 3U;
    audio.writes[3U].value = 0U;
    audio.write_count = 4U;
    if (mysmb_win32_audio_open(&output) == 0) return 1;

    for (frame = 0U; frame < MYSMB_WIN32_AUDIO_BUFFERS; ++frame)
        mysmb_win32_audio_submit(&output, &audio);
    audio.write_count = 0U;
    if (output.queued[0] == 0U || output.samples[0][50U] == 0) {
        mysmb_win32_audio_close(&output);
        return 2;
    }
    /* Reuse completed headers while the normal 60 Hz producer continues. */
    for (frame = 0U; frame < 24U; ++frame) {
        Sleep(17U);
        mysmb_win32_audio_submit(&output, &audio);
    }
    done = 0U;
    for (wait = 0U; wait < 200U && done == 0U; ++wait) {
        Sleep(10U);
        done = 1U;
        for (index = 0U; index < MYSMB_WIN32_AUDIO_BUFFERS; ++index)
            if ((output.headers[index].dwFlags & WHDR_DONE) == 0U)
                done = 0U;
    }
    mysmb_win32_audio_close(&output);
    return done != 0U ? 0 : 3;
}
