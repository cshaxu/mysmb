#ifndef MYGAMES_WIN16_DIB_H
#define MYGAMES_WIN16_DIB_H
#include "kvm/video.h"
/* Bottom-up Windows DIB projection. No USER/GDI or application dependency. */
int mygames_win16_dib_band(mygames_kvm_u8 *pixels,mygames_kvm_u16 capacity,
    mygames_kvm_u16 bits,const struct mygames_kvm_video_band *band,
    const mygames_kvm_u8 reduced_colors[64]);
#endif
