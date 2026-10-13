#include "kvm/pointer.h"
unsigned short mygames_kvm_pointer_update(struct mygames_kvm_pointer *pointer,
    short x,short y,mygames_kvm_u16 buttons,mygames_kvm_u16 modifiers,
    mygames_kvm_u8 space,struct mygames_kvm_input_event *events)
{
    unsigned short changed,count=0U,bit,code;
    struct mygames_kvm_input_event event={0};
    buttons&=31U;changed=(unsigned short)(buttons^pointer->buttons);
    event.x=x;event.y=y;
    event.coordinate_space=space;event.modifiers=modifiers;
    if(changed) {
        for(bit=1U,code=1U;bit<=16U;bit<<=1,++code) {
            if(!(changed&bit))continue;
            pointer->buttons^=bit;event.kind=MYGAMES_KVM_INPUT_MOUSE_BUTTON;
            event.physical_code=code;event.down=(buttons&bit)!=0U;
            event.buttons=pointer->buttons;events[count++]=event;
        }
    } else if(x!=pointer->x || y!=pointer->y || space!=pointer->space) {
        event.kind=MYGAMES_KVM_INPUT_MOUSE_MOVE;event.buttons=buttons;
        events[count++]=event;
    }
    pointer->x=x;pointer->y=y;pointer->space=space;return count;
}
void mygames_kvm_pointer_cancel(struct mygames_kvm_pointer *pointer,
    struct mygames_kvm_input_event *event)
{
    struct mygames_kvm_input_event empty={0};
    *event=empty;event->kind=MYGAMES_KVM_INPUT_CANCEL;
    event->x=pointer->x;event->y=pointer->y;event->coordinate_space=pointer->space;
    pointer->buttons=0U;
}
