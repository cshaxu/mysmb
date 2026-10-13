#ifndef MYSMB_IO_AUDIO_RENDERER_H
#define MYSMB_IO_AUDIO_RENDERER_H
#include "io/audio.h"
#define MYSMB_AUDIO_SAMPLE_RATE 11025U
/* Integer-only NES-output consumer.  It is an adapter-side PCM projection,
 * not another game/APU implementation: source-ordered writes remain its sole
 * input and its state is never serialized with original program RAM. */
struct mysmb_audio_renderer {
    mygames_kvm_u8 registers[MYSMB_IO_AUDIO_REGISTER_COUNT];
    mygames_kvm_u8 enabled;
    mygames_kvm_u8 envelope_start[3];
    mygames_kvm_u8 sweep_reload[2];
    mygames_kvm_u8 triangle_reload;
    mygames_kvm_u8 started;
    mygames_kvm_u16 length[4];
    mygames_kvm_u16 envelope_level[3];
    mygames_kvm_u16 envelope_divider[3];
    mygames_kvm_u16 sweep_divider[2];
    mygames_kvm_u16 triangle_linear;
    mygames_kvm_u16 pulse_timer[2];
    mygames_kvm_u16 noise_shift;
    unsigned long pulse_phase[2];
    unsigned long triangle_phase;
    unsigned long noise_phase;
    unsigned long sample_remainder;
    long highpass_input;
    long highpass_output;
};

void mysmb_audio_renderer_initialize(
    struct mysmb_audio_renderer *renderer);
/* Renders one source tick into at most capacity unsigned 8-bit PCM samples.
 * It returns the count (183 or 184 at 11,025Hz); insufficient capacity yields
 * zero and does not consume the source frame. */
unsigned short mysmb_audio_renderer_render(
    struct mysmb_audio_renderer *renderer,
    const struct mysmb_io_audio_frame *frame,mygames_kvm_u8 *samples,
    unsigned short capacity);

/* Restart device synthesis from a restored neutral register snapshot. */
void mysmb_audio_renderer_sync(struct mysmb_audio_renderer *renderer,
    const struct mysmb_io_audio_frame *frame);
#endif
