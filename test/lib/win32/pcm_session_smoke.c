#include "win32/pcm_session.h"
#include <string.h>
static HANDLE entered,resume_call,completion;
static volatile LONG hold,fail,calls[7],thread_id,bad_thread;
static WAVEHDR *headers[8];
static unsigned prepared;
static unsigned char written[64];
static unsigned resource_call,resource_fail,live_memory,live_handles;
static void *resource_allocate(SIZE_T n)
{void *p;if(++resource_call==resource_fail)return NULL;p=HeapAlloc(GetProcessHeap(),0,n);if(p)++live_memory;return p;}
static void resource_free(void *p){--live_memory;HeapFree(GetProcessHeap(),0,p);}
static HANDLE resource_event(void)
{HANDLE h;if(++resource_call==resource_fail)return NULL;h=CreateEvent(NULL,FALSE,FALSE,NULL);if(h)++live_handles;return h;}
static HANDLE resource_thread(LPTHREAD_START_ROUTINE proc,void *p)
{HANDLE h;if(++resource_call==resource_fail)return NULL;h=CreateThread(NULL,0,proc,p,0,NULL);if(h)++live_handles;return h;}
static void resource_close(HANDLE h){--live_handles;CloseHandle(h);}
static const struct mygames_win32_pcm_resources resources={resource_allocate,resource_free,resource_event,resource_thread,resource_close};
static int gate(int operation)
{
    LONG id=(LONG)GetCurrentThreadId();
    if(!InterlockedCompareExchange(&thread_id,id,0)){} else if(thread_id!=id)bad_thread=1;
    InterlockedIncrement(&calls[operation]);
    if(InterlockedCompareExchange(&hold,0,0)==operation) {
        SetEvent(entered);WaitForSingleObject(resume_call,INFINITE);
    }
    return InterlockedCompareExchange(&fail,0,0)==operation;
}
static MMRESULT WINAPI open_device(LPHWAVEOUT out,UINT id,LPCWAVEFORMATEX format,DWORD_PTR cb,DWORD_PTR context,DWORD flags)
{
    (void)id;(void)format;(void)context;
    completion=(HANDLE)cb;
    if(flags!=CALLBACK_EVENT || gate(1))return 1;
    *out=(HWAVEOUT)1;return 0;
}
static MMRESULT WINAPI prepare(HWAVEOUT d,LPWAVEHDR h,UINT size)
{(void)d;(void)size;if(gate(2))return 1;headers[prepared++]=h;h->dwFlags=WHDR_PREPARED;return 0;}
static MMRESULT WINAPI write_pcm(HWAVEOUT d,LPWAVEHDR h,UINT size)
{
    (void)d;(void)size;
    if(gate(3))return 1;
    written[calls[3]-1]=(unsigned char)h->lpData[0];
    h->dwFlags=WHDR_PREPARED|WHDR_DONE;SetEvent(completion);return 0;
}
static MMRESULT WINAPI reset(HWAVEOUT d)
{unsigned i;(void)d;if(gate(4))return 1;for(i=0;i<prepared;++i)headers[i]->dwFlags=WHDR_PREPARED|WHDR_DONE;return 0;}
static MMRESULT WINAPI unprepare(HWAVEOUT d,LPWAVEHDR h,UINT size)
{(void)d;(void)size;if(gate(5))return 1;h->dwFlags=0;return 0;}
static MMRESULT WINAPI close_device(HWAVEOUT d)
{(void)d;return gate(6)?1:0;}
static const struct mygames_win32_pcm_api api={open_device,prepare,write_pcm,reset,unprepare,close_device};
static int wait_phase(struct mygames_win32_pcm_session *s,int expected)
{
    DWORD started=GetTickCount();
    while(mygames_win32_pcm_session_phase(s)!=expected) {
        if(GetTickCount()-started>2000U)return 0;
        Sleep(1);
    }
    return 1;
}
static int release_session(struct mygames_win32_pcm_session **s)
{
    DWORD started=GetTickCount();
    mygames_win32_pcm_session_stop(*s);
    while(!mygames_win32_pcm_session_release(s)) {
        if(GetTickCount()-started>2000U)return 0;
        Sleep(1);
    }
    return 1;
}
static void initialize(int operation)
{
    memset((void *)calls,0,sizeof(calls));memset(headers,0,sizeof(headers));
    hold=operation;fail=0;thread_id=bad_thread=0;prepared=0;
    ResetEvent(entered);ResetEvent(resume_call);
}
int main(void)
{
    struct mygames_win32_pcm_session *s=NULL;
    unsigned char *samples;
    int operation,slot,i;
    LONG request;
    DWORD start;
    entered=CreateEvent(NULL,TRUE,FALSE,NULL);resume_call=CreateEvent(NULL,TRUE,FALSE,NULL);
    if(!entered || !resume_call)return 1;
    for(resource_fail=1;resource_fail<=9;++resource_fail) {
        resource_call=0;
        if(mygames_win32_pcm_session_begin_with_resources(8000,8,8,8,&api,&resources) ||
           live_memory || live_handles)return 32;
    }
    if(mygames_win32_pcm_session_begin(0,8,8,8,&api) ||
        mygames_win32_pcm_session_begin(8000,16,8,3,&api) ||
        !mygames_win32_pcm_session_release(&s))return 2;
    for(operation=1;operation<=6;++operation) {
        initialize(operation);
        s=mygames_win32_pcm_session_begin(8000,8,8,8,&api);if(!s)return 3;
        if(operation>=3) {
            if(!wait_phase(s,MYGAMES_AUDIO_READY))return 4;
            if(operation==3) {
                samples=mygames_win32_pcm_session_acquire(s,&slot);if(!samples)return 5;
                memset(samples,42,8);mygames_win32_pcm_session_publish(s,slot);
            } else if(operation==4)mygames_win32_pcm_session_reset(s);
            else mygames_win32_pcm_session_stop(s);
        }
        if(WaitForSingleObject(entered,2000)!=WAIT_OBJECT_0)return 6;
        start=GetTickCount();
        /* Producer/status/stop remain usable while each possible driver call
         * is held. Stop priority also covers late open/prepare success. */
        for(i=0;i<1000;++i) {
            (void)mygames_win32_pcm_session_phase(s);
            mygames_win32_pcm_session_stop(s);
            if(mygames_win32_pcm_session_release(&s))return 7;
        }
        if(GetTickCount()-start>=1000U || !mygames_win32_pcm_session_stalled(s,0))return 8;
        SetEvent(resume_call);
        if(!release_session(&s) || bad_thread)return 9;
    }
    initialize(3);s=mygames_win32_pcm_session_begin(8000,8,8,8,&api);
    if(!s || !wait_phase(s,MYGAMES_AUDIO_READY))return 10;
    for(i=0;i<8;++i) {
        samples=mygames_win32_pcm_session_acquire(s,&slot);if(!samples)return 11;
        samples[0]=(unsigned char)i;mygames_win32_pcm_session_publish(s,slot);
    }
    if(WaitForSingleObject(entered,2000)!=WAIT_OBJECT_0 || mygames_win32_pcm_session_acquire(s,&slot))return 12;
    request=mygames_win32_pcm_session_reset(s);
    if(request!=mygames_win32_pcm_session_reset(s) ||
        mygames_win32_pcm_session_reset_result(s,request)!=MYGAMES_AUDIO_PENDING)return 13;
    SetEvent(resume_call);
    start=GetTickCount();
    while(mygames_win32_pcm_session_reset_result(s,request)==MYGAMES_AUDIO_PENDING) {
        if(GetTickCount()-start>2000U)return 14;
        Sleep(1);
    }
    if(mygames_win32_pcm_session_reset_result(s,request)!=MYGAMES_AUDIO_OK || calls[3]!=1)return 15;
    if(!wait_phase(s,MYGAMES_AUDIO_READY))return 16;
    samples=mygames_win32_pcm_session_acquire(s,&slot);if(!samples)return 17;
    mygames_win32_pcm_session_stop(s);
    Sleep(5);
    if(mygames_win32_pcm_session_release(&s))return 18;
    mygames_win32_pcm_session_publish(s,slot);
    if(!release_session(&s))return 19;
    for(operation=1;operation<=6;++operation) {
        initialize(0);fail=operation;
        s=mygames_win32_pcm_session_begin(8000,8,8,8,&api);if(!s)return 20;
        if(operation<=2) {if(!wait_phase(s,MYGAMES_AUDIO_FAILED))return 21;}
        else {
            if(!wait_phase(s,MYGAMES_AUDIO_READY))return 22;
            if(operation==3) {
                samples=mygames_win32_pcm_session_acquire(s,&slot);if(!samples)return 23;
                mygames_win32_pcm_session_publish(s,slot);
                if(!wait_phase(s,MYGAMES_AUDIO_FAILED))return 24;
            } else {
                mygames_win32_pcm_session_stop(s);
                if(!wait_phase(s,MYGAMES_AUDIO_CLEANUP_FAILED) || mygames_win32_pcm_session_release(&s))return 25;
            }
        }
        fail=0;
        if(!release_session(&s) || bad_thread)return 26;
    }
    initialize(0);s=mygames_win32_pcm_session_begin(8000,8,8,8,&api);
    if(!s || !wait_phase(s,MYGAMES_AUDIO_READY))return 27;
    /* More than two ring wraps exercise publication order and coalesced events. */
    for(i=0;i<24;++i) {
        start=GetTickCount();
        while(!(samples=mygames_win32_pcm_session_acquire(s,&slot))) {
            if(GetTickCount()-start>2000U)return 28;
            Sleep(1);
        }
        samples[0]=(unsigned char)i;mygames_win32_pcm_session_publish(s,slot);
    }
    start=GetTickCount();
    while(calls[3]<24){if(GetTickCount()-start>2000U)return 29;Sleep(1);}
    if(!release_session(&s))return 30;
    for(i=0;i<24;++i)if(written[i]!=(unsigned char)i)return 31;
    CloseHandle(entered);CloseHandle(resume_call);return 0;
}
