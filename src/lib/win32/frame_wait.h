#ifndef MYGAMES_WIN32_FRAME_WAIT_H
#define MYGAMES_WIN32_FRAME_WAIT_H
#include <windows.h>
struct mygames_win32_frame_wait {
    HANDLE timer;
    unsigned char precise_timer;
};
void mygames_win32_frame_wait_open(struct mygames_win32_frame_wait *wait);
void mygames_win32_frame_wait_close(struct mygames_win32_frame_wait *wait);
DWORD mygames_win32_frame_wait_timeout(LONGLONG remaining,LONGLONG frequency);
void mygames_win32_frame_wait_until(struct mygames_win32_frame_wait *wait,
    LONGLONG deadline,LONGLONG frequency);
#endif
