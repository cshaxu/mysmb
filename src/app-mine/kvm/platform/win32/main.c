#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string.h>
#include "../../app/session.h"
#include "../../graphics/scene.h"
#include "kvm/color.h"
#include "win32/window.h"
#include "win32/launch.h"
#include "win32/text_console.h"

static MineSession session;
static struct mygames_win32_text_console console;
static struct mygames_win32_input keys;
static struct mygames_win32_window_input pointer;
static struct mygames_win32_window_geometry geometry;
static DWORD pixels[504UL*396UL];
static unsigned char band_pixels[504*16];
static unsigned short width,height;
static HWND window;
static HMENU game_menu;

static void create_menu(void)
{
    HMENU bar=CreateMenu(),help=CreatePopupMenu();
    game_menu=CreatePopupMenu();
    AppendMenu(game_menu,MF_STRING,MYGAMES_KVM_KEY_N,"&New\tF2");
    AppendMenu(game_menu,MF_STRING,MYGAMES_KVM_KEY_1,"&Beginner\t1");
    AppendMenu(game_menu,MF_STRING,MYGAMES_KVM_KEY_2,"&Intermediate\t2");
    AppendMenu(game_menu,MF_STRING,MYGAMES_KVM_KEY_3,"&Expert\t3");
    AppendMenu(game_menu,MF_STRING,MYGAMES_KVM_KEY_M,"&Marks (?)\tM");
    AppendMenu(game_menu,MF_STRING,MYGAMES_KVM_KEY_TAB,"&Text / graphics\tTab");
    AppendMenu(game_menu,MF_STRING,MYGAMES_KVM_KEY_Q,"E&xit\tQ");
    AppendMenu(help,MF_STRING,MYGAMES_KVM_KEY_H,"&Instructions\tF1");
    AppendMenu(bar,MF_POPUP,(UINT_PTR)game_menu,"&Game");
    AppendMenu(bar,MF_POPUP,(UINT_PTR)help,"&Help");SetMenu(window,bar);
    mygames_win32_window_initial_client(window,&geometry);
}

