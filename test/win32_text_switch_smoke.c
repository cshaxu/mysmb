#include "io/text_glyph.h"
#include <windows.h>
#include <string.h>
#include <stdio.h>
static HWND owned_focus;
static unsigned int async_calls;
static HWND probe_foreground(void){return owned_focus;}
static SHORT probe_key(int key){(void)key;++async_calls;return 0;}
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
static int console_shortcut(HWND window,WORD key,unsigned char down);
static int presentation_clock_route(HWND window)
{
    struct mysmb_io_video_frame video;
    LARGE_INTEGER before;
    LONGLONG period;
    unsigned int i;
    static unsigned char indices[MYSMB_SCREEN_WIDTH*MYSMB_SCREEN_HEIGHT];
    for(i=0U;i<sizeof(indices);++i)indices[i]=(unsigned char)i;
    video.pixels=indices;
    mysmb_win32_draw_gameplay(&video);
    for(i=0U;i<sizeof(indices);++i)
        if(g_pixels[i]!=(DWORD)mysmb_io_color_rgb(indices[i]))return 70;
    /* A twelve-frame scheduling stall must retain eight frames after one
     * bounded batch. The former reset-to-now silently removed this debt. */
    QueryPerformanceCounter(&before);period=g_frequency.QuadPart/60;
    before.QuadPart-=12*period;g_last_tick=before;
    mysmb_win32_step(window);
    if(g_last_tick.QuadPart!=before.QuadPart+4*period)return 71;
    return 0;
}
static void input_only_step(HWND window)
{
    QueryPerformanceCounter(&g_last_tick);
    g_last_tick.QuadPart+=g_frequency.QuadPart;
    mysmb_win32_step(window);
}
static int input_record(WORD key,WORD scan,int down)
{
    INPUT_RECORD event;
    DWORD written;
    ZeroMemory(&event,sizeof(event));event.EventType=KEY_EVENT;
    event.Event.KeyEvent.wVirtualKeyCode=key;
    event.Event.KeyEvent.wVirtualScanCode=scan;
    event.Event.KeyEvent.bKeyDown=down?TRUE:FALSE;
    event.Event.KeyEvent.wRepeatCount=1U;
    return WriteConsoleInputA(g_console.input,&event,1U,&written) && written==1U;
}
static int event_input_route(HWND window)
{
    static const WORD keys[]={
        'W','S','A','D','J','K',VK_RETURN,VK_LSHIFT,VK_RSHIFT,
        VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT};
    static const unsigned char buttons[]={
        MYSMB_BUTTON_UP,MYSMB_BUTTON_DOWN,MYSMB_BUTTON_LEFT,MYSMB_BUTTON_RIGHT,
        MYSMB_BUTTON_B,MYSMB_BUTTON_A,MYSMB_BUTTON_START,
        MYSMB_BUTTON_SELECT,MYSMB_BUTTON_SELECT,MYSMB_BUTTON_UP,
        MYSMB_BUTTON_DOWN,MYSMB_BUTTON_LEFT,MYSMB_BUTTON_RIGHT};
    unsigned int i;
    INPUT_RECORD focus;
    DWORD written;
    owned_focus=window;mysmb_win32_release_keys();
    /* Asynchronous state is deliberately zero even during delivered presses. */
    if(probe_key('W')!=0)return 51;
    async_calls=0U;
    for(i=0U;i<sizeof(keys)/sizeof(keys[0]);++i) {
        SendMessage(window,WM_KEYDOWN,keys[i],0);
        if(mysmb_win32_buttons_from_keys(mysmb_win32_poll_keys())!=buttons[i])return 52;
        SendMessage(window,WM_KEYDOWN,keys[i],0x40000000L);
        if(mysmb_win32_buttons_from_keys(mysmb_win32_poll_keys())!=buttons[i])return 53;
        SendMessage(window,WM_KEYUP,keys[i],0);
        if(mysmb_win32_poll_keys())return 54;
    }
    SendMessage(window,WM_SYSKEYDOWN,'J',0);
    SendMessage(window,WM_KEYDOWN,'D',0);
    SendMessage(window,WM_KEYDOWN,'K',0);
    if(mysmb_win32_buttons_from_keys(mysmb_win32_poll_keys())!=
        (MYSMB_BUTTON_B|MYSMB_BUTTON_A|MYSMB_BUTTON_RIGHT))return 55;
    owned_focus=NULL;SendMessage(window,WM_KILLFOCUS,0U,0L);
    if(mysmb_win32_poll_keys())return 56;
    owned_focus=window;SendMessage(window,WM_SETFOCUS,0U,0L);
    SendMessage(window,WM_KEYDOWN,VK_TAB,0);
    input_only_step(window);
    if(!g_text_mode)return 57;
    ShowWindow(g_console.window,SW_HIDE);owned_focus=g_console.window;
    FlushConsoleInputBuffer(g_console.input);
    if(!input_record(VK_TAB,0U,1))return 58;
    input_only_step(window);
    if(!g_text_mode || g_toggle_request)return 59;
    for(i=0U;i<sizeof(keys)/sizeof(keys[0]);++i) {
        if(!input_record(keys[i],0U,1))return 60;
        input_only_step(window);
        if(mysmb_win32_buttons_from_keys(mysmb_win32_poll_keys())!=buttons[i])return 61;
        if(!input_record(keys[i],0U,0))return 62;
        input_only_step(window);
        if(mysmb_win32_poll_keys())return 63;
    }
    if(!input_record('P',0U,1) || !input_record('P',0U,0) ||
        !input_record('O',0U,1) || !input_record('O',0U,0))return 64;
    g_snapshot_ready=0U;input_only_step(window);
    if(g_snapshot_requests)return 65;
    /* Test shortcut requests before their root consumer clears the queue. */
    if(!console_shortcut(window,'P',1U) ||
        g_snapshot_requests!=MYSMB_IO_REQUEST_SAVE)return 66;
    console_shortcut(window,'P',0U);g_snapshot_requests=0U;
    if(!console_shortcut(window,'O',1U) ||
        g_snapshot_requests!=MYSMB_IO_REQUEST_LOAD)return 67;
    console_shortcut(window,'O',0U);g_snapshot_requests=0U;
    if(!input_record('A',0U,1))return 68;
    input_only_step(window);(void)mysmb_win32_poll_keys();
    ZeroMemory(&focus,sizeof(focus));focus.EventType=FOCUS_EVENT;
    focus.Event.FocusEvent.bSetFocus=FALSE;
    if(!WriteConsoleInputA(g_console.input,&focus,1U,&written) || written!=1U)return 69;
    input_only_step(window);
    if(mysmb_win32_poll_keys())return 70;
    if(!input_record(VK_TAB,0U,0) || !input_record(VK_TAB,0U,1))return 71;
    input_only_step(window);owned_focus=window;
    if(g_text_mode || async_calls)return 72;
    SendMessage(window,WM_KEYUP,VK_TAB,0L);
    mysmb_win32_release_keys();
    return 0;
}
static int injected_key(WORD expected,unsigned char down,WORD *key,
    unsigned char *pressed)
{
    unsigned int remaining=64U;
    WORD scan;
    /* AllocConsole may enqueue focus/window events after the explicit flush.
     * Ignore only non-key records; an unexpected key must still fail. */
    while(remaining--!=0U &&
        mysmb_win32_text_console_key(&g_console,key,&scan,pressed)) {
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
    return mysmb_win32_key_event(window,received,0U,pressed);
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
    DWORD written,mode;
    CONSOLE_SCREEN_BUFFER_INFO info;
    CONSOLE_SCREEN_BUFFER_INFOEX color_info;
    unsigned long rgb;
    UINT close_state;
    CHAR_INFO cells[MYSMB_IO_TEXT_CELLS];
    static struct mysmb_io_text_frame glyph_frame;
    static const unsigned char glyph_ids[16]={
        0xb3U,0xc4U,0xdaU,0xbfU,0xc0U,0xd9U,0xc3U,0xb4U,
        0xc2U,0xc1U,0xc5U,0xdbU,0xdcU,0xdfU,0xddU,0xdeU};
    static const unsigned short glyph_unicode[16]={
        0x2502U,0x2500U,0x250cU,0x2510U,0x2514U,0x2518U,0x251cU,0x2524U,
        0x252cU,0x2534U,0x253cU,0x2588U,0x2584U,0x2580U,0x258cU,0x2590U};
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
    result=presentation_clock_route(window);
    if(result)return result;
    mysmb_win32_build_frame();
    saved_game=g_game;saved_audio=g_audio_output;
    memcpy(saved_pixels,g_pixels,sizeof(saved_pixels));
    mysmb_win32_shortcut(window,VK_TAB,1U);
    if(g_toggle_request!=MYSMB_IO_REQUEST_TOGGLE)return 3;
    g_toggle_request=0U;mysmb_win32_switch_presenter(window,0);
    if(!g_text_mode || !g_console.opened)return 4000+(int)GetLastError();
    ShowWindow(g_console.window,SW_HIDE);
    owned_focus=g_console.window;
    if(memcmp(&saved_game,&g_game,sizeof(g_game)) ||
        memcmp(&saved_audio,&g_audio_output,sizeof(g_audio_output)) ||
        g_focus_pause.pending!=0U)return 5;
    if(!GetConsoleScreenBufferInfo(g_console.output,&info) ||
        info.dwSize.X!=80 || info.dwSize.Y!=50 ||
        info.srWindow.Right-info.srWindow.Left+1!=80 ||
        info.srWindow.Bottom-info.srWindow.Top+1!=50)return 6;
    if(!GetConsoleMode(g_console.input,&mode) ||
        (mode&(ENABLE_VIRTUAL_TERMINAL_INPUT|ENABLE_LINE_INPUT|
            ENABLE_ECHO_INPUT|ENABLE_PROCESSED_INPUT|ENABLE_QUICK_EDIT_MODE)))return 46;
    close_state=GetMenuState(GetSystemMenu(g_console.window,FALSE),SC_CLOSE,MF_BYCOMMAND);
    if(close_state==(UINT)-1 || (close_state&(MF_DISABLED|MF_GRAYED)))return 45;
    ZeroMemory(&color_info,sizeof(color_info));color_info.cbSize=sizeof(color_info);
    if(!GetConsoleScreenBufferInfoEx(g_console.output,&color_info))return 43;
    for(i=0U;i<16U;++i) {
        rgb=mysmb_io_color_text_rgb((mysmb_io_u8)i);
        if(color_info.ColorTable[i]!=RGB((rgb>>16U)&255UL,(rgb>>8U)&255UL,rgb&255UL))return 44;
    }
    size.X=80;size.Y=50;origin.X=origin.Y=0;
    view.Left=view.Top=0;view.Right=79;view.Bottom=49;
    if(!ReadConsoleOutputW(g_console.output,cells,size,origin,&view))return 7;
    for(i=0U;i<4000U;++i)
        if(cells[i].Char.UnicodeChar!=(WCHAR)mysmb_io_text_glyph_unicode(g_text_frame.cells[i].character) ||
            cells[i].Attributes!=(WORD)(g_text_frame.cells[i].foreground|
                (g_text_frame.cells[i].background<<4U)))return 8;
    glyph_frame=g_text_frame;
    for(i=0U;i<16U;++i)glyph_frame.cells[i].character=glyph_ids[i];
    if(!mysmb_win32_text_console_present(&g_console,&glyph_frame))return 46;
    view.Left=view.Top=0;view.Right=79;view.Bottom=49;
    if(!ReadConsoleOutputW(g_console.output,cells,size,origin,&view))return 47;
    for(i=0U;i<16U;++i)
        if(cells[i].Char.UnicodeChar!=glyph_unicode[i])return 48;
    glyph_frame.cells[0].character=0x80U;
    if(mysmb_win32_text_console_present(&g_console,&glyph_frame))return 49;
    if(!mysmb_win32_text_console_present(&g_console,&g_text_frame))return 50;
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
    result=event_input_route(window);
    if(result)return result;
    DestroyWindow(window);return 0;
}
