#ifndef MYGAMES_WIN16_TEXT_H
#define MYGAMES_WIN16_TEXT_H
#include <windows.h>
#include "kvm/video.h"
/* Paint immutable CP437 cells across the client rectangle, including blanks.
 * Font and clipping are device mechanics; app owns cells and palette. */
int mygames_win16_text_paint(HDC dc,const RECT *rect,
    const struct mygames_kvm_text_frame FAR *frame);
#endif
