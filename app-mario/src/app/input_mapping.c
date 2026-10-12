#include "app/input_mapping.h"

static mygames_kvm_u8 held(const struct mysmb_app_input_mapping *mapping,
    mygames_kvm_u16 key)
{
    return key < 16U ? mapping->down[key] : 0U;
}

static void sample(const struct mysmb_app_input_mapping *mapping,
    struct mysmb_io_input *input)
{
    input->buttons=0U; input->buttons2=0U;
    if(held(mapping,MYGAMES_KVM_KEY_A))input->buttons|=MYSMB_IO_BUTTON_LEFT;
    if(held(mapping,MYGAMES_KVM_KEY_D))input->buttons|=MYSMB_IO_BUTTON_RIGHT;
    if(held(mapping,MYGAMES_KVM_KEY_W))input->buttons|=MYSMB_IO_BUTTON_UP;
    if(held(mapping,MYGAMES_KVM_KEY_S))input->buttons|=MYSMB_IO_BUTTON_DOWN;
    if(held(mapping,MYGAMES_KVM_KEY_J))input->buttons|=MYSMB_IO_BUTTON_B;
    if(held(mapping,MYGAMES_KVM_KEY_K))input->buttons|=MYSMB_IO_BUTTON_A;
    if(held(mapping,MYGAMES_KVM_KEY_ENTER))input->buttons|=MYSMB_IO_BUTTON_START;
    if(held(mapping,MYGAMES_KVM_KEY_LEFT_SHIFT) || held(mapping,MYGAMES_KVM_KEY_RIGHT_SHIFT))
        input->buttons|=MYSMB_IO_BUTTON_SELECT;
}

void mysmb_app_input_mapping_initialize(struct mysmb_app_input_mapping *mapping)
{
    mygames_kvm_u16 i;
    for(i=0U;i<16U;++i)mapping->down[i]=0U;
}

void mysmb_app_input_mapping_event(struct mysmb_app_input_mapping *mapping,
    const struct mygames_kvm_input_event *event, struct mysmb_io_input *input)
{
    if(event->kind!=MYGAMES_KVM_INPUT_KEY)return;
    if(event->physical_code<16U)mapping->down[event->physical_code]=event->down!=0U?1U:0U;
    if(event->down!=0U) {
        if(event->physical_code==MYGAMES_KVM_KEY_ESCAPE)input->requests|=MYSMB_IO_REQUEST_EXIT;
        if(event->physical_code==MYGAMES_KVM_KEY_P)input->requests|=MYSMB_IO_REQUEST_SAVE;
        if(event->physical_code==MYGAMES_KVM_KEY_O)input->requests|=MYSMB_IO_REQUEST_LOAD;
        if(event->physical_code==MYGAMES_KVM_KEY_TAB)input->requests|=MYSMB_IO_REQUEST_TOGGLE;
    }
    sample(mapping,input);
}
