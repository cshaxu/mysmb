#ifndef MYSMB_WIN32_TEXT_CONSOLE_POLICY_H
#define MYSMB_WIN32_TEXT_CONSOLE_POLICY_H

#include <stddef.h>

unsigned short mysmb_win32_console_rows(unsigned short rows);
size_t mysmb_win32_console_vt_capacity(unsigned short rows);
unsigned char mysmb_win32_console_use_vt(unsigned char indexed_carrier,
    unsigned char output_mode_read,unsigned char output_mode_set);

#endif
