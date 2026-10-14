#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "win16/host.h"
#include "win16/file.h"
#include "win16/audio.h"
static struct mygames_win16_application app;
static unsigned char row[504*8];
static unsigned long colors[16]={0UL,0x0000aaUL,0x00aa00UL,0x00aaaaUL,0xaa0000UL,0xaa00aaUL,0xaa5500UL,0xaaaaaaUL,0x555555UL,0x5555ffUL,0x55ff55UL,0x55ffffUL,0xff5555UL,0xff55ffUL,0xffff55UL,0xffffffUL};
static struct mygames_kvm_text_cell cells[80*25];
static struct mygames_kvm_text_frame text={cells,80,25,80,2000,1,colors};
static struct mygames_win16_menu_item items[]={{"&Probe",42,1,0}};
static struct mygames_win16_menu menus[]={{"&Device",items,1}};
static unsigned char done,view;
static unsigned short phase,buttons,cancels,commands,resizes,draws;
static int failure;
static unsigned long deadline;
static void input(void *context,const struct mygames_kvm_input_event *event)
{
    (void)context;
    if(event->kind==MYGAMES_KVM_INPUT_MOUSE_BUTTON) {
        ++buttons;
        if(buttons==1 && (event->x!=-2 || event->y!=5 || event->buttons!=1))failure=1;
        if(buttons==2 && (event->buttons!=3 || event->modifiers!=MYGAMES_KVM_MOD_SHIFT))failure=2;
    }
    if(event->kind==MYGAMES_KVM_INPUT_CANCEL)++cancels;
    if(event->kind==MYGAMES_KVM_INPUT_COMMAND && event->physical_code==42)++commands;
    if(event->kind==MYGAMES_KVM_INPUT_RESIZE)++resizes;
}
static void update(void *context,unsigned long now,struct mygames_win16_update *out)
{
    HWND window;
    (void)context;mygames_win16_audio_service(now);out->wake_ms=100;
    if(deadline && (long)(now-deadline)<0)return;
    deadline=now+3000UL;out->dirty=1;
    switch(phase++) {
    case 0:break;
    case 1:
        view=1;window=FindWindow("MygamesWin16",0);
        PostMessage(window,WM_LBUTTONDOWN,MK_LBUTTON,MAKELONG(0xfffe,5));
        PostMessage(window,WM_MOUSEMOVE,MK_LBUTTON|MK_RBUTTON|MK_SHIFT,MAKELONG(8,7));
        PostMessage(window,WM_CANCELMODE,0,0);
        PostMessage(window,WM_COMMAND,42,0);break;
    case 2:view=0;app.width=320;app.height=200;break;
    default:done=1;break;
    }
}
static unsigned char presentation(void *context){(void)context;return view;}
static unsigned char exiting(void *context){(void)context;return done;}
static const struct mygames_kvm_text_frame MYGAMES_KVM_FAR *text_view(void *context){(void)context;return &text;}
static int graphics(void *context,struct mygames_kvm_video_band *band)
{
    unsigned short x,y;
    (void)context;++draws;
    for(y=0;y<band->rows;++y)for(x=0;x<app.width;++x)
        row[y*app.width+x]=(unsigned char)(((x/16)+(band->first+y)/16)&15U);
    band->pixels=row;band->width=band->stride=app.width;band->capacity=sizeof(row);return 1;
}
static void started(void *p){(void)p;mygames_win16_audio_begin(11025UL,184U,8U,3U,1000UL);}
static int close_requested(void *p,int reason){(void)p;(void)reason;mygames_win16_audio_stop();return mygames_win16_audio_phase()==MYGAMES_AUDIO_CLOSED;}
int PASCAL WinMain(HINSTANCE instance,HINSTANCE previous,LPSTR command,int show)
{
    struct mygames_win16_lifecycle hooks;unsigned short i;int result;FILE *f;char path[260];
    (void)command;
    if(!mygames_win16_executable_path(instance,path,sizeof(path)))return 20;
    f=fopen("C:\\pcmtmp.dat","w");if(!f)return 21;fputs("neutral",f);fclose(f);
    if(!mygames_win16_file_replace("C:\\pcmtmp.dat","C:\\pcmfinal.dat"))return 22;

    for(i=0;i<2000;++i){cells[i].character=(unsigned char)(i&255U);cells[i].foreground=15;cells[i].background=(unsigned char)((i/80)&15U);}
    app.title="Neutral Win16 device probe";app.available_views=3;
    app.input=input;app.update=update;app.presentation=presentation;app.exit_requested=exiting;
    app.text=text_view;app.graphics=graphics;app.palette=colors;app.palette_count=16;
    app.width=504;app.height=323;app.menus=menus;app.menu_count=1;
    hooks.started=started;hooks.close=close_requested;
    result=mygames_win16_run_lifecycle(instance,previous,show,&app,&hooks);
    if(!failure && (buttons!=2 || cancels<1 || commands!=1 || !resizes || !draws))failure=3;
    f=fopen(result || failure?"C:\\neutral.bad":"C:\\neutral.ok","w");
    if(f){fprintf(f,"result=%d failure=%d phases=%u mouse=%u cancel=%u command=%u resize=%u bands=%u\n",result,failure,phase,buttons,cancels,commands,resizes,draws);fclose(f);}
    return result || failure;
}
