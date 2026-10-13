#include "io/input_latch.h"
int main(void)
{
    struct mysmb_io_input_latch latch;
    struct mysmb_io_input input={0U,0U,255U},sample;
    mysmb_io_input_latch_clear(&latch);
    mysmb_io_input_latch_sample(&latch,&sample);
    if(sample.buttons || sample.buttons2 || sample.requests)return 1;
    input.buttons=MYSMB_IO_BUTTON_START;input.buttons2=MYSMB_IO_BUTTON_A;
    mysmb_io_input_latch_event(&latch,&input,1U);
    input.buttons=input.buttons2=0U;
    mysmb_io_input_latch_event(&latch,&input,0U);
    mysmb_io_input_latch_sample(&latch,&sample);
    if(sample.buttons!=MYSMB_IO_BUTTON_START || sample.buttons2!=MYSMB_IO_BUTTON_A || sample.requests)return 2;
    mysmb_io_input_latch_sample(&latch,&sample);
    if(sample.buttons || sample.buttons2)return 3;
    input.buttons=MYSMB_IO_BUTTON_RIGHT;
    mysmb_io_input_latch_event(&latch,&input,1U);
    mysmb_io_input_latch_sample(&latch,&sample);
    mysmb_io_input_latch_sample(&latch,&sample);
    if(sample.buttons!=MYSMB_IO_BUTTON_RIGHT)return 4;
    /* Focus loss cancels held and pending samples; repeat cannot relatch. */
    mysmb_io_input_latch_clear(&latch);
    mysmb_io_input_latch_event(&latch,&input,0U);
    input.buttons=0U;mysmb_io_input_latch_event(&latch,&input,0U);
    mysmb_io_input_latch_sample(&latch,&sample);
    return sample.buttons!=0U;
}
