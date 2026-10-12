#include "io/palette_pairs.h"
#include <string.h>
void mysmb_io_palette_pairs_prepare(struct mysmb_io_palette_pairs *w,
    const mysmb_io_u8 MYSMB_IO_FAR *palette)
{
    mysmb_io_u16 i;
    if(w->valid && memcmp(w->palette,palette,16U)==0)return;
    memcpy(w->palette,palette,16U);
    for(i=0U;i<256U;++i)w->pairs[i]=(mysmb_io_u16)(palette[i&15U]|
        ((mysmb_io_u16)palette[i>>4U]<<8U));
    w->valid=1U;
}
