#ifndef MYSMB_DOS16_PALETTE_EXPAND_H
#define MYSMB_DOS16_PALETTE_EXPAND_H
#include "io/palette_pairs.h"
int mysmb_dos16_palette_expand(void *context,
    const mysmb_io_u8 MYSMB_IO_FAR *packed,mysmb_io_u8 MYSMB_IO_FAR *pixels,
    mysmb_io_u16 count,const mysmb_io_u8 MYSMB_IO_FAR *palette);
#endif
