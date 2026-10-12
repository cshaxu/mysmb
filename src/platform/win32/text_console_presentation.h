#ifndef MYSMB_WIN32_TEXT_CONSOLE_PRESENTATION_H
#define MYSMB_WIN32_TEXT_CONSOLE_PRESENTATION_H

#include "platform/win32/text_console.h"

int mysmb_win32_console_present_frame(struct mysmb_win32_text_console *console,
    const struct mysmb_io_text_frame *frame);
void mysmb_win32_console_initialize_indexed(struct mysmb_win32_text_console *console);

#endif
