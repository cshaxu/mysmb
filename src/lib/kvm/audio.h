#ifndef MYGAMES_KVM_AUDIO_H
#define MYGAMES_KVM_AUDIO_H
#include "kvm/types.h"
/* Device facts only. A pending/stalled operation still owns its storage.
 * Hosts declare their execution mechanism; these names promise no cancellation. */
enum mygames_kvm_audio_phase {
    MYGAMES_AUDIO_CLOSED, MYGAMES_AUDIO_OPENING, MYGAMES_AUDIO_READY,
    MYGAMES_AUDIO_RESETTING, MYGAMES_AUDIO_FAILED, MYGAMES_AUDIO_STOPPING,
    MYGAMES_AUDIO_CLEANUP_FAILED
};
enum mygames_kvm_audio_result {
    MYGAMES_AUDIO_PENDING, MYGAMES_AUDIO_OK, MYGAMES_AUDIO_ERROR,
    MYGAMES_AUDIO_FULL
};
#endif
