#include "app.h"
#include <string.h>

void app_cancel(MineApp *a)
{
    a->gesture=0;a->chord=0;a->suppress=a->buttons!=0;
    a->buttons=0;a->down_face=0;a->dirty=1;
}
void app_new(MineApp *a,int level)
{
    int questions=a->game.questions;
    a->level=level;a->seed+=7919UL;
    if(level==0)mine_new(&a->game,9,9,10,a->seed);
    else if(level==1)mine_new(&a->game,16,16,40,a->seed);
    else mine_new(&a->game,30,16,99,a->seed);
    a->game.questions=questions;app_cancel(a);a->menu=0;a->help=0;
}
void app_init(MineApp *a,unsigned long seed)
{
    memset(a,0,sizeof(*a));a->seed=seed;a->game.questions=1;
    app_new(a,0);a->suppress=0;
}
void app_mouse(MineApp *a,int x,int y,int buttons)
{
    int old=a->buttons,newpress=buttons&~old;
    a->hover_x=x;a->hover_y=y;a->buttons=buttons;
    if(a->suppress){if(!buttons)a->suppress=0;return;}
    if(a->game.state!=MINE_PLAYING)return;
    if(a->gesture){
        if((buttons&3)==3||(buttons&MINE_MIDDLE))a->chord=1;
        if((old&~buttons)!=0){
            if(a->chord)mine_chord(&a->game,x,y);
            else mine_reveal(&a->game,x,y);
            a->gesture=0;a->chord=0;a->suppress=buttons!=0;
        }
    }else if((newpress&MINE_MIDDLE)||((buttons&3)==3)){
        a->gesture=1;a->chord=1;
    }else if(newpress&MINE_LEFT){a->gesture=1;a->chord=0;}
    else if(newpress&MINE_RIGHT)mine_mark(&a->game,x,y);
    a->dirty=1;
}
int app_tile(const MineApp *a,int x,int y)
{
    int tile=mine_sprite(&a->game,x,y);
    int dx=x-a->hover_x,dy=y-a->hover_y,pressed=0;
    if(a->gesture&&mine_inside(&a->game,a->hover_x,a->hover_y)){
        if(a->chord)pressed=dx>=-1&&dx<=1&&dy>=-1&&dy<=1;
        else pressed=dx==0&&dy==0;
    }
    if(pressed){
        if(tile==MINE_CLOSED)tile=0;
        else if(tile==MINE_QUESTION)tile=9;
    }
    return tile;
}
void app_key(MineApp *a,int key)
{
    if(key>='1'&&key<='3'){app_new(a,key-'1');return;}
    if(key=='n'||key=='N'||key==0x3c00){app_new(a,a->level);return;}
    if(key=='q'||key=='Q'){a->quit=1;return;}
    if(key==27){
        if(a->help||a->menu){a->help=0;a->menu=0;}
        else a->quit=1;
    }
    if(key==9){app_cancel(a);a->switch_view=1;}
    if(key==0x3b00||key=='h'||key=='H'){app_cancel(a);a->help=!a->help;}
    if(key=='m'||key=='M'){app_cancel(a);a->game.questions=!a->game.questions;}
    a->dirty=1;
}
