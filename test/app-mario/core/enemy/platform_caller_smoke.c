#include "core/enemy/platform.h"
#include "core/enemy/core.h"
#include "core/objects.h"
#include "core/oam/oam.h"
#include <string.h>
static unsigned int events[10],count,bad,mutation;
static mysmb_u8 current_slot;
static void record(struct mysmb_game *g,mysmb_u8 s,unsigned int e)
{
    if(s!=current_slot || count>=10U) {++bad;return;}
    events[count++]=e;
    if(e==4U || e==8U) {
        g->ram[0xfU+s]=0U;
        if(mutation==1U) g->ram[0x16U+s]=42U;
        if(mutation==2U) g->ram[0x747U]^=1U;
    }
}
void mysmb_oam_get_enemy_offscreen_bits(struct mysmb_game *g,mysmb_u8 s)
{record(g,s,1U);g->ram[0x3d1U]=0x64U;}
void mysmb_oam_relative_enemy_position(struct mysmb_game *g,mysmb_u8 s)
{if(g->ram[0x3d1U]!=0x64U) ++bad;g->ram[0x3aeU]++;record(g,s,2U);}
#define CHILD(n,e) void n(struct mysmb_game *g,mysmb_u8 s) {record(g,s,e);}
CHILD(mysmb_platform_box_large,3U)
CHILD(mysmb_platform_collision_large,4U)
CHILD(mysmb_objects_draw_large_platform,5U)
CHILD(mysmb_objects_check_enemy_offscreen_bounds,6U)
CHILD(mysmb_platform_box_small,7U)
CHILD(mysmb_platform_collision_small,8U)
CHILD(mysmb_objects_draw_small_platform,9U)
CHILD(mysmb_platform_move_small,10U)
CHILD(mysmb_platform_move_balance,15U)
CHILD(mysmb_platform_move_y,16U)
CHILD(mysmb_platform_move_large_lift,17U)
CHILD(mysmb_platform_move_x,19U)
CHILD(mysmb_platform_move_drop,20U)
CHILD(mysmb_platform_move_right,21U)
#undef CHILD
int main(void)
{
    static const unsigned short targets[7]={0xd432,0xd5d3,0xd64f,0xd64f,0xd607,0xd631,0xd63d};
    static const unsigned int erasures[8]={0xf,0x16,0x1e,0x110,0x796,0x125,0x3c5,0x78a};
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned int id,s,timer,i,j,value,want[10],total,selector;
    unsigned short address;
    for(id=36U;id<=44U;++id) for(s=0U;s<6U;++s)
    for(timer=0U;timer<2U;++timer) for(mutation=0U;mutation<3U;++mutation) {
        memset(g.ram,0xa5,2048U);g.ram[0x16U+s]=(mysmb_u8)id;g.ram[0x747U]=(mysmb_u8)timer;
        memcpy(expected,g.ram,2048U);expected[0x3d1U]=0x64U;expected[0x3aeU]+=2U;expected[0xfU+s]=0U;
        if(mutation==1U) expected[0x16U+s]=42U;
        if(mutation==2U) expected[0x747U]^=1U;
        total=0U;want[total++]=1U;want[total++]=2U;
        want[total++]=id>=43U?7U:3U;want[total++]=id>=43U?8U:4U;
        if(id<43U && expected[0x747U]==0U) {
            selector=(unsigned int)expected[0x16U+s]-36U;address=targets[selector];
            expected[4U]=0x89U;expected[5U]=0xc9U;expected[6U]=(mysmb_u8)address;expected[7U]=(mysmb_u8)(address>>8U);
            want[total++]=selector==3U?17U:15U+selector;
        }
        want[total++]=2U;want[total++]=id>=43U?9U:5U;
        if(id>=43U) want[total++]=10U;
        want[total++]=6U;count=bad=0U;current_slot=(mysmb_u8)s;
        if(id>=43U) mysmb_enemy_run_small_platform(&g,(mysmb_u8)s);
        else mysmb_enemy_run_large_platform(&g,(mysmb_u8)s);
        if(bad || count!=total || memcmp(g.ram,expected,2048U)) return 1;
        for(i=0U;i<total;++i) if(events[i]!=want[i]) return 2;
    }
    for(s=0U;s<6U;++s) for(value=0U;value<256U;++value) {
        memset(g.ram,(int)value,2048U);memcpy(expected,g.ram,2048U);
        for(j=0U;j<8U;++j) expected[erasures[j]+s]=0U;
        mysmb_objects_erase_enemy(&g,(mysmb_u8)s);
        if(memcmp(g.ram,expected,2048U)) return 3;
    }
    return 0;
}
