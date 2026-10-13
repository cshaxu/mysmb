#include "scene.h"
#include "../io/number.h"

/* Original procedural art: bevels, strokes and small block lettering.
 * No external bitmap strips, font files or WinMine resources. */
struct surface {unsigned char *p;int width,first,end;};
static void box(struct surface *s,int x,int y,int w,int h,int color)
{
    int xx,yy;
    for(yy=y;yy<y+h;++yy)if(yy>=s->first&&yy<s->end)
        for(xx=x;xx<x+w;++xx)if(xx>=0&&xx<s->width)
            s->p[(yy-s->first)*s->width+xx]=(unsigned char)color;
}
static void bevel(struct surface *s,int x,int y,int w,int h,int raised)
{
    box(s,x,y,w,h,7);
    box(s,x,y,w,2,raised?15:8);box(s,x,y,2,h,raised?15:8);
    box(s,x,y+h-2,w,2,raised?8:15);box(s,x+w-2,y,2,h,raised?8:15);
}
/* Five columns of seven authored bits, low bit at top. */
static const unsigned char font[][5]={
    {62,81,73,69,62},{0,66,127,64,0},{98,81,73,73,70},{34,65,73,73,54},
    {24,20,18,127,16},{39,69,69,69,57},{60,74,73,73,48},{1,113,9,5,3},
    {54,73,73,73,54},{6,73,73,41,30},
    {126,9,9,9,126},{127,73,73,73,54},{62,65,65,65,34},{127,65,65,34,28},
    {127,73,73,73,65},{127,9,9,9,1},{62,65,73,73,122},{127,8,8,8,127},
    {0,65,127,65,0},{32,64,65,63,1},{127,8,20,34,65},{127,64,64,64,64},
    {127,2,12,2,127},{127,4,8,16,127},{62,65,65,65,62},{127,9,9,9,6},
    {62,65,81,33,94},{127,9,25,41,70},{38,73,73,73,50},{1,1,127,1,1},
    {63,64,64,64,63},{31,32,64,32,31},{63,64,56,64,63},{99,20,8,20,99},
    {3,4,120,4,3},{97,81,73,69,67},{2,1,81,9,6},{8,8,8,8,8}
};
static void label(struct surface *s,int x,int y,const char *text,int color,int scale)
{
    int c,i,j,index;
    while(*text){
        c=*text++;index=-1;
        if(c>='0'&&c<='9')index=c-'0';
        else if(c>='A'&&c<='Z')index=c-'A'+10;
        else if(c=='?')index=36;
        else if(c=='-')index=37;
        if(index>=0)for(i=0;i<5;++i)for(j=0;j<7;++j)
            if(font[index][i]&(1U<<j))box(s,x+i*scale,y+j*scale,scale,scale,color);
        x+=6*scale;
    }
}
int mine_graphics_width(const MineApp *a){return a->game.width*16+24;}
int mine_graphics_height(const MineApp *a){return a->game.height*16+76;}

