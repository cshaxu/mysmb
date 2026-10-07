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
/* Only an actual visible host window may be shown or geometrically managed.
 * A notification HWND is not a window capability;no class-name policy. */
static unsigned char mysmb_win32_console_window(HWND window)
{
    RECT rect;
    return (unsigned char)(window && IsWindowVisible(window) &&
        GetWindowRect(window,&rect) && rect.right>rect.left && rect.bottom>rect.top);
}
static void mysmb_win32_console_fit(struct mysmb_win32_text_console *console,
    unsigned char initial)
{
    CONSOLE_FONT_INFOEX font;
    CONSOLE_SCREEN_BUFFER_INFO info;
    RECT client;
    COORD maximum;
    unsigned int target=8U;
    if(!initial && console->window_usable && GetClientRect(console->window,&client)) {
        unsigned int x=(unsigned int)(client.right-client.left)/80U;
        unsigned int y=(unsigned int)(client.bottom-client.top)/50U;
        if(x<target)target=x;if(y<target)target=y;
        if(target<4U)target=4U;
    }
    ZeroMemory(&font,sizeof(font));font.cbSize=sizeof(font);
    font.FontWeight=FW_NORMAL;lstrcpyW(font.FaceName,L"Consolas");
    for(;;) {
        font.dwFontSize.X=(SHORT)target;font.dwFontSize.Y=(SHORT)target;
        if(SetCurrentConsoleFontEx(console->output,FALSE,&font))console->font_changed=1U;
        maximum=GetLargestConsoleWindowSize(console->output);
        if((maximum.X>=80 && maximum.Y>=50) || target==4U)break;
        --target;
    }
    ZeroMemory(&console->effective_font,sizeof(console->effective_font));
    console->effective_font.cbSize=sizeof(console->effective_font);
    (void)GetCurrentConsoleFontEx(console->output,FALSE,&console->effective_font);
    if(GetConsoleScreenBufferInfo(console->output,&info)) {
        console->observed_view.X=(SHORT)(info.srWindow.Right-info.srWindow.Left+1);
        console->observed_view.Y=(SHORT)(info.srWindow.Bottom-info.srWindow.Top+1);
    }
    console->fit_changed_at=GetTickCount();
}
/* Probe device operations themselves,not the availability of a host HWND.
 * One optional entry attempt restores the former80x50contract on ConPTY too.
 * Never repeat this sequence per frame on a non-window host. */
