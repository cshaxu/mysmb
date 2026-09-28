#include "game/enemy/core.h"
#include "game/enemy/stream.h"
#include "game/enemy/actor_slots.h"
#include "game/objects.h"
#include "game/oam/oam.h"
#include <string.h>

static unsigned int unexpected;
#define UNEXPECTED_SLOT(name) \
void name(struct mysmb_game *game,mysmb_u8 slot) \
{ (void)game;(void)slot;++unexpected; }
UNEXPECTED_SLOT(mysmb_objects_step_bowser_flames_slot)
UNEXPECTED_SLOT(mysmb_objects_step_fireworks_slot)
UNEXPECTED_SLOT(mysmb_objects_step_platforms_slot)
UNEXPECTED_SLOT(mysmb_objects_step_bowsers_slot)
UNEXPECTED_SLOT(mysmb_objects_draw_bowsers_slot)
UNEXPECTED_SLOT(mysmb_objects_step_star_flags_slot)
UNEXPECTED_SLOT(mysmb_objects_step_jumpspring)
#undef UNEXPECTED_SLOT
mysmb_u8 mysmb_objects_step_firebars_slot(struct mysmb_game *game,mysmb_u8 slot)
{ (void)game;(void)slot;++unexpected;return 0U; }
void mysmb_objects_step_vine(struct mysmb_game *game,mysmb_u8 slot)
{ (void)game;(void)slot;++unexpected; }
void mysmb_objects_draw_retainer(struct mysmb_game *game,mysmb_u8 slot)
{ (void)game;(void)slot;++unexpected; }
void mysmb_objects_step_normal_enemy(struct mysmb_game *game,mysmb_u8 slot)
{ (void)game;(void)slot;++unexpected; }
void mysmb_objects_step_power_up(struct mysmb_game *game)
{ (void)game;++unexpected; }

mysmb_u8 mysmb_enemy_stream_process_current(struct mysmb_game *game,
    const struct mysmb_area_source *source,mysmb_u8 slot)
{ (void)game;(void)source;(void)slot;++unexpected;return 0U; }
mysmb_u8 mysmb_objects_get_enemy_x_offscreen_bits(const struct mysmb_game *game,mysmb_u8 slot)
{ (void)game;(void)slot;++unexpected;return 0U; }

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 before[2048];
    static const mysmb_u8 ids[7]={0x17U,0x18U,0x19U,0x1aU,0x23U,0x30U,0x33U};
    static const unsigned int erased[8]={0xfU,0x16U,0x1eU,0x110U,0x796U,0x125U,0x3c5U,0x78aU};
    unsigned int i,j,slot,timer,direction,row;
    for(slot=0U;slot<6U;++slot) for(i=0U;i<7U;++i) {
        memset(game.ram,0x5aU,sizeof(game.ram));
        game.ram[8U]=(mysmb_u8)slot;game.ram[0xfU+slot]=1U;game.ram[0x16U+slot]=ids[i];
        memcpy(before,game.ram,sizeof(before));
        mysmb_enemy_core_step_slot(&game,0,(mysmb_u8)slot);
        if(unexpected||memcmp(before,game.ram,sizeof(before))!=0) return 1;
    }
    for(slot=0U;slot<6U;++slot) {
        memset(game.ram,0x5aU,sizeof(game.ram));
        memcpy(before,game.ram,sizeof(before));
        for(j=0U;j<8U;++j) before[erased[j]+slot]=0U;
        mysmb_objects_erase_enemy(&game,(mysmb_u8)slot);
        if(memcmp(before,game.ram,sizeof(before))!=0) return 2;
    }
    for(timer=0U;timer<2U;++timer) for(direction=1U;direction<3U;++direction) {
        memset(game.ram,0,sizeof(game.ram));
        game.ram[0x16U]=0x33U;game.ram[0x6e5U]=0x20U;
        game.ram[0xcfU]=0x80U;game.ram[0x3aeU]=0x40U;
        game.ram[0x46U]=(mysmb_u8)direction;game.ram[0x78aU]=(mysmb_u8)timer;
        game.ram[0x3c5U]=0x9cU;game.ram[0xecU]=7U;game.ram[0xedU]=0x20U;
        game.ram[0x109U]=1U;
        mysmb_objects_draw_bullet_bill(&game,0U);
        if(unexpected||game.ram[0xebU]!=0x20U||game.ram[0xecU]!=0U||
           game.ram[0xedU]!=0U||game.ram[0xefU]!=8U||game.ram[0x109U]!=0U) return 3;
        for(row=0U;row<3U;++row) {
            i=0x220U+row*8U;
            if(game.ram[i]!=0x7fU+row*8U||game.ram[i+4U]!=game.ram[i]||
               game.ram[i+3U]!=0x40U||game.ram[i+7U]!=0x48U||
               game.ram[i+2U]!=(3U+(timer?0x20U:0U)+(direction==2U?0x40U:0U))) return 4;
        }
    }
    return 0;
}
