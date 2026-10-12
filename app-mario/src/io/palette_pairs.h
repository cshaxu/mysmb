#ifndef MYSMB_IO_PALETTE_PAIRS_H
#define MYSMB_IO_PALETTE_PAIRS_H
#include "kvm/types.h"
/* Packed low/high four-bit indices map to full eight-bit output colors. */
struct mysmb_io_palette_pairs {
    mygames_kvm_u16 pairs[256];
    mygames_kvm_u8 palette[16];
    mygames_kvm_u8 valid;
};
void mysmb_io_palette_pairs_prepare(struct mysmb_io_palette_pairs *workspace,
    const mygames_kvm_u8 MYGAMES_KVM_FAR *palette);
/* Return zero to select the caller's portable fallback. Even count<=256,
 * disjoint spans and count/2 input bytes are required by the caller. */
typedef int (*mysmb_io_palette_expand)(void *context,
    const mygames_kvm_u8 MYGAMES_KVM_FAR *packed,mygames_kvm_u8 MYGAMES_KVM_FAR *pixels,
    mygames_kvm_u16 count,const mygames_kvm_u8 MYGAMES_KVM_FAR *palette);
#endif
