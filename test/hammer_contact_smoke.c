#include "game/world/world.h"
#include "game/objects.h"
#include <stdio.h>
#include <string.h>
static struct mysmb_game game;
static unsigned int failures,boxes,injuries,hit,change;
static mysmb_u8 root_slot;
mysmb_u8 mysmb_world_boxes_collide(const struct mysmb_game *g,mysmb_u16 a,mysmb_u16 b)
{
    if(a!=0x4acU||b!=0x4acU+(mysmb_u8)(root_slot*4U+0x24U))++failures;
    ++boxes;
    if(change)((struct mysmb_game *)g)->ram[8U]=8U;
    return (mysmb_u8)hit;
}
void mysmb_objects_force_injury(struct mysmb_game *g)
{ if(g->ram[0x6beU+g->ram[8U]]!=1U)++failures;++injuries; }
int main(void)
{
    unsigned int slot,speed,v,expected,cases;
    cases=0U;
    for(slot=0U;slot<9U;++slot)for(speed=0U;speed<256U;++speed)for(v=0U;v<8U;++v){
        memset(&game,0,sizeof(game));root_slot=(mysmb_u8)slot;
        game.ram[8U]=root_slot;game.ram[9U]=(mysmb_u8)(v==0U?0U:1U);
        game.ram[0x747U]=(mysmb_u8)(v==1U?0x80U:0U);game.ram[0x3d6U]=(mysmb_u8)(v==2U?1U:0U);
        game.ram[0x6beU+slot]=(mysmb_u8)(v==4U?1U:0U);game.ram[0x64U+slot]=(mysmb_u8)speed;
        game.ram[0x79fU]=(mysmb_u8)(v==5U?1U:0U);hit=v==3U?0U:1U;
        change=boxes=injuries=0U;mysmb_objects_check_hammer_collision(&game,root_slot);
        expected=v>=3U?1U:0U;if(boxes!=expected||injuries!=(v>=6U?1U:0U))++failures;
        if(game.ram[0x64U+slot]!=(mysmb_u8)(v>=5U?0U-speed:speed))++failures;
        ++cases;
    }
    for(hit=0U;hit<2U;++hit){
        memset(&game,0,sizeof(game));root_slot=0U;game.ram[9U]=1U;game.ram[0x6beU+8U]=(mysmb_u8)(hit?0U:1U);
        game.ram[0x64U+8U]=0x10U;game.ram[0x79fU]=1U;change=1U;boxes=injuries=0U;
        mysmb_objects_check_hammer_collision(&game,root_slot);
        if(game.ram[0x6beU+8U]!=hit||game.ram[0x64U+8U]!=(hit?0xf0U:0x10U))++failures;
    }
    for(slot=0U;slot<256U;++slot){
        memset(&game,0,sizeof(game));root_slot=(mysmb_u8)slot;game.ram[9U]=1U;
        game.ram[8U]=root_slot;hit=change=0U;mysmb_objects_check_hammer_collision(&game,root_slot);
    }
    printf("%u gate/latch/speed cases; live hit/miss slot and 256 wrapped box indices; failures=%u\n",cases,failures);
    return failures?1:0;
}
