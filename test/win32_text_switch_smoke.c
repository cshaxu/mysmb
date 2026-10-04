#include <windows.h>
#include <string.h>
static HWND owned_focus;
static SHORT owned_tab;
static HWND probe_foreground(void){return owned_focus;}
static SHORT probe_key(int key){return key==VK_TAB?owned_tab:0;}
#define GetForegroundWindow probe_foreground
#define GetAsyncKeyState probe_key
#define WinMain mysmb_unused_product_entry
#include "../src/platform/win32/main_win32.c"
#undef WinMain
static struct mysmb_game saved_game;
static struct mysmb_win32_audio_output saved_audio;
static DWORD saved_pixels[MYSMB_SCREEN_WIDTH*MYSMB_SCREEN_HEIGHT];

int WINAPI WinMain(HINSTANCE instance,HINSTANCE previous,LPSTR command,int show)
{
    WNDCLASS wc;
    HWND window;
    INPUT_RECORD event;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO info;
    CHAR_INFO cells[MYSMB_IO_TEXT_CELLS];
    SMALL_RECT view;
    COORD size,origin;
    struct mysmb_input input;
    unsigned int i;
    WORD key;
    unsigned char pressed;
    (void)previous;(void)command;(void)show;
    ZeroMemory(&wc,sizeof(wc));wc.lpfnWndProc=mysmb_win32_window_proc;
    wc.hInstance=instance;wc.lpszClassName="MySMBTextSwitchProbe";
    if(!RegisterClass(&wc))return 1;
    window=CreateWindow(wc.lpszClassName,"",0,0,0,256,240,NULL,NULL,instance,NULL);
    if(!window)return 2;
    owned_focus=window;
    mysmb_io_control_initialize(&g_control);mysmb_win32_power_on();
    mysmb_win32_focus_pause_initialize(&g_focus_pause);
    mysmb_win32_focus_pause_gained(&g_focus_pause);
    QueryPerformanceFrequency(&g_frequency);QueryPerformanceCounter(&g_last_tick);
    for(i=0U;i<500U;++i) {
        if(!mysmb_game_startup_step(&g_game,1U))continue;
        input.buttons=i==120U?MYSMB_BUTTON_START:i>120U?MYSMB_BUTTON_RIGHT:0U;
        input.buttons2=0U;mysmb_game_tick(&g_game,&input,&g_frame);
    }
    mysmb_win32_build_frame();
    saved_game=g_game;saved_audio=g_audio_output;
    memcpy(saved_pixels,g_pixels,sizeof(saved_pixels));
    mysmb_win32_shortcut(window,VK_TAB,1U);
    if(g_toggle_request!=MYSMB_IO_REQUEST_TOGGLE)return 3;
    g_toggle_request=0U;mysmb_win32_switch_presenter(window,0);
    if(!g_text_mode || !g_console.opened)return 4;
    ShowWindow(g_console.window,SW_HIDE);
    owned_focus=g_console.window;
    if(memcmp(&saved_game,&g_game,sizeof(g_game)) ||
        memcmp(&saved_audio,&g_audio_output,sizeof(g_audio_output)) ||
        g_focus_pause.pending!=0U)return 5;
    if(!GetConsoleScreenBufferInfo(g_console.output,&info) ||
        info.dwSize.X!=80 || info.dwSize.Y!=50)return 6;
    size.X=80;size.Y=50;origin.X=origin.Y=0;
    view.Left=view.Top=0;view.Right=79;view.Bottom=49;
    if(!ReadConsoleOutputA(g_console.output,cells,size,origin,&view))return 7;
    for(i=0U;i<4000U;++i)
        if(cells[i].Char.AsciiChar!=(CHAR)g_text_frame.cells[i].character ||
            cells[i].Attributes!=(WORD)(g_text_frame.cells[i].foreground|
                (g_text_frame.cells[i].background<<4U)))return 8;
    /* Real owned console input,including a held repeat and physical break. */
    FlushConsoleInputBuffer(g_console.input);
    ZeroMemory(&event,sizeof(event));event.EventType=KEY_EVENT;
    event.Event.KeyEvent.wVirtualKeyCode=VK_TAB;
    event.Event.KeyEvent.bKeyDown=TRUE;
    if(!WriteConsoleInputA(g_console.input,&event,1U,&written) || written!=1U)return 9;
    if(!mysmb_win32_text_console_key(&g_console,&key,&pressed))return 10;
    mysmb_win32_shortcut(window,key,pressed);
    if(g_toggle_request)return 11;
    event.Event.KeyEvent.bKeyDown=FALSE;
    WriteConsoleInputA(g_console.input,&event,1U,&written);
    if(!mysmb_win32_text_console_key(&g_console,&key,&pressed))return 12;
    mysmb_win32_shortcut(window,key,pressed);
    event.Event.KeyEvent.bKeyDown=TRUE;
    WriteConsoleInputA(g_console.input,&event,1U,&written);
    if(!mysmb_win32_text_console_key(&g_console,&key,&pressed))return 13;
    mysmb_win32_shortcut(window,key,pressed);
    if(g_toggle_request!=MYSMB_IO_REQUEST_TOGGLE)return 14;
    mysmb_win32_shortcut(window,'P',1U);
    if(g_snapshot_requests!=MYSMB_IO_REQUEST_SAVE)return 15;
    mysmb_win32_shortcut(window,'P',0U);g_snapshot_requests=0U;
    mysmb_win32_shortcut(window,'O',1U);
    if(g_snapshot_requests!=MYSMB_IO_REQUEST_LOAD)return 16;
    g_toggle_request=0U;mysmb_win32_switch_presenter(window,0);owned_focus=window;
    if(g_text_mode || g_console.opened || g_focus_pause.pending ||
        memcmp(&saved_game,&g_game,sizeof(g_game)) ||
        memcmp(&saved_audio,&g_audio_output,sizeof(g_audio_output)) ||
        memcmp(saved_pixels,g_pixels,sizeof(g_pixels)))return 17;
    DestroyWindow(window);return 0;
}
