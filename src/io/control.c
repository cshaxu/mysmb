#include "io/control.h"
void mysmb_io_control_initialize(struct mysmb_io_control *control)
{
    control->exit_requested=0U;
}
void mysmb_io_control_input(struct mysmb_io_control *control,
    const struct mysmb_io_input *input)
{
    /* One irreversible application decision,independent of game/focus/host.
     * A short Escape press remains accepted after its release event. */
    if ((input->requests & MYSMB_IO_REQUEST_EXIT)!=0U)
        control->exit_requested=1U;
}
