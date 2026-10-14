#ifndef MYGAMES_WIN16_AUDIO_H
#define MYGAMES_WIN16_AUDIO_H
#include "kvm/audio.h"
/* One cooperative owner. service makes at most one WinMM lifecycle call;
 * submit only writes an available block. Neither promises to preempt a driver. */
int mygames_win16_audio_begin(unsigned long rate,mygames_kvm_u16 samples,
    mygames_kvm_u16 count,mygames_kvm_u16 attempts,unsigned long retry_ms);
void mygames_win16_audio_service(unsigned long now);
int mygames_win16_audio_phase(void);
mygames_kvm_u16 mygames_win16_audio_error(void);
/* Returns accepted sample count (all or none), never an ambiguous prefix. */
mygames_kvm_u16 mygames_win16_audio_submit(const mygames_kvm_u8 MYGAMES_KVM_FAR *,mygames_kvm_u16 count);
unsigned long mygames_win16_audio_reset(void);
int mygames_win16_audio_reset_result(unsigned long request);
void mygames_win16_audio_stop(void);
void mygames_win16_audio_retry_cleanup(void);
#endif
