#ifndef MYSMB_TEXT_COMPACT_ELEMENTS_H
#define MYSMB_TEXT_COMPACT_ELEMENTS_H
#include "text/elements.h"
void mysmb_text_compact_size(const struct mysmb_text_element *element,
    unsigned short *width,unsigned short *height);
int mysmb_text_compact_draw(const struct mysmb_text_element *element,
    const mygames_kvm_u8 colors[3],struct mygames_kvm_text_frame MYGAMES_KVM_FAR *frame,
    mysmb_text_cell_filter filter,const void MYGAMES_KVM_FAR *context);
#endif
