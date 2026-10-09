#include "platform/dos16/compact_vga_layout.h"
#include <stdio.h>

int main(void)
{
    mysmb_io_u16 source,offset;
    mysmb_io_u8 plane,first,second;
    mysmb_io_u16 x,y,row,expected_source,expected_x,expected_y,available;
    mysmb_io_u8 scene;
    if(MYSMB_DOS16_COMPACT_TOTAL_BYTES>65536U)return 1;
    if(!mysmb_dos16_compact_cache_address(511U,239U,&plane,&offset) ||
        plane!=3U || offset!=30719U)return 2;
    if(!mysmb_dos16_compact_page_address(0U,263U,239U,&plane,&offset) ||
        plane!=3U || offset!=46559U)return 3;
    if(!mysmb_dos16_compact_page_address(1U,263U,239U,&plane,&offset) ||
        plane!=3U || offset!=62399U)return 4;
    for(y=0U;y<240U;++y)for(x=0U;x<512U;x=(mysmb_io_u16)(x+8U)) {
        if(!mysmb_dos16_compact_viewport_row((mysmb_io_u8)(x>>8U),
            (mysmb_io_u8)x,(mysmb_io_u8)y,239U,&source,&first,&second) ||
            source>=MYSMB_DOS16_COMPACT_CACHE_BYTES ||
            (mysmb_io_u16)first+second!=MYSMB_DOS16_COMPACT_PAGE_STRIDE ||
            first==0U)return 5;
    }
    if(!mysmb_dos16_compact_viewport_row(1U,252U,239U,1U,&source,&first,&second) ||
        source!=126U || first!=2U || second!=64U)return 6;
    /* Cover every legal page, horizontal pan, vertical origin and output row.
     * This is the complete address contract used by the latch-copy loop. */
    for(scene=0U;scene<2U;++scene)for(x=0U;x<256U;++x)
        for(y=0U;y<240U;++y)for(row=0U;row<240U;++row) {
            if(!mysmb_dos16_compact_viewport_row(scene,(mysmb_io_u8)x,
                (mysmb_io_u8)y,(mysmb_io_u8)row,&source,&first,&second))return 7;
            expected_x=(mysmb_io_u16)(scene*256U+(x&0xfff8U));
            if(expected_x>=512U)expected_x-=512U;
            expected_y=(mysmb_io_u16)(y+row);
            if(expected_y>=240U)expected_y-=240U;
            expected_source=(mysmb_io_u16)(expected_y*
                MYSMB_DOS16_COMPACT_CACHE_STRIDE+(expected_x>>2U));
            available=(mysmb_io_u16)(MYSMB_DOS16_COMPACT_CACHE_STRIDE-(expected_x>>2U));
            if(available>MYSMB_DOS16_COMPACT_PAGE_STRIDE)
                available=MYSMB_DOS16_COMPACT_PAGE_STRIDE;
            if(source!=expected_source || first!=available ||
                second!=MYSMB_DOS16_COMPACT_PAGE_STRIDE-available)return 8;
        }
    printf("compact-vga bytes=%u page=%u wrap=1\n",
        MYSMB_DOS16_COMPACT_TOTAL_BYTES,MYSMB_DOS16_COMPACT_PAGE_BYTES);
    return 0;
}
