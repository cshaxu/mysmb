#include <windows.h>

#include "game/game.h"
#include "game/ppu_frame.h"

#ifdef MYSMB_LOCAL_TITLE
#include "smb1_local_rom.h"
#include "smb1_local_title.h"
#endif

#define MYSMB_CLASS_NAME "MySMBWindow"
#define MYSMB_SCALE 2
#define MYSMB_WIN32_KEY_LEFT   0x0001U
#define MYSMB_WIN32_KEY_RIGHT  0x0002U
#define MYSMB_WIN32_KEY_DOWN   0x0004U
#define MYSMB_WIN32_KEY_UP     0x0008U
#define MYSMB_WIN32_KEY_START  0x0010U
#define MYSMB_WIN32_KEY_SELECT 0x0020U
#define MYSMB_WIN32_KEY_B      0x0040U
#define MYSMB_WIN32_KEY_A      0x0080U

static struct mysmb_game g_game;
static struct mysmb_frame g_frame;
static struct mysmb_ppu_frame g_ppu_frame;
static LARGE_INTEGER g_frequency;
static LARGE_INTEGER g_last_tick;
static BITMAPINFO g_bitmap_info;
static DWORD g_pixels[MYSMB_SCREEN_WIDTH * MYSMB_SCREEN_HEIGHT];
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
    unsigned int keys;

    keys = 0U;
    /* Virtual-key polling is layout-independent and is delivered by both a
     * console session and RDP.  Keep the cursor/Z/X bindings as secondary
     * compatibility keys; the documented controls are WASD, J/K, Enter and
     * either Shift key. */
    if ((GetAsyncKeyState('A') & 0x8000) != 0 ||
        (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0) keys |= MYSMB_WIN32_KEY_LEFT;
    if ((GetAsyncKeyState('D') & 0x8000) != 0 ||
        (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0) keys |= MYSMB_WIN32_KEY_RIGHT;
    if ((GetAsyncKeyState('S') & 0x8000) != 0 ||
        (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0) keys |= MYSMB_WIN32_KEY_DOWN;
    if ((GetAsyncKeyState('W') & 0x8000) != 0 ||
        (GetAsyncKeyState(VK_UP) & 0x8000) != 0) keys |= MYSMB_WIN32_KEY_UP;
    if ((GetAsyncKeyState(VK_RETURN) & 0x8000) != 0) keys |= MYSMB_WIN32_KEY_START;
    if ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) != 0 ||
        (GetAsyncKeyState(VK_RSHIFT) & 0x8000) != 0) keys |= MYSMB_WIN32_KEY_SELECT;
    if ((GetAsyncKeyState('J') & 0x8000) != 0) keys |= MYSMB_WIN32_KEY_A;
    if ((GetAsyncKeyState('K') & 0x8000) != 0) keys |= MYSMB_WIN32_KEY_B;
    return keys;
}

