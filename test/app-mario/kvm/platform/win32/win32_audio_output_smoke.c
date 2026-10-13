#include <string.h>
#include <stdio.h>
#include "platform/win32/audio_output.h"
static void dispatch(void)
{
    MSG message;
    while(PeekMessage(&message,NULL,0,0,PM_REMOVE)) {
        TranslateMessage(&message);DispatchMessage(&message);
    }
    Sleep(1);
}
int main(int argc,char **argv)
{
    struct mysmb_io_audio_frame audio;
    struct mysmb_win32_audio_output output;
    struct mysmb_win32_audio_renderer expected;
    short samples[MYSMB_WIN32_AUDIO_FRAME_SAMPLES];
    unsigned int frame;
    DWORD start;
    (void)argv;
    memset(&audio,0,sizeof(audio));memset(&output,0,sizeof(output));
    audio.channel_enable=1U;audio.registers[0]=0x9fU;audio.registers[2]=253U;
    audio.writes[0].index=21;audio.writes[0].value=1;
    audio.writes[1].index=0;audio.writes[1].value=0x9f;
    audio.writes[2].index=2;audio.writes[2].value=253;
    audio.writes[3].index=3;audio.writes[3].value=0;audio.write_count=4;
    mysmb_win32_audio_renderer_initialize(&output.renderer);expected=output.renderer;
    for(frame=0;frame<16;++frame) {
        mysmb_win32_audio_render(&expected,&audio,samples,MYSMB_WIN32_AUDIO_FRAME_SAMPLES,MYSMB_WIN32_AUDIO_RATE);
        mysmb_win32_audio_submit(&output,&audio);audio.write_count=0;
    }
    if(memcmp(&expected,&output.renderer,sizeof(expected)) || !mysmb_win32_audio_close(&output))return 1;
    /* Real endpoint availability belongs to the named host integration target,
     * not to the deterministic renderer/adapter owner test. */
    if(argc<2)return 0;
    if(!waveOutGetNumDevs())return 77;
    if(!mysmb_win32_audio_open(&output))return 2;
    start=GetTickCount();
    while(!mysmb_win32_audio_available(&output)) {
        if(GetTickCount()-start>12000U) {
            fprintf(stderr,"audio phase=%d error=%u\n",mygames_win32_pcm_session_phase(output.session),
                (unsigned)mygames_win32_pcm_session_error(output.session));
            return 3;
        }
        dispatch();
    }
    for(frame=0;frame<24;++frame) {
        mysmb_win32_audio_submit(&output,&audio);Sleep(17);
    }
    start=GetTickCount();
    while(!mysmb_win32_audio_close(&output)) {
        if(GetTickCount()-start>2000U)return 4;
        dispatch();
    }
    return 0;
}
