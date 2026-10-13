#include "platform/dos16/keyboard.h"

void mysmb_dos16_keyboard_initialize(struct mysmb_dos16_keyboard *keyboard)
{
    mygames_dos16_set1_keyboard_initialize(&keyboard->raw);
    keyboard->pending_requests=0U;
    mysmb_io_control_initialize(&keyboard->shortcuts);
}

void mysmb_dos16_keyboard_scan(struct mysmb_dos16_keyboard *keyboard,
                               mygames_kvm_u8 scan)
{
    struct mygames_dos16_key_transition key;
    if(!mygames_dos16_set1_keyboard_scan(&keyboard->raw,scan,&key))return;
    if(!key.extended && key.scan==0x0fU)
        keyboard->pending_requests|=mysmb_io_control_toggle(&keyboard->shortcuts,
            key.down,1U);
    if (!key.extended && key.scan==1U && key.down)
        keyboard->pending_requests|=MYSMB_IO_REQUEST_EXIT;
    if(!key.extended && key.down && !key.repeat){
        if(key.scan==0x19U)keyboard->pending_requests|=MYSMB_IO_REQUEST_SAVE;
        if(key.scan==0x18U)keyboard->pending_requests|=MYSMB_IO_REQUEST_LOAD;
    }
}
void mysmb_dos16_keyboard_after_load(struct mysmb_dos16_keyboard *keyboard)
{
    mygames_kvm_u8 save,load,tab,exit;
    save=keyboard->raw.down[0x19U];load=keyboard->raw.down[0x18U];
    tab=keyboard->raw.down[0x0fU];
    exit=(mygames_kvm_u8)(keyboard->pending_requests&MYSMB_IO_REQUEST_EXIT);
    mysmb_dos16_keyboard_initialize(keyboard);
    /* Held shortcut make repeats stay blocked until the physical break. */
    keyboard->raw.down[0x19U]=save;keyboard->raw.down[0x18U]=load;
    keyboard->raw.down[0x0fU]=tab;keyboard->shortcuts.toggle_held=tab;
    /* Application exit is not stale controller state;retain it across load. */
    keyboard->pending_requests=exit;
}

void mysmb_dos16_keyboard_input(struct mysmb_dos16_keyboard *keyboard,
                                struct mysmb_io_input *input)
{
    mygames_kvm_u8 buttons;
    buttons = 0U;
    if (keyboard->raw.down[0x1e] || keyboard->raw.extended[0x4b]) buttons |= MYSMB_IO_BUTTON_LEFT;
    if (keyboard->raw.down[0x20] || keyboard->raw.extended[0x4d]) buttons |= MYSMB_IO_BUTTON_RIGHT;
    if (keyboard->raw.down[0x11] || keyboard->raw.extended[0x48]) buttons |= MYSMB_IO_BUTTON_UP;
    if (keyboard->raw.down[0x1f] || keyboard->raw.extended[0x50]) buttons |= MYSMB_IO_BUTTON_DOWN;
    if (keyboard->raw.down[0x24]) buttons |= MYSMB_IO_BUTTON_B;
    if (keyboard->raw.down[0x25]) buttons |= MYSMB_IO_BUTTON_A;
    if (keyboard->raw.down[0x1c] || keyboard->raw.extended[0x1c]) buttons |= MYSMB_IO_BUTTON_START;
    if (keyboard->raw.down[0x2a] || keyboard->raw.down[0x36]) buttons |= MYSMB_IO_BUTTON_SELECT;
    input->buttons = buttons;
    input->buttons2 = 0U;
    input->requests=keyboard->pending_requests;
    keyboard->pending_requests=0U;
}
