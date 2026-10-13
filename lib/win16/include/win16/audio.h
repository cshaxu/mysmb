#ifndef MYGAMES_WIN16_AUDIO_H
#define MYGAMES_WIN16_AUDIO_H
#include "kvm/types.h"
/* One process-local mono unsigned-8-bit PCM device. No game or synthesis state. */
int mygames_win16_audio_open(unsigned long sample_rate);
int mygames_win16_audio_submit(const mygames_kvm_u8 *samples,mygames_kvm_u16 count);
int mygames_win16_audio_reset(void);
void mygames_win16_audio_close(void);
#endif
