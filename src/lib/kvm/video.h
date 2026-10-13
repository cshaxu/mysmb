#ifndef MYGAMES_KVM_VIDEO_H
#define MYGAMES_KVM_VIDEO_H
#include "kvm/types.h"

/* A borrowed index surface. Capacity/stride are bytes; RGB entries are
 * 0x00RRGGBB. Storage and palette remain valid for synchronous presentation.
 * Each supplied span must fit the declared16-bit capacity, including padding. */
struct mygames_kvm_video_frame {
    const mygames_kvm_u8 MYGAMES_KVM_FAR *pixels;
    mygames_kvm_u16 width,height,stride,capacity;
    const unsigned long MYGAMES_KVM_FAR *palette;
    mygames_kvm_u16 palette_count;
};
struct mygames_kvm_video_band {
    const mygames_kvm_u8 MYGAMES_KVM_FAR *pixels;
    mygames_kvm_u16 first,rows;
    mygames_kvm_u16 width,stride,capacity;
};
struct mygames_kvm_video_source {
    void *context;
    int (*read_rows)(void *,mygames_kvm_u16,mygames_kvm_u16,
        struct mygames_kvm_video_band *);
};
struct mygames_kvm_text_cell {
    mygames_kvm_u8 character,foreground,background;
};
/* Portable CP437 cell IDs and16 logical foreground/background slots.
 * Capacity and stride count cells; source_colors selects caller RGB versus
 * canonical device16. Application palette construction is not part of KVM. */
struct mygames_kvm_text_frame {
    const struct mygames_kvm_text_cell MYGAMES_KVM_FAR *cells;
    mygames_kvm_u16 columns,rows,stride,capacity;
    mygames_kvm_u8 source_colors;
    const unsigned long MYGAMES_KVM_FAR *colors;
};
#define MYGAMES_KVM_TEXT_FRAME_ROWS(f) ((f)->rows)
#define MYGAMES_KVM_TEXT_FRAME_CELLS(f) ((f)->columns*(f)->rows)
int mygames_kvm_video_valid(const struct mygames_kvm_video_frame *frame);
int mygames_kvm_band_valid(const struct mygames_kvm_video_band *band,
    mygames_kvm_u16 height);
int mygames_kvm_text_valid(const struct mygames_kvm_text_frame MYGAMES_KVM_FAR *frame);
#endif
