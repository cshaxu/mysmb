#ifndef MYSMB_WIN32_AUDIO_SNAPSHOT_H
#define MYSMB_WIN32_AUDIO_SNAPSHOT_H
#include "platform/win32/audio_renderer.h"
#include "io/snapshot.h"
int mysmb_win32_audio_capture(const struct mysmb_win32_audio_renderer *renderer,
    mysmb_io_u8 *bytes);
int mysmb_win32_audio_restore(struct mysmb_win32_audio_renderer *renderer,
    const mysmb_io_u8 *bytes);
#endif
