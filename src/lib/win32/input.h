#ifndef MYGAMES_WIN32_INPUT_H
#define MYGAMES_WIN32_INPUT_H

#include "kvm/input_event.h"

struct mygames_win32_input {
    mygames_kvm_u8 down[256];
};

void mygames_win32_input_initialize(struct mygames_win32_input *input);
void mygames_win32_input_clear(struct mygames_win32_input *input);
/* Returns zero for a key outside the portable physical-event vocabulary,
 * one for a transition, and two for an auto-repeat.  It never assigns an
 * application command or controller bit. */
int mygames_win32_input_key(struct mygames_win32_input *input,
    unsigned short key,unsigned short scan,unsigned char down,
    struct mygames_kvm_input_event *event);

#endif
