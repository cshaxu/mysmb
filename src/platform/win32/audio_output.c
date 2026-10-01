#include "platform/win32/audio_output.h"

int mysmb_win32_audio_open(struct mysmb_win32_audio_output *output)
{
    WAVEFORMATEX format;
    unsigned int index;

    ZeroMemory(output, sizeof(*output));
    mysmb_win32_audio_renderer_initialize(&output->renderer);
    ZeroMemory(&format, sizeof(format));
    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nChannels = 1U;
    format.nSamplesPerSec = MYSMB_WIN32_AUDIO_RATE;
    format.wBitsPerSample = 16U;
    format.nBlockAlign = 2U;
    format.nAvgBytesPerSec = MYSMB_WIN32_AUDIO_RATE * 2U;
    if (waveOutOpen(&output->device, WAVE_MAPPER, &format, 0U, 0U,
                    CALLBACK_NULL) != MMSYSERR_NOERROR) return 0;

    for (index = 0U; index < MYSMB_WIN32_AUDIO_BUFFERS; ++index) {
        output->headers[index].lpData = (LPSTR)output->samples[index];
        output->headers[index].dwBufferLength =
            sizeof(output->samples[index]);
        if (waveOutPrepareHeader(output->device, &output->headers[index],
                sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
            mysmb_win32_audio_close(output);
            return 0;
        }
        output->prepared++;
    }
    return 1;
}

void mysmb_win32_audio_submit(struct mysmb_win32_audio_output *output,
    const struct mysmb_game *game)
{
    unsigned int offset;
    unsigned int index;
    short discarded[MYSMB_WIN32_AUDIO_FRAME_SAMPLES];

    if (output->device == 0) return;
    for (offset = 0U; offset < MYSMB_WIN32_AUDIO_BUFFERS; ++offset) {
        index = (output->next + offset) % MYSMB_WIN32_AUDIO_BUFFERS;
        if (output->queued[index] == 0U ||
            (output->headers[index].dwFlags & WHDR_DONE) != 0U) {
            mysmb_win32_audio_render(&output->renderer, game,
                output->samples[index], MYSMB_WIN32_AUDIO_FRAME_SAMPLES,
                MYSMB_WIN32_AUDIO_RATE);
            if (waveOutWrite(output->device, &output->headers[index],
                    sizeof(WAVEHDR)) == MMSYSERR_NOERROR) {
                output->queued[index] = 1U;
                output->next = (index + 1U) % MYSMB_WIN32_AUDIO_BUFFERS;
            }
            return;
        }
    }
    /* Preserve oscillator time when the audio device falls behind a tick. */
    mysmb_win32_audio_render(&output->renderer, game, discarded,
        MYSMB_WIN32_AUDIO_FRAME_SAMPLES, MYSMB_WIN32_AUDIO_RATE);
}

void mysmb_win32_audio_close(struct mysmb_win32_audio_output *output)
{
    unsigned int index;

    if (output->device == 0) return;
    waveOutReset(output->device);
    for (index = 0U; index < output->prepared; ++index)
        waveOutUnprepareHeader(output->device, &output->headers[index],
                               sizeof(WAVEHDR));
    waveOutClose(output->device);
    output->device = 0;
    output->prepared = 0U;
}
