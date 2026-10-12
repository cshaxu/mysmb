#ifndef MYSMB_DOS16_PLANAR_ROW_H
#define MYSMB_DOS16_PLANAR_ROW_H
#include "io/planar_frame.h"
void mysmb_dos16_pack_native_band(const mygames_kvm_u8 MYGAMES_KVM_FAR *source,
    mygames_kvm_u8 MYGAMES_KVM_FAR *pixels,mygames_kvm_u16 stride,mygames_kvm_u16 rows,
    const mygames_kvm_u16 MYGAMES_KVM_FAR *plan);
void mysmb_dos16_pack_planar_row(const mygames_kvm_u8 MYGAMES_KVM_FAR *source,
    mygames_kvm_u8 MYGAMES_KVM_FAR *pixels,mygames_kvm_u16 stride);
/* Validated1..16rows and IO-owned offsets;source/output/plan are disjoint. */
void mysmb_dos16_pack_planar_band(const mygames_kvm_u8 MYGAMES_KVM_FAR *source,
    mygames_kvm_u8 MYGAMES_KVM_FAR *pixels,mygames_kvm_u16 stride,mygames_kvm_u16 rows,
    const mygames_kvm_u16 MYGAMES_KVM_FAR *plan);
#endif
