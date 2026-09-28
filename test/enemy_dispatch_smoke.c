#include "game/enemy/core.h"
#include "game/enemy/stream.h"
#include "game/enemy/loop.h"
#include "game/enemy/actor_slots.h"
#include "game/objects.h"
#include <string.h>

static unsigned int calls[3];
static unsigned int count;
static unsigned int bad_slot;
static void record(struct mysmb_game *game,mysmb_u8 slot,unsigned int call)
{
    if(slot!=game->ram[8U]) ++bad_slot;
    if(count<3U) calls[count]=call;
    ++count;
}
#define SLOT(name,id) \
void name(struct mysmb_game *game,mysmb_u8 slot) { record(game,slot,id); }
SLOT(mysmb_objects_step_normal_enemy,1U)
SLOT(mysmb_objects_step_bowser_flames_slot,2U)
SLOT(mysmb_objects_step_fireworks_slot,3U)
SLOT(mysmb_objects_step_platforms_slot,5U)
SLOT(mysmb_objects_step_bowsers_slot,6U)
SLOT(mysmb_objects_draw_bowsers_slot,7U)
SLOT(mysmb_objects_step_star_flags_slot,11U)
SLOT(mysmb_objects_step_jumpspring,12U)
SLOT(mysmb_objects_draw_retainer,13U)
#undef SLOT
mysmb_u8 mysmb_objects_step_firebars_slot(struct mysmb_game *game,mysmb_u8 slot)
{ record(game,slot,4U);return 1U; }
void mysmb_objects_step_power_up(struct mysmb_game *game)
{ record(game,game->ram[8U],8U); }

void mysmb_objects_step_vine(struct mysmb_game *game,mysmb_u8 slot)
{ record(game,slot,10U); }
void mysmb_enemy_process_loop_command(struct mysmb_game *game,
    const struct mysmb_area_source *source,mysmb_u8 slot)
{ (void)source;record(game,slot,14U); }

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 expected[2048];
    /* Explicit ID-to-existing-child map; paired source platform targets are
     * still one legacy child and do not earn parent conformance credit. */
    static const unsigned char target[54]={
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,2,3,0,0,0,0,4,4,4,4,4,
        4,4,4,0,5,5,5,5,5,5,5,5,5,6,8,10,
        0,11,12,0,0,13
    };
    static const unsigned int erased[8]={0xfU,0x16U,0x1eU,0x110U,0x796U,0x125U,0x3c5U,0x78aU};
    unsigned int slot,id,want,low,high,lock,j,flag,peer,live;
    /* Source high-bit references read all sixteen low-nibble offsets,
     * including the self-reference case. Only a dead peer clears the flag. */
    for(slot=0U;slot<6U;++slot) for(flag=0x80U;flag<256U;++flag)
    for(live=0U;live<2U;++live) {
        memset(game.ram,0x5a,sizeof(game.ram));
        peer=flag&15U;game.ram[8U]=(mysmb_u8)slot;
        game.ram[0xfU+peer]=(mysmb_u8)live;
        game.ram[0xfU+slot]=(mysmb_u8)flag;
        memcpy(expected,game.ram,sizeof(expected));
        if(peer!=slot && live==0U) expected[0xfU+slot]=0U;
        count=0U;bad_slot=0U;
        mysmb_enemy_core_step_slot(&game,0,(mysmb_u8)slot);
        if(count!=0U || memcmp(expected,game.ram,sizeof(expected))) return 6;
    }
    for(slot=0U;slot<6U;++slot) for(j=0U;j<256U;++j) {
        memset(game.ram,0,sizeof(game.ram));game.ram[8U]=(mysmb_u8)slot;
        game.ram[0x71fU]=(mysmb_u8)j;memcpy(expected,game.ram,sizeof(expected));
        count=0U;bad_slot=0U;
        mysmb_enemy_core_step_slot(&game,0,(mysmb_u8)slot);
        if(count!=((j&7U)==7U?0U:1U) || bad_slot ||
           (count && calls[0]!=14U) || memcmp(expected,game.ram,sizeof(expected))) return 7;
    }
    for(slot=0U;slot<6U;++slot) for(id=0U;id<54U;++id) {
        memset(game.ram,0x5a,sizeof(game.ram));
        game.ram[8U]=(mysmb_u8)slot;
        game.ram[0x16U+slot]=(mysmb_u8)id;
        game.ram[0x723U]=0U;
        memcpy(expected,game.ram,sizeof(expected));
        count=0U;bad_slot=0U;
        mysmb_enemy_run_objects(&game);
        want=target[id];
        if(count!=(want==0U ? 0U : (want==6U ? 2U:1U))) return 1;
        if(want!=0U && calls[0]!=want) return 2;
        if((want==6U) && calls[1]!=want+1U) return 3;
        if(bad_slot || memcmp(expected,game.ram,sizeof(expected))!=0) return 4;
    }
    /* Exhaust both Y bytes. Cycle all slots and include control wrap; compare
     * the entire RAM image, so only the source writes may change. */
    for(low=0U;low<256U;++low) for(high=0U;high<256U;++high)
    for(lock=0U;lock<2U;++lock) {
        slot=(low+high)%6U;
        memset(game.ram,0x5a,sizeof(game.ram));
        game.ram[8U]=(mysmb_u8)slot;game.ram[0x16U+slot]=0x34U;
        game.ram[0x723U]=(mysmb_u8)(lock ? 0x80U:0U);
        game.ram[0xceU]=(mysmb_u8)low;game.ram[0xb5U]=(mysmb_u8)high;
        game.ram[0x6d6U]=(mysmb_u8)(low^high);
        memcpy(expected,game.ram,sizeof(expected));
        if(lock!=0U && (low&high)==0U) {
            expected[0x723U]=0U;
            expected[0x6d6U]=(mysmb_u8)(expected[0x6d6U]+1U);
            for(j=0U;j<8U;++j) expected[erased[j]+slot]=0U;
        }
        count=0U;
        mysmb_enemy_run_objects(&game);
        if(count!=0U || memcmp(expected,game.ram,sizeof(expected))!=0) return 5;
    }
    return 0;
}
