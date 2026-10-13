#ifndef MYSMB_IO_INPUT_LATCH_H
#define MYSMB_IO_INPUT_LATCH_H
#include "io/input.h"
/* Retain decoded physical presses between timer/controller samples. */
struct mysmb_io_input_latch {
    mygames_kvm_u8 held,held2,pressed,pressed2;
};
void mysmb_io_input_latch_clear(struct mysmb_io_input_latch *latch);
void mysmb_io_input_latch_event(struct mysmb_io_input_latch *latch,
    const struct mysmb_io_input *input,mygames_kvm_u8 fresh_down);
void mysmb_io_input_latch_sample(struct mysmb_io_input_latch *latch,
    struct mysmb_io_input *input);
#endif
