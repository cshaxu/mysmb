#include "game/enemy/platform.h"
#include <stdio.h>
#include <string.h>
static unsigned char expected[2048];
static unsigned int failures,cases,calls,small;
static mysmb_u8 expected_slot,expected_old_y;
static void check(struct mysmb_game *g,mysmb_u8 slot)
{ ++calls;if(slot!=expected_slot || memcmp(g->ram,expected,2048U))++failures; }
void mysmb_platform_position_player_vertical(struct mysmb_game *g,mysmb_u8 s)
{ if(small)++failures;check(g,s); }
void mysmb_platform_position_player_small(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 c)
{ if(!small || c!=expected[0x3a2U+s])++failures;check(g,s); }
void mysmb_enemy_x_counter_platform(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 m)
{ (void)g;(void)s;(void)m;++failures; }
void mysmb_enemy_move_with_x_counters(struct mysmb_game *g,mysmb_u8 s)
{ (void)g;(void)s;++failures; }
void mysmb_enemy_move_drop_platform(struct mysmb_game *g,mysmb_u8 s)
{ (void)g;(void)s;++failures; }
mysmb_u8 mysmb_world_move_enemy_horizontally(struct mysmb_game *g,mysmb_u8 s)
{ (void)g;(void)s;++failures;return 0U; }
void mysmb_world_move_platform_vertically(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 up)
{ (void)g;(void)s;(void)up;++failures; }
int main(void)
{
    static struct mysmb_game g;
    unsigned int a,b,m,hit;unsigned long fixed;
    mysmb_u8 s;
    for(a=0U;a<256U;++a)for(b=0U;b<256U;++b)for(m=0U;m<16U;++m) {
        memset(&g,0,sizeof(g));s=(mysmb_u8)(a&1U?5U:0U);expected_slot=s;
        small=(m&2U)?1U:0U;hit=(m&4U)?1U:0U;calls=0U;
        g.ram[8U]=(mysmb_u8)(5U-s);g.ram[0x747U]=(mysmb_u8)(m&1U);
        g.ram[0x417U+s]=(mysmb_u8)a;g.ram[0x434U+s]=(mysmb_u8)b;
        g.ram[0xa0U+s]=(mysmb_u8)(m&8U?0xffU:1U);
        g.ram[0xcfU+s]=(mysmb_u8)(a^b);expected_old_y=g.ram[0xcfU+s];
        g.ram[0xb6U+s]=0x7fU;
        g.ram[0x3a2U+s]=(mysmb_u8)(small?(hit?1U+(a&1U):0U):(hit?3U:0xffU));
        memcpy(expected,g.ram,2048U);
        /* Treat the pair as unsigned fixed point, modulo 16 bits. The
         * original high-Y byte is deliberately outside this integration. */
        if(!(m&1U)) {
            fixed=(unsigned long)expected_old_y*256UL+a+b+(unsigned long)g.ram[0xa0U+s]*256UL;
            expected[0x417U+s]=(unsigned char)fixed;
            expected[0xcfU+s]=(unsigned char)(fixed/256UL);
        }
        if(small)mysmb_platform_move_small(&g,s);else mysmb_platform_move_large_lift(&g,s);
        if(calls!=hit || memcmp(g.ram,expected,2048U))++failures;
        ++cases;
    }
    printf("lift platform cases=%u failures=%u\n",cases,failures);
    return failures?1:0;
}
