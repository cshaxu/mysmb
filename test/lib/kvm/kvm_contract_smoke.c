#include "kvm/color.h"
#include "kvm/glyph.h"
#include "kvm/input_event.h"
#include "kvm/video.h"

int main(void)
{
    struct mygames_kvm_text_frame frame;
    struct mygames_kvm_input_event event;
    if(sizeof(mygames_kvm_u8)!=1U || sizeof(mygames_kvm_u16)!=2U)return 1;
    if(MYGAMES_KVM_TEXT_CELLS!=4000U || MYGAMES_KVM_VIDEO_PIXELS!=61440U)return 2;
    if(mygames_kvm_color_text_nearest(mygames_kvm_color_text_rgb(12U))!=12U)return 3;
    if(mygames_kvm_text_glyph_unicode(MYGAMES_KVM_GLYPH_TOP_LEFT)!=0x250cU)return 4;
    if(mygames_kvm_text_glyph_mirror(MYGAMES_KVM_GLYPH_TOP_LEFT)!=MYGAMES_KVM_GLYPH_TOP_RIGHT)return 5;
    event.kind=MYGAMES_KVM_INPUT_KEY; event.down=1U;
    event.physical_code=MYGAMES_KVM_KEY_J; event.native_scan=0U;
    event.modifiers=0U; event.x=0U; event.y=0U;
    frame.rows=25U;
    if(event.physical_code!=MYGAMES_KVM_KEY_J || MYGAMES_KVM_TEXT_FRAME_ROWS(&frame)!=25U)return 6;
    return 0;
}
