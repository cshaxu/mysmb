#ifndef MYGAMES_KVM_TEXT_GLYPH_H
#define MYGAMES_KVM_TEXT_GLYPH_H
#include "kvm/types.h"

/* Selected one-cell IDs coincide with DOS CP437 font slots. ASCII32..126
 * retains its identity. No locale,game state or font bitmap is stored here. */
#define MYGAMES_KVM_GLYPH_VERTICAL 0xb3U
#define MYGAMES_KVM_GLYPH_HORIZONTAL 0xc4U
#define MYGAMES_KVM_GLYPH_TOP_LEFT 0xdaU
#define MYGAMES_KVM_GLYPH_TOP_RIGHT 0xbfU
#define MYGAMES_KVM_GLYPH_BOTTOM_LEFT 0xc0U
#define MYGAMES_KVM_GLYPH_BOTTOM_RIGHT 0xd9U
#define MYGAMES_KVM_GLYPH_TEE_LEFT 0xc3U
#define MYGAMES_KVM_GLYPH_TEE_RIGHT 0xb4U
#define MYGAMES_KVM_GLYPH_TEE_TOP 0xc2U
#define MYGAMES_KVM_GLYPH_TEE_BOTTOM 0xc1U
#define MYGAMES_KVM_GLYPH_CROSS 0xc5U
#define MYGAMES_KVM_GLYPH_FULL 0xdbU
#define MYGAMES_KVM_GLYPH_LOWER 0xdcU
#define MYGAMES_KVM_GLYPH_UPPER 0xdfU
#define MYGAMES_KVM_GLYPH_LEFT 0xddU
#define MYGAMES_KVM_GLYPH_RIGHT 0xdeU

unsigned short mygames_kvm_text_glyph_unicode(mygames_kvm_u8 glyph);
mygames_kvm_u8 mygames_kvm_text_glyph_mirror(mygames_kvm_u8 glyph);
mygames_kvm_u8 mygames_kvm_text_glyph_flip(mygames_kvm_u8 glyph);
#endif
