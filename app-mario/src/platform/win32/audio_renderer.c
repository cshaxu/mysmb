#include <string.h>

#include "platform/win32/audio_renderer.h"

/* The host consumes ordered APU writes without changing translated game state. */
static const unsigned int mysmb_length_periods[32] = {
    10U, 254U, 20U, 2U, 40U, 4U, 80U, 6U,
    160U, 8U, 60U, 10U, 14U, 12U, 26U, 14U,
    12U, 16U, 24U, 18U, 48U, 20U, 96U, 22U,
    192U, 24U, 72U, 26U, 16U, 28U, 32U, 30U
};
static const unsigned int mysmb_noise_periods[16] = {
    4U, 8U, 16U, 32U, 64U, 96U, 128U, 160U,
    202U, 254U, 380U, 508U, 762U, 1016U, 2034U, 4068U
};
static const double mysmb_pulse_duty[4] = {
    0.125, 0.25, 0.5, 0.75
};

void mysmb_win32_audio_renderer_initialize(
    struct mysmb_win32_audio_renderer *renderer)
{
    memset(renderer, 0, sizeof(*renderer));
    renderer->noise_shift = 1U;
}

static void mysmb_win32_audio_clock_length(
    struct mysmb_win32_audio_renderer *renderer)
{
    static const unsigned int control[4] = {0U, 4U, 8U, 12U};
    unsigned int channel;

    for (channel = 0U; channel < 4U; ++channel)
        if ((renderer->registers[control[channel]] & 0x20U) == 0U &&
            renderer->length[channel] != 0U)
            renderer->length[channel]--;
}

static void mysmb_win32_audio_clock_sweep(
    struct mysmb_win32_audio_renderer *renderer, unsigned int channel)
{
    unsigned int control;
    unsigned int timer;
    unsigned int change;
    unsigned int target;

    control = renderer->registers[channel * 4U + 1U];
    timer = renderer->pulse_timer[channel];
    change = timer >> (control & 7U);
    target = (control & 8U) != 0U ?
        timer - change - (channel == 0U ? 1U : 0U) : timer + change;
    if (renderer->sweep_divider[channel] == 0U &&
        (control & 0x80U) != 0U && (control & 7U) != 0U &&
        timer >= 8U && target <= 0x7ffU)
        renderer->pulse_timer[channel] = target;
    if (renderer->sweep_divider[channel] == 0U ||
        renderer->sweep_reload[channel] != 0U) {
        renderer->sweep_divider[channel] = (control >> 4U) & 7U;
        renderer->sweep_reload[channel] = 0U;
    }
    else renderer->sweep_divider[channel]--;
}

static void mysmb_win32_audio_clock_quarter(
    struct mysmb_win32_audio_renderer *renderer)
{
    static const unsigned int control[3] = {0U, 4U, 12U};
    unsigned int channel;
    unsigned int period;

    for (channel = 0U; channel < 3U; ++channel) {
        period = renderer->registers[control[channel]] & 15U;
        if (renderer->envelope_start[channel] != 0U) {
            renderer->envelope_start[channel] = 0U;
            renderer->envelope_level[channel] = 15U;
            renderer->envelope_divider[channel] = period;
        }
        else if (renderer->envelope_divider[channel] != 0U)
            renderer->envelope_divider[channel]--;
        else {
            renderer->envelope_divider[channel] = period;
            if (renderer->envelope_level[channel] != 0U)
                renderer->envelope_level[channel]--;
            else if ((renderer->registers[control[channel]] & 0x20U) != 0U)
                renderer->envelope_level[channel] = 15U;
        }
    }
    if (renderer->triangle_reload != 0U)
        renderer->triangle_linear = renderer->registers[8U] & 0x7fU;
    else if (renderer->triangle_linear != 0U)
        renderer->triangle_linear--;
    if ((renderer->registers[8U] & 0x80U) == 0U)
        renderer->triangle_reload = 0U;
}

static void mysmb_win32_audio_apply_writes(
    struct mysmb_win32_audio_renderer *renderer,
    const struct mysmb_io_audio_frame *frame)
{
    unsigned int event;
    unsigned int channel;
    unsigned int index;
    mysmb_io_u8 value;

    for (event = 0U; event < frame->write_count &&
         event < MYSMB_IO_AUDIO_WRITE_CAPACITY;
         ++event) {
        index = frame->writes[event].index;
        value = frame->writes[event].value;
        if (index >= 24U) continue;
        renderer->registers[index] = value;
        if (index < 8U) {
            channel = index >> 2U;
            if ((index & 3U) == 1U)
                renderer->sweep_reload[channel] = 1U;
            else if ((index & 3U) == 2U)
                renderer->pulse_timer[channel] =
                    (renderer->pulse_timer[channel] & 0x700U) | value;
            else if ((index & 3U) == 3U)
                renderer->pulse_timer[channel] =
                    (renderer->pulse_timer[channel] & 0xffU) |
                    ((unsigned int)(value & 7U) << 8U);
        }
        if (index == 21U) {
            renderer->enabled = value & 15U;
            for (channel = 0U; channel < 4U; ++channel)
                if ((renderer->enabled & (1U << channel)) == 0U)
                    renderer->length[channel] = 0U;
        }
        else if (index == 23U) {
            if ((value & 0x80U) != 0U)
                mysmb_win32_audio_clock_length(renderer);
        }
        else if (index == 3U || index == 7U ||
                 index == 11U || index == 15U) {
            channel = index >> 2U;
            if ((renderer->enabled & (1U << channel)) != 0U)
                renderer->length[channel] =
                    mysmb_length_periods[value >> 3U];
            if (index == 3U || index == 7U) {
                renderer->pulse_phase[channel] = 0.0;
                renderer->envelope_start[channel] = 1U;
            }
            else if (index == 11U) renderer->triangle_reload = 1U;
            else if ((renderer->enabled & 8U) != 0U)
                renderer->envelope_start[2U] = 1U;
        }
    }
}

