#ifndef MYSMB_DOS16_NIBBLE_EXPAND_H
#define MYSMB_DOS16_NIBBLE_EXPAND_H
#include "io/palette_expand.h"
int mysmb_dos16_nibble_expand(const mysmb_io_u8 MYSMB_IO_FAR *packed,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 count);
#endif
