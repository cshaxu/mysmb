#include "core/enemy/platform.h"
#include "core/world/world.h"
#include "core/player.h"
#include <stdio.h>
#include <string.h>
static struct mysmb_game g;
static unsigned int errors,boxes,offsets,sides;
static mysmb_u8 hit,vertical,mask_value,side_value,mutate;
static mysmb_u8 slots[4];
static void check(int condition){if(!condition)++errors;}
static void reset(void)
{
    memset(&g,0,sizeof(g));boxes=offsets=sides=0U;
    hit=1U;vertical=mask_value=mutate=0U;
    g.ram[8U]=5U;g.ram[0x1bU]=37U;g.ram[0x1dU]=2U;
    g.ram[0x4acU]=0x40U;g.ram[0x4adU]=0x80U;
    g.ram[0x4aeU]=0x50U;g.ram[0x4afU]=0x90U;
    g.ram[0x4c4U]=0x49U;g.ram[0x4c5U]=0x90U;
    g.ram[0x4c6U]=0x69U;g.ram[0x4c7U]=0x98U;
}
mysmb_u8 mysmb_world_player_vertical_carry(struct mysmb_game *game)
{(void)game;return vertical;}
mysmb_u8 mysmb_world_enemy_box_offset_arg(struct mysmb_game *game,mysmb_u8 slot,mysmb_u8 *mask)
{
    (void)game;if(offsets<4U)slots[offsets]=slot;++offsets;
    *mask=mask_value;return (mysmb_u8)(slot*4U+4U);
}
mysmb_u8 mysmb_world_boxes_collide(struct mysmb_game *game,mysmb_u16 first,mysmb_u16 second)
{
    (void)game;check(first==0x4acU && second==0x4b0U+slots[offsets-1U]*4U);
    ++boxes;if(mutate&&boxes==1U)g.ram[8U]=4U;return hit;
}
void mysmb_player_impede_move(struct mysmb_game *game,mysmb_u8 side)
{check(side==game->ram[0U]);++sides;side_value=side;}
int main(void)
{
    unsigned int delta,speed,left,right,cases;
    cases=0U;
    for(delta=0U;delta<256U;++delta)for(speed=0U;speed<256U;++speed) {
        int top;
        reset();g.ram[0x4c5U]=(mysmb_u8)(0x90U-delta);g.ram[0x4c7U]=0x88U;g.ram[0x9fU]=(mysmb_u8)speed;
        mysmb_platform_collision_large(&g,5U);top=delta<6U&&speed<0x80U;
        check(g.ram[0x3a7U]==(top?5U:0xffU));check(g.ram[0x1dU]==(top?0U:2U));
        check(sides==(top?0U:1U));++cases;
        reset();g.ram[0x4c5U]=0x70U;g.ram[0x4c7U]=(mysmb_u8)(0x80U+delta);g.ram[0x9fU]=(mysmb_u8)speed;
        mysmb_platform_collision_large(&g,5U);
        check(g.ram[0x9fU]==(delta<4U&&speed>=0x80U?1U:speed));++cases;
    }
    for(left=0U;left<256U;++left)for(right=0U;right<256U;++right) {
        reset();g.ram[0x4c5U]=0x80U;g.ram[0x4c4U]=(mysmb_u8)(0x50U-left);
        g.ram[0x4c6U]=(mysmb_u8)(0x40U+right+1U);
        mysmb_platform_collision_large(&g,5U);
        check(sides==(left<8U||right<9U?1U:0U));
        if(sides)check(side_value==(left<8U?1U:2U));
        ++cases;
    }
    reset();hit=0U;g.ram[0x1bU]=43U;
    mysmb_platform_collision_small(&g,5U);check(boxes==1U&&offsets==2U);
    check(g.ram[0x4c5U]==0x90U&&g.ram[0x4c7U]==0x98U&&g.ram[0U]==0U);
    reset();g.ram[0x1bU]=43U;g.ram[0x4c5U]=0x10U;g.ram[0x4c7U]=0x18U;
    mysmb_platform_collision_small(&g,5U);check(boxes==1U&&offsets==2U&&g.ram[0x3a7U]==1U);
    check(g.ram[0x1dU]==0U&&g.ram[0x4c5U]==0x90U);
    reset();g.ram[0x1bU]=44U;mysmb_platform_collision_small(&g,5U);check(g.ram[0x3a7U]==2U);
    reset();mask_value=2U;mysmb_platform_collision_small(&g,5U);check(boxes==0U&&g.ram[0U]==2U);
    reset();g.ram[0x747U]=1U;g.ram[0x3a7U]=0xa5U;mysmb_platform_collision_small(&g,5U);check(g.ram[0x3a7U]==0xa5U&&offsets==0U);
    reset();g.ram[0x747U]=1U;mysmb_platform_collision_large(&g,5U);check(g.ram[0x3a7U]==0xffU&&offsets==0U);
    reset();vertical=1U;mysmb_platform_collision_small(&g,5U);check(g.ram[0x3a7U]==0U&&offsets==0U);
    reset();mutate=1U;hit=0U;g.ram[0x1bU]=36U;g.ram[0x23U]=0U;
    mysmb_platform_collision_large(&g,5U);check(offsets==2U&&slots[0]==0U&&slots[1]==4U);
    printf("platform collision: %u cases, %u errors\n",cases,errors);return errors?1:0;
}
