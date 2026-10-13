#include <string.h>
#include "win16/dib.h"
static unsigned char pixels[61440],source[512],colors[64];
int main(void)
{
    unsigned short i;
    struct mygames_kvm_video_band band;
    for(i=0U;i<64U;++i)colors[i]=(unsigned char)(i&15U);
    for(i=0U;i<512U;++i)source[i]=(unsigned char)(i&63U);
    band.pixels=source;band.first=238U;band.rows=2U;
    band.width=band.stride=256U;band.capacity=512U;
    memset(pixels,255,sizeof(pixels));
    if(!mygames_win16_dib_band(pixels,sizeof(pixels),8U,&band,0,240U,64U) ||
        memcmp(pixels+256,source,256) || memcmp(pixels,source+256,256) ||
        pixels[512]!=255U)return 1;
    memset(pixels,255,sizeof(pixels));
    if(!mygames_win16_dib_band(pixels,30720U,4U,&band,colors,240U,64U) ||
        pixels[128]!=1U || pixels[129]!=0x23U || pixels[0]!=1U ||
        pixels[256]!=255U)return 2;
    if(mygames_win16_dib_band(pixels,30719U,4U,&band,colors,240U,64U) ||
        mygames_win16_dib_band(pixels,61439U,8U,&band,colors,240U,64U) ||
        mygames_win16_dib_band(pixels,sizeof(pixels),1U,&band,colors,240U,64U) ||
        mygames_win16_dib_band(pixels,sizeof(pixels),4U,&band,0,240U,64U))return 3;
    band.rows=3U;
    if(mygames_win16_dib_band(pixels,sizeof(pixels),8U,&band,0,240U,64U))return 4;
    band.rows=0U;band.first=240U;
    if(mygames_win16_dib_band(pixels,sizeof(pixels),8U,&band,0,240U,64U))return 5;
    band.first=0U;band.pixels=0;
    if(mygames_win16_dib_band(pixels,sizeof(pixels),8U,&band,0,240U,64U) ||
        mygames_win16_dib_band(0,sizeof(pixels),8U,&band,0,240U,64U) ||
        mygames_win16_dib_band(pixels,sizeof(pixels),8U,0,0,240U,64U))return 6;
    band.pixels=source;
    band.rows=1U;
    if(!mygames_win16_dib_band(pixels,sizeof(pixels),8U,&band,0,240U,64U))return 7;
    /* Odd non-game geometry, padded input/output and a palette entry above63. */
    band.width=3U;band.stride=5U;band.rows=2U;band.capacity=8U;
    source[0]=0U;source[1]=1U;source[2]=2U;
    source[5]=3U;source[6]=4U;source[7]=5U;
    memset(pixels,255,sizeof(pixels));
    if(!mygames_win16_dib_band(pixels,8U,4U,&band,colors,2U,64U) ||
        pixels[0]!=0x34U || pixels[1]!=0x50U || pixels[2] || pixels[3] ||
        pixels[4]!=0x01U || pixels[5]!=0x20U || pixels[8]!=255U)return 8;
    source[7]=200U;
    if(!mygames_win16_dib_band(pixels,8U,8U,&band,0,2U,256U) ||
        pixels[2]!=200U || pixels[3]!=0U)return 9;
    memset(pixels,255,sizeof(pixels));
    if(!mygames_win16_dib_band(pixels,8U,4U,&band,colors,2U,64U) ||
        pixels[0]!=0x34U || pixels[1]!=0U)return 10;
    if(mygames_win16_dib_band(pixels,8U,8U,&band,0,2U,0U) ||
        mygames_win16_dib_band(pixels,8U,8U,&band,0,2U,257U))return 11;
    return 0;
}
