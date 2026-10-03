#include "game/dispatcher.h"
#include "game/frame_root.h"
#include "game/player.h"
#include <string.h>

static unsigned int events[4],count,bad,mutate;
static mysmb_u8 seen_buttons;

/* Record the dispatch seam before its leaf; generic scratch has ROM proof. */
void mysmb_game_jump_engine_state(struct mysmb_game *game,
                                 mysmb_u16 ret, mysmb_u8 selector)
{
    if (ret != 0xb04eU || selector != game->ram[0x000eU] || count != 0U)
        ++bad;
}
static void record(unsigned int event)
{
    if(count<4U) events[count]=event;
    else ++bad;
    ++count;
}
#define CHILD(name,event) \
void name(struct mysmb_game *game) {(void)game;record(event);}
CHILD(mysmb_player_initialize_entrance,0U)
CHILD(mysmb_player_step_auto_climb,1U)
CHILD(mysmb_player_step_side_pipe,2U)
CHILD(mysmb_player_step_vertical_pipe,3U)
CHILD(mysmb_player_step_flagpole_slide,4U)
CHILD(mysmb_player_step_end_level,5U)
CHILD(mysmb_game_lose_life,6U)
CHILD(mysmb_player_step_change_size,9U)
CHILD(mysmb_player_step_death,11U)
CHILD(mysmb_player_step_fire_flower,12U)
#undef CHILD
void mysmb_player_step_injury_blink(struct mysmb_game *game,mysmb_u8 buttons)
{if(buttons!=game->ram[0x6fcU]) ++bad;record(10U);}
void mysmb_player_step(struct mysmb_game *game,mysmb_u8 buttons)
{
    if(game->ram[0x6fcU]!=buttons) ++bad;
    seen_buttons=buttons;record(8U);
    if(mutate==1U) game->ram[0x86U]=0x48U;
    if(mutate==2U) game->ram[0x86U]=0x47U;
}
void mysmb_player_enter_side_pipe(struct mysmb_game *game)
{record(16U);if(mutate==3U) game->ram[0x6deU]=1U;}
void mysmb_player_move_y_axis(struct mysmb_game *game,mysmb_u8 amount)
{
    if(amount!=0xffU) ++bad;
    record(17U);game->ram[0xceU]=(mysmb_u8)(game->ram[0xceU]+amount);
}
void mysmb_game_next_area(struct mysmb_game *game)
{
    if(game->ram[0x6deU]!=0U || game->ram[0x769U]!=0U) ++bad;
    record(18U);
}

static void seed(struct mysmb_game *game)
{
    memset(game,0,sizeof(*game));
    game->ram[0xeU]=7U;game->ram[0xceU]=0x30U;
    game->ram[0x6fcU]=0xa5U;game->ram[0x769U]=0xffU;
    game->ram[0x716U]=0x77U;game->ram[0x33U]=2U;
    count=0U;bad=0U;mutate=0U;seen_buttons=0xffU;
}
static unsigned int ready(const struct mysmb_game *game)
{
    return game->ram[0xeU]==8U && game->ram[0x33U]==1U &&
        game->ram[0x752U]==0U && game->ram[0x716U]==0U && game->ram[0x758U]==0U;
}

int main(void)
{
    static struct mysmb_game game;
    unsigned int id,y,timer,override,height,x,button;
    for(id=0U;id<13U;++id) {
        seed(&game);game.ram[0xeU]=(mysmb_u8)id;
        mysmb_game_routines(&game);
        if(id==7U) {if(count!=0U || !ready(&game)) return 1;}
        else if(count!=1U || events[0]!=id || bad!=0U) return 2;
    }
    /* AutoControlPlayer stores every possible controller byte before child. */
    for(button=0U;button<256U;++button) {
        seed(&game);mysmb_player_auto_control(&game,(mysmb_u8)button);
        if(count!=1U || events[0]!=8U || seen_buttons!=button || bad) return 3;
    }
    /* All alternate bytes except exactly two use the ordinary branch;
     * alternate three must not be a synthetic early return. */
    for(id=0U;id<256U;++id) if(id!=2U) for(y=0U;y<256U;++y) {
        seed(&game);game.ram[0x752U]=(mysmb_u8)id;game.ram[0xceU]=(mysmb_u8)y;
        mysmb_player_finish_normal_entrance(&game);
        if(y<0x30U) {
            if(count!=1U || events[0]!=8U || seen_buttons!=0U || game.ram[0xeU]!=7U) return 4;
        } else if(count!=0U || !ready(&game)) return 5;
        if(bad) return 6;
    }
    for(id=6U;id<8U;++id) for(timer=0U;timer<256U;++timer) {
        seed(&game);game.ram[0x710U]=(mysmb_u8)id;
        mysmb_player_finish_normal_entrance(&game);
        if(count!=1U || events[0]!=8U || seen_buttons!=1U || game.ram[0xeU]!=7U) return 7;
        seed(&game);game.ram[0x710U]=(mysmb_u8)id;game.ram[0x3c4U]=0x20U;
        game.ram[0x6deU]=(mysmb_u8)timer;
        mysmb_player_finish_normal_entrance(&game);
        if(game.ram[0x6deU]!=(mysmb_u8)(timer-1U) || events[0]!=16U || bad) return 8;
        if(timer==1U) {if(count!=2U || events[1]!=18U) return 9;}
        else if(count!=1U || game.ram[0x769U]!=0xffU) return 10;
    }
    seed(&game);game.ram[0x710U]=6U;game.ram[0x3c4U]=1U;mutate=3U;
    mysmb_player_finish_normal_entrance(&game);
    if(count!=2U || events[1]!=18U || bad) return 11;
    for(y=0U;y<256U;++y) {
        seed(&game);game.ram[0x752U]=2U;game.ram[0xceU]=(mysmb_u8)y;
        mysmb_player_finish_normal_entrance(&game);
        if(count!=1U || events[0]!=17U || bad) return 12;
        if(((mysmb_u8)(y-1U)<0x91U)!=ready(&game)) return 13;
    }
    for(override=1U;override<256U;++override) for(height=0U;height<3U;++height)
    for(y=0x98U;y<=0x99U;++y) for(x=0U;x<3U;++x) {
        seed(&game);game.ram[0x752U]=2U;game.ram[0x758U]=(mysmb_u8)override;
        game.ram[0x399U]=(mysmb_u8)(0x5fU+height);game.ram[0xceU]=(mysmb_u8)y;
        game.ram[0x86U]=x==1U ? 0x47U:0x48U;mutate=x;
        mysmb_player_finish_normal_entrance(&game);
        if(height!=1U) {if(count!=0U || game.ram[0xeU]!=7U) return 14;}
        else {
            if(count!=1U || events[0]!=8U || bad) return 15;
            if(seen_buttons!=(y==0x99U ? 8U:1U)) return 16;
            if((x!=2U)!=ready(&game)) return 17;
            if(y==0x99U && (game.ram[0x1dU]!=3U || game.ram[0x5b4U]!=8U)) return 18;
        }
    }
    return 0;
}
