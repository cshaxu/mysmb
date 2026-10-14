#include <stdlib.h>
#include <string.h>
#include "win16/host.h"
#include "win16/text.h"
static LRESULT (*procedure)(HWND,UINT,WPARAM,LPARAM);
static unsigned long now;
static unsigned short timer,sets,updates,draws,paints,inputs;
static int fail_alloc,allocation_calls,fail_lock,lock_calls;
static int failure,step,quit,exit_code,exit_flag,dirty,wake,failed_timer,focus;
static unsigned char pixels[4032];
static struct mygames_win16_application *active_app;
static int fail_font,fail_text;
static int device_bits=8,color_case;
static int hooks_started,hooks_closed,reentrant_updates;
static int scenario,view_kind,mouse_events,cancels,commands,text_draws,allocs;
static unsigned long last_foreground,last_background;
static struct mygames_kvm_input_event last_event;
static struct mygames_kvm_text_cell cells[6]={{1,15,1},{16,14,2},{219,12,3},{179,11,4},{32,10,5},{2,9,6}};
static struct mygames_kvm_text_frame text={cells,3,2,3,6,0,0};
static unsigned char presentation(void *context){(void)context;return (unsigned char)view_kind;}
static const struct mygames_kvm_text_frame *text_view(void *context){(void)context;return &text;}

