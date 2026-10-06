#include "io/palette_expand.h"
#include <string.h>
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
