#ifndef MYSMB_IO_COLOR_H
#define MYSMB_IO_COLOR_H
#include "kvm/color.h"
/* Mario source colour IDs and their reviewed standard16 reduction. */
extern const unsigned long mysmb_io_source_colors[64];
unsigned long mysmb_io_color_rgb(mygames_kvm_u8 index);
mygames_kvm_u8 mysmb_io_color_text16(mygames_kvm_u8 index);
#endif
