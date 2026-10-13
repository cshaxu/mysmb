#include <windows.h>
#include <string.h>
#include "win16/host.h"
#include "win16/dib.h"
#include "kvm/color.h"
#include "kvm/windows_key.h"
#include "kvm/pointer.h"
#include "win16/text.h"

struct win16_bitmap { BITMAPINFOHEADER header; RGBQUAD colors[256]; };
struct win16_palette { WORD version,count; PALETTEENTRY entries[256]; };
static struct win16_bitmap bitmap;
static struct win16_palette palette_description;
static HPALETTE palette;
static const struct mygames_win16_application *app;
struct retained_band {HGLOBAL memory;unsigned char FAR *pixels;unsigned short first,rows,bytes;};
static HGLOBAL descriptors,text_storage;
static struct retained_band FAR *bands;
static unsigned short band_count,text_capacity;
static struct mygames_kvm_text_cell FAR *text_cells;
static struct mygames_kvm_text_frame text_frame;
static unsigned long text_colors[16];
static unsigned char view;
static struct mygames_kvm_pointer pointer;
static HMENU menu;

static unsigned char keys[MYGAMES_KVM_PHYSICAL_KEY_COUNT];
static int ready,closing;
static unsigned short output_bits,row_bytes;
static unsigned char reduced_colors[256];
static unsigned long source_colors[256];
static unsigned short retained_width,retained_height,retained_count;

static void free_surfaces(void)
{
    unsigned short i;
    if(bands) {
        for(i=0;i<band_count;++i)if(bands[i].memory) {
            if(bands[i].pixels)GlobalUnlock(bands[i].memory);
            GlobalFree(bands[i].memory);
        }
        GlobalUnlock(descriptors);
    }
    if(descriptors)GlobalFree(descriptors);
    if(text_cells)GlobalUnlock(text_storage);
    if(text_storage)GlobalFree(text_storage);
    descriptors=text_storage=0;bands=0;text_cells=0;band_count=text_capacity=0;
}
static int allocate_graphics(void)
{
    unsigned short i,rows,first=0;
    unsigned long bytes;
    rows=(unsigned short)(65520UL/row_bytes);
    if(!rows)return 0;
    band_count=(unsigned short)(((unsigned long)app->height+rows-1U)/rows);
    bytes=(unsigned long)band_count*sizeof(*bands);
    if(bytes>65520UL)return 0;
    descriptors=GlobalAlloc(GMEM_MOVEABLE,bytes);
    if(!descriptors)return 0;
    bands=(struct retained_band FAR *)GlobalLock(descriptors);
    if(!bands)return 0;
    memset(bands,0,(unsigned short)bytes);
    for(i=0;i<band_count;++i) {
        bands[i].first=first;bands[i].rows=app->height-first;
        if(bands[i].rows>rows)bands[i].rows=rows;
        bands[i].bytes=bands[i].rows*row_bytes;
        bands[i].memory=GlobalAlloc(GMEM_MOVEABLE,bands[i].bytes);
        if(!bands[i].memory)return 0;
        bands[i].pixels=(unsigned char FAR *)GlobalLock(bands[i].memory);
        if(!bands[i].pixels)return 0;
        first+=bands[i].rows;
    }
    return 1;
}
static int configure_graphics(void)
{
    unsigned short i;
    unsigned long rgb;
    if(!app->palette || !app->palette_count || app->palette_count>256U ||
        !app->width || !app->height || app->width>32767U || app->height>32767U)return 0;
    if(retained_width!=app->width || retained_height!=app->height) {
        free_surfaces();
        retained_width=app->width;retained_height=app->height;
        row_bytes=(unsigned short)((((unsigned long)app->width*output_bits+31UL)/32UL)*4UL);
        if((app->available_views&1U) && !allocate_graphics())return 0;
        bitmap.header.biWidth=app->width;
    }
    if(retained_count==app->palette_count &&
        !memcmp(source_colors,app->palette,retained_count*sizeof(*source_colors)))return 1;
    if(palette){DeleteObject(palette);palette=0;}
    memset(bitmap.colors,0,sizeof(bitmap.colors));
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
    if(output_bits==8U && !palette)return 0;
    retained_count=app->palette_count;
    memcpy(source_colors,app->palette,retained_count*sizeof(*source_colors));
    return 1;
 }
