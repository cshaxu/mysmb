#ifndef MYGAMES_WIN32_WINDOW_H
#define MYGAMES_WIN32_WINDOW_H
#include "win32/input.h"
#include "win32/window_geometry.h"
#include "kvm/pointer.h"
struct mygames_win32_window_input {struct mygames_kvm_pointer pointer;};
typedef void (*mygames_win32_event_sink)(void *,HWND,const struct mygames_kvm_input_event *);
/* Apps supply event meaning and retain their own loop/update policy. */
int mygames_win32_window_event(HWND window,UINT message,WPARAM word,LPARAM detail,
    struct mygames_win32_window_input *pointer,struct mygames_win32_input *keys,
    struct mygames_win32_window_geometry *geometry,
    mygames_win32_event_sink sink,void *context,LRESULT *result);
HWND mygames_win32_window_create(HINSTANCE instance,const char *class_name,
    const char *title,WNDPROC procedure,struct mygames_win32_window_geometry *geometry);
/* Borrowed top-down packed0x00RRGGBB pixels, capacity in DWORD pixels. */
int mygames_win32_pixels_present(HDC dc,const RECT *target,const DWORD *pixels,
    unsigned short width,unsigned short height,unsigned long capacity);
int mygames_win32_window_paint(HWND window,const DWORD *pixels,
    unsigned short width,unsigned short height,unsigned long capacity);
#endif
