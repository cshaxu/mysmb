#ifndef MYSMB_TEXT_LAYOUT_H
#define MYSMB_TEXT_LAYOUT_H
#include "kvm/video.h"
void mysmb_text_frame_initialize(struct mygames_kvm_text_frame MYGAMES_KVM_FAR *frame,
    mygames_kvm_u8 sky,mygames_kvm_u16 rows,const mygames_kvm_u8 *palette);
mygames_kvm_u8 mysmb_text_color(const struct mygames_kvm_text_frame MYGAMES_KVM_FAR *frame,
    mygames_kvm_u8 master);
mygames_kvm_u8 mysmb_text_contrast(const struct mygames_kvm_text_frame MYGAMES_KVM_FAR *frame,
    mygames_kvm_u8 background);
#endif
