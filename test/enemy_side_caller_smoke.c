#include "game/objects.h"
#include "game/world/world.h"
#include <string.h>

static unsigned int queries,solids,bumps,bad,tile_value,query_result;
mysmb_u8 mysmb_world_query_enemy_block(struct mysmb_game *game,mysmb_u8 slot,
    mysmb_u8 index,mysmb_u8 horizontal,struct mysmb_enemy_terrain *terrain)
{
    unsigned int direction=game->ram[0x46U+slot];
    if(slot!=game->ram[8] || horizontal!=1U ||
       index!=(direction==2U ? 0x16U:0x17U) || game->ram[0xeb]!=direction) bad=1U;
    ++queries;terrain->metatile=(mysmb_u8)tile_value;
    return (mysmb_u8)query_result;
}
mysmb_u8 mysmb_objects_is_solid_terrain(mysmb_u8 tile)
{
    if(queries!=1U || tile==0U) bad=1U;
    ++solids;return tile==0x51U ? 1U:0U;
}
void mysmb_objects_bump_enemy(struct mysmb_game *game,mysmb_u8 slot)
{
    if(slot!=game->ram[8] || queries!=1U || solids!=1U ||
       game->ram[0xeb]!=game->ram[0x46U+slot]) bad=1U;
    ++bumps;
    /* Tail handoff must not subsequently decrement the child's counter. */
    game->ram[0xeb]=0x77U;
}
int main(void)
{
    static struct mysmb_game game;
    static const mysmb_u8 tiles[]={0,0x26,0x51};
    unsigned int slot,y,direction,tile,active,hit,expected;
    for(slot=0;slot<6U;++slot) for(y=0;y<256U;++y)
    for(direction=0;direction<256U;++direction) for(tile=0;tile<3U;++tile)
    for(query_result=0;query_result<2U;++query_result) {
        memset(game.ram,0,sizeof(game.ram));
        game.ram[8]=(mysmb_u8)slot;game.ram[0xcfU+slot]=(mysmb_u8)y;
        game.ram[0x46U+slot]=(mysmb_u8)direction;game.ram[0xeb]=0xa5U;
        queries=0;solids=0;bumps=0;bad=0;tile_value=tiles[tile];
        mysmb_objects_check_enemy_side(&game,(mysmb_u8)slot);
        active=y>=32U && (direction==1U || direction==2U);
        hit=active && query_result && tile==2U;
        expected=y<32U ? 0xa5U:(hit ? 0x77U:0U);
        if(bad || queries!=active || solids!=(active && query_result && tile!=0U) ||
           bumps!=hit || game.ram[0xeb]!=expected) return 1;
    }
    return 0;
}
