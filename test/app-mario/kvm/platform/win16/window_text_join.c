/* Real Win16 composition root with a controlled host boundary, not included C.
 * Device behavior belongs to lib tests; this fixture owns Mario's bindings. */
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "win16/host.h"
#include "win16/audio.h"
#include "win16/file.h"
int PASCAL WinMain(HINSTANCE,HINSTANCE,LPSTR,int);
static unsigned long now;
static int allocations,live,fail_alloc,locks,fail_lock,host_calls;
static unsigned char baseline[61440],current[61440];
#define CHECK(c) do {if(!(c)){fprintf(stderr,"Win16 app join: %d\n",__LINE__);exit(1);}}while(0)
HGLOBAL GlobalAlloc(UINT flags,DWORD bytes)
{void *p;(void)flags;if(++allocations==fail_alloc)return 0;p=calloc(1,(size_t)bytes);if(p)++live;return p;}
void *GlobalLock(HGLOBAL p){return ++locks==fail_lock?0:p;}
int GlobalUnlock(HGLOBAL p){(void)p;return 1;}
HGLOBAL GlobalFree(HGLOBAL p){if(p){--live;free(p);}return 0;}
DWORD GetTickCount(void){return now;}
int mygames_win16_executable_path(mygames_kvm_u16 instance,char *p,mygames_kvm_u16 n)
{(void)instance;CHECK(n>20U);strcpy(p,"Z:/unused/mysmb.exe");return 1;}
int mygames_win16_file_replace(const char *a,const char *b){(void)a;(void)b;return 0;}
int mygames_win16_audio_open(unsigned long rate,mygames_kvm_u16 samples,mygames_kvm_u16 count)
{CHECK(rate && samples && count);return 0;}
int mygames_win16_audio_submit(const mygames_kvm_u8 *p,mygames_kvm_u16 n)
{CHECK(p && n);return 0;}
int mygames_win16_audio_reset(void){return 1;}
void mygames_win16_audio_close(void){}
static void event(const struct mygames_win16_application *a,unsigned char kind,
    unsigned short key,unsigned char down,unsigned char repeat)
{
    struct mygames_kvm_input_event e;
    memset(&e,0,sizeof(e));e.kind=kind;e.physical_code=key;e.down=down;e.repeat=repeat;
    a->input(a->context,&e);
}
static void pixels(const struct mygames_win16_application *a,unsigned char *out)
{
    struct mygames_kvm_video_band b;unsigned short y;
    for(y=0;y<240U;y+=8U){memset(&b,0,sizeof(b));b.first=y;b.rows=8U;
        CHECK(a->graphics(a->context,&b));CHECK(b.width==256U && b.rows==8U);
        memcpy(out+(unsigned long)y*256UL,b.pixels,2048U);}
}
int mygames_win16_run(HINSTANCE instance,HINSTANCE previous,int show,
    const struct mygames_win16_application *a)
{
    struct mygames_win16_update u;
    const struct mygames_kvm_text_frame *text;
    unsigned short i;unsigned char initial;
    (void)instance;(void)previous;(void)show;++host_calls;
    CHECK(a->available_views==3U && a->presentation && a->text);
    CHECK(a->presentation(a->context)==MYGAMES_KVM_PRESENTATION_GRAPHICS);
    event(a,MYGAMES_KVM_INPUT_FOCUS,0,1,0);
    for(i=0;i<120U;++i){now+=17UL;a->update(a->context,now,&u);}
    pixels(a,baseline);
    /* No game tick elapses while switching; composition must not write state. */
    for(i=0;i<4U;++i){
        initial=a->presentation(a->context);
        event(a,MYGAMES_KVM_INPUT_KEY,MYGAMES_KVM_KEY_TAB,1,0);
        CHECK(a->presentation(a->context)!=initial);
        a->update(a->context,now,&u);CHECK(u.dirty);
        a->update(a->context,now,&u);CHECK(!u.dirty);
        event(a,MYGAMES_KVM_INPUT_KEY,MYGAMES_KVM_KEY_TAB,1,1);
        CHECK(a->presentation(a->context)!=initial);
        event(a,MYGAMES_KVM_INPUT_KEY,MYGAMES_KVM_KEY_TAB,0,0);
        text=a->text(a->context);CHECK(mygames_kvm_text_valid(text));
        CHECK(text->columns==80U && text->rows==25U && text->source_colors);
        pixels(a,current);CHECK(!memcmp(baseline,current,sizeof(current)));
    }
    event(a,MYGAMES_KVM_INPUT_FOCUS,0,0,0);
    event(a,MYGAMES_KVM_INPUT_KEY,MYGAMES_KVM_KEY_TAB,1,0);
    CHECK(a->presentation(a->context)==MYGAMES_KVM_PRESENTATION_GRAPHICS);
    a->update(a->context,now,&u);CHECK(!u.dirty && !u.wake_ms);
    event(a,MYGAMES_KVM_INPUT_FOCUS,0,1,0);
    event(a,MYGAMES_KVM_INPUT_KEY,MYGAMES_KVM_KEY_TAB,1,1);
    CHECK(a->presentation(a->context)==MYGAMES_KVM_PRESENTATION_GRAPHICS);
    event(a,MYGAMES_KVM_INPUT_KEY,MYGAMES_KVM_KEY_TAB,0,0);
    event(a,MYGAMES_KVM_INPUT_KEY,MYGAMES_KVM_KEY_TAB,1,0);
    CHECK(a->presentation(a->context)==MYGAMES_KVM_PRESENTATION_TEXT);
    event(a,MYGAMES_KVM_INPUT_KEY,MYGAMES_KVM_KEY_ESCAPE,1,0);
    CHECK(a->exit_requested(a->context));return 0;
}
int main(void)
{
    int mode,result;
    for(mode=0;mode<6;++mode){
        now=0;allocations=locks=host_calls=0;fail_alloc=fail_lock=0;
        if(mode==1)fail_alloc=1; /* required snapshot */
        if(mode==2)fail_alloc=2; /* required text workspace */
        if(mode==3)fail_lock=2;
        if(mode==4)fail_alloc=3; /* optional PPU background */
        if(mode==5)fail_lock=3;
        result=WinMain(1,0,"",1);CHECK(live==0);
        CHECK(result==((mode>=1 && mode<=3)?2:0));
        CHECK(host_calls==((mode>=1 && mode<=3)?0:1));
    }
    puts("Win16 Mario Tab/text/graphics/focus/allocation joins passed");return 0;
}
