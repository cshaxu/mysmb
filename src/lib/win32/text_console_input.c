#include <string.h>
#include "win32/text_console.h"
static unsigned short modifiers(DWORD flags)
{
    return (unsigned short)((flags&SHIFT_PRESSED?MYGAMES_KVM_MOD_SHIFT:0U)|
        (flags&(LEFT_CTRL_PRESSED|RIGHT_CTRL_PRESSED)?MYGAMES_KVM_MOD_CONTROL:0U)|
        (flags&(LEFT_ALT_PRESSED|RIGHT_ALT_PRESSED)?MYGAMES_KVM_MOD_ALT:0U));
}
int mygames_win32_text_console_event(struct mygames_win32_text_console *console,
    struct mygames_win32_input *keys,struct mygames_kvm_input_event *out)
{
    DWORD count,read,buttons;
    INPUT_RECORD event;
    CONSOLE_SCREEN_BUFFER_INFO info;
    WORD key,scan,character;
    unsigned short mask;
    short x,y;
    memset(out,0,sizeof(*out));
    if(console->pending_at<console->pending_count) {
        *out=console->pending[console->pending_at++];return 1;
    }
    console->pending_at=console->pending_count=0U;
    if(!console->opened || console->suspended ||
        !GetNumberOfConsoleInputEvents(console->input,&count) || !count ||
        !ReadConsoleInputW(console->input,&event,1U,&read) || read!=1U)return 0;
    if(event.EventType==FOCUS_EVENT) {
        console->focused=event.Event.FocusEvent.bSetFocus?1U:0U;
        if(!console->focused) {
            mygames_win32_input_clear(keys);
            mygames_kvm_pointer_cancel(&console->pointer,console->pending);
            console->pending_count=1U;
        }
        out->kind=MYGAMES_KVM_INPUT_FOCUS;out->down=console->focused;return 1;
    }
    if(event.EventType==KEY_EVENT) {
        key=event.Event.KeyEvent.wVirtualKeyCode;
        scan=event.Event.KeyEvent.wVirtualScanCode;
        if(!key) {
            character=(WORD)event.Event.KeyEvent.uChar.UnicodeChar;
            if(character>='a' && character<='z')character=(WORD)(character-'a'+'A');
            if((character>='A' && character<='Z') || (character>='0' && character<='9') ||
                character==VK_TAB || character==VK_RETURN || character==VK_ESCAPE)key=character;
        }
        if(event.Event.KeyEvent.bKeyDown && key)console->focused=1U;
        (void)mygames_win32_input_key(keys,key,scan,
            (unsigned char)(event.Event.KeyEvent.bKeyDown!=0),out);
        out->modifiers=modifiers(event.Event.KeyEvent.dwControlKeyState);return 1;
    }
    if(event.EventType==MOUSE_EVENT) {
        /* Wheel records are not button presses. Coordinates are viewport cells,
         * not screen-buffer coordinates; negative positions remain outside. */
        if(event.Event.MouseEvent.dwEventFlags&~(MOUSE_MOVED|DOUBLE_CLICK))return 1;
        if(!GetConsoleScreenBufferInfo(console->output,&info))return 1;
        x=(short)(event.Event.MouseEvent.dwMousePosition.X-info.srWindow.Left);
        y=(short)(event.Event.MouseEvent.dwMousePosition.Y-info.srWindow.Top);
        buttons=event.Event.MouseEvent.dwButtonState;
        mask=(unsigned short)((buttons&FROM_LEFT_1ST_BUTTON_PRESSED?1U:0U)|
            (buttons&RIGHTMOST_BUTTON_PRESSED?2U:0U)|
            (buttons&FROM_LEFT_2ND_BUTTON_PRESSED?4U:0U)|
            (buttons&FROM_LEFT_3RD_BUTTON_PRESSED?8U:0U)|
            (buttons&FROM_LEFT_4TH_BUTTON_PRESSED?16U:0U));
        console->pending_count=mygames_kvm_pointer_update(&console->pointer,x,y,mask,
            modifiers(event.Event.MouseEvent.dwControlKeyState),
            MYGAMES_KVM_COORD_TEXT_CELLS,console->pending);
        if(console->pending_count)*out=console->pending[console->pending_at++];
        return 1;
    }
    if(event.EventType==WINDOW_BUFFER_SIZE_EVENT) {
        out->kind=MYGAMES_KVM_INPUT_RESIZE;
        if(GetConsoleScreenBufferInfo(console->output,&info)) {
            out->x=(short)(info.srWindow.Right-info.srWindow.Left+1);
            out->y=(short)(info.srWindow.Bottom-info.srWindow.Top+1);
        }
        out->coordinate_space=MYGAMES_KVM_COORD_TEXT_CELLS;
    }
    return 1;
}
