#include "mine.h"
#include <string.h>

/* A fixed 32-bit stream on both 16-bit and wider C implementations. */
static unsigned long next_random(Mine *g)
{
    unsigned long v=g->random;
    v^=(v<<13)&0xffffffffUL;
    v^=v>>17;
    v^=(v<<5)&0xffffffffUL;
    g->random=v&0xffffffffUL;
    return g->random;
}

int mine_inside(const Mine *g,int x,int y)
{
    return x>=0 && y>=0 && x<g->width && y<g->height;
}

void mine_new(Mine *g,int width,int height,int bombs,unsigned long seed)
{
    int i,total,left;
    memset(g,0,sizeof(*g));
    if(width<1)width=1;
    if(width>30)width=30;
    if(height<1)height=1;
    if(height>20)height=20;
    total=width*height;
    if(bombs<0)bombs=0;
    if(bombs>=total)bombs=total-1;
    g->width=width;g->height=height;g->mines=bombs;
    g->questions=1;g->exploded=-1;
    g->random=seed&0xffffffffUL;
    if(!g->random)g->random=0x91e10da5UL;
    /* Select exactly bombs positions without retries or a shuffle buffer. */
    left=bombs;
    for(i=0;i<total;++i){
        if(next_random(g)%(unsigned long)(total-i)<(unsigned long)left){
            g->hazard[i]=1;--left;
        }
    }
}

int mine_count_bombs(const Mine *g,int x,int y)
{
    int dx,dy,n=0;
    for(dy=-1;dy<=1;++dy)for(dx=-1;dx<=1;++dx)
        if((dx||dy)&&mine_inside(g,x+dx,y+dy))
            n+=g->hazard[(y+dy)*g->width+x+dx]!=0;
    return n;
}

void mine_mark(Mine *g,int x,int y)
{
    int i;
    if(g->state!=MINE_PLAYING||!mine_inside(g,x,y))return;
    i=y*g->width+x;
    if(g->cover[i]==MINE_OPEN)return;
    if(g->cover[i]==MINE_MARKED){
        --g->flags;g->cover[i]=(unsigned char)(g->questions?MINE_UNCERTAIN:MINE_COVERED);
    }else if(g->cover[i]==MINE_UNCERTAIN)g->cover[i]=MINE_COVERED;
    else {++g->flags;g->cover[i]=MINE_MARKED;}
}

static void finish(Mine *g)
{
    int i;
    if(g->state==MINE_PLAYING&&g->opened==g->width*g->height-g->mines){
        g->state=MINE_WON;g->flags=g->mines;
        for(i=0;i<g->width*g->height;++i)
            if(g->hazard[i])g->cover[i]=MINE_MARKED;
    }
}

/* Iterative flood: each safe cell enters once, including numbered borders.
 * A bounded automatic queue avoids recursion and a resident scratch board. */
static void open_region(Mine *g,int start)
{
    unsigned short queue[MINE_CAPACITY];
    int head=0,tail=0,i,x,y,dx,dy,j;
    if(g->cover[start]==MINE_OPEN||g->cover[start]==MINE_MARKED)return;
    if(g->hazard[start]){
        g->state=MINE_LOST;g->exploded=start;return;
    }
    g->cover[start]=MINE_OPEN;++g->opened;
    queue[tail++]=(unsigned short)start;
    while(head<tail){
        i=queue[head++];x=i%g->width;y=i/g->width;
        if(mine_count_bombs(g,x,y))continue;
        for(dy=-1;dy<=1;++dy)for(dx=-1;dx<=1;++dx){
            if(!mine_inside(g,x+dx,y+dy))continue;
            j=(y+dy)*g->width+x+dx;
            if(g->hazard[j]||g->cover[j]==MINE_OPEN||g->cover[j]==MINE_MARKED)continue;
            g->cover[j]=MINE_OPEN;++g->opened;
            queue[tail++]=(unsigned short)j;
        }
    }
}

void mine_reveal(Mine *g,int x,int y)
{
    int i,j,total;
    if(g->state!=MINE_PLAYING||!mine_inside(g,x,y))return;
    i=y*g->width+x;
    if(g->cover[i]==MINE_OPEN||g->cover[i]==MINE_MARKED)return;
    if(!g->started){
        g->started=1;
        if(g->hazard[i]){
            total=g->width*g->height;
            j=(int)(next_random(g)%(unsigned long)total);
            while(g->hazard[j])j=(j+1)%total;
            g->hazard[i]=0;g->hazard[j]=1;
        }
    }
    open_region(g,i);finish(g);
}

void mine_chord(Mine *g,int x,int y)
{
    int dx,dy,n=0;
    if(g->state!=MINE_PLAYING||!mine_inside(g,x,y)||
        g->cover[y*g->width+x]!=MINE_OPEN)return;
    for(dy=-1;dy<=1;++dy)for(dx=-1;dx<=1;++dx)
        if(mine_inside(g,x+dx,y+dy)&&g->cover[(y+dy)*g->width+x+dx]==MINE_MARKED)++n;
    if(n!=mine_count_bombs(g,x,y))return;
    for(dy=-1;dy<=1&&g->state==MINE_PLAYING;++dy)
        for(dx=-1;dx<=1&&g->state==MINE_PLAYING;++dx)
            if(mine_inside(g,x+dx,y+dy))open_region(g,(y+dy)*g->width+x+dx);
    finish(g);
}

void mine_second(Mine *g)
{
    if(g->started&&g->state==MINE_PLAYING&&g->seconds<999)++g->seconds;
}

int mine_sprite(const Mine *g,int x,int y)
{
    int i;
    if(!mine_inside(g,x,y))return MINE_CLOSED;
    i=y*g->width+x;
    if(g->state==MINE_LOST){
        if(i==g->exploded)return MINE_EXPLODED;
        if(g->cover[i]==MINE_MARKED&&!g->hazard[i])return MINE_WRONG;
        if(g->hazard[i]&&g->cover[i]!=MINE_MARKED)return MINE_SHOWN;
    }
    if(g->cover[i]==MINE_OPEN)return mine_count_bombs(g,x,y);
    if(g->cover[i]==MINE_MARKED)return MINE_FLAG;
    if(g->cover[i]==MINE_UNCERTAIN)return MINE_QUESTION;
    return MINE_CLOSED;
}
