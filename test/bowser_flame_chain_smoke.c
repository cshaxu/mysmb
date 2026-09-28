#include "game/enemy/actor_slots.h"
#include "game/enemy/frenzy.h"
#include "game/oam/oam.h"
#include "game/objects.h"
#include <string.h>
const mysmb_u8 mysmb_enemy_flame_y_positions[4]={0x90U,0x80U,0x70U,0x90U};
static mysmb_u8 mask, expected_force;
static unsigned int calls,bad;
void mysmb_oam_relative_enemy_position(struct mysmb_game *g,mysmb_u8 slot)
{
    if (calls++ != 0U || slot!=5U || g->ram[0U]!=expected_force) ++bad;
    g->ram[0U]=5U;g->ram[0x3aeU]=0xfcU;g->ram[0x3b9U]=0x70U;
}
mysmb_u8 mysmb_objects_get_enemy_offscreen_bits(const struct mysmb_game *input,mysmb_u8 slot)
{
    /* The underlying test object is mutable; model the original child's
     * scratch writes despite this legacy const seam. */
    struct mysmb_game *g;
    g=(struct mysmb_game *)input;
    if (calls++ != 1U || slot!=5U || g->ram[0U]!=0x54U || g->ram[0x3aeU]!=0x14U) ++bad;
    g->ram[0U]=0xa5U;
    return mask;
}
int main(void)
{
    static struct mysmb_game g;
    static const mysmb_u8 forces[4]={0U,0x3fU,0x40U,0xffU};
    static const mysmb_u8 xs[4]={0U,1U,2U,255U};
    unsigned int hard,hold,force,x,normal,flip,m,i,count;
    unsigned long position,expected;
    for(hard=0U;hard<2U;++hard) for(hold=0U;hold<2U;++hold)
    for(force=0U;force<4U;++force) for(x=0U;x<4U;++x)
    for(normal=0U;normal<2U;++normal) for(flip=0U;flip<2U;++flip)
    for(m=0U;m<16U;++m) {
        memset(&g,0,sizeof(g));calls=bad=0U;mask=(mysmb_u8)m;
        g.ram[8U]=5U;g.ram[0U]=0xccU;g.ram[0x747U]=(mysmb_u8)hold;
        g.ram[0x6ccU]=(mysmb_u8)hard;g.ram[0x406U]=forces[force];
        g.ram[0x8cU]=xs[x];g.ram[0x73U]=0U;
        g.ram[0x1cU]=0U;g.ram[0xd4U]=0x7fU;g.ram[0x439U]=255U;
        g.ram[0x23U]=(mysmb_u8)(normal?0U:0x20U);
        g.ram[9U]=(mysmb_u8)(flip*2U);g.ram[0x6eaU]=0x30U;
        g.ram[0x23cU]=0x91U;
        expected_force=(mysmb_u8)(hold?0xccU:(hard?0x60U:0x40U));
        position=(unsigned long)xs[x]*256UL+forces[force];
        expected=hold?position:(position-256UL-(hard?96UL:64UL))&0xffffffUL;
        mysmb_enemy_proc_bowser_flame(&g,5U);
        count=normal?2U:1U;
        if(bad || calls!=count || g.ram[0x406U]!=(mysmb_u8)expected ||
            g.ram[0x8cU]!=(mysmb_u8)(expected>>8U) || g.ram[0x73U]!=(mysmb_u8)(expected>>16U) ||
            g.ram[0xd4U]!=(mysmb_u8)(hold?0x7fU:0x7eU))return 1;
        if(!normal) {
            if(g.ram[0U]!=5U || g.ram[0x3aeU]!=0xfcU || g.ram[0x230U]!=0U)return 2;
            continue;
        }
        if(g.ram[0U]!=0xa5U || g.ram[1U]!=(mysmb_u8)(flip?0x82U:2U) ||
            g.ram[0x3d1U]!=mask || g.ram[0x23cU]!=(mysmb_u8)((mask&1U)?0xf8U:0x91U))return 3;
        for(i=0U;i<3U;++i) {
            if(g.ram[0x230U+i*4U]!=(mysmb_u8)((mask&(8U>>i))?0xf8U:0x70U) ||
               g.ram[0x231U+i*4U]!=(mysmb_u8)(0x51U+i) ||
               g.ram[0x232U+i*4U]!=(mysmb_u8)(flip?0x82U:2U) ||
               g.ram[0x233U+i*4U]!=(mysmb_u8)(0xfcU+8U*i))return 4;
        }
    }
    return 0;
}
