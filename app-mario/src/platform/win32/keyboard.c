#include <windows.h>
#include <string.h>
#include "platform/win32/keyboard.h"
static unsigned int mysmb_win32_key_mask(unsigned int key)
{
    switch(key) {
    case 'A':case VK_LEFT:return MYSMB_WIN32_KEY_LEFT;
    case 'D':case VK_RIGHT:return MYSMB_WIN32_KEY_RIGHT;
    case 'S':case VK_DOWN:return MYSMB_WIN32_KEY_DOWN;
    case 'W':case VK_UP:return MYSMB_WIN32_KEY_UP;
    case VK_RETURN:return MYSMB_WIN32_KEY_START;
    case VK_LSHIFT:case VK_RSHIFT:return MYSMB_WIN32_KEY_SELECT;
    case 'J':return MYSMB_WIN32_KEY_B;
    case 'K':return MYSMB_WIN32_KEY_A;
    default:return 0U;
    }
}
void mysmb_win32_keyboard_reset(struct mysmb_win32_keyboard *keyboard)
{
    memset(keyboard,0,sizeof(*keyboard));
}
void mysmb_win32_keyboard_clear_game(struct mysmb_win32_keyboard *keyboard)
{
    unsigned int key;
    for(key=0U;key<256U;++key)if(mysmb_win32_key_mask(key))
        keyboard->held[key]=keyboard->pressed[key]=0U;
}
int mysmb_win32_keyboard_event(struct mysmb_win32_keyboard *keyboard,
    unsigned short key,unsigned short scan,unsigned char down)
{
    /* Window/console generic Shift records retain independent physical sides. */
    if(key==VK_SHIFT)key=scan==0x36U?VK_RSHIFT:VK_LSHIFT;
    if(key>=256U || (!mysmb_win32_key_mask(key) && key!=VK_TAB &&
        key!=VK_ESCAPE && key!='P' && key!='O'))return 0;
    if(down && keyboard->held[key])return 2;
    if(down && !keyboard->held[key])keyboard->pressed[key]=1U;
    keyboard->held[key]=down?1U:0U;
    return 1;
}
unsigned int mysmb_win32_keyboard_sample(struct mysmb_win32_keyboard *keyboard)
{
    unsigned int key,keys;
    keys=0U;
    for(key=0U;key<256U;++key) {
        if(keyboard->held[key] || keyboard->pressed[key])
            keys|=mysmb_win32_key_mask(key);
        keyboard->pressed[key]=0U;
    }
    return keys;
}
