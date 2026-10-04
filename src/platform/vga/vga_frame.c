#include "platform/vga/vga_frame.h"
#include "io/scale.h"
void mysmb_vga_frame_initialize(struct mysmb_vga_frame *frame,
    mysmb_io_u8 MYSMB_VGA_FAR *p0, mysmb_io_u8 MYSMB_VGA_FAR *p1,
    mysmb_io_u8 MYSMB_VGA_FAR *p2, mysmb_io_u8 MYSMB_VGA_FAR *p3)
{
    frame->pages[0]=p0; frame->pages[1]=p1;
    frame->pages[2]=p2; frame->pages[3]=p3;
}
void mysmb_vga_frame_build(const struct mysmb_io_video_frame *source,
                           struct mysmb_vga_frame *frame)
{
    mysmb_io_u16 row;
    for (row=0U; row<MYSMB_VGA_HEIGHT; ++row)
        mysmb_io_scale_row(source,MYSMB_VGA_WIDTH,MYSMB_VGA_HEIGHT,row,
            frame->pages[row/50U]+(row%50U)*MYSMB_VGA_WIDTH);
}
