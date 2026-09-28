#include "game/enemy/core.h"
#include "game/enemy/actor_slots.h"
#include "game/enemy/movement.h"
#include "game/objects.h"
#include "game/oam/oam.h"
#include <string.h>

static unsigned int events[12],count,bad,mutation;
static void record(struct mysmb_game *game,mysmb_u8 slot,unsigned int event)
{
    if(slot!=game->ram[8U] || count>=12U) {++bad;return;}
    events[count++]=event;
}
mysmb_u8 mysmb_objects_get_enemy_offscreen_bits(const struct mysmb_game *game,mysmb_u8 slot)
{
    if(slot!=game->ram[8U] || game->ram[0x3c5U+slot]!=0U) ++bad;
    events[count++]=1U;return 0x56U;
}
void mysmb_oam_relative_enemy_position(struct mysmb_game *game,mysmb_u8 slot)
{ if(game->ram[0x3d1U]!=0x56U) ++bad;record(game,slot,2U); }
#define SLOT(name,event) \
void name(struct mysmb_game *game,mysmb_u8 slot) {record(game,slot,event);}
SLOT(mysmb_objects_draw_goomba,3U)
SLOT(mysmb_objects_update_enemy_bounding_box,4U)
SLOT(mysmb_objects_enemy_background_current,5U)
SLOT(mysmb_objects_step_enemy_collisions_current,6U)
SLOT(mysmb_objects_check_enemy_offscreen_bounds,8U)
SLOT(mysmb_enemy_move_normal,100U)
SLOT(mysmb_objects_step_hammer_bros_slot,101U)
SLOT(mysmb_objects_step_bloobers_slot,102U)
SLOT(mysmb_objects_step_bullet_bills_slot,103U)
SLOT(mysmb_objects_step_swimming_cheep_cheeps_slot,104U)
SLOT(mysmb_objects_step_podoboos_slot,105U)
SLOT(mysmb_objects_step_piranha_plants_slot,106U)
SLOT(mysmb_objects_step_jumping_paratroopas_slot,107U)
SLOT(mysmb_objects_step_red_paratroopas_slot,108U)
SLOT(mysmb_objects_step_flying_green_paratroopas_slot,109U)
SLOT(mysmb_enemy_step_lakitus_slot,110U)
SLOT(mysmb_objects_step_flying_cheep_cheeps_slot,111U)
#undef SLOT
mysmb_u8 mysmb_objects_draw_normal_enemy_graphics(struct mysmb_game *game,mysmb_u8 slot)
{record(game,slot,3U);return 1U;}
void mysmb_objects_player_enemy_current(struct mysmb_game *game,mysmb_u8 slot,
                                        mysmb_u8 preserve_collision_boxes)
{
    if(preserve_collision_boxes!=1U) ++bad;
    record(game,slot,7U);
    if(mutation==1U) game->ram[0x16U+slot]=17U;
    if(mutation==2U) game->ram[0x747U]^=1U;
    /* A cleared flag must not invent a caller-side early return. */
    game->ram[0xfU+slot]=0U;
}

int main(void)
{
    static const unsigned int target[21]={100,100,100,100,100,101,100,
        102,103,0,104,104,105,106,107,108,109,110,100,0,111};
    static struct mysmb_game game;
    unsigned int id,slot,paused,i,want;
    for(id=0U;id<21U;++id) for(slot=0U;slot<6U;++slot)
    for(paused=0U;paused<2U;++paused) for(mutation=0U;mutation<3U;++mutation) {
        memset(game.ram,0,sizeof(game.ram));
        game.ram[8U]=(mysmb_u8)slot;game.ram[0x16U+slot]=(mysmb_u8)id;
        game.ram[0x747U]=(mysmb_u8)paused;game.ram[0x3c5U+slot]=0xffU;
        count=0U;bad=0U;
        mysmb_objects_step_normal_enemy(&game,(mysmb_u8)slot);
        for(i=0U;i<7U;++i) if(events[i]!=i+1U) return 1;
        want=game.ram[0x747U]!=0U ? 0U:target[mutation==1U ? 17U:id];
        if(count!=(want ? 9U:8U) || events[count-1U]!=8U || bad) return 2;
        if(want && events[7U]!=want) return 3;
    }
    return 0;
}
