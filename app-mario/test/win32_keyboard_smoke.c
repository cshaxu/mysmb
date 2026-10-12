#include <windows.h>
#include "platform/win32/keyboard.h"
int main(void)
{
    struct mysmb_win32_keyboard keyboard;
    mysmb_win32_keyboard_reset(&keyboard);
    if(mysmb_win32_keyboard_sample(&keyboard))return 1;
    mysmb_win32_keyboard_event(&keyboard,'J',0U,1U);
    mysmb_win32_keyboard_event(&keyboard,'J',0U,0U);
    if(mysmb_win32_keyboard_sample(&keyboard)!=MYSMB_WIN32_KEY_B ||
        mysmb_win32_keyboard_sample(&keyboard))return 2;
    mysmb_win32_keyboard_event(&keyboard,VK_SHIFT,0x2aU,1U);
    mysmb_win32_keyboard_event(&keyboard,VK_SHIFT,0x36U,1U);
    if(mysmb_win32_keyboard_sample(&keyboard)!=MYSMB_WIN32_KEY_SELECT)return 3;
    mysmb_win32_keyboard_event(&keyboard,VK_SHIFT,0x2aU,0U);
    if(mysmb_win32_keyboard_sample(&keyboard)!=MYSMB_WIN32_KEY_SELECT)return 4;
    mysmb_win32_keyboard_event(&keyboard,VK_SHIFT,0x36U,0U);
    if(mysmb_win32_keyboard_sample(&keyboard))return 5;
    mysmb_win32_keyboard_event(&keyboard,'K',0U,1U);
    mysmb_win32_keyboard_reset(&keyboard);
    if(mysmb_win32_keyboard_sample(&keyboard) ||
        mysmb_win32_keyboard_event(&keyboard,256U,0U,1U) ||
        mysmb_win32_keyboard_event(&keyboard,VK_F1,0U,1U))return 6;
    mysmb_win32_keyboard_event(&keyboard,'A',0U,1U);
    mysmb_win32_keyboard_event(&keyboard,VK_LEFT,0U,1U);
    (void)mysmb_win32_keyboard_sample(&keyboard);
    mysmb_win32_keyboard_event(&keyboard,'A',0U,0U);
    if(mysmb_win32_keyboard_sample(&keyboard)!=MYSMB_WIN32_KEY_LEFT)return 7;
    mysmb_win32_keyboard_event(&keyboard,VK_TAB,0U,1U);
    mysmb_win32_keyboard_event(&keyboard,'O',0U,1U);
    mysmb_win32_keyboard_clear_game(&keyboard);
    if(mysmb_win32_keyboard_sample(&keyboard) ||
        mysmb_win32_keyboard_event(&keyboard,VK_TAB,0U,1U)!=2 ||
        mysmb_win32_keyboard_event(&keyboard,'O',0U,1U)!=2)return 8;
    mysmb_win32_keyboard_event(&keyboard,VK_TAB,0U,0U);
    if(mysmb_win32_keyboard_event(&keyboard,VK_TAB,0U,1U)!=1)return 9;
    return 0;
}
