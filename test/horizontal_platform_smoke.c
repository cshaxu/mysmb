#include "game/enemy/platform.h"
#include "game/enemy/x_counter.h"
#include "game/enemy/movement.h"
#include "game/world/world.h"
#include <stdio.h>
#include <string.h>
static unsigned int failures,cases,step,kind,collision;
static mysmb_u8 input_slot,live_slot,delta,want_x,want_page;
void mysmb_platform_position_player_small(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 c)
{ (void)g;(void)s;(void)c;++failures; }
void mysmb_enemy_x_counter_platform(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 max)
{ (void)g;if(kind!=0U || step++!=0U || s!=input_slot || max!=14U)++failures; }
void mysmb_enemy_move_with_x_counters(struct mysmb_game *g,mysmb_u8 s)
{
    if(kind!=0U || step++!=1U || s!=input_slot)++failures;
    g->ram[8U]=live_slot;g->ram[0U]=delta;
}
mysmb_u8 mysmb_world_move_enemy_horizontally(struct mysmb_game *g,mysmb_u8 s)
{
    if(kind!=1U || step++!=0U || s!=input_slot || g->ram[0x58U+live_slot]!=0x33U)++failures;
    g->ram[8U]=live_slot;return delta;
}
void mysmb_enemy_move_drop_platform(struct mysmb_game *g,mysmb_u8 s)
{ if(kind!=2U || step++!=0U || s!=input_slot)++failures;g->ram[8U]=live_slot; }
void mysmb_platform_position_player_vertical(struct mysmb_game *g,mysmb_u8 s)
{
    if(s!=live_slot || !collision || step++!=(kind==0U?2U:1U))++failures;
    if(kind!=2U && (g->ram[0x86U]!=want_x || g->ram[0x6dU]!=want_page || g->ram[0x3a1U]!=delta))++failures;
    if(kind==1U && g->ram[0x58U+s]!=16U)++failures;
}
void mysmb_world_move_platform_vertically(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 up)
{ (void)g;(void)s;(void)up;++failures; }
static void verify(unsigned int x,unsigned int d,unsigned int page,unsigned int entry,unsigned int hit)
{
    static struct mysmb_game g;
    long position;
    memset(&g,0,sizeof(g));kind=entry;collision=hit;step=0U;
    input_slot=(mysmb_u8)(d&1U?5U:0U);live_slot=(mysmb_u8)(5U-input_slot);delta=(mysmb_u8)d;
    g.ram[8U]=input_slot;g.ram[0x86U]=(mysmb_u8)x;g.ram[0x6dU]=(mysmb_u8)page;
    g.ram[0x58U+live_slot]=0x33U;g.ram[0x3a1U]=0xa5U;
    g.ram[0x3a2U+input_slot]=(mysmb_u8)(entry==2U?(hit?3U:0xffU):(hit?0xffU:3U));
    g.ram[0x3a2U+live_slot]=(mysmb_u8)(hit?3U:0xffU);
    position=(long)page*256L+(long)x+(d<128U?(long)d:(long)d-256L);
    position=(position+65536L)%65536L;want_x=(mysmb_u8)position;want_page=(mysmb_u8)(position/256L);
    if(entry==0U)mysmb_platform_move_x(&g,input_slot);
    else if(entry==1U)mysmb_platform_move_right(&g,input_slot);
    else mysmb_platform_move_drop(&g,input_slot);
    if(step!=(entry==0U?2U+hit:(entry==1U?1U+hit:2U*hit)))++failures;
    if(!hit && (g.ram[0x86U]!=x || g.ram[0x6dU]!=page || g.ram[0x3a1U]!=0xa5U || g.ram[0x58U+live_slot]!=0x33U))++failures;
    ++cases;
}
int main(void)
{
    unsigned int x,d,k;
    for(k=0U;k<2U;++k)for(x=0U;x<256U;++x)for(d=0U;d<256U;++d) {
        verify(x,d,0U,k,1U);verify(x,d,255U,k,1U);verify(x,d,127U,k,0U);
    }
    for(d=0U;d<256U;++d){verify(0U,d,0U,2U,0U);verify(255U,d,255U,2U,1U);}
    printf("horizontal platform cases=%u failures=%u\n",cases,failures);
    return failures?1:0;
}
