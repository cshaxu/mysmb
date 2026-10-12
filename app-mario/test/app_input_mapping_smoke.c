#include "app/input_mapping.h"

int main(void)
{
    struct mysmb_app_input_mapping mapping;
    struct mygames_kvm_input_event event;
    struct mysmb_io_input input;
    mysmb_app_input_mapping_initialize(&mapping);
    input.buttons=0U; input.buttons2=0U; input.requests=0U;
    event.kind=MYGAMES_KVM_INPUT_KEY; event.down=1U; event.native_scan=0U;
    event.modifiers=0U; event.x=0U; event.y=0U;
    event.physical_code=MYGAMES_KVM_KEY_J;
    mysmb_app_input_mapping_event(&mapping,&event,&input);
    if((input.buttons&MYSMB_IO_BUTTON_B)==0U)return 1;
    event.physical_code=MYGAMES_KVM_KEY_K;
    mysmb_app_input_mapping_event(&mapping,&event,&input);
    if((input.buttons&MYSMB_IO_BUTTON_A)==0U)return 2;
    event.physical_code=MYGAMES_KVM_KEY_TAB;
    mysmb_app_input_mapping_event(&mapping,&event,&input);
    if((input.requests&MYSMB_IO_REQUEST_TOGGLE)==0U)return 3;
    return 0;
}
