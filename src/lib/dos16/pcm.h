#ifndef MYGAMES_DOS16_PCM_H
#define MYGAMES_DOS16_PCM_H
#include "kvm/audio.h"
enum {MYGAMES_DOS16_PCM_BLOCK_BYTES=2048U,MYGAMES_DOS16_PCM_BLOCK_COUNT=2U};
struct mygames_dos16_pcm_config {
    mygames_kvm_u16 base_port;
    mygames_kvm_u8 irq;
    mygames_kvm_u8 dma_channel;
};

struct mygames_dos16_pcm_ops {
    int (*probe)(void *context,const struct mygames_dos16_pcm_config *config);
    int (*reserve)(void *context,const struct mygames_dos16_pcm_config *config);
    void (*release)(void *context);
};

struct mygames_dos16_pcm_state {
    struct mygames_dos16_pcm_config config;
    const struct mygames_dos16_pcm_ops *ops;
    void *context;
    mygames_kvm_u8 ready;
    mygames_kvm_u8 reserved;
};

/* Parse the conventional BLASTER A (hex base I/O), I (IRQ) and D (8-bit DMA)
 * fields.  Unknown fields are intentionally ignored; all three required
 * fields must occur once and be in range. */
int mygames_dos16_pcm_parse_blaster(const char *value,
    struct mygames_dos16_pcm_config *config);
void mygames_dos16_pcm_initialize(struct mygames_dos16_pcm_state *state);
int mygames_dos16_pcm_open(struct mygames_dos16_pcm_state *state,
    const char *blaster,const struct mygames_dos16_pcm_ops *ops,void *context);
void mygames_dos16_pcm_close(struct mygames_dos16_pcm_state *state);
/* Reassert device presence after load without allocating, opening a vector or
 * changing presentation state.  A lost device releases its reserved memory. */
int mygames_dos16_pcm_reprobe(struct mygames_dos16_pcm_state *state);
/* 8-bit mono PCM device. Rate is caller configuration; no game/tick meaning.
 * Hardware binding has one process owner, explicit open/reset/close. */
int mygames_dos16_pcm_dos_open(unsigned short rate);
/* 0 retains a pending IRQ; service again after restoring caller IF. */
int mygames_dos16_pcm_dos_close(void);
void mygames_dos16_pcm_dos_reset(void);
int mygames_dos16_pcm_dos_prepared(void);
/* Exact accepted prefix; callers must not retry already consumed samples. */
mygames_kvm_u16 mygames_dos16_pcm_dos_submit(const mygames_kvm_u8 MYGAMES_KVM_FAR *samples,unsigned short count);
enum {MYGAMES_DOS16_PCM_DSP_BUSY=1,MYGAMES_DOS16_PCM_LOST_IRQ=2};
int mygames_dos16_pcm_dos_phase(void);
unsigned short mygames_dos16_pcm_dos_error(void);
/* Existing BIOS/PIT clock units (1193182 Hz); no additional timer or ISR. */
void mygames_dos16_pcm_dos_service(unsigned long now);
#endif
