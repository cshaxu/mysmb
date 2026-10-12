#ifndef MYSMB_IO_TEXT_GLYPH_H
#define MYSMB_IO_TEXT_GLYPH_H
#include "io/types.h"

/* Selected one-cell IDs coincide with DOS CP437 font slots. ASCII32..126
 * retains its identity. No locale,game state or font bitmap is stored here. */
#define MYSMB_IO_GLYPH_VERTICAL 0xb3U
#define MYSMB_IO_GLYPH_HORIZONTAL 0xc4U
#define MYSMB_IO_GLYPH_TOP_LEFT 0xdaU
#define MYSMB_IO_GLYPH_TOP_RIGHT 0xbfU
#define MYSMB_IO_GLYPH_BOTTOM_LEFT 0xc0U
#define MYSMB_IO_GLYPH_BOTTOM_RIGHT 0xd9U
#define MYSMB_IO_GLYPH_TEE_LEFT 0xc3U
#define MYSMB_IO_GLYPH_TEE_RIGHT 0xb4U
#define MYSMB_IO_GLYPH_TEE_TOP 0xc2U
#define MYSMB_IO_GLYPH_TEE_BOTTOM 0xc1U
#define MYSMB_IO_GLYPH_CROSS 0xc5U
#define MYSMB_IO_GLYPH_FULL 0xdbU
#define MYSMB_IO_GLYPH_LOWER 0xdcU
#define MYSMB_IO_GLYPH_UPPER 0xdfU
#define MYSMB_IO_GLYPH_LEFT 0xddU
#define MYSMB_IO_GLYPH_RIGHT 0xdeU

unsigned short mysmb_io_text_glyph_unicode(mysmb_io_u8 glyph);
mysmb_io_u8 mysmb_io_text_glyph_mirror(mysmb_io_u8 glyph);
mysmb_io_u8 mysmb_io_text_glyph_flip(mysmb_io_u8 glyph);
#endif
