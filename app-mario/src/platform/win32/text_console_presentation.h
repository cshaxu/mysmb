#ifndef MYSMB_WIN32_TEXT_CONSOLE_PRESENTATION_H
#define MYSMB_WIN32_TEXT_CONSOLE_PRESENTATION_H

#include "platform/win32/text_console.h"

/* Convert one bounded neutral text rectangle to a VT RGB stream. This is pure
 * presentation formatting: it neither opens a device nor writes a handle. */
size_t mysmb_win32_console_vt_encode(const struct mygames_kvm_text_frame *frame,
    unsigned int width,unsigned int height,WCHAR *out,size_t capacity);
int mysmb_win32_console_present_frame(struct mysmb_win32_text_console *console,
    const struct mygames_kvm_text_frame *frame);
void mysmb_win32_console_initialize_indexed(struct mysmb_win32_text_console *console);

#endif
