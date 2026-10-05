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
    mysmb_io_u16 page,row,group,source_y,phase;
    const mysmb_io_u8 MYSMB_IO_FAR *in;
    mysmb_io_u8 MYSMB_VGA_FAR *out;
    /* Fixed nearest-neighbor ratio:four source columns become five output
     * columns;five output rows consume six source rows. No division or32-bit
     * accumulator in the pixel loop. Generic IO scaling remains independent. */
    source_y=phase=0U;
    for(page=0U;page<4U;++page)for(row=0U;row<50U;++row) {
        in=source->pixels+source_y*256U;
        out=frame->pages[page]+row*320U;
        for(group=0U;group<64U;++group) {
            out[0]=out[1]=(mysmb_io_u8)(in[0]&63U);
            out[2]=(mysmb_io_u8)(in[1]&63U);
            out[3]=(mysmb_io_u8)(in[2]&63U);
            out[4]=(mysmb_io_u8)(in[3]&63U);
            in+=4;out+=5;
        }
        ++source_y;
        if(++phase==5U){++source_y;phase=0U;}
    }
}
