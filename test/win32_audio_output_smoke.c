#include <string.h>

#include "platform/win32/audio_output.h"

int main(void)
{
    struct mysmb_game game;
    struct mysmb_win32_audio_output output;
    unsigned int frame;
    unsigned int index;
    unsigned int done;
    unsigned int wait;

    if (waveOutGetNumDevs() == 0U) return 77;
    memset(&game, 0, sizeof(game));
    game.apu_channel_enable = 1U;
    game.apu_registers[0U] = 0x9fU;
    game.apu_registers[2U] = 253U;
    game.apu_writes[0U].index = 21U;
    game.apu_writes[0U].value = 1U;
    game.apu_writes[1U].index = 0U;
    game.apu_writes[1U].value = 0x9fU;
    game.apu_writes[2U].index = 2U;
    game.apu_writes[2U].value = 253U;
    game.apu_writes[3U].index = 3U;
    game.apu_writes[3U].value = 0U;
    game.apu_write_count = 4U;
    if (mysmb_win32_audio_open(&output) == 0) return 1;

    for (frame = 0U; frame < MYSMB_WIN32_AUDIO_BUFFERS; ++frame)
        mysmb_win32_audio_submit(&output, &game);
    game.apu_write_count = 0U;
    if (output.queued[0] == 0U || output.samples[0][50U] == 0) {
        mysmb_win32_audio_close(&output);
        return 2;
    }
    /* Reuse completed headers while the normal 60 Hz producer continues. */
    for (frame = 0U; frame < 24U; ++frame) {
        Sleep(17U);
        mysmb_win32_audio_submit(&output, &game);
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
