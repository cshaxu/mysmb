#include <windows.h>
#include <mmsystem.h>
#include <string.h>
#include "win16/audio.h"
static unsigned char memory[8192];
static WAVEHDR *headers[8];
static DWORD stamp;
DWORD GetTickCount(void){return stamp;}
static unsigned fail,allocations,locks,libraries,opens,prepared,writes,closed,calls,open_calls,reenter;
static void entered(void){++calls;if(reenter){unsigned n=calls;mygames_win16_audio_service(stamp);if(calls!=n)fail=99;if(reenter==2)mygames_win16_audio_stop();}}
HINSTANCE LoadLibrary(const char *name){(void)name;if(fail==1)return 0;++libraries;return 64;}
void FreeLibrary(HINSTANCE library){(void)library;--libraries;}
HGLOBAL GlobalAlloc(UINT flags,DWORD size){(void)flags;if(fail==3 || size>sizeof(memory))return 0;++allocations;return memory;}
void *GlobalLock(HGLOBAL h){if(fail==4)return 0;++locks;return h;}
int GlobalUnlock(HGLOBAL h){(void)h;--locks;return 1;}
HGLOBAL GlobalFree(HGLOBAL h){(void)h;--allocations;return 0;}
static UINT open_device(HWAVEOUT *out,UINT id,const WAVEFORMAT *format,DWORD cb,DWORD instance,DWORD flags)
{entered();++open_calls;if(fail==11)return MMSYSERR_ALLOCATED;(void)id;(void)cb;(void)instance;(void)flags;if(fail==5 || format->nSamplesPerSec!=11025UL || format->nChannels!=1)return 1;*out=1;++opens;return 0;}
static UINT close_device(HWAVEOUT device){entered();(void)device;if(fail==10)return 1;--opens;++closed;return 0;}
static UINT reset_device(HWAVEOUT device){unsigned i;entered();(void)device;if(fail==8)return 1;for(i=0;i<prepared;++i)headers[i]->dwFlags&=~WHDR_INQUEUE;return 0;}
static UINT prepare(HWAVEOUT device,WAVEHDR *h,UINT size){entered();(void)device;(void)size;if(fail==6 && prepared==3)return 1;headers[prepared++]=h;h->dwFlags|=WHDR_PREPARED;return 0;}
static UINT unprepare(HWAVEOUT device,WAVEHDR *h,UINT size){entered();(void)device;(void)size;if((h->dwFlags&WHDR_INQUEUE) || (fail==9 && h==headers[3]))return 1;h->dwFlags&=~WHDR_PREPARED;return 0;}
static UINT write_header(HWAVEOUT device,WAVEHDR *h,UINT size){entered();(void)device;(void)size;if(fail==7)return 1;h->dwFlags|=WHDR_INQUEUE;++writes;return 0;}
FARPROC GetProcAddress(HINSTANCE library,const char *name)
{(void)library;if(fail==2)return 0;
#define PROC(n,p) if(!strcmp(name,n))return (FARPROC)p
PROC("WAVEOUTOPEN",open_device);PROC("WAVEOUTCLOSE",close_device);PROC("WAVEOUTRESET",reset_device);
PROC("WAVEOUTPREPAREHEADER",prepare);PROC("WAVEOUTUNPREPAREHEADER",unprepare);PROC("WAVEOUTWRITE",write_header);
#undef PROC
return 0;}

