#include "platform/win32/text_console.h"
#include "platform/win32/launch.h"
#include "io/color.h"
#include "io/text_glyph.h"
#ifndef ENABLE_VIRTUAL_TERMINAL_INPUT
#define ENABLE_VIRTUAL_TERMINAL_INPUT 0x0200U
#endif
static HWND exit_owner;
static volatile LONG close_pending;
static BOOL WINAPI mysmb_win32_console_control(DWORD event)
{
    if(event!=CTRL_CLOSE_EVENT)return FALSE;
    InterlockedExchange(&close_pending,1L);
    if(PostMessage(exit_owner,WM_CLOSE,0U,0L))
        /* Returning before the root exits causes STATUS_CONTROL_C_EXIT.
         * Normal CRT process exit stops this thread after device cleanup.
         * The bounded wait lets Windows terminate a genuinely hung root. */
        (void)WaitForSingleObject(GetCurrentProcess(),4000U);
    return TRUE;
}
int mysmb_win32_text_console_open(struct mysmb_win32_text_console *console,
    HWND owner)
{
    COORD size;
    SMALL_RECT tiny,view;
    CONSOLE_CURSOR_INFO cursor;
    CONSOLE_FONT_INFOEX font;
    DWORD mode;
    CONSOLE_SCREEN_BUFFER_INFOEX info;
    unsigned int i;
    unsigned long rgb;
    DWORD processes[2];
    if(console->opened)return 1;
    if(!owner)return 0;
    if(GetConsoleWindow()!=NULL) {
        if(!mysmb_win32_start_in_text())return 0;
        console->borrowed=GetConsoleProcessList(processes,2U)>1U?1U:0U;
    } else if(mysmb_win32_start_in_text() && AttachConsole(ATTACH_PARENT_PROCESS))
        console->borrowed=1U;
    else {
        if(!AllocConsole())return 0;
        console->borrowed=0U;
    }
    console->opened=1U;
    exit_owner=owner;
    InterlockedExchange(&close_pending,0L);
    if(!SetConsoleCtrlHandler(mysmb_win32_console_control,TRUE)) {
        mysmb_win32_text_console_close(console);return 0;
    }
    /* Standard handles may be redirected or absent for a GUI/RDP launcher.
     * Own explicit console devices rather than borrowing process stdio. */
    console->input=CreateFileA("CONIN$",GENERIC_READ|GENERIC_WRITE,
        FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0U,NULL);
    console->window=GetConsoleWindow();
    if(console->input==INVALID_HANDLE_VALUE) {
        mysmb_win32_text_console_close(console);return 0;
    }
    if(console->borrowed) {
        console->shell_output=CreateFileA("CONOUT$",GENERIC_READ|GENERIC_WRITE,
            FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0U,NULL);
        console->shell_title=(WCHAR *)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,
            65536UL*sizeof(WCHAR));
        console->shell_placement.length=sizeof(console->shell_placement);
        if(console->shell_output==INVALID_HANDLE_VALUE || !console->shell_title ||
            !GetConsoleMode(console->input,&console->shell_input_mode) ||
            !GetWindowPlacement(console->window,&console->shell_placement)) {
            mysmb_win32_text_console_close(console);return 0;
        }
        console->mode_saved=1U;
        (void)GetConsoleTitleW(console->shell_title,65536U);
        console->output=CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE,
            FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,CONSOLE_TEXTMODE_BUFFER,NULL);
    } else console->output=CreateFileA("CONOUT$",GENERIC_READ|GENERIC_WRITE,
        FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0U,NULL);
    if(console->output==INVALID_HANDLE_VALUE) {
        mysmb_win32_text_console_close(console);return 0;
    }
    ZeroMemory(&font,sizeof(font));font.cbSize=sizeof(font);
    font.dwFontSize.X=8;font.dwFontSize.Y=8;font.FontWeight=FW_NORMAL;
    lstrcpyW(font.FaceName,L"Consolas");
    (void)SetCurrentConsoleFontEx(console->output,FALSE,&font);
    /* A small remote/headless desktop may not fit fifty rows at eight pixels.
     * Adapt only the device font;the shared frame and buffer stay80x50. */
    for(i=7U;i>=4U;--i) {
        COORD maximum;
        maximum=GetLargestConsoleWindowSize(console->output);
        if(maximum.X>=80 && maximum.Y>=50)break;
        font.dwFontSize.X=0;font.dwFontSize.Y=(SHORT)i;
        (void)SetCurrentConsoleFontEx(console->output,FALSE,&font);
    }
    tiny.Left=tiny.Top=tiny.Right=tiny.Bottom=0;
    size.X=80;size.Y=50;
    view.Left=view.Top=0;view.Right=79;view.Bottom=49;
    ZeroMemory(&info,sizeof(info));info.cbSize=sizeof(info);
    if(!GetConsoleScreenBufferInfoEx(console->output,&info)) {
        mysmb_win32_text_console_close(console);return 0;
    }
    for(i=0U;i<16U;++i) {
        rgb=mysmb_io_color_text_rgb((mysmb_io_u8)i);
        info.ColorTable[i]=RGB((rgb>>16U)&255UL,(rgb>>8U)&255UL,rgb&255UL);
    }
    if(!SetConsoleScreenBufferInfoEx(console->output,&info) ||
        !SetConsoleActiveScreenBuffer(console->output)) {
        mysmb_win32_text_console_close(console);return 0;
    }
    if(console->window==NULL || !GetConsoleMode(console->input,&mode) ||
        !SetConsoleMode(console->input,(mode|ENABLE_EXTENDED_FLAGS|ENABLE_WINDOW_INPUT)&
            ~(ENABLE_QUICK_EDIT_MODE|ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT|
                ENABLE_PROCESSED_INPUT|ENABLE_VIRTUAL_TERMINAL_INPUT)) ||
        !SetConsoleWindowInfo(console->output,TRUE,&tiny) ||
        !SetConsoleScreenBufferSize(console->output,size) ||
        !SetConsoleWindowInfo(console->output,TRUE,&view)) {
        mysmb_win32_text_console_close(console);return 0;
    }
    cursor.dwSize=1;cursor.bVisible=FALSE;
    (void)SetConsoleCursorInfo(console->output,&cursor);
    (void)SetConsoleTitleA("MySMB");
    /* Close requests the same root-owned exit as Escape and the GUI button. */
    if(!console->borrowed && EnableMenuItem(GetSystemMenu(console->window,FALSE),SC_CLOSE,
        MF_BYCOMMAND|MF_ENABLED)==(UINT)-1) {
        mysmb_win32_text_console_close(console);return 0;
    }
    return 1;
}
void mysmb_win32_text_console_close(struct mysmb_win32_text_console *console)
{
    if(!console->opened)return;
    if(console->borrowed) {
        if(console->shell_output && console->shell_output!=INVALID_HANDLE_VALUE)
            (void)SetConsoleActiveScreenBuffer(console->shell_output);
        if(console->mode_saved) {
            (void)SetConsoleMode(console->input,console->shell_input_mode);
            (void)SetConsoleTitleW(console->shell_title);
            (void)SetWindowPlacement(console->window,&console->shell_placement);
        }
        /* Discard game key breaks/shortcuts before returning input to shell. */
        if(console->input && console->input!=INVALID_HANDLE_VALUE)
            (void)FlushConsoleInputBuffer(console->input);
    }
    if(console->input && console->input!=INVALID_HANDLE_VALUE)CloseHandle(console->input);
    if(console->output && console->output!=INVALID_HANDLE_VALUE)CloseHandle(console->output);
    if(console->shell_output && console->shell_output!=INVALID_HANDLE_VALUE)
        CloseHandle(console->shell_output);
    if(console->shell_title)HeapFree(GetProcessHeap(),0U,console->shell_title);
    /* During host close,detaching/unregistering can hand termination back to
     * the default handler before the CRT exit. Leave attachment teardown to
     * process exit;ordinary Tab/recovery detaches immediately. */
    if(!InterlockedCompareExchange(&close_pending,0L,0L)) {
        (void)SetConsoleCtrlHandler(mysmb_win32_console_control,FALSE);
        FreeConsole();
    }
    console->opened=0U;console->window=NULL;
    console->input=console->output=NULL;
    console->shell_output=NULL;console->shell_title=NULL;
    console->borrowed=console->mode_saved=0U;
}
int mysmb_win32_text_console_present(struct mysmb_win32_text_console *console,
    const struct mysmb_io_text_frame *frame)
{
    unsigned short i;
    COORD size,origin;
    SMALL_RECT view;
    if(!console->opened || frame==0)return 0;
    for(i=0U;i<MYSMB_IO_TEXT_CELLS;++i) {
        console->cells[i].Char.UnicodeChar=(WCHAR)mysmb_io_text_glyph_unicode(frame->cells[i].character);
        if(console->cells[i].Char.UnicodeChar==0U)return 0;
        console->cells[i].Attributes=(WORD)((frame->cells[i].foreground&15U)|
            ((frame->cells[i].background&15U)<<4U));
    }
    size.X=80;size.Y=50;origin.X=origin.Y=0;
    view.Left=view.Top=0;view.Right=79;view.Bottom=49;
    /* Windows reports the actual rectangle;success alone permits clipping.
     * A partial frame must reach the root's graphical recovery path. */
    return WriteConsoleOutputW(console->output,console->cells,size,origin,&view)!=0 &&
        view.Left==0 && view.Top==0 && view.Right==79 && view.Bottom==49;
}
int mysmb_win32_text_console_key(struct mysmb_win32_text_console *console,
    WORD *key,WORD *scan,unsigned char *pressed)
{
    DWORD count,read;
    INPUT_RECORD event;
    if(!console->opened || !GetNumberOfConsoleInputEvents(console->input,&count) ||
        count==0U || !ReadConsoleInputA(console->input,&event,1U,&read) || read!=1U)return 0;
    *key=*scan=0U;*pressed=0U;
    if(event.EventType==FOCUS_EVENT) {
        *pressed=event.Event.FocusEvent.bSetFocus?1U:0U;return 2;
    }
    if(event.EventType==KEY_EVENT) {
        *key=event.Event.KeyEvent.wVirtualKeyCode;
        *scan=event.Event.KeyEvent.wVirtualScanCode;
        *pressed=event.Event.KeyEvent.bKeyDown?1U:0U;
    }
    return 1;
}
