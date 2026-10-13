#ifndef MYGAMES_KVM_POINTER_H
#define MYGAMES_KVM_POINTER_H
#include "kvm/input_event.h"
#define MYGAMES_KVM_POINTER_EVENTS 5U
struct mygames_kvm_pointer {short x,y;mygames_kvm_u16 buttons;mygames_kvm_u8 space;};
/* At most five ordered button transitions, or one move. The caller owns
 * output storage; negative/outside positions are deliberately preserved. */
unsigned short mygames_kvm_pointer_update(struct mygames_kvm_pointer *pointer,
    short x,short y,mygames_kvm_u16 buttons,mygames_kvm_u16 modifiers,
    mygames_kvm_u8 space,struct mygames_kvm_input_event *events);
void mygames_kvm_pointer_cancel(struct mygames_kvm_pointer *pointer,
    struct mygames_kvm_input_event *event);
#endif
