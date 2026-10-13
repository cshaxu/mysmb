#include <windows.h>
#include <string.h>
#include "../../app/session.h"
#include "../../graphics/scene.h"
#include "kvm/color.h"
#include "win16/host.h"

static MineSession session;
static struct mygames_win16_application application;
static unsigned char pixels[504*8];
static unsigned long palette[16];
static int client_width,client_height;
static int sized_width,sized_height,sized_view=-1;

/* Window size is Mine presentation policy. The retained USER/GDI host still
 * owns painting and delivers every resulting physical resize/input event. */
static void size_view(void)
{
    HWND window;
    RECT rect;
    char name[32];
    int w,h,maximum_w,maximum_h;
    if(sized_width==application.width&&sized_height==application.height&&sized_view==session.text_mode)return;
    window=GetActiveWindow();
    if(!window||!GetClassName(window,name,sizeof(name))||strcmp(name,"MygamesWin16"))return;
    rect.left=rect.top=rect.right=rect.bottom=0;
    AdjustWindowRect(&rect,WS_OVERLAPPEDWINDOW,TRUE);
    maximum_w=GetSystemMetrics(SM_CXSCREEN)-(rect.right-rect.left)-8;
    maximum_h=GetSystemMetrics(SM_CYSCREEN)-(rect.bottom-rect.top)-8;
    w=session.text_mode?640:application.width;
    h=session.text_mode?400:application.height;
    if(!session.text_mode&&w*2<=maximum_w&&h*2<=maximum_h){w*=2;h*=2;}
    if(w>maximum_w)w=maximum_w;if(h>maximum_h)h=maximum_h;
    sized_width=application.width;sized_height=application.height;sized_view=session.text_mode;
    SetWindowPos(window,0,0,0,w+rect.right-rect.left,h+rect.bottom-rect.top,
        SWP_NOZORDER|SWP_NOACTIVATE);
}
static struct mygames_win16_menu_item game_items[]={
    {"&New\tF2",MYGAMES_KVM_KEY_N,0,0},
    {"&Beginner\t1",MYGAMES_KVM_KEY_1,0,0},
    {"&Intermediate\t2",MYGAMES_KVM_KEY_2,0,0},
    {"&Expert\t3",MYGAMES_KVM_KEY_3,0,0},
    {"&Marks (?)\tM",MYGAMES_KVM_KEY_M,0,0},
    {"&Text / graphics\tTab",MYGAMES_KVM_KEY_TAB,0,0},
    {"E&xit\tQ",MYGAMES_KVM_KEY_Q,0,0}
};
static const struct mygames_win16_menu_item help_items[]={
    {"&Instructions\tF1",MYGAMES_KVM_KEY_H,0,0}
};
static const struct mygames_win16_menu menus[]={
    {"&Game",game_items,7},{"&Help",help_items,1}
};
static void input(void *context,const struct mygames_kvm_input_event *e)
{
    struct mygames_kvm_input_event mapped=*e;
    if(e->kind==MYGAMES_KVM_INPUT_RESIZE){client_width=e->x;client_height=e->y;}
    if((e->kind==MYGAMES_KVM_INPUT_MOUSE_BUTTON||e->kind==MYGAMES_KVM_INPUT_MOUSE_MOVE)&&
        client_width>0&&client_height>0){
        mapped.x=e->x<0?-1:(short)((long)e->x*(session.text_mode?80:application.width)/client_width);
        mapped.y=e->y<0?-1:(short)((long)e->y*(session.text_mode?25:application.height)/client_height);
        if(session.text_mode)mapped.coordinate_space=MYGAMES_KVM_COORD_TEXT_CELLS;
    }
    mine_session_event((MineSession *)context,&mapped);
}
static void update(void *context,unsigned long now,struct mygames_win16_update *result)
{
    MineSession *s=(MineSession *)context;
    int i;
    mine_session_update(s,now);
    if(s->app.switch_view){s->app.switch_view=0;s->text_mode=!s->text_mode;s->app.dirty=1;}
    application.width=(unsigned short)mine_graphics_width(&s->app);
    application.height=(unsigned short)mine_graphics_height(&s->app);
    size_view();
    for(i=0;i<3;++i)game_items[i+1].checked=(unsigned char)(i==s->app.level);
    game_items[4].checked=(unsigned char)s->app.game.questions;
    result->dirty=(unsigned char)s->app.dirty;s->app.dirty=0;
    result->wake_ms=(unsigned short)(s->app.game.started&&s->app.game.state==MINE_PLAYING?100:0);
}
static unsigned char presentation(void *context){return ((MineSession *)context)->text_mode;}
static unsigned char quit(void *context){return (unsigned char)((MineSession *)context)->app.quit;}
static const struct mygames_kvm_text_frame FAR *text(void *context)
{
    return mine_session_text((MineSession *)context);
}
static int graphics(void *context,struct mygames_kvm_video_band *band)
{
    return mine_graphics_rows(&((MineSession *)context)->app,band->first,band->rows,
        pixels,sizeof(pixels),band);
}
int PASCAL WinMain(HINSTANCE instance,HINSTANCE previous,LPSTR command,int show)
{
    int i;
    (void)command;
    mine_session_init(&session,GetTickCount(),0);
    for(i=0;i<16;++i)palette[i]=mygames_kvm_color_text_rgb((unsigned char)i);
    application.context=&session;application.title="Mine";
    application.available_views=MYGAMES_WIN16_VIEW_GRAPHICS|MYGAMES_WIN16_VIEW_TEXT;
    application.input=input;application.update=update;application.presentation=presentation;
    application.exit_requested=quit;application.text=text;application.graphics=graphics;
    application.palette=palette;application.palette_count=16;
    application.width=(unsigned short)mine_graphics_width(&session.app);
    application.height=(unsigned short)mine_graphics_height(&session.app);
    application.menus=menus;application.menu_count=2;
    return mygames_win16_run(instance,previous,show,&application);
}
