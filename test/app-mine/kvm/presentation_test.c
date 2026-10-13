#include "kvm/app/session.h"
#include "kvm/graphics/scene.h"
#include "kvm/io/number.h"
#include <stdio.h>
#include <string.h>
static MineSession s;
static unsigned char pixels[504*8+2];
int main(void)
{
    const struct mygames_kvm_text_frame *text;
    struct mygames_kvm_video_band band;
    unsigned long hash=2166136261UL;
    int level,y,i,h,rows,w;
    char number[8];
    if(mine_number(number,-32768,3)!=number+6||strcmp(number,"-32768"))return 8;
    mine_number(number,0,3);if(strcmp(number,"000"))return 9;
    mine_number(number,-2,3);if(strcmp(number,"-02"))return 10;
    mine_number(number,32767,1);if(strcmp(number,"32767"))return 11;
    mine_session_init(&s,1,1);
    for(level=0;level<3;++level){
        app_new(&s.app,level);text=mine_session_text(&s);
        if(!mygames_kvm_text_valid(text))return 1;
        for(i=0;i<2000;++i)if(s.cells[i].foreground>15||s.cells[i].background>15)return 2;
        w=mine_graphics_width(&s.app);h=mine_graphics_height(&s.app);
        for(y=0;y<h;y+=rows){
            rows=h-y;if(rows>8)rows=8;pixels[0]=231;pixels[w*rows+1]=231;
            if(!mine_graphics_rows(&s.app,(unsigned short)y,(unsigned short)rows,pixels+1,sizeof(pixels)-2,&band))return 3;
            if(pixels[0]!=231||pixels[w*rows+1]!=231||!mygames_kvm_band_valid(&band,(unsigned short)h))return 4;
            for(i=0;i<w*rows;++i){if(pixels[i+1]>15)return 5;hash=((hash^pixels[i+1])*16777619UL)&0xffffffffUL;}
        }
        s.app.help=1;mine_session_text(&s);
        if(!mine_graphics_rows(&s.app,50,8,pixels,sizeof(pixels),&band))return 6;
    }
    /* Cover each original authored tile: numeric borders, flag/question,
     * explosion, unflagged mine and wrong flag. No imported board encoding. */
    app_new(&s.app,0);memset(s.app.game.hazard,0,sizeof(s.app.game.hazard));
    for(i=0;i<9;++i)s.app.game.hazard[i]=1;
    s.app.game.cover[9]=MINE_MARKED;s.app.game.cover[10]=MINE_UNCERTAIN;
    s.app.game.cover[11]=MINE_OPEN;s.app.game.cover[12]=MINE_OPEN;
    s.app.gesture=0;mine_session_text(&s);
    s.app.gesture=1;s.app.hover_x=1;s.app.hover_y=1;
    for(level=0;level<3;++level){
        s.app.game.state=level;s.app.game.exploded=0;s.app.menu=level==1;
        mine_session_text(&s);
        h=mine_graphics_height(&s.app);
        for(y=0;y<h;y+=rows){rows=h-y;if(rows>8)rows=8;
            if(!mine_graphics_rows(&s.app,(unsigned short)y,(unsigned short)rows,pixels,sizeof(pixels),&band))return 12;
        }
    }
    if(mine_graphics_rows(&s.app,0,0,pixels,sizeof(pixels),&band)||
        mine_graphics_rows(&s.app,0,8,pixels,1,&band)||
        mine_graphics_rows(&s.app,400,8,pixels,sizeof(pixels),&band))return 7;
    printf("presentation bounds/colors/bands passed hash=%08lx\n",hash);return 0;
}
