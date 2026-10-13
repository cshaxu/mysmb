#include <string.h>
#include "kvm/pointer.h"
int main(void)
{
    struct mygames_kvm_pointer state;
    struct mygames_kvm_input_event events[5];
    unsigned short n,i;
    memset(&state,0,sizeof(state));
    n=mygames_kvm_pointer_update(&state,-3,5,0,0,MYGAMES_KVM_COORD_CLIENT_PIXELS,events);
    if(n!=1 || events[0].x!=-3 || events[0].kind!=MYGAMES_KVM_INPUT_MOUSE_MOVE)return 1;
    if(mygames_kvm_pointer_update(&state,-3,5,0,0,MYGAMES_KVM_COORD_CLIENT_PIXELS,events))return 2;
    n=mygames_kvm_pointer_update(&state,-3,5,31,7,MYGAMES_KVM_COORD_CLIENT_PIXELS,events);
    if(n!=5)return 3;
    for(i=0;i<5;++i)if(events[i].physical_code!=i+1 || !events[i].down ||
        events[i].buttons!=(1U<<(i+1))-1U || events[i].modifiers!=7)return 4;
    n=mygames_kvm_pointer_update(&state,99,-99,31,0,MYGAMES_KVM_COORD_CLIENT_PIXELS,events);
    if(n!=1 || events[0].buttons!=31 || events[0].y!=-99)return 5;
    n=mygames_kvm_pointer_update(&state,99,-99,0,0,MYGAMES_KVM_COORD_CLIENT_PIXELS,events);
    if(n!=5 || events[4].buttons || events[0].down)return 6;
    mygames_kvm_pointer_update(&state,3,4,3,0,MYGAMES_KVM_COORD_TEXT_CELLS,events);
    mygames_kvm_pointer_cancel(&state,events);
    if(state.buttons || events[0].kind!=MYGAMES_KVM_INPUT_CANCEL || events[0].buttons ||
        events[0].coordinate_space!=MYGAMES_KVM_COORD_TEXT_CELLS)return 7;
    return 0;
}
