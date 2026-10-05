#include <windows.h>
#include <string.h>

#include "app/game_io.h"
#include "app/game_snapshot.h"
#include "io/snapshot_store.h"
#include "io/snapshot_keys.h"
#include "platform/file/snapshot_files.h"
#include "platform/win32/audio_snapshot.h"
#include "io/color.h"
#include "io/control.h"
#include "game/area.h"
#include "game/game.h"
#include "ppu/frame.h"
#include "platform/win32/audio_output.h"
#include "platform/win32/focus_pause.h"
#include "platform/win32/text_console.h"
#include "platform/win32/launch.h"
#include "platform/win32/keyboard.h"
#include "platform/win32/frame_wait.h"
#include "game/presentation/text/scene.h"

#ifdef MYSMB_LOCAL_TITLE
#include "smb1_local_rom.h"
#include "smb1_local_title.h"
#endif

#define MYSMB_CLASS_NAME "MySMBWindow"
#define MYSMB_SCALE 2

static struct mysmb_game g_game;
static struct mysmb_frame g_frame;
static struct mysmb_ppu_frame g_ppu_frame;
static struct mysmb_io_audio_frame g_audio_frame;
static struct mysmb_win32_audio_output g_audio_output;
static struct mysmb_win32_focus_pause g_focus_pause;
static struct mysmb_io_control g_control;
static struct mysmb_io_snapshot g_snapshot;
static struct mysmb_io_snapshot_cache g_snapshot_cache;
static struct mysmb_snapshot_store g_snapshot_store;
static struct mysmb_file_storage g_snapshot_files;
static struct mysmb_snapshot_keys g_snapshot_keys;
static mysmb_io_u8 g_snapshot_fingerprint[16];
static mysmb_io_u8 g_snapshot_ready;
static mysmb_io_u8 g_snapshot_requests;
static struct mysmb_win32_text_console g_console;
static struct mysmb_win32_keyboard g_keyboard;
static struct mysmb_text_scene_workspace g_text_workspace;
static struct mysmb_io_text_frame g_text_frame;
static mysmb_io_u8 g_text_mode,g_switching,g_toggle_request,g_text_failed;
static mysmb_io_u8 g_window_focused;
static LARGE_INTEGER g_frequency;
static LARGE_INTEGER g_last_tick;
static struct mysmb_win32_frame_wait g_frame_wait;
static mysmb_u8 g_game_started;
static mysmb_u8 g_audio_available;
static mysmb_u8 g_title_paused;
static BITMAPINFO g_bitmap_info;
static DWORD g_pixels[MYSMB_SCREEN_WIDTH * MYSMB_SCREEN_HEIGHT];
static LRESULT CALLBACK mysmb_win32_window_proc(HWND,UINT,WPARAM,LPARAM);

static int mysmb_win32_presenter_focused(HWND window)
{
    (void)window;
    /* Input delivery belongs to each device,not a global foreground HWND.
     * RDP/terminal hosts can expose a different or unavailable HWND. */
    return g_text_mode?g_console.opened && g_console.focused:g_window_focused;
}
static void mysmb_win32_shortcut(HWND window,WORD key,mysmb_io_u8 pressed)
{
    mysmb_io_u8 focused,request;
    focused=(mysmb_io_u8)mysmb_win32_presenter_focused(window);
    if(key==VK_TAB) {
        g_toggle_request|=mysmb_io_control_toggle(&g_control,pressed,focused);
        return;
    }
    if(key==VK_ESCAPE && pressed && focused) {
        struct mysmb_io_input input;
        input.buttons=input.buttons2=0U;input.requests=MYSMB_IO_REQUEST_EXIT;
        mysmb_io_control_input(&g_control,&input);return;
    }
    if(key!='P' && key!='O')return;
    request=key=='P'?MYSMB_IO_REQUEST_SAVE:MYSMB_IO_REQUEST_LOAD;
    g_snapshot_requests|=mysmb_snapshot_keys_transition(&g_snapshot_keys,
        request,pressed,focused);
}