static void cancel_pointer(HWND window)
{
    struct mygames_kvm_input_event event;
    mygames_kvm_pointer_cancel(&pointer,&event);
    if(GetCapture()==window)ReleaseCapture();
    app->input(app->context,&event);
}
static int compose(void)
{
    struct mygames_kvm_video_band band;
    const struct mygames_kvm_text_frame FAR *text;
    unsigned short first,i,count;
    unsigned char next=app->presentation?app->presentation(app->context):
        MYGAMES_KVM_PRESENTATION_GRAPHICS;
    if(next==MYGAMES_KVM_PRESENTATION_TEXT) {
        if(!(app->available_views&MYGAMES_WIN16_VIEW_TEXT) || !app->text)return 0;
        text=app->text(app->context);
        if(!mygames_kvm_text_valid(text))return 0;
        count=text->columns*text->rows;
        if(count>text_capacity) {
            if(text_cells)GlobalUnlock(text_storage);
            if(text_storage)GlobalFree(text_storage);
            text_cells=0;text_capacity=0;
            text_storage=GlobalAlloc(GMEM_MOVEABLE,(unsigned long)count*sizeof(*text_cells));
            if(!text_storage)return 0;
            text_cells=(struct mygames_kvm_text_cell FAR *)GlobalLock(text_storage);
            if(!text_cells)return 0;
            text_capacity=count;
        }
        for(i=0;i<text->rows;++i)memcpy(text_cells+i*text->columns,
            text->cells+i*text->stride,text->columns*sizeof(*text_cells));
        for(i=0;i<16;++i)text_colors[i]=text->source_colors?text->colors[i]:mygames_kvm_color_text_rgb((unsigned char)i);
        text_frame=*text;text_frame.cells=text_cells;text_frame.stride=text->columns;
        text_frame.capacity=count;text_frame.colors=text_colors;text_frame.source_colors=1;
    } else {
        if(next!=MYGAMES_KVM_PRESENTATION_GRAPHICS || !app->graphics || !configure_graphics() || !bands)return 0;
        for(i=0;i<band_count;++i)for(first=0U;first<bands[i].rows;first+=band.rows) {
            memset(&band,0,sizeof(band));
            band.first=bands[i].first+first;band.rows=bands[i].rows-first;
            if(band.rows>8U)band.rows=8U;
            if(!app->graphics(app->context,&band) || band.first!=bands[i].first+first ||
                !band.rows || band.rows>8U || band.width!=app->width)return 0;
            band.first=first;
            if(!mygames_win16_dib_band(bands[i].pixels,bands[i].bytes,output_bits,&band,
                reduced_colors,bands[i].rows,app->palette_count))return 0;
        }
    }
    view=next;return 1;
}

static int create_menu(void)
{
    unsigned short g,i;
    HMENU popup;
    const struct mygames_win16_menu_item *item;
    if(!app->menu_count)return 1;
    if(!app->menus || app->menu_count>32U)return 0;
    menu=CreateMenu();if(!menu)return 0;
    for(g=0;g<app->menu_count;++g) {
        if(!app->menus[g].label || (app->menus[g].count && !app->menus[g].items))goto fail;
        popup=CreatePopupMenu();if(!popup)goto fail;
        if(!AppendMenu(menu,MF_POPUP,(UINT)popup,app->menus[g].label)){DestroyMenu(popup);goto fail;}
        for(i=0;i<app->menus[g].count;++i) {
            item=&app->menus[g].items[i];
            if(!AppendMenu(popup,item->label?MF_STRING:MF_SEPARATOR,item->command,item->label))goto fail;
        }
    }
    return 1;
fail:
    DestroyMenu(menu);menu=0;return 0;
}
static void sync_menu(HWND window)
{
    unsigned short g,i;
    const struct mygames_win16_menu_item *item;
    if(!menu)return;
    for(g=0;g<app->menu_count;++g)for(i=0;i<app->menus[g].count;++i) {
        item=&app->menus[g].items[i];if(!item->label)continue;
        CheckMenuItem(menu,item->command,MF_BYCOMMAND|(item->checked?MF_CHECKED:MF_UNCHECKED));
        EnableMenuItem(menu,item->command,MF_BYCOMMAND|(item->disabled?MF_GRAYED:MF_ENABLED));
    }
    DrawMenuBar(window);
}

