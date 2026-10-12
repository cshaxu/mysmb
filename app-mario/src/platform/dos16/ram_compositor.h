#ifndef MYSMB_PLATFORM_DOS16_RAM_COMPOSITOR_H
#define MYSMB_PLATFORM_DOS16_RAM_COMPOSITOR_H

#include "ppu/frame.h"

/*
 * DOS16's RAM screen is deliberately a consumer of the already prepared PPU
 * view.  It owns no scroll, split, palette, priority, or OAM decision: the
 * frame API has made all of those decisions before this adapter is called.
 */
int mysmb_dos16_ram_composite(const struct mysmb_ppu_frame_view *view,
    mygames_kvm_u8 MYGAMES_KVM_FAR *screen,mygames_kvm_u16 capacity);

#endif
