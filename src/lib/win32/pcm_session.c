#include "win32/pcm_session.h"
enum { SLOT_FREE, SLOT_FILLING, SLOT_READY, SLOT_DRIVER };
struct mygames_win32_pcm_session {
    struct mygames_win32_pcm pcm;
    struct mygames_win32_pcm_api api;
    const struct mygames_win32_pcm_api *binding;
    struct mygames_win32_pcm_resources resources;
    HANDLE thread,wake,completion;
    WAVEHDR *headers;
    unsigned char *queued,*samples;
    volatile LONG *slots;
    DWORD *order;
    DWORD sequence;
    volatile LONG phase,stop,request,done,result,calling,started,error;
    unsigned long rate;
    unsigned short bits,count,bytes,producer;
};
static void *allocate(SIZE_T size){return HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,size);}
static void free_memory(void *data){HeapFree(GetProcessHeap(),0,data);}
static HANDLE event(void){return CreateEvent(NULL,FALSE,FALSE,NULL);}
static HANDLE thread(LPTHREAD_START_ROUTINE proc,void *context){return CreateThread(NULL,0,proc,context,0,NULL);}
static void close_handle(HANDLE handle){CloseHandle(handle);}
static const struct mygames_win32_pcm_resources system_resources={allocate,free_memory,event,thread,close_handle};
static LONG read_long(volatile LONG *value)
{return InterlockedCompareExchange(value,0,0);}
static void phase(struct mygames_win32_pcm_session *s,int value)
{InterlockedExchange(&s->phase,value);}
static void call_begin(struct mygames_win32_pcm_session *s)
{
    InterlockedExchange(&s->started,(LONG)GetTickCount());
    InterlockedExchange(&s->calling,1);
}
static void call_end(struct mygames_win32_pcm_session *s)
{InterlockedExchange(&s->error,(LONG)s->pcm.result);InterlockedExchange(&s->calling,0);}
static void discard_ready(struct mygames_win32_pcm_session *s)
{
    unsigned short i;
    for(i=0;i<s->count;++i) {
        /* Filling storage belongs to the producer until publish. */
        if(read_long(&s->slots[i])!=SLOT_FILLING)
            InterlockedExchange(&s->slots[i],SLOT_FREE);
    }
}
static int producer_busy(struct mygames_win32_pcm_session *s)
{
    unsigned short i;
    for(i=0;i<s->count;++i)if(read_long(&s->slots[i])==SLOT_FILLING)return 1;
    return 0;
}
static DWORD WINAPI run(void *context)
{
    struct mygames_win32_pcm_session *s=context;
    HANDLE events[2];
    LONG request;
    int ready,ok,selected;
    unsigned short i,pass;
    DWORD last=0,delta,best;
    events[0]=s->wake;events[1]=s->completion;
    call_begin(s);
    ready=mygames_win32_pcm_open_event(&s->pcm,s->rate,1,s->bits,
        s->headers,s->queued,s->samples,s->count,s->bytes,s->binding,s->completion);
    call_end(s);
    phase(s,read_long(&s->stop)?MYGAMES_AUDIO_STOPPING:
        (ready?MYGAMES_AUDIO_READY:MYGAMES_AUDIO_FAILED));
    for(;;) {
        if(read_long(&s->stop)) {
            phase(s,MYGAMES_AUDIO_STOPPING);
            if(producer_busy(s)) {WaitForSingleObject(s->wake,INFINITE);continue;}
            call_begin(s);ok=mygames_win32_pcm_close(&s->pcm);call_end(s);
            if(ok){phase(s,MYGAMES_AUDIO_CLOSED);return 0;}
            phase(s,MYGAMES_AUDIO_CLEANUP_FAILED);
            /* Only an explicit subsequent stop retries failed cleanup. */
            WaitForSingleObject(s->wake,INFINITE);continue;
        }
        request=read_long(&s->request);
        if(request!=read_long(&s->done)) {
            phase(s,MYGAMES_AUDIO_RESETTING);
            if(producer_busy(s)){WaitForSingleObject(s->wake,INFINITE);continue;}
            call_begin(s);ok=mygames_win32_pcm_reset(&s->pcm);call_end(s);
            if(ok)discard_ready(s);
            else ready=0;
            InterlockedExchange(&s->result,ok?MYGAMES_AUDIO_OK:MYGAMES_AUDIO_ERROR);
            InterlockedExchange(&s->done,request);
            phase(s,ready?MYGAMES_AUDIO_READY:MYGAMES_AUDIO_FAILED);
            continue;
        }
        if(ready)for(pass=0;pass<s->count;++pass) {
            if(read_long(&s->stop) || read_long(&s->request)!=read_long(&s->done))break;
            selected=-1;best=MAXDWORD;
            for(i=0;i<s->count;++i) {
                if(read_long(&s->slots[i])==SLOT_DRIVER && (s->headers[i].dwFlags&WHDR_DONE))
                    InterlockedExchange(&s->slots[i],SLOT_FREE);
                if(read_long(&s->slots[i])==SLOT_READY) {
                    delta=s->order[i]-last;
                    if(delta<best){selected=i;best=delta;}
                }
            }
            if(selected>=0) {
                i=(unsigned short)selected;
                call_begin(s);ok=mygames_win32_pcm_submit(&s->pcm,i);call_end(s);
                if(ok){last=s->order[i];InterlockedExchange(&s->slots[i],SLOT_DRIVER);}
                else {phase(s,MYGAMES_AUDIO_FAILED);ready=0;break;}
            } else break;
        }
        WaitForMultipleObjects(2,events,FALSE,INFINITE);
    }
}
static void destroy(struct mygames_win32_pcm_session *s)
{
    if(s->thread)s->resources.close(s->thread);
    if(s->wake)s->resources.close(s->wake);
    if(s->completion)s->resources.close(s->completion);
    if(s->headers)s->resources.free(s->headers);
    if(s->queued)s->resources.free(s->queued);
    if(s->samples)s->resources.free(s->samples);
    if(s->slots)s->resources.free((void *)s->slots);
    if(s->order)s->resources.free(s->order);
    s->resources.free(s);
}
struct mygames_win32_pcm_session *mygames_win32_pcm_session_begin_with_resources(
 unsigned long rate,unsigned short bits,unsigned short count,unsigned short bytes,
 const struct mygames_win32_pcm_api *api,const struct mygames_win32_pcm_resources *resources)
{
    struct mygames_win32_pcm_session *s;
    if(!count || count>256U || !bytes || !rate || rate>192000UL ||
       (bits!=8U && bits!=16U) || bytes%(bits/8U))return NULL;
    if(api && (!api->open || !api->prepare || !api->write || !api->reset ||
        !api->unprepare || !api->close))return NULL;
    if(!resources)resources=&system_resources;
    if(!resources->allocate || !resources->free || !resources->event ||
        !resources->thread || !resources->close)return NULL;
    s=resources->allocate(sizeof(*s));
    if(!s)return NULL;
    ZeroMemory(s,sizeof(*s));s->resources=*resources;
    s->rate=rate;s->bits=bits;s->count=count;s->bytes=bytes;
    if(api){s->api=*api;s->binding=&s->api;}
    s->headers=resources->allocate(count*sizeof(WAVEHDR));
    s->queued=resources->allocate(count);
    s->samples=resources->allocate((SIZE_T)count*bytes);
    s->slots=resources->allocate(count*sizeof(LONG));
    s->order=resources->allocate(count*sizeof(DWORD));
    s->wake=resources->event();
    s->completion=resources->event();
    if(!s->headers || !s->queued || !s->samples || !s->slots || !s->order || !s->wake || !s->completion){destroy(s);return NULL;}
    ZeroMemory((void *)s->slots,count*sizeof(LONG));
    phase(s,MYGAMES_AUDIO_OPENING);
    s->thread=resources->thread(run,s);
    if(!s->thread){destroy(s);return NULL;}
    return s;
}
struct mygames_win32_pcm_session *mygames_win32_pcm_session_begin(
 unsigned long rate,unsigned short bits,unsigned short count,unsigned short bytes,
 const struct mygames_win32_pcm_api *api)
{return mygames_win32_pcm_session_begin_with_resources(rate,bits,count,bytes,api,NULL);}
int mygames_win32_pcm_session_phase(struct mygames_win32_pcm_session *s)
{return s?(int)read_long(&s->phase):MYGAMES_AUDIO_CLOSED;}
MMRESULT mygames_win32_pcm_session_error(struct mygames_win32_pcm_session *s)
{return s?(MMRESULT)read_long(&s->error):MMSYSERR_NOERROR;}
int mygames_win32_pcm_session_stalled(struct mygames_win32_pcm_session *s,DWORD budget)
{return s && read_long(&s->calling) && (DWORD)(GetTickCount()-(DWORD)read_long(&s->started))>=budget;}
void *mygames_win32_pcm_session_acquire(struct mygames_win32_pcm_session *s,int *slot)
{
    unsigned short n,i;
    LONG epoch;
    if(!slot)return NULL;
    *slot=-1;
    if(!s)return NULL;
    epoch=read_long(&s->request);
    if(read_long(&s->phase)!=MYGAMES_AUDIO_READY || read_long(&s->stop) ||
        epoch!=read_long(&s->done))return NULL;
    for(n=0;n<s->count;++n) {
        i=(unsigned short)((s->producer+n)%s->count);
        if(InterlockedCompareExchange(&s->slots[i],SLOT_FILLING,SLOT_FREE)==SLOT_FREE) {
            s->order[i]=(DWORD)epoch;
            s->producer=(unsigned short)((i+1U)%s->count);*slot=i;
            return s->samples+(unsigned long)i*s->bytes;
        }
    }
    return NULL;
}
void mygames_win32_pcm_session_publish(struct mygames_win32_pcm_session *s,int slot)
{
    LONG target;
    if(!s || slot<0 || slot>=s->count)return;
    if(read_long(&s->slots[slot])!=SLOT_FILLING)return;
    target=read_long(&s->stop) || s->order[slot]!=(DWORD)read_long(&s->request) ||
        read_long(&s->request)!=read_long(&s->done) ||
        read_long(&s->phase)!=MYGAMES_AUDIO_READY?SLOT_FREE:SLOT_READY;
    s->order[slot]=++s->sequence;
    if(InterlockedCompareExchange(&s->slots[slot],target,SLOT_FILLING)==SLOT_FILLING)SetEvent(s->wake);
}
LONG mygames_win32_pcm_session_reset(struct mygames_win32_pcm_session *s)
{
    LONG id;
    if(!s)return 0;
    if(read_long(&s->stop))return -1;
    id=read_long(&s->request);
    if(id==read_long(&s->done))id=InterlockedIncrement(&s->request);
    SetEvent(s->wake);return id;
}
int mygames_win32_pcm_session_reset_result(struct mygames_win32_pcm_session *s,LONG id)
{
    if(!s)return id==0?MYGAMES_AUDIO_OK:MYGAMES_AUDIO_ERROR;
    if(id<0 || read_long(&s->stop))return MYGAMES_AUDIO_ERROR;
    if(read_long(&s->done)!=id)return MYGAMES_AUDIO_PENDING;
    return (int)read_long(&s->result);
}
void mygames_win32_pcm_session_stop(struct mygames_win32_pcm_session *s)
{if(s){InterlockedExchange(&s->stop,1);SetEvent(s->wake);}}
int mygames_win32_pcm_session_release(struct mygames_win32_pcm_session **owner)
{
    struct mygames_win32_pcm_session *s;
    if(!owner)return 0;
    s=*owner;if(!s)return 1;
    if(WaitForSingleObject(s->thread,0)!=WAIT_OBJECT_0 || producer_busy(s))return 0;
    destroy(s);*owner=NULL;return 1;
}
