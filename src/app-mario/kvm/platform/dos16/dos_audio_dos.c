#include "platform/dos16/dos_audio.h"
#include "dos16/pcm.h"
static struct mysmb_audio_renderer renderer;
static mygames_kvm_u8 samples[184];
int mysmb_dos16_audio_dos_open(void)
{
    mysmb_audio_renderer_initialize(&renderer);
    return mygames_dos16_pcm_dos_open(MYSMB_AUDIO_SAMPLE_RATE);
}
int mysmb_dos16_audio_dos_close(void){return mygames_dos16_pcm_dos_close();}
void mysmb_dos16_audio_dos_after_load(void)
{
    mygames_dos16_pcm_dos_reset();
    mysmb_audio_renderer_initialize(&renderer);
}
int mysmb_dos16_audio_dos_prepared(void){return mygames_dos16_pcm_dos_prepared();}
mygames_kvm_u8 mysmb_dos16_audio_dos_submit(const struct mysmb_io_audio_frame *frame)
{
    unsigned short count;
    if(!frame || !mygames_dos16_pcm_dos_prepared())return MYSMB_IO_AUDIO_UNAVAILABLE;
    count=mysmb_audio_renderer_render(&renderer,frame,samples,sizeof(samples));
    return mygames_dos16_pcm_dos_submit(samples,count)==count?MYSMB_IO_AUDIO_AVAILABLE:
        MYSMB_IO_AUDIO_UNAVAILABLE;
}
