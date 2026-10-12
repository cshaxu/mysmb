#ifndef MYSMB_IO_PALETTE_PAIRS_H
#define MYSMB_IO_PALETTE_PAIRS_H
#include "io/types.h"
/* Packed low/high four-bit indices map to full eight-bit output colors. */
struct mysmb_io_palette_pairs {
    mysmb_io_u16 pairs[256];
    mysmb_io_u8 palette[16];
    mysmb_io_u8 valid;
};
void mysmb_io_palette_pairs_prepare(struct mysmb_io_palette_pairs *workspace,
    const mysmb_io_u8 MYSMB_IO_FAR *palette);
/* Return zero to select the caller's portable fallback. Even count<=256,
 * disjoint spans and count/2 input bytes are required by the caller. */
typedef int (*mysmb_io_palette_expand)(void *context,
    const mysmb_io_u8 MYSMB_IO_FAR *packed,mysmb_io_u8 MYSMB_IO_FAR *pixels,
    mysmb_io_u16 count,const mysmb_io_u8 MYSMB_IO_FAR *palette);
#endif
