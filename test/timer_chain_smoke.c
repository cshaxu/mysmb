#include "core/frame_root.h"
#include "core/status.h"
#include "game/objects.h"
#include <stdio.h>
#include <string.h>
static unsigned int calls,errors,mutate;
void mysmb_status_apply_digit_modifier(struct mysmb_game *g,mysmb_u8 offset)
{
    if(calls!=0U || offset!=0x23U || g->ram[0x139U]!=0xffU || g->ram[0x787U]!=0x18U) ++errors;
    calls=1U;g->ram[0x139U]=0U;
}
mysmb_u8 mysmb_status_queue_timer(struct mysmb_game *g)
{
    if(calls!=1U || g->ram[0x139U]!=0U) ++errors;
    calls=2U;return 0U;
}
void mysmb_objects_force_injury_entry(struct mysmb_game *g, mysmb_u8 a)
{
    if(a!=0U || calls!=0U || g->ram[0x756U]!=0U) ++errors;
    calls=3U;
    if(mutate!=0U) g->ram[0x759U]=0xffU;
}
int main(void)
{
    static struct mysmb_game game;
    static const mysmb_u8 digits[5][3]={{0,0,0},{1,0,0},{1,0,1},{0,0,1},{2,0,0}};
    unsigned int mode,engine,high,control,d,gate,cases;
    mysmb_u8 result;
    cases=0U;
    for(mode=0U;mode<3U;++mode)
    for(engine=0U;engine<13U;++engine)
    for(high=0U;high<4U;++high)
    for(control=0U;control<2U;++control)
    for(d=0U;d<5U;++d) {
        memset(&game,0,sizeof(game));calls=0U;
        game.ram[0x770U]=(mysmb_u8)mode;game.ram[0xeU]=(mysmb_u8)engine;
        game.ram[0xb5U]=(mysmb_u8)high;game.ram[0x787U]=(mysmb_u8)control;
        game.ram[0x756U]=2U;game.ram[0xfcU]=0x55U;game.ram[0x139U]=0x33U;
        memcpy(game.ram+0x7f8U,digits[d],3U);
        result=mysmb_game_run_timer(&game);++cases;
        gate=mode!=0U && engine>=8U && engine!=11U && high<2U && control==0U;
        if(!gate) {
            if(calls!=0U || result!=0U || game.ram[0x139U]!=0x33U || game.ram[0xfcU]!=0x55U || game.ram[0x756U]!=2U) ++errors;
        } else if(d==0U) {
            if(calls!=3U || result!=0U || game.ram[0x759U]!=1U || game.ram[0x139U]!=0x33U) ++errors;
        } else {
            if(calls!=2U || result!=1U || game.ram[0xfcU]!=(d==1U?0x40U:0x55U)) ++errors;
        }
    }
    memset(&game,0,sizeof(game));calls=0U;mutate=1U;
    game.ram[0x770U]=1U;game.ram[0xeU]=8U;game.ram[0xb5U]=1U;
    game.ram[0x756U]=2U;game.ram[0x79eU]=0xffU;
    (void)mysmb_game_run_timer(&game);
    if(calls!=3U || game.ram[0x759U]!=0U) ++errors;
    printf("timer gate cases=%u; post-child expiry wrap; errors=%u\n",cases,errors);
    return errors!=0U;
}
