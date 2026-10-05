#include "core/player.h"
#include "core/enemy/movement.h"
#include "core/world/world.h"
#include <stdio.h>
#include <string.h>
static unsigned int calls,failures,expect_offset,expect_force,expect_max,expect_direction;
void mysmb_world_impose_gravity(struct mysmb_game *g,mysmb_u8 offset,mysmb_u8 up)
{(void)g;(void)offset;(void)up;++failures;}
void mysmb_world_move_platform_vertically(struct mysmb_game *g,mysmb_u8 slot,mysmb_u8 up)
{(void)g;(void)slot;(void)up;++failures;}
void mysmb_world_impose_gravity_spr_object(struct mysmb_game *g,mysmb_u8 offset,
                                            mysmb_u8 force,mysmb_u8 maximum)
{
    ++calls;
    if(offset!=expect_offset || force!=expect_force || maximum!=expect_max ||
       g->ram[0U]!=force) ++failures;
}
void mysmb_world_red_gravity(struct mysmb_game *g,mysmb_u8 offset,mysmb_u8 up)
{
    ++calls;
    if(offset!=expect_offset || up!=expect_direction || g->ram[0U]!=3U ||
       g->ram[1U]!=6U || g->ram[2U]!=2U) ++failures;
}
void mysmb_world_impose_gravity_block(struct mysmb_game *g,mysmb_u8 slot)
{(void)g;(void)slot;++failures;}
void mysmb_world_impose_gravity_misc(struct mysmb_game *g,mysmb_u8 slot,
                                    mysmb_u8 force,mysmb_u8 maximum)
{(void)g;(void)slot;(void)force;(void)maximum;++failures;}
int main(void)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned int timer,animation,slot,state,route,amount,maximum,allowed;
    unsigned long count;
    count=0UL;
    for(timer=0U;timer<256U;++timer) for(animation=0U;animation<256U;++animation) {
        memset(&g,0xa5,sizeof(g));g.ram[0x747U]=(mysmb_u8)timer;
        g.ram[0x70eU]=(mysmb_u8)animation;g.ram[0x709U]=(mysmb_u8)(timer^animation);
        memcpy(expected,g.ram,sizeof(expected));allowed=timer!=0U || animation==0U;
        expect_offset=0U;expect_force=g.ram[0x709U];expect_max=4U;calls=0U;
        if(allowed) expected[0U]=(mysmb_u8)expect_force;
        mysmb_player_move_vertically(&g);
        if(calls!=allowed || memcmp(expected,g.ram,sizeof(expected))) ++failures;
        if(failures) return 1;
        ++count;
    }
    for(slot=0U;slot<6U;++slot) for(state=0U;state<256U;++state) {
        memset(&g,0xa5,sizeof(g));g.ram[0x1eU+slot]=(mysmb_u8)state;
        memcpy(expected,g.ram,sizeof(expected));expect_offset=slot+1U;
        expect_force=state==5U?0x20U:0x3dU;expect_max=3U;
        expected[0U]=(mysmb_u8)expect_force;calls=0U;
        mysmb_enemy_move_d_vertically(&g,(mysmb_u8)slot);
        if(calls!=1U || memcmp(expected,g.ram,sizeof(expected))) ++failures;
        if(failures) return 2;
        ++count;
    }
    for(slot=0U;slot<6U;++slot) for(route=0U;route<6U;++route) {
        memset(&g,0xa5,sizeof(g));memcpy(expected,g.ram,sizeof(expected));
        expect_offset=slot+1U;expect_force=route==0U?0x20U:(route==1U?0x7fU:(route==2U?0x0fU:0x1cU));
        expect_max=route==1U||route==2U?2U:3U;
        expected[0U]=(mysmb_u8)expect_force;calls=0U;
        if(route>=4U) {expected[0U]=3U;expected[1U]=6U;expected[2U]=2U;expect_direction=route-4U;}
        switch(route) {
        case 0U:mysmb_enemy_move_falling_platform(&g,(mysmb_u8)slot);break;
        case 1U:mysmb_enemy_move_drop_platform(&g,(mysmb_u8)slot);break;
        case 2U:mysmb_enemy_move_slow_vertically(&g,(mysmb_u8)slot);break;
        case 3U:mysmb_enemy_move_j_vertically(&g,(mysmb_u8)slot);break;
        case 4U:mysmb_enemy_move_red_down(&g,(mysmb_u8)slot);break;
        default:mysmb_enemy_move_red_up(&g,(mysmb_u8)slot);break;
        }
        if(calls!=1U || memcmp(expected,g.ram,sizeof(expected))) ++failures;
        if(failures) return 3;
        ++count;
    }
    for(slot=0U;slot<6U;++slot) for(amount=0U;amount<256U;++amount)
        for(maximum=0U;maximum<256U;++maximum) {
            memset(&g,0xa5,sizeof(g));memcpy(expected,g.ram,sizeof(expected));
            expect_offset=slot+1U;expect_force=amount;expect_max=maximum;
            expected[0U]=(mysmb_u8)amount;calls=0U;
            mysmb_enemy_move_downward(&g,(mysmb_u8)slot,(mysmb_u8)amount,(mysmb_u8)maximum);
            if(calls!=1U || memcmp(expected,g.ram,sizeof(expected))) ++failures;
            if(failures) return 4;
            ++count;
        }
    printf("%lu adapter gate/parameter/full-write cases, %u failures\n",count,failures);
    return failures?1:0;
}
