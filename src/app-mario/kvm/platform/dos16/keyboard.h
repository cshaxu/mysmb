#ifndef MYSMB_DOS16_KEYBOARD_H
#define MYSMB_DOS16_KEYBOARD_H

#include "io/input.h"
#include "io/control.h"
#include "dos16/raw_keyboard.h"

/* AT set-1 physical key state, independent of BIOS character buffering. */
struct mysmb_dos16_keyboard {
    struct mygames_dos16_set1_keyboard raw;
    mygames_kvm_u8 pending_requests;
    struct mysmb_io_control shortcuts;
};
void mysmb_dos16_keyboard_initialize(struct mysmb_dos16_keyboard *keyboard);
void mysmb_dos16_keyboard_after_load(struct mysmb_dos16_keyboard *keyboard);
void mysmb_dos16_keyboard_scan(struct mysmb_dos16_keyboard *keyboard,
                               mygames_kvm_u8 scan);
void mysmb_dos16_keyboard_input(struct mysmb_dos16_keyboard *keyboard,
                                struct mysmb_io_input *input);

#endif
