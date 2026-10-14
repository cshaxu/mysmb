#include <windows.h>
#include <mmsystem.h>
#include "win16/memory.h"
#include "win16/audio.h"
struct pcm_block { WAVEHDR header; unsigned char samples[1]; };
typedef UINT (WINAPI *open_proc)(HWAVEOUT FAR *,UINT,const WAVEFORMAT FAR *,DWORD,DWORD,DWORD);
typedef UINT (WINAPI *device_proc)(HWAVEOUT);
typedef UINT (WINAPI *header_proc)(HWAVEOUT,WAVEHDR FAR *,UINT);
static HINSTANCE library;
static HWAVEOUT device;
static HGLOBAL memory;
static unsigned char FAR *blocks;
static unsigned short block_count,block_samples,block_stride,prepared,next;
static unsigned short attempts,limit,cleanup_attempts,error;
static unsigned long rate,delay,stamp,request,done;
static int phase,busy,stopping,step,retry_wait,failed,result;
static open_proc open_device;
static device_proc close_device,reset_device;
static header_proc prepare_header,unprepare_header,write_header;
static struct pcm_block FAR *block(unsigned short index)
{return (struct pcm_block FAR *)(blocks+(unsigned long)index*block_stride);}
static void free_storage(void)
{
    if(blocks){GlobalUnlock(memory);blocks=0;}
    if(memory){GlobalFree(memory);memory=0;}
    if(library){FreeLibrary(library);library=0;}
    prepared=next=0;
}
static int allocate_storage(void)
{
    library=LoadLibrary("MMSYSTEM.DLL");
    if((UINT)library<32U){library=0;return 0;}
    open_device=(open_proc)GetProcAddress(library,"WAVEOUTOPEN");
    close_device=(device_proc)GetProcAddress(library,"WAVEOUTCLOSE");
    reset_device=(device_proc)GetProcAddress(library,"WAVEOUTRESET");
    prepare_header=(header_proc)GetProcAddress(library,"WAVEOUTPREPAREHEADER");
    unprepare_header=(header_proc)GetProcAddress(library,"WAVEOUTUNPREPAREHEADER");
    write_header=(header_proc)GetProcAddress(library,"WAVEOUTWRITE");
    if(!open_device || !close_device || !reset_device || !prepare_header ||
        !unprepare_header || !write_header)return 0;
    memory=GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,(unsigned long)block_stride*block_count);
    blocks=memory?(unsigned char FAR *)GlobalLock(memory):0;
    if(!blocks)return 0;
    mygames_win16_zero(blocks,0,(unsigned short)(block_stride*block_count));return 1;
}
int mygames_win16_audio_begin(unsigned long sample_rate,mygames_kvm_u16 samples,
    mygames_kvm_u16 count,mygames_kvm_u16 tries,unsigned long retry_ms)
{
    unsigned long stride;
    if(busy || device || library || (phase!=MYGAMES_AUDIO_CLOSED && phase!=MYGAMES_AUDIO_FAILED) ||
       !sample_rate || sample_rate>192000UL || !samples || !count || count>256U || !tries)return 0;
    stride=((unsigned long)sizeof(WAVEHDR)+samples+1UL)&~1UL;
    if(stride*count>65520UL)return 0;
    rate=sample_rate;block_samples=samples;block_count=count;block_stride=(unsigned short)stride;
    limit=tries;delay=retry_ms;attempts=cleanup_attempts=error=prepared=next=0;
    stopping=failed=retry_wait=step=0;done=request;result=MYGAMES_AUDIO_OK;
    phase=MYGAMES_AUDIO_OPENING;return 1;
}
int mygames_win16_audio_phase(void){return phase;}
mygames_kvm_u16 mygames_win16_audio_error(void){return error;}
unsigned long mygames_win16_audio_reset(void)
{
    if(stopping)return 0;
    if(done==request){++request;if(!request)++request;}
    return request;
}
int mygames_win16_audio_reset_result(unsigned long id)
{
    if(!id || stopping)return MYGAMES_AUDIO_ERROR;
    return id==done?result:MYGAMES_AUDIO_PENDING;
}
void mygames_win16_audio_stop(void)
{
    if(stopping || phase==MYGAMES_AUDIO_CLOSED)return;
    stopping=1;retry_wait=0;cleanup_attempts=0;step=0;
    phase=MYGAMES_AUDIO_STOPPING;
}
void mygames_win16_audio_retry_cleanup(void)
{
    if(phase==MYGAMES_AUDIO_CLEANUP_FAILED) {
        cleanup_attempts=0;retry_wait=0;phase=MYGAMES_AUDIO_STOPPING;
    }
}
static void cleanup(unsigned long now)
{
    if(!device){free_storage();phase=failed && !stopping?MYGAMES_AUDIO_FAILED:MYGAMES_AUDIO_CLOSED;return;}
    if(step==0) {
        error=reset_device(device);
        if(!error){step=1;next=0;}
    } else if(prepared) {
        error=unprepare_header(device,&block(prepared-1U)->header,sizeof(WAVEHDR));
        if(!error)--prepared;
    } else {
        error=close_device(device);
        if(!error){device=0;free_storage();phase=failed && !stopping?MYGAMES_AUDIO_FAILED:MYGAMES_AUDIO_CLOSED;}
    }
    if(error) {
        if(++cleanup_attempts>=limit)phase=MYGAMES_AUDIO_CLEANUP_FAILED;
        else {retry_wait=1;stamp=now;}
    }
}
void mygames_win16_audio_service(unsigned long now)
{
    PCMWAVEFORMAT format;
    WAVEHDR FAR *header;
    if(busy)return;
    busy=1;
    if(retry_wait) {
        if(now-stamp<delay){busy=0;return;}
        retry_wait=0;
    }
    if(phase==MYGAMES_AUDIO_STOPPING)cleanup(now);
    else if(phase==MYGAMES_AUDIO_OPENING) {
        if(!library && !allocate_storage()) {
            error=1;free_storage();phase=stopping?MYGAMES_AUDIO_CLOSED:MYGAMES_AUDIO_FAILED;
        } else if(!stopping && !device) {
            memset(&format,0,sizeof(format));
            format.wf.wFormatTag=WAVE_FORMAT_PCM;format.wf.nChannels=1U;
            format.wf.nSamplesPerSec=rate;format.wf.nAvgBytesPerSec=rate;
            format.wf.nBlockAlign=1U;format.wBitsPerSample=8U;
            ++attempts;error=open_device(&device,(UINT)WAVE_MAPPER,&format.wf,0L,0L,CALLBACK_NULL);
            if(error) {
                device=0;
                if(!stopping && error==MMSYSERR_ALLOCATED && attempts<limit){retry_wait=1;stamp=now;}
                else {free_storage();phase=stopping?MYGAMES_AUDIO_CLOSED:MYGAMES_AUDIO_FAILED;}
            }
        } else if(!stopping) {
            header=&block(prepared)->header;header->lpData=(LPSTR)block(prepared)->samples;
            header->dwBufferLength=block_samples;
            error=prepare_header(device,header,sizeof(WAVEHDR));
            if(!error){++prepared;if(!stopping && prepared==block_count)phase=MYGAMES_AUDIO_READY;}
            else {failed=1;step=0;phase=MYGAMES_AUDIO_STOPPING;}
        }
    } else if(!stopping && request!=done && phase!=MYGAMES_AUDIO_CLEANUP_FAILED) {
        phase=MYGAMES_AUDIO_RESETTING;
        error=device?reset_device(device):0;
        result=error?MYGAMES_AUDIO_ERROR:MYGAMES_AUDIO_OK;done=request;
        if(!stopping){phase=error || !device?MYGAMES_AUDIO_FAILED:MYGAMES_AUDIO_READY;if(!error)next=0;}
    }
    busy=0;
}
mygames_kvm_u16 mygames_win16_audio_submit(const mygames_kvm_u8 MYGAMES_KVM_FAR *samples,mygames_kvm_u16 count)
{
    WAVEHDR FAR *header;
    if(busy || stopping || request!=done || phase!=MYGAMES_AUDIO_READY ||
       !samples || !count || count>block_samples)return 0;
    header=&block(next)->header;
    if(header->dwFlags&WHDR_INQUEUE)return 0;
    busy=1;mygames_win16_copy(block(next)->samples,samples,count);header->dwBufferLength=count;
    error=write_header(device,header,sizeof(WAVEHDR));
    if(!error)next=(unsigned short)((next+1U)%block_count);
    else if(!stopping)phase=MYGAMES_AUDIO_FAILED;
    busy=0;return error?0:count;
}
