#include "io/planar_frame.h"
#include <stdio.h>
#include <string.h>
static mysmb_io_u8 pixels[MYSMB_IO_VIDEO_PIXELS];
static mysmb_io_u8 pages[4][MYSMB_VGA_PAGE_SIZE+2];
static mysmb_io_u8 scratch[MYSMB_VGA_PAGE_SIZE+2];
static unsigned char packed[5120+32],old[1280+32];
static unsigned char encoded[5120+32];
static unsigned short band_calls;
static void row_encoder(const mysmb_io_u8 *source,mysmb_io_u8 *out,
    mysmb_io_u16 stride)
{
 unsigned short p,x;
 for(p=0U;p<4U;++p)for(x=0U;x<80U;++x)
  out[p*stride+x]=(mysmb_io_u8)(source[(4U*x+p)*4U/5U]&63U);
}
static void band_encoder(const mysmb_io_u8 *source,mysmb_io_u8 *out,
    mysmb_io_u16 stride,mysmb_io_u16 rows,const mysmb_io_u16 *plan)
{
 unsigned short row,p;
 ++band_calls;
 for(row=0U;row<rows;++row){
  if(plan[row]==0xffffU){
   for(p=0U;p<4U;++p)
    memcpy(out+p*stride+row*80U,out+p*stride+(row-1U)*80U,80U);
  }else row_encoder(source+plan[row],out+row*80U,stride);
 }
}
static void native_encoder(const mysmb_io_u8 *source,mysmb_io_u8 *out,
    mysmb_io_u16 stride,mysmb_io_u16 rows,const mysmb_io_u16 *plan)
{
 unsigned short row,p,x;
 ++band_calls;
 for(row=0U;row<rows;++row)for(p=0U;p<4U;++p)for(x=0U;x<64U;++x)
  out[p*stride+row*64U+x]=(mysmb_io_u8)(source[plan[row]+x*4U+p]&63U);
}
static int native_planes(void)
{
 struct mysmb_io_video_band band;unsigned short first,rows,p,x,y,i;
 unsigned long count=0UL;
 for(rows=1U;rows<=16U;++rows)for(first=0U;first+rows<=240U;++first){
  band.first=first;band.rows=rows;band.pixels=pixels+first*256U;
  memset(packed,0xa5,sizeof(packed));memset(encoded,0xa5,sizeof(encoded));
  band_calls=0;
  if(!mysmb_io_planar_native_band(&band,packed+16,rows*256U,0) ||
   !mysmb_io_planar_native_band(&band,encoded+16,rows*256U,native_encoder) ||
   band_calls!=1 || memcmp(packed,encoded,sizeof(packed)))return 20;
  for(p=0U;p<4U;++p)for(y=0U;y<rows;++y)for(x=0U;x<64U;++x){
   if(packed[16U+(p*rows+y)*64U+x]!=(pixels[(first+y)*256U+x*4U+p]&63U))return 21;
   ++count;
  }
  for(i=0U;i<16U;++i)if(packed[i]!=0xa5 || packed[16U+rows*256U+i]!=0xa5)return 22;
 }
 band.first=0;band.rows=16;band.pixels=pixels;band_calls=0;
 if(mysmb_io_planar_native_band(&band,packed,4095,native_encoder))return 23;
 band.rows=17;if(mysmb_io_planar_native_band(&band,packed,5120,native_encoder))return 24;
 band.rows=1;band.first=240;if(mysmb_io_planar_native_band(&band,packed,5120,native_encoder))return 25;
 band.first=239;band.rows=2;if(mysmb_io_planar_native_band(&band,packed,5120,native_encoder))return 26;
 band.rows=0;if(mysmb_io_planar_native_band(&band,packed,5120,native_encoder) || band_calls)return 27;
 printf("native256x240 allBands1to16 comparedBytes=%lu guards=1 invalidRejected=1\n",count);
 return 0;
}
static int four_planes(void)
{
 struct mysmb_io_video_band band;unsigned short first,rows,p,x,y,sy,sx,i;
 unsigned long compared=0UL;
 for(i=0U;i<61440U;++i)pixels[i]=(unsigned char)((i*13U+i/256U)&255U);
 for(rows=1U;rows<=16U;++rows)for(first=0U;first+rows<=400U;++first){
  band.first=(unsigned short)(first*3U/5U);
  band.rows=(unsigned short)((first+rows-1U)*3U/5U-band.first+1U);
  band.pixels=pixels+band.first*256U;
  memset(packed,0xa5,sizeof(packed));
  if(!mysmb_vga_frame_build_planes(&band,first,rows,packed+16,5120))return 1;
  memset(encoded,0xa5,sizeof(encoded));
  if(!mysmb_io_planar_build_planes(&band,first,rows,encoded+16,5120,row_encoder) ||
   memcmp(encoded,packed,sizeof(packed)))return 8;
  memset(encoded,0xa5,sizeof(encoded));band_calls=0U;
  if(!mysmb_io_planar_build_band(&band,first,rows,encoded+16,5120,band_encoder) ||
   band_calls!=1U || memcmp(encoded,packed,sizeof(packed)))return 9;
  memset(encoded,0xa5,sizeof(encoded));
  if(!mysmb_io_planar_build_band(&band,first,rows,encoded+16,5120,0) ||
   memcmp(encoded,packed,sizeof(packed)))return 10;
  for(p=0U;p<4U;++p){
   memset(old,0xa5,sizeof(old));if(!mysmb_vga_frame_build_band(&band,p,first,rows,old+16))return 2;
   if(memcmp(old+16,packed+16+p*rows*80U,rows*80U))return 3;
   for(y=0U;y<rows;++y)for(x=0U;x<80U;++x){
    sy=(unsigned short)((first+y)*3U/5U);sx=(unsigned short)((4U*x+p)*4U/5U);
    if(packed[16U+(p*rows+y)*80U+x]!=(pixels[sy*256U+sx]&63U))return 4;
    ++compared;
   }
  }
  for(i=0;i<16;++i)if(packed[i]!=0xa5 || packed[16U+rows*320U+i]!=0xa5)return 5;
 }
 memset(packed,0xa5,sizeof(packed));band.first=1;band.rows=1;band.pixels=pixels;
 if(mysmb_vga_frame_build_planes(&band,0,16,packed+16,5120)||mysmb_vga_frame_build_planes(&band,0,17,packed+16,5120))return 6;
 band.first=0;band.rows=10;
 if(mysmb_vga_frame_build_planes(&band,0,16,packed+16,5119))return 7;
 band_calls=0U;
 if(mysmb_io_planar_build_band(&band,0,16,packed+16,5119,band_encoder) ||
  mysmb_io_planar_build_band(&band,0,17,packed+16,5120,band_encoder) ||
  mysmb_io_planar_build_band(&band,400,1,packed+16,5120,band_encoder))return 11;
 band.first=1;
 if(mysmb_io_planar_build_band(&band,0,16,packed+16,5120,band_encoder))return 12;
 band.first=0;
 if(!mysmb_io_planar_build_band(&band,0,0,packed+16,5120,band_encoder) ||
  band_calls!=0U)return 13;
 for(i=0;i<sizeof(packed);++i)if(packed[i]!=0xa5)return 8;
 printf("allFirstRows1to16=1 comparedBytes=%lu guards=1 invalidRejected=1\n",compared);return 0;
}

