#ifndef MYSMB_PLATFORM_WIN32_AUDIO_RENDERER_H
#define MYSMB_PLATFORM_WIN32_AUDIO_RENDERER_H

#include "io/audio.h"

struct mysmb_win32_audio_renderer {
    mygames_kvm_u8 registers[24];
    mygames_kvm_u8 enabled;
    unsigned int length[4];
    unsigned int envelope_level[3];
    unsigned int envelope_divider[3];
    mygames_kvm_u8 envelope_start[3];
    unsigned int pulse_timer[2];
    unsigned int sweep_divider[2];
    mygames_kvm_u8 sweep_reload[2];
    unsigned int triangle_linear;
    mygames_kvm_u8 triangle_reload;
    double pulse_phase[2];
    double triangle_phase;
    double noise_phase;
    double highpass_input;
    double highpass_output;
    unsigned short noise_shift;
};

void mysmb_win32_audio_renderer_initialize(
    struct mysmb_win32_audio_renderer *renderer);
void mysmb_win32_audio_render(struct mysmb_win32_audio_renderer *renderer,
    const struct mysmb_io_audio_frame *frame, short *samples, unsigned int count,
    unsigned int sample_rate);

#endif
