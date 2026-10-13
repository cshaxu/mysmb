#include <windows.h>
#include <string.h>

#include "win32/input.h"

static mygames_kvm_u16 mygames_win32_input_code(unsigned short key,
    unsigned short scan)
{
    if(key==VK_SHIFT) key=scan==0x36U?VK_RSHIFT:VK_LSHIFT;
    switch(key) {
    case 'A': return MYGAMES_KVM_KEY_A;
    case 'D': return MYGAMES_KVM_KEY_D;
    case 'W': return MYGAMES_KVM_KEY_W;
    case 'S': return MYGAMES_KVM_KEY_S;
    case 'J': return MYGAMES_KVM_KEY_J;
    case 'K': return MYGAMES_KVM_KEY_K;
    case 'P': return MYGAMES_KVM_KEY_P;
    case 'O': return MYGAMES_KVM_KEY_O;
    case VK_TAB: return MYGAMES_KVM_KEY_TAB;
    case VK_RETURN: return MYGAMES_KVM_KEY_ENTER;
    case VK_LSHIFT: return MYGAMES_KVM_KEY_LEFT_SHIFT;
    case VK_RSHIFT: return MYGAMES_KVM_KEY_RIGHT_SHIFT;
    case VK_ESCAPE: return MYGAMES_KVM_KEY_ESCAPE;
    case VK_LEFT: return MYGAMES_KVM_KEY_LEFT_ARROW;
    case VK_RIGHT: return MYGAMES_KVM_KEY_RIGHT_ARROW;
    case VK_UP: return MYGAMES_KVM_KEY_UP_ARROW;
    case VK_DOWN: return MYGAMES_KVM_KEY_DOWN_ARROW;
    default: return MYGAMES_KVM_KEY_NONE;
    }
}

void mygames_win32_input_initialize(struct mygames_win32_input *input)
{
    memset(input,0,sizeof(*input));
}

void mygames_win32_input_clear(struct mygames_win32_input *input)
{
    memset(input,0,sizeof(*input));
}

int mygames_win32_input_key(struct mygames_win32_input *input,
    unsigned short key,unsigned short scan,unsigned char down,
    struct mygames_kvm_input_event *event)
{
    mygames_kvm_u16 code=mygames_win32_input_code(key,scan);
    if(code==MYGAMES_KVM_KEY_NONE)return 0;
    event->kind=MYGAMES_KVM_INPUT_KEY;
    event->down=down!=0U?1U:0U;
    event->repeat=down!=0U && input->down[code]!=0U?1U:0U;
    event->physical_code=code;
    event->native_scan=scan;
    event->modifiers=0U;
    event->x=0U;
    event->y=0U;
    input->down[code]=event->down;
    return event->repeat!=0U?2:1;
}
