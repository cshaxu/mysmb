#ifndef MYSMB_PLATFORM_DOS16_COMPACT_VGA_LAYOUT_H
#define MYSMB_PLATFORM_DOS16_COMPACT_VGA_LAYOUT_H

#include "kvm/types.h"

/* Four unchained VGA planes each have a 64KiB address window.  One 512x240
 * background period plus two 264x240 pages leaves 3136 bytes per plane. */
enum {
    MYSMB_DOS16_COMPACT_CACHE_WIDTH=512U,
    MYSMB_DOS16_COMPACT_CACHE_HEIGHT=240U,
    MYSMB_DOS16_COMPACT_CACHE_STRIDE=128U,
    MYSMB_DOS16_COMPACT_CACHE_BYTES=30720U,
    MYSMB_DOS16_COMPACT_PAGE_WIDTH=264U,
    MYSMB_DOS16_COMPACT_PAGE_HEIGHT=240U,
    MYSMB_DOS16_COMPACT_PAGE_STRIDE=66U,
    MYSMB_DOS16_COMPACT_PAGE_BYTES=15840U,
    MYSMB_DOS16_COMPACT_PAGE_A=MYSMB_DOS16_COMPACT_CACHE_BYTES,
    MYSMB_DOS16_COMPACT_PAGE_B=MYSMB_DOS16_COMPACT_CACHE_BYTES+
        MYSMB_DOS16_COMPACT_PAGE_BYTES,
    MYSMB_DOS16_COMPACT_TOTAL_BYTES=MYSMB_DOS16_COMPACT_CACHE_BYTES+
        MYSMB_DOS16_COMPACT_PAGE_BYTES+MYSMB_DOS16_COMPACT_PAGE_BYTES
};

/* Converts a cache pixel to its physical VGA plane and per-plane offset. */
int mysmb_dos16_compact_cache_address(mygames_kvm_u16 x,mygames_kvm_u16 y,
    mygames_kvm_u8 *plane,mygames_kvm_u16 *offset);

/* Converts a pixel in page 0 or 1, including its panning margin. */
int mysmb_dos16_compact_page_address(mygames_kvm_u8 page,mygames_kvm_u16 x,
    mygames_kvm_u16 y,mygames_kvm_u8 *plane,mygames_kvm_u16 *offset);

/* Returns the source byte span for one output row.  The row is deliberately
 * byte-aligned and includes the one-byte panning tail.  If it crosses the
 * 512-pixel cache seam, first_count describes the first physical span and
 * second_count the wrapped span.  It has no PPU or VGA-register policy. */
int mysmb_dos16_compact_viewport_row(mygames_kvm_u8 scene_page,mygames_kvm_u8 scroll_x,
    mygames_kvm_u8 scroll_y,mygames_kvm_u8 row,mygames_kvm_u16 *source,
    mygames_kvm_u8 *first_count,mygames_kvm_u8 *second_count);

#endif