static double mysmb_win32_pulse_sample(
    struct mysmb_win32_audio_renderer *renderer,
    unsigned int channel, unsigned int sample_rate)
{
    unsigned int offset;
    unsigned int timer;
    unsigned int volume;
    double phase;

    offset = channel * 4U;
    if ((renderer->enabled & (1U << channel)) == 0U ||
        renderer->length[channel] == 0U) return 0.0;
    volume = (renderer->registers[offset] & 0x10U) != 0U ?
        (renderer->registers[offset] & 15U) :
        renderer->envelope_level[channel];
    timer = renderer->pulse_timer[channel];
    if (volume == 0U || timer < 8U) return 0.0;
    phase = renderer->pulse_phase[channel] +
        1789773.0 / (16.0 * (double)(timer + 1U) * (double)sample_rate);
    if (phase >= 1.0) phase -= (unsigned int)phase;
    renderer->pulse_phase[channel] = phase;
    return phase < mysmb_pulse_duty[renderer->registers[offset] >> 6U] ?
        (double)volume * 450.0 : 0.0;
}

static double mysmb_win32_triangle_sample(
    struct mysmb_win32_audio_renderer *renderer, unsigned int sample_rate)
{
    unsigned int timer;
    double phase;

    if ((renderer->enabled & 4U) == 0U || renderer->length[2U] == 0U ||
        renderer->triangle_linear == 0U) return 0.0;
    timer = renderer->registers[10U] |
        ((unsigned int)(renderer->registers[11U] & 7U) << 8U);
    if (timer < 2U) return 0.0;
    phase = renderer->triangle_phase +
        1789773.0 / (32.0 * (double)(timer + 1U) * (double)sample_rate);
    if (phase >= 1.0) phase -= (unsigned int)phase;
    renderer->triangle_phase = phase;
    return phase < 0.5 ? 3360.0 * (2.0 * phase) :
        3360.0 * (2.0 - 2.0 * phase);
}

static double mysmb_win32_noise_sample(
    struct mysmb_win32_audio_renderer *renderer, unsigned int sample_rate)
{
    unsigned int volume;
    unsigned int tap;
    unsigned int feedback;

    if ((renderer->enabled & 8U) == 0U || renderer->length[3U] == 0U)
        return 0.0;
    volume = (renderer->registers[12U] & 0x10U) != 0U ?
        (renderer->registers[12U] & 15U) : renderer->envelope_level[2U];
    if (volume == 0U) return 0.0;
    renderer->noise_phase += 1789773.0 /
        ((double)(mysmb_noise_periods[renderer->registers[14U] & 15U] + 1U) *
         (double)sample_rate);
    tap = (renderer->registers[14U] & 0x80U) != 0U ? 6U : 1U;
    while (renderer->noise_phase >= 1.0) {
        feedback = (renderer->noise_shift ^
            (renderer->noise_shift >> tap)) & 1U;
        renderer->noise_shift = (unsigned short)(
            (renderer->noise_shift >> 1U) | (feedback << 14U));
        renderer->noise_phase -= 1.0;
    }
    return (renderer->noise_shift & 1U) == 0U ?
        (double)volume * 336.0 : 0.0;
}

void mysmb_win32_audio_render(struct mysmb_win32_audio_renderer *renderer,
    const struct mysmb_io_audio_frame *frame, short *samples, unsigned int count,
    unsigned int sample_rate)
{
    unsigned int index;
    double input;
    double output;

    if (sample_rate == 0U) return;
    mysmb_win32_audio_apply_writes(renderer, frame);
    for (index = 0U; index < count; ++index) {
        if (index == count / 4U || index == count / 2U ||
            index == (count * 3U) / 4U) {
            mysmb_win32_audio_clock_quarter(renderer);
            if (index == count / 2U) {
                mysmb_win32_audio_clock_length(renderer);
                mysmb_win32_audio_clock_sweep(renderer, 0U);
                mysmb_win32_audio_clock_sweep(renderer, 1U);
            }
        }
        input = mysmb_win32_pulse_sample(renderer, 0U, sample_rate) +
            mysmb_win32_pulse_sample(renderer, 1U, sample_rate) +
            mysmb_win32_triangle_sample(renderer, sample_rate) +
            mysmb_win32_noise_sample(renderer, sample_rate);
        output = input - renderer->highpass_input +
            0.995 * renderer->highpass_output;
        renderer->highpass_input = input;
        renderer->highpass_output = output;
        if (output > 32767.0) output = 32767.0;
        if (output < -32768.0) output = -32768.0;
        samples[index] = (short)output;
    }
    if ((renderer->registers[23U] & 0x80U) == 0U) {
        mysmb_win32_audio_clock_quarter(renderer);
        mysmb_win32_audio_clock_length(renderer);
        mysmb_win32_audio_clock_sweep(renderer, 0U);
        mysmb_win32_audio_clock_sweep(renderer, 1U);
    }
}