#define CHECK(c) do {if(!(c))return __LINE__;}while(0)
static int drive(int target)
{
    unsigned i,n;
    for(i=0;i<100;++i) {
        if(mygames_win16_audio_phase()==target)return 1;
        n=calls;stamp+=1000;mygames_win16_audio_service(stamp);
        if(calls-n>1)return 0;
    }
    return 0;
}
static int close_all(void)
{mygames_win16_audio_stop();return drive(MYGAMES_AUDIO_CLOSED) && !libraries && !allocations && !locks && !opens;}
int main(void)
{
    unsigned i,n;unsigned long id;unsigned char samples[184];memset(samples,42,sizeof(samples));
    CHECK(!mygames_win16_audio_submit(samples,184));
    CHECK(!mygames_win16_audio_begin(0,184,8,3,1000));
    CHECK(!mygames_win16_audio_begin(11025,65535,8,3,1000));
    for(fail=1;fail<=6;++fail) {
        prepared=0;CHECK(mygames_win16_audio_begin(11025,184,8,3,1000));
        CHECK(drive(MYGAMES_AUDIO_FAILED));CHECK(!libraries && !allocations && !locks && !opens);
    }
    fail=0;prepared=0;reenter=1;
    CHECK(mygames_win16_audio_begin(11025,184,8,3,1000));CHECK(drive(MYGAMES_AUDIO_READY));
    CHECK(prepared==8 && fail==0);reenter=0;
    CHECK(!mygames_win16_audio_submit(0,1) && !mygames_win16_audio_submit(samples,0) && !mygames_win16_audio_submit(samples,185));
    for(i=0;i<8;++i)CHECK(mygames_win16_audio_submit(samples,183)==183);
    CHECK(writes==8 && headers[0]->dwBufferLength==183 && !memcmp(headers[0]->lpData,samples,183));
    CHECK(!mygames_win16_audio_submit(samples,184));
    id=mygames_win16_audio_reset();CHECK(id && mygames_win16_audio_reset()==id);
    CHECK(!mygames_win16_audio_submit(samples,184));
    mygames_win16_audio_service(stamp);CHECK(mygames_win16_audio_reset_result(id)==MYGAMES_AUDIO_OK);
    CHECK(mygames_win16_audio_submit(samples,184)==184);
    fail=8;id=mygames_win16_audio_reset();mygames_win16_audio_service(stamp);
    CHECK(mygames_win16_audio_reset_result(id)==MYGAMES_AUDIO_ERROR && allocations && opens);
    mygames_win16_audio_stop();CHECK(drive(MYGAMES_AUDIO_CLEANUP_FAILED));
    n=calls;for(i=0;i<10;++i)mygames_win16_audio_service(stamp+=1000);CHECK(n==calls);
    CHECK(allocations && opens);fail=9;mygames_win16_audio_retry_cleanup();CHECK(drive(MYGAMES_AUDIO_CLEANUP_FAILED));
    CHECK(allocations && opens);fail=10;mygames_win16_audio_retry_cleanup();CHECK(drive(MYGAMES_AUDIO_CLEANUP_FAILED));
    CHECK(allocations && opens);fail=0;mygames_win16_audio_retry_cleanup();CHECK(close_all());
    /* Write failure is terminal for submission, not an endlessly retried block. */
    prepared=0;CHECK(mygames_win16_audio_begin(11025,184,8,3,1000));CHECK(drive(MYGAMES_AUDIO_READY));
    fail=7;CHECK(!mygames_win16_audio_submit(samples,184));CHECK(mygames_win16_audio_phase()==MYGAMES_AUDIO_FAILED);
    n=calls;CHECK(!mygames_win16_audio_submit(samples,184) && calls==n);fail=0;CHECK(close_all());
    /* Exactly three busy attempts; submit never retries and stop cancels delay. */
    fail=11;open_calls=0;stamp=100;CHECK(mygames_win16_audio_begin(11025,184,8,3,1000));
    mygames_win16_audio_service(stamp);CHECK(open_calls==1);
    mygames_win16_audio_service(1099);CHECK(open_calls==1);
    CHECK(!mygames_win16_audio_submit(samples,184) && open_calls==1);
    stamp=1100;mygames_win16_audio_service(stamp);CHECK(open_calls==2);
    stamp=2100;mygames_win16_audio_service(stamp);CHECK(open_calls==3 && mygames_win16_audio_phase()==MYGAMES_AUDIO_FAILED);
    CHECK(close_all());CHECK(mygames_win16_audio_begin(11025,184,8,3,1000));mygames_win16_audio_service(stamp);
    mygames_win16_audio_stop();CHECK(close_all());CHECK(open_calls==4);
    fail=11;prepared=0;CHECK(mygames_win16_audio_begin(11025,184,8,3,1000));
    mygames_win16_audio_service(stamp);fail=0;CHECK(drive(MYGAMES_AUDIO_READY));CHECK(close_all());
    /* Reentrant stop during open and partial preparation cannot resurrect ready. */
    fail=0;prepared=0;reenter=2;CHECK(mygames_win16_audio_begin(11025,184,8,3,1000));
    mygames_win16_audio_service(stamp);reenter=0;CHECK(mygames_win16_audio_phase()==MYGAMES_AUDIO_STOPPING);CHECK(close_all());
    prepared=0;CHECK(mygames_win16_audio_begin(11025,184,8,3,1000));
    mygames_win16_audio_service(stamp);reenter=2;mygames_win16_audio_service(stamp);reenter=0;
    CHECK(mygames_win16_audio_phase()==MYGAMES_AUDIO_STOPPING);CHECK(close_all());
    /* Caller controls retry policy; timestamp subtraction survives wrap. */
    fail=11;stamp=0xfffffff0UL;CHECK(mygames_win16_audio_begin(11025,184,8,3,1000));
    mygames_win16_audio_service(stamp);n=open_calls;mygames_win16_audio_service(stamp+999UL);CHECK(open_calls==n);
    mygames_win16_audio_service(stamp+1000UL);CHECK(open_calls==n+1);CHECK(close_all());
    n=calls;mygames_win16_audio_service(stamp);CHECK(calls==n && mygames_win16_audio_phase()==MYGAMES_AUDIO_CLOSED);
    fail=0;id=mygames_win16_audio_reset();CHECK(!id); /* stopped means stop, not reset */
    return 0;
}
