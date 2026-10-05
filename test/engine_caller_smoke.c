#include "core/dispatcher.h"
#include "core/frame_root.h"
#include "core/area.h"
#include "game/objects.h"
#include "game/oam/oam.h"
#include "game/player.h"
#include <string.h>

static unsigned int sequence[20], count, bad, timer_result;
static void event(unsigned int value)
{
    if(count>=20U) { bad=1U; return; }
    sequence[count++]=value;
}
void mysmb_game_engine_actors(struct mysmb_game *game,
                               const struct mysmb_area_source *source)
{
    if(source->prg!=game->area_prg || source->prg_size!=game->area_prg_size)
        bad=1U;
    event(1U);
}
#define CHILD(name,number) \
void name(struct mysmb_game *game) { (void)game;event(number); }
CHILD(mysmb_oam_get_player_offscreen_bits,2U)
CHILD(mysmb_oam_relative_player_position,3U)
CHILD(mysmb_oam_render_player,4U)
CHILD(mysmb_area_apply_block_replacements,5U)
CHILD(mysmb_game_engine_blocks,6U)
CHILD(mysmb_objects_step_misc,7U)
CHILD(mysmb_game_process_cannons,8U)
CHILD(mysmb_game_process_whirlpools,9U)
CHILD(mysmb_objects_step_flagpole,10U)
#undef CHILD
mysmb_u8 mysmb_game_run_timer(struct mysmb_game *game)
{ (void)game;event(11U);return (mysmb_u8)timer_result; }
mysmb_u8 mysmb_area_queue_timer_status(struct mysmb_game *game)
{ (void)game;bad=1U;return 0U; }
void mysmb_area_step_palette_rotation(struct mysmb_game *game)
{ (void)game;event(13U); }
void mysmb_game_cycle_player_palette(struct mysmb_game *game)
{
    /* SaveAB must observe the value after all preceding children. */
    game->ram[0xaU]^=0xffU;
    event(14U);
}
void mysmb_game_step_area_parser(struct mysmb_game *game)
{
    if(game->ram[0xdU]!=game->ram[0xaU] || game->ram[0xcU]!=0U) bad=1U;
    event(15U);
}

/* GameRoutines shares this translation unit but is not a GameEngine
 * child. Fail if the engine invents any of these player/mode calls. */
#define UNEXPECTED(name) \
void name(struct mysmb_game *game) { (void)game;bad=1U; }
UNEXPECTED(mysmb_game_lose_life)
UNEXPECTED(mysmb_game_next_area)
UNEXPECTED(mysmb_player_initialize_entrance)
UNEXPECTED(mysmb_player_step_auto_climb)
UNEXPECTED(mysmb_player_finish_normal_entrance)
UNEXPECTED(mysmb_player_step_vertical_pipe)
UNEXPECTED(mysmb_player_step_side_pipe)
UNEXPECTED(mysmb_player_step_change_size)
UNEXPECTED(mysmb_player_step_fire_flower)
#undef UNEXPECTED
void mysmb_player_step(struct mysmb_game *game,mysmb_u8 buttons)
{ (void)game;(void)buttons;bad=1U; }
void mysmb_player_step_injury_blink(struct mysmb_game *game,mysmb_u8 buttons)
{ (void)game;(void)buttons;bad=1U; }

int main(void)
{
    static struct mysmb_game game;
    static const mysmb_u8 source[1]={0};
    unsigned int buttons,i,j;
    for(buttons=0U;buttons<256U;++buttons)
    for(timer_result=0U;timer_result<2U;++timer_result) {
        memset(game.ram,0,sizeof(game.ram));
        game.area_prg=source;game.area_prg_size=1U;
        game.ram[0xaU]=(mysmb_u8)buttons;
        game.ram[0xcU]=0xffU;game.ram[0xdU]=(mysmb_u8)buttons;
        count=0U;bad=0U;
        mysmb_game_engine(&game);
        if(bad || count!=14U) return 1;
        j=0U;
        for(i=1U;i<=15U;++i) {
            if(i==12U) continue;
            if(sequence[j++]!=i) return 2;
        }
        if(game.ram[0xdU]!=(mysmb_u8)(buttons^0xffU)) return 3;
    }
    return 0;
}
