#ifndef MYSMB_WIN32_TEXT_CONSOLE_GEOMETRY_H
#define MYSMB_WIN32_TEXT_CONSOLE_GEOMETRY_H

#include "platform/win32/text_console.h"

unsigned char mysmb_win32_console_window(HWND window);
unsigned char mysmb_win32_console_indexed_carrier(struct mysmb_win32_text_console *console);
void mysmb_win32_console_fit(struct mysmb_win32_text_console *console,
    unsigned char initial);
unsigned char mysmb_win32_console_size(struct mysmb_win32_text_console *console,
    COORD size,const SMALL_RECT *view);
int mysmb_win32_console_geometry(struct mysmb_win32_text_console *console);

#endif
