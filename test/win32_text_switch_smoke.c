#include "io/text_glyph.h"
#include <windows.h>
#include <string.h>
#include <stdio.h>
static HWND owned_focus;
static unsigned int async_calls;
static HWND mismatched_foreground;
static unsigned int foreground_calls;
static RECT diagnostic_client,diagnostic_work,diagnostic_outer;
static int diagnostic_game_changed,diagnostic_audio_changed;
static HWND probe_foreground(void){++foreground_calls;return mismatched_foreground;}
static SHORT probe_key(int key){(void)key;++async_calls;return 0;}
#define GetForegroundWindow probe_foreground
#define GetAsyncKeyState probe_key
static int painted_width,painted_height,paint_source_ok;
static int probe_stretch(HDC dc,int x,int y,int w,int h,int sx,int sy,int sw,int sh,
    const void *bits,const BITMAPINFO *info,UINT usage,DWORD rop)
{
    painted_width=w;painted_height=h;
    paint_source_ok=x==0 && y==0 && sx==0 && sy==0 && sw==256 && sh==240;
    return StretchDIBits(dc,x,y,w,h,sx,sy,sw,sh,bits,info,usage,rop);
}
#define StretchDIBits probe_stretch
#define WinMain mysmb_unused_product_entry
#define MYSMB_WIN32_EMBEDDED_TEST 1
#include "../src/platform/win32/main_win32.c"
#undef WinMain
static struct mysmb_game saved_game;
static struct mysmb_win32_audio_output saved_audio;
static DWORD saved_pixels[MYSMB_SCREEN_WIDTH*MYSMB_SCREEN_HEIGHT];
static struct mysmb_io_snapshot expected_snapshot,restored_snapshot;
static struct mysmb_io_text_frame expected_text;
static int console_shortcut(HWND window,WORD key,unsigned char down);
static int console_restore_route(void)
{
    CONSOLE_FONT_INFOEX font,after;
    CONSOLE_SCREEN_BUFFER_INFO info;
    CHAR_INFO readback[4000];
    COORD size={80,50},origin={0,0};
    SMALL_RECT view;
    unsigned int cycle,phase,i,attempt;
    HWND host=g_console.window;
    ZeroMemory(&font,sizeof(font));font.cbSize=sizeof(font);
    if(!GetCurrentConsoleFontEx(g_console.output,FALSE,&font))return 110;
    for(cycle=0;cycle<3;++cycle) {
        for(phase=0;phase<2;++phase) {
            /* Same WM_SYSCOMMAND as title-bar maximize/Restore buttons. */
            if(!PostMessage(host,WM_SYSCOMMAND,phase?SC_RESTORE:SC_MAXIMIZE,0))return 111;
            for(attempt=0;attempt<80;++attempt) {
                if((IsZoomed(host)!=0)==(phase==0))break;
                Sleep(25U);
            }
            if(attempt==80)return 112;
            /* Caption state precedes final buffer resize. Model continuous
             * rendering until every cell converges,with a one-second bound. */
            for(attempt=0;attempt<40;++attempt) {
                mysmb_win32_build_frame();
                if(!g_text_mode || g_text_failed || host!=g_console.window)return 113;
                if(!GetConsoleScreenBufferInfo(g_console.output,&info))return 114;
                view.Left=view.Top=0;view.Right=79;view.Bottom=49;
                if(!ReadConsoleOutputW(g_console.output,readback,size,origin,&view))return 117;
                i=0;
                if(view.Right==79 && view.Bottom==49)for(;i<4000;++i)
                    if(readback[i].Char.UnicodeChar!=mysmb_io_text_glyph_unicode(g_text_frame.cells[i].character) ||
                        readback[i].Attributes!=(WORD)(g_text_frame.cells[i].foreground|
                            (g_text_frame.cells[i].background<<4)))break;
                if(i==4000)break;
                Sleep(25U);
            }
            if(attempt==40)return 118;
            if(phase && (info.dwSize.X!=80 || info.dwSize.Y!=50 ||
                info.srWindow.Left!=0 || info.srWindow.Top!=0 ||
                info.srWindow.Right!=79 || info.srWindow.Bottom!=49))return 115;
            ZeroMemory(&after,sizeof(after));after.cbSize=sizeof(after);
            if(!GetCurrentConsoleFontEx(g_console.output,FALSE,&after) ||
                font.dwFontSize.X!=after.dwFontSize.X ||
                font.dwFontSize.Y!=after.dwFontSize.Y)return 116;
        }
    }
    return 0;
}
static int geometry_route(HINSTANCE instance)
{
    HWND window;
    RECT initial,rect,margins,client,outer;
    MINMAXINFO limits;
    MONITORINFO monitor;
    UINT edge,dpi;
    int w,h;
    SetRect(&initial,0,0,512,480);
    AdjustWindowRectEx(&initial,WS_OVERLAPPEDWINDOW,FALSE,0U);
    window=CreateWindow("MySMBTextSwitchProbe","geometry",WS_OVERLAPPEDWINDOW,
        30,30,initial.right-initial.left,initial.bottom-initial.top,NULL,NULL,instance,NULL);
    if(!window)return 90;
    for(dpi=96U;dpi<=192U;dpi+=48U) {
        mysmb_win32_window_margins(window,dpi,&margins);
        for(edge=WMSZ_LEFT;edge<=WMSZ_BOTTOMRIGHT;++edge) {
            SetRect(&rect,40,40,813,709);
            mysmb_win32_size_rectangle(window,&rect,edge,dpi);
            w=rect.right-rect.left-(margins.right-margins.left);
            h=rect.bottom-rect.top-(margins.bottom-margins.top);
            if(w<256 || h<240 || w*15!=h*16)return 91;
        }
    }
    mysmb_win32_window_margins(window,mysmb_win32_window_dpi(window),&margins);
    for(edge=WMSZ_LEFT;edge<=WMSZ_BOTTOMRIGHT;++edge) {
        SetRect(&rect,40,40,43,43);
        SendMessage(window,WM_SIZING,edge,(LPARAM)&rect);
        if(rect.right-rect.left-(margins.right-margins.left)!=256 ||
            rect.bottom-rect.top-(margins.bottom-margins.top)!=240)return 92;
    }
    ZeroMemory(&limits,sizeof(limits));SendMessage(window,WM_GETMINMAXINFO,0,(LPARAM)&limits);
    monitor.cbSize=sizeof(monitor);
    if(!GetMonitorInfo(MonitorFromWindow(window,MONITOR_DEFAULTTONEAREST),&monitor))return 93;
    w=limits.ptMaxSize.x-(margins.right-margins.left);
    h=limits.ptMaxSize.y-(margins.bottom-margins.top);
    if(w*15!=h*16 || limits.ptMaxSize.x>monitor.rcWork.right-monitor.rcWork.left ||
        limits.ptMaxSize.y>monitor.rcWork.bottom-monitor.rcWork.top)return 94;
    /* Real sizing messages and paint destination,including programmatic changes. */
    ZeroMemory(&g_bitmap_info,sizeof(g_bitmap_info));
    g_bitmap_info.bmiHeader.biSize=sizeof(g_bitmap_info.bmiHeader);
    g_bitmap_info.bmiHeader.biWidth=256;g_bitmap_info.bmiHeader.biHeight=-240;
    g_bitmap_info.bmiHeader.biPlanes=1;g_bitmap_info.bmiHeader.biBitCount=32;
    for(edge=0;edge<3;++edge) {
        SetWindowPos(window,NULL,0,0,501+(int)edge*73,503+(int)edge*41,
            SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
        GetClientRect(window,&client);
        if(client.right*15!=client.bottom*16)return 95;
        InvalidateRect(window,NULL,FALSE);SendMessage(window,WM_PAINT,0,0);
        if(painted_width!=client.right || painted_height!=client.bottom || !paint_source_ok)return 96;
    }
    ShowWindow(window,SW_MAXIMIZE);GetClientRect(window,&client);GetWindowRect(window,&outer);
    if(!IsZoomed(window) || client.right*15!=client.bottom*16)return 97;
    {
        POINT corner={0,0};
        ClientToScreen(window,&corner);
        SetRect(&diagnostic_client,corner.x,corner.y,corner.x+client.right,corner.y+client.bottom);
        diagnostic_work=monitor.rcWork;diagnostic_outer=outer;
        if(corner.x<monitor.rcWork.left || corner.y<monitor.rcWork.top ||
            corner.x+client.right>monitor.rcWork.right ||
            corner.y+client.bottom>monitor.rcWork.bottom)return 98;
    }
    ShowWindow(window,SW_RESTORE);GetClientRect(window,&client);
    if(client.right*15!=client.bottom*16)return 99;
    SetRect(&rect,35,35,743,722);SendMessage(window,0x02e0U,MAKELONG(144,144),(LPARAM)&rect);
    GetClientRect(window,&client);if(client.right*15!=client.bottom*16)return 100;
    ShowWindow(window,SW_MINIMIZE);SendMessage(window,WM_PAINT,0,0);
    ShowWindow(window,SW_RESTORE);
    /* DestroyWindow invokes root cleanup;no game has been initialized here. */
    DestroyWindow(window);return 0;
}

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
    /* Freeze logical updates for device-only assertions. RDP host calls can
     * consume more than one second;real debt is tested separately above. */
    g_last_tick.QuadPart+=g_frequency.QuadPart*60;
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
    owned_focus=window;SendMessage(window,WM_SETFOCUS,0,0);mysmb_win32_release_keys();
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
    SendMessage(window,WM_ACTIVATEAPP,FALSE,0);
    SendMessage(window,WM_KEYDOWN,'W',0);
    if(mysmb_win32_poll_keys())return 86;
    SendMessage(window,WM_KEYUP,'W',0);
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
    if(mysmb_win32_poll_keys() || g_console.focused)return 70;
    /* A character-only remote record needs neither a VK nor a focus gain. */
    {
        INPUT_RECORD character;
        ZeroMemory(&character,sizeof(character));character.EventType=KEY_EVENT;
        character.Event.KeyEvent.bKeyDown=TRUE;
        character.Event.KeyEvent.uChar.UnicodeChar=L'w';
        if(!WriteConsoleInputW(g_console.input,&character,1U,&written) || written!=1U)return 87;
        input_only_step(window);
        if(!g_console.focused || mysmb_win32_buttons_from_keys(mysmb_win32_poll_keys())!=MYSMB_BUTTON_UP)return 88;
        character.Event.KeyEvent.bKeyDown=FALSE;
        if(!WriteConsoleInputW(g_console.input,&character,1U,&written) || written!=1U)return 89;
        input_only_step(window);if(mysmb_win32_poll_keys())return 90;
    }
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
    /* An optional console loss hint clears held state and reaches auto-pause.
     * Valid subsequent key records must work even without a gain hint. */
    owned_focus=NULL;
    {
        INPUT_RECORD loss;
        DWORD written;
        ZeroMemory(&loss,sizeof(loss));loss.EventType=FOCUS_EVENT;
        loss.Event.FocusEvent.bSetFocus=FALSE;
        FlushConsoleInputBuffer(g_console.input);
        if(!WriteConsoleInputA(g_console.input,&loss,1U,&written) || written!=1U)return 85;
    }
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

static int mysmb_fixture_run(HINSTANCE instance,HINSTANCE previous,LPSTR command,int show)
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
    mysmb_win32_enable_dpi();
    ZeroMemory(&wc,sizeof(wc));wc.lpfnWndProc=mysmb_win32_window_proc;
    wc.hInstance=instance;wc.lpszClassName="MySMBTextSwitchProbe";
    if(!RegisterClass(&wc))return 1;
    result=geometry_route(instance);if(result)return result;
    window=CreateWindow(wc.lpszClassName,"",0,0,0,256,240,NULL,NULL,instance,NULL);
    if(!window)return 2;
    owned_focus=window;SendMessage(window,WM_SETFOCUS,0,0);
    mismatched_foreground=strstr(command,"foreign")?
        CreateWindowA("STATIC","unrelated foreground fixture",0,0,0,0,0,NULL,NULL,instance,NULL):NULL;
    foreground_calls=0U;
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
    if(!strncmp(command,"borrowed",8U)) {
        HWND parent=NULL;
        result=event_input_route(window);if(result)return result;
        for(i=0U;i<3U;++i) {
            mysmb_win32_switch_presenter(window,0);
            if(!g_text_mode || !g_console.borrowed)return 80;
            if(parent && parent!=g_console.window)return 81;
            parent=g_console.window;owned_focus=parent;
            result=console_restore_route();if(result)return result;
            if(memcmp(&saved_game,&g_game,sizeof(g_game)) ||
                memcmp(&saved_audio,&g_audio_output,sizeof(saved_audio)) ||
                memcmp(saved_pixels,g_pixels,sizeof(saved_pixels)))return 82;
            mysmb_win32_shortcut(window,VK_TAB,0U);
            mysmb_win32_shortcut(window,VK_TAB,1U);
            input_only_step(window);owned_focus=window;
            if(g_text_mode || g_console.opened || g_console.borrowed)return 83;
            {
                RECT resized;
                SetWindowPos(window,NULL,0,0,672,633,SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
                GetClientRect(window,&resized);
                diagnostic_client=resized;
                diagnostic_game_changed=memcmp(&saved_game,&g_game,sizeof(g_game))!=0;
                diagnostic_audio_changed=memcmp(&saved_audio,&g_audio_output,sizeof(saved_audio))!=0;
                if(resized.right*15!=resized.bottom*16 ||
                    memcmp(&saved_game,&g_game,sizeof(g_game)) ||
                    memcmp(&saved_audio,&g_audio_output,sizeof(saved_audio)))return 84;
            }
            mysmb_win32_shortcut(window,VK_TAB,0U);
        }
        DestroyWindow(window);return 0;
    }
    mysmb_win32_shortcut(window,VK_TAB,1U);
    if(g_toggle_request!=MYSMB_IO_REQUEST_TOGGLE)return 3;
    g_toggle_request=0U;mysmb_win32_switch_presenter(window,0);
    if(!g_text_mode || !g_console.opened)return 4000+(int)GetLastError();
    {
        char title[80];
        if(GetConsoleTitleA(title,sizeof(title))!=5U || strcmp(title,"MySMB"))return 51;
    }
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
    result=console_restore_route();if(result)return result;
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
    {
        char title[80];
        if(GetConsoleTitleA(title,sizeof(title))!=5U || strcmp(title,"MySMB"))return 52;
    }
    ShowWindow(g_console.window,SW_HIDE);
    view.Left=view.Top=view.Right=view.Bottom=0;
    size.X=79;size.Y=49;
    if(!SetConsoleWindowInfo(g_console.output,TRUE,&view) ||
        !SetConsoleScreenBufferSize(g_console.output,size))return 21;
    mysmb_win32_build_frame();
    if(g_text_failed || !g_text_mode)return 22;
    if(!GetConsoleScreenBufferInfo(g_console.output,&info) || info.dwSize.X!=80 ||
        info.dwSize.Y!=50 || info.srWindow.Right!=79 || info.srWindow.Bottom!=49)return 23;
    input_only_step(window);if(!g_text_mode || g_text_failed)return 24;
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
    if(foreground_calls)return 120;
    DestroyWindow(window);return 0;
}

/* A shell's START status is not the GUI child's test result. Emit an explicit
 * neutral result under the supplied ignored output directory for host probes. */
int WINAPI WinMain(HINSTANCE instance,HINSTANCE previous,LPSTR command,int show)
{
    int result;
    char normalized[520];
    const char *directory=command;
    char path[600];
    unsigned int length;
    FILE *file;
    if(command[0]=='"' && strlen(command)<sizeof(normalized)) {
        length=(unsigned int)strlen(command+1);
        if(length && command[length]=='"')--length;
        memcpy(normalized,command+1,length);normalized[length]=0;
        command=normalized;directory=command;
    }
    result=mysmb_fixture_run(instance,previous,command,show);
    if(!strncmp(directory,"borrowed",8U)) {
        while(*directory && *directory!=' ')++directory;
        while(*directory==' ')++directory;
    }
    if(*directory=='"')++directory;
    length=(unsigned int)strlen(directory);
    if(length && directory[length-1]=='"')--length;
    if(length && length<500U) {
        memcpy(path,directory,length);path[length]=0;
        strcat(path,"/root-result.txt");
        file=fopen(path,"w");if(file){fprintf(file,"%d\n",result);fclose(file);}
        if(result==98 || result==84) {
            path[length]=0;strcat(path,"/geometry-diagnostic.txt");file=fopen(path,"w");
            if(file) {
                fprintf(file,"client%d,%d,%d,%d work%d,%d,%d,%d outer%d,%d,%d,%d\n",
                    diagnostic_client.left,diagnostic_client.top,diagnostic_client.right,diagnostic_client.bottom,
                    diagnostic_work.left,diagnostic_work.top,diagnostic_work.right,diagnostic_work.bottom,
                    diagnostic_outer.left,diagnostic_outer.top,diagnostic_outer.right,diagnostic_outer.bottom);
                fprintf(file,"game_changed%d audio_changed%d\n",diagnostic_game_changed,diagnostic_audio_changed);
                fclose(file);
            }
        }
    }
    return result;
}
