#include "io/video.h"
#include "io/color.h"
#include "platform/win32/snapshot_replace.h"
#include <windows.h>
#include <string.h>

#include "app/game_io.h"
#include "app/game_snapshot.h"
#include "app/input_mapping.h"
#include "io/snapshot_store.h"
#include "io/snapshot_keys.h"
#include "io/file/snapshot_files.h"
#include "platform/win32/audio_snapshot.h"
#include "kvm/color.h"
#include "io/control.h"
#include "core/area.h"
#include "core/game.h"
#include "ppu/frame.h"
#include "io/palette_expand.h"
#include "platform/win32/audio_output.h"
#include "platform/win32/focus_pause.h"
#include "win32/text_console.h"
#include "win32/launch.h"
#include "win32/input.h"
#include "win32/window.h"
#include "win32/frame_wait.h"
#include "win32/window_geometry.h"
#include "text/scene.h"

#ifdef MYSMB_LOCAL_TITLE
#include "smb1_local_rom.h"
#include "smb1_local_title.h"
#endif

#define MYSMB_CLASS_NAME "MySMBWindow"
#define MYSMB_SCALE 2

static struct mysmb_game g_game;
static struct mysmb_frame g_frame;
static struct mysmb_ppu_frame g_ppu_frame;
static struct mysmb_ppu_frame_workspace g_ppu_workspace;
static mygames_kvm_u8 g_video_palette[MYSMB_VIDEO_PALETTE_COLORS];
static mygames_kvm_u8 g_chr_decoded[MYSMB_PPU_CHR_DECODED_BYTES];
static mygames_kvm_u8 g_background_slots[MYSMB_PPU_BACKGROUND_BYTES];
static mygames_kvm_u8 g_background_second[MYSMB_PPU_BACKGROUND_SECOND_BYTES];
static struct mysmb_io_audio_frame g_audio_frame;
static struct mysmb_win32_audio_output g_audio_output;
static struct mysmb_win32_focus_pause g_focus_pause;
static struct mysmb_io_control g_control;
static struct mysmb_snapshot_store g_snapshot_store;
static struct mysmb_file_storage g_snapshot_files;
static struct mysmb_snapshot_keys g_snapshot_keys;
static mygames_kvm_u8 g_snapshot_fingerprint[16];
static mygames_kvm_u8 g_snapshot_ready;
static mygames_kvm_u8 g_snapshot_requests;
static struct mygames_win32_text_console g_console;
static struct mygames_win32_text_console g_console_job;
static HANDLE g_console_thread;
static HDESK g_console_desktop;
static struct mygames_win32_input g_keyboard;
static struct mygames_win32_window_input g_window_input;
static struct mysmb_app_input_mapping g_input_mapping;
static mysmb_u8 g_mapped_buttons;
static struct mysmb_text_scene_workspace g_text_workspace;
static struct mysmb_io_text_frame g_text_frame;
static mygames_kvm_u8 g_text_mode,g_switching,g_toggle_request,g_text_failed;
static mygames_kvm_u8 g_window_focused;
static LARGE_INTEGER g_frequency;
static LARGE_INTEGER g_last_tick;
static struct mygames_win32_frame_wait g_frame_wait;
/* Window messages can arrive while CreateWindow is establishing a test or
 * product window.  Keep the Mario-owned geometry declaration valid from
 * process startup, then initialise the identical values in WinMain. */
static struct mygames_win32_window_geometry g_window_geometry={16,15,16,32,0};
static mysmb_u8 g_game_started;
static mysmb_u8 g_audio_available;
static mysmb_u8 g_title_paused;
static DWORD g_pixels[MYSMB_SCREEN_WIDTH * MYSMB_SCREEN_HEIGHT];
static LRESULT CALLBACK mysmb_win32_window_proc(HWND,UINT,WPARAM,LPARAM);

