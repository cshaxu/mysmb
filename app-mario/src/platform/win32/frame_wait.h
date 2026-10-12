#ifndef MYSMB_WIN32_FRAME_WAIT_H
#define MYSMB_WIN32_FRAME_WAIT_H
#include <windows.h>
struct mysmb_win32_frame_wait {
    HANDLE timer;
    unsigned char precise_timer;
};
void mysmb_win32_frame_wait_open(struct mysmb_win32_frame_wait *wait);
void mysmb_win32_frame_wait_close(struct mysmb_win32_frame_wait *wait);
DWORD mysmb_win32_frame_wait_timeout(LONGLONG remaining,LONGLONG frequency);
void mysmb_win32_frame_wait_until(struct mysmb_win32_frame_wait *wait,
    LONGLONG deadline,LONGLONG frequency);
#endif
