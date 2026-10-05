#include "core/enemy/loop.h"
#include "core/enemy/stream.h"
#include "core/enemy/init.h"
#include "core/objects.h"
#include <string.h>

/* Native caller contract only. Child bodies receive no equivalence credit. */
static unsigned int erased, bad, parser, initializer;
static mysmb_u8 wanted_slot;
void mysmb_objects_erase_enemy(struct mysmb_game *game, mysmb_u8 slot)
{
    if (erased >= 5U || slot != 4U-erased || game->ram[0x745U] != 1U ||
        game->ram[0x6cbU] != 0x5aU) ++bad;
    ++erased;
}
mysmb_u8 mysmb_enemy_stream_process_current(struct mysmb_game *game,
    const struct mysmb_area_source *source, mysmb_u8 slot)
{
    (void)game; (void)source;
    if (slot != wanted_slot) ++bad;
    ++parser;
    return 0U;
}
void mysmb_enemy_checkpoint_loaded(struct mysmb_game *game, mysmb_u8 slot)
{
    if (slot != wanted_slot || game->ram[0x6cdU] != 0U ||
        game->ram[0x1eU+slot] != 0U || game->ram[0xfU+slot] != 1U ||
        game->ram[0x16U+slot] != 0x12U) ++bad;
    ++initializer;
}

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 expected[2048];
    static const mysmb_u8 world[11]={3,3,6,6,6,6,6,6,7,7,7};
    static const mysmb_u8 page[11]={5,9,4,5,6,8,9,10,6,11,16};
    static const mysmb_u8 height[11]={0x40,0xb0,0xb0,0x80,0x40,0x40,
        0x80,0x40,0xf0,0xf0,0xf0};
    static const mysmb_u8 offset[11]={0x12,0x36,0x0e,0x0e,0x0e,0x32,
        0x32,0x32,0x0a,0x26,0x40};
    static const unsigned int rewind[5]={0x6d,0x725,0x71a,0x71b,0x72a};
    unsigned int row, correct, passes, successes, queue, gate, i;
    unsigned int next_pass, next_correct, back, reset, initial_correct;
    for(row=0U;row<11U;++row) for(correct=0U;correct<3U;++correct)
    for(passes=0U;passes<256U;++passes) for(successes=0U;successes<5U;++successes)
    for(queue=0U;queue<2U;++queue) for(gate=0U;gate<4U;++gate) {
        memset(game.ram,0x5a,sizeof(game.ram));
        wanted_slot=(mysmb_u8)(row%6U); game.ram[8U]=wanted_slot;
        game.ram[0x745U]=(mysmb_u8)(gate==1U?0U:1U);
        game.ram[0x726U]=(mysmb_u8)(gate==2U?1U:0U);
        game.ram[0x75fU]=(mysmb_u8)(gate==3U?0U:world[row]);
        game.ram[0x725U]=page[row];
        game.ram[0xceU]=(mysmb_u8)(height[row]+(correct==0U?1U:0U));
        game.ram[0x1dU]=(mysmb_u8)(correct==2U?1U:0U);
        game.ram[0x6daU]=(mysmb_u8)passes;
        initial_correct=successes==4U?255U:successes;
        game.ram[0x6d9U]=(mysmb_u8)initial_correct;
        game.ram[0x6cdU]=(mysmb_u8)(queue?0x12U:0U);
        game.ram[0x6dU]=(mysmb_u8)passes;
        memcpy(expected,game.ram,sizeof(expected));
        back=0U;reset=0U;
        if(gate==0U) {
            if(world[row]==6U) {
                next_pass=(passes+1U)&255U;
                next_correct=(initial_correct+(correct==1U?1U:0U))&255U;
                expected[0x6daU]=(mysmb_u8)next_pass;
                expected[0x6d9U]=(mysmb_u8)next_correct;
                reset=next_pass==3U;
                back=reset && next_correct!=3U;
            } else { reset=1U;back=correct!=1U; }
            if(back) {
                for(i=0U;i<5U;++i) expected[rewind[i]]=(mysmb_u8)(expected[rewind[i]]-4U);
                expected[0x73bU]=0U;expected[0x72bU]=0U;
                expected[0x739U]=0U;expected[0x73aU]=0U;
                expected[0x72cU]=offset[row];expected[0x6cbU]=0U;
            }
            if(reset) { expected[0x6daU]=0U;expected[0x6d9U]=0U; }
            expected[0x745U]=0U;
        }
        if(queue) {
            expected[0x16U+wanted_slot]=0x12U;
            expected[0xfU+wanted_slot]=1U;
            expected[0x1eU+wanted_slot]=0U;expected[0x6cdU]=0U;
        }
        erased=0U;bad=0U;parser=0U;initializer=0U;
        mysmb_enemy_process_loop_command(&game,0,wanted_slot);
        if(bad || erased!=(back?5U:0U) || parser!=(queue?0U:1U) ||
            initializer!=queue || memcmp(expected,game.ram,sizeof(expected))) return 1;
    }
    return 0;
}
