#include "game/objects.h"
#include "game/area.h"
#include "game/world/world.h"
#include "game/enemy/distance.h"
#include "game/enemy/init_targets.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game g;
static unsigned int errors, palettes, stuns, turns, pickups, defeats, boxes;
static mysmb_u8 hit, vertical, next_slot, sign;
static void check(int condition) { if (!condition) ++errors; }
static void reset(void)
{
    memset(&g, 0, sizeof(g));
    palettes=stuns=turns=pickups=defeats=boxes=0U;
    hit=1U;vertical=0U;next_slot=0U;sign=0U;
    g.ram[0xeU]=8U;g.ram[0x74eU]=1U;g.ram[0x3aeU]=0x78U;
}
mysmb_u8 mysmb_area_queue_player_palette(struct mysmb_game *game)
{
    check(game->ram[0x79eU]==8U && game->ram[0xffU]==0x10U);
    ++palettes;return 1U;
}
mysmb_u8 mysmb_enemy_player_difference(struct mysmb_game *game,mysmb_u8 slot)
{ (void)game;(void)slot;return sign; }
void mysmb_enemy_init_vertical_state(struct mysmb_game *game,mysmb_u8 slot)
{ game->ram[0xa0U+slot]=0U;game->ram[0x434U+slot]=0U; }
void mysmb_world_set_stun(struct mysmb_game *game,mysmb_u8 slot)
{ ++stuns;game->ram[0x46U+slot]=0xffU;game->ram[0xcfU+slot]-=2U; }
void mysmb_objects_turn_enemy(struct mysmb_game *game,mysmb_u8 slot)
{ (void)game;(void)slot;++turns; }
mysmb_u8 mysmb_world_player_vertical_carry(struct mysmb_game *game)
{ (void)game;return vertical; }
mysmb_u8 mysmb_world_enemy_box_offset(struct mysmb_game *game)
{ return (mysmb_u8)(game->ram[8U]*4U+4U); }
mysmb_u8 mysmb_world_boxes_collide(struct mysmb_game *game,
    mysmb_u16 first,mysmb_u16 second)
{
    check(first==0x4acU && second==0x4acU+(mysmb_u8)(game->ram[8U]*4U+4U));
    ++boxes;
    /* Test-owned object, exposed const by the legacy geometry interface. */
    g.ram[8U]=next_slot;
    return hit;
}
void mysmb_objects_collect_power_up(struct mysmb_game *game,mysmb_u8 slot)
{ check(slot==game->ram[8U]);++pickups; }
void mysmb_world_shell_or_block_defeat(struct mysmb_game *game,mysmb_u8 slot)
{ check(slot==game->ram[8U]);++defeats; }

int main(void)
{
    unsigned int slot,timer,status,chain,direction,cases;
    static const mysmb_u8 kick[3]={10U,6U,4U};
    cases=0U;
    for(slot=0U;slot<6U;++slot)
    for(timer=0U;timer<256U;++timer)
    for(chain=0U;chain<256U;++chain) {
        reset();g.ram[0x16U+slot]=0U;g.ram[0x1eU+slot]=4U;
        g.ram[0x796U+slot]=(mysmb_u8)timer;g.ram[0x484U]=(mysmb_u8)chain;
        g.ram[0xcfU+slot]=0x89U;sign=(mysmb_u8)(chain&0x80U);
        mysmb_objects_handle_player_enemy_contact(&g,(mysmb_u8)slot,0U);
        check(g.ram[0x110U+slot]==(timer<3U?kick[timer]:(mysmb_u8)(chain+3U)));
        check(g.ram[0x117U+slot]==0x78U && g.ram[0x11eU+slot]==0x89U);
        check(g.ram[0x12cU+slot]==0x30U && g.ram[0xffU]==8U);
        check(g.ram[0x1eU+slot]==0x84U && g.ram[0x491U+slot]==1U);
        check(g.ram[0x58U+slot]==(sign?0xd0U:0x30U));++cases;
    }
    for(timer=0U;timer<256U;++timer)
    for(status=0U;status<256U;++status) {
        reset();g.ram[0x79eU]=(mysmb_u8)timer;g.ram[0x756U]=(mysmb_u8)status;
        mysmb_objects_force_injury(&g);
        check(g.ram[0xeU]==(timer?8U:(status?10U:11U)));
        check(palettes==(timer==0U&&status!=0U?1U:0U));
        reset();g.ram[0x79eU]=(mysmb_u8)timer;g.ram[0x756U]=(mysmb_u8)status;
        mysmb_objects_force_injury_entry(&g,0U);
        check(g.ram[0xeU]==(status?10U:11U) && g.ram[0x1dU]==1U);
        check(g.ram[0x747U]==0xffU && g.ram[0x775U]==0U);
        check(palettes==(status?1U:0U));++cases;
    }
    for(slot=0U;slot<6U;++slot)
    for(direction=0U;direction<256U;++direction) {
        reset();g.ram[0x16U+slot]=7U;g.ram[0xcfU+slot]=0U;
        g.ram[0x46U+slot]=(mysmb_u8)direction;
        mysmb_objects_enemy_stomped(&g,(mysmb_u8)slot);
        check(stuns==1U && g.ram[0x46U+slot]==direction);
        check(g.ram[0x110U+slot]==6U && g.ram[0x11eU+slot]==0U);
        check(g.ram[0xcfU+slot]==0xfeU && g.ram[0x1eU+slot]==0x20U);
        check(g.ram[0x9fU]==0xfdU && g.ram[0xffU]==4U);++cases;
    }
    reset();g.ram[8U]=1U;next_slot=4U;g.ram[0x491U+4U]=0xffU;hit=0U;
    mysmb_objects_player_enemy_current(&g,1U,1U);
    check(boxes==1U && g.ram[0x491U+4U]==0xfeU && g.ram[0x491U+1U]==0U);
    reset();g.ram[8U]=1U;next_slot=5U;g.ram[0x16U+5U]=0x2eU;g.ram[0x79fU]=1U;
    mysmb_objects_player_enemy_current(&g,1U,1U);check(pickups==1U&&defeats==0U);
    reset();g.ram[8U]=1U;next_slot=4U;g.ram[0x79fU]=1U;
    mysmb_objects_player_enemy_current(&g,1U,1U);check(defeats==1U&&pickups==0U);
    reset();vertical=1U;mysmb_objects_player_enemy_current(&g,0U,1U);check(boxes==0U);
    reset();g.ram[9U]=1U;mysmb_objects_player_enemy_current(&g,0U,1U);check(boxes==0U);
    check(mysmb_residual_x_speeds[0]==0x18U&&mysmb_residual_x_speeds[1]==0xe8U);
    printf("%u kick/injury/stomp cases plus live-slot and gate contracts; failures=%u\n",cases,errors);
    return errors?1:0;
}
