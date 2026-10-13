#include <windows.h>
#include "app/input_mapping.h"
#include "win32/input.h"
int main(void)
{
    struct mygames_win32_input host;
    struct mygames_kvm_input_event event;
    struct mysmb_app_input_mapping mario;
    struct mysmb_io_input input,before;
    mygames_win32_input_initialize(&host);
    mysmb_app_input_mapping_initialize(&mario);
    input.buttons=input.buttons2=input.requests=0U;
    if(mygames_win32_input_key(&host,'J',0U,1U,&event)!=1 ||
        event.physical_code!=MYGAMES_KVM_KEY_J || event.repeat!=0U)return 1;
    mysmb_app_input_mapping_event(&mario,&event,&input);
    if((input.buttons&MYSMB_IO_BUTTON_B)==0U)return 2;
    if(mygames_win32_input_key(&host,'J',0U,1U,&event)!=2 || event.repeat!=1U)return 3;
    if(mygames_win32_input_key(&host,VK_SHIFT,0x2aU,1U,&event)!=1 ||
        event.physical_code!=MYGAMES_KVM_KEY_LEFT_SHIFT)return 4;
    mysmb_app_input_mapping_event(&mario,&event,&input);
    if((input.buttons&MYSMB_IO_BUTTON_SELECT)==0U)return 5;
    if(mygames_win32_input_key(&host,VK_LEFT,0U,1U,&event)!=1 ||
        event.physical_code!=MYGAMES_KVM_KEY_LEFT_ARROW)return 6;
    mysmb_app_input_mapping_event(&mario,&event,&input);
    if((input.buttons&MYSMB_IO_BUTTON_LEFT)==0U)return 7;
    if(mygames_win32_input_key(&host,VK_DOWN,0U,1U,&event)!=1 ||
        event.physical_code!=MYGAMES_KVM_KEY_DOWN_ARROW)return 8;
    mysmb_app_input_mapping_event(&mario,&event,&input);
    if((input.buttons&MYSMB_IO_BUTTON_DOWN)==0U)return 9;
    before=input;
    if(mygames_win32_input_key(&host,VK_F1,0U,1U,&event)!=1)return 10;
    mysmb_app_input_mapping_event(&mario,&event,&input);
    if(input.buttons!=before.buttons || input.buttons2!=before.buttons2 ||
        input.requests!=before.requests)return 11;
    return 0;
}
