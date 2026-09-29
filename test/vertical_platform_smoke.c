#include "game/enemy/platform.h"
#include "game/world/world.h"
#include <stdio.h>
#include <string.h>
static unsigned int moves,placements,failures,cases;
static mysmb_u8 expected_slot,expected_up,returned_slot,placement_slot;
void mysmb_world_move_platform_vertically(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 up)
{
    ++moves;
    if(s!=expected_slot || up!=expected_up)++failures;
    g->ram[8U]=returned_slot;
}
void mysmb_platform_position_player_vertical(struct mysmb_game *g,mysmb_u8 s)
{
    (void)g;++placements;if(s!=placement_slot)++failures;
}
static void verify(unsigned int y,unsigned int bound,unsigned int mode)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned int frame,want_move,want_place;
    mysmb_u8 s;
    memset(&g,0,sizeof(g));s=(mysmb_u8)(mode&1U?5U:0U);
    expected_slot=s;returned_slot=(mysmb_u8)(5U-s);
    frame=(mode>>1U)&7U;
    g.ram[8U]=s;g.ram[9U]=(mysmb_u8)frame;
    g.ram[0xcfU+s]=(mysmb_u8)y;g.ram[0x417U+s]=0xa5U;
    g.ram[0x3a2U+s]=(mysmb_u8)(mode&16U?0xffU:3U);
    g.ram[0x3a2U+returned_slot]=(mysmb_u8)(mode&16U?2U:0xffU);
    g.ram[0x401U+s]=(mysmb_u8)bound;g.ram[0x58U+s]=0x80U;
    if(mode&32U) {
        g.ram[0xa0U+s]=(mysmb_u8)(mode&64U?0U:0xffU);
        g.ram[0x434U+s]=(mysmb_u8)(mode&64U?1U:0U);
        g.ram[0x58U+s]=(mysmb_u8)bound;
    }
    memcpy(expected,g.ram,2048U);
    /* Independent partitions: moving always uses the center; at rest,
     * the half-open [0,top) interval only ticks every eighth frame. */
    want_move=(mode&32U)?1U:(y>=bound?1U:0U);
    if(!(mode&32U))expected[0x417U+s]=0U;
    if(want_move) {
        expected[8U]=returned_slot;
        expected_up=(mysmb_u8)(y>=g.ram[0x58U+s]);
        want_place=(mode&16U)?1U:0U;placement_slot=returned_slot;
    } else {
        if(frame==0U)expected[0xcfU+s]=(unsigned char)(y+1U);
        want_place=(mode&16U)?0U:1U;placement_slot=s;
    }
    moves=placements=0U;mysmb_platform_move_y(&g,s);
    if(moves!=want_move || placements!=want_place || memcmp(expected,g.ram,2048U))++failures;
    ++cases;
}
int main(void)
{
    unsigned int y,b,m;
    for(y=0U;y<256U;++y)for(b=0U;b<256U;++b) {
        verify(y,b,(y+b)%32U);
        verify(y,b,32U+(y+b)%32U);
        verify(y,b,96U+(y+b)%32U);
    }
    for(m=0U;m<32U;++m)for(y=0U;y<256U;++y)verify(y,255U,m);
    printf("vertical platform cases=%u failures=%u\n",cases,failures);
    return failures?1:0;
}
