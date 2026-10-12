#ifndef MYSMB_IO_SCALE_H
#define MYSMB_IO_SCALE_H
#include "io/video.h"
/* Caller owns one destination row with at least width writable bytes. */
void mysmb_io_scale_row(const struct mysmb_io_video_frame *source,
    mysmb_io_u16 width, mysmb_io_u16 height, mysmb_io_u16 row,
    mysmb_io_u8 MYSMB_IO_FAR *destination);
#endif
