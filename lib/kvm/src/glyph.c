#include "kvm/glyph.h"

unsigned short mygames_kvm_text_glyph_unicode(mygames_kvm_u8 glyph)
{
    if(glyph>=32U && glyph<=126U)return glyph;
    switch(glyph) {
    case MYGAMES_KVM_GLYPH_VERTICAL:return 0x2502U;
    case MYGAMES_KVM_GLYPH_HORIZONTAL:return 0x2500U;
    case MYGAMES_KVM_GLYPH_TOP_LEFT:return 0x250cU;
    case MYGAMES_KVM_GLYPH_TOP_RIGHT:return 0x2510U;
    case MYGAMES_KVM_GLYPH_BOTTOM_LEFT:return 0x2514U;
    case MYGAMES_KVM_GLYPH_BOTTOM_RIGHT:return 0x2518U;
    case MYGAMES_KVM_GLYPH_TEE_LEFT:return 0x251cU;
    case MYGAMES_KVM_GLYPH_TEE_RIGHT:return 0x2524U;
    case MYGAMES_KVM_GLYPH_TEE_TOP:return 0x252cU;
    case MYGAMES_KVM_GLYPH_TEE_BOTTOM:return 0x2534U;
    case MYGAMES_KVM_GLYPH_CROSS:return 0x253cU;
    case MYGAMES_KVM_GLYPH_FULL:return 0x2588U;
    case MYGAMES_KVM_GLYPH_LOWER:return 0x2584U;
    case MYGAMES_KVM_GLYPH_UPPER:return 0x2580U;
    case MYGAMES_KVM_GLYPH_LEFT:return 0x258cU;
    case MYGAMES_KVM_GLYPH_RIGHT:return 0x2590U;
    default:return 0U;
    }
}

mygames_kvm_u8 mygames_kvm_text_glyph_mirror(mygames_kvm_u8 glyph)
{
    switch(glyph) {
    case MYGAMES_KVM_GLYPH_TOP_LEFT:return MYGAMES_KVM_GLYPH_TOP_RIGHT;
    case MYGAMES_KVM_GLYPH_TOP_RIGHT:return MYGAMES_KVM_GLYPH_TOP_LEFT;
    case MYGAMES_KVM_GLYPH_BOTTOM_LEFT:return MYGAMES_KVM_GLYPH_BOTTOM_RIGHT;
    case MYGAMES_KVM_GLYPH_BOTTOM_RIGHT:return MYGAMES_KVM_GLYPH_BOTTOM_LEFT;
    case MYGAMES_KVM_GLYPH_TEE_LEFT:return MYGAMES_KVM_GLYPH_TEE_RIGHT;
    case MYGAMES_KVM_GLYPH_TEE_RIGHT:return MYGAMES_KVM_GLYPH_TEE_LEFT;
    case MYGAMES_KVM_GLYPH_LEFT:return MYGAMES_KVM_GLYPH_RIGHT;
    case MYGAMES_KVM_GLYPH_RIGHT:return MYGAMES_KVM_GLYPH_LEFT;
    case '/':return '\\';case '\\':return '/';
    case '<':return '>';case '>':return '<';
    case '(':return ')';case ')':return '(';
    default:return glyph;
    }
}

mygames_kvm_u8 mygames_kvm_text_glyph_flip(mygames_kvm_u8 glyph)
{
    switch(glyph) {
    case MYGAMES_KVM_GLYPH_TOP_LEFT:return MYGAMES_KVM_GLYPH_BOTTOM_LEFT;
    case MYGAMES_KVM_GLYPH_TOP_RIGHT:return MYGAMES_KVM_GLYPH_BOTTOM_RIGHT;
    case MYGAMES_KVM_GLYPH_BOTTOM_LEFT:return MYGAMES_KVM_GLYPH_TOP_LEFT;
    case MYGAMES_KVM_GLYPH_BOTTOM_RIGHT:return MYGAMES_KVM_GLYPH_TOP_RIGHT;
    case MYGAMES_KVM_GLYPH_TEE_TOP:return MYGAMES_KVM_GLYPH_TEE_BOTTOM;
    case MYGAMES_KVM_GLYPH_TEE_BOTTOM:return MYGAMES_KVM_GLYPH_TEE_TOP;
    case MYGAMES_KVM_GLYPH_UPPER:return MYGAMES_KVM_GLYPH_LOWER;
    case MYGAMES_KVM_GLYPH_LOWER:return MYGAMES_KVM_GLYPH_UPPER;
    case '/':return '\\';case '\\':return '/';
    case '^':return 'v';case 'v':return '^';
    default:return glyph;
    }
}
