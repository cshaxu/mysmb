#include "game/player.h"
#include <stdio.h>
#include <string.h>
static unsigned int failures, auto_calls, scroll_calls, mutate, expected_y;
static mysmb_u8 last_buttons;
static void check(int ok) { if(!ok) ++failures; }
void mysmb_player_auto_control(struct mysmb_game *game, mysmb_u8 buttons)
{
    ++auto_calls;last_buttons=buttons;
    if(mutate) game->ram[0x6deU]=1U;
}
void mysmb_player_update_scroll(struct mysmb_game *game)
{
    ++scroll_calls;check(game->ram[0xceU]==expected_y);
    if(mutate) {game->ram[0x6deU]=1U;game->ram[0x6d6U]=0U;game->ram[0x74eU]=3U;}
}
static void prepare(struct mysmb_game *game)
{
    memset(game,0,sizeof(*game));auto_calls=0U;scroll_calls=0U;mutate=0U;
    game->ram[0x752U]=0x5aU;game->ram[0x774U]=0xffU;
    game->ram[0x772U]=3U;game->ram[0x722U]=1U;
}
static void transition(struct mysmb_game *game,unsigned int timer,unsigned int mode)
{
    check(game->ram[0x6deU]==(mysmb_u8)(timer-1U));
    if(timer==1U) check(game->ram[0x752U]==mode && game->ram[0x774U]==0U &&
                       game->ram[0x772U]==0U && game->ram[0x722U]==0U);
    else check(game->ram[0x752U]==0x5aU && game->ram[0x774U]==0xffU &&
               game->ram[0x772U]==3U && game->ram[0x722U]==1U);
}
int main(void)
{
    static struct mysmb_game game;
    unsigned int y,amount,high,timer,x,area,warp;
    for(y=0U;y<256U;++y) for(amount=0U;amount<256U;++amount) {
        prepare(&game);game.ram[0xceU]=(mysmb_u8)y;game.ram[0xb5U]=0x9aU;
        mysmb_player_move_y_axis(&game,(mysmb_u8)amount);
        check(game.ram[0xceU]==(mysmb_u8)(y+amount) && game.ram[0xb5U]==0x9aU);
    }
    for(high=0U;high<256U;++high) for(y=0U;y<256U;++y) {
        prepare(&game);game.ram[0xb5U]=(mysmb_u8)high;game.ram[0xceU]=(mysmb_u8)y;
        mysmb_player_step_auto_climb(&game);
        if(high==0U && y<0xe4U) check(auto_calls==0U && game.ram[0x752U]==2U &&
            game.ram[0x774U]==0U && game.ram[0x772U]==0U && game.ram[0x722U]==0U);
        else check(auto_calls==1U && last_buttons==8U && game.ram[0x758U]==8U &&
                   game.ram[0x1dU]==3U && game.ram[0x772U]==3U);
    }
    for(timer=0U;timer<256U;++timer) for(area=0U;area<4U;++area)
    for(warp=0U;warp<2U;++warp) {
        prepare(&game);game.ram[0x6deU]=(mysmb_u8)timer;
        game.ram[0x74eU]=(mysmb_u8)area;game.ram[0x6d6U]=(mysmb_u8)warp;
        game.ram[0xceU]=0xffU;expected_y=0U;
        mysmb_player_step_vertical_pipe(&game);check(scroll_calls==1U && auto_calls==0U);
        transition(&game,timer,warp!=0U ? 0U:(area==3U ? 2U:1U));
    }
    for(timer=0U;timer<256U;++timer) for(x=0U;x<256U;++x) {
        prepare(&game);game.ram[0x6deU]=(mysmb_u8)timer;game.ram[0x86U]=(mysmb_u8)x;
        mysmb_player_step_side_pipe(&game);
        check(auto_calls==1U && last_buttons==((x&15U)!=0U ? 1U:0U));
        check(game.ram[0x57U]==((x&15U)!=0U ? 8U:0U));transition(&game,timer,2U);
    }
    prepare(&game);mutate=1U;game.ram[0x6deU]=0U;game.ram[0x6d6U]=1U;
    expected_y=1U;mysmb_player_step_vertical_pipe(&game);transition(&game,1U,2U);
    prepare(&game);mutate=1U;game.ram[0x6deU]=0U;
    mysmb_player_step_side_pipe(&game);transition(&game,1U,2U);
    if(failures) fprintf(stderr,"transition failures: %u\n",failures);
    return failures ? 1:0;
}
