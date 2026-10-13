#include "io/palette_pairs.h"
#include <string.h>
void mysmb_io_palette_pairs_prepare(struct mysmb_io_palette_pairs *w,
    const mygames_kvm_u8 MYGAMES_KVM_FAR *palette)
{
    mygames_kvm_u16 i;
    if(w->valid && memcmp(w->palette,palette,16U)==0)return;
    memcpy(w->palette,palette,16U);
    for(i=0U;i<256U;++i)w->pairs[i]=(mygames_kvm_u16)(palette[i&15U]|
        ((mygames_kvm_u16)palette[i>>4U]<<8U));
    w->valid=1U;
}
