#ifndef MYGAMES_WIN32_TEXT_CONSOLE_PRESENTATION_H
#define MYGAMES_WIN32_TEXT_CONSOLE_PRESENTATION_H

#include "win32/text_console.h"

/* Convert one bounded neutral text rectangle to a VT RGB stream. This is pure
 * presentation formatting: it neither opens a device nor writes a handle. */
size_t mygames_win32_console_vt_encode(const struct mygames_kvm_text_frame *frame,
    unsigned int width,unsigned int height,WCHAR *out,size_t capacity);
int mygames_win32_console_present_frame(struct mygames_win32_text_console *console,
    const struct mygames_kvm_text_frame *frame);
void mygames_win32_console_initialize_indexed(struct mygames_win32_text_console *console);

#endif
