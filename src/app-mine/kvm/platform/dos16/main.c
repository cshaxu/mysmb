#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../app/session.h"
#include "dos16/host.h"
#include "dos16/mouse.h"
#include "dos16/raw_keyboard.h"
#include "dos16/text_cells.h"

static MineSession session;
static struct mygames_dos16_mouse mouse;
static struct mygames_dos16_set1_keyboard keyboard;
/* IRQ records only bytes; app state is never changed from an interrupt. */
static volatile unsigned char scans[64],head,tail,overflow;
static void scan(void *context,unsigned char value)
{
    unsigned char next=(unsigned char)((head+1U)&63U);
    (void)context;
    if(next==tail)overflow=1;
    else {scans[head]=value;head=next;}
}
static unsigned short key(unsigned char value)
{
    switch(value){
    case 1:return MYGAMES_KVM_KEY_ESCAPE;
    case 2:return MYGAMES_KVM_KEY_1;
    case 3:return MYGAMES_KVM_KEY_2;
    case 4:return MYGAMES_KVM_KEY_3;
    case 15:return MYGAMES_KVM_KEY_TAB;
    case 16:return MYGAMES_KVM_KEY_Q;
    case 35:return MYGAMES_KVM_KEY_H;
    case 49:return MYGAMES_KVM_KEY_N;
    case 50:return MYGAMES_KVM_KEY_M;
    case 59:return MYGAMES_KVM_KEY_F1;
    case 60:return MYGAMES_KVM_KEY_F2;
    default:return 0;
    }
}
int main(void)
{
    struct mygames_dos16_video_state video;
    struct mygames_dos16_key_transition transition;
    struct mygames_kvm_input_event e;
    unsigned short bytes;
    unsigned char value;
    unsigned long stamp,last,delta,milliseconds=0,remainder=0;
    void *saved;
    int keyboard_open=0,result=1;
    bytes=mygames_dos16_mouse_storage(&mygames_dos16_mouse_native_bus,NULL);
    if(!bytes){puts("Mine requires an installed DOS mouse driver.");return 1;}
    saved=malloc(bytes);if(!saved){puts("Not enough memory for mouse state.");return 1;}
    if(!mygames_dos16_mouse_open(&mouse,&mygames_dos16_mouse_native_bus,NULL,saved,bytes))goto cleanup;
    mygames_dos16_video_capture(&video);
    if(!mygames_dos16_text_mode(25))goto restore;
    if(!mygames_dos16_mouse_range(&mouse,639,199,8,8,MYGAMES_KVM_COORD_TEXT_CELLS))goto restore;
    mine_session_init(&session,mygames_dos16_clock_stamp(),1);
    mygames_dos16_set1_keyboard_initialize(&keyboard);
    if(!mygames_dos16_keyboard_open(scan,NULL))goto restore;
    keyboard_open=1;last=mygames_dos16_clock_stamp();
    while(!session.app.quit){
        if(overflow){
            _disable();tail=head;overflow=0;_enable();
            app_cancel(&session.app);mygames_dos16_set1_keyboard_initialize(&keyboard);
        }
        while(tail!=head){
            value=scans[tail];tail=(unsigned char)((tail+1U)&63U);
            if(mygames_dos16_set1_keyboard_scan(&keyboard,value,&transition)&&!transition.extended){
                e.kind=MYGAMES_KVM_INPUT_KEY;e.physical_code=key(transition.scan);
                e.down=transition.down;e.repeat=transition.repeat;
                mine_session_event(&session,&e);
            }
        }
        while(mygames_dos16_mouse_poll(&mouse,&e))mine_session_event(&session,&e);
        session.app.switch_view=0; /* DOS Mine declares text-only presentation. */
        stamp=mygames_dos16_clock_stamp();delta=stamp-last;last=stamp;
        if(delta<11931820UL){
            /* PIT ticks to milliseconds, retaining sub-ms remainder. */
            remainder+=delta;milliseconds+=remainder/1193UL;remainder%=1193UL;
        }
        mine_session_update(&session,milliseconds);
        if(session.app.dirty){
            mygames_dos16_mouse_visible(&mouse,0);
            mygames_dos16_text_cells(mine_session_text(&session),(unsigned short far *)0xb8000000UL);
            mygames_dos16_mouse_visible(&mouse,1);session.app.dirty=0;
        }
        _asm {sti}
        _asm {hlt}
    }
    result=0;
restore:
    if(keyboard_open)mygames_dos16_keyboard_close();
    mygames_dos16_mouse_close(&mouse);mygames_dos16_video_restore(&video);
cleanup:
    free(saved);return result;
}
