#ifndef MYSMB_PLATFORM_DOS16_DOS_AUDIO_H
#define MYSMB_PLATFORM_DOS16_DOS_AUDIO_H

#include "kvm/types.h"
#include "io/audio.h"

enum {
    MYSMB_DOS16_AUDIO_SAMPLE_RATE=11025U,
    MYSMB_DOS16_AUDIO_BLOCK_BYTES=2048U,
    MYSMB_DOS16_AUDIO_BLOCK_COUNT=2U
};

/* This is a physical-device contract only.  It deliberately has no APU or
 * game-state field: a later renderer may feed the prepared PCM DMA blocks,
 * but discovery and resource ownership must be independently testable. */
struct mysmb_dos16_audio_config {
    mygames_kvm_u16 base_port;
    mygames_kvm_u8 irq;
    mygames_kvm_u8 dma_channel;
};

struct mysmb_dos16_audio_ops {
    int (*probe)(void *context,const struct mysmb_dos16_audio_config *config);
    int (*reserve)(void *context,const struct mysmb_dos16_audio_config *config);
    void (*release)(void *context);
};

struct mysmb_dos16_audio_state {
    struct mysmb_dos16_audio_config config;
    const struct mysmb_dos16_audio_ops *ops;
    void *context;
    mygames_kvm_u8 ready;
    mygames_kvm_u8 reserved;
};

/* Integer-only NES-output consumer.  It is an adapter-side PCM projection,
 * not another game/APU implementation: source-ordered writes remain its sole
 * input and its state is never serialized with original program RAM. */
struct mysmb_dos16_audio_renderer {
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

/* Parse the conventional BLASTER A (hex base I/O), I (IRQ) and D (8-bit DMA)
 * fields.  Unknown fields are intentionally ignored; all three required
 * fields must occur once and be in range. */
int mysmb_dos16_audio_parse_blaster(const char *value,
    struct mysmb_dos16_audio_config *config);
void mysmb_dos16_audio_initialize(struct mysmb_dos16_audio_state *state);
int mysmb_dos16_audio_open(struct mysmb_dos16_audio_state *state,
    const char *blaster,const struct mysmb_dos16_audio_ops *ops,void *context);
void mysmb_dos16_audio_close(struct mysmb_dos16_audio_state *state);
/* Reassert device presence after load without allocating, opening a vector or
 * changing presentation state.  A lost device releases its reserved memory. */
int mysmb_dos16_audio_reprobe(struct mysmb_dos16_audio_state *state);
void mysmb_dos16_audio_renderer_initialize(
    struct mysmb_dos16_audio_renderer *renderer);
/* Renders one source tick into at most capacity unsigned 8-bit PCM samples.
 * It returns the count (183 or 184 at 11,025Hz); insufficient capacity yields
 * zero and does not consume the source frame. */
unsigned short mysmb_dos16_audio_renderer_render(
    struct mysmb_dos16_audio_renderer *renderer,
    const struct mysmb_io_audio_frame *frame,mygames_kvm_u8 *samples,
    unsigned short capacity);

/* DOS hardware binding.  It owns only the standard BLASTER environment,
 * Sound Blaster DSP reset handshake and one fixed future-DMA reservation.
 * It deliberately installs no IRQ and starts no DMA until PCM exists. */
int mysmb_dos16_audio_dos_open(void);
void mysmb_dos16_audio_dos_close(void);
void mysmb_dos16_audio_dos_after_load(void);
int mysmb_dos16_audio_dos_prepared(void);
mygames_kvm_u8 mysmb_dos16_audio_dos_submit(
    const struct mysmb_io_audio_frame *frame);

#endif
