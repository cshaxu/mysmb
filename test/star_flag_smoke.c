#include "core/enemy/actor_slots.h"
#include "core/objects.h"
#include <stdio.h>
#include <string.h>

static unsigned int calls, failures, mutation;
static mysmb_u8 ids[4], args[4];
static void note(mysmb_u8 id, mysmb_u8 arg)
{
    if (calls >= 4U) { ++failures; return; }
    ids[calls] = id;args[calls++] = arg;
}
void mysmb_oam_relative_enemy_position(struct mysmb_game *g, mysmb_u8 slot)
{
    note(1U,slot);
    /* Mutation catches using the caller's stale X/coordinates/OAM. */
    if (mutation) {
        g->ram[8U]=5U;g->ram[0x6eaU]=0xfcU;
        g->ram[0x3aeU]=0xfcU;g->ram[0x3b9U]=0xfeU;
        g->ram[0x79bU]=0U;g->ram[0x7b1U]=0U;
    } else {
        g->ram[0x3aeU]=g->ram[0x87U+slot];
        g->ram[0x3b9U]=g->ram[0xcfU+slot];
    }
}
void mysmb_status_apply_digit_modifier(struct mysmb_game *g, mysmb_u8 offset)
{
    note(2U,offset);
    if (offset==0x23U) {
        if (g->ram[0x139U]!=0xffU) ++failures;
    } else if (g->ram[0x139U]!=5U) ++failures;
    if (mutation) g->ram[0x753U]=(mysmb_u8)(offset==0x23U?1U:0x10U);
}
mysmb_u8 mysmb_score_update_number(struct mysmb_game *g, mysmb_u8 nybbles)
{ note(3U,nybbles);return g->ram[8U]; }

static struct mysmb_game g;
static void reset(mysmb_u8 task)
{
    memset(&g,0,sizeof(g));memset(ids,0,sizeof(ids));memset(args,0,sizeof(args));
    calls=0U;mutation=0U;g.ram[0x746U]=task;g.ram[0x6cbU]=0x55U;
    /* No flag/ID guard belongs at the original entry. */
}
#define CHECK(c) do { if (!(c)) { printf("line %d\n",__LINE__);++failures; } } while(0)
int main(void)
{
    unsigned int n, total;mysmb_u8 fire,state;
    total=0U;
    for(n=0U;n<256U;++n) {
        reset(1U);g.ram[0x7faU]=(mysmb_u8)n;
        mysmb_objects_step_star_flags_slot(&g,0U);
        fire=(mysmb_u8)(n==1U || n==3U || n==6U?n:255U);
        state=(mysmb_u8)(n==1U?5U:(n==3U?3U:0U));
        CHECK(g.ram[0x6d7U]==fire && g.ram[0x1eU]==state);
        CHECK(g.ram[0x746U]==2U && calls==0U && g.ram[0x6cbU]==0U);
        ++total;
    }
    for(n=0U;n<256U;++n) {
        if(n>0U && n<5U)continue;
        reset((mysmb_u8)n);g.ram[4U]=0xa5U;
        mysmb_objects_step_star_flags_slot(&g,0U);
        CHECK(g.ram[0x6cbU]==0U && calls==0U);
        CHECK(g.ram[4U]==(n==0U?0xe7U:0xa5U));++total;
    }
    for(n=0U;n<8U;++n) {
        reset(2U);g.ram[9U]=(mysmb_u8)n;g.ram[0xfeU]=0x80U;g.ram[0x7faU]=1U;
        g.ram[0x138U]=0x6aU;mutation=1U;
        mysmb_objects_step_star_flags_slot(&g,0U);
        CHECK(calls==3U && ids[0]==2U && args[0]==0x23U &&
              ids[1]==2U && args[1]==0x11U && ids[2]==3U && args[2]==4U);
        CHECK(g.ram[0x138U]==0x6aU && g.ram[0x139U]==5U);
        CHECK(g.ram[0xfeU]==((n&4U)?0x10U:0x80U));++total;
    }
    reset(2U);mysmb_objects_step_star_flags_slot(&g,0U);
    CHECK(calls==0U && g.ram[0x746U]==3U);++total;
    for(n=0U;n<256U;++n) {
        reset(3U);g.ram[0xcfU]=0x71U;g.ram[0x6d7U]=(mysmb_u8)n;
        g.ram[0x796U]=0x55U;mutation=1U;
        mysmb_objects_step_star_flags_slot(&g,0U);
        CHECK(calls==1U && ids[0]==1U && args[0]==0U);
        CHECK(g.ram[0x2fcU]==6U && g.ram[0x2fdU]==0x57U &&
              g.ram[0x2ffU]==4U && g.ram[0x201U]==0x56U &&
              g.ram[0x205U]==0x55U && g.ram[0x209U]==0x54U);
        CHECK(g.ram[0x796U]==0x55U);
        if(n==0U || n>=128U) {
            CHECK(g.ram[0x746U]==4U && g.ram[0x79bU]==6U && g.ram[0x6cbU]==0U);
        } else CHECK(g.ram[0x746U]==3U && g.ram[0x6cbU]==0x16U);
        ++total;
    }
    reset(3U);g.ram[0xcfU]=0x72U;
    mysmb_objects_step_star_flags_slot(&g,0U);
    CHECK(g.ram[0xcfU]==0x71U && g.ram[0x746U]==3U && calls==1U);++total;
    for(n=0U;n<4U;++n) {
        reset(4U);g.ram[0x796U]=(mysmb_u8)(n&1U);g.ram[0x7b1U]=(mysmb_u8)(n&2U);
        g.ram[0xfcU]=(mysmb_u8)(n?0U:1U);
        mysmb_objects_step_star_flags_slot(&g,0U);
        CHECK(calls==1U && g.ram[0x746U]==(n?4U:5U));++total;
    }
    reset(4U);g.ram[0x796U]=7U;g.ram[0x7b1U]=8U;mutation=1U;
    mysmb_objects_step_star_flags_slot(&g,0U);
    CHECK(calls==1U && g.ram[0x746U]==5U);++total;
    printf("star flag native cases=%u failures=%u\n",total,failures);
    return failures?1:0;
}
