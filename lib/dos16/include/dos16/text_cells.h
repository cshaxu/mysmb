#ifndef MYGAMES_DOS16_TEXT_CELLS_H
#define MYGAMES_DOS16_TEXT_CELLS_H

#include "kvm/video.h"

/* Convert a neutral text frame into already-addressed B800 cell words. The
 * caller owns video-mode selection and the physical B800 pointer. */
void mygames_dos16_text_cells(const struct mygames_kvm_text_frame MYGAMES_KVM_FAR *frame,
    volatile mygames_kvm_u16 MYGAMES_KVM_FAR *cells);

#endif
