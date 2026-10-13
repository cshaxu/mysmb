#include "core/player.h"
#include <string.h>

int main(void)
{
    static struct mysmb_game game;
    unsigned int buttons,collision,direction,state,swim,timer,rising;
    unsigned int spring,pressed,previous,y,whirlpool,size;
    unsigned int allowed,jump,expected_speed;
    for(buttons=0U;buttons<16U;++buttons)
    for(collision=0U;collision<256U;++collision) {
        memset(game.ram,0,sizeof(game.ram));
        game.ram[0x1dU]=3U;game.ram[0xbU]=(mysmb_u8)buttons;
        game.ram[0x490U]=(mysmb_u8)collision;
        game.ram[0x450U]=0xa5U;game.ram[0x456U]=0x5aU;
        allowed=buttons&collision;
        direction=allowed==0U?0U:((allowed&8U)!=0U?1U:2U);
        mysmb_player_physics_sub(&game);
        if(game.ram[0x9fU]!=(direction==0U?0U:(direction==1U?255U:1U)) ||
           game.ram[0x433U]!=(direction==0U?0U:(direction==1U?32U:255U)) ||
           game.ram[0x70cU]!=(direction==1U?8U:4U)) return 1;
        if(game.ram[0x450U]!=0xa5U || game.ram[0x456U]!=0x5aU) return 2;
    }
    for(state=0U;state<3U;++state)
    for(swim=0U;swim<2U;++swim)
    for(timer=0U;timer<2U;++timer)
    for(rising=0U;rising<2U;++rising)
    for(spring=0U;spring<2U;++spring)
    for(pressed=0U;pressed<2U;++pressed)
    for(previous=0U;previous<2U;++previous)
    for(y=0x13U;y<=0x14U;++y)
    for(whirlpool=0U;whirlpool<2U;++whirlpool)
    for(size=0U;size<2U;++size) {
        memset(game.ram,0,sizeof(game.ram));
        game.ram[0x1dU]=(mysmb_u8)state;game.ram[0x704U]=(mysmb_u8)swim;
        game.ram[0x782U]=(mysmb_u8)timer;game.ram[0x9fU]=rising!=0U?0xffU:0U;
        game.ram[0x70eU]=(mysmb_u8)spring;game.ram[0xaU]=pressed!=0U?0x80U:0U;
        game.ram[0xdU]=previous!=0U?0x80U:0U;game.ram[0xceU]=(mysmb_u8)y;
        game.ram[0x47dU]=(mysmb_u8)whirlpool;game.ram[0x754U]=(mysmb_u8)size;
        game.ram[0xb5U]=1U;game.ram[0x416U]=0x5aU;game.ram[0x433U]=0xa5U;
        game.ram[0xffU]=0x33U;game.ram[0x708U]=0xeeU;
        jump=spring==0U && pressed!=0U && previous==0U &&
             (state==0U || (swim!=0U && (timer!=0U || rising==0U)));
        mysmb_player_physics_sub(&game);
        if(jump!=0U) {
            expected_speed=swim!=0U?(y<0x14U?0U:(whirlpool!=0U?255U:254U)):252U;
            if(game.ram[0x1dU]!=1U || game.ram[0x782U]!=0x20U ||
               game.ram[0x416U]!=0U || game.ram[0x707U]!=1U ||
               game.ram[0x708U]!=y || game.ram[0x706U]!=1U ||
               game.ram[0x9fU]!=expected_speed) return 3;
            if(game.ram[0xffU]!=(swim!=0U?4U:(size!=0U?128U:1U))) return 4;
        } else if(game.ram[0x1dU]!=state || game.ram[0x782U]!=timer ||
                  game.ram[0x416U]!=0x5aU || game.ram[0x433U]!=0xa5U ||
                  game.ram[0x708U]!=0xeeU || game.ram[0xffU]!=0x33U ||
                  game.ram[0x9fU]!=(rising!=0U?255U:0U)) return 5;
    }
    return 0;
}
