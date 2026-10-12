#ifndef MYSMB_TEXT_LAYOUT_H
#define MYSMB_TEXT_LAYOUT_H
#include "io/video.h"
void mysmb_text_frame_initialize(struct mysmb_io_text_frame MYSMB_IO_FAR *frame,
    mysmb_io_u8 sky,mysmb_io_u16 rows,const mysmb_io_u8 *palette);
mysmb_io_u8 mysmb_text_color(const struct mysmb_io_text_frame MYSMB_IO_FAR *frame,
    mysmb_io_u8 master);
mysmb_io_u8 mysmb_text_contrast(const struct mysmb_io_text_frame MYSMB_IO_FAR *frame,
    mysmb_io_u8 background);
#endif
