#include "platform/win32/text_console.h"
#include "io/color.h"
#include "io/text_glyph.h"
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
    if(console->opened)return 1;
    if(!owner)return 0;
    if(!AllocConsole())return 0;
    console->opened=1U;
    exit_owner=owner;
    InterlockedExchange(&close_pending,0L);
    if(!SetConsoleCtrlHandler(mysmb_win32_console_control,TRUE)) {
        mysmb_win32_text_console_close(console);return 0;
    }
    console->input=GetStdHandle(STD_INPUT_HANDLE);
    console->output=GetStdHandle(STD_OUTPUT_HANDLE);
    console->window=GetConsoleWindow();
    ZeroMemory(&font,sizeof(font));font.cbSize=sizeof(font);
    font.dwFontSize.X=8;font.dwFontSize.Y=8;font.FontWeight=FW_NORMAL;
    lstrcpyW(font.FaceName,L"Consolas");
    (void)SetCurrentConsoleFontEx(console->output,FALSE,&font);
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
    if(!SetConsoleScreenBufferInfoEx(console->output,&info)) {
        mysmb_win32_text_console_close(console);return 0;
    }
    if(console->window==NULL || !GetConsoleMode(console->input,&mode) ||
        !SetConsoleMode(console->input,(mode|ENABLE_EXTENDED_FLAGS)&
            ~(ENABLE_QUICK_EDIT_MODE|ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT|ENABLE_PROCESSED_INPUT)) ||
        !SetConsoleWindowInfo(console->output,TRUE,&tiny) ||
        !SetConsoleScreenBufferSize(console->output,size) ||
        !SetConsoleWindowInfo(console->output,TRUE,&view)) {
        mysmb_win32_text_console_close(console);return 0;
    }
    cursor.dwSize=1;cursor.bVisible=FALSE;
    (void)SetConsoleCursorInfo(console->output,&cursor);
    (void)SetConsoleTitleA("MySMB text preview - Tab: graphics");
    /* Close requests the same root-owned exit as Escape and the GUI button. */
    if(EnableMenuItem(GetSystemMenu(console->window,FALSE),SC_CLOSE,
        MF_BYCOMMAND|MF_ENABLED)==(UINT)-1) {
        mysmb_win32_text_console_close(console);return 0;
    }
    return 1;
}
void mysmb_win32_text_console_close(struct mysmb_win32_text_console *console)
{
    if(!console->opened)return;
    /* During host close,detaching/unregistering can hand termination back to
     * the default handler before the CRT exit. Leave attachment teardown to
     * process exit;ordinary Tab/recovery detaches immediately. */
    if(!InterlockedCompareExchange(&close_pending,0L,0L)) {
        (void)SetConsoleCtrlHandler(mysmb_win32_console_control,FALSE);
        FreeConsole();
    }
    console->opened=0U;console->window=NULL;
    console->input=console->output=NULL;
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
    WORD *key,unsigned char *pressed)
{
    DWORD count,read;
    INPUT_RECORD event;
    if(!console->opened || !GetNumberOfConsoleInputEvents(console->input,&count) ||
        count==0U || !ReadConsoleInputA(console->input,&event,1U,&read) || read!=1U)return 0;
    *key=0U;*pressed=0U;
    if(event.EventType==KEY_EVENT) {
        *key=event.Event.KeyEvent.wVirtualKeyCode;
        *pressed=event.Event.KeyEvent.bKeyDown?1U:0U;
    }
    return 1;
}
