#include "game/enemy/actor_slots.h"
#include "game/enemy/movement.h"
#include <string.h>
static unsigned int gravity_calls;
void mysmb_enemy_move_slow_vertically(struct mysmb_game *g,mysmb_u8 slot)
{ ++gravity_calls;g->ram[0xcfU+slot]=0x93U; }
int main(void)
{
    static struct mysmb_game g;
    unsigned char expected[2048];
    unsigned int n,slot;
    for(n=0U;n<11U;++n) {
        memset(&g,0,sizeof(g));slot=n<2U?n:2U;
        g.ram[0x16U+slot]=10U;g.ram[0x1eU+slot]=0x1fU;
        g.ram[0x401U+slot]=0x40U;g.ram[0x87U+slot]=1U;
        g.ram[0x6eU+slot]=3U;g.ram[0xcfU+slot]=0x80U;
        g.ram[0xb6U+slot]=1U;g.ram[0x417U+slot]=0x20U;
        g.ram[0x434U+slot]=0x80U;g.ram[0x58U+slot]=0x0fU;
        g.ram[2U]=0x99U;g.ram[3U]=0x99U;
        if(n==1U) {
            g.ram[0x16U+slot]=11U;g.ram[0x401U+slot]=0x7fU;
            g.ram[0x87U+slot]=0U;g.ram[0x6eU+slot]=0U;
        }
        if(n==2U) {
            g.ram[0x417U+slot]=0U;g.ram[0xcfU+slot]=0U;
            g.ram[0xb6U+slot]=0U;g.ram[0x434U+slot]=0U;
        }
        if(n==3U) {
            g.ram[0x58U+slot]=0x10U;g.ram[0x417U+slot]=0xffU;
            g.ram[0xcfU+slot]=0xffU;g.ram[0xb6U+slot]=0xffU;
            g.ram[0x434U+slot]=0x10U;
        }
        if(n==4U) g.ram[0xcfU+slot]=0x8fU;
        if(n==5U) {
            g.ram[0xcfU+slot]=0x71U;g.ram[0x58U+slot]=0xffU;
        }
        if(n==6U) { g.ram[0xcfU+slot]=0U;g.ram[0x434U+slot]=0xffU; }
        if(n==7U) { g.ram[0xcfU+slot]=0xffU;g.ram[0x434U+slot]=0U; }
        if(n==8U) g.ram[0xcfU+slot]=0U;
        if(n==10U) g.ram[0x1eU+slot]=0x20U;
        memcpy(expected,g.ram,2048U);
        if(n!=10U) {
            expected[2U]=0x20U;expected[3U]=0U;expected[0x401U+slot]=0U;
            if(slot>=2U) expected[0x417U+slot]=0U;
        }
        switch(n) {
        case 1U:
            expected[0x401U+slot]=0xffU;expected[0x87U+slot]=0xffU;
            expected[0x6eU+slot]=0xffU;break;
        case 2U:
            expected[0x417U+slot]=0xe0U;expected[0xcfU+slot]=0xffU;
            expected[0xb6U+slot]=0xffU;break;
        case 3U:
            expected[0x417U+slot]=0x1fU;expected[0xcfU+slot]=0U;
            expected[0xb6U+slot]=0U;break;
        case 4U:expected[0x58U+slot]=0U;break;
        case 5U:expected[0x417U+slot]=0x40U;expected[0x58U+slot]=0x10U;break;
        case 8U:expected[0x58U+slot]=0x10U;break;
        case 10U:expected[0xcfU+slot]=0x93U;break;
        default:break;
        }
        gravity_calls=0U;mysmb_objects_step_swimming_cheep_cheeps_slot(&g,(mysmb_u8)slot);
        if(memcmp(g.ram,expected,2048U)!=0 || gravity_calls!=(n==10U?1U:0U)) return (int)n+1;
    }
    return 0;
}
