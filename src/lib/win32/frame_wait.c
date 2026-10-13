#include "win32/frame_wait.h"
#include <mmsystem.h>
#include <string.h>
typedef HANDLE (WINAPI *mygames_create_timer)(LPSECURITY_ATTRIBUTES,LPCWSTR,
    DWORD,DWORD);
void mygames_win32_frame_wait_open(struct mygames_win32_frame_wait *wait)
{
    mygames_create_timer create_timer;
    FARPROC raw_timer;
    wait->timer=NULL;wait->precise_timer=0U;
    /* Resolve at runtime:old Windows still loads the same executable. Flag2
     * requests a high-resolution timer unaffected by window occlusion. */
    raw_timer=GetProcAddress(GetModuleHandleA("kernel32.dll"),
        "CreateWaitableTimerExW");
    memcpy(&create_timer,&raw_timer,sizeof(create_timer));
    if(create_timer)wait->timer=create_timer(NULL,NULL,2U,TIMER_ALL_ACCESS);
    if(!wait->timer)
        wait->precise_timer=(unsigned char)(timeBeginPeriod(1U)==TIMERR_NOERROR);
}
void mygames_win32_frame_wait_close(struct mygames_win32_frame_wait *wait)
{
    if(wait->timer) {
        CancelWaitableTimer(wait->timer);CloseHandle(wait->timer);wait->timer=NULL;
    }
    if(wait->precise_timer) {
        timeEndPeriod(1U);
        wait->precise_timer=0U;
    }
}
DWORD mygames_win32_frame_wait_timeout(LONGLONG remaining,LONGLONG frequency)
{
    LONGLONG milliseconds;
    if(remaining<=0 || frequency<=0)return 0U;
    /* Cap unusual host-clock deltas without multiplying an unbounded value.
     * Round up so an ordinary early wake never turns into a busy spin. */
    if(remaining>=frequency)return 1000U;
    milliseconds=(remaining*1000+frequency-1)/frequency;
    return (DWORD)milliseconds;
}
void mygames_win32_frame_wait_until(struct mygames_win32_frame_wait *wait,
    LONGLONG deadline,LONGLONG frequency)
{
    LARGE_INTEGER now,due;
    LONGLONG remaining;
    QueryPerformanceCounter(&now);
    remaining=deadline-now.QuadPart;
    if(remaining<=0 || frequency<=0)return;
    if(wait->timer) {
        if(remaining>frequency)remaining=frequency;
        due.QuadPart=-((remaining*10000000+frequency-1)/frequency);
        if(SetWaitableTimer(wait->timer,&due,0,NULL,NULL,FALSE)) {
            MsgWaitForMultipleObjects(1U,&wait->timer,FALSE,1000U,QS_ALLINPUT);
            return;
        }
    }
    /* New messages wake input immediately;pending frame debt returns at once.
     * The root pumps messages between bounded logical-update batches. */
    MsgWaitForMultipleObjects(0U,NULL,FALSE,
        mygames_win32_frame_wait_timeout(remaining,frequency),QS_ALLINPUT);
}
