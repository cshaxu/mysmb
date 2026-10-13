#include "core/player.h"
#include "core/oam/oam.h"
#include "core/world/world.h"
#include <stdio.h>
#include <string.h>

static unsigned int stage, failures, mutate, transition;
static void check(int ok) { if (!ok) ++failures; }
void mysmb_player_movement_subs(struct mysmb_game *game)
{
    check(stage++ == 0U);
    if (mutate) {
        game->ram[0x754U] = 0U;
        game->ram[0x714U] = 4U;
        game->ram[0x57U] = 0xffU;
    }
}
void mysmb_player_update_scroll(struct mysmb_game *game)
{
    check(stage++ == 1U);
    if (mutate) check(game->ram[0x499U] == 2U && game->ram[0x45U] == 2U);
}
void mysmb_oam_get_player_offscreen_bits(struct mysmb_game *game)
{ (void)game; check(stage++ == 2U); }
void mysmb_oam_relative_player_position(struct mysmb_game *game)
{
    check(stage++ == 3U);
    game->ram[0x3adU] = 0x21U; game->ram[0x3b8U] = 0x43U;
}
void mysmb_world_set_bounding_box(struct mysmb_game *game, mysmb_u16 address,
                                 mysmb_u8 control, mysmb_u8 x, mysmb_u8 y)
{
    check(stage++ == 4U);
    check(address == 0x4acU && control == game->ram[0x499U]);
    check(x == 0x21U && y == 0x43U);
}
void mysmb_player_background_collision(struct mysmb_game *game)
{
    check(stage++ == 5U);
    if (mutate) {game->ram[0xceU] = 0x40U; game->ram[0xeU] = 8U;}
}
void mysmb_player_set_entrance(struct mysmb_game *game)
{
    check(stage == 6U && game->ram[0x758U] == 0U);
    ++transition;
    game->ram[0x752U] = 0xfeU;
}
static void prepare(struct mysmb_game *game)
{
    memset(game,0,sizeof(*game));stage=0U;mutate=0U;transition=0U;
    game->ram[0x74eU]=1U;game->ram[0xb5U]=1U;game->ram[0xeU]=8U;
    game->ram[0x754U]=1U;game->ram[0x45U]=0x5aU;
}
int main(void)
{
    static struct mysmb_game game;
    unsigned int input,high,y,state,mode,flag,music;
    unsigned int threshold,death,entered,should_transition;
    unsigned int lr,ud;
    for(input=0U;input<256U;++input) for(state=0U;state<4U;++state) {
        prepare(&game);game.ram[0x1dU]=(mysmb_u8)state;
        mysmb_player_step(&game,(mysmb_u8)input);
        lr=input&3U;ud=input&12U;
        if ((ud&4U)!=0U && state==0U && lr!=0U) {lr=0U;ud=0U;}
        check(stage==6U && game.ram[0xaU]==(input&0xc0U));
        check(game.ram[0xcU]==lr && game.ram[0xbU]==ud);
        check(game.ram[0x6fcU]==input && game.ram[0x45U]==0x5aU);
    }
    for(high=0U;high<256U;++high) for(y=0U;y<256U;++y) {
        prepare(&game);game.ram[0x74eU]=0U;
        game.ram[0xb5U]=(mysmb_u8)high;game.ram[0xceU]=(mysmb_u8)y;
        mysmb_player_latch_input(&game,0xffU);
        check(game.ram[0x6fcU]==(high==1U && y<0xd0U ? 0xffU:0U));
    }
    for(mode=0U;mode<13U;++mode) for(y=0U;y<256U;++y) {
        prepare(&game);game.ram[0xeU]=(mysmb_u8)mode;
        game.ram[0xceU]=(mysmb_u8)y;game.ram[0x3c4U]=0xffU;
        game.ram[0xaU]=0x55U;game.ram[0xbU]=0x66U;
        game.ram[0xcU]=0x77U;game.ram[0x6fcU]=0x88U;
        mysmb_player_step(&game,0U);
        check(game.ram[0x3c4U]==(y>=0x40U && mode>=4U && mode!=5U && mode!=7U ? 0xdfU:0xffU));
        if(mode==11U) check(game.ram[0xaU]==0x55U && game.ram[0xbU]==0x66U &&
                           game.ram[0xcU]==0x77U && game.ram[0x6fcU]==0x88U);
    }
    for(high=0U;high<256U;++high) for(flag=0U;flag<8U;++flag)
    for(mode=0U;mode<2U;++mode) for(music=0U;music<2U;++music) {
        prepare(&game);game.ram[0xb5U]=(mysmb_u8)high;
        game.ram[0x743U]=(mysmb_u8)(flag&1U);
        game.ram[0x759U]=(mysmb_u8)(flag&2U);
        game.ram[0x712U]=(mysmb_u8)(flag&4U);
        game.ram[0x7b1U]=(mysmb_u8)music;
        game.ram[0xeU]=mode ? 11U:8U;game.ram[0x758U]=0xa5U;
        game.ram[7U]=0xa5U;
        entered=((high+254U)&255U)<128U;
        death=(flag&2U)!=0U || (flag&1U)==0U;
        threshold=death && !mode ? 6U:4U;
        should_transition=entered && ((high+256U-threshold)&255U)<128U;
        mysmb_player_step(&game,0U);
        check(stage==6U && game.ram[0x723U]==entered);
        check(game.ram[7U]==(entered ? threshold:0xa5U));
        check(transition==(should_transition && !death));
        if(transition) check(game.ram[0x752U]==0xffU);
        check(game.ram[0xfcU]==(entered && death && !mode && !(flag&4U) ? 1U:0U));
        check(game.ram[0xeU]==(should_transition && death && !music ? 6U:(mode ? 11U:8U)));
    }
    prepare(&game);mutate=1U;game.ram[0x3c4U]=0xffU;
    mysmb_player_step(&game,0U);
    check(stage==6U && game.ram[0x499U]==2U && game.ram[0x3c4U]==0xdfU);
    if(failures) fprintf(stderr,"player-control failures: %u\n",failures);
    return failures ? 1:0;
}
