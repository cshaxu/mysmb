#include <windows.h>

#include "game/game.h"

#define MYSMB_CLASS_NAME "MySMBWindow"
#define MYSMB_SCALE 2

static struct mysmb_game g_game;
static struct mysmb_frame g_frame;
static LARGE_INTEGER g_frequency;
static LARGE_INTEGER g_last_tick;

static void mysmb_win32_paint(HWND window)
{
    PAINTSTRUCT paint;
    HDC dc;
    HBRUSH sky;
    HBRUSH ground;
    HBRUSH actor;
    RECT rect;

    dc = BeginPaint(window, &paint);
    sky = CreateSolidBrush(RGB(92, 148, 252));
    ground = CreateSolidBrush(RGB(0, 168, 0));
    actor = CreateSolidBrush(g_frame.start_pressed != 0U ? RGB(255, 216, 0) : RGB(220, 48, 32));

    rect.left = 0;
    rect.top = 0;
    rect.right = MYSMB_SCREEN_WIDTH * MYSMB_SCALE;
    rect.bottom = MYSMB_SCREEN_HEIGHT * MYSMB_SCALE;
    FillRect(dc, &rect, sky);

    rect.top = 200 * MYSMB_SCALE;
    FillRect(dc, &rect, ground);

    rect.left = (int)g_frame.sprite0_x * MYSMB_SCALE;
    rect.top = (int)g_frame.sprite0_y * MYSMB_SCALE;
    rect.right = rect.left + (16 * MYSMB_SCALE);
    rect.bottom = rect.top + (16 * MYSMB_SCALE);
    FillRect(dc, &rect, actor);

    DeleteObject(actor);
    DeleteObject(ground);
    DeleteObject(sky);
    EndPaint(window, &paint);
}

static void mysmb_win32_step(HWND window)
{
    LARGE_INTEGER now;
    LONGLONG elapsed;
    LONGLONG frame_period;
    struct mysmb_input input;

    QueryPerformanceCounter(&now);
    elapsed = now.QuadPart - g_last_tick.QuadPart;
    frame_period = g_frequency.QuadPart / 60;
    if (elapsed < frame_period) {
        return;
    }

    g_last_tick.QuadPart += frame_period;
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0) {
        input.buttons = MYSMB_BUTTON_LEFT;
    }
    else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0) {
        input.buttons = MYSMB_BUTTON_RIGHT;
    }
    else {
        input.buttons = 0U;
    }
    if ((GetAsyncKeyState(VK_RETURN) & 0x8000) != 0) {
        input.buttons = (mysmb_u8)(input.buttons | MYSMB_BUTTON_START);
    }
    mysmb_game_tick(&g_game, &input, &g_frame);
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
    (void)command;
    ZeroMemory(&window_class, sizeof(window_class));
    window_class.lpfnWndProc = mysmb_win32_window_proc;
    window_class.hInstance = instance;
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.lpszClassName = MYSMB_CLASS_NAME;
    if (RegisterClass(&window_class) == 0) {
        return 1;
    }

    mysmb_game_initialize(&g_game);
    ZeroMemory(&g_frame, sizeof(g_frame));
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