static void input(void *context,HWND target,const struct mygames_kvm_input_event *event)
{
    struct mygames_kvm_input_event e=*event;
    RECT client;
    (void)context;
    if(e.coordinate_space==MYGAMES_KVM_COORD_CLIENT_PIXELS&&
        (e.kind==MYGAMES_KVM_INPUT_MOUSE_BUTTON||e.kind==MYGAMES_KVM_INPUT_MOUSE_MOVE)){
        GetClientRect(target,&client);
        if(client.right>0&&client.bottom>0){
            /* Preserve negative captured coordinates rather than rounding into cell0. */
            e.x=e.x<0?-1:(short)((long)e.x*width/client.right);
            e.y=e.y<0?-1:(short)((long)e.y*height/client.bottom);
        }
    }
    mine_session_event(&session,&e);
}
static LRESULT CALLBACK procedure(HWND target,UINT message,WPARAM word,LPARAM detail)
{
    LRESULT result;
    if(message==WM_CLOSE){session.app.quit=1;return 0;}
    if(message==WM_PAINT){mygames_win32_window_paint(target,pixels,width,height,504UL*396UL);return 0;}
    if(message==WM_PRINTCLIENT){
        RECT client;GetClientRect(target,&client);
        mygames_win32_pixels_present((HDC)word,&client,pixels,width,height,504UL*396UL);return 0;
    }
    if(message==WM_ERASEBKGND)return 1;
    if(mygames_win32_window_event(target,message,word,detail,&pointer,&keys,
        &geometry,input,NULL,&result))return result;
    return DefWindowProc(target,message,word,detail);
}
static void compose(void)
{
    struct mygames_kvm_video_band band;
    unsigned short y,rows,i;
    unsigned long offset;
    width=(unsigned short)mine_graphics_width(&session.app);
    height=(unsigned short)mine_graphics_height(&session.app);
    for(y=0;y<height;y=(unsigned short)(y+rows)){
        rows=(unsigned short)(height-y);if(rows>16)rows=16;
        if(!mine_graphics_rows(&session.app,y,rows,band_pixels,sizeof(band_pixels),&band))return;
        offset=(unsigned long)y*width;
        for(i=0;i<width*rows;++i)pixels[offset+i]=mygames_kvm_color_text_rgb(band_pixels[i]);
    }
}
static int text_view(void)
{
    int ok;
    if(console.opened)ok=mygames_win32_text_console_resume(&console);
    else ok=mygames_win32_text_console_open_profile(&console,window,25,"Mine");
    if(!ok)return 0;
    session.text_mode=1;ShowWindow(window,SW_HIDE);
    if(console.window_usable){ShowWindow(console.window,SW_SHOW);SetForegroundWindow(console.window);}
    session.app.dirty=1;return 1;
}
static void graphics_view(void)
{
    if(console.opened&&!console.suspended)mygames_win32_text_console_suspend(&console);
    if(console.borrowed&&console.window_usable)ShowWindow(console.window,SW_SHOWNA);
    session.text_mode=0;ShowWindow(window,SW_SHOW);SetForegroundWindow(window);
    session.app.dirty=1;
}
int main(int argc,char **argv)
{
    MSG message;
    struct mygames_kvm_input_event event;
    int text=mygames_win32_parent_console_available(),i,presented;
    unsigned short old_width,old_height;
    for(i=1;i<argc;++i){
        if(!strcmp(argv[i],"--text"))text=1;
        else if(!strcmp(argv[i],"--window"))text=0;
    }
    mine_session_init(&session,GetTickCount(),0);
    compose();mygames_win32_input_initialize(&keys);
    mygames_win32_window_enable_dpi();
    mygames_win32_window_geometry_initialize(&geometry,width,height,1,2);
    window=mygames_win32_window_create(GetModuleHandle(NULL),"MyGamesMine","Mine",procedure,&geometry);
    if(!window)return 1;
    create_menu();
    if(text){if(!text_view())graphics_view();}
    else {
        /* Console-subsystem startup can own a newly allocated launcher console.
         * Open/suspend through the common session to preserve parent ownership. */
        if(GetConsoleWindow()){
            if(mygames_win32_text_console_open_profile(&console,window,25,"Mine"))
                mygames_win32_text_console_suspend(&console);
        }
        graphics_view();
    }
    while(!session.app.quit){
        while(PeekMessage(&message,NULL,0,0,PM_REMOVE)){
            if(message.message==WM_QUIT){session.app.quit=1;break;}
            TranslateMessage(&message);DispatchMessage(&message);
        }
        if(session.text_mode)while(mygames_win32_text_console_event(&console,&keys,&event))
            mine_session_event(&session,&event);
        mine_session_update(&session,GetTickCount());
        if(session.app.switch_view){
            session.app.switch_view=0;app_cancel(&session.app);
            if(session.text_mode)graphics_view();else text_view();
            mygames_win32_input_clear(&keys);
        }
        if(session.app.dirty){
            for(i=0;i<3;++i)CheckMenuItem(game_menu,MYGAMES_KVM_KEY_1+i,
                MF_BYCOMMAND|(session.app.level==i?MF_CHECKED:MF_UNCHECKED));
            CheckMenuItem(game_menu,MYGAMES_KVM_KEY_M,
                MF_BYCOMMAND|(session.app.game.questions?MF_CHECKED:MF_UNCHECKED));
            old_width=width;old_height=height;compose();
            if(old_width!=width||old_height!=height){
                mygames_win32_window_geometry_initialize(&geometry,width,height,1,2);
                mygames_win32_window_initial_client(window,&geometry);
            }
            session.app.dirty=0;
            if(session.text_mode){
                presented=mygames_win32_text_console_present(&console,mine_session_text(&session));
                if(presented==MYGAMES_WIN32_CONSOLE_LOST)graphics_view();
                else if(presented==MYGAMES_WIN32_CONSOLE_DEFER)session.app.dirty=1;
            }else InvalidateRect(window,NULL,FALSE);
        }
        MsgWaitForMultipleObjects(0,NULL,FALSE,20,QS_ALLINPUT);
    }
    mygames_win32_text_console_close(&console);DestroyWindow(window);return 0;
}
