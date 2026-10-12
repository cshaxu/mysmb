#ifndef MYSMB_DOS16_PALETTE_EXPAND_H
#define MYSMB_DOS16_PALETTE_EXPAND_H
#include "io/palette_pairs.h"
int mysmb_dos16_palette_expand(void *context,
    const mygames_kvm_u8 MYGAMES_KVM_FAR *packed,mygames_kvm_u8 MYGAMES_KVM_FAR *pixels,
    mygames_kvm_u16 count,const mygames_kvm_u8 MYGAMES_KVM_FAR *palette);
#endif
