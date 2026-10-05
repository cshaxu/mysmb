#include "platform/vga/vga_frame.h"
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
    mysmb_io_u16 plane,row,column,source_y,vertical_phase,source_x,phase;
    const mysmb_io_u8 MYSMB_IO_FAR *in;
    mysmb_io_u8 MYSMB_VGA_FAR *out;
    /* Stretch the complete256x240 source to320x400 without downsampling.
     * VGA scanout doubles horizontal dots to640x400;there are no margins.
     * Each far page holds one plane,80bytes per row,below64KB. */
    for(plane=0U;plane<4U;++plane) {
        source_y=0U;vertical_phase=0U;
        for(row=0U;row<400U;++row) {
            in=source->pixels+source_y*256U;
            out=frame->pages[plane]+row*80U;
            source_x=(mysmb_io_u16)(plane*4U/5U);
            phase=(mysmb_io_u16)(plane*4U%5U);
            for(column=0U;column<80U;++column) {
                *out++=(mysmb_io_u8)(in[source_x]&63U);
                source_x+=3U;
                if(++phase==5U) { phase=0U;++source_x; }
            }
            vertical_phase+=3U;
            if(vertical_phase>=5U) { vertical_phase-=5U;++source_y; }
        }
    }
}
