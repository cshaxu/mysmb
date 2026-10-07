#include "platform/dos16/keyboard.h"

void mysmb_dos16_keyboard_initialize(struct mysmb_dos16_keyboard *keyboard)
{
    mysmb_io_u16 i;
    for (i = 0U; i < 128U; ++i) {
        keyboard->down[i] = 0U;
        keyboard->extended[i] = 0U;
    }
    keyboard->prefix = 0U;
    keyboard->pause_bytes = 0U;
    keyboard->pending_requests=0U;
    mysmb_io_control_initialize(&keyboard->shortcuts);
}

void mysmb_dos16_keyboard_scan(struct mysmb_dos16_keyboard *keyboard,
                               mysmb_io_u8 scan)
{
    mysmb_io_u8 *keys;
    if (keyboard->pause_bytes != 0U) {
        --keyboard->pause_bytes;
        return;
    }
    if (scan == 0xe1U) {
        keyboard->pause_bytes = 5U;
        keyboard->prefix = 0U;
        return;
    }
    if (scan == 0xe0U) {
        keyboard->prefix = 1U;
        return;
    }
    keys = keyboard->prefix != 0U ? keyboard->extended : keyboard->down;
    if(keyboard->prefix==0U && (scan&0x7fU)==0x0fU)
        keyboard->pending_requests|=mysmb_io_control_toggle(&keyboard->shortcuts,
            (mysmb_io_u8)((scan&0x80U)==0U),1U);
    if (keyboard->prefix==0U && scan==1U)
        keyboard->pending_requests|=MYSMB_IO_REQUEST_EXIT;
    if(keyboard->prefix==0U && keys[scan&0x7fU]==0U){
        if(scan==0x19U)keyboard->pending_requests|=MYSMB_IO_REQUEST_SAVE;
        if(scan==0x18U)keyboard->pending_requests|=MYSMB_IO_REQUEST_LOAD;
    }
    keys[scan & 0x7fU] = (scan & 0x80U) != 0U ? 0U : 1U;
    keyboard->prefix = 0U;
}
void mysmb_dos16_keyboard_after_load(struct mysmb_dos16_keyboard *keyboard)
{
    mysmb_io_u8 save,load,tab,exit;
    save=keyboard->down[0x19U];load=keyboard->down[0x18U];
    tab=keyboard->down[0x0fU];
    exit=(mysmb_io_u8)(keyboard->pending_requests&MYSMB_IO_REQUEST_EXIT);
    mysmb_dos16_keyboard_initialize(keyboard);
    /* Held shortcut make repeats stay blocked until the physical break. */
    keyboard->down[0x19U]=save;keyboard->down[0x18U]=load;
    keyboard->down[0x0fU]=tab;keyboard->shortcuts.toggle_held=tab;
    /* Application exit is not stale controller state;retain it across load. */
    keyboard->pending_requests=exit;
}

void mysmb_dos16_keyboard_input(struct mysmb_dos16_keyboard *keyboard,
                                struct mysmb_io_input *input)
{
    mysmb_io_u8 buttons;
    buttons = 0U;
    if (keyboard->down[0x1e] || keyboard->extended[0x4b]) buttons |= MYSMB_IO_BUTTON_LEFT;
    if (keyboard->down[0x20] || keyboard->extended[0x4d]) buttons |= MYSMB_IO_BUTTON_RIGHT;
    if (keyboard->down[0x11] || keyboard->extended[0x48]) buttons |= MYSMB_IO_BUTTON_UP;
    if (keyboard->down[0x1f] || keyboard->extended[0x50]) buttons |= MYSMB_IO_BUTTON_DOWN;
    if (keyboard->down[0x24]) buttons |= MYSMB_IO_BUTTON_B;
    if (keyboard->down[0x25]) buttons |= MYSMB_IO_BUTTON_A;
    if (keyboard->down[0x1c] || keyboard->extended[0x1c]) buttons |= MYSMB_IO_BUTTON_START;
    if (keyboard->down[0x2a] || keyboard->down[0x36]) buttons |= MYSMB_IO_BUTTON_SELECT;
    input->buttons = buttons;
    input->buttons2 = 0U;
    input->requests=keyboard->pending_requests;
    keyboard->pending_requests=0U;
}