static void service(HWND window)
{
    struct mygames_win16_update update;
    unsigned char old_view;
    if(closing)return;
    if(pointer.buttons && GetCapture()!=window)cancel_pointer(window);
    KillTimer(window,1);
    if(app->exit_requested(app->context)){closing=1;DestroyWindow(window);return;}
    memset(&update,0,sizeof(update));
    app->update(app->context,GetTickCount(),&update);
    if(app->exit_requested(app->context)){closing=1;DestroyWindow(window);return;}
    sync_menu(window);
    if(update.dirty) {
        old_view=view;ready=compose();
        if(ready && old_view!=view && pointer.buttons)cancel_pointer(window);
        if(!ready){closing=1;DestroyWindow(window);PostQuitMessage(6);return;}
        InvalidateRect(window,0,FALSE);
        if(ready)UpdateWindow(window);
        if(closing)return;
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
    event.modifiers=(GetKeyState(16)<0?MYGAMES_KVM_MOD_SHIFT:0U)|
        (GetKeyState(17)<0?MYGAMES_KVM_MOD_CONTROL:0U)|(GetKeyState(18)<0?MYGAMES_KVM_MOD_ALT:0U);
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
    struct mygames_kvm_input_event events[MYGAMES_KVM_POINTER_EVENTS];
    unsigned short i,count,buttons,mods;
    int top,bottom,paint_ok;
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
    case WM_MOUSEMOVE: case WM_LBUTTONDOWN: case WM_LBUTTONUP:
    case WM_RBUTTONDOWN: case WM_RBUTTONUP: case WM_MBUTTONDOWN: case WM_MBUTTONUP:
        if(pointer.buttons && GetCapture()!=window)cancel_pointer(window);
        buttons=(word&MK_LBUTTON?1U:0U)|(word&MK_RBUTTON?2U:0U)|(word&MK_MBUTTON?4U:0U);
        mods=(word&MK_SHIFT?MYGAMES_KVM_MOD_SHIFT:0U)|(word&MK_CONTROL?MYGAMES_KVM_MOD_CONTROL:0U);
        if(buttons)SetCapture(window);
        count=mygames_kvm_pointer_update(&pointer,(short)(detail&0xffffL),
            (short)((unsigned long)detail>>16),buttons,mods,MYGAMES_KVM_COORD_CLIENT_PIXELS,events);
        if(!buttons && GetCapture()==window)ReleaseCapture();
        for(i=0;i<count;++i)app->input(app->context,&events[i]);
        service(window);return 0;
    case WM_CANCELMODE: cancel_pointer(window);service(window);return 0;
    case WM_COMMAND:
        memset(&event,0,sizeof(event));event.kind=MYGAMES_KVM_INPUT_COMMAND;
        event.physical_code=(unsigned short)word;app->input(app->context,&event);
        service(window);return 0;
    case WM_SIZE:
        memset(&event,0,sizeof(event));event.kind=MYGAMES_KVM_INPUT_RESIZE;
        event.x=(short)(detail&0xffffL);event.y=(short)((unsigned long)detail>>16);
        event.coordinate_space=MYGAMES_KVM_COORD_CLIENT_PIXELS;
        app->input(app->context,&event);service(window);return 0;
    case WM_SETFOCUS: case WM_KILLFOCUS:
        if(message==WM_KILLFOCUS && pointer.buttons)cancel_pointer(window);
        memset(keys,0,sizeof(keys));memset(&event,0,sizeof(event));
        event.kind=MYGAMES_KVM_INPUT_FOCUS;
        event.down=(unsigned char)(message==WM_SETFOCUS);
        app->input(app->context,&event);service(window);return 0;
    case WM_TIMER: service(window);return 0;
    case WM_PAINT:
        dc=BeginPaint(window,&paint);GetClientRect(window,&rect);
        old_palette=0;paint_ok=1;
        if(palette){old_palette=SelectPalette(dc,palette,FALSE);RealizePalette(dc);}
        SetStretchBltMode(dc,COLORONCOLOR);
        if(ready && rect.right>0 && rect.bottom>0) {
            if(view==MYGAMES_KVM_PRESENTATION_TEXT)paint_ok=mygames_win16_text_paint(dc,&rect,&text_frame);
            else for(i=0;i<band_count;++i) {
                top=(int)((long)bands[i].first*rect.bottom/retained_height);
                bottom=(int)((long)(bands[i].first+bands[i].rows)*rect.bottom/retained_height);
                bitmap.header.biHeight=bands[i].rows;bitmap.header.biSizeImage=bands[i].bytes;
                if(bottom>top)StretchDIBits(dc,0,top,rect.right,bottom-top,0,0,retained_width,bands[i].rows,
                    bands[i].pixels,(BITMAPINFO FAR *)&bitmap,DIB_RGB_COLORS,SRCCOPY);
            }
        }
        if(old_palette)SelectPalette(dc,old_palette,TRUE);
        EndPaint(window,&paint);
        if(!paint_ok){closing=1;DestroyWindow(window);PostQuitMessage(6);}
        return 0;
    case WM_DESTROY: closing=1;if(pointer.buttons)cancel_pointer(window);KillTimer(window,1);PostQuitMessage(0);return 0;
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
    HDC screen;
    int maximum_width;
    if(!application || !application->input || !application->update ||
        !application->exit_requested || !application->available_views ||
        (application->available_views&~3U) ||
        ((application->available_views&1U) && !application->graphics) ||
        ((application->available_views&2U) && !application->text))return 1;
    if(!application->palette || !application->palette_count ||
        application->palette_count>256U || !application->width || !application->height ||
        application->width>32767U || application->height>32767U)return 1;
    app=application;ready=closing=0;palette=0;menu=0;
    retained_width=retained_height=retained_count=0;
    memset(&pointer,0,sizeof(pointer));
    memset(keys,0,sizeof(keys));memset(&bitmap,0,sizeof(bitmap));
    bitmap.header.biSize=sizeof(BITMAPINFOHEADER);
    bitmap.header.biWidth=app->width;bitmap.header.biHeight=app->height;
    screen=GetDC(0);
    if(!screen){free_surfaces();return 3;}
    output_bits=GetDeviceCaps(screen,BITSPIXEL)*GetDeviceCaps(screen,PLANES)<=4?4U:8U;
    ReleaseDC(0,screen);
    if(!configure_graphics()){DeleteObject(palette);free_surfaces();return 2;}
    if(!previous) {
        memset(&cls,0,sizeof(cls));cls.style=CS_HREDRAW|CS_VREDRAW;
        cls.lpfnWndProc=MygamesWin16WndProc;cls.hInstance=instance;
        cls.hCursor=LoadCursor(0,IDC_ARROW);
        cls.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
        cls.lpszClassName="MygamesWin16";
        if(!RegisterClass(&cls)){DeleteObject(palette);free_surfaces();return 3;}
    }
    rect.left=rect.top=0;
    rect.bottom=GetSystemMetrics(SM_CYSCREEN)-GetSystemMetrics(SM_CYCAPTION)-
        2*GetSystemMetrics(SM_CYFRAME)-16;
    if(rect.bottom>480)rect.bottom=480;
    if(rect.bottom<120)rect.bottom=120;
    rect.right=(int)((long)rect.bottom*app->width/app->height);
    maximum_width=GetSystemMetrics(SM_CXSCREEN)-2*GetSystemMetrics(SM_CXFRAME)-16;
    if(maximum_width<1)maximum_width=1;
    if(rect.right>maximum_width){rect.right=maximum_width;rect.bottom=(int)((long)maximum_width*app->height/app->width);}
    if(rect.bottom<1)rect.bottom=1;
    if(!create_menu()){DeleteObject(palette);free_surfaces();return 3;}
    AdjustWindowRect(&rect,WS_OVERLAPPEDWINDOW,menu!=0);
    window=CreateWindow("MygamesWin16",app->title,WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,CW_USEDEFAULT,rect.right-rect.left,rect.bottom-rect.top,
        0,menu,instance,0);
    if(!window){if(menu)DestroyMenu(menu);DeleteObject(palette);free_surfaces();return 4;}
    ShowWindow(window,show);service(window);UpdateWindow(window);
    while(GetMessage(&message,0,0,0)) {
        TranslateMessage(&message);DispatchMessage(&message);
    }
    DeleteObject(palette);free_surfaces();app=0;
    return (int)message.wParam;
}
