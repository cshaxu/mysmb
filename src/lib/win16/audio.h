#ifndef MYGAMES_WIN16_AUDIO_H
#define MYGAMES_WIN16_AUDIO_H
#include "kvm/types.h"
/* One process-local mono unsigned-8-bit PCM device. No game or synthesis state. */
int mygames_win16_audio_open(unsigned long sample_rate,
    mygames_kvm_u16 block_samples,mygames_kvm_u16 block_count);
int mygames_win16_audio_submit(const mygames_kvm_u8 MYGAMES_KVM_FAR *samples,mygames_kvm_u16 count);
int mygames_win16_audio_reset(void);
void mygames_win16_audio_close(void);
#endif
