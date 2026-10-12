#include "platform/win32/text_console.h"

int mysmb_win32_text_console_key(struct mysmb_win32_text_console *console,
    WORD *key,WORD *scan,unsigned char *pressed)
{
    DWORD count,read;
    INPUT_RECORD event;
    if(!console->opened || !GetNumberOfConsoleInputEvents(console->input,&count) || count==0U ||
        !ReadConsoleInputW(console->input,&event,1U,&read) || read!=1U)return 0;
    *key=*scan=0U;*pressed=0U;
    if(event.EventType==FOCUS_EVENT) {
        /* Internal focus records are optional release/pause hints only.
         * A host need not send them before delivering a valid key down. */
        *pressed=event.Event.FocusEvent.bSetFocus?1U:0U;
        console->focused=*pressed;return 2;
    }
    if(event.EventType==KEY_EVENT) {
        *key=event.Event.KeyEvent.wVirtualKeyCode;
        *scan=event.Event.KeyEvent.wVirtualScanCode;
        *pressed=event.Event.KeyEvent.bKeyDown?1U:0U;
        if(!*key) {
            WORD character=(WORD)event.Event.KeyEvent.uChar.UnicodeChar;
            if(character>='a' && character<='z')character=(WORD)(character-'a'+'A');
            if((character>='A' && character<='Z') || character==VK_TAB ||
                character==VK_RETURN || character==VK_ESCAPE)*key=character;
        }
        /* Delivered key downs establish device input without foreground or
         * a mandatory gain record. Key ups never undo a prior loss hint. */
        if(*pressed && *key)console->focused=1U;
    }
    return 1;
}

