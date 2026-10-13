#include <string.h>
#include "win32/window.h"
static unsigned short pointer_buttons(WPARAM word)
{
    return (unsigned short)((word&MK_LBUTTON?1U:0U)|(word&MK_RBUTTON?2U:0U)|
        (word&MK_MBUTTON?4U:0U)|(word&MK_XBUTTON1?8U:0U)|(word&MK_XBUTTON2?16U:0U));
}
int mygames_win32_window_event(HWND window,UINT message,WPARAM word,LPARAM detail,
    struct mygames_win32_window_input *pointer,struct mygames_win32_input *keys,
    struct mygames_win32_window_geometry *geometry,
    mygames_win32_event_sink sink,void *context,LRESULT *result)
{
    struct mygames_kvm_input_event events[MYGAMES_KVM_POINTER_EVENTS];
    struct mygames_kvm_input_event *event=events;
    unsigned short count,i,buttons;
    RECT rect;
    *result=0;memset(events,0,sizeof(events));
    if(message==WM_KEYDOWN || message==WM_KEYUP || message==WM_SYSKEYDOWN || message==WM_SYSKEYUP) {
        if(!mygames_win32_input_key(keys,(WORD)word,(WORD)((detail>>16)&255L),
            (unsigned char)(message==WM_KEYDOWN || message==WM_SYSKEYDOWN),event))return 0;
        if(event->down && (detail&0x40000000L))event->repeat=1U;
        event->modifiers=(unsigned short)((GetKeyState(VK_SHIFT)<0?MYGAMES_KVM_MOD_SHIFT:0U)|
            (GetKeyState(VK_CONTROL)<0?MYGAMES_KVM_MOD_CONTROL:0U)|
            (GetKeyState(VK_MENU)<0?MYGAMES_KVM_MOD_ALT:0U));
        sink(context,window,event);return 1;
    }
    if(message==WM_MOUSEMOVE || message==WM_LBUTTONDOWN || message==WM_LBUTTONUP ||
        message==WM_RBUTTONDOWN || message==WM_RBUTTONUP || message==WM_MBUTTONDOWN ||
        message==WM_MBUTTONUP || message==WM_XBUTTONDOWN || message==WM_XBUTTONUP) {
        buttons=pointer_buttons(word);
        count=mygames_kvm_pointer_update(&pointer->pointer,(short)LOWORD(detail),
            (short)HIWORD(detail),buttons,(unsigned short)((word&MK_SHIFT?MYGAMES_KVM_MOD_SHIFT:0U)|
            (word&MK_CONTROL?MYGAMES_KVM_MOD_CONTROL:0U)),MYGAMES_KVM_COORD_CLIENT_PIXELS,events);
        if(buttons && GetCapture()!=window)SetCapture(window);
        for(i=0U;i<count;++i)sink(context,window,events+i);
        if(!buttons && GetCapture()==window)ReleaseCapture();
        *result=TRUE;return 1;
    }
    if(message==WM_CANCELMODE || (message==WM_CAPTURECHANGED && pointer->pointer.buttons)) {
        mygames_kvm_pointer_cancel(&pointer->pointer,event);
        if(GetCapture()==window)ReleaseCapture();
        sink(context,window,event);return 1;
    }
    if(message==WM_KILLFOCUS || message==WM_SETFOCUS || message==WM_ACTIVATEAPP) {
        if(message==WM_ACTIVATEAPP && word && GetFocus()!=window)return 0;
        event->kind=MYGAMES_KVM_INPUT_FOCUS;
        event->down=(unsigned char)(message==WM_SETFOCUS || (message==WM_ACTIVATEAPP && word));
        if(!event->down) {
            mygames_win32_input_clear(keys);
            mygames_kvm_pointer_cancel(&pointer->pointer,events+1);
            if(GetCapture()==window)ReleaseCapture();
        }
        sink(context,window,event);
        if(!event->down)sink(context,window,events+1);
        return 1;
    }
    if(message==WM_COMMAND) {
        event->kind=MYGAMES_KVM_INPUT_COMMAND;event->physical_code=LOWORD(word);
        sink(context,window,event);return 1;
    }
    if(message==WM_SIZING && geometry) {
        mygames_win32_window_size_rectangle(window,(RECT *)detail,(UINT)word,0U,geometry);
        *result=TRUE;return 1;
    }
    if(message==WM_GETMINMAXINFO && geometry) {
        mygames_win32_window_size_limits(window,(MINMAXINFO *)detail,geometry);return 1;
    }
    if(message==0x02e0U && geometry) {
        rect=*(RECT *)detail;
        mygames_win32_window_size_rectangle(window,&rect,WMSZ_BOTTOMRIGHT,LOWORD(word),geometry);
        SetWindowPos(window,NULL,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,
            SWP_NOZORDER|SWP_NOACTIVATE);return 1;
    }
    if(message==WM_SIZE) {
        if(word!=SIZE_MINIMIZED && geometry)mygames_win32_window_normalize_client(window,geometry);
        GetClientRect(window,&rect);event->kind=MYGAMES_KVM_INPUT_RESIZE;
        event->x=(short)(rect.right>32767?32767:rect.right);
        event->y=(short)(rect.bottom>32767?32767:rect.bottom);
        event->coordinate_space=MYGAMES_KVM_COORD_CLIENT_PIXELS;
        sink(context,window,event);InvalidateRect(window,NULL,FALSE);return 1;
    }
    return 0;
}
HWND mygames_win32_window_create(HINSTANCE instance,const char *class_name,
    const char *title,WNDPROC procedure,struct mygames_win32_window_geometry *geometry)
{
    WNDCLASS cls;
    HWND window;
    RECT initial;
    if(!geometry || !class_name || !procedure || geometry->unit_width<1 ||
        geometry->unit_height<1 || geometry->minimum_units<1 ||
        geometry->initial_units<geometry->minimum_units || geometry->initial_units>32767 ||
        geometry->unit_width>32767/geometry->initial_units ||
        geometry->unit_height>32767/geometry->initial_units)return NULL;
    memset(&cls,0,sizeof(cls));cls.lpfnWndProc=procedure;cls.hInstance=instance;
    cls.hCursor=LoadCursor(NULL,IDC_ARROW);cls.lpszClassName=class_name;
    if(!RegisterClass(&cls) && GetLastError()!=ERROR_CLASS_ALREADY_EXISTS)return NULL;
    SetRect(&initial,0,0,geometry->unit_width*geometry->initial_units,
        geometry->unit_height*geometry->initial_units);
    AdjustWindowRectEx(&initial,WS_OVERLAPPEDWINDOW,FALSE,0U);
    geometry->adjusting=1;
    window=CreateWindow(class_name,title,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,
        initial.right-initial.left,initial.bottom-initial.top,NULL,NULL,instance,NULL);
    if(window && !mygames_win32_window_initial_client(window,geometry)) {
        DestroyWindow(window);window=NULL;
    }
    geometry->adjusting=0;return window;
}
int mygames_win32_pixels_present(HDC dc,const RECT *target,const DWORD *pixels,
    unsigned short width,unsigned short height,unsigned long capacity)
{
    BITMAPINFO info;
    int result,old_mode;
    if(!dc || !target || !pixels || !width || !height || width>32767U || height>32767U ||
        (unsigned long)width*height>capacity || target->right<=target->left ||
        target->bottom<=target->top)return 0;
    memset(&info,0,sizeof(info));info.bmiHeader.biSize=sizeof(info.bmiHeader);
    info.bmiHeader.biWidth=width;info.bmiHeader.biHeight=-(LONG)height;
    info.bmiHeader.biPlanes=1;info.bmiHeader.biBitCount=32;info.bmiHeader.biCompression=BI_RGB;
    old_mode=SetStretchBltMode(dc,COLORONCOLOR);
    result=StretchDIBits(dc,target->left,target->top,target->right-target->left,
        target->bottom-target->top,0,0,width,height,pixels,&info,DIB_RGB_COLORS,SRCCOPY)>0;
    if(old_mode)SetStretchBltMode(dc,old_mode);
    return result;
}
int mygames_win32_window_paint(HWND window,const DWORD *pixels,
    unsigned short width,unsigned short height,unsigned long capacity)
{
    PAINTSTRUCT paint;
    HDC dc;
    RECT client;
    int result;
    dc=BeginPaint(window,&paint);if(!dc)return 0;
    SetRect(&client,0,0,0,0);GetClientRect(window,&client);
    result=mygames_win32_pixels_present(dc,&client,pixels,width,height,capacity);
    EndPaint(window,&paint);return result;
}
