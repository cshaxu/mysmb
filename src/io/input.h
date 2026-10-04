#ifndef MYSMB_IO_INPUT_H
#define MYSMB_IO_INPUT_H

#include "io/types.h"

/* Decoded controller bits, not host virtual keys or BIOS scan codes.
 * J means B, K means A; physical key decoding remains with each adapter. */
enum {
    MYSMB_IO_BUTTON_RIGHT = 0x01,
    MYSMB_IO_BUTTON_LEFT = 0x02,
    MYSMB_IO_BUTTON_DOWN = 0x04,
    MYSMB_IO_BUTTON_UP = 0x08,
    MYSMB_IO_BUTTON_START = 0x10,
    MYSMB_IO_BUTTON_SELECT = 0x20,
    MYSMB_IO_BUTTON_B = 0x40,
    MYSMB_IO_BUTTON_A = 0x80
};

struct mysmb_io_input {
    mysmb_io_u8 buttons;
    mysmb_io_u8 buttons2;
};

#endif
