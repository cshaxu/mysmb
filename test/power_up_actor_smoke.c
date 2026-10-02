#include "game/objects.h"
#include "game/enemy/movement.h"
#include "game/oam/oam.h"
#include <stdio.h>
#include <string.h>
static unsigned int failures,calls,ids[10];
static void child(struct mysmb_game *g,unsigned int id,mysmb_u8 slot)
{
    if(slot!=5U || g->ram[8U]!=5U || calls>=10U) {++failures;return;}
    ids[calls++]=id;
    if(id==6U) g->ram[0x3d1U]=0x44U;
    if(id==9U) {g->ram[0x1bU]=0U;g->ram[0x23U]=0U;}
}
void mysmb_enemy_move_jumping(struct mysmb_game *g,mysmb_u8 x) {child(g,1U,x);}
void mysmb_objects_step_enemy_jump_terrain(struct mysmb_game *g,mysmb_u8 x) {child(g,2U,x);}
void mysmb_enemy_move_normal(struct mysmb_game *g,mysmb_u8 x) {child(g,3U,x);}
void mysmb_objects_enemy_background_current(struct mysmb_game *g,mysmb_u8 x) {child(g,4U,x);}
void mysmb_oam_relative_enemy_position(struct mysmb_game *g,mysmb_u8 x) {child(g,5U,x);}
void mysmb_oam_get_enemy_offscreen_bits(struct mysmb_game *g,mysmb_u8 x)
{child(g,6U,x);}
void mysmb_objects_update_enemy_bounding_box(struct mysmb_game *g,mysmb_u8 x) {child(g,7U,x);}
void mysmb_objects_draw_power_up(struct mysmb_game *g) {child(g,8U,5U);}
void mysmb_objects_player_enemy_current(struct mysmb_game *g,mysmb_u8 x,mysmb_u8 preserve)
{if(preserve!=1U) ++failures;child(g,9U,x);}
void mysmb_objects_check_enemy_offscreen_bounds(struct mysmb_game *g,mysmb_u8 x) {child(g,10U,x);}

int main(void)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned int state,frame,timer,type,n,i,want,first,cases;
    cases=0U;
    for(state=0U;state<256U;++state) for(frame=0U;frame<4U;++frame)
    for(timer=0U;timer<2U;++timer) for(type=0U;type<5U;++type) {
        memset(&g,0xa5,sizeof(g));g.ram[0x23U]=(mysmb_u8)state;
        g.ram[9U]=(mysmb_u8)frame;g.ram[0x747U]=(mysmb_u8)timer;
        g.ram[0x39U]=(mysmb_u8)type;
        memcpy(expected,g.ram,2048U);expected[8U]=5U;calls=0U;first=0U;
        n=state;
        if(n!=0U && n<128U && frame==0U) {
            expected[0xd4U]--;n++;
            if(state>=17U) {
                n=128U;expected[0x5dU]=16U;expected[0x3caU]=0U;expected[0x4bU]=1U;
            }
            expected[0x23U]=(mysmb_u8)n;
        }
        want=state!=0U && n>=6U?6U:0U;
        if(state>=128U && timer==0U) {
            if(type==0U || type==3U) first=3U;
            else if(type==2U) first=1U;
        }
        if(first) want+=2U;
        if(want) {expected[0x3d1U]=0x44U;expected[0x1bU]=0U;expected[0x23U]=0U;}
        mysmb_objects_step_power_up(&g);
        if(calls!=want || memcmp(g.ram,expected,2048U)!=0) ++failures;
        i=0U;
        if(first) {if(ids[0]!=first || ids[1]!=first+1U) ++failures;i=2U;}
        if(want) for(n=5U;n<=10U;++n) if(ids[i++]!=n) ++failures;
        ++cases;
    }
    printf("%u power-up actor cases, %u failures\n",cases,failures);
    return failures?1:0;
}
