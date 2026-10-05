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
    mysmb_io_u16 row,column,source_y,vertical_phase,previous_y=240U;
    static const mysmb_io_u8 offsets[4][5]={{0U,3U,6U,9U,12U},
        {0U,4U,7U,10U,13U},{1U,4U,8U,11U,14U},{2U,5U,8U,12U,15U}};
    mysmb_io_u8 index0,index1,index2,index3,index4;
    const mysmb_io_u8 MYSMB_IO_FAR *in;
    mysmb_io_u8 MYSMB_VGA_FAR *out;
    if(source==0 || source->pixels==0 || pixels==0 || plane>=4U || first>=400U || rows>400U-first)return;
    /* floor((4*column+plane)*4/5) repeats every five outputs/16 inputs. */
    index0=offsets[plane][0];index1=offsets[plane][1];index2=offsets[plane][2];
    index3=offsets[plane][3];index4=offsets[plane][4];
    /* Exact full-screen mapping;each repeated source row reuses its output. */
    source_y=(mysmb_io_u16)(first*3U/5U);
    vertical_phase=(mysmb_io_u16)(first*3U%5U);
    for(row=0U;row<rows;++row) {
        out=pixels+row*80U;
        if(source_y==previous_y)memcpy(out,out-80U,80U);
        else {
            in=source->pixels+source_y*256U;
            for(column=0U;column<16U;++column) {
                out[0]=(mysmb_io_u8)(in[index0]&63U);
                out[1]=(mysmb_io_u8)(in[index1]&63U);
                out[2]=(mysmb_io_u8)(in[index2]&63U);
                out[3]=(mysmb_io_u8)(in[index3]&63U);
                out[4]=(mysmb_io_u8)(in[index4]&63U);
                out+=5U;in+=16U;
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