static int mysmb_win32_presenter_focused(HWND window)
{
    (void)window;
    /* Input delivery belongs to each device,not a global foreground HWND.
     * RDP/terminal hosts can expose a different or unavailable HWND. */
    return g_text_mode?g_console.opened && g_console.focused:g_window_focused;
}
static void mysmb_win32_apply_requests(HWND window,mygames_kvm_u8 requests,
    mygames_kvm_u8 pressed)
{
    mygames_kvm_u8 focused,request;
    focused=(mygames_kvm_u8)mysmb_win32_presenter_focused(window);
    if((requests&MYSMB_IO_REQUEST_TOGGLE)!=0U) {
        g_toggle_request|=mysmb_io_control_toggle(&g_control,pressed,focused);
    }
    if((requests&MYSMB_IO_REQUEST_EXIT)!=0U && pressed && focused) {
        struct mysmb_io_input input;
        input.buttons=input.buttons2=0U;input.requests=MYSMB_IO_REQUEST_EXIT;
        mysmb_io_control_input(&g_control,&input);return;
    }
    request=(mygames_kvm_u8)(requests&(MYSMB_IO_REQUEST_SAVE|MYSMB_IO_REQUEST_LOAD));
    if(request!=0U)g_snapshot_requests|=mysmb_snapshot_keys_transition(
        &g_snapshot_keys,request,pressed,focused);
}

static mygames_kvm_u8 mysmb_win32_requests_from_message(UINT message,WPARAM key)
{
    return message==WM_CLOSE || (message==WM_KEYDOWN && key==VK_ESCAPE)?
        MYSMB_IO_REQUEST_EXIT:0U;
}
static void mysmb_win32_release_keys(void)
{
    mygames_win32_input_clear(&g_keyboard);
    mysmb_app_input_mapping_initialize(&g_input_mapping);
    g_mapped_buttons=0U;
    mysmb_snapshot_keys_reset(&g_snapshot_keys);g_snapshot_requests=0U;
    (void)mysmb_io_control_toggle(&g_control,0U,0U);
}
static void mysmb_win32_transfer_keys(void)
{
    mygames_kvm_u8 tab_held=g_control.toggle_held;
    mysmb_win32_release_keys();
    /* A presenter transfer does not physically release the app's Tab key.
     * Suppress a make delivered by the new device until its break arrives. */
    g_control.toggle_held=tab_held;
}
static void mysmb_win32_physical_event(void *context,HWND window,
    const struct mygames_kvm_input_event *event)
{
    struct mysmb_io_input mapped;
    if(event->kind==MYGAMES_KVM_INPUT_FOCUS) {
        if(!context) {
            g_window_focused=event->down;
            if(g_text_mode)return; /* Hidden GUI focus is not Console focus. */
        }
        if(!g_switching) {
            if(event->down)mysmb_win32_focus_pause_gained(&g_focus_pause);
            else {
                mysmb_win32_focus_pause_lost(&g_focus_pause,g_game_started,&g_game);
                mysmb_win32_release_keys();
            }
        }
        return;
    }
    if(event->kind!=MYGAMES_KVM_INPUT_KEY)return;
    if(event->down && !mysmb_win32_presenter_focused(window))return;
    mapped.buttons=mapped.buttons2=mapped.requests=0U;
    mysmb_app_input_mapping_event(&g_input_mapping,event,&mapped);
    g_mapped_buttons=mapped.buttons;
    if(!event->repeat)mysmb_win32_apply_requests(window,mapped.requests,event->down);
}
static int mysmb_win32_key_event(HWND window,WORD key,WORD scan,unsigned char pressed)
{
    struct mygames_kvm_input_event event;
    if(pressed && !mysmb_win32_presenter_focused(window))return 0;
    if(!mygames_win32_input_key(&g_keyboard,key,scan,pressed,&event))return 0;
    mysmb_win32_physical_event(0,window,&event);return 1;
}

/* Root-local probes retain these narrow helpers.  They exercise the same
 * generic-event then Mario-mapping route as a delivered host key. */
static void mysmb_win32_shortcut(HWND window,WORD key,mygames_kvm_u8 pressed)
{
    struct mygames_kvm_input_event event;
    struct mysmb_io_input mapped;
    if(!mygames_win32_input_key(&g_keyboard,key,0U,pressed,&event))return;
    mapped.buttons=mapped.buttons2=mapped.requests=0U;
    mysmb_app_input_mapping_event(&g_input_mapping,&event,&mapped);
    g_mapped_buttons=mapped.buttons;
    if(event.repeat==0U)mysmb_win32_apply_requests(window,mapped.requests,pressed);
}

static unsigned int mysmb_win32_poll_keys(void)
{
    return g_mapped_buttons;
}

