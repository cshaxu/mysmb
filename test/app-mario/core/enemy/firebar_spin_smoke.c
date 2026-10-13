#include "core/enemy/firebar.h"
#include "core/objects.h"
#include "core/oam/oam.h"
#include <stdio.h>
#include <string.h>

/* Uncalled sibling seams; this executable links the spin owner only. */
void mysmb_oam_get_enemy_offscreen_bits(struct mysmb_game *g,mysmb_u8 s)
{ (void)g;(void)s; }
void mysmb_oam_relative_enemy_position(struct mysmb_game *g,mysmb_u8 s)
{ (void)g;(void)s; }
int main(void)
{
    static struct mysmb_game g;
    static mysmb_u8 expected[2048];
    static const mysmb_u8 highs[4]={0U,1U,127U,255U};
    static const mysmb_u8 directions[3]={0U,1U,255U};
    unsigned int slot_index,d,h,low,speed,i;
    unsigned long phase,next,cases;
    mysmb_u8 slot,returned;
    cases=0UL;
    for(i=0U;i<2048U;++i)g.ram[i]=(mysmb_u8)i;
    for(slot_index=0U;slot_index<2U;++slot_index)
    for(d=0U;d<3U;++d)
    for(h=0U;h<4U;++h)
    for(low=0U;low<256U;++low)
    for(speed=0U;speed<256U;++speed) {
        slot=(mysmb_u8)(slot_index*5U);
        g.ram[7U]=0xa5U;
        g.ram[0x34U+slot]=directions[d];g.ram[0x58U+slot]=(mysmb_u8)low;
        g.ram[0xa0U+slot]=highs[h];memcpy(expected,g.ram,2048U);
        phase=(unsigned long)highs[h]*256UL+low;
        next=(d==0U?phase+speed:phase+65536UL-speed)&65535UL;
        expected[7U]=(mysmb_u8)speed;expected[0x58U+slot]=(mysmb_u8)next;
        returned=mysmb_firebar_spin(&g,slot,(mysmb_u8)speed);
        if(returned!=(mysmb_u8)(next>>8U) || memcmp(expected,g.ram,2048U)) {
            printf("spin mismatch slot=%u dir=%u high=%u low=%u speed=%u\n",
                   (unsigned int)slot,d,h,low,speed);return 1;
        }
        ++cases;
    }
    printf("Firebar spin exact RAM/A cases=%lu\n",cases);return 0;
}
