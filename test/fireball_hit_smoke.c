#include "game/world/world.h"
#include "game/oam/oam.h"
#include "game/objects.h"
#include "game/enemy/init_targets.h"
#include <stdio.h>
#include <string.h>
static struct mysmb_game game;
static unsigned char prg[0x5900U];
static unsigned int failures,calls,score,stuns,inits,mutate;
static mysmb_u8 stun_a,stun_slot,score_slot;
void mysmb_oam_relative_enemy_position(struct mysmb_game *g,mysmb_u8 s)
{ (void)s;++calls;if(mutate)g->ram[1U]=2U; }
void mysmb_enemy_init_vertical_state(struct mysmb_game *g,mysmb_u8 s)
{ ++inits;g->ram[0xa0U+s]=0U;g->ram[0x434U+s]=0U; }
void mysmb_world_stun_enemy(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 a)
{ (void)g;++stuns;stun_a=a;stun_slot=s; }
void mysmb_objects_setup_floatey_from_relative(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 a)
{ (void)g;score=a;score_slot=s; }
static void reset(void)
{ memset(&game,0,sizeof(game));calls=score=stuns=inits=mutate=0U;game.ram[1U]=4U; }
int main(void)
{
    static const unsigned char identities[8]={6,0,2,18,17,7,5,45};
    unsigned int id,y,hp,world,duplicate,expected,cases;
    cases=0U;
    for(id=0U;id<256U;++id)for(y=0U;y<256U;++y){
        reset();game.ram[0x16U+4U]=(mysmb_u8)id;game.ram[0xcfU+4U]=(mysmb_u8)y;
        mysmb_world_handle_fireball_enemy_hit(&game,4U);
        expected=id!=2U&&id!=8U&&id!=12U&&id<21U;
        if(calls!=1U||stuns!=expected)++failures;
        if(expected){
            if(stun_slot!=4U||stun_a!=(id==13U?(mysmb_u8)(y+25U):id))++failures;
            if(score!=(id==5U?6U:(id==6U?1U:2U))||score_slot!=4U||game.ram[0xffU]!=8U)++failures;
        }
        ++cases;
    }
    for(duplicate=0U;duplicate<2U;++duplicate)for(world=0U;world<8U;++world)for(hp=0U;hp<256U;++hp){
        mysmb_u8 s;
        reset();s=(mysmb_u8)(duplicate?3U:4U);game.ram[0xfU+4U]=(mysmb_u8)(duplicate?0x83U:1U);
        game.ram[0x16U+s]=45U;game.ram[0x483U]=(mysmb_u8)hp;game.ram[0x75fU]=(mysmb_u8)world;
        mysmb_world_handle_fireball_enemy_hit(&game,4U);
        if(game.ram[0x483U]!=(mysmb_u8)(hp-1U)||inits!=(hp==1U?1U:0U))++failures;
        if(hp==1U && (game.ram[0x16U+s]!=identities[world]||game.ram[0x1eU+s]!=(world<3U?0x23U:0x20U)||score!=9U||score_slot!=4U||game.ram[0xfeU]!=0x80U))++failures;
        ++cases;
    }
    reset();mutate=1U;game.ram[0x16U+2U]=6U;mysmb_world_handle_fireball_enemy_hit(&game,4U);
    if(stun_slot!=2U||score_slot!=2U||score!=1U)++failures;
    for(world=0U;world<256U;++world){
        reset();prg[0x5736U+world]=(unsigned char)(world^0xa5U);
        game.area_prg=prg;game.area_prg_size=sizeof(prg);
        game.ram[0x16U+4U]=45U;game.ram[0x483U]=1U;game.ram[0x75fU]=(mysmb_u8)world;
        mysmb_world_handle_fireball_enemy_hit(&game,4U);
        if(game.ram[0x16U+4U]!=(mysmb_u8)(world^0xa5U))++failures;
    }
    printf("%u immunity/Piranha/health/world cases; live-slot and 256 unmasked PRG indices; failures=%u\n",cases,failures);
    return failures?1:0;
}
