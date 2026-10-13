#include "kvm/color.h"
#include "kvm/glyph.h"
#include "kvm/input_event.h"
#include "kvm/video.h"
#include <string.h>

int main(void)
{
    struct mygames_kvm_text_frame frame;
    struct mygames_kvm_input_event event;
    struct mygames_kvm_video_frame video;
    struct mygames_kvm_video_band band;
    struct mygames_kvm_text_cell cells[12];
    unsigned char pixels[32];
    unsigned long colors[16];
    unsigned short i,glyph;
    memset(&frame,0,sizeof(frame));memset(&video,0,sizeof(video));
    memset(&band,0,sizeof(band));
    if(sizeof(mygames_kvm_u8)!=1U || sizeof(mygames_kvm_u16)!=2U)return 1;
    if(mygames_kvm_text_valid(0) || mygames_kvm_text_valid(&frame))return 2;
    frame.cells=cells;frame.columns=3U;frame.rows=2U;frame.stride=5U;
    frame.capacity=8U;
    if(!mygames_kvm_text_valid(&frame))return 7;
    frame.capacity=7U;if(mygames_kvm_text_valid(&frame))return 8;
    frame.capacity=12U;frame.source_colors=1U;
    if(mygames_kvm_text_valid(&frame))return 9;
    frame.colors=colors;if(!mygames_kvm_text_valid(&frame))return 10;
    frame.stride=2U;if(mygames_kvm_text_valid(&frame))return 11;
    frame.stride=65535U;frame.rows=65535U;
    if(mygames_kvm_text_valid(&frame))return 12;
    video.pixels=pixels;video.width=4U;video.height=2U;
    video.stride=8U;video.capacity=12U;video.palette=colors;video.palette_count=16U;
    if(!mygames_kvm_video_valid(&video))return 13;
    video.palette_count=257U;if(mygames_kvm_video_valid(&video))return 14;
    video.palette_count=0U;if(mygames_kvm_video_valid(&video))return 23;
    video.palette_count=16U;video.pixels=0;
    if(mygames_kvm_video_valid(&video) || mygames_kvm_video_valid(0))return 24;
    video.pixels=pixels;video.palette=0;if(mygames_kvm_video_valid(&video))return 25;
    video.palette=colors;video.width=0U;if(mygames_kvm_video_valid(&video))return 26;
    video.width=4U;video.height=0U;if(mygames_kvm_video_valid(&video))return 27;
    video.height=2U;video.stride=3U;if(mygames_kvm_video_valid(&video))return 28;
    video.stride=8U;video.capacity=11U;if(mygames_kvm_video_valid(&video))return 29;
    band.pixels=pixels;band.width=4U;band.rows=2U;band.stride=8U;band.capacity=12U;
    if(!mygames_kvm_band_valid(&band,2U))return 15;
    band.first=1U;if(mygames_kvm_band_valid(&band,2U))return 16;
    band.first=2U;if(mygames_kvm_band_valid(&band,2U))return 30;
    band.first=0U;band.rows=0U;if(mygames_kvm_band_valid(&band,2U))return 31;
    band.rows=1U;band.pixels=0;
    if(mygames_kvm_band_valid(&band,2U) || mygames_kvm_band_valid(0,2U))return 32;
    frame.columns=3U;frame.rows=2U;frame.stride=5U;frame.capacity=12U;
    frame.source_colors=2U;if(mygames_kvm_text_valid(&frame))return 33;
    frame.source_colors=0U;frame.capacity=21846U;
    if(mygames_kvm_text_valid(&frame))return 34;
    for(i=0U;i<256U;++i) {
        glyph=mygames_kvm_text_glyph_unicode((mygames_kvm_u8)i);
        if(!glyph || (glyph>=0xd800U && glyph<=0xdfffU))return 19;
        if(i>=32U && i<=126U && glyph!=i)return 20;
        if(mygames_kvm_text_glyph_mirror(mygames_kvm_text_glyph_mirror((mygames_kvm_u8)i))!=i ||
            mygames_kvm_text_glyph_flip(mygames_kvm_text_glyph_flip((mygames_kvm_u8)i))!=i)return 21;
    }
    if(mygames_kvm_text_glyph_unicode(0U)!=32U ||
        mygames_kvm_text_glyph_unicode(MYGAMES_KVM_GLYPH_UPPER)!=0x2580U ||
        mygames_kvm_text_glyph_unicode(MYGAMES_KVM_GLYPH_LOWER)!=0x2584U)return 22;
    if(mygames_kvm_text_glyph_unicode(1U)!=0x263aU ||
        mygames_kvm_text_glyph_unicode(16U)!=0x25baU ||
        mygames_kvm_text_glyph_unicode(0x80U)!=0x00c7U)return 17;
    if(mygames_kvm_color_text_nearest(mygames_kvm_color_text_rgb(12U))!=12U)return 3;
    if(mygames_kvm_text_glyph_unicode(MYGAMES_KVM_GLYPH_TOP_LEFT)!=0x250cU)return 4;
    if(mygames_kvm_text_glyph_mirror(MYGAMES_KVM_GLYPH_TOP_LEFT)!=MYGAMES_KVM_GLYPH_TOP_RIGHT)return 5;
    event.kind=MYGAMES_KVM_INPUT_KEY; event.down=1U;
    event.physical_code=MYGAMES_KVM_KEY_J; event.native_scan=0U;
    event.modifiers=0U; event.x=-1; event.y=-2;
    if(event.x>=0 || event.y>=0)return 18;
    frame.rows=25U;
    if(event.physical_code!=MYGAMES_KVM_KEY_J || MYGAMES_KVM_TEXT_FRAME_ROWS(&frame)!=25U)return 6;
    return 0;
}
