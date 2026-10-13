#include <string.h>
#include "win16/dib.h"
int mygames_win16_dib_band(mygames_kvm_u8 *pixels,mygames_kvm_u16 capacity,
    mygames_kvm_u16 bits,const struct mygames_kvm_video_band *band,
    const mygames_kvm_u8 reduced_colors[64])
{
    mygames_kvm_u16 row,x,stride;
    if(!pixels || !band || !band->pixels || (bits!=4U && bits!=8U) ||
        band->first>=240U || band->rows>240U-band->first ||
        (bits==4U && !reduced_colors))return 0;
    stride=bits==4U?128U:256U;
    if(capacity<stride*240U)return 0;
    for(row=0U;row<band->rows;++row) {
        if(bits==8U)
            memcpy(pixels+(239U-band->first-row)*stride,
                band->pixels+row*256U,256U);
        else for(x=0U;x<256U;x+=2U)
            pixels[(239U-band->first-row)*stride+x/2U]=(mygames_kvm_u8)(
                ((reduced_colors[band->pixels[row*256U+x]&63U]&15U)<<4)|
                (reduced_colors[band->pixels[row*256U+x+1U]&63U]&15U));
    }
    return 1;
}
