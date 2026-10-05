#include "game/objects.h"
#include "core/area.h"
#include <stdio.h>
#include <string.h>
static struct mysmb_game game;
static unsigned int failures,phase,palette,routine,change;
static mysmb_u8 root_slot;
void mysmb_objects_erase_enemy(struct mysmb_game *g,mysmb_u8 s)
{ if(phase++!=0U||s!=root_slot)++failures;if(change==1U)g->ram[0x39U]=2U; }
void mysmb_objects_setup_floatey_from_relative(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 a)
{
    if(phase++!=1U||s!=root_slot||a!=6U)++failures;
    g->ram[0x110U+s]=a;if(change==2U)g->ram[0x756U]=1U;
}
mysmb_u8 mysmb_area_queue_player_palette(struct mysmb_game *g)
{ if(phase++!=2U||g->ram[0x756U]!=2U)++failures;++palette;return 1U; }
void mysmb_objects_set_player_routine(struct mysmb_game *g,mysmb_u8 a,mysmb_u8 y)
{ (void)g;if(y!=0U||phase!=(a==12U?3U:2U))++failures;routine=a; }
int main(void)
{
    unsigned int s,t,p,cases;
    cases=0U;
    for(s=0U;s<6U;++s)for(t=0U;t<256U;++t)for(p=0U;p<256U;++p){
        memset(&game,0,sizeof(game));root_slot=(mysmb_u8)s;phase=palette=routine=change=0U;
        game.ram[0x39U]=(mysmb_u8)t;game.ram[0x756U]=(mysmb_u8)p;
        mysmb_objects_collect_power_up(&game,root_slot);
        if(game.ram[0xfeU]!=0x20U||game.ram[0x110U+s]!=(t==3U?11U:6U))++failures;
        if(t>=2U&&t!=3U){if(game.ram[0x79fU]!=0x23U||game.ram[0xfbU]!=0x40U)++failures;}
        if(routine!=(t<2U?(p==0U?9U:(p==1U?12U:0U)):0U))++failures;
        if(palette!=(t<2U&&p==1U?1U:0U))++failures;
        ++cases;
    }
    for(change=1U;change<=2U;++change){
        memset(&game,0,sizeof(game));root_slot=5U;phase=palette=routine=0U;
        mysmb_objects_collect_power_up(&game,root_slot);
        if(change==1U&&game.ram[0xfbU]!=0x40U)++failures;
        if(change==2U&&routine!=12U)++failures;
    }
    printf("%u type/status/slot cases and child-mutated type/status; failures=%u\n",cases,failures);
    return failures?1:0;
}
