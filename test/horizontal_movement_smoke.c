#include "game/world/world.h"
#include "game/player.h"
#include <stdio.h>
#include <string.h>
static unsigned long cases;
static int run_case(unsigned int offset,unsigned int speed,unsigned int force,
                    unsigned int x,unsigned int page,unsigned int entry)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    long position,velocity;
    unsigned int integer,new_x;
    mysmb_u8 actual,answer;
    memset(&g,0xa5,sizeof(g));g.ram[8U]=(mysmb_u8)(offset-1U);
    g.ram[0x70eU]=0U;g.ram[0x57U+offset]=(mysmb_u8)speed;
    g.ram[0x400U+offset]=(mysmb_u8)force;
    g.ram[0x86U+offset]=(mysmb_u8)x;g.ram[0x6dU+offset]=(mysmb_u8)page;
    memcpy(expected,g.ram,sizeof(expected));
    velocity=speed<128U?(long)speed:(long)speed-256L;
    position=((long)page*256L+(long)x)*256L+(long)force+velocity*16L;
    if(position<0L) position+=16777216L;
    if(position>=16777216L) position-=16777216L;
    new_x=(unsigned int)((position/256L)%256L);
    integer=speed/16U;if(speed>=128U) integer+=240U;
    expected[0U]=(unsigned char)integer;
    expected[1U]=(unsigned char)((speed%16U)*16U);
    expected[2U]=speed>=128U?255U:0U;
    expected[0x400U+offset]=(unsigned char)(position%256L);
    expected[0x86U+offset]=(unsigned char)new_x;
    expected[0x6dU+offset]=(unsigned char)(position/65536L);
    answer=(mysmb_u8)(new_x-x);
    if(entry==1U) actual=mysmb_player_move_horizontally(&g);
    else if(entry==2U) actual=mysmb_world_move_enemy_horizontally(&g,(mysmb_u8)(offset-1U));
    else actual=mysmb_world_move_spr_object_horizontally(&g,(mysmb_u8)offset);
    ++cases;
    if(actual!=answer || memcmp(expected,g.ram,sizeof(expected))) {
        printf("offset=%u speed=%u force=%u x=%u page=%u entry=%u\n",offset,speed,force,x,page,entry);
        return 1;
    }
    return 0;
}
int main(void)
{
    static const unsigned int offsets[7]={0U,1U,6U,7U,9U,13U,22U};
    static const unsigned int positions[5]={0U,1U,127U,254U,255U};
    static const unsigned int pages[4]={0U,1U,127U,255U};
    static struct mysmb_game g;
    static unsigned char unchanged[2048];
    unsigned int i,speed,force,p,slot,gate;
    for(i=0U;i<7U;++i)
        for(speed=0U;speed<256U;++speed)
            for(force=0U;force<256U;++force)
                for(p=0U;p<5U;++p)
                    if(run_case(offsets[i],speed,force,positions[p],pages[(speed+force+p)%4U],0U)) return 1;
    for(speed=0U;speed<256U;++speed)
        for(force=0U;force<256U;++force)
            if(run_case(0U,speed,force,positions[speed%5U],pages[force%4U],1U)) return 1;
    for(slot=0U;slot<6U;++slot)
        for(speed=0U;speed<256U;++speed)
            if(run_case(slot+1U,speed,255U,positions[speed%5U],pages[speed%4U],2U)) return 1;
    for(gate=1U;gate<256U;++gate) {
        memset(&g,0xa5,sizeof(g));g.ram[0x70eU]=(mysmb_u8)gate;
        memcpy(unchanged,g.ram,sizeof(unchanged));
        if(mysmb_player_move_horizontally(&g)!=gate || memcmp(unchanged,g.ram,sizeof(unchanged))) return 1;
    }
    printf("%lu arithmetic/write/return cases, 255 no-write gate cases\n",cases);
    return 0;
}
