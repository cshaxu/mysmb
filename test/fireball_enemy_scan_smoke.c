#include "game/world/world.h"
#include <stdio.h>
#include <string.h>
static struct mysmb_game game;
static unsigned int collisions,hits,errors,mode;
static mysmb_u8 root_slot;
mysmb_u8 mysmb_world_boxes_collide(struct mysmb_game *g,mysmb_u16 a,mysmb_u16 b)
{
    struct mysmb_game *mutable_game;
    if(a!=0x4acU+(mysmb_u8)(g->ram[1U]*4U+4U)||
       b!=0x4acU+(mysmb_u8)(root_slot*4U+0x1cU))++errors;
    ++collisions;
    mutable_game=(struct mysmb_game *)g;
    if(mode==2U){mutable_game->ram[1U]=0U;mutable_game->ram[8U]=1U;}
    if(mode==3U){mutable_game->ram[1U]=0U;return 0U;}
    return mode==1U?0U:1U;
}
void mysmb_world_handle_fireball_enemy_hit(struct mysmb_game *g,mysmb_u8 s)
{
    if(s!=g->ram[1U]||g->ram[0x24U+g->ram[8U]]!=0x80U)++errors;
    ++hits;
    if(mode==4U)g->ram[1U]=0U;
}
int main(void)
{
    unsigned int id,state,slot,i,expected,cases;
    cases=0U;
    for(slot=0U;slot<2U;++slot)for(id=0U;id<256U;++id)for(state=0U;state<256U;++state){
        memset(&game,0,sizeof(game));root_slot=(mysmb_u8)slot;game.ram[8U]=root_slot;
        game.ram[0x24U+slot]=1U;collisions=hits=0U;mode=0U;
        for(i=0U;i<5U;++i){game.ram[0xfU+i]=1U;game.ram[0x16U+i]=(mysmb_u8)id;game.ram[0x1eU+i]=(mysmb_u8)state;}
        expected=(!(state&0x20U)&&(id<0x24U||id>=0x2bU)&&(id!=6U||state<2U))?5U:0U;
        mysmb_world_fireball_enemy_collision(&game,root_slot);
        if(collisions!=expected||hits!=expected||game.ram[1U]!=0U)++errors;
        ++cases;
    }
    for(mode=1U;mode<=4U;++mode){
        memset(&game,0,sizeof(game));root_slot=0U;game.ram[0x24U]=1U;collisions=hits=0U;
        for(i=0U;i<5U;++i)game.ram[0xfU+i]=1U;
        mysmb_world_fireball_enemy_collision(&game,root_slot);
        if(collisions!=(mode==1U?5U:1U)||hits!=((mode==1U||mode==3U)?0U:1U))++errors;
        if(mode==2U && game.ram[0x25U]!=0x80U)++errors;
    }
    printf("%u eligibility cases and live child-state contracts; failures=%u\n",cases,errors);
    return errors?1:0;
}
