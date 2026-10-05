#include "platform/vga/vga_frame.h"
#include <string.h>
void mysmb_vga_frame_initialize(struct mysmb_vga_frame *frame,
    mysmb_io_u8 MYSMB_VGA_FAR *p0, mysmb_io_u8 MYSMB_VGA_FAR *p1,
    mysmb_io_u8 MYSMB_VGA_FAR *p2, mysmb_io_u8 MYSMB_VGA_FAR *p3)
{
    frame->pages[0]=p0; frame->pages[1]=p1;
    frame->pages[2]=p2; frame->pages[3]=p3;
}
void mysmb_vga_frame_build_rows(const struct mysmb_io_video_frame *source,
    mysmb_io_u16 plane,mysmb_io_u16 first,mysmb_io_u16 rows,
    mysmb_io_u8 MYSMB_VGA_FAR *pixels)
{
    mysmb_io_u16 row,column,source_y,vertical_phase,source_x,phase,previous_y=240U;
    const mysmb_io_u8 MYSMB_IO_FAR *in;
    mysmb_io_u8 MYSMB_VGA_FAR *out;
    if(source==0 || source->pixels==0 || pixels==0 || plane>=4U || first>=400U || rows>400U-first)return;
    /* Exact full-screen mapping;each repeated source row reuses its output. */
    source_y=(mysmb_io_u16)(first*3U/5U);
    vertical_phase=(mysmb_io_u16)(first*3U%5U);
    for(row=0U;row<rows;++row) {
        out=pixels+row*80U;
        if(source_y==previous_y)memcpy(out,out-80U,80U);
        else {
            in=source->pixels+source_y*256U;
            source_x=(mysmb_io_u16)(plane*4U/5U);phase=(mysmb_io_u16)(plane*4U%5U);
            for(column=0U;column<80U;++column) {
                *out++=(mysmb_io_u8)(in[source_x]&63U);
                source_x+=3U;
                if(++phase==5U){phase=0U;++source_x;}
            }
        }
        previous_y=source_y;
        vertical_phase+=3U;
        if(vertical_phase>=5U){vertical_phase-=5U;++source_y;}
    }
}
void mysmb_vga_frame_build(const struct mysmb_io_video_frame *source,
    struct mysmb_vga_frame *frame)
{
    mysmb_io_u16 plane;
    for(plane=0U;plane<4U;++plane)
        mysmb_vga_frame_build_rows(source,plane,0U,400U,frame->pages[plane]);
}
