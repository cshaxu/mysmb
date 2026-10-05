#ifndef MYSMB_PLATFORM_VGA_FRAME_H
#define MYSMB_PLATFORM_VGA_FRAME_H
#include "io/video.h"
#define MYSMB_VGA_FAR MYSMB_IO_FAR
enum { MYSMB_VGA_WIDTH=320, MYSMB_VGA_HEIGHT=400, MYSMB_VGA_PAGE_COUNT=4, MYSMB_VGA_PAGE_SIZE=32000 };
struct mysmb_vga_frame { mysmb_io_u8 MYSMB_VGA_FAR *pages[4]; };
void mysmb_vga_frame_initialize(struct mysmb_vga_frame *frame,
    mysmb_io_u8 MYSMB_VGA_FAR *p0, mysmb_io_u8 MYSMB_VGA_FAR *p1,
    mysmb_io_u8 MYSMB_VGA_FAR *p2, mysmb_io_u8 MYSMB_VGA_FAR *p3);
void mysmb_vga_frame_build(const struct mysmb_io_video_frame *source,
                           struct mysmb_vga_frame *frame);
#endif
