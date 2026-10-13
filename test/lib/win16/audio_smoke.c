#include <windows.h>
#include <mmsystem.h>
#include <string.h>
#include "win16/audio.h"
static unsigned char memory[8192];
static WAVEHDR *headers[8];
static DWORD stamp;
DWORD GetTickCount(void){return stamp;}
static unsigned fail,allocations,locks,libraries,opens,prepared,writes,closed;
HINSTANCE LoadLibrary(const char *name){(void)name;if(fail==1)return 0;++libraries;return 64;}
void FreeLibrary(HINSTANCE library){(void)library;--libraries;}
HGLOBAL GlobalAlloc(UINT flags,DWORD size){(void)flags;if(fail==3 || size>sizeof(memory))return 0;++allocations;return memory;}
void *GlobalLock(HGLOBAL h){if(fail==4)return 0;++locks;return h;}
int GlobalUnlock(HGLOBAL h){(void)h;--locks;return 1;}
HGLOBAL GlobalFree(HGLOBAL h){(void)h;--allocations;return 0;}
static UINT open_device(HWAVEOUT *out,UINT id,const WAVEFORMAT *format,DWORD cb,DWORD instance,DWORD flags)
{if(fail==11)return MMSYSERR_ALLOCATED;(void)id;(void)cb;(void)instance;(void)flags;if(fail==5 || format->nSamplesPerSec!=11025UL || format->nChannels!=1)return 1;*out=1;++opens;return 0;}
static UINT close_device(HWAVEOUT device){(void)device;if(fail==10)return 1;--opens;++closed;return 0;}
static UINT reset_device(HWAVEOUT device){unsigned i;(void)device;if(fail==8)return 1;for(i=0;i<prepared;++i)headers[i]->dwFlags&=~WHDR_INQUEUE;return 0;}
static UINT prepare(HWAVEOUT device,WAVEHDR *h,UINT size){(void)device;(void)size;if(fail==6 && prepared==3)return 1;headers[prepared++]=h;h->dwFlags|=WHDR_PREPARED;return 0;}
static UINT unprepare(HWAVEOUT device,WAVEHDR *h,UINT size){(void)device;(void)size;if((h->dwFlags&WHDR_INQUEUE) || (fail==9 && h==headers[3]))return 1;h->dwFlags&=~WHDR_PREPARED;return 0;}
static UINT write_header(HWAVEOUT device,WAVEHDR *h,UINT size){(void)device;(void)size;if(fail==7)return 1;h->dwFlags|=WHDR_INQUEUE;++writes;return 0;}
FARPROC GetProcAddress(HINSTANCE library,const char *name)
{(void)library;if(fail==2)return 0;
#define PROC(n,p) if(!strcmp(name,n))return (FARPROC)p
PROC("WAVEOUTOPEN",open_device);PROC("WAVEOUTCLOSE",close_device);PROC("WAVEOUTRESET",reset_device);
PROC("WAVEOUTPREPAREHEADER",prepare);PROC("WAVEOUTUNPREPAREHEADER",unprepare);PROC("WAVEOUTWRITE",write_header);
#undef PROC
return 0;}
int main(void)
{
    unsigned i;unsigned char samples[184];memset(samples,42,sizeof(samples));
    if(mygames_win16_audio_submit(samples,184) || mygames_win16_audio_reset())return 1;
    for(fail=1;fail<=6;++fail){prepared=0;if(mygames_win16_audio_open(11025UL,184U,8U) || libraries || allocations || locks || opens)return 2;}
    fail=0;prepared=0;
    if(mygames_win16_audio_open(0UL,184U,8U) || !mygames_win16_audio_open(11025UL,184U,8U) || prepared!=8)return 3;
    if(mygames_win16_audio_submit(0,1) || mygames_win16_audio_submit(samples,0) || mygames_win16_audio_submit(samples,185))return 4;
    fail=7;if(mygames_win16_audio_submit(samples,183))return 5;fail=0;
    for(i=0;i<8;++i)if(!mygames_win16_audio_submit(samples,183))return 6;
    if(writes!=8 || headers[0]->dwBufferLength!=183 || memcmp(headers[0]->lpData,samples,183) || mygames_win16_audio_submit(samples,184))return 7;
    fail=8;mygames_win16_audio_close();if(!allocations || !opens)return 8;
    fail=0;if(!mygames_win16_audio_reset() || !mygames_win16_audio_submit(samples,184))return 9;
    fail=9;mygames_win16_audio_close();if(!allocations || !opens || mygames_win16_audio_submit(samples,184))return 10;
    fail=10;mygames_win16_audio_close();if(!allocations || !opens)return 11;
    fail=0;mygames_win16_audio_close();mygames_win16_audio_close();
    if(libraries || allocations || locks || opens || !closed)return 12;
    prepared=0;fail=11;stamp=100;
    if(mygames_win16_audio_open(11025UL,184U,8U) || allocations || opens)return 13;
    fail=0;stamp=1099;if(mygames_win16_audio_submit(samples,184) || opens)return 14;
    stamp=1100;if(!mygames_win16_audio_submit(samples,184) || !opens)return 15;
    mygames_win16_audio_close();
    prepared=0;
    if(mygames_win16_audio_open(11025UL,65535U,8U) ||
        !mygames_win16_audio_open(11025UL,256U,3U) || prepared!=3)return 16;
    if(!mygames_win16_audio_submit(samples,184))return 17;
    mygames_win16_audio_close();
    return libraries || allocations || locks || opens;
}
