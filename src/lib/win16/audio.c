#include <windows.h>
#include <mmsystem.h>
#include <string.h>
#include "win16/audio.h"
#define BLOCKS 8U
#define SAMPLES 184U
struct pcm_block { WAVEHDR header; unsigned char samples[SAMPLES]; };
typedef UINT (WINAPI *open_proc)(HWAVEOUT FAR *,UINT,const WAVEFORMAT FAR *,DWORD,DWORD,DWORD);
typedef UINT (WINAPI *device_proc)(HWAVEOUT);
typedef UINT (WINAPI *header_proc)(HWAVEOUT,WAVEHDR FAR *,UINT);
static HINSTANCE library;
static HWAVEOUT device;
static HGLOBAL memory;
static struct pcm_block FAR *blocks;
static unsigned short prepared,next,retry_pending;
static unsigned long retry_rate,retry_stamp;
static open_proc open_device;
static device_proc close_device,reset_device;
static header_proc prepare_header,unprepare_header,write_header;

int mygames_win16_audio_reset(void)
{
    if(!device)return 0;
    if(reset_device(device)!=MMSYSERR_NOERROR)return 0;
    next=0U;return 1;
}
void mygames_win16_audio_close(void)
{
    unsigned short i;
    retry_pending=0U;
    if(device) {
        /* Never release memory still owned by a driver after a failed reset. */
        if(!mygames_win16_audio_reset())return;
        for(i=0U;i<prepared;++i)
            if((blocks[i].header.dwFlags&WHDR_PREPARED) &&
                unprepare_header(device,&blocks[i].header,sizeof(WAVEHDR))!=MMSYSERR_NOERROR)return;
        prepared=0U;
        if(close_device(device)!=MMSYSERR_NOERROR)return;
        device=0;
    }
    if(blocks){GlobalUnlock(memory);blocks=0;}
    if(memory){GlobalFree(memory);memory=0;}
    if(library){FreeLibrary(library);library=0;}
    next=prepared=0U;
}
int mygames_win16_audio_open(unsigned long sample_rate)
{
    PCMWAVEFORMAT format;
    unsigned short i,status;
    mygames_win16_audio_close();
    if(device || sample_rate==0UL)return 0;
    library=LoadLibrary("MMSYSTEM.DLL");
    if((UINT)library<32U){library=0;return 0;}
    open_device=(open_proc)GetProcAddress(library,"WAVEOUTOPEN");
    close_device=(device_proc)GetProcAddress(library,"WAVEOUTCLOSE");
    reset_device=(device_proc)GetProcAddress(library,"WAVEOUTRESET");
    prepare_header=(header_proc)GetProcAddress(library,"WAVEOUTPREPAREHEADER");
    unprepare_header=(header_proc)GetProcAddress(library,"WAVEOUTUNPREPAREHEADER");
    write_header=(header_proc)GetProcAddress(library,"WAVEOUTWRITE");
    if(!open_device || !close_device || !reset_device || !prepare_header ||
        !unprepare_header || !write_header){mygames_win16_audio_close();return 0;}
    memory=GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,(DWORD)(BLOCKS*sizeof(struct pcm_block)));
    blocks=memory?(struct pcm_block FAR *)GlobalLock(memory):0;
    if(!blocks){mygames_win16_audio_close();return 0;}
    memset(blocks,0,BLOCKS*sizeof(struct pcm_block));
    memset(&format,0,sizeof(format));
    format.wf.wFormatTag=WAVE_FORMAT_PCM;format.wf.nChannels=1U;
    format.wf.nSamplesPerSec=sample_rate;format.wf.nAvgBytesPerSec=sample_rate;
    format.wf.nBlockAlign=1U;format.wBitsPerSample=8U;
    status=open_device(&device,(UINT)WAVE_MAPPER,&format.wf,0L,0L,CALLBACK_NULL);
    if(status!=MMSYSERR_NOERROR) {
        device=0;mygames_win16_audio_close();
        /* Win3.x waveform drivers can be held briefly by startup sound.
         * Retry only transient device ownership, without blocking USER. */
        if(status==MMSYSERR_ALLOCATED) {
            retry_pending=1U;retry_rate=sample_rate;retry_stamp=GetTickCount();
        }
        return 0;
    }
    for(i=0U;i<BLOCKS;++i) {
        blocks[i].header.lpData=(LPSTR)blocks[i].samples;
        blocks[i].header.dwBufferLength=SAMPLES;
        if(prepare_header(device,&blocks[i].header,sizeof(WAVEHDR))!=MMSYSERR_NOERROR) {
            mygames_win16_audio_close();return 0;
        }
        ++prepared;
    }
    return 1;
}
int mygames_win16_audio_submit(const mygames_kvm_u8 *samples,mygames_kvm_u16 count)
{
    WAVEHDR FAR *header;
    if(!samples || !count || count>SAMPLES)return 0;
    if(!device && retry_pending && GetTickCount()-retry_stamp>=1000UL)
        (void)mygames_win16_audio_open(retry_rate);
    if(!device)return 0;
    header=&blocks[next].header;
    if(header->dwFlags&WHDR_INQUEUE)return 0;
    memcpy(blocks[next].samples,samples,count);header->dwBufferLength=count;
    if(write_header(device,header,sizeof(WAVEHDR))!=MMSYSERR_NOERROR)return 0;
    next=(unsigned short)((next+1U)%BLOCKS);return 1;
}
