#include <string.h>

#include "platform/win32/audio_renderer.h"

#define SAMPLE_RATE 44100U
#define FRAME_SAMPLES 735U

static void apu_write(struct mysmb_game *game, unsigned int index,
                      mysmb_u8 value)
{
    game->apu_registers[index] = value;
    game->apu_writes[game->apu_write_count].index = (mysmb_u8)index;
    game->apu_writes[game->apu_write_count].value = value;
    game->apu_write_count++;
}

static unsigned int nonzero_samples(const short *samples)
{
    unsigned int index;
    unsigned int count;

    count = 0U;
    for (index = 0U; index < FRAME_SAMPLES; ++index)
        if (samples[index] != 0) count++;
    return count;
}

static unsigned int sign_changes(const short *samples)
{
    unsigned int index;
    unsigned int count;
    int previous;
    int current;

    count = 0U;
    previous = 0;
    for (index = 0U; index < FRAME_SAMPLES; ++index) {
        current = samples[index] > 0 ? 1 : samples[index] < 0 ? -1 : 0;
        if (current != 0) {
            if (previous != 0 && current != previous) count++;
            previous = current;
        }
    }
    return count;
}

static void render_frame(struct mysmb_win32_audio_renderer *renderer,
    struct mysmb_game *game, short *samples)
{
    mysmb_win32_audio_render(renderer, game, samples, FRAME_SAMPLES,
                            SAMPLE_RATE);
    game->apu_write_count = 0U;
}

int main(void)
{
    struct mysmb_game game;
    struct mysmb_win32_audio_renderer renderer;
    short samples[FRAME_SAMPLES];
    unsigned int high_pitch_changes;
    unsigned int frame;

    memset(&game, 0, sizeof(game));
    mysmb_win32_audio_renderer_initialize(&renderer);
    render_frame(&renderer, &game, samples);
    if (nonzero_samples(samples) != 0U) return 1;

    apu_write(&game, 21U, 1U);
    apu_write(&game, 0U, 0x9fU);
    apu_write(&game, 2U, 253U);
    apu_write(&game, 3U, 0U);
    render_frame(&renderer, &game, samples);
    if (nonzero_samples(samples) < FRAME_SAMPLES / 2U) return 2;
    high_pitch_changes = sign_changes(samples);
    if (high_pitch_changes < 10U) return 3;

    mysmb_win32_audio_renderer_initialize(&renderer);
    game.apu_write_count = 0U;
    apu_write(&game, 21U, 1U);
    apu_write(&game, 0U, 0x9fU);
    apu_write(&game, 2U, 251U);
    apu_write(&game, 3U, 1U);
    render_frame(&renderer, &game, samples);
    if (sign_changes(samples) >= high_pitch_changes) return 4;

    memset(&game, 0, sizeof(game));
    mysmb_win32_audio_renderer_initialize(&renderer);
    apu_write(&game, 21U, 4U);
    apu_write(&game, 8U, 0x1fU);
    apu_write(&game, 10U, 126U);
    apu_write(&game, 11U, 0U);
    render_frame(&renderer, &game, samples);
    if (nonzero_samples(samples) < FRAME_SAMPLES / 2U) return 5;
    if (renderer.triangle_linear >= 31U) return 6;

    memset(&game, 0, sizeof(game));
    mysmb_win32_audio_renderer_initialize(&renderer);
    apu_write(&game, 21U, 8U);
    apu_write(&game, 12U, 0x1fU);
    apu_write(&game, 14U, 8U);
    apu_write(&game, 15U, 0x18U);
    render_frame(&renderer, &game, samples);
    if (nonzero_samples(samples) < FRAME_SAMPLES / 2U) return 7;
    if (renderer.length[3U] != 0U) return 8;
    render_frame(&renderer, &game, samples);
    if (renderer.length[3U] != 0U) return 9;
    /* The next note may write the same $400F value again. */
    apu_write(&game, 15U, 0x18U);
    render_frame(&renderer, &game, samples);
    if (nonzero_samples(samples) < FRAME_SAMPLES / 2U) return 10;

    mysmb_win32_audio_renderer_initialize(&renderer);
    game.apu_write_count = 0U;
    apu_write(&game, 21U, 8U);
    apu_write(&game, 12U, 0x0cU);
    apu_write(&game, 15U, 0x58U);
    for (frame = 0U; frame < 4U; ++frame)
        render_frame(&renderer, &game, samples);
    if (renderer.envelope_level[2U] >= 15U ||
        renderer.envelope_level[2U] == 0U) return 11;

    memset(&game, 0, sizeof(game));
    mysmb_win32_audio_renderer_initialize(&renderer);
    apu_write(&game, 21U, 1U);
    apu_write(&game, 0U, 0x82U);
    apu_write(&game, 2U, 253U);
    apu_write(&game, 3U, 0x08U);
    render_frame(&renderer, &game, samples);
    if (renderer.envelope_level[0U] <= 2U) return 12;
    return 0;
}
