#include <windows.h>
#include <string.h>
#include <stdio.h>
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
static struct mysmb_io_snapshot expected_snapshot,restored_snapshot;
static struct mysmb_io_text_frame expected_text;
static int injected_key(WORD expected,unsigned char down,WORD *key,
    unsigned char *pressed)
{
    unsigned int remaining=64U;
    /* AllocConsole may enqueue focus/window events after the explicit flush.
     * Ignore only non-key records; an unexpected key must still fail. */
    while(remaining--!=0U &&
        mysmb_win32_text_console_key(&g_console,key,pressed)) {
        if(*key!=0U)return *key==expected && *pressed==down;
    }
    return 0;
}

static int console_shortcut(HWND window,WORD key,unsigned char down)
{
    INPUT_RECORD event;
    DWORD written;
    WORD received;
    unsigned char pressed;
    ZeroMemory(&event,sizeof(event));event.EventType=KEY_EVENT;
    event.Event.KeyEvent.wVirtualKeyCode=key;
    event.Event.KeyEvent.bKeyDown=down?TRUE:FALSE;
    if(!WriteConsoleInputA(g_console.input,&event,1U,&written) || written!=1U ||
        !injected_key(key,down,&received,&pressed))return 0;
    mysmb_win32_shortcut(window,received,pressed);return 1;
}

static int text_snapshot_route(HWND window,const char *directory)
{
    struct mysmb_snapshot_files files;
    struct mysmb_input input;
    unsigned int i;
    char path[320];
    LARGE_INTEGER now;
    struct mysmb_io_audio_frame continuation;
    short expected_samples[MYSMB_WIN32_AUDIO_FRAME_SAMPLES];
    short actual_samples[MYSMB_WIN32_AUDIO_FRAME_SAMPLES];
    if(strlen(directory)>260U ||
        (!strstr(directory,"/build/") && !strstr(directory,"\\build\\")))return 28;
    if(!CreateDirectoryA(directory,NULL) && GetLastError()!=ERROR_ALREADY_EXISTS)return 29;
    mysmb_win32_power_on();mysmb_win32_snapshot_initialize();
    if(!mysmb_file_storage_initialize(&g_snapshot_files,directory,
        mysmb_win32_snapshot_replace,&files) ||
        !mysmb_snapshot_store_initialize(&g_snapshot_store,&files))return 30;
    g_snapshot_ready=1U;
    mysmb_win32_audio_renderer_initialize(&g_audio_output.renderer);
    for(i=0U;i<1200U;++i) {
        if(!mysmb_game_startup_step(&g_game,1U))continue;
        input.buttons=i==100U?MYSMB_BUTTON_START:0U;input.buttons2=0U;
        mysmb_game_tick(&g_game,&input,&g_frame);
        mysmb_game_io_audio(&g_game,&g_audio_frame);
        mysmb_win32_audio_submit(&g_audio_output,&g_audio_frame);
        mysmb_win32_snapshot_capture();
        if(g_snapshot_cache.valid &&
            mysmb_game_pause_input_state(&g_game)==MYSMB_PAUSE_INPUT_READY)break;
    }
    if(i==1200U)return 31;
    g_game_started=1U;
    expected_snapshot=g_snapshot_cache.last_running;
    saved_audio=g_audio_output;
    mysmb_win32_switch_presenter(window,0);
    if(!g_text_mode)return 32;
    ShowWindow(g_console.window,SW_HIDE);owned_focus=g_console.window;
    expected_text=g_text_frame;
    /* Public focus loss reaches translated pause through the real root tick. */
    owned_focus=NULL;
    QueryPerformanceCounter(&now);
    g_last_tick.QuadPart=now.QuadPart-g_frequency.QuadPart/60;
    mysmb_win32_step(window);
    if(!mysmb_game_is_paused(&g_game) || g_focus_pause.pending)return 33;
    owned_focus=g_console.window;
    if(!console_shortcut(window,'P',1U))return 34;
    mysmb_win32_snapshot_request(window);
    if(!console_shortcut(window,'P',0U))return 35;
    if(!console_shortcut(window,'O',1U) ||
        !mysmb_win32_snapshot_request(window))return 36;
    if(!g_text_mode || !g_console.opened || g_text_failed ||
        mysmb_game_is_paused(&g_game))return 37;
    if(!mysmb_game_snapshot_capture(&g_game,&restored_snapshot,g_snapshot_fingerprint) ||
        !mysmb_win32_audio_capture(&g_audio_output.renderer,
            restored_snapshot.payload+MYSMB_SNAPSHOT_CORE_BYTES) ||
        memcmp(&expected_snapshot,&restored_snapshot,sizeof(expected_snapshot)) ||
        memcmp(&expected_text,&g_text_frame,sizeof(expected_text)))return 38;
    if(!console_shortcut(window,'O',0U))return 39;
    ZeroMemory(&continuation,sizeof(continuation));
    for(i=0U;i<60U;++i) {
        mysmb_win32_audio_render(&saved_audio.renderer,&continuation,
            expected_samples,MYSMB_WIN32_AUDIO_FRAME_SAMPLES,MYSMB_WIN32_AUDIO_RATE);
        mysmb_win32_audio_render(&g_audio_output.renderer,&continuation,
            actual_samples,MYSMB_WIN32_AUDIO_FRAME_SAMPLES,MYSMB_WIN32_AUDIO_RATE);
        if(memcmp(expected_samples,actual_samples,sizeof(expected_samples)))return 42;
    }
    saved_game=g_game;saved_audio=g_audio_output;
    mysmb_win32_switch_presenter(window,0);owned_focus=window;
    if(memcmp(&saved_game,&g_game,sizeof(g_game)) ||
        memcmp(&saved_audio,&g_audio_output,sizeof(g_audio_output)))return 40;
    sprintf(path,"%s/mysmb.sav",directory);
    if(remove(path))return 41;
    return 0;
}

