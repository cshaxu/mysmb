#include "core/enemy/actor_slots.h"
#include "core/oam/oam.h"
#include <string.h>
static unsigned int calls,bad;
static mysmb_u8 root_slot;
void mysmb_oam_relative_enemy_position(struct mysmb_game *g,mysmb_u8 slot)
{
    if (calls++ != 0U || slot != root_slot) ++bad;
    g->ram[0U]=slot;g->ram[0x3aeU]=0xf9U;g->ram[0x3b9U]=0x71U;
    /* Prove that the caller reloads the source child's X/ObjectOffset and
     * reads both explosion arguments after the relative-position child. */
    g->ram[8U]=2U;g->ram[0x5aU]=2U;g->ram[0x6e7U]=0x90U;
}
void mysmb_oam_draw_fireworks_explosion(struct mysmb_game *g,mysmb_u8 frame,mysmb_u8 oam)
{
    if(calls++ != 1U || frame != 2U || oam != 0x90U ||
       g->ram[0x3afU]!=0xf9U || g->ram[0x3baU]!=0x71U) ++bad;
    g->ram[1U]=0x65U;
}
void mysmb_objects_end_area_points(struct mysmb_game *g)
{
    if(calls++ != 0U || g->ram[0xfU+root_slot]!=0U ||
       g->ram[0xfeU]!=8U || g->ram[0x138U]!=5U) ++bad;
    g->ram[0U]=0x91U;
}
int main(void)
{
    static struct mysmb_game g;
    static mysmb_u8 expected[2048];
    static const mysmb_u8 timers[4]={0U,1U,2U,255U};
    static const mysmb_u8 after[4]={255U,8U,1U,254U};
    static const mysmb_u8 frames[4]={0U,1U,2U,255U};
    static const mysmb_u8 advanced[4]={1U,2U,3U,0U};
    unsigned int s,t,f,ending;
    for(s=0U;s<2U;++s)for(t=0U;t<4U;++t)for(f=0U;f<4U;++f){
        memset(&g,0,sizeof(g));calls=bad=0U;root_slot=(mysmb_u8)(s*5U);
        g.ram[8U]=root_slot;g.ram[0xa0U+root_slot]=timers[t];
        g.ram[0xfU+root_slot]=(mysmb_u8)s;
        g.ram[0x58U+root_slot]=frames[f];g.ram[0xfeU]=0x80U;g.ram[0x138U]=0x42U;
        g.ram[0x747U]=1U; /* RunFireworks has no master-timer gate. */
        memcpy(expected,g.ram,sizeof(expected));
        expected[0xa0U+root_slot]=after[t];
        if(t==1U)expected[0x58U+root_slot]=advanced[f];
        ending=t==1U && f==2U;
        if(ending){expected[0xfU+root_slot]=0U;expected[0xfeU]=8U;expected[0x138U]=5U;expected[0U]=0x91U;}
        else {expected[0U]=root_slot;expected[1U]=0x65U;expected[8U]=2U;
              expected[0x3aeU]=expected[0x3afU]=0xf9U;expected[0x3b9U]=expected[0x3baU]=0x71U;
              expected[0x5aU]=2U;expected[0x6e7U]=0x90U;}
        mysmb_objects_step_fireworks_slot(&g,root_slot);
        if(bad || calls!=(ending?1U:2U) || memcmp(g.ram,expected,sizeof(expected)))return 1;
    }
    return 0;
}
