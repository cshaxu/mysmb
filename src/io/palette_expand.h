#ifndef MYSMB_IO_PALETTE_EXPAND_H
#define MYSMB_IO_PALETTE_EXPAND_H
#include "io/palette_pairs.h"
/* Pair bytes are ordered low nibble then high nibble on every host. */
extern const mysmb_io_u8 MYSMB_IO_FAR mysmb_io_nibble_pairs[512];
typedef int (*mysmb_io_nibble_expander)(const mysmb_io_u8 MYSMB_IO_FAR *,
    mysmb_io_u8 MYSMB_IO_FAR *,mysmb_io_u16);
/* Lossless low/high nibble expansion,without interpreting a color palette. */
int mysmb_io_nibble_expand(const mysmb_io_u8 MYSMB_IO_FAR *packed,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 count);
/* Always available; a null context uses palette lookup without cached pairs.
 * Host overrides may reject a span; the shared caller retries this service. */
int mysmb_io_palette_expand_portable(void *context,
    const mysmb_io_u8 MYSMB_IO_FAR *packed,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 count,
    const mysmb_io_u8 MYSMB_IO_FAR *palette);
#endif
