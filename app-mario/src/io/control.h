#ifndef MYSMB_IO_CONTROL_H
#define MYSMB_IO_CONTROL_H
#include "io/input.h"
struct mysmb_io_control { mygames_kvm_u8 exit_requested; mygames_kvm_u8 toggle_held; };
void mysmb_io_control_initialize(struct mysmb_io_control *control);
void mysmb_io_control_input(struct mysmb_io_control *control,
    const struct mysmb_io_input *input);
mygames_kvm_u8 mysmb_io_control_toggle(struct mysmb_io_control *control,
    mygames_kvm_u8 pressed,mygames_kvm_u8 focused);
#endif
