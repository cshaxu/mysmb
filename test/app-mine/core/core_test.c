#include "core/mine.h"
#include <stdio.h>
#include <string.h>
static int checks,failures;
#define CHECK(e) do {++checks;if(!(e)){++failures;printf("FAIL %d: %s\n",__LINE__,#e);}} while(0)
static Mine a,b;
static void fixture(void)
{
    mine_new(&a,3,3,1,1);memset(a.hazard,0,sizeof(a.hazard));a.hazard[0]=1;
    a.started=1;
}
int main(void)
{
    int i,j,n;
    unsigned long hash=2166136261UL;
    mine_new(&a,-1,50,999,0);
    CHECK(a.width==1&&a.height==20&&a.mines==19&&a.exploded==-1);
    mine_new(&a,99,-1,-2,1);CHECK(a.width==30&&a.height==1&&a.mines==0);
    for(i=0;i<64;++i){
        mine_new(&a,30,20,99,(unsigned long)i);mine_new(&b,30,20,99,(unsigned long)i);
        CHECK(!memcmp(a.hazard,b.hazard,sizeof(a.hazard)));
        n=0;for(j=0;j<600;++j){n+=a.hazard[j];hash=((hash^a.hazard[j])*16777619UL)&0xffffffffUL;}
        CHECK(n==99);
        for(j=0;j<600&&!a.hazard[j];++j){}
        mine_reveal(&a,j%30,j/30);CHECK(a.started&&a.state!=MINE_LOST&&!a.hazard[j]);
        n=0;for(j=0;j<600;++j)n+=a.hazard[j];CHECK(n==99);
    }
    fixture();CHECK(mine_count_bombs(&a,1,1)==1&&mine_count_bombs(&a,2,2)==0);
    CHECK(!mine_inside(&a,-1,0)&&!mine_inside(&a,3,0)&&mine_inside(&a,2,2));
    mine_mark(&a,-1,0);mine_reveal(&a,3,0);mine_chord(&a,3,0);CHECK(a.opened==0&&a.flags==0);
    CHECK(mine_sprite(&a,-1,0)==MINE_CLOSED);
    mine_mark(&a,1,1);CHECK(a.flags==1&&mine_sprite(&a,1,1)==MINE_FLAG);
    mine_reveal(&a,1,1);CHECK(a.opened==0);
    mine_mark(&a,1,1);CHECK(a.flags==0&&mine_sprite(&a,1,1)==MINE_QUESTION);
    mine_mark(&a,1,1);CHECK(mine_sprite(&a,1,1)==MINE_CLOSED);
    a.questions=0;mine_mark(&a,1,1);mine_mark(&a,1,1);CHECK(a.cover[4]==MINE_COVERED);
    mine_reveal(&a,1,1);CHECK(a.opened==1&&mine_sprite(&a,1,1)==1);
    mine_mark(&a,1,1);CHECK(a.flags==0);
    mine_chord(&a,1,1);CHECK(a.opened==1);
    mine_mark(&a,0,0);mine_chord(&a,1,1);
    CHECK(a.state==MINE_WON&&a.opened==8&&a.flags==1);
    mine_reveal(&a,0,0);mine_mark(&a,0,0);mine_second(&a);CHECK(a.state==MINE_WON&&a.seconds==0);
    fixture();mine_reveal(&a,1,1);mine_mark(&a,2,2);mine_chord(&a,1,1);
    CHECK(a.state==MINE_LOST&&mine_sprite(&a,0,0)==MINE_EXPLODED&&mine_sprite(&a,2,2)==MINE_WRONG);
    fixture();a.hazard[1]=1;a.mines=2;mine_reveal(&a,0,0);CHECK(mine_sprite(&a,1,0)==MINE_SHOWN);
    fixture();mine_mark(&a,0,0);mine_reveal(&a,2,2);CHECK(a.state==MINE_WON);
    mine_new(&a,30,20,0,1);mine_second(&a);CHECK(a.seconds==0);
    mine_reveal(&a,0,0);CHECK(a.opened==600&&a.state==MINE_WON);
    fixture();a.seconds=998;mine_second(&a);mine_second(&a);CHECK(a.seconds==999);
    fixture();mine_chord(&a,0,1);CHECK(a.opened==0);
    printf("core checks=%d failures=%d hash=%08lx size=%u\n",checks,failures,hash,(unsigned)sizeof(a));
    return failures?1:0;
}