int main(void)
{
    struct mysmb_io_video_frame source;
    struct mysmb_vga_frame frame;
    unsigned long i, offset, x, y, sx, sy,first,rows,batch;
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
    /* Arbitrary batch boundaries and partial final batches match the oracle. */
    for(batch=1UL;batch<=400UL;batch=batch==1UL?7UL:batch==7UL?16UL:batch==16UL?63UL:batch==63UL?400UL:400UL+1UL) {
        for(i=0UL;i<4UL;++i)for(first=0UL;first<400UL;first+=batch) {
            rows=400UL-first;if(rows>batch)rows=batch;
            scratch[0]=0xa5U;scratch[rows*80UL+1UL]=0x5aU;
            mysmb_vga_frame_build_rows(&source,(mysmb_io_u16)i,(mysmb_io_u16)first,(mysmb_io_u16)rows,scratch+1);
            for(offset=0UL;offset<rows*80UL;++offset)
                if(scratch[offset+1]!=pages[i][first*80UL+offset+1])return 3;
            if(scratch[0]!=0xa5U || scratch[rows*80UL+1]!=0x5aU)return 4;
        }
    }
    scratch[1]=0xa5U;
    mysmb_vga_frame_build_rows(&source,4U,0U,1U,scratch+1);
    mysmb_vga_frame_build_rows(&source,0U,399U,2U,scratch+1);
    if(scratch[1]!=0xa5U)return 5;
    if(four_planes())return 10;
    return native_planes();
}
