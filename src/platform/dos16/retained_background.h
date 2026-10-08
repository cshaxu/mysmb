#ifndef MYSMB_PLATFORM_DOS16_RETAINED_BACKGROUND_H
#define MYSMB_PLATFORM_DOS16_RETAINED_BACKGROUND_H

#include "io/types.h"

enum {
    MYSMB_DOS16_RETAINED_WIDTH=512U,
    MYSMB_DOS16_RETAINED_HEIGHT=480U,
    MYSMB_DOS16_RETAINED_STRIDE=128U,
    MYSMB_DOS16_RETAINED_PLANE_BYTES=61440U
};

/* Converts a physical 512-by-480 VGA-surface pixel to one planar byte.
 * It contains no PPU, game, palette, device-register or frame policy. */
int mysmb_dos16_retained_address(mysmb_io_u16 x,mysmb_io_u16 y,
    mysmb_io_u8 *plane,mysmb_io_u16 *offset);

/* Two PPU nametables occupy the 512-wide first period. The second period
 * repeats it at y+240 for a hardware-scrolled 240-row viewport. */
int mysmb_dos16_retained_tile_address(mysmb_io_u8 table,mysmb_io_u8 row,
    mysmb_io_u8 column,mysmb_io_u8 vertical_copy,mysmb_io_u8 *plane,
    mysmb_io_u16 *offset);

struct mysmb_ppu_frame_view;
/* The writer receives only PPU-selected tile slots and physical projection
 * coordinates. It owns the VGA write; this adapter cannot select pixels,
 * scroll, palette, HUD or sprites. One callback is issued per changed tile. */
typedef int (*mysmb_dos16_retained_tile_writer)(void *,mysmb_io_u8,mysmb_io_u8,
    mysmb_io_u8,const mysmb_io_u8 MYSMB_IO_FAR *);
int mysmb_dos16_retained_background_apply(const struct mysmb_ppu_frame_view *view,
    mysmb_dos16_retained_tile_writer writer,void *context);

/* Same selected-tile stream, ordered by physical plane.  This lets the VGA
 * adapter select each plane once instead of doing a sequencer-port round trip
 * for every changed tile.  The PPU still supplies every slot byte. */
typedef int (*mysmb_dos16_retained_plane_tile_writer)(void *,mysmb_io_u8,
    mysmb_io_u8,mysmb_io_u8,mysmb_io_u8,
    const mysmb_io_u8 MYSMB_IO_FAR *);
int mysmb_dos16_retained_background_apply_planes(const struct mysmb_ppu_frame_view *view,
    mysmb_dos16_retained_plane_tile_writer writer,void *context);

#endif
