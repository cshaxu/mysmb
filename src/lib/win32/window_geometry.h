#ifndef MYGAMES_WIN32_WINDOW_GEOMETRY_H
#define MYGAMES_WIN32_WINDOW_GEOMETRY_H

#include <windows.h>

/* A host-side integer-pixel sizing policy.  Applications supply their own
 * frame dimensions; this component does not know a game's resolution. */
struct mygames_win32_window_geometry {
    int unit_width;
    int unit_height;
    int minimum_units;
    int initial_units;
    int adjusting;
};

void mygames_win32_window_geometry_initialize(
    struct mygames_win32_window_geometry *geometry,int unit_width,
    int unit_height,int minimum_units,int initial_units);
UINT mygames_win32_window_dpi(HWND window);
void mygames_win32_window_margins(HWND window,UINT dpi,RECT *margins);
void mygames_win32_window_enable_dpi(void);
int mygames_win32_window_initial_client(HWND window,
    const struct mygames_win32_window_geometry *geometry);
void mygames_win32_window_size_rectangle(HWND window,RECT *rect,UINT edge,UINT dpi,
    const struct mygames_win32_window_geometry *geometry);
void mygames_win32_window_size_limits(HWND window,MINMAXINFO *limits,
    const struct mygames_win32_window_geometry *geometry);
void mygames_win32_window_normalize_client(HWND window,
    struct mygames_win32_window_geometry *geometry);

#endif
