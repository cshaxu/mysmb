#ifndef MYGAMES_KVM_WINDOWS_KEY_H
#define MYGAMES_KVM_WINDOWS_KEY_H
#include "kvm/input_event.h"
/* Windows keyboard message wire codes, independent of USER and pointer ABI. */
mygames_kvm_u16 mygames_kvm_windows_key(mygames_kvm_u16 key,
    mygames_kvm_u16 scan);
#endif