static unsigned char mysmb_win32_console_size(struct mysmb_win32_text_console *console,
    COORD size,const SMALL_RECT *view)
{
    SMALL_RECT tiny={0,0,0,0};
    CONSOLE_SCREEN_BUFFER_INFO before,info;
    if(!GetConsoleScreenBufferInfo(console->output,&before))return 0U;
    if(SetConsoleWindowInfo(console->output,TRUE,&tiny) &&
        SetConsoleScreenBufferSize(console->output,size) &&
        SetConsoleWindowInfo(console->output,TRUE,view) &&
        GetConsoleScreenBufferInfo(console->output,&info) &&
        info.dwSize.X==size.X && info.dwSize.Y==size.Y &&
        info.srWindow.Left==view->Left && info.srWindow.Top==view->Top &&
        info.srWindow.Right==view->Right && info.srWindow.Bottom==view->Bottom) {
        console->observed_view.X=(SHORT)(info.srWindow.Right-info.srWindow.Left+1);
        console->observed_view.Y=(SHORT)(info.srWindow.Bottom-info.srWindow.Top+1);
        return 1U;
    }
    /* Optional partial failure must not leave the temporary1x1view behind. */
    (void)SetConsoleWindowInfo(console->output,TRUE,&tiny);
    (void)SetConsoleScreenBufferSize(console->output,before.dwSize);
    (void)SetConsoleWindowInfo(console->output,TRUE,&before.srWindow);
    return 0U;
}
int mysmb_win32_text_console_open(struct mysmb_win32_text_console *console,
    HWND owner)
{
    COORD size;
    SMALL_RECT view;
    CONSOLE_CURSOR_INFO cursor;
    DWORD mode;
    CONSOLE_SCREEN_BUFFER_INFOEX info;
    unsigned int i;
    unsigned long rgb;
    DWORD processes[2];
    DWORD output_mode;
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
    console->window_usable=mysmb_win32_console_window(console->window);
    if(console->input==INVALID_HANDLE_VALUE) {
        mysmb_win32_text_console_close(console);return 0;
    }
    if(console->borrowed) {
        console->shell_output=CreateFileA("CONOUT$",GENERIC_READ|GENERIC_WRITE,
            FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0U,NULL);
        console->shell_title=(WCHAR *)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,
            65536UL*sizeof(WCHAR));
        ZeroMemory(&console->shell_placement,sizeof(console->shell_placement));
        console->shell_placement.length=sizeof(console->shell_placement);
        if(console->shell_output==INVALID_HANDLE_VALUE || !console->shell_title ||
            !GetConsoleMode(console->input,&console->shell_input_mode) ||
            !GetConsoleScreenBufferInfo(console->shell_output,&console->shell_info)) {
            mysmb_win32_text_console_close(console);return 0;
        }
        console->mode_saved=1U;
        ZeroMemory(&console->shell_font,sizeof(console->shell_font));
        console->shell_font.cbSize=sizeof(console->shell_font);
        if(!GetCurrentConsoleFontEx(console->shell_output,FALSE,&console->shell_font))
            console->shell_font.cbSize=0U;
        /* A pseudoconsole may expose a non-window notification handle. */
        (void)GetWindowPlacement(console->window,&console->shell_placement);
        (void)GetConsoleTitleW(console->shell_title,65536U);
        console->output=CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE,
            FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,CONSOLE_TEXTMODE_BUFFER,NULL);
    } else console->output=CreateFileA("CONOUT$",GENERIC_READ|GENERIC_WRITE,
        FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0U,NULL);
    if(console->output==INVALID_HANDLE_VALUE) {
        mysmb_win32_text_console_close(console);return 0;
    }
    size.X=80;size.Y=50;
    view.Left=view.Top=0;view.Right=79;view.Bottom=49;
    if(GetConsoleMode(console->output,&output_mode) &&
        SetConsoleMode(console->output,output_mode|0x0001U|0x0004U|0x0008U)) {
        console->terminal_output=(WCHAR *)HeapAlloc(GetProcessHeap(),0U,
            (MYSMB_IO_TEXT_CELLS*48U+1024U)*sizeof(WCHAR));
        console->vt_output=(unsigned char)(console->terminal_output!=NULL);
    }
    ZeroMemory(&info,sizeof(info));info.cbSize=sizeof(info);
    if(!console->vt_output && GetConsoleScreenBufferInfoEx(console->output,&info)) {
        for(i=0U;i<16U;++i) {
            rgb=mysmb_io_color_text_rgb((mysmb_io_u8)i);
            info.ColorTable[i]=RGB((rgb>>16U)&255UL,(rgb>>8U)&255UL,rgb&255UL);
        }
        (void)SetConsoleScreenBufferInfoEx(console->output,&info);
    }
    if(!SetConsoleActiveScreenBuffer(console->output)) {
        mysmb_win32_text_console_close(console);return 0;
    }
    if(!GetConsoleMode(console->input,&mode) ||
        !SetConsoleMode(console->input,(mode|ENABLE_EXTENDED_FLAGS|ENABLE_WINDOW_INPUT)&
            ~(ENABLE_QUICK_EDIT_MODE|ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT|
                ENABLE_PROCESSED_INPUT|ENABLE_VIRTUAL_TERMINAL_INPUT))) {
        mysmb_win32_text_console_close(console);return 0;
    }
    /* Font request is attempted on every output buffer. API success may be
     * virtualized;effective physical glyph geometry still needs visual proof. */
    mysmb_win32_console_fit(console,1U);
    console->geometry_usable=mysmb_win32_console_size(console,size,&view);
    cursor.dwSize=1;cursor.bVisible=FALSE;
    (void)SetConsoleCursorInfo(console->output,&cursor);
    (void)SetConsoleTitleA("MySMB");
    /* Close requests the same root-owned exit as Escape and the GUI button. */
    if(!console->borrowed) {
        HMENU menu=GetSystemMenu(console->window,FALSE);
        /* Decoration is optional; console input/output defines device health. */
        if(menu)(void)EnableMenuItem(menu,SC_CLOSE,MF_BYCOMMAND|MF_ENABLED);
    }
    console->focused=1U;
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
            if(console->font_changed && console->shell_font.cbSize)
                (void)SetCurrentConsoleFontEx(console->shell_output,FALSE,&console->shell_font);
            if(console->shell_placement.showCmd!=0U)
                (void)SetWindowPlacement(console->window,&console->shell_placement);
            /* Host pixel placement can round a restored cell view down a row.
             * Restore its original cell rectangle explicitly after placement. */
            if(console->geometry_usable) {
                SMALL_RECT tiny={0,0,0,0};
                /* Host pixel rounding may also grow a narrow shell buffer. */
                (void)SetConsoleWindowInfo(console->shell_output,TRUE,&tiny);
                (void)SetConsoleScreenBufferSize(console->shell_output,console->shell_info.dwSize);
                (void)SetConsoleWindowInfo(console->shell_output,TRUE,&console->shell_info.srWindow);
            }
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
    if(console->terminal_output)HeapFree(GetProcessHeap(),0U,console->terminal_output);
    console->terminal_output=NULL;console->vt_output=console->window_usable=console->font_changed=console->geometry_usable=0U;
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
    console->borrowed=console->mode_saved=console->focused=0U;console->geometry_pending=console->output_failures=0U;
}
/* Resize is an optional geometry operation,never a device-loss signal.
 * Apply font/geometry only after a settled change,not on every video frame. */
