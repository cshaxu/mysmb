#include <stdlib.h>
#include <string.h>
#include "win16/host.h"
static LRESULT (*procedure)(HWND,UINT,WPARAM,LPARAM);
static unsigned long now;
static unsigned short timer,sets,updates,draws,paints,inputs;
static int failure,step,quit,exit_code,exit_flag,dirty,wake,failed_timer,focus;
static unsigned char pixels[16];
static unsigned long colors[2]={0UL,0xffffffUL};
static HWND window=(HWND)1;
static void input(void *context,const struct mygames_kvm_input_event *event)
{
    (void)context;++inputs;
    if(event->kind==MYGAMES_KVM_INPUT_FOCUS)focus=event->down;
    else if(event->physical_code==MYGAMES_KVM_KEY_ESCAPE)exit_flag=1;
    else if(event->down)dirty=1;
}
static void update(void *context,unsigned long time,struct mygames_win16_update *out)
{(void)context;++updates;now=time;out->wake_ms=(unsigned short)wake;out->dirty=(unsigned char)dirty;dirty=0;}
static int graphics(void *context,struct mygames_kvm_video_band *band)
{(void)context;++draws;band->pixels=pixels;band->width=band->stride=4;band->capacity=16;return 1;}
static mygames_kvm_u8 exiting(void *context){(void)context;return (mygames_kvm_u8)exit_flag;}
DWORD GetTickCount(void){return now;}
HGLOBAL GlobalAlloc(UINT flags,DWORD bytes){(void)flags;return malloc(bytes);}
void *GlobalLock(HGLOBAL memory){return memory;}
int GlobalUnlock(HGLOBAL memory){(void)memory;return 0;}
HGLOBAL GlobalFree(HGLOBAL memory){free(memory);return 0;}
int KillTimer(HWND w,unsigned short id){(void)w;(void)id;timer=0;return 1;}
int SetTimer(HWND w,unsigned short id,unsigned short ms,void *proc)
{(void)w;(void)id;(void)proc;++sets;if(failed_timer)return 0;timer=ms;return 1;}
void PostQuitMessage(int code){quit=1;exit_code=code;}
int DestroyWindow(HWND w){procedure(w,WM_KILLFOCUS,0,0);procedure(w,WM_DESTROY,0,0);return 1;}
void InvalidateRect(HWND w,const RECT *r,int erase){(void)w;(void)r;(void)erase;}
void UpdateWindow(HWND w){procedure(w,WM_PAINT,0,0);}
HDC GetDC(HWND w){(void)w;return (HDC)1;}
HPALETTE SelectPalette(HDC dc,HPALETTE p,int force){(void)dc;(void)force;return p;}
unsigned short RealizePalette(HDC dc){(void)dc;return 0;}
void ReleaseDC(HWND w,HDC dc){(void)w;(void)dc;}
HDC BeginPaint(HWND w,PAINTSTRUCT *p){(void)w;(void)p;return (HDC)1;}
void GetClientRect(HWND w,RECT *r){(void)w;r->left=r->top=0;r->right=r->bottom=100;}
void SetStretchBltMode(HDC dc,int mode){(void)dc;(void)mode;}
void StretchDIBits(HDC dc,int a,int b,int c,int d,int e,int f,int g,int h,const void *p,const BITMAPINFO *i,int mode,long operation)
{(void)dc;(void)a;(void)b;(void)c;(void)d;(void)e;(void)f;(void)g;(void)h;(void)p;(void)i;(void)mode;(void)operation;++paints;}
void EndPaint(HWND w,PAINTSTRUCT *p){(void)w;(void)p;}
LRESULT DefWindowProc(HWND w,UINT m,WPARAM p,LPARAM l){(void)w;(void)m;(void)p;(void)l;return 0;}
int GetDeviceCaps(HDC dc,int index){(void)dc;return index==PLANES?1:8;}
HPALETTE CreatePalette(const LOGPALETTE *p){(void)p;return (HPALETTE)1;}
int DeleteObject(void *p){(void)p;return 1;}
void *LoadCursor(HINSTANCE i,const char *name){(void)i;(void)name;return 0;}
int RegisterClass(const WNDCLASS *cls){procedure=cls->lpfnWndProc;return 1;}
int GetSystemMetrics(int index){return index==SM_CYSCREEN?480:8;}
int AdjustWindowRect(RECT *r,long style,int menu){(void)r;(void)style;(void)menu;return 1;}
HWND CreateWindow(const char *c,const char *title,long style,int x,int y,int width,int height,HWND parent,void *menu,HINSTANCE instance,void *data)
{(void)c;(void)title;(void)style;(void)x;(void)y;(void)width;(void)height;(void)parent;(void)menu;(void)instance;(void)data;return window;}
void ShowWindow(HWND w,int show){(void)show;procedure(w,WM_SETFOCUS,0,0);}
void TranslateMessage(const MSG *m){(void)m;}
void DispatchMessage(const MSG *m){procedure(window,m->message,m->wParam,m->lParam);}
int GetMessage(MSG *m,HWND w,int first,int last)
{
    (void)w;(void)first;(void)last;memset(m,0,sizeof(*m));
    if(quit){m->wParam=(WPARAM)exit_code;return 0;}
    switch(step++) {
    case 0:
        if(timer || sets || draws || paints || !focus || updates!=2)failure=20;
        m->message=WM_KEYDOWN;m->wParam='N';return 1;
    case 1:
        if(draws!=1 || paints!=1)failure=21;
        m->message=WM_PAINT;return 1;
    case 2:
        if(draws!=1 || paints!=2 || updates!=3)failure=22;
        wake=123;now=999;
        m->message=WM_KEYUP;m->wParam='N';return 1;
    case 3:
        if(timer!=123 || sets!=1 || draws!=1)failure=23;
        wake=0;m->message=WM_TIMER;return 1;
    case 4:
        if(timer || sets!=1 || draws!=1)failure=24;
        m->message=WM_KILLFOCUS;return 1;
    case 5:
        if(focus || timer)failure=25;
        m->message=WM_KEYDOWN;m->wParam=27;return 1;
    default:quit=1;m->wParam=99;return 0;
    }
    return 0;
}
int main(void)
{
    struct mygames_win16_application app;
    int result;
    memset(&app,0,sizeof(app));app.title="Neutral idle client";
    app.available_views=MYGAMES_WIN16_VIEW_GRAPHICS;app.input=input;
    app.update=update;app.exit_requested=exiting;app.graphics=graphics;
    app.palette=colors;app.palette_count=2;app.width=app.height=4;
    result=mygames_win16_run(1,0,1,&app);
    if(failure)return failure;
    if(result || !exit_flag || draws!=1 || paints!=2 || inputs!=6)return 1;
    /* Requested timer failure must terminate, not strand the client. */
    quit=exit_flag=step=0;wake=1;failed_timer=1;
    if(mygames_win16_run(1,0,1,&app)!=5)return 2;
    return 0;
}
