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
#define MYSMB_PPU_BACKGROUND_DAMAGE_BYTES 240U
/* Two 32-by-30 nametables, one bit per background tile.  This is a neutral
 * cache-output descriptor, not a game-state or platform-memory interface. */
struct mysmb_ppu_background_damage {
    mysmb_io_u8 full;
    mysmb_io_u16 count;
    mysmb_io_u8 tiles[MYSMB_PPU_BACKGROUND_DAMAGE_BYTES];
};
/* Read-only scene viewport selected by the PPU's already-latched output.
 * Hosts may map it to a device surface but cannot derive camera policy from
 * game state. fixed_top is a composition requirement, not a host choice. */
struct mysmb_ppu_scene_viewport {
    mysmb_io_u8 background_enabled;
    mysmb_io_u8 fixed_top;
    /* Output page is a neutral presentation coordinate, never a PPU store. */
    mysmb_io_u8 scene_page;
    mysmb_io_u8 output_origin_x;
    mysmb_io_u8 output_origin_y;
};
struct mysmb_ppu_frame;
struct mysmb_ppu_frame_view;
/* A host may complete already-selected 256-slot background rows synchronously.
 * Source A then B form each row;both source spans advance 256 bytes per row.
 * Returning zero leaves the exact portable row path as the sole fallback. */
typedef int (*mysmb_ppu_slot_rows_copier)(const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *,
    const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *,mysmb_io_u8 MYSMB_PPU_FRAME_FAR *,
    mysmb_io_u16,mysmb_io_u16,mysmb_io_u16);
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
    mysmb_io_u8 bg_valid,bg_pattern,bg_visible;
    /* Cumulative rebuilt-tile count; diagnostic only, never a cache key. */
    unsigned long bg_tiles;
    /* Rebuilt-tile map for the most recent preparation.  It is valid only
     * while this borrowed workspace remains bound and unprepared again. */
    struct mysmb_ppu_background_damage bg_damage;
    mysmb_io_palette_expand expand;
    void *expand_context;
    mysmb_io_nibble_expander nibble_expand;
    mysmb_ppu_slot_rows_copier slot_rows_copy;
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
void mysmb_ppu_frame_slot_rows_bind(struct mysmb_ppu_frame_workspace *workspace,
    mysmb_ppu_slot_rows_copier copy);
/* Slot output and normalized table reconstruct the canonical master pixels. */
void mysmb_ppu_frame_palette(const struct mysmb_ppu_state *state,
    mysmb_io_u8 MYSMB_IO_FAR *palette);
void mysmb_ppu_frame_build_slots_cached(const struct mysmb_ppu_state *state,
    struct mysmb_ppu_frame *frame,struct mysmb_ppu_frame_workspace *workspace);
int mysmb_ppu_frame_slot_rows(const struct mysmb_ppu_frame_view *view,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 capacity,
    mysmb_io_u16 first,mysmb_io_u16 rows);
/* Selected background palette slots only. This is the same frame latched
 * scroll/split/mask projection as slot_rows, deliberately before OAM. */
int mysmb_ppu_frame_background_rows(const struct mysmb_ppu_frame_view *view,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 capacity,
    mysmb_io_u16 first,mysmb_io_u16 rows);
/* Copies a bounded screen-space background rectangle from the already-latched
 * PPU view. The caller cannot choose scroll, split, masking or nametable. */
int mysmb_ppu_frame_background_rect(const struct mysmb_ppu_frame_view *view,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 capacity,
    mysmb_io_u8 x,mysmb_io_u8 y,mysmb_io_u8 width,mysmb_io_u8 height);
/* The scrollable scene behind a fixed top region.  This is a PPU-selected
 * output surface, so a host can restore temporary fixed overlays without
 * reading its display memory or interpreting scroll policy. */
int mysmb_ppu_frame_scene_rows(const struct mysmb_ppu_frame_view *view,
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

/* Copies the neutral background-cache output map for a prepared view.  A
 * false result leaves output untouched and means no bound cache is available. */
int mysmb_ppu_frame_background_damage(const struct mysmb_ppu_frame_view *view,
    struct mysmb_ppu_background_damage *damage);
/* Copies one already-selected 8-by-8 nametable tile as palette-slot bytes.
 * This exposes only cache output;table,row,column are PPU coordinates and
 * cannot select game state, scroll, palette conversion or host memory. */
int mysmb_ppu_frame_background_tile_slots(const struct mysmb_ppu_frame_view *view,
    mysmb_io_u8 table,mysmb_io_u8 row,mysmb_io_u8 column,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *slots,mysmb_io_u16 capacity);
int mysmb_ppu_frame_scene_viewport(const struct mysmb_ppu_frame_view *view,
    struct mysmb_ppu_scene_viewport *viewport);
/* The PPU enumerates visible 8-by-8 sprite overlays in its existing
 * descending OAM order. slots holds 0xff for transparent, masked or
 * background-priority-suppressed pixels;the caller supplies this synchronous
 * 64-byte buffer and cannot select sprite/game/PPU policy. */
typedef int (*mysmb_ppu_sprite_tile_writer)(void *,mysmb_io_u8,mysmb_io_u8,
    mysmb_io_u8,const mysmb_io_u8 MYSMB_PPU_FRAME_FAR *);
int mysmb_ppu_frame_sprite_tiles(const struct mysmb_ppu_frame_view *view,
    mysmb_io_u8 MYSMB_PPU_FRAME_FAR *slots,mysmb_io_u16 capacity,
    mysmb_ppu_sprite_tile_writer writer,void *context);

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
