#include "io/control.h"
void mysmb_io_control_initialize(struct mysmb_io_control *control)
{
    control->exit_requested=0U;
    control->toggle_held=0U;
}
mysmb_io_u8 mysmb_io_control_toggle(struct mysmb_io_control *control,
    mysmb_io_u8 pressed,mysmb_io_u8 focused)
{
    if(pressed==0U){control->toggle_held=0U;return 0U;}
    if(focused==0U || control->toggle_held!=0U)return 0U;
    control->toggle_held=1U;
    return MYSMB_IO_REQUEST_TOGGLE;
}
void mysmb_io_control_input(struct mysmb_io_control *control,
    const struct mysmb_io_input *input)
{
    /* One irreversible application decision,independent of game/focus/host.
     * A short Escape press remains accepted after its release event. */
    if ((input->requests & MYSMB_IO_REQUEST_EXIT)!=0U)
        control->exit_requested=1U;
}
