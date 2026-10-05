#include "core/objects.h"
#include "core/world/world.h"
#include <stdio.h>
#include <string.h>
static struct mysmb_game g;
static unsigned int errors,boxes,defeats,scores;
static mysmb_u8 hit,mutation,score_slot,score_value;
static void check(int condition) { if(!condition)++errors; }
static void reset(void)
{
    memset(&g,0,sizeof(g));boxes=defeats=scores=0U;hit=1U;mutation=0U;
    g.ram[8U]=5U;g.ram[9U]=1U;g.ram[0x74eU]=1U;g.ram[0x13U]=1U;
    g.ram[0x5dU]=8U;g.ram[0x5cU]=0xf8U;
}
mysmb_u8 mysmb_world_enemy_box_offset(struct mysmb_game *game)
{ return (mysmb_u8)(game->ram[8U]*4U+4U); }
mysmb_u8 mysmb_world_boxes_collide(struct mysmb_game *game,mysmb_u16 first,mysmb_u16 second)
{
    check(first==0x4c0U && second==0x4c4U);++boxes;
    if(mutation==1U){g.ram[8U]=2U;g.ram[1U]=0U;}
    (void)game;return hit;
}
void mysmb_world_shell_or_block_defeat(struct mysmb_game *game,mysmb_u8 slot)
{
    ++defeats;game->ram[0x1eU+slot]|=0x20U;
    if(mutation==2U){game->ram[8U]=2U;game->ram[1U]=0U;}
}
void mysmb_objects_setup_floatey_from_relative(struct mysmb_game *game,mysmb_u8 slot,mysmb_u8 value)
{
    ++scores;score_slot=slot;score_value=value;
    if(mutation==3U){game->ram[8U]=2U;game->ram[1U]=0U;}
}
int main(void)
{
    unsigned int a,b,latch,chain,id,speed,direction,cases;
    cases=0U;
    for(a=0U;a<256U;++a)for(b=0U;b<256U;++b)for(latch=0U;latch<2U;++latch) {
        unsigned int expected_defeats,expected_scores;
        int responds;
        reset();g.ram[0x23U]=(mysmb_u8)a;g.ram[0x22U]=(mysmb_u8)b;
        g.ram[0x495U]=(mysmb_u8)(latch?4U:0U);
        responds=((a|b)&0x20U)==0U && (((a|b)&0x80U)!=0U || !latch);
        expected_defeats=responds?(a>=6U?1U+((b&0x80U)!=0U):(b>=6U?1U:0U)):0U;
        expected_scores=responds?(a>=6U?1U+((b&0x80U)!=0U):(b>=6U?1U:0U)):0U;
        mysmb_objects_step_enemy_collisions_current(&g,5U);
        check(boxes==1U && defeats==expected_defeats && scores==expected_scores);
        check(g.ram[1U]==0U);
        if(responds && a<6U && b<6U)check(g.ram[0x5dU]==0xf8U && g.ram[0x5cU]==8U);
        ++cases;
    }
    for(chain=0U;chain<256U;++chain) {
        reset();g.ram[0x23U]=0x84U;g.ram[0x12aU]=(mysmb_u8)chain;
        mysmb_objects_step_enemy_collisions_current(&g,5U);
        check(score_slot==4U && score_value==(mysmb_u8)(chain+4U));
        check(g.ram[0x12aU]==(mysmb_u8)(chain+1U));++cases;
    }
    for(id=0U;id<256U;++id)for(speed=0U;speed<256U;++speed)for(direction=0U;direction<4U;++direction) {
        int turns;
        reset();g.ram[0x1bU]=(mysmb_u8)id;g.ram[0x5dU]=(mysmb_u8)speed;g.ram[0x4bU]=(mysmb_u8)direction;
        turns=(id<7U&&id!=5U)||id==14U||id==18U;
        mysmb_objects_turn_enemy(&g,5U);
        check(g.ram[0x5dU]==(turns?(mysmb_u8)(0U-speed):(mysmb_u8)speed));
        check(g.ram[0x4bU]==(turns?(direction^3U):direction));++cases;
    }
    reset();mutation=1U;hit=0U;g.ram[0x491U]=0xffU;
    mysmb_objects_step_enemy_collisions_current(&g,5U);check(g.ram[0x491U]==0xdfU && boxes==1U);
    reset();mutation=2U;g.ram[0x23U]=0x84U;g.ram[0x127U]=0xffU;
    mysmb_objects_step_enemy_collisions_current(&g,5U);
    check(score_slot==0U && score_value==3U && g.ram[0x127U]==0U);
    reset();mutation=3U;g.ram[0x23U]=0x84U;
    mysmb_objects_step_enemy_collisions_current(&g,5U);check(g.ram[0x127U]==1U && g.ram[0x12aU]==0U);
    reset();g.ram[9U]=0U;mysmb_objects_step_enemy_collisions_current(&g,5U);check(boxes==0U);
    reset();g.ram[0x74eU]=0U;mysmb_objects_step_enemy_collisions_current(&g,5U);check(boxes==0U);
    reset();mysmb_objects_step_enemy_collisions_current(&g,0U);check(boxes==0U);
    printf("enemy-pair: %u cases, %u errors\n",cases,errors);return errors?1:0;
}
