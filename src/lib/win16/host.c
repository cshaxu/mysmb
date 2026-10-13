#include <windows.h>
#include <string.h>
#include "win16/host.h"
#include "win16/dib.h"
#include "kvm/color.h"
#include "kvm/windows_key.h"

struct win16_bitmap { BITMAPINFOHEADER header; RGBQUAD colors[256]; };
struct win16_palette { WORD version,count; PALETTEENTRY entries[256]; };
static struct win16_bitmap bitmap;
static struct win16_palette palette_description;
static HPALETTE palette;
static const struct mygames_win16_application *app;
static HGLOBAL storage;
static unsigned char FAR *pixels;
static unsigned char keys[MYGAMES_KVM_PHYSICAL_KEY_COUNT];
static int ready,closing;
static unsigned short output_bits,row_bytes,storage_bytes;
static unsigned char reduced_colors[256];

static int compose(void)
{
    struct mygames_kvm_video_band band;
    unsigned short first;
    for(first=0U;first<app->height;first=(unsigned short)(first+band.rows)) {
        memset(&band,0,sizeof(band));
        band.first=first;band.rows=(unsigned short)(app->height-first);
        if(band.rows>8U)band.rows=8U;
        if(!app->graphics(app->context,&band) || !band.pixels ||
            band.first!=first || !band.rows || band.rows>8U || band.width!=app->width)return 0;
        if(!mygames_win16_dib_band(pixels,storage_bytes,output_bits,&band,
            reduced_colors,app->height,app->palette_count))return 0;
    }
    return 1;
}

static void service(HWND window)
{
    struct mygames_win16_update update;
    if(closing)return;
    KillTimer(window,1);
    if(app->exit_requested(app->context)){closing=1;DestroyWindow(window);return;}
    memset(&update,0,sizeof(update));
    app->update(app->context,GetTickCount(),&update);
    if(app->exit_requested(app->context)){closing=1;DestroyWindow(window);return;}
    if(update.dirty) {
        ready=compose();InvalidateRect(window,0,FALSE);
        if(ready)UpdateWindow(window);
    }
    if(update.wake_ms && !SetTimer(window,1,update.wake_ms,0)) {
        /* A requested wake cannot be silently lost. */
        closing=1;DestroyWindow(window);PostQuitMessage(5);
    }
}

static void key_event(WPARAM key,LPARAM detail,int down)
{
    struct mygames_kvm_input_event event;
    unsigned short scan=(unsigned short)((detail>>16)&0xffL);
    unsigned short code=mygames_kvm_windows_key(key,scan);
    if(!code)return;
    memset(&event,0,sizeof(event));
    event.kind=MYGAMES_KVM_INPUT_KEY;event.down=(unsigned char)down;
    event.repeat=(unsigned char)(down && keys[code]);
    event.physical_code=code;event.native_scan=scan;
    keys[code]=(unsigned char)down;
    app->input(app->context,&event);
}

LRESULT FAR PASCAL __export MygamesWin16WndProc(HWND window,UINT message,
    WPARAM word,LPARAM detail)
{
    PAINTSTRUCT paint;
    RECT rect;
    HDC dc;
    HPALETTE old_palette;
    struct mygames_kvm_input_event event;
    switch(message) {
    case WM_QUERYNEWPALETTE:
        if(!palette)return 0;
        dc=GetDC(window);old_palette=SelectPalette(dc,palette,FALSE);
        word=RealizePalette(dc);
        if(old_palette)SelectPalette(dc,old_palette,TRUE);
        ReleaseDC(window,dc);
        if(word)InvalidateRect(window,0,FALSE);
        return word!=0;
    case WM_PALETTECHANGED:
        if((HWND)word!=window && palette)InvalidateRect(window,0,FALSE);
        return 0;
    case WM_KEYDOWN: key_event(word,detail,1);service(window);return 0;
    case WM_KEYUP: key_event(word,detail,0);service(window);return 0;
    case WM_SETFOCUS: case WM_KILLFOCUS:
        memset(keys,0,sizeof(keys));memset(&event,0,sizeof(event));
        event.kind=MYGAMES_KVM_INPUT_FOCUS;
        event.down=(unsigned char)(message==WM_SETFOCUS);
        app->input(app->context,&event);service(window);return 0;
    case WM_TIMER: service(window);return 0;
    case WM_PAINT:
        dc=BeginPaint(window,&paint);GetClientRect(window,&rect);
        old_palette=0;
        if(palette){old_palette=SelectPalette(dc,palette,FALSE);RealizePalette(dc);}
        SetStretchBltMode(dc,COLORONCOLOR);
        if(ready && rect.right>0 && rect.bottom>0)
            StretchDIBits(dc,0,0,rect.right,rect.bottom,0,0,app->width,app->height,
                pixels,(BITMAPINFO FAR *)&bitmap,DIB_RGB_COLORS,SRCCOPY);
        if(old_palette)SelectPalette(dc,old_palette,TRUE);
        EndPaint(window,&paint);return 0;
    case WM_DESTROY: closing=1;KillTimer(window,1);PostQuitMessage(0);return 0;
    }
    return DefWindowProc(window,message,word,detail);
}

