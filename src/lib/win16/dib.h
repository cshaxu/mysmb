#ifndef MYGAMES_WIN16_DIB_H
#define MYGAMES_WIN16_DIB_H
#include "kvm/video.h"
/* Bottom-up Windows DIB projection. No USER/GDI or application dependency.
 * An8-bit DIB provides256 palette entries; undeclared entries are black.
 * In4-bit output undeclared indices reduce to black without a table overread. */
int mygames_win16_dib_band(mygames_kvm_u8 MYGAMES_KVM_FAR *pixels,mygames_kvm_u16 capacity,
    mygames_kvm_u16 bits,const struct mygames_kvm_video_band *band,
    const mygames_kvm_u8 *reduced_colors,mygames_kvm_u16 height,
    mygames_kvm_u16 palette_count);
#endif
