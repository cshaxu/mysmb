#include "core/player.h"
#include <string.h>

static unsigned int controls;
static mysmb_u8 input;
void mysmb_player_step(struct mysmb_game *game, mysmb_u8 buttons)
{
    ++controls;
    input = buttons;
    /* Caller must preserve the returned child state, including timer/task. */
    game->ram[0x0747U] = 0x51U;
    game->ram[0x000eU] = 0x52U;
}

int main(void)
{
    static struct mysmb_game game;
    unsigned int timer, flag, size, attributes, frame;
    for (timer=0U; timer<256U; ++timer)
    for (flag=0U; flag<256U; ++flag) {
        for (size=0U; size<2U; ++size) {
            memset(&game,0,sizeof(game));
            game.ram[0x747U]=(mysmb_u8)timer;
            game.ram[0x70bU]=(mysmb_u8)flag;
            game.ram[0x70dU]=0x7fU;game.ram[0xeU]=9U;
            game.ram[0x754U]=(mysmb_u8)size;
            mysmb_player_step_change_size(&game);
            if(game.ram[0x747U]!=(timer==0xc4U?0U:timer) ||
               game.ram[0xeU]!=(timer==0xc4U?8U:9U)) return 1;
            if(game.ram[0x70bU]!=(timer==0xf8U && flag==0U?1U:flag) ||
               game.ram[0x70dU]!=(timer==0xf8U && flag==0U?0U:0x7fU) ||
               game.ram[0x754U]!=(timer==0xf8U && flag==0U?size^1U:size)) return 2;
        }
    }
    for(flag=0U;flag<256U;++flag)
    for(size=0U;size<256U;++size) {
        controls=0U;game.ram[0x747U]=0xf0U;game.ram[0xeU]=10U;
        game.ram[0x70bU]=(mysmb_u8)flag;game.ram[0x754U]=(mysmb_u8)size;
        game.ram[0x70dU]=5U;
        mysmb_player_step_injury_blink(&game,0U);
        if(controls!=0U || game.ram[0x70bU]!=(flag==0U?1U:flag) ||
           game.ram[0x754U]!=(flag==0U?size^1U:size) ||
           game.ram[0x70dU]!=(flag==0U?0U:5U) ||
           game.ram[0x747U]!=0xf0U || game.ram[0xeU]!=10U) return 13;
    }
    for(timer=0U;timer<256U;++timer) {
        controls=0U;game.ram[0x747U]=(mysmb_u8)timer;game.ram[0xeU]=10U;
        mysmb_player_step_injury_blink(&game,0x82U);
        if(timer>=0xf0U) {
            if(controls!=0U || game.ram[0x747U]!=timer || game.ram[0xeU]!=10U) return 3;
        } else if(timer==0xc8U) {
            if(controls!=0U || game.ram[0x747U]!=0U || game.ram[0xeU]!=8U) return 4;
        } else if(controls!=1U || input!=0x82U || game.ram[0x747U]!=0x51U || game.ram[0xeU]!=0x52U) return 5;
        controls=0U;game.ram[0x747U]=(mysmb_u8)timer;game.ram[0xeU]=11U;game.ram[0x6fcU]=0x43U;
        mysmb_player_step_death(&game);
        if(controls!=(timer<0xf0U?1U:0U)) return 6;
        if(timer<0xf0U && (input!=0x43U || game.ram[0x747U]!=0x51U || game.ram[0xeU]!=0x52U)) return 7;
        if(timer>=0xf0U && (game.ram[0x747U]!=timer || game.ram[0xeU]!=11U)) return 8;
    }
    for(attributes=0U;attributes<256U;++attributes)
    for(frame=0U;frame<256U;++frame) {
        game.ram[0x3c4U]=(mysmb_u8)attributes;
        mysmb_player_cycle_palette(&game,(mysmb_u8)frame);
        if(game.ram[0x3c4U]!=(attributes/4U*4U+frame%4U) || game.ram[0]!=frame%4U) return 9;
        mysmb_player_reset_palette(&game);
        if(game.ram[0x3c4U]!=attributes/4U*4U) return 10;
        game.ram[0x3c4U]=(mysmb_u8)attributes;game.ram[9U]=(mysmb_u8)frame;
        game.ram[0x747U]=0xc1U;game.ram[0xeU]=12U;
        mysmb_player_step_fire_flower(&game);
        if(game.ram[0x3c4U]!=(attributes/4U*4U+(frame/4U)%4U) || game.ram[0x747U]!=0xc1U || game.ram[0xeU]!=12U) return 11;
        game.ram[0x747U]=0xc0U;
        mysmb_player_step_fire_flower(&game);
        if(game.ram[0x3c4U]!=attributes/4U*4U || game.ram[0x747U]!=0U || game.ram[0xeU]!=8U) return 12;
    }
    return 0;
}
