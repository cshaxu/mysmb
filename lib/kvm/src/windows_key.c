#include "kvm/windows_key.h"

mygames_kvm_u16 mygames_kvm_windows_key(mygames_kvm_u16 key,
    mygames_kvm_u16 scan)
{
    if(key==0x10U)key=scan==0x36U?0xa1U:0xa0U;
    switch(key) {
    case 'A': return MYGAMES_KVM_KEY_A;
    case 'D': return MYGAMES_KVM_KEY_D;
    case 'W': return MYGAMES_KVM_KEY_W;
    case 'S': return MYGAMES_KVM_KEY_S;
    case 'J': return MYGAMES_KVM_KEY_J;
    case 'K': return MYGAMES_KVM_KEY_K;
    case 'P': return MYGAMES_KVM_KEY_P;
    case 'O': return MYGAMES_KVM_KEY_O;
    case 0x09U: return MYGAMES_KVM_KEY_TAB;
    case 0x0dU: return MYGAMES_KVM_KEY_ENTER;
    case 0xa0U: return MYGAMES_KVM_KEY_LEFT_SHIFT;
    case 0xa1U: return MYGAMES_KVM_KEY_RIGHT_SHIFT;
    case 0x1bU: return MYGAMES_KVM_KEY_ESCAPE;
    case 0x25U: return MYGAMES_KVM_KEY_LEFT_ARROW;
    case 0x27U: return MYGAMES_KVM_KEY_RIGHT_ARROW;
    case 0x26U: return MYGAMES_KVM_KEY_UP_ARROW;
    case 0x28U: return MYGAMES_KVM_KEY_DOWN_ARROW;
    default: return MYGAMES_KVM_KEY_NONE;
    }
}
