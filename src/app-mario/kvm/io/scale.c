#include "io/scale.h"
void mysmb_io_scale_row(const struct mygames_kvm_video_frame *source,
    mygames_kvm_u16 width, mygames_kvm_u16 height, mygames_kvm_u16 row,
    mygames_kvm_u8 MYGAMES_KVM_FAR *destination)
{
    mygames_kvm_u16 column, source_x, source_y, source_offset;
    unsigned long remainder;
    if (width==0U || height==0U || row>=height) return;
    source_y=(mygames_kvm_u16)((unsigned long)row*MYGAMES_KVM_VIDEO_HEIGHT/height);
    source_offset=(mygames_kvm_u16)(source_y*MYGAMES_KVM_VIDEO_WIDTH);
    source_x=0U; remainder=0UL;
    for (column=0U;column<width;++column) {
        destination[column]=source->pixels[source_offset+source_x]&0x3fU;
        remainder+=MYGAMES_KVM_VIDEO_WIDTH;
        while (remainder>=width) { remainder-=width; ++source_x; }
    }
}