int mine_graphics_rows(const MineApp *a,unsigned short first,unsigned short rows,
    unsigned char *p,unsigned short capacity,struct mygames_kvm_video_band *band)
{
    static const int colors[9]={0,1,2,4,1,4,3,0,8};
    struct surface s;
    int w=mine_graphics_width(a),h=mine_graphics_height(a),x,y,v,px,py,c;
    char text[12];
    if(!p||!band||!rows||first>=(unsigned short)h||rows>(unsigned short)(h-first)||(unsigned long)w*rows>capacity)return 0;
    s.p=p;s.width=w;s.first=first;s.end=first+rows;
    box(&s,0,first,w,rows,7);
    bevel(&s,0,0,w,h,1);bevel(&s,8,8,w-16,40,0);
    box(&s,14,15,40,25,0);box(&s,w-54,15,40,25,0);
    mine_number(text,a->game.mines-a->game.flags,3);label(&s,16,20,text,12,2);
    mine_number(text,a->game.seconds,3);label(&s,w-52,20,text,12,2);
    bevel(&s,w/2-14,14,28,28,!a->down_face);
    box(&s,w/2-9,18,18,18,14);
    box(&s,w/2-5,22,2,2,0);box(&s,w/2+3,22,2,2,0);
    if(a->game.state==MINE_WON)box(&s,w/2-7,21,14,3,0);
    if(a->gesture)box(&s,w/2-2,28,4,4,0);
    else {
        box(&s,w/2-5,a->game.state==MINE_LOST?28:31,10,2,0);
        box(&s,w/2-6,28,2,3,0);box(&s,w/2+4,28,2,3,0);
    }
    bevel(&s,10,54,w-20,h-64,0);
    for(y=0;y<a->game.height;++y)for(x=0;x<a->game.width;++x){
        px=12+x*16;py=56+y*16;
        if(py+16<=s.first||py>=s.end)continue;
        v=app_tile(a,x,y);c=v==MINE_EXPLODED?12:7;
        if(v==MINE_CLOSED||v==MINE_FLAG||v==MINE_QUESTION)bevel(&s,px,py,16,16,1);
        else {box(&s,px,py,16,16,8);box(&s,px+1,py+1,15,15,c);}
        if(v>=1&&v<=8){text[0]=(char)('0'+v);text[1]=0;label(&s,px+5,py+4,text,colors[v],1);}
        else if(v==9||v==MINE_QUESTION)label(&s,px+5,py+4,"?",0,1);
        else if(v==MINE_FLAG){
            box(&s,px+7,py+3,1,9,0);box(&s,px+3,py+3,5,4,12);box(&s,px+4,py+12,8,1,0);
        }else if(v==MINE_SHOWN||v==MINE_EXPLODED){
            box(&s,px+5,py+5,7,7,0);box(&s,px+8,py+2,1,12,0);
            box(&s,px+2,py+8,12,1,0);box(&s,px+6,py+6,2,2,15);
        }else if(v==MINE_WRONG){
            label(&s,px+5,py+4,"X",12,1);
        }
    }
    if(a->help){
        bevel(&s,4,50,w-8,100,1);
        label(&s,10,60,"LEFT OPEN",0,1);label(&s,10,73,"RIGHT FLAG",0,1);
        label(&s,10,86,"BOTH CHORD",0,1);label(&s,10,99,"F2 NEW  123 LEVEL",0,1);
        label(&s,10,112,"TAB VIEW  M MARKS",0,1);label(&s,10,125,"ESC CLOSE HELP",0,1);
    }
    band->pixels=p;band->first=first;band->rows=rows;
    band->width=(unsigned short)w;band->stride=(unsigned short)w;band->capacity=capacity;
    return 1;
}

void mine_graphics_mouse(MineApp *a,int x,int y,int buttons)
{
    int w=mine_graphics_width(a),left=(buttons&1)&&!(a->buttons&1);
    if(a->suppress){app_mouse(a,-1,-1,buttons);return;}
    if(a->help){if(left){a->help=0;a->buttons=buttons;app_cancel(a);}else a->buttons=buttons;return;}
    if(a->down_face){
        if(!(buttons&1)){
            a->down_face=0;
            if(x>=w/2-14&&x<w/2+14&&y>=14&&y<42){
                app_new(a,a->level);a->suppress=buttons!=0;
            }
        }
        a->buttons=buttons;a->dirty=1;return;
    }
    if(left&&x>=w/2-14&&x<w/2+14&&y>=14&&y<42){
        a->down_face=1;a->buttons=buttons;a->dirty=1;return;
    }
    if(x<12||y<56||x>=12+a->game.width*16||y>=56+a->game.height*16)app_mouse(a,-1,-1,buttons);
    else app_mouse(a,(x-12)/16,(y-56)/16,buttons);
}
