#include "win32/frame_wait.h"
int main(void)
{
    struct mygames_win32_frame_wait wait;
    LARGE_INTEGER frequency,now;
    MSG message;
    if(mygames_win32_frame_wait_timeout(-10,60000)!=0U ||
        mygames_win32_frame_wait_timeout(0,60000)!=0U ||
        mygames_win32_frame_wait_timeout(1,60000)!=1U ||
        mygames_win32_frame_wait_timeout(1000,60000)!=17U ||
        mygames_win32_frame_wait_timeout(60001,60000)!=1000U ||
        mygames_win32_frame_wait_timeout(1000,0)!=0U)return 1;
    mygames_win32_frame_wait_open(&wait);
    QueryPerformanceFrequency(&frequency);QueryPerformanceCounter(&now);
    /* Exercise an overdue deadline and a queued message without timing gates
     * that depend on the machine load. Neither may block on a future frame. */
    mygames_win32_frame_wait_until(&wait,now.QuadPart-1,frequency.QuadPart);
    PeekMessage(&message,NULL,0U,0U,PM_NOREMOVE);
    if(!PostThreadMessage(GetCurrentThreadId(),WM_APP,0,0))return 2;
    mygames_win32_frame_wait_until(&wait,now.QuadPart+frequency.QuadPart,frequency.QuadPart);
    /* Also exercise the old-host fallback with no timer handle. */
    mygames_win32_frame_wait_close(&wait);
    mygames_win32_frame_wait_until(&wait,now.QuadPart+frequency.QuadPart,frequency.QuadPart);
    mygames_win32_frame_wait_close(&wait);
    mygames_win32_frame_wait_close(&wait);
    return wait.precise_timer || wait.timer?3:0;
}