static mysmb_io_u8 mysmb_win32_requests_from_message(UINT message,WPARAM key)
{
    return message==WM_CLOSE || (message==WM_KEYDOWN && key==VK_ESCAPE)?
        MYSMB_IO_REQUEST_EXIT:0U;
}
static void mysmb_win32_release_keys(void)
{
    mysmb_win32_keyboard_reset(&g_keyboard);
    mysmb_snapshot_keys_reset(&g_snapshot_keys);g_snapshot_requests=0U;
    (void)mysmb_io_control_toggle(&g_control,0U,0U);
}
static int mysmb_win32_key_event(HWND window,WORD key,WORD scan,
    unsigned char pressed)
{
    int kind;
    if(!mysmb_win32_presenter_focused(window))return 0;
    kind=mysmb_win32_keyboard_event(&g_keyboard,key,scan,pressed);
    if(!kind)return 0;
    if(kind==1)mysmb_win32_shortcut(window,key,pressed);
    return 1;
}
static void mysmb_win32_finish_exit(HWND window)
{
    if (g_control.exit_requested!=0U) DestroyWindow(window);
}

static void mysmb_win32_update_title(HWND window)
{
    mysmb_u8 paused;
    const char *title;

    paused = mysmb_game_is_paused(&g_game);
    if (paused == g_title_paused) return;
    if (paused != 0U)
        title = g_audio_available != 0U ? "MySMB (Paused)" :
                "MySMB (Paused) (audio unavailable)";
    else
        title = g_audio_available != 0U ? "MySMB" :
                "MySMB (audio unavailable)";
    if (SetWindowText(window, title) != 0) g_title_paused = paused;
}

static mysmb_u8 mysmb_win32_buttons_from_keys(unsigned int keys)
{
    mysmb_u8 buttons;

    buttons = 0U;
    if ((keys & MYSMB_WIN32_KEY_LEFT) != 0U) buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_LEFT);
    if ((keys & MYSMB_WIN32_KEY_RIGHT) != 0U) buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_RIGHT);
    if ((keys & MYSMB_WIN32_KEY_DOWN) != 0U) buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_DOWN);
    if ((keys & MYSMB_WIN32_KEY_UP) != 0U) buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_UP);
    if ((keys & MYSMB_WIN32_KEY_START) != 0U) buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_START);
    if ((keys & MYSMB_WIN32_KEY_SELECT) != 0U) buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_SELECT);
    if ((keys & MYSMB_WIN32_KEY_B) != 0U) buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_B);
    if ((keys & MYSMB_WIN32_KEY_A) != 0U) buttons = (mysmb_u8)(buttons | MYSMB_BUTTON_A);
    return buttons;
}

static unsigned int mysmb_win32_poll_keys(void)
{
    return mysmb_win32_keyboard_sample(&g_keyboard);
}

static void mysmb_win32_draw_gameplay(const struct mysmb_io_video_frame *frame)
{
    DWORD palette[64];
    unsigned int index;
    for(index=0U;index<64U;++index)
        palette[index]=(DWORD)mysmb_io_color_rgb((mysmb_io_u8)index);
    for(index=0U;index<MYSMB_SCREEN_WIDTH*MYSMB_SCREEN_HEIGHT;++index)
        g_pixels[index]=palette[frame->pixels[index]&63U];
}
static void mysmb_win32_build_frame(void)
{
    struct mysmb_io_video_frame video;

    if(g_text_mode) {
        g_text_failed=(mysmb_io_u8)(!mysmb_text_scene_build(&g_game,&g_text_workspace,&g_text_frame) ||
            !mysmb_win32_text_console_present(&g_console,&g_text_frame));
        return;
    }
    mysmb_ppu_frame_build(&g_game.ppu, &g_ppu_frame);
    mysmb_game_io_video(&g_ppu_frame, &video);
    mysmb_win32_draw_gameplay(&video);
}

/* Only the root chooses a presenter; device code receives neutral cells.
 * Internal focus transfer never enters the game's auto-pause input path. */
