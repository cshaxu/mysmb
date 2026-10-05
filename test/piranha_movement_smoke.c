#include "core/objects.h"
#include "core/enemy/actor_slots.h"
#include "core/enemy/distance.h"
#include <stdio.h>
#include <string.h>

static struct mysmb_game g;
static unsigned int calls,failures;
static mysmb_u8 low_result,page_result;
mysmb_u8 mysmb_enemy_player_difference(struct mysmb_game *game,mysmb_u8 slot)
{
    if(slot!=2U)++failures;
    ++calls;game->ram[0U]=low_result;
    /* Source child preserves X; changing ObjectOffset must not change X. */
    game->ram[8U]=5U;
    return page_result;
}
#define CHECK(c) do { if(!(c)) { printf("line %d\n",__LINE__);++failures; } } while(0)
static void reset(void)
{
    memset(&g,0,sizeof(g));calls=0U;low_result=0x21U;page_result=0U;
    g.ram[8U]=2U;g.ram[0x5aU]=1U;g.ram[0xd1U]=0x80U;
    g.ram[0x419U]=0x7fU;g.ram[0x436U]=0x81U;g.ram[0x3c7U]=0xc3U;
    g.ram[0U]=0x66U;g.ram[9U]=1U;
}
int main(void)
{
    unsigned int n,total;mysmb_u8 expected;
    total=0U;
    for(n=1U;n<256U;++n) {
        reset();g.ram[0x20U]=(mysmb_u8)n;mysmb_objects_step_piranha_plants_slot(&g,2U);
        CHECK(calls==0U && g.ram[0U]==0x66U && g.ram[0xd1U]==0x80U && g.ram[0x3c7U]==0x20U);++total;
        reset();g.ram[0x78cU]=(mysmb_u8)n;mysmb_objects_step_piranha_plants_slot(&g,2U);
        CHECK(calls==0U && g.ram[0U]==0x66U && g.ram[0xd1U]==0x80U && g.ram[0x3c7U]==0x20U);++total;
    }
    for(n=0U;n<256U;++n) {
        reset();low_result=(mysmb_u8)n;mysmb_objects_step_piranha_plants_slot(&g,2U);
        CHECK(calls==1U && g.ram[0x3c7U]==0x20U);
        if(n<33U)CHECK(g.ram[0xd1U]==0x80U && g.ram[0x5aU]==1U && g.ram[0U]==n);
        else CHECK(g.ram[0xd1U]==0x7fU && g.ram[0x5aU]==0xffU && g.ram[0x78cU]==0x40U);
        CHECK(g.ram[0x3caU]==0U);++total;
        reset();low_result=(mysmb_u8)n;page_result=0xffU;
        mysmb_objects_step_piranha_plants_slot(&g,2U);expected=(mysmb_u8)(0U-n);
        CHECK(calls==1U && g.ram[0x3c7U]==0x20U);
        CHECK(g.ram[0xd1U]==(expected<33U?0x80U:0x7fU));++total;
    }
    reset();g.ram[0x5aU]=0xffU;mysmb_objects_step_piranha_plants_slot(&g,2U);
    CHECK(calls==0U && g.ram[0x5aU]==1U && g.ram[0xd1U]==0x81U && g.ram[0x78cU]==0x40U);++total;
    for(n=0U;n<256U;++n) {
        reset();g.ram[0xa2U]=0xffU;g.ram[0x5aU]=(mysmb_u8)n;g.ram[0xd1U]=0xffU;
        g.ram[0x419U]=g.ram[0x436U]=(mysmb_u8)(n-1U);
        mysmb_objects_step_piranha_plants_slot(&g,2U);
        CHECK(calls==0U && g.ram[0xd1U]==(mysmb_u8)(n-1U) && g.ram[0xa2U]==0U && g.ram[0x78cU]==0x40U);++total;
    }
    reset();g.ram[9U]=0U;mysmb_objects_step_piranha_plants_slot(&g,2U);
    CHECK(g.ram[0U]==0x7fU && g.ram[0x5aU]==0xffU && g.ram[0xa2U]==1U && g.ram[0xd1U]==0x80U && g.ram[0x3c7U]==0x20U);++total;
    reset();g.ram[0x747U]=0xffU;mysmb_objects_step_piranha_plants_slot(&g,2U);
    CHECK(g.ram[0U]==0x7fU && g.ram[0x5aU]==0xffU && g.ram[0xa2U]==1U && g.ram[0xd1U]==0x80U);++total;
    reset();g.ram[0x419U]=0x7eU;mysmb_objects_step_piranha_plants_slot(&g,2U);
    CHECK(g.ram[0xd1U]==0x7fU && g.ram[0xa2U]==1U && g.ram[0x78cU]==0U);++total;
    printf("Piranha native cases=%u failures=%u\n",total,failures);return failures?1:0;
}
