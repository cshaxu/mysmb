#include "platform/vga/vga_frame.h"
#include <string.h>
void mysmb_vga_frame_initialize(struct mysmb_vga_frame *frame,
    mysmb_io_u8 MYSMB_VGA_FAR *p0, mysmb_io_u8 MYSMB_VGA_FAR *p1,
    mysmb_io_u8 MYSMB_VGA_FAR *p2, mysmb_io_u8 MYSMB_VGA_FAR *p3)
{
    frame->pages[0]=p0; frame->pages[1]=p1;
    frame->pages[2]=p2; frame->pages[3]=p3;
}
static void build_rows(const mysmb_io_u8 MYSMB_IO_FAR *source,
    mysmb_io_u16 source_first,
    mysmb_io_u16 plane,mysmb_io_u16 first,mysmb_io_u16 rows,
    mysmb_io_u8 MYSMB_VGA_FAR *pixels)
{
    mysmb_io_u16 row,column,source_y,vertical_phase,previous_y=240U;
    static const mysmb_io_u8 offsets[4][5]={{0U,3U,6U,9U,12U},
        {0U,4U,7U,10U,13U},{1U,4U,8U,11U,14U},{2U,5U,8U,12U,15U}};
    mysmb_io_u8 index0,index1,index2,index3,index4;
    const mysmb_io_u8 MYSMB_IO_FAR *in;
    mysmb_io_u8 MYSMB_VGA_FAR *out;
    if(source==0 || pixels==0 || plane>=4U || first>=400U || rows>400U-first)return;
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
            in=source+(source_y-source_first)*256U;
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
void mysmb_vga_frame_build_rows(const struct mysmb_io_video_frame *source,
    mysmb_io_u16 plane,mysmb_io_u16 first,mysmb_io_u16 rows,
    mysmb_io_u8 MYSMB_VGA_FAR *pixels)
{
    if(source)build_rows(source->pixels,0U,plane,first,rows,pixels);
}
int mysmb_vga_frame_build_band(const struct mysmb_io_video_band *source,
    mysmb_io_u16 plane,mysmb_io_u16 first,mysmb_io_u16 rows,
    mysmb_io_u8 MYSMB_VGA_FAR *pixels)
{
    mysmb_io_u16 low,high;
    if(source==0 || source->pixels==0 || pixels==0 || plane>=4U || first>=400U ||
        rows>400U-first || source->first>=240U || source->rows>240U-source->first)return 0;
    if(rows==0U)return 1;
    low=(mysmb_io_u16)(first*3U/5U);
    high=(mysmb_io_u16)((first+rows-1U)*3U/5U);
    if(low<source->first || high>=source->first+source->rows)return 0;
    build_rows(source->pixels,source->first,plane,first,rows,pixels);
    return 1;
}

void mysmb_vga_frame_build(const struct mysmb_io_video_frame *source,
    struct mysmb_vga_frame *frame)
{
    mysmb_io_u16 plane;
    for(plane=0U;plane<4U;++plane)
        mysmb_vga_frame_build_rows(source,plane,0U,400U,frame->pages[plane]);
}

/* One16-byte source group supplies all four exact plane index sequences. */
int mysmb_vga_frame_build_planes(const struct mysmb_io_video_band *source,
    mysmb_io_u16 first,mysmb_io_u16 rows,mysmb_io_u8 MYSMB_IO_FAR *out,
    mysmb_io_u16 capacity)
{
    mysmb_io_u16 row,group,p,sy,previous=240U,phase,low,high;
    mysmb_io_u8 input[16];
    const mysmb_io_u8 MYSMB_IO_FAR *in;
    mysmb_io_u8 MYSMB_IO_FAR *p0,*p1,*p2,*p3;
    if(!source || !source->pixels || !out || first>=400U || rows>MYSMB_VGA_BATCH_ROWS ||
        rows>400U-first || rows>capacity/320U || source->first>=240U ||
        source->rows>240U-source->first)return 0;
    if(rows==0U)return 1;
    low=(mysmb_io_u16)(first*3U/5U);high=(mysmb_io_u16)((first+rows-1U)*3U/5U);
    if(low<source->first || high>=source->first+source->rows)return 0;
    sy=low;phase=(mysmb_io_u16)(first*3U%5U);
    for(row=0U;row<rows;++row){
        if(sy==previous){
            for(p=0U;p<4U;++p)memcpy(out+(p*rows+row)*80U,out+(p*rows+row-1U)*80U,80U);
        }else{
            in=source->pixels+(sy-source->first)*256U;
            p0=out+row*80U;p1=out+(rows+row)*80U;
            p2=out+(rows*2U+row)*80U;p3=out+(rows*3U+row)*80U;
            for(group=0U;group<16U;++group){
                memcpy(input,in,16U);in+=16U;
                p0[0U]=(mysmb_io_u8)(input[0U]&63U);
                p0[1U]=(mysmb_io_u8)(input[3U]&63U);
                p0[2U]=(mysmb_io_u8)(input[6U]&63U);
                p0[3U]=(mysmb_io_u8)(input[9U]&63U);
                p0[4U]=(mysmb_io_u8)(input[12U]&63U);
                p1[0U]=(mysmb_io_u8)(input[0U]&63U);
                p1[1U]=(mysmb_io_u8)(input[4U]&63U);
                p1[2U]=(mysmb_io_u8)(input[7U]&63U);
                p1[3U]=(mysmb_io_u8)(input[10U]&63U);
                p1[4U]=(mysmb_io_u8)(input[13U]&63U);
                p2[0U]=(mysmb_io_u8)(input[1U]&63U);
                p2[1U]=(mysmb_io_u8)(input[4U]&63U);
                p2[2U]=(mysmb_io_u8)(input[8U]&63U);
                p2[3U]=(mysmb_io_u8)(input[11U]&63U);
                p2[4U]=(mysmb_io_u8)(input[14U]&63U);
                p3[0U]=(mysmb_io_u8)(input[2U]&63U);
                p3[1U]=(mysmb_io_u8)(input[5U]&63U);
                p3[2U]=(mysmb_io_u8)(input[8U]&63U);
                p3[3U]=(mysmb_io_u8)(input[12U]&63U);
                p3[4U]=(mysmb_io_u8)(input[15U]&63U);
                p0+=5U;p1+=5U;p2+=5U;p3+=5U;
            }
        }
        previous=sy;phase+=3U;if(phase>=5U){phase-=5U;++sy;}
    }
    return 1;
}
