#ifndef MYSMB_TEXT_LAYOUT_H
#define MYSMB_TEXT_LAYOUT_H
#include "io/video.h"
void mysmb_text_frame_initialize(struct mysmb_io_text_frame MYGAMES_KVM_FAR *frame,
    mygames_kvm_u8 sky,mygames_kvm_u16 rows,const mygames_kvm_u8 *palette);
mygames_kvm_u8 mysmb_text_color(const struct mysmb_io_text_frame MYGAMES_KVM_FAR *frame,
    mygames_kvm_u8 master);
mygames_kvm_u8 mysmb_text_contrast(const struct mysmb_io_text_frame MYGAMES_KVM_FAR *frame,
    mygames_kvm_u8 background);
#endif
