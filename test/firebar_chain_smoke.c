#include "game/enemy/firebar.h"
#include "game/enemy/actor_slots.h"
#include "game/objects.h"
#include <string.h>

static unsigned char data[0x5000];
static unsigned char offsets[16];
static unsigned int stage, bad, draws, injuries, offscreen, mutate;
void mysmb_firebar_offscreen(struct mysmb_game *g,mysmb_u8 slot)
{
    if(stage!=0U || slot!=0U) ++bad;
    stage=1U;g->ram[0x3d1U]=(mysmb_u8)offscreen;
}
mysmb_u8 mysmb_firebar_spin(struct mysmb_game *g,mysmb_u8 slot,mysmb_u8 speed)
{
    if(stage!=1U || slot!=0U || speed!=3U) ++bad;
    stage=2U;g->ram[7U]=speed;return 0x28U;
}
mysmb_u8 mysmb_firebar_relative(struct mysmb_game *g,mysmb_u8 slot)
{
    if((stage!=1U && stage!=2U) || slot!=0U) ++bad;
    stage=3U;g->ram[0U]=slot;g->ram[0x3aeU]=0x80U;g->ram[0x3b9U]=0x78U;
    return 0x80U;
}
mysmb_u8 mysmb_oam_draw_firebar(struct mysmb_game *g,mysmb_u8 oam)
{
    if(stage!=3U || draws>=16U) { ++bad;return oam; }
    offsets[draws++]=oam;g->ram[0x201U+oam]=0x64U;
    return (mysmb_u8)(oam+(mutate && draws==1U?8U:0U));
}
void mysmb_objects_force_injury(struct mysmb_game *g)
{
    if(draws!=1U || g->ram[0U]!=1U || g->ram[0x46U]!=1U) ++bad;
    ++injuries;g->ram[0U]=0xeeU;g->ram[5U]=0x99U;g->ram[0x747U]=0xffU;
}
int main(void)
{
    static struct mysmb_game g;
    unsigned int n,i;
    mysmb_u8 result;
    for(n=0U;n<5U;++n) {
        memset(&g,0,sizeof(g));memset(data,0,sizeof(data));
        g.area_prg=data;g.area_prg_size=sizeof(data);
        g.ram[0x16U]=(mysmb_u8)(n==0U?27U:31U);
        g.ram[0x6e5U]=0x40U;g.ram[0x6e6U]=0x80U;g.ram[0x6cfU]=1U;
        g.ram[0x388U]=3U;g.ram[0xa0U]=8U;
        g.ram[0x754U]=1U;g.ram[0xb5U]=1U;g.ram[0xceU]=0x60U;
        g.ram[0x207U]=0x7cU;
        if(n!=2U) g.ram[0x747U]=1U;
        stage=bad=draws=injuries=0U;offscreen=n==3U?8U:0U;mutate=n==4U;
        result=mysmb_enemy_proc_firebar(&g,0U);
        if(bad) return 1;
        if(n==3U) {
            if(stage!=1U || draws || g.ram[0xa0U]!=8U) return 2;
            continue;
        }
        if(draws!=(n==0U?6U:12U) || injuries!=(n==2U?1U:0U) ||
            result!=(n==2U?1U:0U)) return 3;
        if(g.ram[0U]!=(n==0U?5U:11U) || g.ram[0xedU]!=g.ram[0U] ||
            g.ram[0xa0U]!=(n==0U?8U:9U)) return 4;
        if(offsets[0]!=0x40U || offsets[1]!=(n==4U?0x4cU:0x44U)) return 5;
        for(i=2U;i<6U;++i) if(offsets[i]!=(mysmb_u8)(0x40U+i*4U+(n==4U?8U:0U))) return 6;
        if(n!=0U) for(i=6U;i<12U;++i) if(offsets[i]!=(mysmb_u8)(0x80U+(i-6U)*4U)) return 7;
    }
    memset(&g,0,sizeof(g));memset(data,0,sizeof(data));
    g.area_prg=data;g.area_prg_size=sizeof(data);
    data[0x4cc7U]=2U;data[0x4ccfU]=9U;data[0x4d2aU]=1U;
    if(!mysmb_firebar_get_position(&g,0U) || g.ram[1U]!=2U ||
        g.ram[2U]!=9U || g.ram[3U]!=1U) return 8;
    /* Residual source reads: byte-offset addition wraps before table access. */
    g.ram[0U]=0xffU;data[0x4e2dU]=0xf0U;
    data[0x4db8U]=0x13U;data[0x4dbeU]=0x27U;data[0x4d49U]=0x35U;
    if(!mysmb_firebar_get_position(&g,0xffU) || g.ram[1U]!=0x13U ||
        g.ram[2U]!=0x27U || g.ram[3U]!=0x35U) return 9;
    return 0;
}
