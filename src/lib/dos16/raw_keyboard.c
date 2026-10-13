#include <string.h>

#include "dos16/raw_keyboard.h"

void mygames_dos16_set1_keyboard_initialize(
    struct mygames_dos16_set1_keyboard *keyboard)
{
    memset(keyboard,0,sizeof(*keyboard));
}

int mygames_dos16_set1_keyboard_scan(struct mygames_dos16_set1_keyboard *keyboard,
    mygames_kvm_u8 scan,struct mygames_dos16_key_transition *transition)
{
    mygames_kvm_u8 *keys;
    mygames_kvm_u8 code;
    if(keyboard->pause_bytes!=0U) {
        --keyboard->pause_bytes;
        return 0;
    }
    if(scan==0xe1U) {
        keyboard->pause_bytes=5U;
        keyboard->prefix=0U;
        return 0;
    }
    if(scan==0xe0U) {
        keyboard->prefix=1U;
        return 0;
    }
    code=(mygames_kvm_u8)(scan&0x7fU);
    keys=keyboard->prefix!=0U?keyboard->extended:keyboard->down;
    transition->scan=code;
    transition->extended=keyboard->prefix;
    transition->down=(mygames_kvm_u8)((scan&0x80U)==0U);
    transition->repeat=(mygames_kvm_u8)(transition->down!=0U && keys[code]!=0U);
    keys[code]=transition->down;
    keyboard->prefix=0U;
    return 1;
}
