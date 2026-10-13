#include "kvm/video.h"

static int span_valid(mygames_kvm_u16 width,mygames_kvm_u16 rows,
    mygames_kvm_u16 stride,mygames_kvm_u16 capacity)
{
    unsigned long end;
    if(!width || !rows || stride<width)return 0;
    end=(unsigned long)(rows-1U)*stride+width;
    return end<=capacity;
}
int mygames_kvm_video_valid(const struct mygames_kvm_video_frame *frame)
{
    return frame && frame->pixels && frame->palette &&
        frame->palette_count && frame->palette_count<=256U &&
        span_valid(frame->width,frame->height,frame->stride,frame->capacity);
}
int mygames_kvm_band_valid(const struct mygames_kvm_video_band *band,
    mygames_kvm_u16 height)
{
    return band && band->pixels && band->first<height &&
        band->rows<=height-band->first &&
        span_valid(band->width,band->rows,band->stride,band->capacity);
}
int mygames_kvm_text_valid(const struct mygames_kvm_text_frame MYGAMES_KVM_FAR *frame)
{
    return frame && frame->cells && frame->source_colors<=1U &&
        (!frame->source_colors || frame->colors) &&
        frame->capacity<=65535UL/sizeof(struct mygames_kvm_text_cell) &&
        span_valid(frame->columns,frame->rows,frame->stride,frame->capacity);
}
