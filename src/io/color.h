#ifndef MYSMB_IO_COLOR_H
#define MYSMB_IO_COLOR_H

#include "io/types.h"

/* Stable presentation palette; indexed game pixels retain all six bits. */
unsigned long mysmb_io_color_rgb(mysmb_io_u8 index);
/* Canonical RGB for the neutral sixteen-color text attributes. */
unsigned long mysmb_io_color_text_rgb(mysmb_io_u8 index);
/* Device fallback for an arbitrary neutral RGB text palette. */
mysmb_io_u8 mysmb_io_color_text_nearest(unsigned long rgb);
/* Color reduction only; never character selection or pixel sampling. */
mysmb_io_u8 mysmb_io_color_text16(mysmb_io_u8 index);

/* Black/white ink chosen for a canonical text background. */
mysmb_io_u8 mysmb_io_color_text_contrast(mysmb_io_u8 background);

#endif
