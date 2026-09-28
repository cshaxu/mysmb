#include "game/score.h"
#include "game/status.h"
#include "game/objects.h"
#include <string.h>
#include <stdio.h>

static unsigned int failures, calls, tests;
static mysmb_u8 arguments[3], ids[3], flip_player, final_offset, digit;
static void check(int ok) { if (!ok) ++failures; }
void mysmb_status_apply_digit_modifier(struct mysmb_game *g, mysmb_u8 offset)
{
    ids[calls]=1U; arguments[calls++]=offset;
    if (calls==1U) check(g->ram[0x139U]==1U);
    else check(g->ram[0x138U]==2U);
    if (flip_player) g->ram[0x753U]^=1U;
}
mysmb_u8 mysmb_status_print_numbers(struct mysmb_game *g,mysmb_u8 nybbles)
{
    ids[calls]=2U;arguments[calls++]=nybbles;
    g->ram[0x300U]=final_offset;
    g->ram[0x2fbU+final_offset]=digit;
    g->ram[8U]=0xa5U;
    return 1U;
}
int main(void)
{
    static struct mysmb_game g;
    unsigned int p,c,l,f,o,d;
    mysmb_u8 result;
    for(p=0U;p<2U;++p) for(c=0U;c<256U;++c)
    for(l=0U;l<2U;++l) for(f=0U;f<2U;++f) {
        memset(&g,0,sizeof(g));calls=0U;flip_player=(mysmb_u8)f;
        final_offset=14U;digit=0U;
        g.ram[0x753U]=(mysmb_u8)p;g.ram[0x75eU]=(mysmb_u8)c;
        g.ram[0x75aU]=l?255U:0U;g.ram[0xfeU]=1U;
        mysmb_objects_give_one_coin(&g);
        check(calls==3U && ids[0]==1U && ids[1]==1U && ids[2]==2U);
        check(arguments[0]==(p?0x1dU:0x17U));
        check(arguments[1]==((p^f)?0x11U:0x0bU));
        check(arguments[2]==(p?0x13U:0x02U));
        check(g.ram[0x75eU]==(c==99U?0U:(mysmb_u8)(c+1U)));
        check(g.ram[0x75aU]==(mysmb_u8)((l?255U:0U)+(c==99U?1U:0U)));
        check(g.ram[0xfeU]==(c==99U?0x40U:1U));
        check(g.ram[0x309U]==0x24U);++tests;
    }
    for(o=0U;o<256U;++o) for(d=0U;d<2U;++d) {
        memset(&g,0,sizeof(g));calls=0U;final_offset=(mysmb_u8)o;
        digit=o==5U?5U:(d?9U:0U);
        result=mysmb_score_update_number(&g,0xfaU);
        check(calls==1U && ids[0]==2U && arguments[0]==0xfaU);
        check(g.ram[0x2fbU+o]==(digit?digit:0x24U));
        check(result==0xa5U);++tests;
    }
    printf("%u score chain cases; %u failures\n",tests,failures);
    return failures?1:0;
}

