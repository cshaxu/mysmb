#include "dos16/text_cells.h"
#include "kvm/color.h"

void mygames_dos16_text_cells(const struct mygames_kvm_text_frame MYGAMES_KVM_FAR *frame,
    volatile mygames_kvm_u16 MYGAMES_KVM_FAR *cells)
{
    mygames_kvm_u8 colors[16];
    mygames_kvm_u16 index,x,y;
    if(!mygames_kvm_text_valid(frame) || !cells || frame->columns>80U || frame->rows>50U)return;
    mygames_kvm_color_text_attributes(frame->colors,frame->source_colors,colors);
    for(y=0U;y<frame->rows;++y)for(x=0U;x<frame->columns;++x) {
        index=(mygames_kvm_u16)(y*frame->stride+x);
        cells[y*80U+x]=(mygames_kvm_u16)(frame->cells[index].character|
            ((mygames_kvm_u16)colors[frame->cells[index].foreground&15U]<<8U)|
            ((mygames_kvm_u16)colors[frame->cells[index].background&15U]<<12U));
    }
}
