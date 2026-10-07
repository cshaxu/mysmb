#ifndef MYSMB_IO_VIDEO_H
#define MYSMB_IO_VIDEO_H

#include "io/types.h"

#define MYSMB_IO_VIDEO_WIDTH 256U
#define MYSMB_IO_VIDEO_HEIGHT 240U
#define MYSMB_IO_VIDEO_PIXELS 61440U

/* Borrowed row-major source color indices. The compositor owns pixels;
 * a presenter must consume the view before its next rebuild and cannot write
 * through it. No scale, palette reduction, HUD or object logic belongs here. */
struct mysmb_io_video_frame {
    const mysmb_io_u8 MYSMB_IO_FAR *pixels;
};

/* Synchronous read-only row producer. A returned view is valid only until the
 * next read_rows call or return from the present operation. No tick may advance
 * while the consumer borrows it. first/rows name logical256x240coordinates. */
struct mysmb_io_video_band {
    const mysmb_io_u8 MYSMB_IO_FAR *pixels;
    mysmb_io_u16 first,rows;
};
struct mysmb_io_video_source {
    void *context;
    int (*read_rows)(void *context,mysmb_io_u16 first,mysmb_io_u16 rows,
        struct mysmb_io_video_band *band);
};

#define MYSMB_IO_VIDEO_PALETTE_COLORS 32U
struct mysmb_io_palette_video_frame {
    const mysmb_io_u8 MYSMB_IO_FAR *pixels;
    const mysmb_io_u8 MYSMB_IO_FAR *master_colors;
};
/* Explicit slot-index view. Entries map slots to original master colors.
 * Both table and rows are immutable for the complete synchronous present. */
struct mysmb_io_palette_video_source {
    struct mysmb_io_video_source rows;
    const mysmb_io_u8 MYSMB_IO_FAR *master_colors;
};

/* Authored text output. Character IDs follow io/text_glyph.h;no quantizer. */
#define MYSMB_IO_TEXT_COLUMNS 80U
#define MYSMB_IO_TEXT_ROWS 50U
#define MYSMB_IO_TEXT_CELLS 4000U

struct mysmb_io_text_cell {
    mysmb_io_u8 character;
    mysmb_io_u8 foreground;
    mysmb_io_u8 background;
};

struct mysmb_io_text_frame {
    struct mysmb_io_text_cell cells[MYSMB_IO_TEXT_CELLS];
    /* Retained capacity supports both layouts;only selected rows are output.
     * Palette entries are neutral RGB,not host attributes or game state. */
    mysmb_io_u16 rows;
    mysmb_io_u8 source_colors;
    unsigned long colors[16];
    mysmb_io_u8 master_map[64];
};

#define MYSMB_IO_TEXT_FRAME_ROWS(f) ((f)->rows==25U?25U:50U)
#define MYSMB_IO_TEXT_FRAME_CELLS(f) (80U*MYSMB_IO_TEXT_FRAME_ROWS(f))

#endif
