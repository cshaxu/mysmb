#include <windows.h>

#include "game/game.h"
#ifndef MYSMB_LOCAL_TITLE
#include "game/render.h"
#endif

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
#ifndef MYSMB_LOCAL_TITLE
static struct mysmb_render_frame g_render_frame;
#endif
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
    if ((GetAsyncKeyState('J') & 0x8000) != 0 ||
        (GetAsyncKeyState('Z') & 0x8000) != 0) keys |= MYSMB_WIN32_KEY_B;
    if ((GetAsyncKeyState('K') & 0x8000) != 0 ||
        (GetAsyncKeyState('X') & 0x8000) != 0) keys |= MYSMB_WIN32_KEY_A;
    return keys;
}

static DWORD mysmb_win32_dib_color(COLORREF color)
{
    return ((DWORD)(color & 0x000000ffUL) << 16U) |
           (DWORD)(color & 0x0000ff00UL) |
           ((DWORD)(color & 0x00ff0000UL) >> 16U);
}

static void mysmb_win32_plot(unsigned int x, unsigned int y, COLORREF color)
{
    if (x >= MYSMB_SCREEN_WIDTH || y >= MYSMB_SCREEN_HEIGHT) return;
    g_pixels[y * MYSMB_SCREEN_WIDTH + x] = mysmb_win32_dib_color(color);
}

static void mysmb_win32_fill_rect(unsigned int x, unsigned int y,
                                   unsigned int width, unsigned int height,
                                   COLORREF color)
{
    unsigned int row;
    unsigned int column;

    for (row = y; row < y + height && row < MYSMB_SCREEN_HEIGHT; ++row) {
        for (column = x; column < x + width && column < MYSMB_SCREEN_WIDTH;
             ++column) {
            mysmb_win32_plot(column, row, color);
        }
    }
}

#ifdef MYSMB_LOCAL_TITLE
static void mysmb_win32_draw_background(void);
static void mysmb_win32_draw_oam(void);
#endif

#ifndef MYSMB_LOCAL_TITLE
static COLORREF mysmb_win32_tile_color(mysmb_u8 tile)
{
    if (tile == 0x24U) return RGB(92, 148, 252);
    if (tile >= 0x80U) return RGB(0, 168, 0);
    if (tile >= 0x50U) return RGB(180, 92, 24);
    if (tile >= 0x30U) return RGB(252, 188, 60);
    return RGB(92, 148, 252);
}

static COLORREF mysmb_win32_actor_color(mysmb_u8 identity)
{
    if (identity == 0U) return RGB(220, 48, 32);
    if ((identity & 1U) != 0U) return RGB(252, 188, 60);
    return RGB(112, 48, 24);
}
#endif

static void mysmb_win32_draw_gameplay(void)
{
#ifdef MYSMB_LOCAL_TITLE
    /* The ROM-enabled build consumes CHR-backed name-table pixels instead of
     * the diagnostic color buckets below.  Sprite/OAM composition follows in
     * the next renderer slice. */
    mysmb_win32_draw_background();
    mysmb_win32_draw_oam();
#else
    unsigned int index;
    unsigned int tile_index;
    struct mysmb_render_command *command;

    for (index = 0U; index < g_render_frame.command_count; ++index) {
        command = &g_render_frame.commands[index];
        if (command->kind == MYSMB_RENDER_COMMAND_TILE_ROW) {
            for (tile_index = 0U; tile_index < command->length; ++tile_index) {
                mysmb_win32_fill_rect((command->x + tile_index) * 8U,
                    command->y * 8U, 8U, 8U,
                    mysmb_win32_tile_color(g_render_frame.tile_data[
                        command->data_offset + tile_index]));
            }
        } else if (command->kind == MYSMB_RENDER_COMMAND_ACTOR) {
            mysmb_win32_fill_rect(command->x, command->y, command->length,
                command->length, mysmb_win32_actor_color(command->identity));
        }
    }
#endif
}
#ifdef MYSMB_LOCAL_TITLE
static COLORREF mysmb_win32_nes_color(mysmb_u8 index)
{
    /* The 2C02 master palette encoded by SMB1's $3f00-$3f1f entries. */
    static const COLORREF colors[64] = {
        RGB(84,84,84), RGB(0,30,116), RGB(8,16,144), RGB(48,0,136), RGB(68,0,100), RGB(92,0,48), RGB(84,4,0), RGB(60,24,0), RGB(32,42,0), RGB(8,58,0), RGB(0,64,0), RGB(0,60,0), RGB(0,50,60), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0),
        RGB(152,150,152), RGB(8,76,196), RGB(48,50,236), RGB(92,30,228), RGB(136,20,176), RGB(160,20,100), RGB(152,34,32), RGB(120,60,0), RGB(84,90,0), RGB(40,114,0), RGB(8,124,0), RGB(0,118,40), RGB(0,102,120), RGB(0,0,0), RGB(0,0,0), RGB(0,0,0),
        RGB(236,238,236), RGB(76,154,236), RGB(120,124,236), RGB(176,98,236), RGB(228,84,236), RGB(236,88,180), RGB(236,106,100), RGB(212,136,32), RGB(160,170,0), RGB(116,196,0), RGB(76,208,32), RGB(56,204,108), RGB(56,180,204), RGB(60,60,60), RGB(0,0,0), RGB(0,0,0),
        RGB(236,238,236), RGB(168,204,236), RGB(188,188,236), RGB(212,178,236), RGB(236,174,236), RGB(236,174,212), RGB(236,180,176), RGB(228,196,144), RGB(204,210,120), RGB(180,222,120), RGB(168,226,144), RGB(152,226,180), RGB(160,214,228), RGB(160,162,160), RGB(0,0,0), RGB(0,0,0)
    };

    return colors[index & 0x3fU];
}

