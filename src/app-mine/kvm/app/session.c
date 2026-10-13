#include "session.h"
#include "../text/scene.h"
#include "../graphics/scene.h"
#include <string.h>
static int command(unsigned short key)
{
    switch(key){
    case MYGAMES_KVM_KEY_TAB:return 9;
    case MYGAMES_KVM_KEY_ESCAPE:return 27;
    case MYGAMES_KVM_KEY_F1:case MYGAMES_KVM_KEY_H:return 'h';
    case MYGAMES_KVM_KEY_F2:case MYGAMES_KVM_KEY_N:return 'n';
    case MYGAMES_KVM_KEY_M:return 'm';
    case MYGAMES_KVM_KEY_Q:return 'q';
    case MYGAMES_KVM_KEY_1:return '1';
    case MYGAMES_KVM_KEY_2:return '2';
    case MYGAMES_KVM_KEY_3:return '3';
    default:return 0;
    }
}
void mine_session_init(MineSession *s,unsigned long seed,int text_mode)
{
    memset(s,0,sizeof(*s));app_init(&s->app,seed);s->text_mode=(unsigned char)(text_mode!=0);
    s->text.cells=s->cells;s->text.columns=80;s->text.rows=25;
    s->text.stride=80;s->text.capacity=2000;
}
void mine_session_event(MineSession *s,const struct mygames_kvm_input_event *e)
{
    int key;
    if(e->kind==MYGAMES_KVM_INPUT_RESIZE)s->app.dirty=1;
    if(e->kind==MYGAMES_KVM_INPUT_KEY&&e->physical_code==MYGAMES_KVM_KEY_TAB){
        if(!e->down){s->tab_down=0;return;}
        if(s->tab_down||e->repeat)return;
        s->tab_down=1;
    }
    if(e->kind==MYGAMES_KVM_INPUT_CANCEL||(e->kind==MYGAMES_KVM_INPUT_FOCUS&&!e->down))app_cancel(&s->app);
    else if((e->kind==MYGAMES_KVM_INPUT_KEY&&e->down&&!e->repeat)||e->kind==MYGAMES_KVM_INPUT_COMMAND){
        key=command(e->physical_code);if(key)app_key(&s->app,key);
    }else if(e->kind==MYGAMES_KVM_INPUT_MOUSE_MOVE||e->kind==MYGAMES_KVM_INPUT_MOUSE_BUTTON){
        if(e->coordinate_space==MYGAMES_KVM_COORD_TEXT_CELLS)text_mouse(&s->app,e->x,e->y,e->buttons&7);
        else if(e->coordinate_space==MYGAMES_KVM_COORD_CLIENT_PIXELS)mine_graphics_mouse(&s->app,e->x,e->y,e->buttons&7);
    }
}
void mine_session_update(MineSession *s,unsigned long now)
{
    unsigned long elapsed;
    int old=s->app.game.seconds;
    if(!s->clock_ready||!s->app.game.started){s->last_second=now;s->clock_ready=1;}
    elapsed=(now-s->last_second)&0xffffffffUL;
    if(elapsed>=1000UL){
        s->last_second=now-elapsed%1000UL;
        elapsed/=1000UL;if(elapsed>999UL)elapsed=999UL;
        while(elapsed--)mine_second(&s->app.game);
    }
    if(old!=s->app.game.seconds)s->app.dirty=1;
}
const struct mygames_kvm_text_frame *mine_session_text(MineSession *s)
{
    text_scene(&s->app,s->cells);return &s->text;
}
