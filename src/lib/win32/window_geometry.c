#include <windows.h>
#include <string.h>

#include "win32/window_geometry.h"

typedef UINT (WINAPI *mygames_win32_get_dpi_fn)(HWND);
typedef BOOL (WINAPI *mygames_win32_adjust_for_dpi_fn)(LPRECT,DWORD,BOOL,DWORD,UINT);

UINT mygames_win32_window_dpi(HWND window)
{
    FARPROC raw=GetProcAddress(GetModuleHandleA("user32.dll"),"GetDpiForWindow");
    mygames_win32_get_dpi_fn function=NULL;
    UINT dpi;
    memcpy(&function,&raw,sizeof(function));
    dpi=function?function(window):96U;
    return dpi?dpi:96U;
}

void mygames_win32_window_margins(HWND window,UINT dpi,RECT *margins)
{
    FARPROC raw=GetProcAddress(GetModuleHandleA("user32.dll"),
        "AdjustWindowRectExForDpi");
    mygames_win32_adjust_for_dpi_fn function=NULL;
    DWORD style=(DWORD)GetWindowLongPtr(window,GWL_STYLE);
    DWORD extended=(DWORD)GetWindowLongPtr(window,GWL_EXSTYLE);
    BOOL has_menu=GetMenu(window)!=NULL;
    memcpy(&function,&raw,sizeof(function));
    SetRect(margins,0,0,0,0);
    if(function) (void)function(margins,style,has_menu,extended,dpi);
    else (void)AdjustWindowRectEx(margins,style,has_menu,extended);
}

static int mygames_win32_window_units(int width,int height,int by_height,
    const struct mygames_win32_window_geometry *geometry)
{
    int units=by_height?height/geometry->unit_height:width/geometry->unit_width;
    return units<geometry->minimum_units?geometry->minimum_units:units;
}

void mygames_win32_window_geometry_initialize(
    struct mygames_win32_window_geometry *geometry,int unit_width,
    int unit_height,int minimum_units,int initial_units)
{
    geometry->unit_width=unit_width;
    geometry->unit_height=unit_height;
    geometry->minimum_units=minimum_units;
    geometry->initial_units=initial_units;
    geometry->adjusting=0;
}

void mygames_win32_window_enable_dpi(void)
{
    typedef BOOL (WINAPI *aware_fn)(HANDLE);
    FARPROC raw=GetProcAddress(GetModuleHandleA("user32.dll"),
        "SetProcessDpiAwarenessContext");
    aware_fn function=NULL;
    memcpy(&function,&raw,sizeof(function));
    if(!function || !function((HANDLE)(LONG_PTR)-4)) (void)SetProcessDPIAware();
}

int mygames_win32_window_initial_client(HWND window,
    const struct mygames_win32_window_geometry *geometry)
{
    RECT margins;
    UINT dpi=mygames_win32_window_dpi(window);
    int units=MulDiv(geometry->initial_units,(int)dpi,96);
    if(units<1) units=1;
    mygames_win32_window_margins(window,dpi,&margins);
    return SetWindowPos(window,NULL,0,0,
        units*geometry->unit_width+margins.right-margins.left,
        units*geometry->unit_height+margins.bottom-margins.top,
        SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE)!=0;
}

void mygames_win32_window_size_rectangle(HWND window,RECT *rect,UINT edge,UINT dpi,
    const struct mygames_win32_window_geometry *geometry)
{
    RECT margins;
    int width,height,units,dx,dy;
    mygames_win32_window_margins(window,dpi?dpi:mygames_win32_window_dpi(window),&margins);
    width=rect->right-rect->left-(margins.right-margins.left);
    height=rect->bottom-rect->top-(margins.bottom-margins.top);
    units=mygames_win32_window_units(width,height,
        edge==WMSZ_TOP || edge==WMSZ_BOTTOM,geometry);
    dx=units*geometry->unit_width+(margins.right-margins.left)-(rect->right-rect->left);
    dy=units*geometry->unit_height+(margins.bottom-margins.top)-(rect->bottom-rect->top);
    if(edge==WMSZ_LEFT || edge==WMSZ_TOPLEFT || edge==WMSZ_BOTTOMLEFT) rect->left-=dx;
    else if(edge==WMSZ_TOP || edge==WMSZ_BOTTOM) { rect->left-=dx/2;rect->right+=dx-dx/2; }
    else rect->right+=dx;
    if(edge==WMSZ_TOP || edge==WMSZ_TOPLEFT || edge==WMSZ_TOPRIGHT) rect->top-=dy;
    else if(edge==WMSZ_LEFT || edge==WMSZ_RIGHT) { rect->top-=dy/2;rect->bottom+=dy-dy/2; }
    else rect->bottom+=dy;
}

void mygames_win32_window_size_limits(HWND window,MINMAXINFO *limits,
    const struct mygames_win32_window_geometry *geometry)
{
    MONITORINFO monitor;
    RECT margins;
    int units,width,height,border_width,border_height;
    monitor.cbSize=sizeof(monitor);
    if(!GetMonitorInfo(MonitorFromWindow(window,MONITOR_DEFAULTTONEAREST),&monitor)) return;
    mygames_win32_window_margins(window,mygames_win32_window_dpi(window),&margins);
    border_width=margins.right-margins.left;
    border_height=margins.bottom-margins.top;
    width=monitor.rcWork.right-monitor.rcWork.left;
    height=monitor.rcWork.bottom-monitor.rcWork.top;
    units=(width-border_width)/geometry->unit_width;
    if((height-border_height)/geometry->unit_height<units)
        units=(height-border_height)/geometry->unit_height;
    if(units<1) units=1;
    limits->ptMaxSize.x=units*geometry->unit_width+border_width;
    limits->ptMaxSize.y=units*geometry->unit_height+border_height;
    limits->ptMaxPosition.x=monitor.rcWork.left-monitor.rcMonitor.left+
        (width-limits->ptMaxSize.x)/2;
    limits->ptMaxPosition.y=monitor.rcWork.top-monitor.rcMonitor.top+
        (height-limits->ptMaxSize.y)/2;
    limits->ptMinTrackSize.x=geometry->minimum_units*geometry->unit_width+border_width;
    limits->ptMinTrackSize.y=geometry->minimum_units*geometry->unit_height+border_height;
    limits->ptMaxTrackSize=limits->ptMaxSize;
}

void mygames_win32_window_normalize_client(HWND window,
    struct mygames_win32_window_geometry *geometry)
{
    RECT client,outer;
    int units,width,height;
    if(geometry->adjusting || !GetClientRect(window,&client)) return;
    width=client.right;height=client.bottom;
    if(width<=0 || height<=0 ||
        (width%geometry->unit_width==0 && height%geometry->unit_height==0 &&
         width/geometry->unit_width==height/geometry->unit_height)) return;
    units=width/geometry->unit_width;
    if(height/geometry->unit_height<units) units=height/geometry->unit_height;
    if(units<1) units=1;
    if(!GetWindowRect(window,&outer)) return;
    geometry->adjusting=1;
    (void)SetWindowPos(window,NULL,0,0,
        outer.right-outer.left-width+units*geometry->unit_width,
        outer.bottom-outer.top-height+units*geometry->unit_height,
        SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
    geometry->adjusting=0;
}