static COLORREF mysmb_win32_background_color(unsigned char palette,
                                              unsigned char color)
{
    return mysmb_win32_nes_color(g_game.palette[color == 0U ? 0U : (palette << 2U) + color]);
}

static COLORREF mysmb_win32_sprite_color(unsigned char palette,
                                          unsigned char color)
{
    return mysmb_win32_nes_color(g_game.palette[0x10U + (palette << 2U) + color]);
}
static unsigned char mysmb_win32_background_pixel(unsigned int x, unsigned int y)
{
    unsigned int source_x;
    unsigned int source_y;
    unsigned int row;
    unsigned int column;
    unsigned int table;
    unsigned int tile;
    unsigned char low;
    unsigned char high;
    unsigned int pixel_x;
    unsigned int pixel_y;
    unsigned int pattern_base;

    source_x = (x + g_game.visible_scroll_x) & 0x01ffU;
    source_y = (y + g_game.visible_scroll_y) % 480U;
    table = (unsigned int)(g_game.visible_ppu_name_table & 3U);
    if (source_x >= 256U) table ^= 1U;
    if (source_y >= 240U) table ^= 2U;
    row = (source_y % 240U) / 8U;
    column = (source_x & 0xffU) / 8U;
    /* SMB1 uses vertical mirroring: logical tables 0/2 and 1/3 share CIRAM. */
    table &= 1U;
    tile = g_game.name_table[table][row * 32U + column];
    pixel_y = source_y & 7U;
    pixel_x = source_x & 7U;
    pattern_base = (g_game.visible_ppu_control_0 & 0x10U) != 0U ? 0x1000U : 0U;
    low = mysmb_local_chr[pattern_base + tile * 16U + pixel_y];
    high = mysmb_local_chr[pattern_base + tile * 16U + pixel_y + 8U];
    return (unsigned char)(((low >> (7U - pixel_x)) & 1U) |
                           (((high >> (7U - pixel_x)) & 1U) << 1U));
}

