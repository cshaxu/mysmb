#ifndef MYSMB_WIN32_TEXT_CONSOLE_H
#define MYSMB_WIN32_TEXT_CONSOLE_H
#include <windows.h>
#include "io/video.h"
struct mysmb_win32_text_console {
    HANDLE input,output;
    HANDLE shell_output;
    DWORD shell_input_mode;
    WCHAR *shell_title;
    WINDOWPLACEMENT shell_placement;
    CONSOLE_SCREEN_BUFFER_INFO shell_info;
    HWND window;
    unsigned char opened,borrowed,mode_saved,focused,window_usable,vt_output,font_changed;
    CONSOLE_FONT_INFOEX shell_font,effective_font;
    COORD observed_view;
    unsigned short output_failures;
    DWORD fit_changed_at;
    WCHAR *terminal_output;
    unsigned short geometry_pending;
    CHAR_INFO cells[MYSMB_IO_TEXT_CELLS];
};
int mysmb_win32_text_console_open(struct mysmb_win32_text_console *console,
    HWND owner);
void mysmb_win32_text_console_close(struct mysmb_win32_text_console *console);
enum mysmb_win32_console_result {
    MYSMB_WIN32_CONSOLE_LOST=0, MYSMB_WIN32_CONSOLE_READY=1,
    MYSMB_WIN32_CONSOLE_DEFER=2
};
int mysmb_win32_text_console_present(struct mysmb_win32_text_console *console,
    const struct mysmb_io_text_frame *frame);
int mysmb_win32_text_console_key(struct mysmb_win32_text_console *console,
    WORD *key,WORD *scan,unsigned char *pressed);
/* Returns0 without input,1 for a record,2 for a focus record (pressed=focus). */
#endif
