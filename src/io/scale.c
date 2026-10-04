#include "io/scale.h"
void mysmb_io_scale_row(const struct mysmb_io_video_frame *source,
    mysmb_io_u16 width, mysmb_io_u16 height, mysmb_io_u16 row,
    mysmb_io_u8 MYSMB_IO_FAR *destination)
{
    mysmb_io_u16 column, source_x, source_y, source_offset;
    unsigned long remainder;
    if (width==0U || height==0U || row>=height) return;
    source_y=(mysmb_io_u16)((unsigned long)row*MYSMB_IO_VIDEO_HEIGHT/height);
    source_offset=(mysmb_io_u16)(source_y*MYSMB_IO_VIDEO_WIDTH);
    source_x=0U; remainder=0UL;
    for (column=0U;column<width;++column) {
        destination[column]=source->pixels[source_offset+source_x]&0x3fU;
        remainder+=MYSMB_IO_VIDEO_WIDTH;
        while (remainder>=width) { remainder-=width; ++source_x; }
    }
}