int mygames_win16_run(HINSTANCE instance,HINSTANCE previous,int show,
    const struct mygames_win16_application *application)
{
    WNDCLASS cls;
    HWND window;
    MSG message;
    RECT rect;
    unsigned short i;
    unsigned long rgb,bytes;
    HDC screen;
    if(!application || !application->input || !application->update ||
        !application->graphics || !application->exit_requested ||
        !(application->available_views&MYGAMES_WIN16_VIEW_GRAPHICS))return 1;
    if(!application->palette || !application->palette_count ||
        application->palette_count>256U || !application->width || !application->height ||
        application->width>32767U || application->height>32767U)return 1;
    app=application;ready=closing=0;
    memset(keys,0,sizeof(keys));memset(&bitmap,0,sizeof(bitmap));
    bytes=(((unsigned long)app->width+3UL)/4UL)*4UL*app->height;
    if(bytes>65535UL)return 2;
    storage_bytes=(unsigned short)bytes;
    storage=GlobalAlloc(GMEM_MOVEABLE,bytes);
    if(!storage)return 2;
    pixels=(unsigned char FAR *)GlobalLock(storage);
    if(!pixels){GlobalFree(storage);return 2;}
    bitmap.header.biSize=sizeof(BITMAPINFOHEADER);
    bitmap.header.biWidth=app->width;bitmap.header.biHeight=app->height;
    screen=GetDC(0);
    if(!screen){GlobalUnlock(storage);GlobalFree(storage);return 3;}
    output_bits=GetDeviceCaps(screen,BITSPIXEL)*GetDeviceCaps(screen,PLANES)<=4?4U:8U;
    ReleaseDC(0,screen);row_bytes=(unsigned short)((((unsigned long)app->width*output_bits+31UL)/32UL)*4UL);
    bitmap.header.biPlanes=1;bitmap.header.biBitCount=output_bits;
    bitmap.header.biSizeImage=(unsigned long)row_bytes*app->height;
    bitmap.header.biClrUsed=output_bits==4U?16L:256L;
    palette_description.version=0x300;
    palette_description.count=output_bits==4U?16U:app->palette_count;
    for(i=0U;i<app->palette_count;++i)
        reduced_colors[i]=mygames_kvm_color_text_nearest(app->palette[i]);
    for(i=0U;i<palette_description.count;++i) {
        rgb=output_bits==4U?mygames_kvm_color_text_rgb((unsigned char)i):
            app->palette[i];
        bitmap.colors[i].rgbRed=(unsigned char)(rgb>>16);
        bitmap.colors[i].rgbGreen=(unsigned char)(rgb>>8);
        bitmap.colors[i].rgbBlue=(unsigned char)rgb;
        palette_description.entries[i].peRed=bitmap.colors[i].rgbRed;
        palette_description.entries[i].peGreen=bitmap.colors[i].rgbGreen;
        palette_description.entries[i].peBlue=bitmap.colors[i].rgbBlue;
        palette_description.entries[i].peFlags=0;
    }
    palette=output_bits==8U?CreatePalette((LOGPALETTE FAR *)&palette_description):0;
    if(output_bits==8U && !palette){GlobalUnlock(storage);GlobalFree(storage);return 3;}
    if(!previous) {
        memset(&cls,0,sizeof(cls));cls.style=CS_HREDRAW|CS_VREDRAW;
        cls.lpfnWndProc=MygamesWin16WndProc;cls.hInstance=instance;
        cls.hCursor=LoadCursor(0,IDC_ARROW);
        cls.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
        cls.lpszClassName="MygamesWin16";
        if(!RegisterClass(&cls)){DeleteObject(palette);GlobalUnlock(storage);GlobalFree(storage);return 3;}
    }
    rect.left=rect.top=0;
    rect.bottom=GetSystemMetrics(SM_CYSCREEN)-GetSystemMetrics(SM_CYCAPTION)-
        2*GetSystemMetrics(SM_CYFRAME)-16;
    if(rect.bottom>480)rect.bottom=480;
    if(rect.bottom<120)rect.bottom=120;
    rect.right=(int)((long)rect.bottom*app->width/app->height);
    AdjustWindowRect(&rect,WS_OVERLAPPEDWINDOW,FALSE);
    window=CreateWindow("MygamesWin16",app->title,WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,CW_USEDEFAULT,rect.right-rect.left,rect.bottom-rect.top,
        0,0,instance,0);
    if(!window){DeleteObject(palette);GlobalUnlock(storage);GlobalFree(storage);return 4;}
    ShowWindow(window,show);service(window);UpdateWindow(window);
    while(GetMessage(&message,0,0,0)) {
        TranslateMessage(&message);DispatchMessage(&message);
    }
    DeleteObject(palette);GlobalUnlock(storage);GlobalFree(storage);pixels=0;app=0;
    return (int)message.wParam;
}
