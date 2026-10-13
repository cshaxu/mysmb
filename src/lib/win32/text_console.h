#ifndef MYGAMES_WIN32_TEXT_CONSOLE_H
#define MYGAMES_WIN32_TEXT_CONSOLE_H
#include <windows.h>
#include "kvm/video.h"
#include "win32/text_console_policy.h"
struct mygames_win32_text_console {
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
int mygames_win32_text_console_open(struct mygames_win32_text_console *console,
    HWND owner);
int mygames_win32_text_console_open_profile(struct mygames_win32_text_console *console,
    HWND owner,unsigned short rows,const char *title);
void mygames_win32_text_console_close(struct mygames_win32_text_console *console);
/* A normal presenter switch retains the already-open console session. */
int mygames_win32_text_console_suspend(struct mygames_win32_text_console *console);
int mygames_win32_text_console_resume(struct mygames_win32_text_console *console);
int mygames_win32_text_console_present(struct mygames_win32_text_console *console,
    const struct mygames_kvm_text_frame *frame);
int mygames_win32_text_console_key(struct mygames_win32_text_console *console,
    WORD *key,WORD *scan,unsigned char *pressed);
/* Returns0 without input,1 for a record,2 for a focus record (pressed=focus). */
#endif
