#ifndef MYSMB_IO_PALETTE_EXPAND_H
#define MYSMB_IO_PALETTE_EXPAND_H
#include "io/palette_pairs.h"
/* Pair bytes are ordered low nibble then high nibble on every host. */
extern const mygames_kvm_u8 MYGAMES_KVM_FAR mysmb_io_nibble_pairs[512];
typedef int (*mysmb_io_nibble_expander)(const mygames_kvm_u8 MYGAMES_KVM_FAR *,
    mygames_kvm_u8 MYGAMES_KVM_FAR *,mygames_kvm_u16);
/* Lossless low/high nibble expansion,without interpreting a color palette. */
int mysmb_io_nibble_expand(const mygames_kvm_u8 MYGAMES_KVM_FAR *packed,
    mygames_kvm_u8 MYGAMES_KVM_FAR *pixels,mygames_kvm_u16 count);
/* Always available; a null context uses palette lookup without cached pairs.
 * Host overrides may reject a span; the shared caller retries this service. */
int mysmb_io_palette_expand_portable(void *context,
    const mygames_kvm_u8 MYGAMES_KVM_FAR *packed,
    mygames_kvm_u8 MYGAMES_KVM_FAR *pixels,mygames_kvm_u16 count,
    const mygames_kvm_u8 MYGAMES_KVM_FAR *palette);
#endif
