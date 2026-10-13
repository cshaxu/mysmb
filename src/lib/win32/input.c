#include <windows.h>
#include <string.h>

#include "win32/input.h"
#include "kvm/windows_key.h"

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
    mygames_kvm_u16 code=mygames_kvm_windows_key(key,scan);
    if(code==MYGAMES_KVM_KEY_NONE)return 0;
    memset(event,0,sizeof(*event));
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
