#ifndef MYSMB_DOS16_NIBBLE_EXPAND_H
#define MYSMB_DOS16_NIBBLE_EXPAND_H
#include "io/palette_expand.h"
int mysmb_dos16_nibble_expand(const mygames_kvm_u8 MYGAMES_KVM_FAR *packed,
    mygames_kvm_u8 MYGAMES_KVM_FAR *pixels,mygames_kvm_u16 count);
#endif
