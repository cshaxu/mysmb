#include "platform/win32/text_console.h"
#include "platform/win32/text_console_geometry.h"
#include "platform/win32/text_console_policy.h"
#include "platform/win32/text_console_presentation.h"
#include "platform/win32/launch.h"
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
int mysmb_win32_text_console_open_profile(struct mysmb_win32_text_console *console,
    HWND owner,unsigned short rows)
{
    COORD size;
    SMALL_RECT view;
    CONSOLE_CURSOR_INFO cursor;
    DWORD mode,output_mode;
    DWORD processes[2];
    if(console->opened)return 1;
    console->rows=mysmb_win32_console_rows(rows);console->colors_valid=0U;
    if(!owner)return 0;
    if(GetConsoleProcessList(processes,2U)!=0U) {
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
    size.X=80;size.Y=(SHORT)console->rows;
    view.Left=view.Top=0;view.Right=79;view.Bottom=(SHORT)(console->rows-1U);
    if(!SetConsoleActiveScreenBuffer(console->output)) {
        mysmb_win32_text_console_close(console);return 0;
    }
    if(!GetConsoleMode(console->input,&mode) ||
        !SetConsoleMode(console->input,(mode|ENABLE_EXTENDED_FLAGS|ENABLE_WINDOW_INPUT)&
            ~(ENABLE_QUICK_EDIT_MODE|ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT|
                ENABLE_PROCESSED_INPUT|ENABLE_VIRTUAL_TERMINAL_INPUT))) {
        mysmb_win32_text_console_close(console);return 0;
    }
    {
        unsigned char indexed_carrier=mysmb_win32_console_indexed_carrier(console);
        unsigned char output_mode_read=(unsigned char)GetConsoleMode(console->output,&output_mode);
        unsigned char output_mode_set=0U;
        if(output_mode_read && !indexed_carrier)
            output_mode_set=(unsigned char)SetConsoleMode(console->output,
                output_mode|ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        if(mysmb_win32_console_use_vt(indexed_carrier,output_mode_read,output_mode_set)) {
        console->terminal_output=(WCHAR *)HeapAlloc(GetProcessHeap(),0U,
            mysmb_win32_console_vt_capacity(console->rows)*sizeof(WCHAR));
        console->vt_output=(unsigned char)(console->terminal_output!=NULL);
        }
    }
    if(!console->vt_output)
        mysmb_win32_console_initialize_indexed(console);
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
int mysmb_win32_text_console_suspend(struct mysmb_win32_text_console *console)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    COORD origin={0,0};
    DWORD cells,written;
    if(!console || !console->opened)return 0;
    /* Keep the actual console attachment, screen buffer and handles alive.
     * Parent-shell discovery is initial-launch policy, never resume policy. */
    if(console->input && console->input!=INVALID_HANDLE_VALUE)
        (void)FlushConsoleInputBuffer(console->input);
    /* Return the borrowed console to its parent buffer before hiding it. The
     * separate game buffer is blanked so no stale frame remains on re-show. */
    if(console->borrowed && console->shell_output &&
        console->shell_output!=INVALID_HANDLE_VALUE) {
        if(!SetConsoleActiveScreenBuffer(console->shell_output))return 0;
        if(!GetConsoleScreenBufferInfo(console->output,&info))return 0;
        cells=(DWORD)(unsigned short)info.dwSize.X*(DWORD)(unsigned short)info.dwSize.Y;
        if(!FillConsoleOutputCharacterW(console->output,L' ',cells,origin,&written) ||
            written!=cells || !FillConsoleOutputAttribute(console->output,0U,cells,origin,&written) ||
            written!=cells)return 0;
    }
    if(console->window_usable)(void)ShowWindow(console->window,SW_HIDE);
    console->focused=0U;console->suspended=1U;
    return 1;
}
int mysmb_win32_text_console_resume(struct mysmb_win32_text_console *console)
{
    DWORD input_mode,output_mode;
    if(!console || !console->opened ||
        !console->input || console->input==INVALID_HANDLE_VALUE ||
        !console->output || console->output==INVALID_HANDLE_VALUE ||
        !GetConsoleMode(console->input,&input_mode) ||
        !GetConsoleMode(console->output,&output_mode) ||
        !SetConsoleActiveScreenBuffer(console->output))return 0;
    console->focused=1U;console->suspended=0U;
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
    console->terminal_output=NULL;console->vt_output=console->window_usable=
        console->font_changed=console->geometry_usable=0U;
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
    console->borrowed=console->mode_saved=console->focused=console->suspended=0U;console->geometry_pending=console->output_failures=0U;
}
int mysmb_win32_text_console_present(struct mysmb_win32_text_console *console,
    const struct mysmb_io_text_frame *frame)
{
    int geometry;
    DWORD input_mode,output_mode;
    if(!console->opened || frame==0 ||
        !GetConsoleMode(console->input,&input_mode) ||
        !GetConsoleMode(console->output,&output_mode))return MYSMB_WIN32_CONSOLE_LOST;
    geometry=mysmb_win32_console_geometry(console);
    if(geometry!=MYSMB_WIN32_CONSOLE_READY)return geometry;
    return mysmb_win32_console_present_frame(console,frame);
}

int mysmb_win32_text_console_open(struct mysmb_win32_text_console *console,HWND owner)
{return mysmb_win32_text_console_open_profile(console,owner,50U);}
