#include <windows.h>

#include "game/game.h"
#include "game/render.h"

#ifdef MYSMB_LOCAL_TITLE
#include "smb1_local_rom.h"
#include "smb1_local_title.h"
#endif

#define MYSMB_CLASS_NAME "MySMBWindow"
#define MYSMB_SCALE 2

static struct mysmb_game g_game;
static struct mysmb_frame g_frame;
static struct mysmb_render_frame g_render_frame;
static LARGE_INTEGER g_frequency;
static LARGE_INTEGER g_last_tick;

#ifdef MYSMB_LOCAL_TITLE
static void mysmb_win32_draw_background(HDC dc);
static void mysmb_win32_plot(HDC dc, unsigned int x, unsigned int y,
                             COLORREF color)
{
    SetPixel(dc, (int)(x * MYSMB_SCALE), (int)(y * MYSMB_SCALE), color);
    SetPixel(dc, (int)(x * MYSMB_SCALE + 1U), (int)(y * MYSMB_SCALE), color);
    SetPixel(dc, (int)(x * MYSMB_SCALE), (int)(y * MYSMB_SCALE + 1U), color);
    SetPixel(dc, (int)(x * MYSMB_SCALE + 1U), (int)(y * MYSMB_SCALE + 1U), color);
}
static void mysmb_win32_draw_oam(HDC dc);
#endif

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

static void mysmb_win32_draw_gameplay(HDC dc)
{
#ifdef MYSMB_LOCAL_TITLE
    /* The ROM-enabled build consumes CHR-backed name-table pixels instead of
     * the diagnostic color buckets below.  Sprite/OAM composition follows in
     * the next renderer slice. */
    mysmb_win32_draw_background(dc);
    mysmb_win32_draw_oam(dc);
#else
    unsigned int index;
    unsigned int tile_index;
    struct mysmb_render_command *command;
    HBRUSH brush;
    RECT rect;

    for (index = 0U; index < g_render_frame.command_count; ++index) {
        command = &g_render_frame.commands[index];
        if (command->kind == MYSMB_RENDER_COMMAND_TILE_ROW) {
            for (tile_index = 0U; tile_index < command->length; ++tile_index) {
                brush = CreateSolidBrush(mysmb_win32_tile_color(
                    g_render_frame.tile_data[command->data_offset + tile_index]));
                rect.left = (int)((command->x + tile_index) * 8U * MYSMB_SCALE);
                rect.top = (int)(command->y * 8U * MYSMB_SCALE);
                rect.right = rect.left + 8 * MYSMB_SCALE;
                rect.bottom = rect.top + 8 * MYSMB_SCALE;
                FillRect(dc, &rect, brush);
                DeleteObject(brush);
            }
        } else if (command->kind == MYSMB_RENDER_COMMAND_ACTOR) {
            brush = CreateSolidBrush(mysmb_win32_actor_color(command->identity));
            rect.left = (int)command->x * MYSMB_SCALE;
            rect.top = (int)command->y * MYSMB_SCALE;
            rect.right = rect.left + (command->length * MYSMB_SCALE);
            rect.bottom = rect.top + (command->length * MYSMB_SCALE);
            FillRect(dc, &rect, brush);
            DeleteObject(brush);
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
    return mysmb_win32_nes_color(g_game.palette[(palette << 2U) + color]);
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

static void mysmb_win32_draw_background(HDC dc)
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
            mysmb_win32_plot(dc, x, y, mysmb_win32_background_color(palette, color));
        }
    }
}
static void mysmb_win32_draw_oam(HDC dc)
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

    for (sprite = 64U; sprite != 0U; --sprite) {
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
                    mysmb_win32_plot(dc, x + pixel_x, y + pixel_y,
                        mysmb_win32_sprite_color((unsigned char)(attributes & 3U), color));
                }
            }
        }
    }
}
#endif

static void mysmb_win32_paint(HWND window)
{
    PAINTSTRUCT paint;
    HDC dc;

    dc = BeginPaint(window, &paint);
#ifdef MYSMB_LOCAL_TITLE
    mysmb_win32_draw_background(dc);
    mysmb_win32_draw_oam(dc);
    EndPaint(window, &paint);
    return;
#endif
    mysmb_win32_draw_gameplay(dc);
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
    input.buttons = 0U;
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0) {
        input.buttons = (mysmb_u8)(input.buttons | MYSMB_BUTTON_LEFT);
    }
    if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0) {
        input.buttons = (mysmb_u8)(input.buttons | MYSMB_BUTTON_RIGHT);
    }
    if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0) {
        input.buttons = (mysmb_u8)(input.buttons | MYSMB_BUTTON_DOWN);
    }
    if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0) {
        input.buttons = (mysmb_u8)(input.buttons | MYSMB_BUTTON_UP);
    }
    if ((GetAsyncKeyState(VK_RETURN) & 0x8000) != 0) {
        input.buttons = (mysmb_u8)(input.buttons | MYSMB_BUTTON_START);
    }
    if ((GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0) {
        input.buttons = (mysmb_u8)(input.buttons | MYSMB_BUTTON_SELECT);
    }
    if ((GetAsyncKeyState('Z') & 0x8000) != 0) {
        input.buttons = (mysmb_u8)(input.buttons | MYSMB_BUTTON_A);
    }
    if ((GetAsyncKeyState('X') & 0x8000) != 0) {
        input.buttons = (mysmb_u8)(input.buttons | MYSMB_BUTTON_B);
    }
    mysmb_game_tick(&g_game, &input, &g_frame);
    mysmb_render_build(&g_game, &g_render_frame);
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
    ZeroMemory(&g_frame, sizeof(g_frame));
    mysmb_render_build(&g_game, &g_render_frame);
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
