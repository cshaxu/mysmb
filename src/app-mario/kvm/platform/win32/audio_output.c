#include "platform/win32/audio_output.h"
int mysmb_win32_audio_open(struct mysmb_win32_audio_output *output)
{
    ZeroMemory(output,sizeof(*output));
    mysmb_win32_audio_renderer_initialize(&output->renderer);
    output->session=mygames_win32_pcm_session_begin(MYSMB_WIN32_AUDIO_RATE,16,
        MYSMB_WIN32_AUDIO_BUFFERS,MYSMB_WIN32_AUDIO_FRAME_SAMPLES*sizeof(short),0);
    return output->session!=0;
}
int mysmb_win32_audio_available(struct mysmb_win32_audio_output *output)
{
    if(mygames_win32_pcm_session_stalled(output->session,2000U) && !output->recovery)
        output->recovery=mygames_win32_pcm_session_reset(output->session);
    if(output->recovery) {
        if(mygames_win32_pcm_session_reset_result(output->session,output->recovery)==MYGAMES_AUDIO_PENDING)return 0;
        output->recovery=0;
    }
    return mygames_win32_pcm_session_phase(output->session)==MYGAMES_AUDIO_READY;
}
void mysmb_win32_audio_submit(struct mysmb_win32_audio_output *output,
    const struct mysmb_io_audio_frame *frame)
{
    int index=-1;
    short *samples;
    short discarded[MYSMB_WIN32_AUDIO_FRAME_SAMPLES];
    samples=mysmb_win32_audio_available(output)?
        mygames_win32_pcm_session_acquire(output->session,&index):0;
    /* Ordered writes and phase advance during pending/full/unavailable output. */
    mysmb_win32_audio_render(&output->renderer,frame,samples?samples:discarded,
        MYSMB_WIN32_AUDIO_FRAME_SAMPLES,MYSMB_WIN32_AUDIO_RATE);
    if(samples)mygames_win32_pcm_session_publish(output->session,index);
}
int mysmb_win32_audio_close(struct mysmb_win32_audio_output *output)
{
    mygames_win32_pcm_session_stop(output->session);
    return mygames_win32_pcm_session_release(&output->session);
}
LONG mysmb_win32_audio_reset_queue(struct mysmb_win32_audio_output *output)
{return mygames_win32_pcm_session_reset(output->session);}
