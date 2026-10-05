#include "platform/win32/frame_wait.h"
int main(void)
{
    struct mysmb_win32_frame_wait wait;
    LARGE_INTEGER frequency,now;
    MSG message;
    if(mysmb_win32_frame_wait_timeout(-10,60000)!=0U ||
        mysmb_win32_frame_wait_timeout(0,60000)!=0U ||
        mysmb_win32_frame_wait_timeout(1,60000)!=1U ||
        mysmb_win32_frame_wait_timeout(1000,60000)!=17U ||
        mysmb_win32_frame_wait_timeout(60001,60000)!=1000U ||
        mysmb_win32_frame_wait_timeout(1000,0)!=0U)return 1;
    mysmb_win32_frame_wait_open(&wait);
    QueryPerformanceFrequency(&frequency);QueryPerformanceCounter(&now);
    /* Exercise an overdue deadline and a queued message without timing gates
     * that depend on the machine load. Neither may block on a future frame. */
    mysmb_win32_frame_wait_until(&wait,now.QuadPart-1,frequency.QuadPart);
    PeekMessage(&message,NULL,0U,0U,PM_NOREMOVE);
    if(!PostThreadMessage(GetCurrentThreadId(),WM_APP,0,0))return 2;
    mysmb_win32_frame_wait_until(&wait,now.QuadPart+frequency.QuadPart,frequency.QuadPart);
    /* Also exercise the old-host fallback with no timer handle. */
    mysmb_win32_frame_wait_close(&wait);
    mysmb_win32_frame_wait_until(&wait,now.QuadPart+frequency.QuadPart,frequency.QuadPart);
    mysmb_win32_frame_wait_close(&wait);
    mysmb_win32_frame_wait_close(&wait);
    return wait.precise_timer || wait.timer?3:0;
}
