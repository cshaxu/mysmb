#ifndef MYSMB_PLATFORM_DOS16_SLOT_COPY_H
#define MYSMB_PLATFORM_DOS16_SLOT_COPY_H
#include "ppu/frame.h"
/* Physical-only equivalent of the neutral 256-slot-row contract,1..240rows.
 * Caller supplies non-overlapping, segment-contained source/destination spans. */
int mysmb_dos16_slot_rows_copy(const mygames_kvm_u8 MYGAMES_KVM_FAR *first,
    const mygames_kvm_u8 MYGAMES_KVM_FAR *second,mygames_kvm_u8 MYGAMES_KVM_FAR *destination,
    mygames_kvm_u16 first_count,mygames_kvm_u16 second_count,mygames_kvm_u16 rows);
#endif
