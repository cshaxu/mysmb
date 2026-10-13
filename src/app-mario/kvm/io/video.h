#ifndef MYSMB_IO_VIDEO_H
#define MYSMB_IO_VIDEO_H
#include "kvm/video.h"
#define MYSMB_VIDEO_WIDTH 256U
#define MYSMB_VIDEO_HEIGHT 240U
#define MYSMB_VIDEO_PIXELS 61440U
#define MYSMB_IO_TEXT_COLUMNS 80U
#define MYSMB_IO_TEXT_ROWS 50U
#define MYSMB_IO_TEXT_CELLS 4000U
#define MYSMB_VIDEO_PALETTE_COLORS 32U
struct mysmb_palette_video_frame {
    const mygames_kvm_u8 MYGAMES_KVM_FAR *pixels;
    const mygames_kvm_u8 MYGAMES_KVM_FAR *master_colors;
};
/* Explicit slot-index view. Entries map slots to original master colors.
 * Both table and rows are immutable for the complete synchronous present. */
struct mysmb_palette_video_source {
    struct mygames_kvm_video_source rows;
    const mygames_kvm_u8 MYGAMES_KVM_FAR *master_colors;
};

struct mysmb_io_text_frame {
    struct mygames_kvm_text_cell cells[MYSMB_IO_TEXT_CELLS];
    /* Retained capacity supports both layouts;only selected rows are output.
     * Palette entries are neutral RGB,not host attributes or game state. */
    mygames_kvm_u16 rows;
    mygames_kvm_u8 source_colors;
    unsigned long colors[16];
    mygames_kvm_u8 master_map[64];
};

#define MYSMB_IO_TEXT_FRAME_ROWS(f) ((f)->rows==25U?25U:50U)
#define MYSMB_IO_TEXT_FRAME_CELLS(f) (80U*MYSMB_IO_TEXT_FRAME_ROWS(f))

/* Borrow only for this synchronous presentation. No cell copy or allocation. */
void mysmb_text_frame_view(const struct mysmb_io_text_frame MYGAMES_KVM_FAR *source,
    struct mygames_kvm_text_frame *view);
#endif