int WINAPI WinMain(HINSTANCE instance,HINSTANCE previous,LPSTR command,int show)
{
    WNDCLASS wc;
    HWND window;
    INPUT_RECORD event;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO info;
    CONSOLE_SCREEN_BUFFER_INFOEX color_info;
    unsigned long rgb;
    UINT close_state;
    CHAR_INFO cells[MYSMB_IO_TEXT_CELLS];
    SMALL_RECT view;
    COORD size,origin;
    struct mysmb_input input;
    unsigned int i;
    WORD key;
    unsigned char pressed;
    int result;
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
    close_state=GetMenuState(GetSystemMenu(g_console.window,FALSE),SC_CLOSE,MF_BYCOMMAND);
    if(close_state==(UINT)-1 || !(close_state&(MF_DISABLED|MF_GRAYED)))return 45;
    ZeroMemory(&color_info,sizeof(color_info));color_info.cbSize=sizeof(color_info);
    if(!GetConsoleScreenBufferInfoEx(g_console.output,&color_info))return 43;
    for(i=0U;i<16U;++i) {
        rgb=mysmb_io_color_text_rgb((mysmb_io_u8)i);
        if(color_info.ColorTable[i]!=RGB((rgb>>16U)&255UL,(rgb>>8U)&255UL,rgb&255UL))return 44;
    }
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
    if(!injected_key(VK_TAB,1U,&key,&pressed))return 10;
    mysmb_win32_shortcut(window,key,pressed);
    if(g_toggle_request)return 11;
    event.Event.KeyEvent.bKeyDown=FALSE;
    WriteConsoleInputA(g_console.input,&event,1U,&written);
    if(!injected_key(VK_TAB,0U,&key,&pressed))return 12;
    mysmb_win32_shortcut(window,key,pressed);
    event.Event.KeyEvent.bKeyDown=TRUE;
    WriteConsoleInputA(g_console.input,&event,1U,&written);
    if(!injected_key(VK_TAB,1U,&key,&pressed))return 13;
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
    /* An existing attachment makes AllocConsole fail without changing state. */
    if(!AllocConsole())return 18;
    ShowWindow(GetConsoleWindow(),SW_HIDE);
    mysmb_win32_switch_presenter(window,0);
    if(g_text_mode || g_console.opened ||
        memcmp(&saved_game,&g_game,sizeof(g_game)) ||
        memcmp(&saved_audio,&g_audio_output,sizeof(g_audio_output)))return 19;
    FreeConsole();
    mysmb_win32_switch_presenter(window,0);
    if(!g_text_mode)return 20;
    ShowWindow(g_console.window,SW_HIDE);
    view.Left=view.Top=view.Right=view.Bottom=0;
    size.X=79;size.Y=49;
    if(!SetConsoleWindowInfo(g_console.output,TRUE,&view) ||
        !SetConsoleScreenBufferSize(g_console.output,size))return 21;
    mysmb_win32_build_frame();
    if(!g_text_failed)return 22;
    mysmb_win32_switch_presenter(window,0);
    if(g_text_mode || g_console.opened || g_console.input || g_console.output ||
        memcmp(saved_pixels,g_pixels,sizeof(g_pixels)))return 23;
    mysmb_win32_switch_presenter(window,0);
    if(!g_text_mode)return 24;
    ShowWindow(g_console.window,SW_HIDE);
    if(!FreeConsole())return 25;
    mysmb_win32_build_frame();
    if(!g_text_failed)return 26;
    mysmb_win32_switch_presenter(window,0);
    if(g_text_mode || g_console.opened ||
        memcmp(&saved_game,&g_game,sizeof(g_game)) ||
        memcmp(&saved_audio,&g_audio_output,sizeof(g_audio_output)) ||
        memcmp(saved_pixels,g_pixels,sizeof(g_pixels)))return 27;
    if(command[0]) {
        result=text_snapshot_route(window,command);
        if(result)return result;
    }
    DestroyWindow(window);return 0;
}