static unsigned long colors[2]={0UL,0xffffffUL};
static HWND window=(HWND)1;
static void input(void *context,const struct mygames_kvm_input_event *event)
{
    (void)context;++inputs;last_event=*event;
    if(event->kind==MYGAMES_KVM_INPUT_MOUSE_BUTTON || event->kind==MYGAMES_KVM_INPUT_MOUSE_MOVE)++mouse_events;
    if(event->kind==MYGAMES_KVM_INPUT_CANCEL)++cancels;
    if(event->kind==MYGAMES_KVM_INPUT_COMMAND)++commands;
    if(event->kind==MYGAMES_KVM_INPUT_FOCUS)focus=event->down;
    else if(event->physical_code==MYGAMES_KVM_KEY_ESCAPE)exit_flag=1;
    else if(event->down)dirty=1;
}
static void update(void *context,unsigned long time,struct mygames_win16_update *out)
{(void)context;++updates;if(scenario==2){++reentrant_updates;procedure(window,WM_TIMER,0,0);}now=time;out->wake_ms=(unsigned short)wake;out->dirty=(unsigned char)dirty;dirty=0;}
static int graphics(void *context,struct mygames_kvm_video_band *band)
{(void)context;++draws;band->pixels=pixels;band->width=band->stride=active_app->width;band->capacity=sizeof(pixels);return 1;}
static mygames_kvm_u8 exiting(void *context){(void)context;return (mygames_kvm_u8)exit_flag;}
DWORD GetTickCount(void){return now;}
HGLOBAL GlobalAlloc(UINT flags,DWORD bytes){(void)flags;if(++allocation_calls==fail_alloc)return 0;++allocs;return malloc(bytes);}
void *GlobalLock(HGLOBAL memory){if(++lock_calls==fail_lock)return 0;return memory;}
int GlobalUnlock(HGLOBAL memory){(void)memory;return 0;}
HGLOBAL GlobalFree(HGLOBAL memory){--allocs;free(memory);return 0;}
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
int GetDeviceCaps(HDC dc,int index){(void)dc;return index==PLANES?1:device_bits;}
HPALETTE CreatePalette(const LOGPALETTE *p){(void)p;return (HPALETTE)1;}
int DeleteObject(void *p){(void)p;return 1;}
void *LoadCursor(HINSTANCE i,const char *name){(void)i;(void)name;return 0;}
int RegisterClass(const WNDCLASS *cls){procedure=cls->lpfnWndProc;return 1;}
int GetSystemMetrics(int index){return index==SM_CYSCREEN?480:index==SM_CXSCREEN?640:8;}
int AdjustWindowRect(RECT *r,long style,int menu){(void)r;(void)style;(void)menu;return 1;}
HWND CreateWindow(const char *c,const char *title,long style,int x,int y,int width,int height,HWND parent,HMENU menu,HINSTANCE instance,void *data)
{(void)c;(void)title;(void)style;(void)x;(void)y;(void)width;(void)height;(void)parent;(void)menu;(void)instance;(void)data;return window;}
void ShowWindow(HWND w,int show){(void)show;procedure(w,WM_SETFOCUS,0,0);}
void TranslateMessage(const MSG *m){(void)m;}
void DispatchMessage(const MSG *m){procedure(window,m->message,m->wParam,m->lParam);}
int GetMessage(MSG *m,HWND w,int first,int last)
{
    (void)w;(void)first;(void)last;memset(m,0,sizeof(*m));
    if(quit){m->wParam=(WPARAM)exit_code;return 0;}
    if(scenario==2) {
        if(!hooks_started || !paints)failure=60;
        m->message=step++?WM_TIMER:WM_CLOSE;now+=20;
        if(step>8){failure=61;quit=1;return 0;}return 1;
    }
    if(scenario) {
        switch(step++) {
        case 0:
            if(draws<41 || paints!=6 || allocs!=4)failure=30;
            m->message=WM_LBUTTONDOWN;m->wParam=MK_LBUTTON;m->lParam=(5L<<16)|0xfffeL;return 1;
        case 1:
            if(mouse_events!=1 || last_event.x!=-2 || last_event.buttons!=1 || GetCapture()!=window)failure=31;
            m->message=WM_MOUSEMOVE;m->wParam=MK_LBUTTON|MK_RBUTTON|MK_SHIFT;m->lParam=(7L<<16)|8;return 1;
        case 2:
            if(last_event.buttons!=3 || last_event.modifiers!=MYGAMES_KVM_MOD_SHIFT)failure=32;
            m->message=WM_CANCELMODE;return 1;
        case 3:
            if(cancels!=1 || GetCapture())failure=33;
            m->message=WM_COMMAND;m->wParam=42;return 1;
        case 4:
            if(commands!=1 || last_event.physical_code!=42)failure=34;
            view_kind=1;dirty=1;m->message=WM_TIMER;return 1;
        case 5:
            if(text_draws!=6)failure=35;
            cells[0].character=99;m->message=WM_PAINT;return 1;
        case 6:
            if(text_draws!=12)failure=36;
            view_kind=0;active_app->width=8;active_app->height=8;dirty=1;
            m->message=WM_SIZE;m->lParam=(80L<<16)|100;return 1;
        case 7:
            if(last_event.kind!=MYGAMES_KVM_INPUT_RESIZE || last_event.x!=100 || last_event.y!=80 || allocs!=2)failure=37;
            m->message=WM_KEYDOWN;m->wParam=27;return 1;
        default:quit=1;m->wParam=98;return 0;
        }
    }
    switch(step++) {
    case 0:
        if(timer || sets || draws || paints || !focus || updates!=1)failure=20;
        m->message=WM_KEYDOWN;m->wParam='N';return 1;
    case 1:
        if(draws!=1 || paints!=1)failure=21;
        m->message=WM_PAINT;return 1;
    case 2:
        if(draws!=1 || paints!=2 || updates!=2)failure=22;
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
short GetKeyState(int key){(void)key;return 0;}
static HWND captured;
HWND GetCapture(void){return captured;}
HWND SetCapture(HWND w){HWND old=captured;captured=w;return old;}
void ReleaseCapture(void){captured=0;}
HMENU CreateMenu(void){return 1;}
HMENU CreatePopupMenu(void){return 2;}
int AppendMenu(HMENU m,unsigned short f,UINT id,const char *label){(void)m;(void)f;(void)id;(void)label;return 1;}
int DestroyMenu(HMENU m){(void)m;return 1;}
int CheckMenuItem(HMENU m,UINT id,UINT f){(void)m;(void)id;(void)f;return 1;}
int EnableMenuItem(HMENU m,UINT id,UINT f){(void)m;(void)id;(void)f;return 1;}
void DrawMenuBar(HWND w){(void)w;}
HFONT CreateFont(int a,int b,int c,int d,int e,unsigned char f,unsigned char g,unsigned char h,unsigned char i,unsigned char j,unsigned char k,unsigned char l,unsigned char m,const char *n)
{(void)a;(void)b;(void)c;(void)d;(void)e;(void)f;(void)g;(void)h;(void)i;(void)j;(void)k;(void)l;(void)m;(void)n;return fail_font?0:(HFONT)1;}
void *SelectObject(HDC dc,void *o){(void)dc;return o;}
DWORD SetTextColor(HDC dc,DWORD c){(void)dc;last_foreground=c;return c;}
DWORD SetBkColor(HDC dc,DWORD c){(void)dc;last_background=c;return c;}
int ExtTextOut(HDC dc,int x,int y,UINT flags,const RECT *r,const char *c,UINT n,const int *spacing)
{(void)dc;(void)x;(void)y;(void)spacing;
 if(n!=1 || flags!=(ETO_OPAQUE|ETO_CLIPPED) || r->right<=r->left || r->bottom<=r->top)failure=38;
 if(!color_case && text_draws%6==0 && ((unsigned char)*c!=1 || last_foreground!=0xffffffUL || last_background!=0xaa0000UL))failure=39;
 ++text_draws;return !fail_text;}
static void after_paint(void *p){(void)p;if(!paints)failure=62;++hooks_started;}
static int controlled_close(void *p,int reason){(void)p;(void)reason;return ++hooks_closed>=4;}
int main(void)
{
    struct mygames_win16_application app;
    struct mygames_win16_lifecycle hooks;
    int result,i;
    RECT rect;
    unsigned long source_colors[16];
    memset(&app,0,sizeof(app));app.title="Neutral idle client";
    app.available_views=MYGAMES_WIN16_VIEW_GRAPHICS;app.input=input;
    app.update=update;app.exit_requested=exiting;app.graphics=graphics;
    app.palette=colors;app.palette_count=2;app.width=app.height=4;
    active_app=&app;
    result=mygames_win16_run(1,0,1,&app);
    if(failure)return failure;
    if(result || !exit_flag || draws!=1 || paints!=2 || inputs!=6)return 1;
    /* Requested timer failure must terminate, not strand the client. */
    quit=exit_flag=step=0;wake=1;failed_timer=1;
    if(mygames_win16_run(1,0,1,&app)!=5)return 2;
    scenario=1;quit=exit_flag=step=failed_timer=0;wake=0;dirty=1;draws=paints=0;
    app.width=504;app.height=323;app.available_views=3;app.presentation=presentation;app.text=text_view;
    if(mygames_win16_run(1,0,1,&app) || failure || allocs)return failure?failure:3;
    app.width=504;app.height=323;
    for(i=1;i<=4;++i) {
        fail_alloc=i;allocation_calls=0;
        if(mygames_win16_run(1,0,1,&app)!=2 || allocs)return 40+i;
    }
    fail_alloc=0;
    for(i=1;i<=4;++i) {
        fail_lock=i;lock_calls=0;
        if(mygames_win16_run(1,0,1,&app)!=2 || allocs)return 45+i;
    }
    fail_lock=0;rect.left=rect.top=0;rect.right=100;rect.bottom=80;
    if(mygames_win16_text_paint(0,&rect,&text))return 50;
    fail_font=1;if(mygames_win16_text_paint((HDC)1,&rect,&text))return 51;
    fail_font=0;fail_text=1;cells[0].character=1;
    if(mygames_win16_text_paint((HDC)1,&rect,&text) || failure)return 52;
    /* Device conversion owns custom RGB reduction, independent of any app. */
    fail_text=0;color_case=1;text.columns=text.rows=text.stride=text.capacity=1;
    memset(source_colors,0,sizeof(source_colors));
    source_colors[0]=0x787cecUL;source_colors[1]=0xeceeeeUL;
    text.colors=source_colors;text.source_colors=1;
    cells[0].foreground=1;cells[0].background=0;
    device_bits=4;
    if(!mygames_win16_text_paint((HDC)1,&rect,&text) ||
        last_background!=0xff5555UL || last_foreground!=0xffffffUL)return 53;
    device_bits=8;
    if(!mygames_win16_text_paint((HDC)1,&rect,&text) ||
        last_background!=0xec7c78UL || last_foreground!=0xeeeeecUL)return 54;
    scenario=2;quit=exit_flag=step=failed_timer=0;dirty=1;paints=0;wake=16;
    app.width=app.height=4;app.available_views=1;view_kind=0;
    hooks.started=after_paint;hooks.close=controlled_close;
    if(mygames_win16_run_lifecycle(1,0,1,&app,&hooks) || failure ||
        hooks_started!=1 || hooks_closed!=4 || !reentrant_updates || allocs)return failure?failure:63;
    return 0;
}