static DWORD mysmb_win32_dib_color(mysmb_u8 color)
{
    static const DWORD colors[64] = {
        0x545454UL,0x001e74UL,0x081090UL,0x300088UL,0x440064UL,0x5c0030UL,0x540400UL,0x3c1800UL,0x202a00UL,0x083a00UL,0x004000UL,0x003c00UL,0x00323cUL,0,0,0,
        0x989698UL,0x084cc4UL,0x3032ecUL,0x5c1ee4UL,0x8814b0UL,0xa01464UL,0x982220UL,0x783c00UL,0x545a00UL,0x287200UL,0x087c00UL,0x007628UL,0x006678UL,0,0,0,
        0xeceeeeUL,0x4c9aecUL,0x787cecUL,0xb062ecUL,0xe454ecUL,0xec58b4UL,0xec6a64UL,0xd48820UL,0xa0aa00UL,0x74c400UL,0x4cd020UL,0x38c06cUL,0x38b4ccUL,0x3c3c3cUL,0,0,
        0xeceeeeUL,0xa8ccecUL,0xbcbcecUL,0xd4b2ecUL,0xecaeecUL,0xecaed4UL,0xecb4b0UL,0xe4c690UL,0xccd278UL,0xb4de78UL,0xa8e290UL,0x98e2b4UL,0xa0d6e4UL,0xa0a2a0UL,0,0
    };
    /* Table values are already top-down 32-bit DIB BGR words. */
    return colors[color & 0x3fU];
}
static void mysmb_win32_draw_gameplay(void)
{
    unsigned int index;
    for(index=0U;index<MYSMB_SCREEN_WIDTH*MYSMB_SCREEN_HEIGHT;++index) g_pixels[index]=mysmb_win32_dib_color(g_ppu_frame.pixels[index]);
}
static void mysmb_win32_build_frame(void)
{
    mysmb_ppu_frame_build(&g_game, &g_ppu_frame);
    mysmb_win32_draw_gameplay();
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
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_LEFT) != MYSMB_BUTTON_LEFT) return 14;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_RIGHT) != MYSMB_BUTTON_RIGHT) return 15;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_DOWN) != MYSMB_BUTTON_DOWN) return 16;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_UP) != MYSMB_BUTTON_UP) return 17;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_START) != MYSMB_BUTTON_START) return 18;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_SELECT) != MYSMB_BUTTON_SELECT) return 19;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_B) != MYSMB_BUTTON_B) return 20;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_A) != MYSMB_BUTTON_A) return 21;
    return 0;
}
#endif
static void mysmb_win32_paint(HWND window)
{
    PAINTSTRUCT paint;
    HDC dc;

    dc = BeginPaint(window, &paint);
    StretchDIBits(dc, 0, 0, MYSMB_SCREEN_WIDTH * MYSMB_SCALE,
                  MYSMB_SCREEN_HEIGHT * MYSMB_SCALE, 0, 0,
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
    unsigned int steps;

    QueryPerformanceCounter(&now);
    elapsed = now.QuadPart - g_last_tick.QuadPart;
    frame_period = g_frequency.QuadPart / 60;
    if (elapsed < frame_period) return;

    input.buttons = mysmb_win32_buttons_from_keys(mysmb_win32_poll_keys());
    steps = 0U;
    do {
        g_last_tick.QuadPart += frame_period;
        mysmb_game_tick(&g_game, &input, &g_frame);
        ++steps;
        elapsed = now.QuadPart - g_last_tick.QuadPart;
    } while (elapsed >= frame_period && steps < 4U);
    /* Discard excess wall-clock debt after four logical frames.  This keeps
     * the message pump responsive instead of attempting an unbounded catch-up. */
    if (elapsed >= frame_period) g_last_tick = now;
    mysmb_win32_build_frame();
    InvalidateRect(window, NULL, FALSE);
}

static LRESULT CALLBACK mysmb_win32_window_proc(HWND window, UINT message,
                                                  WPARAM w_param, LPARAM l_param)
{
    (void)w_param;
    (void)l_param;
    if (message == WM_PAINT) {
        mysmb_win32_paint(window);
        return 0;
    }
    if (message == WM_DESTROY) {
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

    (void)previous;
    if (mysmb_win32_argument_is_self_test(command) != 0) {
#ifdef MYSMB_LOCAL_TITLE
        return mysmb_win32_run_self_test();
#else
        return 2;
#endif
    }
    ZeroMemory(&window_class, sizeof(window_class));
    window_class.lpfnWndProc = mysmb_win32_window_proc;
    window_class.hInstance = instance;
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.lpszClassName = MYSMB_CLASS_NAME;
    if (RegisterClass(&window_class) == 0) {
        return 1;
    }

    mysmb_game_initialize(&g_game);
#ifdef MYSMB_LOCAL_TITLE
    mysmb_game_bind_area_source(&g_game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_chr_source(&g_game, mysmb_local_chr, MYSMB_LOCAL_CHR_SIZE);
    mysmb_game_bind_title_source(&g_game, mysmb_local_title_data,
                                 MYSMB_LOCAL_TITLE_DATA_SIZE,
                                 mysmb_local_title_icon_data,
                                 MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
    if (mysmb_game_begin_title_bootstrap(&g_game) == 0U) {
        return 1;
    }
#endif
    ZeroMemory(&g_bitmap_info, sizeof(g_bitmap_info));
    g_bitmap_info.bmiHeader.biSize = sizeof(g_bitmap_info.bmiHeader);
    g_bitmap_info.bmiHeader.biWidth = MYSMB_SCREEN_WIDTH;
    g_bitmap_info.bmiHeader.biHeight = -(LONG)MYSMB_SCREEN_HEIGHT;
    g_bitmap_info.bmiHeader.biPlanes = 1U;
    g_bitmap_info.bmiHeader.biBitCount = 32U;
    g_bitmap_info.bmiHeader.biCompression = BI_RGB;
    ZeroMemory(&g_frame, sizeof(g_frame));
    mysmb_win32_build_frame();
    QueryPerformanceFrequency(&g_frequency);
    QueryPerformanceCounter(&g_last_tick);
    window = CreateWindow(MYSMB_CLASS_NAME, "MySMB", WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          MYSMB_SCREEN_WIDTH * MYSMB_SCALE + 16,
                          MYSMB_SCREEN_HEIGHT * MYSMB_SCALE + 39,
                          NULL, NULL, instance, NULL);
    if (window == NULL) {
        return 1;
    }
    ShowWindow(window, show);
    UpdateWindow(window);

    for (;;) {
        while (PeekMessage(&message, NULL, 0U, 0U, PM_REMOVE) != 0) {
            if (message.message == WM_QUIT) {
                return 0;
            }
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        mysmb_win32_step(window);
        Sleep(1U);
    }
}
