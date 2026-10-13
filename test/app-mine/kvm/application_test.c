#include "kvm/app/session.h"
#include "kvm/graphics/scene.h"
#include "kvm/text/scene.h"
#include <stdio.h>
#include <string.h>
static MineSession s;
static int checks,failures;
#define CHECK(e) do {++checks;if(!(e)){++failures;printf("FAIL %d: %s\n",__LINE__,#e);}} while(0)
static void key(int code)
{
    struct mygames_kvm_input_event e;
    memset(&e,0,sizeof(e));e.kind=MYGAMES_KVM_INPUT_KEY;e.down=1;e.physical_code=(unsigned short)code;
    mine_session_event(&s,&e);
}
int main(void)
{
    struct mygames_kvm_input_event e;
    MineApp *a=&s.app;
    mine_session_init(&s,1,1);CHECK(a->game.width==9&&a->game.mines==10&&s.text_mode==1);
    key(MYGAMES_KVM_KEY_2);CHECK(a->game.width==16&&a->game.mines==40);
    key(MYGAMES_KVM_KEY_3);CHECK(a->game.width==30&&a->game.mines==99);
    key(MYGAMES_KVM_KEY_M);CHECK(!a->game.questions);
    key(MYGAMES_KVM_KEY_1);CHECK(a->game.width==9&&!a->game.questions);
    key(MYGAMES_KVM_KEY_H);CHECK(a->help);key(MYGAMES_KVM_KEY_ESCAPE);CHECK(!a->help&&!a->quit);
    key(MYGAMES_KVM_KEY_F1);CHECK(a->help);key(MYGAMES_KVM_KEY_F2);CHECK(!a->help);
    memset(&e,0,sizeof(e));e.kind=MYGAMES_KVM_INPUT_KEY;e.down=1;e.repeat=1;e.physical_code=MYGAMES_KVM_KEY_TAB;
    mine_session_event(&s,&e);CHECK(!a->switch_view);
    key(MYGAMES_KVM_KEY_TAB);CHECK(a->switch_view);a->switch_view=0;
    app_mouse(a,0,0,1);CHECK(a->gesture&&app_tile(a,0,0)==0&&!a->game.opened);
    e.kind=MYGAMES_KVM_INPUT_CANCEL;mine_session_event(&s,&e);
    app_mouse(a,0,0,0);CHECK(!a->gesture&&!a->game.opened);
    app_mouse(a,0,0,1);app_mouse(a,-1,-1,0);CHECK(!a->game.opened);
    app_mouse(a,0,0,2);CHECK(a->game.flags==1);app_mouse(a,0,0,0);
    app_mouse(a,0,0,2);app_mouse(a,0,0,0);CHECK(app_tile(a,0,0)==MINE_CLOSED);
    mine_session_update(&s,100);app_mouse(a,0,0,1);app_mouse(a,0,0,0);CHECK(a->game.started&&a->game.opened>0);
    mine_session_update(&s,1100);CHECK(a->game.seconds==1);
    key(MYGAMES_KVM_KEY_N);mine_session_update(&s,4000);CHECK(!a->game.started&&a->game.seconds==0);
    mine_graphics_mouse(a,mine_graphics_width(a)/2,20,1);CHECK(a->down_face);
    mine_graphics_mouse(a,-1,-1,0);CHECK(!a->down_face);
    text_mouse(a,34,0,1);CHECK(a->menu);text_mouse(a,34,0,0);key(MYGAMES_KVM_KEY_ESCAPE);CHECK(!a->menu);
    key(MYGAMES_KVM_KEY_H);mine_graphics_mouse(a,20,70,1);mine_graphics_mouse(a,20,70,0);CHECK(!a->help);
    e.kind=MYGAMES_KVM_INPUT_COMMAND;e.physical_code=MYGAMES_KVM_KEY_3;mine_session_event(&s,&e);CHECK(a->level==2);
    e.kind=MYGAMES_KVM_INPUT_MOUSE_BUTTON;e.coordinate_space=MYGAMES_KVM_COORD_TEXT_CELLS;e.x=10;e.y=4;e.buttons=2;
    mine_session_event(&s,&e);CHECK(a->game.flags==1);
    e.kind=MYGAMES_KVM_INPUT_FOCUS;e.down=0;mine_session_event(&s,&e);CHECK(!a->gesture);
    mine_session_init(&s,1,0);key(MYGAMES_KVM_KEY_A);CHECK(!a->quit);
    e.kind=MYGAMES_KVM_INPUT_RESIZE;mine_session_event(&s,&e);CHECK(a->dirty);
    e.kind=MYGAMES_KVM_INPUT_KEY;e.physical_code=MYGAMES_KVM_KEY_TAB;e.down=0;mine_session_event(&s,&e);
    e.kind=MYGAMES_KVM_INPUT_MOUSE_BUTTON;e.coordinate_space=MYGAMES_KVM_COORD_CLIENT_PIXELS;
    e.x=20;e.y=64;e.buttons=2;mine_session_event(&s,&e);CHECK(a->game.flags==1);
    e.buttons=0;mine_session_event(&s,&e);
    mine_graphics_mouse(a,-1,64,1);mine_graphics_mouse(a,-1,64,0);CHECK(!a->game.opened);
    mine_graphics_mouse(a,mine_graphics_width(a)/2,20,1);
    mine_graphics_mouse(a,mine_graphics_width(a)/2,20,0);CHECK(!a->game.flags);
    app_mouse(a,1,1,4);CHECK(a->chord&&app_tile(a,1,1)==0);
    app_mouse(a,1,1,0);CHECK(!a->gesture);
    app_mouse(a,1,1,1);app_mouse(a,1,1,3);CHECK(a->chord);
    app_mouse(a,1,1,2);app_mouse(a,1,1,0);CHECK(!a->suppress);
    a->game.cover[10]=MINE_UNCERTAIN;
    app_mouse(a,1,1,1);CHECK(app_tile(a,1,1)==9);app_cancel(a);app_mouse(a,1,1,0);
    /* Text menu and face hit regions belong to the text presenter. */
    text_mouse(a,38,0,1);text_mouse(a,38,0,0);CHECK(a->help);
    text_mouse(a,12,7,1);text_mouse(a,12,7,0);CHECK(!a->help);
    text_mouse(a,40,2,1);text_mouse(a,40,2,0);CHECK(!a->game.opened);
    {int row;for(row=2;row<=7;++row){
        app_new(a,0);a->buttons=0;a->suppress=0;a->menu=1;
        text_mouse(a,32,row,1);text_mouse(a,32,row,0);
        CHECK(!a->menu);
    }}
    mine_session_init(&s,1,0);mine_session_update(&s,0xfffffff0UL);
    a->game.started=1;mine_session_update(&s,0x3d8UL);CHECK(a->game.seconds==1);
    mine_session_update(&s,2000000UL);CHECK(a->game.seconds==999);
    key(MYGAMES_KVM_KEY_ESCAPE);CHECK(a->quit);
    key(MYGAMES_KVM_KEY_Q);CHECK(a->quit);
    printf("application checks=%d failures=%d\n",checks,failures);return failures?1:0;
}
