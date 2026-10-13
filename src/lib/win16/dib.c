#include "win16/memory.h"
#include "win16/dib.h"
int mygames_win16_dib_band(mygames_kvm_u8 MYGAMES_KVM_FAR *pixels,mygames_kvm_u16 capacity,
    mygames_kvm_u16 bits,const struct mygames_kvm_video_band *band,
    const mygames_kvm_u8 *reduced_colors,mygames_kvm_u16 height,
    mygames_kvm_u16 palette_count)
{
    mygames_kvm_u16 row,x,stride;
    mygames_kvm_u8 color;
    unsigned long bytes;
    const mygames_kvm_u8 MYGAMES_KVM_FAR *source;
    mygames_kvm_u8 MYGAMES_KVM_FAR *target;
    if(!pixels || !mygames_kvm_band_valid(band,height) ||
        (bits!=4U && bits!=8U) || !palette_count || palette_count>256U ||
        (bits==4U && !reduced_colors))return 0;
    bytes=(((unsigned long)band->width*bits+31UL)/32UL)*4UL;
    if(bytes>65535UL || bytes*height>capacity)return 0;
    stride=(mygames_kvm_u16)bytes;
    for(row=0U;row<band->rows;++row) {
        source=band->pixels+row*band->stride;
        target=pixels+(height-1U-band->first-row)*stride;
        mygames_win16_zero(target,0,stride);
        if(bits==8U)mygames_win16_copy(target,source,band->width);
        else for(x=0U;x<band->width;++x) {
            color=source[x]<palette_count?(mygames_kvm_u8)(reduced_colors[source[x]]&15U):0U;
            if(!(x&1U))target[x/2U]=(mygames_kvm_u8)(color<<4);
            else target[x/2U]|=color;
        }
    }
    return 1;
}
