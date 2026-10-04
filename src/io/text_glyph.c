#include "io/text_glyph.h"

unsigned short mysmb_io_text_glyph_unicode(mysmb_io_u8 glyph)
{
    if(glyph>=32U && glyph<=126U)return glyph;
    switch(glyph) {
    case MYSMB_IO_GLYPH_VERTICAL:return 0x2502U;
    case MYSMB_IO_GLYPH_HORIZONTAL:return 0x2500U;
    case MYSMB_IO_GLYPH_TOP_LEFT:return 0x250cU;
    case MYSMB_IO_GLYPH_TOP_RIGHT:return 0x2510U;
    case MYSMB_IO_GLYPH_BOTTOM_LEFT:return 0x2514U;
    case MYSMB_IO_GLYPH_BOTTOM_RIGHT:return 0x2518U;
    case MYSMB_IO_GLYPH_TEE_LEFT:return 0x251cU;
    case MYSMB_IO_GLYPH_TEE_RIGHT:return 0x2524U;
    case MYSMB_IO_GLYPH_TEE_TOP:return 0x252cU;
    case MYSMB_IO_GLYPH_TEE_BOTTOM:return 0x2534U;
    case MYSMB_IO_GLYPH_CROSS:return 0x253cU;
    case MYSMB_IO_GLYPH_FULL:return 0x2588U;
    case MYSMB_IO_GLYPH_LOWER:return 0x2584U;
    case MYSMB_IO_GLYPH_UPPER:return 0x2580U;
    case MYSMB_IO_GLYPH_LEFT:return 0x258cU;
    case MYSMB_IO_GLYPH_RIGHT:return 0x2590U;
    default:return 0U;
    }
}

mysmb_io_u8 mysmb_io_text_glyph_mirror(mysmb_io_u8 glyph)
{
    switch(glyph) {
    case MYSMB_IO_GLYPH_TOP_LEFT:return MYSMB_IO_GLYPH_TOP_RIGHT;
    case MYSMB_IO_GLYPH_TOP_RIGHT:return MYSMB_IO_GLYPH_TOP_LEFT;
    case MYSMB_IO_GLYPH_BOTTOM_LEFT:return MYSMB_IO_GLYPH_BOTTOM_RIGHT;
    case MYSMB_IO_GLYPH_BOTTOM_RIGHT:return MYSMB_IO_GLYPH_BOTTOM_LEFT;
    case MYSMB_IO_GLYPH_TEE_LEFT:return MYSMB_IO_GLYPH_TEE_RIGHT;
    case MYSMB_IO_GLYPH_TEE_RIGHT:return MYSMB_IO_GLYPH_TEE_LEFT;
    case MYSMB_IO_GLYPH_LEFT:return MYSMB_IO_GLYPH_RIGHT;
    case MYSMB_IO_GLYPH_RIGHT:return MYSMB_IO_GLYPH_LEFT;
    case '/':return '\\';case '\\':return '/';
    case '<':return '>';case '>':return '<';
    case '(':return ')';case ')':return '(';
    default:return glyph;
    }
}

mysmb_io_u8 mysmb_io_text_glyph_flip(mysmb_io_u8 glyph)
{
    switch(glyph) {
    case MYSMB_IO_GLYPH_TOP_LEFT:return MYSMB_IO_GLYPH_BOTTOM_LEFT;
    case MYSMB_IO_GLYPH_TOP_RIGHT:return MYSMB_IO_GLYPH_BOTTOM_RIGHT;
    case MYSMB_IO_GLYPH_BOTTOM_LEFT:return MYSMB_IO_GLYPH_TOP_LEFT;
    case MYSMB_IO_GLYPH_BOTTOM_RIGHT:return MYSMB_IO_GLYPH_TOP_RIGHT;
    case MYSMB_IO_GLYPH_TEE_TOP:return MYSMB_IO_GLYPH_TEE_BOTTOM;
    case MYSMB_IO_GLYPH_TEE_BOTTOM:return MYSMB_IO_GLYPH_TEE_TOP;
    case MYSMB_IO_GLYPH_UPPER:return MYSMB_IO_GLYPH_LOWER;
    case MYSMB_IO_GLYPH_LOWER:return MYSMB_IO_GLYPH_UPPER;
    case '/':return '\\';case '\\':return '/';
    case '^':return 'v';case 'v':return '^';
    default:return glyph;
    }
}
