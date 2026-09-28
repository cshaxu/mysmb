#include "game/player.h"
#include <string.h>

int main(void)
{
    static struct mysmb_game game;
    static const unsigned int friction[4]={0U,0x98U,0x1c8U,0x1ffU};
    unsigned int speed,force,k,buttons,moving,index,raw,absolute,expected;
    unsigned int add,delta;
    for(speed=0U;speed<256U;++speed)
    for(force=0U;force<256U;++force)
    for(k=0U;k<8U;++k) {
        memset(game.ram,0,sizeof(game.ram));
        game.ram[0x57U]=(mysmb_u8)speed;game.ram[0x705U]=(mysmb_u8)force;
        game.ram[0x701U]=(mysmb_u8)(friction[k%4U]/256U);
        game.ram[0x702U]=(mysmb_u8)friction[k%4U];
        game.ram[0xcU]=k<4U?1U:2U;game.ram[0x490U]=3U;
        game.ram[0x450U]=0xd8U;game.ram[0x456U]=0x28U;
        add=k<4U;
        if(add) raw=(speed*256U+force+friction[k%4U])%65536UL;
        else raw=(speed*256UL+force+65536UL-friction[k%4U])%65536UL;
        expected=raw/256U;
        delta=(expected+256U-(add?0x28U:0xd8U))%256U;
        if((add && delta<128U) || (!add && delta>=128U)) expected=add?0x28U:0xd8U;
        absolute=expected<128U?expected:256U-expected;
        mysmb_player_impose_friction(&game);
        if(game.ram[0x705U]!=(mysmb_u8)raw || game.ram[0x57U]!=expected ||
           game.ram[0x700U]!=absolute) return 1;
    }
    for(speed=0U;speed<256U;++speed)
    for(buttons=0U;buttons<256U;++buttons)
    for(moving=1U;moving<3U;++moving) {
        memset(game.ram,0,sizeof(game.ram));
        game.ram[0x700U]=(mysmb_u8)speed;game.ram[0x45U]=(mysmb_u8)moving;
        game.ram[0x33U]=(mysmb_u8)(moving^3U);
        game.ram[0x703U]=0x5aU;game.ram[0x57U]=0x17U;game.ram[0x705U]=0xa5U;
        mysmb_player_update_animation_speed(&game,(mysmb_u8)buttons);
        index=speed>=28U?2U:(speed>=14U?4U:7U);
        if(game.ram[0x70cU]!=index) return 2;
        if(speed>=28U) {
            if(game.ram[0x703U]!=speed) return 3;
        } else if((buttons&127U)==0U) {
            if(game.ram[0x703U]!=0x5aU) return 4;
        } else if((buttons&3U)==moving) {
            if(game.ram[0x703U]!=0U) return 5;
        } else if(speed<11U) {
            if(game.ram[0x57U]!=0U || game.ram[0x705U]!=0U ||
               game.ram[0x45U]!=(moving^3U)) return 6;
        }
    }
    return 0;
}
