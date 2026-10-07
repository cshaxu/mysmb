#ifndef MYSMB_PPU_FRAME_H
#define MYSMB_PPU_FRAME_H

#include "ppu/state.h"
#include "io/video.h"
#include "io/palette_pairs.h"
#include "io/palette_expand.h"

enum {
    /* Source NMI holds scroll at zero until the sprite-0 split. */
    MYSMB_PPU_STATUS_BAR_HEIGHT = 32,
    MYSMB_PPU_FRAME_WIDTH = MYSMB_IO_VIDEO_WIDTH,
    MYSMB_PPU_FRAME_HEIGHT = MYSMB_IO_VIDEO_HEIGHT
};

#define MYSMB_PPU_FRAME_FAR MYSMB_IO_FAR

#define MYSMB_PPU_CHR_DECODED_BYTES 8192U
#define MYSMB_PPU_BACKGROUND_BYTES 63488U
#define MYSMB_PPU_BACKGROUND_SECOND_BYTES 61440U
struct mysmb_ppu_frame;
struct mysmb_ppu_frame_view;
/* Caller-owned packed two-bit indices,four pixels per byte.
 * Each tile row uses two bytes;CHR is immutable until rebind/reset. */
struct mysmb_ppu_frame_workspace {
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *decoded;
    const mysmb_io_u8 *chr;
    mysmb_io_u16 chr_size;
    mysmb_io_u8 valid;
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *bg;
    /* Non-null selects two byte-slot surfaces;null retains packed fallback. */
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *bg_second;
    const mysmb_io_u8 *bg_chr;
    mysmb_io_u16 bg_size;
    mysmb_io_u8 bg_valid,bg_pattern;
    /* Cumulative rebuilt-tile count; diagnostic only, never a cache key. */
    unsigned long bg_tiles;
    mysmb_io_palette_expand expand;
    void *expand_context;
    mysmb_io_nibble_expander nibble_expand;
};
void mysmb_ppu_frame_workspace_bind(struct mysmb_ppu_frame_workspace *workspace,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *decoded);

/* Portable expansion is the default,including an allocation-free lookup path.
 * Null restores that service; host overrides are only acceleration capabilities.
 * A rejected host span is completed by the same portable implementation. */
void mysmb_ppu_frame_expansion_bind(struct mysmb_ppu_frame_workspace *workspace,
    mysmb_io_palette_expand expand,void *context);
void mysmb_ppu_frame_nibble_bind(struct mysmb_ppu_frame_workspace *workspace,
    mysmb_io_nibble_expander expand);
/* Slot output and normalized table reconstruct the canonical master pixels. */
void mysmb_ppu_frame_palette(const struct mysmb_ppu_state *state,
    mysmb_io_u8 MYSMB_IO_FAR *palette);
void mysmb_ppu_frame_build_slots_cached(const struct mysmb_ppu_state *state,
    struct mysmb_ppu_frame *frame,struct mysmb_ppu_frame_workspace *workspace);
int mysmb_ppu_frame_slot_rows(const struct mysmb_ppu_frame_view *view,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 capacity,
    mysmb_io_u16 first,mysmb_io_u16 rows);

struct mysmb_ppu_frame {
#ifdef MYSMB_DOS16_TARGET
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *pixels;
#else
    mysmb_io_u8 pixels[MYSMB_PPU_FRAME_WIDTH * MYSMB_PPU_FRAME_HEIGHT];
#endif
};
#ifdef MYSMB_DOS16_TARGET
void mysmb_ppu_frame_bind_pixels(struct mysmb_ppu_frame *frame,
                                 mysmb_io_u8 MYSMB_PPU_FRAME_FAR *pixels);
#endif

/* Borrowed background storage:2048 source bytes followed by two 30720-byte
 * packed palette-slot surfaces. Rebind invalidates; no allocation is hidden.
 * CHR bytes remain immutable until workspace rebind, as for decoded storage. */
void mysmb_ppu_frame_background_bind(struct mysmb_ppu_frame_workspace *workspace,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *storage,mysmb_io_u16 capacity);
/* First:2048snapshot+61440slots;second:61440slots. Both borrowed and segment
 * bounded. Rebind invalidates derived data;null second selects packed first. */
void mysmb_ppu_frame_background_byte_bind(struct mysmb_ppu_frame_workspace *workspace,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *first,mysmb_io_u16 first_capacity,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *second,mysmb_io_u16 second_capacity);

/* One synchronous presentation borrows an immutable source and workspace.
 * Do not mutate/rebind either between begin and end; no view escapes the call.
 * Standalone builders prepare independently and retain their old contract. */
struct mysmb_ppu_frame_view {
    const struct mysmb_ppu_state *state;
    struct mysmb_ppu_frame_workspace *workspace;
    mysmb_io_u8 active;
    mysmb_io_u8 sprite_range[2];
};
void mysmb_ppu_frame_begin(const struct mysmb_ppu_state *state,
    struct mysmb_ppu_frame_workspace *workspace,struct mysmb_ppu_frame_view *view);
void mysmb_ppu_frame_end(struct mysmb_ppu_frame_view *view);
int mysmb_ppu_frame_rows(const struct mysmb_ppu_frame_view *view,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *pixels,mysmb_io_u16 capacity,
    mysmb_io_u16 first,mysmb_io_u16 rows);

/* Composes the source PPU-visible state and embedded CHR into one frame.  This
 * is a read-only PPU projection:all backends receive the same pixel result. */
void mysmb_ppu_frame_build(const struct mysmb_ppu_state *state,
                           struct mysmb_ppu_frame *frame);

void mysmb_ppu_frame_build_cached(const struct mysmb_ppu_state *state,
    struct mysmb_ppu_frame *frame,struct mysmb_ppu_frame_workspace *workspace);

/* Absolute logical rows,packed from output offset zero. Invalid requests leave
 * output/cache untouched;capacity is bytes within one caller-owned segment. */
int mysmb_ppu_frame_build_rows_cached(const struct mysmb_ppu_state *state,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *pixels,mysmb_io_u16 capacity,
    mysmb_io_u16 first,mysmb_io_u16 rows,struct mysmb_ppu_frame_workspace *workspace);

#endif
