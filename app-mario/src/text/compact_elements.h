#ifndef MYSMB_TEXT_COMPACT_ELEMENTS_H
#define MYSMB_TEXT_COMPACT_ELEMENTS_H
#include "text/elements.h"
void mysmb_text_compact_size(const struct mysmb_text_element *element,
    unsigned short *width,unsigned short *height);
int mysmb_text_compact_draw(const struct mysmb_text_element *element,
    const mysmb_io_u8 colors[3],struct mysmb_io_text_frame MYSMB_IO_FAR *frame,
    mysmb_text_cell_filter filter,const void MYSMB_IO_FAR *context);
#endif