static void mysmb_win32_draw_background(void)
{
    unsigned int y;
    unsigned int x;
    unsigned int source_x;
    unsigned int source_y;
    unsigned int row;
    unsigned int column;
    unsigned int table;
    unsigned int attribute;
    unsigned char palette;
    unsigned char color;

    for (y = 0U; y < MYSMB_SCREEN_HEIGHT; ++y) {
        for (x = 0U; x < MYSMB_SCREEN_WIDTH; ++x) {
            source_x = (x + g_game.visible_scroll_x) & 0x01ffU;
            source_y = (y + g_game.visible_scroll_y) % 480U;
            table = (unsigned int)(g_game.visible_ppu_name_table & 3U);
            if (source_x >= 256U) table ^= 1U;
            if (source_y >= 240U) table ^= 2U;
            row = (source_y % 240U) / 8U;
            column = (source_x & 0xffU) / 8U;
            table &= 1U;
            attribute = g_game.name_table[table][0x03c0U + (row / 4U) * 8U + column / 4U];
            palette = (unsigned char)((attribute >> (((row & 2U) << 1U) + (column & 2U))) & 3U);
            color = mysmb_win32_background_pixel(x, y);
            mysmb_win32_plot(x, y, mysmb_win32_background_color(palette, color));
        }
    }
}
static void mysmb_win32_draw_oam(void)
{
    unsigned int sprite;
    unsigned int pixel_y;
    unsigned int pixel_x;
    unsigned int x;
    unsigned int y;
    unsigned int tile;
    unsigned int attributes;
    unsigned int bit;
    unsigned char low;
    unsigned char high;
    unsigned char color;

    for (sprite = 64U; sprite != 0U;) {
        --sprite;
        y = g_game.visible_oam[sprite * 4U] + 1U;
        tile = g_game.visible_oam[sprite * 4U + 1U];
        attributes = g_game.visible_oam[sprite * 4U + 2U];
        x = g_game.visible_oam[sprite * 4U + 3U];
        if (y >= MYSMB_SCREEN_HEIGHT) continue;
        for (pixel_y = 0U; pixel_y < 8U && y + pixel_y < MYSMB_SCREEN_HEIGHT; ++pixel_y) {
            low = mysmb_local_chr[((g_game.visible_ppu_control_0 & 0x08U) != 0U ? 0x1000U : 0U) + tile * 16U +
                ((attributes & 0x80U) != 0U ? 7U - pixel_y : pixel_y)];
            high = mysmb_local_chr[((g_game.visible_ppu_control_0 & 0x08U) != 0U ? 0x1000U : 0U) + tile * 16U + 8U +
                ((attributes & 0x80U) != 0U ? 7U - pixel_y : pixel_y)];
            for (pixel_x = 0U; pixel_x < 8U && x + pixel_x < MYSMB_SCREEN_WIDTH; ++pixel_x) {
                bit = (attributes & 0x40U) != 0U ? pixel_x : 7U - pixel_x;
                color = (unsigned char)(((low >> bit) & 1U) | (((high >> bit) & 1U) << 1U));
                if (color != 0U && ((attributes & 0x20U) == 0U ||
                    mysmb_win32_background_pixel(x + pixel_x, y + pixel_y) == 0U)) {
                    mysmb_win32_plot(x + pixel_x, y + pixel_y,
                        mysmb_win32_sprite_color((unsigned char)(attributes & 3U), color));
                }
            }
        }
    }
}
#endif

static void mysmb_win32_build_frame(void)
{
    ZeroMemory(g_pixels, sizeof(g_pixels));
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
/* Runs the composition root without a visible window, exercising embedded-ROM
 * startup, title input, GameCore entry, and software frame generation. */
static int mysmb_win32_run_self_test(void)
{
    struct mysmb_input input;
    unsigned int index;

    mysmb_game_initialize(&g_game);
    mysmb_game_bind_area_source(&g_game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_title_source(&g_game, mysmb_local_title_data,
                                 MYSMB_LOCAL_TITLE_DATA_SIZE,
                                 mysmb_local_title_icon_data,
                                 MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
    if (mysmb_game_begin_title_bootstrap(&g_game) == 0U) return 10;
    ZeroMemory(&g_frame, sizeof(g_frame));
    for (index = 0U; index < 280U; ++index) {
        input.buttons = 0U;
        if (index == 40U) input.buttons = MYSMB_BUTTON_START;
        else if (index > 41U) input.buttons = MYSMB_BUTTON_RIGHT;
        mysmb_game_tick(&g_game, &input, &g_frame);
    }
    if (g_game.ram[0x0770U] != 1U) return 11;
    if (g_game.ram[0x0772U] != 3U) return 12;
    if ((g_game.visible_ppu_mask & 0x18U) != 0x18U) return 13;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_LEFT) != MYSMB_BUTTON_LEFT) return 14;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_RIGHT) != MYSMB_BUTTON_RIGHT) return 15;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_DOWN) != MYSMB_BUTTON_DOWN) return 16;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_UP) != MYSMB_BUTTON_UP) return 17;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_START) != MYSMB_BUTTON_START) return 18;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_SELECT) != MYSMB_BUTTON_SELECT) return 19;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_B) != MYSMB_BUTTON_B) return 20;
    if (mysmb_win32_buttons_from_keys(MYSMB_WIN32_KEY_A) != MYSMB_BUTTON_A) return 21;
    mysmb_win32_build_frame();
    /* This intentionally avoids a desktop DC; presentation itself remains the
     * same single-DIB transfer used by mysmb_win32_paint. */
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
#ifndef MYSMB_LOCAL_TITLE
    mysmb_render_build(&g_game, &g_render_frame);
#endif
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
#ifndef MYSMB_LOCAL_TITLE
    mysmb_render_build(&g_game, &g_render_frame);
#endif
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
