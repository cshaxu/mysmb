#ifndef MYSMB_IO_CONTROL_H
#define MYSMB_IO_CONTROL_H
#include "io/input.h"
struct mysmb_io_control { mysmb_io_u8 exit_requested; };
void mysmb_io_control_initialize(struct mysmb_io_control *control);
void mysmb_io_control_input(struct mysmb_io_control *control,
    const struct mysmb_io_input *input);
#endif