static void mysmb_win32_switch_presenter(HWND window,int activate)
{
    g_switching=1U;
    mysmb_win32_keyboard_clear_game(&g_keyboard);
    if(!g_text_mode) {
        if(mysmb_win32_text_console_open(&g_console,window)) {
            g_text_mode=1U;
            if(activate) {
                ShowWindow(window,SW_HIDE);
                ShowWindow(g_console.window,SW_SHOW);
                SetForegroundWindow(g_console.window);
            }
        }
    } else {
        g_text_mode=0U;
        mysmb_win32_text_console_close(&g_console);
        if(activate) {ShowWindow(window,SW_SHOW);SetForegroundWindow(window);}
    }
    g_switching=0U;
    g_text_failed=0U;
    mysmb_win32_build_frame();
    if(!g_text_mode)InvalidateRect(window,NULL,FALSE);
}

static void mysmb_win32_snapshot_initialize(void)
{
    char directory[260];
    char *separator;
    DWORD count;
    struct mysmb_snapshot_files files;
    g_snapshot_ready=0U;g_snapshot_requests=0U;
    mysmb_snapshot_keys_reset(&g_snapshot_keys);
    mysmb_snapshot_cache_initialize(&g_snapshot_cache);
    mysmb_game_snapshot_fingerprint(&g_game,g_snapshot_fingerprint);
    count=GetModuleFileNameA(NULL,directory,sizeof(directory));
    if (count==0U || count>=sizeof(directory)) return;
    separator=strrchr(directory,'\\');
    if (!separator) return;
    separator[1]='\0';
    if (mysmb_file_storage_initialize(&g_snapshot_files,directory,
        mysmb_win32_snapshot_replace,&files) &&
        mysmb_snapshot_store_initialize(&g_snapshot_store,&files)) g_snapshot_ready=1U;
}
static void mysmb_win32_snapshot_capture(void)
{
    if (!mysmb_game_snapshot_running(&g_game,&g_frame)) return;
    if (mysmb_game_snapshot_capture(&g_game,&g_snapshot,g_snapshot_fingerprint) &&
        mysmb_win32_audio_capture(&g_audio_output.renderer,
            g_snapshot.payload+MYSMB_SNAPSHOT_CORE_BYTES))
        mysmb_snapshot_cache_update(&g_snapshot_cache,&g_snapshot,1U);
}
static int mysmb_win32_snapshot_request(HWND window)
{
    const struct mysmb_io_snapshot *candidate;
    struct mysmb_win32_audio_renderer audio;
    mysmb_io_u8 requests;
    requests=g_snapshot_requests;g_snapshot_requests=0U;
    if (!g_snapshot_ready || requests==0U || !mysmb_win32_presenter_focused(window))
        return 0;
    if ((requests&MYSMB_IO_REQUEST_LOAD)!=0U) {
        candidate=mysmb_snapshot_load(&g_snapshot_store,g_snapshot_fingerprint);
        if (!candidate) return 0;
        if (!mysmb_game_snapshot_valid(&g_game,candidate) ||
            !mysmb_win32_audio_restore(&audio,
                candidate->payload+MYSMB_SNAPSHOT_CORE_BYTES) ||
            !mysmb_win32_audio_reset_queue(&g_audio_output)) {
            g_snapshot_store.files.log(g_snapshot_store.files.context,
                "mysmb.log",MYSMB_SNAPSHOT_LOAD_ERROR);
            return 0;
        }
        (void)mysmb_game_snapshot_restore(&g_game,candidate);
        g_audio_output.renderer=audio;
        mysmb_snapshot_cache_update(&g_snapshot_cache,candidate,1U);
        mysmb_snapshot_keys_reset(&g_snapshot_keys);
        mysmb_win32_keyboard_clear_game(&g_keyboard);
        mysmb_win32_focus_pause_initialize(&g_focus_pause);
        mysmb_win32_focus_pause_gained(&g_focus_pause);
        mysmb_game_frame_initialize(&g_frame);
        g_game_started=1U;
        QueryPerformanceCounter(&g_last_tick);
        mysmb_win32_build_frame();mysmb_win32_update_title(window);
        InvalidateRect(window,NULL,FALSE);
        return 1;
    }
    if ((requests&MYSMB_IO_REQUEST_SAVE)!=0U)
        (void)mysmb_snapshot_save(&g_snapshot_store,
            mysmb_snapshot_cache_current(&g_snapshot_cache));
    return 0;
}

