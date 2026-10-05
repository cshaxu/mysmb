#include "platform/vga/vga_frame.h"
static mysmb_io_u8 pixels[MYSMB_IO_VIDEO_PIXELS];
static mysmb_io_u8 pages[4][MYSMB_VGA_PAGE_SIZE+2];
int main(void)
{
    struct mysmb_io_video_frame source;
    struct mysmb_vga_frame frame;
    unsigned long i, offset, x, y, sx, sy;
    for (i=0UL;i<MYSMB_IO_VIDEO_PIXELS;++i) pixels[i]=(mysmb_io_u8)((i*7UL+i/256UL)&255UL);
    for (i=0UL;i<4UL;++i) { pages[i][0]=0xa5U; pages[i][MYSMB_VGA_PAGE_SIZE+1]=0x5aU; }
    source.pixels=pixels;
    mysmb_vga_frame_initialize(&frame,pages[0]+1,pages[1]+1,pages[2]+1,pages[3]+1);
    mysmb_vga_frame_build(&source,&frame);
    for(y=0UL;y<400UL;++y)for(x=0UL;x<320UL;++x) {
        offset=y*80UL+x/4UL;
        sx=x*4UL/5UL;sy=y*3UL/5UL;
        if(frame.pages[x%4UL][offset]!=(pixels[sy*256UL+sx]&63U))return 1;
    }
    for (i=0UL;i<4UL;++i)
        if (pages[i][0]!=0xa5U || pages[i][MYSMB_VGA_PAGE_SIZE+1]!=0x5aU) return 2;
    return 0;
}
