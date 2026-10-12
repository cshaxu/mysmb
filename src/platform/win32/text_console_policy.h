#ifndef MYSMB_WIN32_TEXT_CONSOLE_POLICY_H
#define MYSMB_WIN32_TEXT_CONSOLE_POLICY_H

#include <stddef.h>
#include <windows.h>

enum mysmb_win32_console_result {
    MYSMB_WIN32_CONSOLE_LOST=0, MYSMB_WIN32_CONSOLE_READY=1,
    MYSMB_WIN32_CONSOLE_DEFER=2
};

unsigned short mysmb_win32_console_rows(unsigned short rows);
size_t mysmb_win32_console_vt_capacity(unsigned short rows);
unsigned char mysmb_win32_console_use_vt(unsigned char indexed_carrier,
    unsigned char output_mode_read,unsigned char output_mode_set);
/* Classify a failed Console write without touching a host handle. `failures`
 * is the saturated consecutive-failure count after this write. */
int mysmb_win32_console_write_result(DWORD error,unsigned short failures);

#endif
