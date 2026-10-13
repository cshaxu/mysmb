#ifndef MYSMB_IO_SCALE_H
#define MYSMB_IO_SCALE_H
#include "io/video.h"
/* Caller owns one destination row with at least width writable bytes. */
void mysmb_io_scale_row(const struct mygames_kvm_video_frame *source,
    mygames_kvm_u16 width, mygames_kvm_u16 height, mygames_kvm_u16 row,
    mygames_kvm_u8 MYGAMES_KVM_FAR *destination);
#endif