static void mysmb_win32_power_on(void)
{
    mysmb_game_power_on(&g_game);
    mysmb_text_observer_enable(&g_game,1U);
    mysmb_game_frame_initialize(&g_frame);
#ifdef MYSMB_LOCAL_TITLE
    mysmb_game_bind_area_source(&g_game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_chr_source(&g_game, mysmb_local_chr, MYSMB_LOCAL_CHR_SIZE);
    mysmb_game_bind_title_source(&g_game, mysmb_local_title_data,
                                 MYSMB_LOCAL_TITLE_DATA_SIZE,
                                 mysmb_local_title_icon_data,
                                 MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
#endif
}

static int mysmb_win32_argument_is_self_test(const char *command)
{
    static const char self_test[] = "--self-test";
    unsigned int index;

    while (*command == ' ') command++;
    for (index = 0U; self_test[index] != '\0'; ++index) {
        if (command[index] != self_test[index]) return 0;
    }
    return command[index] == '\0' ? 1 : 0;
}

#ifdef MYSMB_LOCAL_TITLE
/* Platform check: it exercises only the physical keyboard adapter and the
 * common pixel submission path; translated game behavior is tested in game. */
static int mysmb_win32_run_self_test(void)
{
    WNDCLASS window_class;
    HWND window;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_LEFT) != MYSMB_BUTTON_LEFT) return 14;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_RIGHT) != MYSMB_BUTTON_RIGHT) return 15;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_DOWN) != MYSMB_BUTTON_DOWN) return 16;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_UP) != MYSMB_BUTTON_UP) return 17;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_START) != MYSMB_BUTTON_START) return 18;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_SELECT) != MYSMB_BUTTON_SELECT) return 19;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_B) != MYSMB_BUTTON_B) return 20;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_A) != MYSMB_BUTTON_A) return 21;
    if (mysmb_win32_requests_from_message(WM_KEYUP,VK_ESCAPE)!=0U ||
        mysmb_win32_requests_from_message(WM_KEYDOWN,'K')!=0U ||
        mysmb_win32_requests_from_message(WM_CLOSE,0U)!=MYSMB_IO_REQUEST_EXIT) return 22;
    /* Actual hidden window/message/teardown route,no desktop key injection. */
    ZeroMemory(&window_class,sizeof(window_class));
    window_class.lpfnWndProc=mysmb_win32_window_proc;
    window_class.hInstance=GetModuleHandle(NULL);
    window_class.lpszClassName="MySMBExitProbe";
    if (!RegisterClass(&window_class)) return 23;
    window=CreateWindow(window_class.lpszClassName,"",WS_OVERLAPPEDWINDOW,
        0,0,32,32,NULL,NULL,window_class.hInstance,NULL);
    if (!window) return 24;
    mysmb_io_control_initialize(&g_control);
    SendMessage(window,WM_KEYDOWN,VK_ESCAPE,0);
    SendMessage(window,WM_KEYUP,VK_ESCAPE,0);
    if (g_control.exit_requested==0U) {DestroyWindow(window);return 25;}
    mysmb_win32_finish_exit(window);
    if (IsWindow(window)) return 26;
    UnregisterClass(window_class.lpszClassName,window_class.hInstance);
    return 0;
}
#endif
/* The device owns window geometry;the frame remains an unchanged256x240.
 * Quantize client sizes to16:15 integer units,not outer title/border sizes. */
