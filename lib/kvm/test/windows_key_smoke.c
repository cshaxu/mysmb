#include "kvm/windows_key.h"
int main(void)
{
    static const unsigned short codes[]={
        'A','D','W','S','J','K','P','O',9U,13U,0xa0U,0xa1U,27U,
        0x25U,0x27U,0x26U,0x28U};
    static const unsigned short expected[]={
        MYGAMES_KVM_KEY_A,MYGAMES_KVM_KEY_D,MYGAMES_KVM_KEY_W,MYGAMES_KVM_KEY_S,
        MYGAMES_KVM_KEY_J,MYGAMES_KVM_KEY_K,MYGAMES_KVM_KEY_P,MYGAMES_KVM_KEY_O,
        MYGAMES_KVM_KEY_TAB,MYGAMES_KVM_KEY_ENTER,MYGAMES_KVM_KEY_LEFT_SHIFT,
        MYGAMES_KVM_KEY_RIGHT_SHIFT,MYGAMES_KVM_KEY_ESCAPE,
        MYGAMES_KVM_KEY_LEFT_ARROW,MYGAMES_KVM_KEY_RIGHT_ARROW,
        MYGAMES_KVM_KEY_UP_ARROW,MYGAMES_KVM_KEY_DOWN_ARROW};
    unsigned short i;
    for(i=0U;i<sizeof(codes)/sizeof(codes[0]);++i)
        if(mygames_kvm_windows_key(codes[i],0U)!=expected[i])return 1;
    if(mygames_kvm_windows_key(0x10U,0x2aU)!=MYGAMES_KVM_KEY_LEFT_SHIFT ||
        mygames_kvm_windows_key(0x10U,0x36U)!=MYGAMES_KVM_KEY_RIGHT_SHIFT)return 2;
    if(mygames_kvm_windows_key(0xffffU,0U)!=MYGAMES_KVM_KEY_NONE)return 3;
    return 0;
}
