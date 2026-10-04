#ifndef MYSMB_DOS16_KEYBOARD_H
#define MYSMB_DOS16_KEYBOARD_H

#include "io/input.h"

/* AT set-1 physical key state, independent of BIOS character buffering. */
struct mysmb_dos16_keyboard {
    mysmb_io_u8 down[128];
    mysmb_io_u8 extended[128];
    mysmb_io_u8 prefix;
    mysmb_io_u8 pause_bytes;
    mysmb_io_u8 pending_requests;
};
void mysmb_dos16_keyboard_initialize(struct mysmb_dos16_keyboard *keyboard);
void mysmb_dos16_keyboard_scan(struct mysmb_dos16_keyboard *keyboard,
                               mysmb_io_u8 scan);
void mysmb_dos16_keyboard_input(struct mysmb_dos16_keyboard *keyboard,
                                struct mysmb_io_input *input);

#endif
