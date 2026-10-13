#include "platform/win32/audio_output.h"
int mysmb_win32_audio_open(struct mysmb_win32_audio_output *output)
{
    ZeroMemory(output,sizeof(*output));
    mysmb_win32_audio_renderer_initialize(&output->renderer);
    return mygames_win32_pcm_open(&output->pcm,MYSMB_WIN32_AUDIO_RATE,1,16,
        output->headers,output->queued,output->samples,MYSMB_WIN32_AUDIO_BUFFERS,
        sizeof(output->samples[0]),0);
}
void mysmb_win32_audio_submit(struct mysmb_win32_audio_output *output,
    const struct mysmb_io_audio_frame *frame)
{
    int index;
    short discarded[MYSMB_WIN32_AUDIO_FRAME_SAMPLES];
    if(!output->pcm.device)return;
    index=mygames_win32_pcm_acquire(&output->pcm);
    /* Oscillator time advances even when the device queue is full. */
    mysmb_win32_audio_render(&output->renderer,frame,index<0?discarded:output->samples[index],
        MYSMB_WIN32_AUDIO_FRAME_SAMPLES,MYSMB_WIN32_AUDIO_RATE);
    if(index>=0)(void)mygames_win32_pcm_submit(&output->pcm,(unsigned short)index);
}
void mysmb_win32_audio_close(struct mysmb_win32_audio_output *output)
{mygames_win32_pcm_close(&output->pcm);}
int mysmb_win32_audio_reset_queue(struct mysmb_win32_audio_output *output)
{return mygames_win32_pcm_reset(&output->pcm);}
