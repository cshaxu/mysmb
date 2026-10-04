#ifndef MYSMB_IO_COLOR_H
#define MYSMB_IO_COLOR_H

#include "io/types.h"

/* Stable presentation palette; indexed game pixels retain all six bits. */
unsigned long mysmb_io_color_rgb(mysmb_io_u8 index);
/* Canonical RGB for the neutral sixteen-color text attributes. */
unsigned long mysmb_io_color_text_rgb(mysmb_io_u8 index);
/* Color reduction only; never character selection or pixel sampling. */
mysmb_io_u8 mysmb_io_color_text16(mysmb_io_u8 index);

#endif
