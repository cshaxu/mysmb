#include "game/objects.h"
#include "game/world/world.h"
#include "game/enemy/background.h"
#include <string.h>

static unsigned int events[5],count,bad,query_result,tile_value,side_y,jump_phase;
static void record(struct mysmb_game *game,mysmb_u8 slot,unsigned int event)
{
    if(slot!=game->ram[8] || count>=5U) {bad=1U;return;}
    events[count++]=event;
}
void mysmb_objects_step_hammer_terrain(struct mysmb_game *game,mysmb_u8 slot)
{record(game,slot,2U);}
void mysmb_objects_check_enemy_side(struct mysmb_game *game,mysmb_u8 slot)
{record(game,slot,6U);side_y=game->ram[0xcfU+slot];}
void mysmb_objects_bump_enemy(struct mysmb_game *game,mysmb_u8 slot)
{record(game,slot,7U);}
mysmb_u8 mysmb_world_query_enemy_block(struct mysmb_game *game,mysmb_u8 slot,
    mysmb_u8 index,mysmb_u8 horizontal,struct mysmb_enemy_terrain *terrain)
{
    if(index!=0x15U || horizontal!=0U) bad=1U;
    record(game,slot,jump_phase ? 3U : 1U);terrain->metatile=(mysmb_u8)tile_value;
    return (mysmb_u8)query_result;
}
mysmb_u8 mysmb_world_query_enemy_under(struct mysmb_game *game, mysmb_u8 slot,
    struct mysmb_enemy_terrain *terrain)
{
    return mysmb_world_query_enemy_block(game, slot, 0x15U, 0U, terrain);
}
mysmb_u8 mysmb_objects_is_solid_terrain(mysmb_u8 tile)
{
    if(count>=5U || tile==0U) {bad=1U;return 0U;}
    events[count++]=4U;
    return tile==0x51U ? 1U:0U;
}
void mysmb_world_land_enemy(struct mysmb_game *game,mysmb_u8 slot)
{
    record(game,slot,5U);
    game->ram[0xcfU+slot]=0x5aU;
    game->ram[0xa0U+slot]=0xabU;
}

void mysmb_objects_kill_enemy_above_block(struct mysmb_game *game, mysmb_u8 slot)
{ (void)game; (void)slot; bad = 1U; }
void mysmb_objects_setup_floatey_from_relative(struct mysmb_game *game,
    mysmb_u8 slot, mysmb_u8 control)
{ (void)game; (void)slot; (void)control; bad = 1U; }

int main(void)
{
    static struct mysmb_game game;
    static const mysmb_u8 states[]={0,1,5,0x20,0x40,0x80,0xa0,0xff};
    static const mysmb_u8 tiles[]={0,0x26,0x51};
    unsigned int slot,id,y,state,speed,tile,expected,index,probe,land;
    for(slot=0;slot<6U;++slot) for(id=0;id<54U;++id)
    for(y=0;y<256U;++y) for(state=0;state<sizeof(states);++state) {
        memset(game.ram,0,sizeof(game.ram));
        game.ram[8]=(mysmb_u8)slot;game.ram[0x16U+slot]=(mysmb_u8)id;
        game.ram[0xcfU+slot]=(mysmb_u8)y;game.ram[0x1eU+slot]=states[state];
        count=0;bad=0;
        mysmb_objects_enemy_background_current(&game,(mysmb_u8)slot);
        expected=0U;
        if((states[state]&0x20U)==0U && y>=6U && y<=193U) {
            if(id==14U) expected=6U;
            else if(id==5U) expected=2U;
            else if(id<7U || id==46U || (id==18U && y>=37U)) expected=1U;
        }
        if (expected == 6U || expected == 2U) continue;
        if (expected == 1U) {
            if (count != 2U || events[0] != 1U ||
                events[1] != (id == 3U && states[state] == 0U ? 7U : 6U)) return 1;
        }
        else if(bad || count!=(expected!=0U ? 1U:0U)) return 2;
        if(expected > 1U && events[0]!=expected) return 3;
    }
    jump_phase = 1U;
    for(slot=0;slot<6U;++slot) for(y=0;y<256U;++y)
    for(speed=0;speed<256U;++speed) for(tile=0;tile<3U;++tile)
    for(query_result=0;query_result<2U;++query_result) {
        memset(game.ram,0,sizeof(game.ram));
        game.ram[8]=(mysmb_u8)slot;game.ram[0xcfU+slot]=(mysmb_u8)y;
        game.ram[0xa0U+slot]=(mysmb_u8)speed;
        tile_value=tiles[tile];count=0;bad=0;
        mysmb_objects_step_enemy_jump_terrain(&game,(mysmb_u8)slot);
        probe=y>=6U && y<=193U && speed>=1U && speed<=253U;
        land=probe && query_result && tile==2U;index=0U;
        if(probe && events[index++]!=3U) return 3;
        if(probe && query_result && tile!=0U && events[index++]!=4U) return 4;
        if(land && events[index++]!=5U) return 5;
        if(events[index++]!=6U || count!=index || bad) return 6;
        if(game.ram[0xa0U+slot]!=(land ? 0xfdU:speed) ||
           side_y!=(land ? 0x5aU:y)) return 7;
    }
    return 0;
}