static int g_geometry_adjusting;
static UINT mysmb_win32_window_dpi(HWND window)
{
    typedef UINT (WINAPI *dpi_fn)(HWND);
    dpi_fn fn=(dpi_fn)GetProcAddress(GetModuleHandleA("user32.dll"),"GetDpiForWindow");
    return fn?fn(window):96U;
}
static void mysmb_win32_window_margins(HWND window,UINT dpi,RECT *margins)
{
    typedef BOOL (WINAPI *adjust_fn)(LPRECT,DWORD,BOOL,DWORD,UINT);
    adjust_fn fn=(adjust_fn)GetProcAddress(GetModuleHandleA("user32.dll"),
        "AdjustWindowRectExForDpi");
    DWORD style=(DWORD)GetWindowLongPtr(window,GWL_STYLE);
    DWORD ex=(DWORD)GetWindowLongPtr(window,GWL_EXSTYLE);
    SetRect(margins,0,0,0,0);
    if(fn)fn(margins,style,FALSE,ex,dpi);
    else AdjustWindowRectEx(margins,style,FALSE,ex);
}
static int mysmb_win32_geometry_units(int width,int height,int by_height)
{
    int units=by_height?height/15:width/16;
    return units<16?16:units;
}
static void mysmb_win32_size_rectangle(HWND window,RECT *rect,UINT edge,UINT dpi)
{
    RECT margins;
    int width,height,units,dx,dy;
    mysmb_win32_window_margins(window,dpi,&margins);
    width=rect->right-rect->left-(margins.right-margins.left);
    height=rect->bottom-rect->top-(margins.bottom-margins.top);
    units=mysmb_win32_geometry_units(width,height,edge==WMSZ_TOP || edge==WMSZ_BOTTOM);
    dx=units*16+(margins.right-margins.left)-(rect->right-rect->left);
    dy=units*15+(margins.bottom-margins.top)-(rect->bottom-rect->top);
    if(edge==WMSZ_LEFT || edge==WMSZ_TOPLEFT || edge==WMSZ_BOTTOMLEFT)rect->left-=dx;
    else if(edge==WMSZ_TOP || edge==WMSZ_BOTTOM){rect->left-=dx/2;rect->right+=dx-dx/2;}
    else rect->right+=dx;
    if(edge==WMSZ_TOP || edge==WMSZ_TOPLEFT || edge==WMSZ_TOPRIGHT)rect->top-=dy;
    else if(edge==WMSZ_LEFT || edge==WMSZ_RIGHT){rect->top-=dy/2;rect->bottom+=dy-dy/2;}
    else rect->bottom+=dy;
}
static void mysmb_win32_size_limits(HWND window,MINMAXINFO *limits)
{
    MONITORINFO monitor;
    RECT margins;
    int units,w,h,bw,bh;
    monitor.cbSize=sizeof(monitor);
    if(!GetMonitorInfo(MonitorFromWindow(window,MONITOR_DEFAULTTONEAREST),&monitor))return;
    mysmb_win32_window_margins(window,mysmb_win32_window_dpi(window),&margins);
    bw=margins.right-margins.left;bh=margins.bottom-margins.top;
    w=monitor.rcWork.right-monitor.rcWork.left;
    h=monitor.rcWork.bottom-monitor.rcWork.top;
    units=(w-bw)/16;if((h-bh)/15<units)units=(h-bh)/15;
    if(units<1)units=1;
    limits->ptMaxSize.x=units*16+bw;limits->ptMaxSize.y=units*15+bh;
    limits->ptMaxPosition.x=monitor.rcWork.left-monitor.rcMonitor.left+
        (w-limits->ptMaxSize.x)/2;
    limits->ptMaxPosition.y=monitor.rcWork.top-monitor.rcMonitor.top+
        (h-limits->ptMaxSize.y)/2;
    limits->ptMinTrackSize.x=256+bw;limits->ptMinTrackSize.y=240+bh;
    limits->ptMaxTrackSize=limits->ptMaxSize;
}
static void mysmb_win32_normalize_client(HWND window)
{
    RECT client,outer;
    int units,w,h;
    if(g_geometry_adjusting || !GetClientRect(window,&client))return;
    w=client.right;h=client.bottom;
    if(w<=0 || h<=0 || (w%16==0 && h%15==0 && w/16==h/15))return;
    units=w/16;if(h/15<units)units=h/15;if(units<1)units=1;
    if(!GetWindowRect(window,&outer))return;
    g_geometry_adjusting=1;
    SetWindowPos(window,NULL,0,0,outer.right-outer.left-w+units*16,
        outer.bottom-outer.top-h+units*15,SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
    g_geometry_adjusting=0;
}
static void mysmb_win32_enable_dpi(void)
{
    typedef BOOL (WINAPI *aware_fn)(HANDLE);
    aware_fn fn=(aware_fn)GetProcAddress(GetModuleHandleA("user32.dll"),
        "SetProcessDpiAwarenessContext");
    if(!fn || !fn((HANDLE)(LONG_PTR)-4))SetProcessDPIAware();
}
static void mysmb_win32_paint(HWND window)
{
    PAINTSTRUCT paint;
    HDC dc;
    RECT client;

    dc = BeginPaint(window, &paint);
    GetClientRect(window,&client);
    if(client.right>0 && client.bottom>0)
    StretchDIBits(dc, 0, 0, client.right, client.bottom, 0, 0,
                  MYSMB_SCREEN_WIDTH, MYSMB_SCREEN_HEIGHT, g_pixels,
                  &g_bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    EndPaint(window, &paint);
}
static void mysmb_win32_step(HWND window)
{
    LARGE_INTEGER now;
    LONGLONG elapsed;
    LONGLONG frame_period;
    struct mysmb_input input;
    struct mysmb_io_input decoded;
    mysmb_u8 physical_buttons;
    unsigned int steps;
    unsigned int events;
    WORD key,scan;
    int event_kind;
    unsigned char pressed;

    if(g_text_mode && (g_text_failed || !IsWindow(g_console.window)))
        mysmb_win32_switch_presenter(window,1);
    for(events=0U;events<64U && g_text_mode &&
        (event_kind=mysmb_win32_text_console_key(&g_console,&key,&scan,&pressed));++events) {
        if(event_kind==2 && !pressed)mysmb_win32_release_keys();
        else if(event_kind==1)mysmb_win32_key_event(window,key,scan,pressed);
    }
    if(g_toggle_request) {
        g_toggle_request=0U;mysmb_win32_switch_presenter(window,1);
    }
    decoded.buttons=0U;decoded.buttons2=0U;decoded.requests=0U;
    mysmb_io_control_input(&g_control,&decoded);
    if (g_control.exit_requested!=0U) return;
    if (mysmb_win32_snapshot_request(window)) return;
    QueryPerformanceCounter(&now);
    elapsed = now.QuadPart - g_last_tick.QuadPart;
    frame_period = g_frequency.QuadPart / 60;
    if (elapsed < frame_period) return;

    if (mysmb_game_startup_step(&g_game, 1U) == 0U) {
        g_last_tick.QuadPart += frame_period;
        return;
    }
    g_game_started = 1U;

    if (g_focus_pause.focused != 0U && !mysmb_win32_presenter_focused(window)) {
        mysmb_win32_release_keys();
        mysmb_win32_focus_pause_lost(&g_focus_pause, g_game_started, &g_game);
    }
    if(mysmb_win32_presenter_focused(window))
        mysmb_win32_focus_pause_gained(&g_focus_pause);
    physical_buttons = 0U;
    if (g_focus_pause.focused != 0U)
        physical_buttons = mysmb_win32_buttons_from_keys(mysmb_win32_poll_keys());
    decoded.buttons2 = 0U;
    steps = 0U;
    do {
        decoded.buttons = mysmb_win32_focus_pause_buttons(&g_focus_pause,
                                                        &g_game, physical_buttons);
        mysmb_game_io_input(&decoded, &input);
        g_last_tick.QuadPart += frame_period;
        mysmb_game_tick(&g_game, &input, &g_frame);
        mysmb_win32_focus_pause_after_tick(&g_focus_pause, &g_game);
        mysmb_game_io_audio(&g_game, &g_audio_frame);
        mysmb_win32_audio_submit(&g_audio_output, &g_audio_frame);
        mysmb_win32_snapshot_capture();
        ++steps;
        elapsed = now.QuadPart - g_last_tick.QuadPart;
    } while (elapsed >= frame_period && steps < 4U);
    mysmb_win32_update_title(window);
    /* Retain remaining logical-frame debt. The next batch still returns to
     * the message pump after at most four updates;no game ticks are dropped. */
    mysmb_win32_build_frame();
    if(!g_text_mode)InvalidateRect(window, NULL, FALSE);
}

static LRESULT CALLBACK mysmb_win32_window_proc(HWND window, UINT message,
                                                  WPARAM w_param, LPARAM l_param)
{
    struct mysmb_io_input decoded;
    decoded.buttons=0U;decoded.buttons2=0U;
    decoded.requests=mysmb_win32_requests_from_message(message,w_param);
    if (decoded.requests!=0U) {
        mysmb_io_control_input(&g_control,&decoded);
        return 0;
    }
    if (message==WM_KEYDOWN || message==WM_KEYUP ||
        message==WM_SYSKEYDOWN || message==WM_SYSKEYUP) {
        if((message==WM_KEYDOWN || message==WM_SYSKEYDOWN) &&
            (l_param&0x40000000L)!=0 &&
            (w_param==VK_TAB || w_param=='P' || w_param=='O'))return 0;
        if(mysmb_win32_key_event(window,(WORD)w_param,
            (WORD)((l_param>>16)&255L),
            (unsigned char)(message==WM_KEYDOWN || message==WM_SYSKEYDOWN)))return 0;
    }
    if (message == WM_KILLFOCUS ||
        (message == WM_ACTIVATEAPP && w_param == 0U)) {
        g_window_focused=0U;
        if(!g_switching && !g_text_mode) {
            mysmb_win32_focus_pause_lost(&g_focus_pause, g_game_started, &g_game);
            mysmb_win32_release_keys();
        }
    }
    if (message == WM_SETFOCUS ||
        (message == WM_ACTIVATEAPP && w_param != 0U && GetFocus() == window)) {
        g_window_focused=1U;
        if(!g_switching && !g_text_mode)mysmb_win32_focus_pause_gained(&g_focus_pause);
    }
    if(message==WM_SIZING) {
        mysmb_win32_size_rectangle(window,(RECT *)l_param,(UINT)w_param,
            mysmb_win32_window_dpi(window));return TRUE;
    }
    if(message==WM_GETMINMAXINFO) {
        mysmb_win32_size_limits(window,(MINMAXINFO *)l_param);return 0;
    }
    if(message==0x02e0U) { /* WM_DPICHANGED,also builds with old headers. */
        RECT rect=*(RECT *)l_param;
        mysmb_win32_size_rectangle(window,&rect,WMSZ_BOTTOMRIGHT,LOWORD(w_param));
        SetWindowPos(window,NULL,rect.left,rect.top,rect.right-rect.left,
            rect.bottom-rect.top,SWP_NOZORDER|SWP_NOACTIVATE);return 0;
    }
    if(message==WM_SIZE) {
        if(w_param!=SIZE_MINIMIZED)mysmb_win32_normalize_client(window);
        InvalidateRect(window,NULL,FALSE);return 0;
    }
    if (message == WM_PAINT) {
        mysmb_win32_paint(window);
        return 0;
    }
    if (message == WM_DESTROY) {
        mysmb_win32_audio_close(&g_audio_output);
        mysmb_win32_text_console_close(&g_console);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(window, message, w_param, l_param);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR command, int show)
{
    WNDCLASS window_class;
    HWND window;
    MSG message;
    int start_text;
    unsigned int messages;
    RECT initial;

    (void)previous;
    mysmb_io_control_initialize(&g_control);
    if (mysmb_win32_argument_is_self_test(command) != 0) {
#ifdef MYSMB_LOCAL_TITLE
        return mysmb_win32_run_self_test();
#else
        return 2;
#endif
    }
    mysmb_win32_enable_dpi();
    start_text=mysmb_win32_start_in_text();
    if(!start_text)(void)FreeConsole();
    ZeroMemory(&window_class, sizeof(window_class));
    window_class.lpfnWndProc = mysmb_win32_window_proc;
    window_class.hInstance = instance;
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.lpszClassName = MYSMB_CLASS_NAME;
    if (RegisterClass(&window_class) == 0) {
        return 1;
    }

    ZeroMemory(&g_bitmap_info, sizeof(g_bitmap_info));
    g_bitmap_info.bmiHeader.biSize = sizeof(g_bitmap_info.bmiHeader);
    g_bitmap_info.bmiHeader.biWidth = MYSMB_SCREEN_WIDTH;
    g_bitmap_info.bmiHeader.biHeight = -(LONG)MYSMB_SCREEN_HEIGHT;
    g_bitmap_info.bmiHeader.biPlanes = 1U;
    g_bitmap_info.bmiHeader.biBitCount = 32U;
    g_bitmap_info.bmiHeader.biCompression = BI_RGB;
    QueryPerformanceFrequency(&g_frequency);
    QueryPerformanceCounter(&g_last_tick);
    g_game_started = 0U;
    mysmb_win32_focus_pause_initialize(&g_focus_pause);
    mysmb_win32_power_on();
    mysmb_win32_snapshot_initialize();
    SetRect(&initial,0,0,MYSMB_SCREEN_WIDTH*MYSMB_SCALE,MYSMB_SCREEN_HEIGHT*MYSMB_SCALE);
    AdjustWindowRectEx(&initial,WS_OVERLAPPEDWINDOW,FALSE,0U);
    window = CreateWindow(MYSMB_CLASS_NAME, "MySMB", WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          initial.right-initial.left,initial.bottom-initial.top,
                          NULL, NULL, instance, NULL);
    if (window == NULL) {
        return 1;
    }
    if(start_text)mysmb_win32_switch_presenter(window,0);
    if(g_text_mode) {
        ShowWindow(g_console.window,show);
        SetForegroundWindow(g_console.window);
    } else {
        ShowWindow(window, show);
        UpdateWindow(window);
    }
    g_audio_available = mysmb_win32_audio_open(&g_audio_output) != 0 ? 1U : 0U;
    g_title_paused = 2U;
    mysmb_win32_update_title(window);
    mysmb_win32_frame_wait_open(&g_frame_wait);
    QueryPerformanceCounter(&g_last_tick);

    for (;;) {
        for(messages=0U;messages<64U &&
            PeekMessage(&message, NULL, 0U, 0U, PM_REMOVE)!=0;++messages) {
            if (message.message == WM_QUIT) {
                mysmb_win32_frame_wait_close(&g_frame_wait);
                return 0;
            }
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        if (g_control.exit_requested!=0U) mysmb_win32_finish_exit(window);
        else mysmb_win32_step(window);
        mysmb_win32_frame_wait_until(&g_frame_wait,
            g_last_tick.QuadPart+g_frequency.QuadPart/60,
            g_frequency.QuadPart);
    }
}

#ifndef MYSMB_WIN32_EMBEDDED_TEST
/* Console-subsystem CRT entry preserves interactive shell wait semantics.
 * Presenter policy still belongs to the Windows root,not the CRT subsystem. */
int main(void)
{
    STARTUPINFOA startup;
    char *command=GetCommandLineA();
    if(*command=='"') {
        ++command;while(*command && *command!='"')++command;
        if(*command)++command;
    } else while(*command && *command!=' ' && *command!='\t')++command;
    while(*command==' ' || *command=='\t')++command;
    ZeroMemory(&startup,sizeof(startup));startup.cb=sizeof(startup);
    GetStartupInfoA(&startup);
    return WinMain(GetModuleHandle(NULL),NULL,command,
        (startup.dwFlags&STARTF_USESHOWWINDOW)!=0U?startup.wShowWindow:SW_SHOWDEFAULT);
}
#endif
