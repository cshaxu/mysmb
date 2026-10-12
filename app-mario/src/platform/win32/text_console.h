#ifndef MYSMB_WIN32_TEXT_CONSOLE_H
#define MYSMB_WIN32_TEXT_CONSOLE_H
#include <windows.h>
#include "kvm/video.h"
#include "platform/win32/text_console_policy.h"
struct mysmb_win32_text_console {
    HANDLE input,output;
    HANDLE shell_output;
    DWORD shell_input_mode;
    WCHAR *shell_title;
    WINDOWPLACEMENT shell_placement;
    CONSOLE_SCREEN_BUFFER_INFO shell_info;
    HWND window;
    unsigned char opened,borrowed,mode_saved,focused,suspended,window_usable,vt_output,font_changed,geometry_usable;
    CONSOLE_FONT_INFOEX shell_font,effective_font;
    COORD observed_view;
    unsigned short output_failures;
    DWORD fit_changed_at;
    WCHAR *terminal_output;
    unsigned short geometry_pending;
    unsigned short rows;
    unsigned char colors_valid;
    unsigned long colors[16];
    unsigned char fallback_colors[16];
    CHAR_INFO cells[MYGAMES_KVM_TEXT_CELLS];
};
int mysmb_win32_text_console_open(struct mysmb_win32_text_console *console,
    HWND owner);
int mysmb_win32_text_console_open_profile(struct mysmb_win32_text_console *console,
    HWND owner,unsigned short rows);
void mysmb_win32_text_console_close(struct mysmb_win32_text_console *console);
/* A normal presenter switch retains the already-open console session. */
int mysmb_win32_text_console_suspend(struct mysmb_win32_text_console *console);
int mysmb_win32_text_console_resume(struct mysmb_win32_text_console *console);
int mysmb_win32_text_console_present(struct mysmb_win32_text_console *console,
    const struct mygames_kvm_text_frame *frame);
int mysmb_win32_text_console_key(struct mysmb_win32_text_console *console,
    WORD *key,WORD *scan,unsigned char *pressed);
/* Returns0 without input,1 for a record,2 for a focus record (pressed=focus). */
#endif
