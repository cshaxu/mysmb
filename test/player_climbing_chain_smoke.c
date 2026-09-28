#include "game/player.h"
#include <string.h>

int main(void)
{
    static struct mysmb_game game;
    static const unsigned char speeds[6] = {0U,1U,0x7fU,0x80U,0xfeU,0xffU};
    static const unsigned char forces[6] = {0U,1U,0xffU,0x20U,0x80U,0xffU};
    static const int offsets[2][2] = {{14,4},{-4,-14}};
    unsigned int y,dummy,k,buttons,collision,facing,x,timer;
    unsigned long initial,expected;
    int delta;
    /* Independent 24-bit fixed-point addition checks the two ADC carries
     * together, including downward and upward page wrapping. */
    for(k=0U;k<6U;++k)
    for(y=0U;y<256U;++y)
    for(dummy=0U;dummy<256U;++dummy) {
        memset(game.ram,0,sizeof(game.ram));
        game.ram[0xb5U]=k%2U!=0U?0xffU:0U;
        game.ram[0xceU]=(mysmb_u8)y;game.ram[0x416U]=(mysmb_u8)dummy;
        game.ram[0x9fU]=speeds[k];game.ram[0x433U]=forces[k];
        game.ram[0x789U]=9U;
        initial=((unsigned long)game.ram[0xb5U]<<16)+(y*256UL)+dummy;
        delta=speeds[k]<128U?(int)speeds[k]:(int)speeds[k]-256;
        expected=(initial+(unsigned long)((long)delta*256L)+forces[k])&0xffffffUL;
        mysmb_player_climb(&game);
        if(game.ram[0x416U]!=(mysmb_u8)expected ||
           game.ram[0xceU]!=(mysmb_u8)(expected>>8) ||
           game.ram[0xb5U]!=(mysmb_u8)(expected>>16) ||
           game.ram[0x789U]!=0U) return 1;
    }
    /* Controller and collision masks independently select which side is
     * allowed. Facing selects the nearer/farther displacement on that side. */
    for(buttons=0U;buttons<4U;++buttons)
    for(collision=0U;collision<4U;++collision)
    for(facing=1U;facing<3U;++facing)
    for(x=0U;x<256U;++x)
    for(timer=0U;timer<2U;++timer) {
        memset(game.ram,0,sizeof(game.ram));
        game.ram[0xcU]=(mysmb_u8)buttons;game.ram[0x490U]=(mysmb_u8)collision;
        game.ram[0x33U]=(mysmb_u8)facing;game.ram[0x789U]=(mysmb_u8)timer;
        game.ram[0x6dU]=x%2U!=0U?0xffU:0U;game.ram[0x86U]=(mysmb_u8)x;
        initial=game.ram[0x6dU]*256UL+x;
        expected=initial;
        if((buttons&collision)!=0U && timer==0U) {
            delta=offsets[(buttons&collision&1U)!=0U?0U:1U][facing-1U];
            expected=(initial+(unsigned long)delta)&0xffffUL;
        }
        mysmb_player_climb(&game);
        if(game.ram[0x86U]!=(mysmb_u8)expected ||
           game.ram[0x6dU]!=(mysmb_u8)(expected>>8)) return 2;
        if((buttons&collision)==0U) {
            if(game.ram[0x789U]!=0U || game.ram[0x33U]!=facing) return 3;
        } else if(timer!=0U) {
            if(game.ram[0x789U]!=timer || game.ram[0x33U]!=facing) return 4;
        } else if(game.ram[0x789U]!=0x18U || game.ram[0x33U]!=(buttons^3U)) return 5;
    }
    return 0;
}
