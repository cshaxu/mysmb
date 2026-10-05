#include "core/enemy/actor_slots.h"
#include "core/enemy/x_counter.h"
#include "core/world/world.h"
#include <string.h>

static unsigned char expected[2048];
static unsigned int bad,calls;
static mysmb_u8 child_a,child_frame,slot_expected;
mysmb_u8 mysmb_world_move_enemy_horizontally(struct mysmb_game *g,mysmb_u8 slot)
{
    if(slot!=slot_expected || memcmp(g->ram,expected,2048U)) ++bad;
    ++calls;g->ram[0x58U+slot]=0x55U;g->ram[9U]=child_frame;
    expected[9U]=child_frame;
    return child_a;
}
int main(void)
{
    static struct mysmb_game g;
    static const unsigned char primary[4]={0U,1U,0xfeU,0xffU};
    unsigned int slot,maximum,p,q,phase,secondary,mode,saved;
    for(slot=0U;slot<6U;++slot) for(maximum=0U;maximum<256U;++maximum)
    for(p=0U;p<4U;++p) for(q=0U;q<8U;++q) for(phase=0U;phase<4U;++phase) {
        secondary=q==0U?0U:(q==1U?((maximum-1U)&255U):(q==2U?maximum:
            (q==3U?((maximum+1U)&255U):(q==4U?1U:(q==5U?127U:(q==6U?128U:255U))))));
        memset(g.ram,0xa5,2048U);g.ram[9U]=(mysmb_u8)phase;
        g.ram[0xa0U+slot]=primary[p];g.ram[0x58U+slot]=(mysmb_u8)secondary;
        memcpy(expected,g.ram,2048U);expected[1U]=(mysmb_u8)maximum;
        if(phase==0U) {
            if((primary[p]&1U)==0U) {
                if(secondary==maximum) ++expected[0xa0U+slot];
                else ++expected[0x58U+slot];
            }
            else if(secondary==0U) ++expected[0xa0U+slot];
            else --expected[0x58U+slot];
        }
        mysmb_enemy_x_counter_platform(&g,(mysmb_u8)slot,(mysmb_u8)maximum);
        if(memcmp(g.ram,expected,2048U)) return 1;
    }
    for(slot=0U;slot<6U;++slot) for(p=0U;p<4U;++p)
    for(secondary=0U;secondary<256U;++secondary) for(mode=0U;mode<4U;++mode) {
        memset(g.ram,0xa5,2048U);slot_expected=(mysmb_u8)slot;
        g.ram[0xa0U+slot]=primary[p];g.ram[0x58U+slot]=(mysmb_u8)secondary;
        g.ram[9U]=1U;g.ram[0xcfU+slot]=(mysmb_u8)(mode&1U?255U:0U);
        memcpy(expected,g.ram,2048U);expected[1U]=0x13U;
        expected[0x46U+slot]=(mysmb_u8)(primary[p]&2U?1U:2U);
        expected[0x58U+slot]=(mysmb_u8)(primary[p]&2U?secondary:0U-secondary);
        saved=secondary;child_frame=(mysmb_u8)(mode==0U?1U:(mode==1U?0U:0x40U));
        child_a=(mysmb_u8)(secondary^0x93U);calls=bad=0U;
        mysmb_objects_step_flying_green_paratroopas_slot(&g,(mysmb_u8)slot);
        expected[0x58U+slot]=(mysmb_u8)saved;expected[0U]=child_a;
        if((child_frame&3U)==0U) {
            expected[0U]=(mysmb_u8)(child_frame&0x40U?1U:255U);
            expected[0xcfU+slot]=(mysmb_u8)(expected[0xcfU+slot]+expected[0U]);
        }
        if(bad || calls!=1U || memcmp(g.ram,expected,2048U)) return 2;
    }
    return 0;
}
