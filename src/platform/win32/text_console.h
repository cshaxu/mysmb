#ifndef MYSMB_WIN32_TEXT_CONSOLE_H
#define MYSMB_WIN32_TEXT_CONSOLE_H
#include <windows.h>
#include "io/video.h"
struct mysmb_win32_text_console {
    HANDLE input,output;
    HWND window;
    unsigned char opened;
    CHAR_INFO cells[MYSMB_IO_TEXT_CELLS];
};
int mysmb_win32_text_console_open(struct mysmb_win32_text_console *console,
    HWND owner);
void mysmb_win32_text_console_close(struct mysmb_win32_text_console *console);
int mysmb_win32_text_console_present(struct mysmb_win32_text_console *console,
    const struct mysmb_io_text_frame *frame);
int mysmb_win32_text_console_key(struct mysmb_win32_text_console *console,
    WORD *key,unsigned char *pressed);
#endif
