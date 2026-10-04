#include "platform/dos16/dos16_root.h"
#include "platform/dos16/keyboard.h"
struct host { unsigned calls; };
static void read_input(void *context, struct mysmb_io_input *input)
{ (void)context; input->buttons=0U; input->buttons2=0U; }
static void present(void *context, const struct mysmb_io_video_frame *frame)
{ if (frame->pixels!=0) ++((struct host *)context)->calls; }
int main(void)
{
    static struct mysmb_dos16_root root;
    struct mysmb_dos16_hooks hooks;
    struct mysmb_dos16_keyboard keyboard;
    struct mysmb_io_input input;
    struct host host;
    mysmb_dos16_keyboard_initialize(&keyboard);
    mysmb_dos16_keyboard_scan(&keyboard,0x20U);
    mysmb_dos16_keyboard_scan(&keyboard,0x24U);
    mysmb_dos16_keyboard_scan(&keyboard,0x25U);
    mysmb_dos16_keyboard_scan(&keyboard,0x2aU);
    mysmb_dos16_keyboard_input(&keyboard,&input);
    if (input.buttons!=(MYSMB_IO_BUTTON_RIGHT|MYSMB_IO_BUTTON_B|MYSMB_IO_BUTTON_A|MYSMB_IO_BUTTON_SELECT)) return 1;
    mysmb_dos16_keyboard_scan(&keyboard,0xa0U);
    mysmb_dos16_keyboard_scan(&keyboard,0xa4U);
    mysmb_dos16_keyboard_scan(&keyboard,0xa5U);
    mysmb_dos16_keyboard_scan(&keyboard,0xaaU);
    mysmb_dos16_keyboard_scan(&keyboard,0x36U);
    mysmb_dos16_keyboard_input(&keyboard,&input);
    if (input.buttons!=MYSMB_IO_BUTTON_SELECT) return 2;
    mysmb_dos16_keyboard_scan(&keyboard,0xb6U);
    mysmb_dos16_keyboard_scan(&keyboard,0xe0U);
    mysmb_dos16_keyboard_scan(&keyboard,0x4bU);
    mysmb_dos16_keyboard_scan(&keyboard,0xe0U);
    mysmb_dos16_keyboard_scan(&keyboard,0x2aU);
    mysmb_dos16_keyboard_input(&keyboard,&input);
    if (input.buttons!=MYSMB_IO_BUTTON_LEFT) return 3;
    mysmb_dos16_keyboard_scan(&keyboard,0xe0U);
    mysmb_dos16_keyboard_scan(&keyboard,0xcbU);
    mysmb_dos16_keyboard_scan(&keyboard,0xe1U);
    mysmb_dos16_keyboard_scan(&keyboard,0x1dU);
    mysmb_dos16_keyboard_scan(&keyboard,0x45U);
    mysmb_dos16_keyboard_scan(&keyboard,0xe1U);
    mysmb_dos16_keyboard_scan(&keyboard,0x9dU);
    mysmb_dos16_keyboard_scan(&keyboard,0xc5U);
    mysmb_dos16_keyboard_input(&keyboard,&input);
    if (input.buttons!=0U || input.buttons2!=0U) return 4;
    host.calls=0U; hooks.context=&host; hooks.read_input=read_input; hooks.present_video=present;
    if (mysmb_dos16_root_initialize(&root,0)!=0) return 5;
    if (!mysmb_dos16_root_initialize(&root,&hooks)) return 6;
    mysmb_dos16_root_step(&root); mysmb_dos16_root_step(&root);
    if (root.game.frame_number!=0UL || host.calls!=0U) return 7;
    mysmb_dos16_root_step(&root);
    if (root.game.frame_number!=1UL || host.calls!=1U) return 8;
    mysmb_dos16_root_shutdown(&root); mysmb_dos16_root_shutdown(&root);
    mysmb_dos16_root_step(&root);
    return host.calls==1U ? 0:9;
}