static int mysmb_win32_console_geometry(struct mysmb_win32_text_console *console)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    COORD size,visible;
    SMALL_RECT tiny={0,0,0,0},view={0,0,79,49};
    DWORD now=GetTickCount();
    if(!GetConsoleScreenBufferInfo(console->output,&info))return MYSMB_WIN32_CONSOLE_DEFER;
    if(console->window_usable && IsIconic(console->window))return MYSMB_WIN32_CONSOLE_DEFER;
    visible.X=(SHORT)(info.srWindow.Right-info.srWindow.Left+1);
    visible.Y=(SHORT)(info.srWindow.Bottom-info.srWindow.Top+1);
    if(visible.X!=console->observed_view.X || visible.Y!=console->observed_view.Y) {
        console->observed_view=visible;console->fit_changed_at=now;
        console->geometry_pending=1U;
    }
    if(console->geometry_pending && now-console->fit_changed_at>=150U) {
        console->geometry_pending=0U;
        mysmb_win32_console_fit(console,0U);
        if(console->window_usable && !IsZoomed(console->window)) {
            size.X=80;size.Y=50;
            (void)SetConsoleWindowInfo(console->output,TRUE,&tiny);
            (void)SetConsoleScreenBufferSize(console->output,size);
            (void)SetConsoleWindowInfo(console->output,TRUE,&view);
        }
    }
    return MYSMB_WIN32_CONSOLE_READY;
}
/* Successful short writes are resize races. Failed writes distinguish actual
 * access/device loss from a transient unavailable viewport. */
static int mysmb_win32_console_write_failure(struct mysmb_win32_text_console *console)
{
    DWORD error=GetLastError();
    if(error==ERROR_INVALID_HANDLE || error==ERROR_ACCESS_DENIED)
        return MYSMB_WIN32_CONSOLE_LOST;
    if(error==ERROR_INVALID_PARAMETER || error==ERROR_NOT_READY)
        return MYSMB_WIN32_CONSOLE_DEFER;
    if(++console->output_failures>=120U)return MYSMB_WIN32_CONSOLE_LOST;
    return MYSMB_WIN32_CONSOLE_DEFER;
}
/* Terminal owns its font and viewport. Emit exact neutral RGB cells only in
 * the current visible region; never resize the user's terminal during a frame. */
