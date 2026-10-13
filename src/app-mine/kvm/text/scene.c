#include "scene.h"
#include <string.h>
#include "../io/number.h"
static void put(MineCell*c,int x,int y,int glyph,int fg,int bg){if(x>=0&&x<80&&y>=0&&y<25){c[y*80+x].character=(unsigned char)glyph;c[y*80+x].foreground=(unsigned char)fg;c[y*80+x].background=(unsigned char)bg;}}
static void str(MineCell*c,int x,int y,const char*s,int fg,int bg){while(*s)put(c,x++,y,*s++,fg,bg);}
static void panel(MineCell*c,int x,int y,int w,int h){int xx,yy;for(yy=y;yy<y+h;yy++)for(xx=x;xx<x+w;xx++)put(c,xx,yy,' ',0,7);for(xx=x;xx<x+w;xx++){put(c,xx,y,196,15,7);put(c,xx,y+h-1,196,8,7);}for(yy=y;yy<y+h;yy++){put(c,x,yy,179,15,7);put(c,x+w-1,yy,179,8,7);}put(c,x,y,218,15,7);put(c,x+w-1,y,191,8,7);put(c,x,y+h-1,192,15,7);put(c,x+w-1,y+h-1,217,8,7);}
void text_scene(const MineApp*a,MineCell*c){
 static const unsigned char colors[9]={0,9,2,12,1,4,3,0,8};
 int x,y,v,l=(80-(a->game.width*2+2))/2,w=a->game.width*2+2;char s[80];
 for(y=0;y<25;y++)for(x=0;x<80;x++)put(c,x,y,' ',7,1);
 for(x=l;x<l+w;x++)put(c,x,0,' ',0,7);
 str(c,l+1,0,"Game",0,7);str(c,l+8,0,"Help",0,7);
 panel(c,l,1,w,a->game.height+4);
 mine_number(s,a->game.mines-a->game.flags,3);str(c,l+2,2,s,12,0);
 mine_number(s,a->game.seconds,3);str(c,l+w-5,2,s,12,0);
 str(c,l+w/2-1,2,a->game.state==MINE_WON?"[B]":a->game.state==MINE_LOST?"[X]":a->gesture?"[O]":"[\001]",0,7);
 for(x=l+1;x<l+w-1;x++)put(c,x,3,196,8,7);
 for(y=0;y<a->game.height;y++)for(x=0;x<a->game.width;x++){
  int px=l+1+x*2,py=4+y;v=app_tile(a,x,y);
  put(c,px,py,' ',0,7);put(c,px+1,py,' ',0,7);
  if(v==15){
   put(c,px,py,'[',8,7);put(c,px+1,py,']',8,7);
  }else if(v==13)put(c,px,py,'?',0,7);
  else if(v==14)put(c,px,py,16,12,7);
  else if(v>=1&&v<=8)put(c,px,py,'0'+v,colors[v],7);
  else if(v==9)put(c,px,py,'?',0,7);
  else if(v==10)put(c,px,py,'*',0,7);
  else if(v==11)put(c,px,py,'X',12,7);
  else if(v==12){put(c,px,py,'*',0,12);put(c,px+1,py,' ',0,12);}
 }
 str(c,2,22,"L:Open R:Flag L+R:Chord  F2:New  1/2/3:Level  F1:Help  Q:Exit",15,1);
 str(c,2,24,a->game.state==MINE_WON?"YOU WIN!":a->game.state==MINE_LOST?"GAME OVER":"MINE",14,1);
 mine_number(s,a->game.width,1);str(c,14,24,s,14,1);str(c,16,24,"x",14,1);
 mine_number(s,a->game.height,1);str(c,17,24,s,14,1);
 mine_number(s,a->game.mines,1);str(c,22,24,s,14,1);
 str(c,26,24,a->game.questions?"mines  Marks (?) on":"mines  Marks (?) off",14,1);
 if(a->menu){panel(c,l,1,26,9);str(c,l+2,2,"New game           F2",0,7);str(c,l+2,3,"Beginner            1",0,7);str(c,l+2,4,"Intermediate        2",0,7);str(c,l+2,5,"Expert              3",0,7);str(c,l+2,6,"Toggle marks (?)    M",0,7);str(c,l+2,7,"Exit                Q",0,7);}
 if(a->help){panel(c,8,5,64,14);str(c,11,7,"MINE - classic Minesweeper",0,7);str(c,11,9,"Left: reveal. Right: flag / question / clear.",0,7);str(c,11,10,"Hold both buttons on a number, then release:",0,7);str(c,11,11,"matching flags reveal all remaining neighbors.",0,7);str(c,11,13,"First reveal is safe. Open all non-mine cells.",0,7);str(c,11,15,"F2 new / 1,2,3 difficulty / M question marks",0,7);str(c,11,17,"Click or press Esc to close help.",0,7);}
}
void text_mouse(MineApp*a,int col,int row,int buttons){
 int l=(80-(a->game.width*2+2))/2,w=a->game.width*2+2,newleft=(buttons&1)&&!(a->buttons&1);
 if(a->suppress){app_mouse(a,-1,-1,buttons);return;}
 if(a->help){if(newleft){a->help=0;a->buttons=buttons;app_cancel(a);}else a->buttons=buttons;return;}
 if(a->menu){if(newleft){if(col>=l&&col<l+26){if(row==2)app_new(a,a->level);else if(row>=3&&row<=5)app_new(a,row-3);else if(row==6)a->game.questions=!a->game.questions;else if(row==7)a->quit=1;}a->menu=0;a->buttons=buttons;app_cancel(a);}else a->buttons=buttons;return;}
 if(newleft&&row==0){if(col>=l&&col<l+7){a->menu=1;a->buttons=buttons;app_cancel(a);return;}if(col>=l+8&&col<l+13){a->help=1;a->buttons=buttons;app_cancel(a);return;}}
 if(newleft&&row==2&&col>=l+w/2-1&&col<=l+w/2+1){app_new(a,a->level);return;}
 if(col<l+1||col>=l+w-1||row<4||row>=4+a->game.height)app_mouse(a,-1,-1,buttons);
 else app_mouse(a,(col-l-1)/2,row-4,buttons);
}