static mysmb_u8 mysmb_win32_buttons_from_keys(unsigned int keys)
{
    return (mysmb_u8)keys;
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


static int mysmb_win32_present_text(struct mygames_win32_text_console *console,
    const struct mysmb_io_text_frame *frame)
{
    struct mygames_kvm_text_frame view;
    mysmb_text_frame_view(frame,&view);
    return mygames_win32_text_console_present(console,&view);
}

static void mysmb_win32_draw_gameplay(const struct mysmb_palette_video_frame *frame)
{
    DWORD palette[MYSMB_VIDEO_PALETTE_COLORS];
    unsigned int index;
    for(index=0U;index<MYSMB_VIDEO_PALETTE_COLORS;++index)
        palette[index]=(DWORD)mysmb_io_color_rgb(frame->master_colors[index]);
    for(index=0U;index<MYSMB_SCREEN_WIDTH*MYSMB_SCREEN_HEIGHT;++index)
        g_pixels[index]=palette[frame->pixels[index]];
}
static void mysmb_win32_build_frame(void)
{
    struct mysmb_palette_video_frame video;

    if(g_text_mode) {
        g_text_failed=(mygames_kvm_u8)(!mysmb_text_scene_build_profile(&g_game,&g_text_workspace,&g_text_frame,25U) ||
            mysmb_win32_present_text(&g_console,&g_text_frame)==MYGAMES_WIN32_CONSOLE_LOST);
        return;
    }
    mysmb_ppu_frame_palette(&g_game.ppu,g_video_palette);
    mysmb_ppu_frame_build_slots_cached(&g_game.ppu,&g_ppu_frame,&g_ppu_workspace);
    video.pixels=g_ppu_frame.pixels;video.master_colors=g_video_palette;
    mysmb_win32_draw_gameplay(&video);
}

/* Host allocation can wait on an external terminal. The device thread owns
 * only its pending console; the root keeps pumping while it is acquired. */
static DWORD WINAPI mygames_win32_console_job(void *owner)
{
    (void)SetThreadDesktop(g_console_desktop);
    return mygames_win32_text_console_open_profile(&g_console_job,(HWND)owner,25U,"MySMB")?1U:0U;
}
static void mygames_win32_console_begin(HWND window)
{
    if(g_console_thread)return;
    g_switching=1U;
    mysmb_win32_transfer_keys();
    ZeroMemory(&g_console_job,sizeof(g_console_job));
    g_console_desktop=GetThreadDesktop(GetCurrentThreadId());
    g_console_thread=CreateThread(NULL,0U,mygames_win32_console_job,window,0U,NULL);
    if(!g_console_thread)g_switching=0U;
}
static void mysmb_win32_console_complete(HWND window)
{
    DWORD result;
    if(!g_console_thread || WaitForSingleObject(g_console_thread,0U)!=WAIT_OBJECT_0)return;
    result=0U;(void)GetExitCodeThread(g_console_thread,&result);
    CloseHandle(g_console_thread);g_console_thread=NULL;
    if(result!=0U) {
        g_console=g_console_job;ZeroMemory(&g_console_job,sizeof(g_console_job));
        g_text_mode=1U;ShowWindow(window,SW_HIDE);
        if(g_console.window_usable) {
            ShowWindow(g_console.window,SW_SHOW);SetForegroundWindow(g_console.window);
        }
    }
    g_switching=0U;g_text_failed=0U;
    mysmb_win32_build_frame();
    if(!g_text_mode)InvalidateRect(window,NULL,FALSE);
}

/* Only the root chooses a presenter; device code receives neutral cells.
 * Internal focus transfer never enters the game's auto-pause input path. */
static void mysmb_win32_switch_presenter(HWND window,int activate)
{
    g_switching=1U;
    mysmb_win32_transfer_keys();
    if(!g_text_mode) {
        if(g_console.opened && !mygames_win32_text_console_resume(&g_console))
            mygames_win32_text_console_close(&g_console);
        if((g_console.opened ||
            mygames_win32_text_console_open_profile(&g_console,window,25U,"MySMB"))) {
            g_text_mode=1U;
            if(activate) {
                ShowWindow(window,SW_HIDE);
                if(g_console.window_usable) {
                    ShowWindow(g_console.window,SW_SHOW);
                    SetForegroundWindow(g_console.window);
                }
            }
        }
    } else {
        g_text_mode=0U;
        /* A borrowed parent console survives Tab for an identity-preserving
         * return. A console allocated by this graphical session must close. */
        if(g_text_failed || !g_console.borrowed ||
            !mygames_win32_text_console_suspend(&g_console))
            mygames_win32_text_console_close(&g_console);
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
static int mysmb_win32_snapshot_capture(void)
{
    struct mysmb_io_snapshot *staged;
    if (!g_snapshot_ready || !mysmb_game_snapshot_available(&g_game,&g_frame)) return 0;
    staged=&g_snapshot_store.staging;
    return mysmb_game_snapshot_capture(&g_game,staged,g_snapshot_fingerprint) &&
        mysmb_win32_audio_capture(&g_audio_output.renderer,
            staged->payload+MYSMB_SNAPSHOT_CORE_BYTES);
}
static int mysmb_win32_snapshot_request(HWND window)
{
    const struct mysmb_io_snapshot *candidate;
    struct mysmb_win32_audio_renderer audio;
    mygames_kvm_u8 requests;
    requests=g_snapshot_requests;g_snapshot_requests=0U;
    if (!g_snapshot_ready || requests==0U || !mysmb_win32_presenter_focused(window))
        return 0;
    if ((requests&MYSMB_IO_REQUEST_LOAD)!=0U) {
        candidate=mysmb_snapshot_load(&g_snapshot_store,g_snapshot_fingerprint);
        QueryPerformanceCounter(&g_last_tick);
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
        mysmb_snapshot_keys_reset(&g_snapshot_keys);
        mysmb_win32_release_keys();
        mysmb_win32_focus_pause_initialize(&g_focus_pause);
        mysmb_win32_focus_pause_gained(&g_focus_pause);
        mysmb_game_snapshot_resume_frame(&g_game,&g_frame);
        g_game_started=1U;
        QueryPerformanceCounter(&g_last_tick);
        mysmb_win32_build_frame();mysmb_win32_update_title(window);
        InvalidateRect(window,NULL,FALSE);
        return 1;
    }
    if ((requests&MYSMB_IO_REQUEST_SAVE)!=0U) {
        candidate=0;
        if(mysmb_win32_snapshot_capture())candidate=&g_snapshot_store.staging;
        (void)mysmb_snapshot_save(&g_snapshot_store,candidate);
        QueryPerformanceCounter(&g_last_tick);
        return 1;
    }
    return 0;
}

static void mysmb_win32_power_on(void)
{
    mysmb_ppu_frame_workspace_bind(&g_ppu_workspace,g_chr_decoded);
    mysmb_ppu_frame_background_byte_bind(&g_ppu_workspace,g_background_slots,
        MYSMB_PPU_BACKGROUND_BYTES,g_background_second,MYSMB_PPU_BACKGROUND_SECOND_BYTES);
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
/* This product check exercises the root's close/message and pixel routes.
 * Physical-event and Mario-mapping assertions have dedicated owner tests. */
static int mysmb_win32_run_self_test(void)
{
    WNDCLASS window_class;
    HWND window;
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
static void mysmb_win32_paint(HWND window)
{
    (void)mygames_win32_window_paint(window,g_pixels,
        MYSMB_SCREEN_WIDTH,MYSMB_SCREEN_HEIGHT,MYSMB_SCREEN_WIDTH*MYSMB_SCREEN_HEIGHT);
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
    struct mygames_kvm_input_event event;

    mysmb_win32_console_complete(window);
    if(g_text_mode && g_text_failed && !g_console_thread)
        mysmb_win32_switch_presenter(window,1);
    for(events=0U;events<64U && g_text_mode &&
        mygames_win32_text_console_event(&g_console,&g_keyboard,&event);++events)
        mysmb_win32_physical_event(&g_console,window,&event);
    if(g_toggle_request && !g_console_thread) {
        g_toggle_request=0U;
        if(g_text_mode || g_console.opened || mygames_win32_parent_console_available())
            mysmb_win32_switch_presenter(window,1);
        else mygames_win32_console_begin(window);
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

    if (!g_switching && g_focus_pause.focused != 0U && !mysmb_win32_presenter_focused(window)) {
        mysmb_win32_release_keys();
        mysmb_win32_focus_pause_lost(&g_focus_pause, g_game_started, &g_game);
    }
    if(mysmb_win32_presenter_focused(window))
        mysmb_win32_focus_pause_gained(&g_focus_pause);
    physical_buttons = 0U;
    if (g_focus_pause.focused != 0U)
        physical_buttons = g_mapped_buttons;
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
        ++steps;
        elapsed = now.QuadPart - g_last_tick.QuadPart;
    } while (elapsed >= frame_period && steps < 4U);
    /* Logical ticks and audio above always run.  If their bounded catch-up
     * batch still missed this display deadline, publishing an already stale
     * frame only delays the next useful state. */
    QueryPerformanceCounter(&now);
    if(now.QuadPart-g_last_tick.QuadPart>=frame_period)return;
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
    LRESULT result;
    decoded.buttons=0U;decoded.buttons2=0U;
    decoded.requests=mysmb_win32_requests_from_message(message,w_param);
    if (decoded.requests!=0U) {
        mysmb_io_control_input(&g_control,&decoded);
        return 0;
    }
    /* The retained hidden GUI is not the active input device in text mode. */
    if(g_text_mode && (message==WM_KILLFOCUS || message==WM_SETFOCUS || message==WM_ACTIVATEAPP)) {
        g_window_focused=(mygames_kvm_u8)(message==WM_SETFOCUS ||
            (message==WM_ACTIVATEAPP && w_param && GetFocus()==window));
        return 0;
    }
    if(mygames_win32_window_event(window,message,w_param,l_param,&g_window_input,
        &g_keyboard,&g_window_geometry,mysmb_win32_physical_event,0,&result))return result;
    if (message == WM_PAINT) {
        mysmb_win32_paint(window);
        return 0;
    }
    if (message == WM_DESTROY) {
        mysmb_win32_audio_close(&g_audio_output);
        mygames_win32_text_console_close(&g_console);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(window, message, w_param, l_param);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previous, LPSTR command, int show)
{
    HWND window;
    MSG message;
    int start_text;
    unsigned int messages;

    (void)previous;
    mysmb_io_control_initialize(&g_control);
    if (mysmb_win32_argument_is_self_test(command) != 0) {
#ifdef MYSMB_LOCAL_TITLE
        return mysmb_win32_run_self_test();
#else
        return 2;
#endif
    }
    mygames_win32_window_enable_dpi();
    start_text=mygames_win32_parent_console_available();
    if(!start_text)(void)FreeConsole();
    QueryPerformanceFrequency(&g_frequency);
    QueryPerformanceCounter(&g_last_tick);
    g_game_started = 0U;
    mysmb_win32_focus_pause_initialize(&g_focus_pause);
    mygames_win32_input_initialize(&g_keyboard);
    mysmb_app_input_mapping_initialize(&g_input_mapping);
    g_mapped_buttons=0U;
    mygames_win32_window_geometry_initialize(&g_window_geometry,16,15,16,32);
    mysmb_win32_power_on();
    mysmb_win32_snapshot_initialize();
    window=mygames_win32_window_create(instance,MYSMB_CLASS_NAME,"MySMB",
        mysmb_win32_window_proc,&g_window_geometry);
    if(!window)return 1;
    if(start_text)mysmb_win32_switch_presenter(window,0);
    if(g_text_mode) {
        if(g_console.window_usable) {
            ShowWindow(g_console.window,show);
            SetForegroundWindow(g_console.window);
        }
    } else {
        ShowWindow(window, show);
        UpdateWindow(window);
    }
    g_audio_available = mysmb_win32_audio_open(&g_audio_output) != 0 ? 1U : 0U;
    g_title_paused = 2U;
    mysmb_win32_update_title(window);
    mygames_win32_frame_wait_open(&g_frame_wait);
    QueryPerformanceCounter(&g_last_tick);

    for (;;) {
        for(messages=0U;messages<64U &&
            PeekMessage(&message, NULL, 0U, 0U, PM_REMOVE)!=0;++messages) {
            if (message.message == WM_QUIT) {
                mygames_win32_frame_wait_close(&g_frame_wait);
                return 0;
            }
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        if (g_control.exit_requested!=0U) mysmb_win32_finish_exit(window);
        else mysmb_win32_step(window);
        mygames_win32_frame_wait_until(&g_frame_wait,
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
