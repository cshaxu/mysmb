#ifndef MYSMB_IO_PLANAR_FRAME_H
#define MYSMB_IO_PLANAR_FRAME_H
#include "io/video.h"
#define MYSMB_VGA_FAR MYSMB_IO_FAR
enum { MYSMB_VGA_WIDTH=320, MYSMB_VGA_HEIGHT=400, MYSMB_VGA_PAGE_COUNT=4, MYSMB_VGA_PAGE_SIZE=32000, MYSMB_VGA_BATCH_ROWS=16, MYSMB_VGA_BATCH_SIZE=1280 };
enum { MYSMB_PLANAR_NATIVE_WIDTH=256, MYSMB_PLANAR_NATIVE_HEIGHT=240,
    MYSMB_PLANAR_NATIVE_PITCH=64, MYSMB_PLANAR_NATIVE_BAND_BYTES=4096 };
struct mysmb_vga_frame { mysmb_io_u8 MYSMB_VGA_FAR *pages[4]; };
void mysmb_vga_frame_initialize(struct mysmb_vga_frame *frame,
    mysmb_io_u8 MYSMB_VGA_FAR *p0, mysmb_io_u8 MYSMB_VGA_FAR *p1,
    mysmb_io_u8 MYSMB_VGA_FAR *p2, mysmb_io_u8 MYSMB_VGA_FAR *p3);
void mysmb_vga_frame_build(const struct mysmb_io_video_frame *source,
                           struct mysmb_vga_frame *frame);
/* Caller supplies rows*80bytes in one far segment;no prior batch is required. */
void mysmb_vga_frame_build_rows(const struct mysmb_io_video_frame *source,
    mysmb_io_u16 plane,mysmb_io_u16 first,mysmb_io_u16 rows,
    mysmb_io_u8 MYSMB_VGA_FAR *pixels);
/* Reject a band that does not cover every required logical source row. */
int mysmb_vga_frame_build_band(const struct mysmb_io_video_band *source,
    mysmb_io_u16 plane,mysmb_io_u16 first,mysmb_io_u16 rows,
    mysmb_io_u8 MYSMB_VGA_FAR *pixels);
/* Packs four plane bands,each rows*80bytes. Caller supplies rows*320bytes;
 * source/output ranges must not overlap. Consume source before its next rebuild. */
int mysmb_vga_frame_build_planes(const struct mysmb_io_video_band *source,
    mysmb_io_u16 first,mysmb_io_u16 rows,mysmb_io_u8 MYSMB_IO_FAR *out,
    mysmb_io_u16 capacity);
/* Optional synchronous row encoder receives exactly256source bytes and four
 * disjoint80-byte output spans separated by stride. It restores caller state.
 * Null selects the portable owner;callbacks may not change source or metadata. */
typedef void (*mysmb_io_planar_row_packer)(const mysmb_io_u8 MYSMB_IO_FAR *,
    mysmb_io_u8 MYSMB_IO_FAR *,mysmb_io_u16);
/* A synchronous band encoder borrows rows<=16 offsets. Each word is a
 * source byte offset,or 0xffff to copy the preceding destination row.
 * It receives four rows*80-byte planes and must preserve source/plan.
 * Null uses the same portable layout implementation. */
typedef void (*mysmb_io_planar_band_packer)(const mysmb_io_u8 MYSMB_IO_FAR *,
    mysmb_io_u8 MYSMB_IO_FAR *,mysmb_io_u16,mysmb_io_u16,
    const mysmb_io_u16 MYSMB_IO_FAR *);
int mysmb_io_planar_build_band(const struct mysmb_io_video_band *source,
    mysmb_io_u16 first,mysmb_io_u16 rows,mysmb_io_u8 MYSMB_IO_FAR *out,
    mysmb_io_u16 capacity,mysmb_io_planar_band_packer packer);
int mysmb_io_planar_build_planes(const struct mysmb_io_video_band *source,
    mysmb_io_u16 first,mysmb_io_u16 rows,mysmb_io_u8 MYSMB_IO_FAR *out,
    mysmb_io_u16 capacity,mysmb_io_planar_row_packer packer);
/* Lossless native deinterleave;four rows*64-byte planes,identity source rows.
 * The optional synchronous encoder receives rows*64 stride and byte offsets.
 * No repeated-row sentinel is supplied. Source/output must not overlap. */
int mysmb_io_planar_native_band(const struct mysmb_io_video_band *source,
    mysmb_io_u8 MYSMB_IO_FAR *out,mysmb_io_u16 capacity,
    mysmb_io_planar_band_packer packer);
#endif
