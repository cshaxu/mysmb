#include "io/audio_renderer.h"
#include <string.h>
int main(void)
{
    struct mysmb_audio_renderer renderer;
    struct mysmb_io_audio_frame frame;
    mygames_kvm_u8 samples[184U];
    unsigned short count;
    unsigned ticks,total=0U,non_silent=0U;
    memset(&frame,0,sizeof(frame));
    frame.write_count=5U;
    frame.writes[0].index=21U;frame.writes[0].value=1U;
    frame.writes[1].index=0U;frame.writes[1].value=0xdfU;
    frame.writes[2].index=2U;frame.writes[2].value=0x40U;
    frame.writes[3].index=2U;frame.writes[3].value=0x41U;
    frame.writes[4].index=3U;frame.writes[4].value=0xf8U;
    mysmb_audio_renderer_initialize(&renderer);
    if(mysmb_audio_renderer_render(&renderer,&frame,samples,1U)!=0U ||
        renderer.sample_remainder!=0UL)return 10;
    for(ticks=0U;ticks<60U;++ticks) {
        count=mysmb_audio_renderer_render(&renderer,&frame,samples,sizeof(samples));
        if(count<183U || count>184U)return 11;
        total+=count;
        if(samples[0]!=128U || samples[count-1U]!=128U)++non_silent;
        frame.write_count=0U;
    }
    if(total!=MYSMB_AUDIO_SAMPLE_RATE || renderer.registers[2U]!=0x41U ||
        renderer.registers[3U]!=0xf8U || !non_silent)return 12;
    frame.registers[21]=1U;frame.registers[0]=0xdfU;
    frame.registers[2]=0x41U;frame.registers[3]=0xf8U;
    mysmb_audio_renderer_sync(&renderer,&frame);
    if(renderer.enabled!=1U || renderer.pulse_timer[0]!=0x41U || !renderer.length[0] || renderer.sample_remainder)return 13;
    if(mysmb_audio_renderer_render(0,&frame,samples,sizeof(samples)) ||
        mysmb_audio_renderer_render(&renderer,0,samples,sizeof(samples)) ||
        mysmb_audio_renderer_render(&renderer,&frame,0,sizeof(samples)))return 14;
    return 0;
}
