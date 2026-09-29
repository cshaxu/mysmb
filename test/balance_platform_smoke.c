#include "game/enemy/platform.h"
#include "game/enemy/movement.h"
#include "game/enemy/init_targets.h"
#include "game/objects.h"
#include "game/world/world.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game g;
static mysmb_u8 new_y,new_speed,mode;
static unsigned int calls,failures;
static mysmb_u8 ids[8],slots[8];
static void note(mysmb_u8 id,mysmb_u8 slot)
{ if(calls>=8U){++failures;return;}ids[calls]=id;slots[calls++]=slot; }
void mysmb_objects_erase_enemy(struct mysmb_game *game,mysmb_u8 slot)
{ (void)game;note(1U,slot); }
void mysmb_world_move_platform_vertically(struct mysmb_game *game,mysmb_u8 slot,mysmb_u8 up)
{
    note(up?2U:3U,slot);
    game->ram[0xcfU+slot]=new_y;game->ram[0xa0U+slot]=new_speed;
}
void mysmb_enemy_init_vertical_state(struct mysmb_game *game,mysmb_u8 slot)
{ note(4U,slot);game->ram[0xa0U+slot]=0U;game->ram[0x434U+slot]=0U; }
void mysmb_platform_position_player_vertical(struct mysmb_game *game,mysmb_u8 slot)
{ (void)game;note(5U,slot); }
void mysmb_platform_get_offscreen(struct mysmb_game *game,mysmb_u8 slot)
{ note(6U,slot);if(mode==1U)game->ram[8U]=2U; }
void mysmb_objects_setup_floatey_from_relative(struct mysmb_game *game,mysmb_u8 slot,mysmb_u8 control)
{ note(7U,slot);if(control!=6U)++failures;if(mode==1U){game->ram[8U]=4U;game->ram[0x3adU]=0x6aU;} }
void mysmb_enemy_move_falling_platform(struct mysmb_game *game,mysmb_u8 slot)
{ note(8U,slot);if(mode==2U)game->ram[8U]=(mysmb_u8)(calls==1U?3U:4U); }
#define CHECK(c) do { if(!(c)){printf("line %d\n",__LINE__);++failures;} } while(0)
static void reset(mysmb_u8 slot)
{
    memset(g.ram,0,2048U);calls=0U;mode=0U;
    g.ram[8U]=slot;g.ram[0x1eU+slot]=1U;g.ram[0xb6U+slot]=1U;
    g.ram[0xcfU+slot]=0x80U;g.ram[0xd0U]=0x80U;
    g.ram[0x3a2U+slot]=0xffU;g.ram[0x434U+slot]=6U;
}
/* Geometric address oracle: 32 tiles per row, paired columns, alternating
 * nametables. The original separate additions select the carry interval. */
static mysmb_u16 rope_address(unsigned int x,unsigned int y,unsigned int page,
                              unsigned int hard,unsigned int negative)
{
    unsigned int carry,column,row,address;
    carry=hard?(x>=248U):(x>=232U && x<248U);
    column=(((x+(hard?8U:24U))%256U)/16U)*2U;
    row=((y+(negative?8U:0U))%256U)/8U;
    address=0x2000U+((page+carry)%2U)*0x400U+row*32U+column;
    if(y>=232U)address&=0xffbfU;
    return (mysmb_u16)address;
}
int main(void)
{
    unsigned int x,y,hard,negative;unsigned long cases;
    mysmb_u8 slot,buffer,peer_y;mysmb_u16 first,second;
    cases=0UL;
    for(x=0U;x<256U;++x)for(y=0U;y<256U;++y)
    for(hard=0U;hard<2U;++hard)for(negative=0U;negative<2U;++negative) {
        slot=(mysmb_u8)(x&1U?5U:0U);reset(slot);
        new_y=(mysmb_u8)y;new_speed=(mysmb_u8)(negative?255U:1U);
        g.ram[0x87U+slot]=(mysmb_u8)x;g.ram[0x88U]=(mysmb_u8)(255U-x);
        g.ram[0x6eU+slot]=1U;g.ram[0x6fU]=2U;g.ram[0x6ccU]=(mysmb_u8)hard;
        buffer=(mysmb_u8)(y&1U?31U:0U);g.ram[0x300U]=buffer;
        mysmb_platform_move_balance(&g,slot);peer_y=(mysmb_u8)(0U-y);
        first=rope_address(x,y,1U,hard,negative);
        second=rope_address(255U-x,peer_y,2U,hard,!negative);
        if(calls!=1U || ids[0]!=2U || slots[0]!=slot || g.ram[0xd0U]!=peer_y ||
           g.ram[0x301U+buffer]!=(mysmb_u8)(first>>8U) || g.ram[0x302U+buffer]!=(mysmb_u8)first ||
           g.ram[0x306U+buffer]!=(mysmb_u8)(second>>8U) || g.ram[0x307U+buffer]!=(mysmb_u8)second ||
           g.ram[0x303U+buffer]!=2U || g.ram[0x308U+buffer]!=2U ||
           g.ram[0x304U+buffer]!=(negative?0x24U:0xa2U) ||
           g.ram[0x305U+buffer]!=(negative?0x24U:0xa3U) ||
           g.ram[0x309U+buffer]!=(negative?0xa2U:0x24U) ||
           g.ram[0x30aU+buffer]!=(negative?0xa3U:0x24U) ||
           g.ram[0x30bU+buffer]!=0U || g.ram[0x300U]!=(mysmb_u8)(buffer+10U)) {
            printf("rope mismatch x=%u y=%u hard=%u negative=%u\n",x,y,hard,negative);return 1;
        }
        ++cases;
    }
    reset(5U);g.ram[0xbbU]=3U;mysmb_platform_move_balance(&g,5U);
    CHECK(calls==1U && ids[0]==1U && slots[0]==5U);++cases;
    reset(5U);g.ram[0x23U]=0xffU;mysmb_platform_move_balance(&g,5U);CHECK(calls==0U);++cases;
    reset(5U);g.ram[0xd4U]=0x2dU;g.ram[0x3a7U]=1U;mode=1U;
    g.ram[0xceU]=0x56U;g.ram[0xa2U]=4U;g.ram[0xa1U]=5U;
    mysmb_platform_move_balance(&g,5U);
    CHECK(calls==3U && ids[0]==6U && slots[0]==1U && ids[1]==7U && slots[1]==2U && ids[2]==4U && slots[2]==2U);
    CHECK(g.ram[0x119U]==0x6aU && g.ram[0x120U]==0x56U && g.ram[0x48U]==1U && g.ram[0xa2U]==0U && g.ram[0xa1U]==0U);++cases;
    reset(5U);g.ram[0x4bU]=1U;mode=2U;g.ram[0x3a6U]=2U;
    mysmb_platform_move_balance(&g,5U);
    CHECK(calls==3U && ids[0]==8U && slots[0]==5U && ids[1]==8U && slots[1]==1U && ids[2]==5U && slots[2]==2U);++cases;
    reset(5U);g.ram[0xd4U]=0x2cU;mysmb_platform_move_balance(&g,5U);
    CHECK(calls==1U && ids[0]==4U && g.ram[0xd4U]==0x2fU && g.ram[0xa1U]==0U);++cases;
    reset(5U);g.ram[0x300U]=32U;new_y=0x81U;new_speed=1U;
    mysmb_platform_move_balance(&g,5U);CHECK(calls==1U && g.ram[0x300U]==32U && g.ram[0x321U]==0U);++cases;
    printf("balance native cases=%lu failures=%u\n",cases,failures);return failures?1:0;
}
