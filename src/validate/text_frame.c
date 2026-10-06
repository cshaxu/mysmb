#include "validate/text_frame.h"
static mysmb_io_u8 mysmb_text_color(mysmb_io_u8 color)
{ if (color == 0x21U || color == 0x31U) return 0x1fU; if (color == 0x16U || color == 0x26U) return 0x4fU; if (color == 0x19U || color == 0x29U) return 0x2eU; return 0x6fU; }
void mysmb_text_frame_build(const struct mysmb_ppu_frame *ppu_frame, struct mysmb_text_frame *frame)
{
    mysmb_io_u16 row; mysmb_io_u16 column; mysmb_io_u16 source_x; mysmb_io_u16 source_y; mysmb_io_u8 color;
    for (row=0U;row<MYSMB_TEXT_ROWS;++row) { source_y=(mysmb_io_u16)(row*MYSMB_PPU_FRAME_HEIGHT/MYSMB_TEXT_ROWS); for(column=0U;column<MYSMB_TEXT_COLUMNS;++column) { source_x=(mysmb_io_u16)(column*MYSMB_PPU_FRAME_WIDTH/MYSMB_TEXT_COLUMNS); color=ppu_frame->pixels[source_y*MYSMB_PPU_FRAME_WIDTH+source_x]; frame->cells[row*MYSMB_TEXT_COLUMNS+column].character=(color==0x21U||color==0x31U)?' ':'#'; frame->cells[row*MYSMB_TEXT_COLUMNS+column].color=mysmb_text_color(color); } }
}
