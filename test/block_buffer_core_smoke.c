#include <string.h>
#include "game/world/world.h"
int main(void)
{
    struct mysmb_game game;
    struct mysmb_enemy_terrain terrain;
    struct mysmb_player_terrain player;
    static const mysmb_u8 x_adders[28] = {
        8U,3U,12U,2U,2U,13U,13U,8U,3U,12U,2U,2U,13U,13U,
        8U,3U,12U,2U,2U,13U,13U,8U,0U,16U,4U,20U,4U,4U
    };
    static const mysmb_u8 y_adders[28] = {
        4U,32U,32U,8U,24U,8U,24U,2U,32U,32U,8U,24U,8U,24U,
        18U,32U,32U,24U,24U,24U,24U,24U,20U,20U,6U,6U,8U,16U
    };
    mysmb_u8 index;
    mysmb_u8 row;
    mysmb_u16 address;
    unsigned int i;
    memset(&game,0,sizeof(game));
    game.ram[0x006eU]=0U; game.ram[0x0087U]=0xfcU;
    game.ram[0x00cfU]=0x40U; game.ram[0x0600U]=0x26U;
    if (mysmb_world_query_enemy_block(&game,0U,0x1bU,1U,&terrain)==0U) return 1;
    if (game.ram[2U]!=0x30U || game.ram[3U]!=0x26U || game.ram[4U]!=0x0cU ||
        game.ram[5U]!=0U || game.ram[6U]!=0xd0U || game.ram[7U]!=5U) return 2;
    game.ram[0x006dU]=1U; game.ram[0x0086U]=0U; game.ram[0x00ceU]=0U;
    game.ram[0x05d0U+0xe0U]=0x61U;
    if (mysmb_world_query_player_block(&game,0U,0U,0U,&player)==0U) return 3;
    if (game.ram[2U]!=0xe0U || game.ram[3U]!=0x61U) return 4;
    memset(&game,0,sizeof(game));
    game.ram[0x006dU+0x0dU]=0U; game.ram[0x0086U+0x0dU]=0xfcU;
    game.ram[0x00ceU+0x0dU]=0x40U; game.ram[0x0600U]=0x26U;
    if (mysmb_world_query_misc_block(&game,0U,&terrain)==0U ||
        terrain.metatile!=0x26U || game.ram[4U]!=0U ||
        game.ram[5U]!=0U || game.ram[2U]!=0x30U) return 5;
    {
        static mysmb_u8 prg[0x6400U];
        memset(&game,0,sizeof(game));
        prg[0x63b0U+0x15U]=0x0fU; prg[0x63ccU+0x15U]=0x30U;
        game.area_prg=prg; game.area_prg_size=sizeof(prg);
        game.ram[0x006eU]=0U; game.ram[0x0087U]=0x10U;
        game.ram[0x00cfU]=0x40U; game.ram[0x0551U]=0x62U;
        if(mysmb_world_query_enemy_block(&game,0U,0x15U,0U,&terrain)==0U ||
           terrain.metatile!=0x62U || game.ram[5U]!=0x1fU || game.ram[2U]!=0x50U) return 6;
    }
    for (i=0U;i<28U;++i) {
        memset(&game,0,sizeof(game));
        game.ram[0x006dU]=0U; game.ram[0x0086U]=0U; game.ram[0x00ceU]=0x40U;
        row=(mysmb_u8)(((0x40U+y_adders[i])&0xf0U)-0x20U);
        address=(mysmb_u16)(0x0500U+(x_adders[i]>>4U));
        game.ram[address+row]=(mysmb_u8)(i+1U);
        index=(mysmb_u8)i;
        if(mysmb_world_query_player_probe(&game,&index,MYSMB_TERRAIN_HEAD,&player)==0U ||
           player.metatile!=(mysmb_u8)(i+1U) || game.ram[5U]!=x_adders[i] ||
           game.ram[2U]!=row || game.ram[4U]!=0U) return 7;
    }
    return 0;
}
