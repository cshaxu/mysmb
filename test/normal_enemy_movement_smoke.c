#include "game/enemy/movement.h"
#include "game/objects.h"
#include "game/world/world.h"
#include <string.h>

static unsigned int horizontal_calls,erase_calls,observed_speed,observed_y;
void mysmb_world_move_enemy_horizontally(struct mysmb_game *game,mysmb_u8 slot)
{
    ++horizontal_calls;
    observed_speed=game->ram[0x58U+slot];observed_y=game->ram[0xcfU+slot];
    /* A caller saving speed must restore its input even across a mutating
     * test child; direct tail callers must leave the child's result intact. */
    game->ram[0x58U+slot]=0x55U;
}
void mysmb_objects_erase_enemy(struct mysmb_game *game,mysmb_u8 slot)
{ (void)game;(void)slot;++erase_calls; }

int main(void)
{
    /* Branch expectations from the source state priority. 0=steady,
     * 1=fall/temporary speed, 2=fall/direct, 3=revive, 4=defeated/direct. */
    static const unsigned char cases[][2]={
        {0,0},{1,1},{2,2},{3,3},{4,3},{5,1},{6,3},{7,3},
        {0x20,4},{0x21,4},{0x40,1},{0x41,1},{0x60,1},
        {0x80,0},{0x83,0},{0xa0,0},{0xc0,1}
    };
    static const unsigned char ids[]={0,6,18,0x2e};
    static const unsigned char timers[]={0,0x0e,0x10};
    static struct mysmb_game game;
    unsigned int c,slot,speed,id,hard,phase,timer,action,want;
    for(c=0U;c<sizeof(cases)/sizeof(cases[0]);++c)
    for(slot=0U;slot<6U;++slot) for(speed=0U;speed<256U;++speed)
    for(id=0U;id<4U;++id) for(hard=0U;hard<2U;++hard)
    for(phase=0U;phase<2U;++phase) for(timer=0U;timer<3U;++timer) {
        memset(game.ram,0,sizeof(game.ram));
        game.ram[8U]=(mysmb_u8)slot;game.ram[9U]=(mysmb_u8)phase;
        game.ram[0x16U+slot]=ids[id];game.ram[0x1eU+slot]=cases[c][0];
        game.ram[0x58U+slot]=(mysmb_u8)speed;
        game.ram[0x796U+slot]=timers[timer];game.ram[0x76aU]=(mysmb_u8)hard;
        game.ram[0xcfU+slot]=0x70U;game.ram[0xb6U+slot]=1U;
        game.ram[0xa0U+slot]=1U;game.ram[0x434U+slot]=0x80U;
        game.ram[0x417U+slot]=0x80U;
        horizontal_calls=0U;erase_calls=0U;
        mysmb_enemy_move_normal(&game,(mysmb_u8)slot);
        action=cases[c][1];
        if(action==3U) {
            if(horizontal_calls || game.ram[0xcfU+slot]!=0x70U) return 1;
            if(timers[timer]==0U) {
                want=hard ? 12U:8U;
                if(phase) want=(256U-want)&255U;
                if(game.ram[0x58U+slot]!=want || game.ram[0x1eU+slot]!=0U ||
                   game.ram[0x46U+slot]!=phase+1U || erase_calls) return 2;
            } else {
                want=timers[timer]==0x0eU && ids[id]==6U ? 1U:0U;
                if(erase_calls!=want || game.ram[0x58U+slot]!=speed) return 3;
            }
        } else {
            if(horizontal_calls!=1U || erase_calls) return 4;
            if(observed_y!=(action==0U ? 0x70U:0x72U)) return 5;
            want=action==0U ? 0x80U:(cases[c][0]==5U ? 0xa0U:0xbdU);
            if(game.ram[0x434U+slot]!=want) return 9;
            want=speed;
            if(action==1U && (cases[c][0]&0x40U)!=0U && ids[id]!=0x2eU)
                want=(speed+(speed<128U ? 232U:24U))&255U;
            if(observed_speed!=want) return 6;
            want=action==2U || action==4U ? 0x55U:speed;
            if(game.ram[0x58U+slot]!=want) return 7;
        }
        if(game.ram[8U]!=slot) return 8;
    }
    return 0;
}
