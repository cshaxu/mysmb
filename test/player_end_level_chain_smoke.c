#include "game/player.h"
#include "core/area.h"
#include "core/frame_root.h"
#include <string.h>

static unsigned int calls,loads,modes;
static mysmb_u8 input,mutate,area_seen,timer_seen;
void mysmb_player_auto_control(struct mysmb_game *game,mysmb_u8 buttons)
{
    ++calls;input=buttons;
    if(mutate!=0U) {
        game->ram[0xceU]=0xaeU;game->ram[0x723U]=1U;
        game->ram[0x490U]=0U;game->ram[0x746U]=5U;
        game->ram[0x75cU]=2U;
    }
}
mysmb_u8 mysmb_area_load_area_pointer(struct mysmb_game *game,
                                     const struct mysmb_area_source *source)
{
    (void)source;++loads;area_seen=game->ram[0x760U];
    if(mutate!=0U) game->ram[0x757U]=0xffU;
    return 1U;
}
void mysmb_player_change_area_mode(struct mysmb_game *game)
{
    ++modes;timer_seen=game->ram[0x757U];
    ++game->ram[0x774U];game->ram[0x772U]=0U;game->ram[0x722U]=0U;
}

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 data[0x3400U];
    unsigned int id,y,world,coins,state,collision;
    for(id=0U;id<256U;++id)
    for(y=0U;y<256U;++y) {
        memset(game.ram,0,sizeof(game.ram));calls=0U;
        game.ram[0x1bU]=(mysmb_u8)id;game.ram[0xceU]=(mysmb_u8)y;
        game.ram[0xeU]=0xffU;game.ram[0x713U]=0x42U;game.ram[0xffU]=0x81U;
        mysmb_player_step_flagpole_slide(&game);
        if(id==0x30U) {
            if(calls!=1U || input!=(y<0x9eU?4U:0U) || game.ram[0xffU]!=0x42U ||
               game.ram[0x713U]!=0U || game.ram[0xeU]!=0xffU) return 1;
        } else if(calls!=0U || game.ram[0xeU]!=0U ||
                  game.ram[0x713U]!=0x42U || game.ram[0xffU]!=0x81U) return 2;
    }
    for(y=0U;y<256U;++y)
    for(state=0U;state<5U;++state)
    for(collision=0U;collision<2U;++collision) {
        memset(game.ram,0,sizeof(game.ram));calls=loads=modes=0U;
        game.ram[0xceU]=(mysmb_u8)y;game.ram[0x746U]=(mysmb_u8)state;
        game.ram[0x490U]=(mysmb_u8)collision;game.ram[0x723U]=1U;
        game.ram[0xfcU]=0x80U;game.ram[0x3c4U]=0xa3U;
        mysmb_player_step_end_level(&game);
        if(calls!=1U || input!=1U || loads!=0U || modes!=0U) return 3;
        if(game.ram[0xfcU]!=(y>=0xaeU?0x20U:0x80U) ||
           game.ram[0x723U]!=(y>=0xaeU?0U:1U)) return 4;
        if(game.ram[0x746U]!=(state==0U && collision==0U?1U:state) ||
           game.ram[0x3c4U]!=(collision==0U?0x20U:0xa3U)) return 5;
    }
    game.area_prg=data;game.area_prg_size=sizeof(data);
    for(world=0U;world<256U;++world) data[0x32c2U+world]=(mysmb_u8)(world^0x5aU);
    for(world=0U;world<256U;++world)
    for(coins=0U;coins<256U;++coins) {
        memset(game.ram,0,sizeof(game.ram));calls=loads=modes=0U;mutate=1U;
        game.ram[0x75fU]=(mysmb_u8)world;game.ram[0x748U]=(mysmb_u8)coins;
        game.ram[0x75dU]=0xffU;game.ram[0x760U]=0xffU;
        game.ram[0x75bU]=7U;game.ram[0x774U]=0xffU;game.ram[0x722U]=1U;game.ram[0x772U]=3U;
        mysmb_player_step_end_level(&game);
        if(calls!=1U || loads!=1U || modes!=1U || area_seen!=0U || timer_seen!=0U) return 6;
        if(game.ram[0x75dU]!=(coins>=(world^0x5aU)?0U:0xffU) || game.ram[0x75cU]!=3U) return 7;
        if(game.ram[0x75bU]!=0U || game.ram[0xfcU]!=0x80U || game.ram[0x774U]!=0U ||
           game.ram[0x722U]!=0U || game.ram[0x772U]!=0U || game.ram[0x3c4U]!=0x20U) return 8;
    }
    return 0;
}
