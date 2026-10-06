#ifndef MYSMB_DOS16_PLANAR_ROW_H
#define MYSMB_DOS16_PLANAR_ROW_H
#include "io/planar_frame.h"
void mysmb_dos16_pack_planar_row(const mysmb_io_u8 MYSMB_IO_FAR *source,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 stride);
#endif
