#ifndef MYGAMES_DOS16_RAW_KEYBOARD_H
#define MYGAMES_DOS16_RAW_KEYBOARD_H

#include "kvm/types.h"

/* AT Set-1 decoder. It exposes physical transitions only; applications map
 * them to controller, menu, save/load or presentation meanings. */
struct mygames_dos16_set1_keyboard {
    mygames_kvm_u8 down[128];
    mygames_kvm_u8 extended[128];
    mygames_kvm_u8 prefix;
    mygames_kvm_u8 pause_bytes;
};

struct mygames_dos16_key_transition {
    mygames_kvm_u8 scan;
    mygames_kvm_u8 extended;
    mygames_kvm_u8 down;
    mygames_kvm_u8 repeat;
};

void mygames_dos16_set1_keyboard_initialize(
    struct mygames_dos16_set1_keyboard *keyboard);
/* Returns one only when scan completes a make/break transition. Prefix and
 * Pause sequence bytes are consumed without fabricating a physical key. */
int mygames_dos16_set1_keyboard_scan(struct mygames_dos16_set1_keyboard *keyboard,
    mygames_kvm_u8 scan,struct mygames_dos16_key_transition *transition);

#endif
