#include "game/objects.h"
#include "game/oam/oam.h"
#include "game/world/world.h"
#include <stdio.h>
#include <string.h>

static unsigned int errors,count,ids[64],slots[64];
static mysmb_u8 returned_speed;
static void record(struct mysmb_game *g,unsigned int id,mysmb_u8 slot)
{
    if(count>=64U) {++errors;return;}
    ids[count]=id;slots[count++]=slot;
    if(g->ram[8U]!=slot) ++errors;
}
void mysmb_objects_step_hammer(struct mysmb_game *g,mysmb_u8 slot)
{record(g,1U,slot);}
void mysmb_world_impose_gravity_spr_object(struct mysmb_game *g,mysmb_u8 offset,
    mysmb_u8 amount,mysmb_u8 maximum)
{
    mysmb_u8 slot;
    slot=(mysmb_u8)(offset-13U);record(g,2U,slot);
    if(amount!=0x50U || maximum!=6U || g->ram[0]!=0x50U ||
       g->ram[1]!=3U || g->ram[2]!=6U) ++errors;
    g->ram[0xacU+slot]=returned_speed;
}
void mysmb_oam_relative_misc_position(struct mysmb_game *g,mysmb_u8 slot)
{record(g,3U,slot);}
void mysmb_oam_get_misc_offscreen_bits(struct mysmb_game *g,mysmb_u8 slot)
{record(g,4U,slot);}
void mysmb_objects_get_coin_bounding_box(struct mysmb_game *g,mysmb_u8 slot)
{record(g,5U,slot);}
void mysmb_objects_draw_jump_coin(struct mysmb_game *g,mysmb_u8 slot)
{record(g,6U,slot);}

int main(void)
{
    static struct mysmb_game g;
    unsigned int slot,state,speed,scroll,i,expected_count,first,cases;
    mysmb_u8 expected_state;

    cases=0U;
    for(slot=0U;slot<9U;++slot)
    for(state=0U;state<256U;++state)
    for(speed=4U;speed<=6U;++speed)
    for(scroll=0U;scroll<2U;++scroll) {
        memset(&g,0,sizeof(g));count=0U;returned_speed=(mysmb_u8)speed;
        g.ram[8U]=0xffU;g.ram[0x2aU+slot]=(mysmb_u8)state;
        g.ram[0x93U+slot]=0xffU;g.ram[0x7aU+slot]=0xffU;
        g.ram[0x775U]=(mysmb_u8)scroll;g.ram[0x747U]=0xffU;
        mysmb_objects_step_misc(&g);
        if(g.ram[8U]!=0U) ++errors;
        expected_state=(mysmb_u8)state;
        first=0U;expected_count=0U;
        if(state>=128U) {first=1U;expected_count=1U;}
        else if(state==1U) {
            first=2U;expected_count=5U;
            if(speed==5U) expected_state=2U;
        }
        else if(state!=0U) {
            expected_state=(mysmb_u8)(state+1U);
            if(expected_state==0x30U) expected_state=0U;
            else {first=3U;expected_count=4U;}
            if(g.ram[0x93U+slot]!=(mysmb_u8)(0xffU+scroll) ||
               g.ram[0x7aU+slot]!=(scroll!=0U?0U:0xffU)) ++errors;
        }
        if(g.ram[0x2aU+slot]!=expected_state || count!=expected_count) ++errors;
        for(i=0U;i<count;++i)
            if(ids[i]!=first+i || slots[i]!=slot) ++errors;
        ++cases;
    }
    /* A mixed array proves descending order and visits empty slots between
     * active entries; the last empty slot must still leave ObjectOffset zero. */
    memset(&g,0,sizeof(g));count=0U;returned_speed=5U;
    g.ram[0x32U]=0x81U;g.ram[0x30U]=1U;g.ram[0x2dU]=0x2fU;g.ram[0x2bU]=2U;
    mysmb_objects_step_misc(&g);
    if(count!=10U || slots[0]!=8U || ids[0]!=1U ||
       slots[1]!=6U || ids[1]!=2U || slots[6]!=1U || ids[6]!=3U ||
       g.ram[0x2dU]!=0U || g.ram[8U]!=0U) ++errors;
    ++cases;
    printf("misc lifetime: %u cases, %u errors\n",cases,errors);
    return errors!=0U;
}
