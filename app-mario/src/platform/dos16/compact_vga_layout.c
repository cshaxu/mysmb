#include "platform/dos16/compact_vga_layout.h"

int mysmb_dos16_compact_cache_address(mysmb_io_u16 x,mysmb_io_u16 y,
    mysmb_io_u8 *plane,mysmb_io_u16 *offset)
{
    if(!plane || !offset || x>=MYSMB_DOS16_COMPACT_CACHE_WIDTH ||
        y>=MYSMB_DOS16_COMPACT_CACHE_HEIGHT)return 0;
    *plane=(mysmb_io_u8)(x&3U);
    *offset=(mysmb_io_u16)(y*MYSMB_DOS16_COMPACT_CACHE_STRIDE+(x>>2U));
    return 1;
}

int mysmb_dos16_compact_page_address(mysmb_io_u8 page,mysmb_io_u16 x,
    mysmb_io_u16 y,mysmb_io_u8 *plane,mysmb_io_u16 *offset)
{
    mysmb_io_u16 base;
    if(!plane || !offset || page>=2U || x>=MYSMB_DOS16_COMPACT_PAGE_WIDTH ||
        y>=MYSMB_DOS16_COMPACT_PAGE_HEIGHT)return 0;
    base=page==0U?MYSMB_DOS16_COMPACT_PAGE_A:MYSMB_DOS16_COMPACT_PAGE_B;
    *plane=(mysmb_io_u8)(x&3U);
    *offset=(mysmb_io_u16)(base+y*MYSMB_DOS16_COMPACT_PAGE_STRIDE+(x>>2U));
    return 1;
}

int mysmb_dos16_compact_viewport_row(mysmb_io_u8 scene_page,mysmb_io_u8 scroll_x,
    mysmb_io_u8 scroll_y,mysmb_io_u8 row,mysmb_io_u16 *source,
    mysmb_io_u8 *first_count,mysmb_io_u8 *second_count)
{
    mysmb_io_u16 x,y,available;
    if(!source || !first_count || !second_count || scene_page>=2U || row>=240U)
        return 0;
    x=(mysmb_io_u16)scene_page*256U+scroll_x;
    y=(mysmb_io_u16)scroll_y+row;
    if(y>=240U)y=(mysmb_io_u16)(y-240U);
    /* CRTC start is word-addressed: use an 8-pixel aligned source and let
     * hardware panning select the requested first pixel. */
    x=(mysmb_io_u16)(x&0xfff8U);
    if(x>=512U)x=(mysmb_io_u16)(x-512U);
    *source=(mysmb_io_u16)(y*MYSMB_DOS16_COMPACT_CACHE_STRIDE+(x>>2U));
    available=(mysmb_io_u16)(MYSMB_DOS16_COMPACT_CACHE_STRIDE-(x>>2U));
    *first_count=(mysmb_io_u8)(available>=MYSMB_DOS16_COMPACT_PAGE_STRIDE?
        MYSMB_DOS16_COMPACT_PAGE_STRIDE:available);
    *second_count=(mysmb_io_u8)(MYSMB_DOS16_COMPACT_PAGE_STRIDE-*first_count);
    return 1;
}
