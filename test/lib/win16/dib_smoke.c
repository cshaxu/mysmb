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
    memset(pixels,255,sizeof(pixels));
    if(!mygames_win16_dib_band(pixels,sizeof(pixels),8U,&band,0) ||
        memcmp(pixels+256,source,256) || memcmp(pixels,source+256,256) ||
        pixels[512]!=255U)return 1;
    memset(pixels,255,sizeof(pixels));
    if(!mygames_win16_dib_band(pixels,30720U,4U,&band,colors) ||
        pixels[128]!=1U || pixels[129]!=0x23U || pixels[0]!=1U ||
        pixels[256]!=255U)return 2;
    if(mygames_win16_dib_band(pixels,30719U,4U,&band,colors) ||
        mygames_win16_dib_band(pixels,61439U,8U,&band,colors) ||
        mygames_win16_dib_band(pixels,sizeof(pixels),1U,&band,colors) ||
        mygames_win16_dib_band(pixels,sizeof(pixels),4U,&band,0))return 3;
    band.rows=3U;
    if(mygames_win16_dib_band(pixels,sizeof(pixels),8U,&band,0))return 4;
    band.rows=0U;band.first=240U;
    if(mygames_win16_dib_band(pixels,sizeof(pixels),8U,&band,0))return 5;
    band.first=0U;band.pixels=0;
    if(mygames_win16_dib_band(pixels,sizeof(pixels),8U,&band,0) ||
        mygames_win16_dib_band(0,sizeof(pixels),8U,&band,0) ||
        mygames_win16_dib_band(pixels,sizeof(pixels),8U,0,0))return 6;
    band.pixels=source;
    return !mygames_win16_dib_band(pixels,sizeof(pixels),8U,&band,0);
}
