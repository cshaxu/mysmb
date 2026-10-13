#ifndef MYGAMES_WIN32_TEXT_CONSOLE_GEOMETRY_H
#define MYGAMES_WIN32_TEXT_CONSOLE_GEOMETRY_H

#include "win32/text_console.h"

unsigned char mygames_win32_console_window(HWND window);
unsigned char mygames_win32_console_indexed_carrier(struct mygames_win32_text_console *console);
void mygames_win32_console_fit(struct mygames_win32_text_console *console,
    unsigned char initial);
unsigned char mygames_win32_console_size(struct mygames_win32_text_console *console,
    COORD size,const SMALL_RECT *view);
int mygames_win32_console_geometry(struct mygames_win32_text_console *console);

#endif
