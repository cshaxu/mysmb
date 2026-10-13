#include "io/input_latch.h"
void mysmb_io_input_latch_clear(struct mysmb_io_input_latch *latch)
{latch->held=latch->held2=latch->pressed=latch->pressed2=0U;}
void mysmb_io_input_latch_event(struct mysmb_io_input_latch *latch,
    const struct mysmb_io_input *input,mygames_kvm_u8 fresh_down)
{
    latch->held=input->buttons;latch->held2=input->buttons2;
    if(fresh_down){latch->pressed|=input->buttons;latch->pressed2|=input->buttons2;}
}
void mysmb_io_input_latch_sample(struct mysmb_io_input_latch *latch,
    struct mysmb_io_input *input)
{
    input->buttons=(mygames_kvm_u8)(latch->held|latch->pressed);
    input->buttons2=(mygames_kvm_u8)(latch->held2|latch->pressed2);
    input->requests=0U;latch->pressed=latch->pressed2=0U;
}
