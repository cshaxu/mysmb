#include <string.h>
#include <stdio.h>
#include "platform/win32/audio_output.h"
static unsigned long written,nonzero;
static short minimum,maximum;
static int real_device;
static MMRESULT WINAPI accepting_open(LPHWAVEOUT out,UINT id,LPCWAVEFORMATEX format,
    DWORD_PTR callback,DWORD_PTR instance,DWORD flags)
{
    (void)id;(void)callback;(void)instance;(void)flags;
    if(format->wBitsPerSample!=16 || format->nChannels!=1)return WAVERR_BADFORMAT;
    *out=(HWAVEOUT)(UINT_PTR)1;return MMSYSERR_NOERROR;
}
static MMRESULT WINAPI accepting_header(HWAVEOUT device,LPWAVEHDR header,UINT bytes)
{(void)device;(void)header;(void)bytes;return MMSYSERR_NOERROR;}
static MMRESULT WINAPI accepting_device(HWAVEOUT device)
{(void)device;return MMSYSERR_NOERROR;}
static MMRESULT WINAPI capture_write(HWAVEOUT device,LPWAVEHDR header,UINT bytes)
{
    MMRESULT result=real_device?waveOutWrite(device,header,bytes):MMSYSERR_NOERROR;
    unsigned long i;
    short *pcm=(short *)header->lpData;
    if(!real_device)header->dwFlags|=WHDR_DONE;
    if(result==MMSYSERR_NOERROR) {
        ++written;
        for(i=0;i<header->dwBufferLength/sizeof(short);++i) {
            if(pcm[i])++nonzero;
            if(pcm[i]<minimum)minimum=pcm[i];
            if(pcm[i]>maximum)maximum=pcm[i];
        }
    }
    return result;
}
static const struct mygames_win32_pcm_api capture_api={
    waveOutOpen,waveOutPrepareHeader,capture_write,waveOutReset,
    waveOutUnprepareHeader,waveOutClose
};
static const struct mygames_win32_pcm_api accepting_api={
    accepting_open,accepting_header,capture_write,accepting_device,
    accepting_header,accepting_device
};
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
    real_device=argc>1;
    if(real_device && !waveOutGetNumDevs())return 77;
    mysmb_win32_audio_renderer_initialize(&output.renderer);
    output.session=mygames_win32_pcm_session_begin(MYSMB_WIN32_AUDIO_RATE,16,
        MYSMB_WIN32_AUDIO_BUFFERS,MYSMB_WIN32_AUDIO_FRAME_SAMPLES*sizeof(short),
        real_device?&capture_api:&accepting_api);
    if(!output.session)return 2;
    start=GetTickCount();
    while(!mysmb_win32_audio_available(&output)) {
        if(GetTickCount()-start>12000U) {
            fprintf(stderr,"audio phase=%d error=%u\n",mygames_win32_pcm_session_phase(output.session),
                (unsigned)mygames_win32_pcm_session_error(output.session));
            return 3;
        }
        dispatch();
    }
    audio.write_count=4;
    for(frame=0;frame<24;++frame) {
        mysmb_win32_audio_submit(&output,&audio);Sleep(17);
        audio.write_count=0;
    }
    start=GetTickCount();
    while(!mysmb_win32_audio_close(&output)) {
        if(GetTickCount()-start>2000U)return 4;
        dispatch();
    }
    printf("%s writes=%lu nonzero_samples=%lu range=%d..%d\n",
        real_device?"real WinMM":"accepting PCM sink",written,nonzero,(int)minimum,(int)maximum);
    return written>=8 && nonzero && minimum<maximum ? 0:5;
}