static int mysmb_win32_terminal_present(struct mysmb_win32_text_console *console,
    const struct mysmb_io_text_frame *frame)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    WCHAR *out=console->terminal_output,sequence[96];
    DWORD written;
    unsigned int width,height,x,y,count=0U,length;
    int foreground=-1,background=-1;
    unsigned long fg,bg;
    WCHAR glyph;
    const struct mysmb_io_text_cell *cell;
    if(!out || !GetConsoleScreenBufferInfo(console->output,&info))return MYSMB_WIN32_CONSOLE_DEFER;
    width=(unsigned int)(info.srWindow.Right-info.srWindow.Left+1);
    height=(unsigned int)(info.srWindow.Bottom-info.srWindow.Top+1);
    if(width>80U)width=80U;
    if(height>50U)height=50U;
    if(!width || !height)return MYSMB_WIN32_CONSOLE_DEFER;
    lstrcpyW(out,L"\x1b[?25l");count=6U;
    for(y=0U;y<height;++y) {
        length=(unsigned int)wsprintfW(sequence,L"\x1b[%u;1H",y+1U);
        CopyMemory(out+count,sequence,length*sizeof(WCHAR));count+=length;
        for(x=0U;x<width;++x) {
            cell=&frame->cells[y*80U+x];
            if(foreground!=(int)(cell->foreground&15U) ||
                background!=(int)(cell->background&15U)) {
                foreground=cell->foreground&15U;background=cell->background&15U;
                fg=mysmb_io_color_text_rgb((mysmb_io_u8)foreground);
                bg=mysmb_io_color_text_rgb((mysmb_io_u8)background);
                length=(unsigned int)wsprintfW(sequence,
                    L"\x1b[38;2;%u;%u;%u;48;2;%u;%u;%um",
                    (unsigned int)((fg>>16U)&255U),(unsigned int)((fg>>8U)&255U),
                    (unsigned int)(fg&255U),(unsigned int)((bg>>16U)&255U),
                    (unsigned int)((bg>>8U)&255U),(unsigned int)(bg&255U));
                CopyMemory(out+count,sequence,length*sizeof(WCHAR));count+=length;
            }
            glyph=(WCHAR)mysmb_io_text_glyph_unicode(cell->character);
            if(!glyph)return 0;
            out[count++]=glyph;
        }
    }
    if(!WriteConsoleW(console->output,out,count,&written,NULL))
        return mysmb_win32_console_write_failure(console);
    console->output_failures=0U;
    return written==count?MYSMB_WIN32_CONSOLE_READY:MYSMB_WIN32_CONSOLE_DEFER;
}
int mysmb_win32_text_console_present(struct mysmb_win32_text_console *console,
    const struct mysmb_io_text_frame *frame)
{
    unsigned short i;
    int geometry;
    DWORD input_mode,output_mode;
    COORD size,origin;
    SMALL_RECT view;
    if(!console->opened || frame==0 ||
        !GetConsoleMode(console->input,&input_mode) ||
        !GetConsoleMode(console->output,&output_mode))return MYSMB_WIN32_CONSOLE_LOST;
    geometry=mysmb_win32_console_geometry(console);
    if(geometry!=MYSMB_WIN32_CONSOLE_READY)return geometry;
    if(console->vt_output)return mysmb_win32_terminal_present(console,frame);
    for(i=0U;i<MYSMB_IO_TEXT_CELLS;++i) {
        console->cells[i].Char.UnicodeChar=(WCHAR)mysmb_io_text_glyph_unicode(frame->cells[i].character);
        if(console->cells[i].Char.UnicodeChar==0U)return 0;
        console->cells[i].Attributes=(WORD)((frame->cells[i].foreground&15U)|
            ((frame->cells[i].background&15U)<<4U));
    }
    size.X=80;size.Y=50;origin.X=origin.Y=0;
    view.Left=view.Top=0;view.Right=79;view.Bottom=49;
    if(!WriteConsoleOutputW(console->output,console->cells,size,origin,&view))
        return mysmb_win32_console_write_failure(console);
    console->output_failures=0U;
    if(view.Left==0 && view.Top==0 && view.Right==79 && view.Bottom==49)
        return MYSMB_WIN32_CONSOLE_READY;
    /* Clipping/partial writes during valid-host resize defer this frame.
     * The next tick validates both handles before trying again. */
    return MYSMB_WIN32_CONSOLE_DEFER;
}
int mysmb_win32_text_console_key(struct mysmb_win32_text_console *console,
    WORD *key,WORD *scan,unsigned char *pressed)
{
    DWORD count,read;
    INPUT_RECORD event;
    if(!console->opened || !GetNumberOfConsoleInputEvents(console->input,&count) ||
        count==0U || !ReadConsoleInputW(console->input,&event,1U,&read) || read!=1U)return 0;
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
