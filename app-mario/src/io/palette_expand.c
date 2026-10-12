#include "io/palette_expand.h"
#include <string.h>
/* Fixed low/high nibble byte pairs,independent of palette and host endian. */
const mysmb_io_u8 MYSMB_IO_FAR mysmb_io_nibble_pairs[512]={
0,0,1,0,2,0,3,0,4,0,5,0,6,0,7,0,8,0,9,0,10,0,11,0,12,0,13,0,14,0,15,0,
0,1,1,1,2,1,3,1,4,1,5,1,6,1,7,1,8,1,9,1,10,1,11,1,12,1,13,1,14,1,15,1,
0,2,1,2,2,2,3,2,4,2,5,2,6,2,7,2,8,2,9,2,10,2,11,2,12,2,13,2,14,2,15,2,
0,3,1,3,2,3,3,3,4,3,5,3,6,3,7,3,8,3,9,3,10,3,11,3,12,3,13,3,14,3,15,3,
0,4,1,4,2,4,3,4,4,4,5,4,6,4,7,4,8,4,9,4,10,4,11,4,12,4,13,4,14,4,15,4,
0,5,1,5,2,5,3,5,4,5,5,5,6,5,7,5,8,5,9,5,10,5,11,5,12,5,13,5,14,5,15,5,
0,6,1,6,2,6,3,6,4,6,5,6,6,6,7,6,8,6,9,6,10,6,11,6,12,6,13,6,14,6,15,6,
0,7,1,7,2,7,3,7,4,7,5,7,6,7,7,7,8,7,9,7,10,7,11,7,12,7,13,7,14,7,15,7,
0,8,1,8,2,8,3,8,4,8,5,8,6,8,7,8,8,8,9,8,10,8,11,8,12,8,13,8,14,8,15,8,
0,9,1,9,2,9,3,9,4,9,5,9,6,9,7,9,8,9,9,9,10,9,11,9,12,9,13,9,14,9,15,9,
0,10,1,10,2,10,3,10,4,10,5,10,6,10,7,10,8,10,9,10,10,10,11,10,12,10,13,10,14,10,15,10,
0,11,1,11,2,11,3,11,4,11,5,11,6,11,7,11,8,11,9,11,10,11,11,11,12,11,13,11,14,11,15,11,
0,12,1,12,2,12,3,12,4,12,5,12,6,12,7,12,8,12,9,12,10,12,11,12,12,12,13,12,14,12,15,12,
0,13,1,13,2,13,3,13,4,13,5,13,6,13,7,13,8,13,9,13,10,13,11,13,12,13,13,13,14,13,15,13,
0,14,1,14,2,14,3,14,4,14,5,14,6,14,7,14,8,14,9,14,10,14,11,14,12,14,13,14,14,14,15,14,
0,15,1,15,2,15,3,15,4,15,5,15,6,15,7,15,8,15,9,15,10,15,11,15,12,15,13,15,14,15,15,15
};

int mysmb_io_nibble_expand(const mysmb_io_u8 MYSMB_IO_FAR *packed,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 count)
{
    mysmb_io_u16 i,bytes,group[2];mysmb_io_u8 value;
    if(!packed || !pixels || count>256U || (count&1U))return 0;
    bytes=(mysmb_io_u16)(count/2U);
    for(i=0U;i+4U<=bytes;i+=4U){
        memcpy(group,packed+i,4U);if(group[0]|group[1])break;
    }
    if(i+4U>bytes)while(i<bytes && !packed[i])++i;
    if(i==bytes){memset(pixels,0,count);return 1;}
    for(i=0U;i<bytes;++i){value=packed[i];
        memcpy(pixels+i*2U,mysmb_io_nibble_pairs+value*2U,2U); }
    return 1;
}
/* Neutral implementation of the same bounded span contract as host encoders. */
int mysmb_io_palette_expand_portable(void *context,
    const mysmb_io_u8 MYSMB_IO_FAR *packed,
    mysmb_io_u8 MYSMB_IO_FAR *pixels,mysmb_io_u16 count,
    const mysmb_io_u8 MYSMB_IO_FAR *palette)
{
    struct mysmb_io_palette_pairs *w;
    mysmb_io_u16 i,pair,bytes;
    mysmb_io_u16 group[2];
    if(!packed || !pixels || !palette || count>256U || (count&1U))return 0;
    w=(struct mysmb_io_palette_pairs *)context;
    bytes=(mysmb_io_u16)(count/2U);
    for(i=0U;i+4U<=bytes;i+=4U){
        memcpy(&group,packed+i,4U);
        if(group[0]|group[1])break;
    }
    if(i+4U>bytes)while(i<bytes && !packed[i])++i;
    if(i==bytes){memset(pixels,palette[0],count);return 1;}
    if(w)mysmb_io_palette_pairs_prepare(w,palette);
    for(i=0U;i<count/2U;++i){
        if(w){
            pair=w->pairs[packed[i]];
            pixels[i*2U]=(mysmb_io_u8)pair;
            pixels[i*2U+1U]=(mysmb_io_u8)(pair>>8U);
        }else{
            pixels[i*2U]=palette[packed[i]&15U];
            pixels[i*2U+1U]=palette[packed[i]>>4U];
        }
    }
    return 1;
}
