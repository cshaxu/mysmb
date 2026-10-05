#ifndef MYSMB_PLATFORM_TEXT_FRAME_H
#define MYSMB_PLATFORM_TEXT_FRAME_H
#include "ppu/frame.h"
enum { MYSMB_TEXT_COLUMNS = 80, MYSMB_TEXT_ROWS = 25 };
struct mysmb_text_cell { mysmb_io_u8 character; mysmb_io_u8 color; };
struct mysmb_text_frame { struct mysmb_text_cell cells[MYSMB_TEXT_ROWS * MYSMB_TEXT_COLUMNS]; };
/* Backend character quantization only; input is the shared game PPU frame. */
void mysmb_text_frame_build(const struct mysmb_ppu_frame *ppu_frame, struct mysmb_text_frame *text_frame);
#endif
