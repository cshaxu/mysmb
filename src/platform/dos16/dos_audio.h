#ifndef MYSMB_PLATFORM_DOS16_DOS_AUDIO_H
#define MYSMB_PLATFORM_DOS16_DOS_AUDIO_H

#include "io/types.h"

/* This is a physical-device contract only.  It deliberately has no APU or
 * game-state field: a later renderer may feed the prepared PCM DMA blocks,
 * but discovery and resource ownership must be independently testable. */
struct mysmb_dos16_audio_config {
    mysmb_io_u16 base_port;
    mysmb_io_u8 irq;
    mysmb_io_u8 dma_channel;
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
    mysmb_io_u8 ready;
    mysmb_io_u8 reserved;
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

/* DOS hardware binding.  It owns only the standard BLASTER environment,
 * Sound Blaster DSP reset handshake and one fixed future-DMA reservation.
 * It deliberately installs no IRQ and starts no DMA until PCM exists. */
int mysmb_dos16_audio_dos_open(void);
void mysmb_dos16_audio_dos_close(void);
void mysmb_dos16_audio_dos_after_load(void);
int mysmb_dos16_audio_dos_prepared(void);

#endif
