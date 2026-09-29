#include "game/objects.h"
#include <stdio.h>
#include <string.h>
static unsigned char expected[2048];
static unsigned int calls,failures,cases;
static mysmb_u8 expected_slot;
void mysmb_objects_erase_enemy(struct mysmb_game *g,mysmb_u8 slot)
{ ++calls;if(slot!=expected_slot || memcmp(g->ram,expected,2048U))++failures; }
int main(void)
{
    static struct mysmb_game g;
    unsigned int id,x,v,want,inside_left,inside_right;
    unsigned long left,right,enemy;
    long raw_left;
    mysmb_u8 s;
    for(id=0U;id<256U;++id)for(x=0U;x<256U;++x)for(v=0U;v<8U;++v) {
        memset(&g,0,sizeof(g));s=(mysmb_u8)(v&1U?5U:7U);expected_slot=s;calls=0U;
        g.ram[0x16U+s]=(mysmb_u8)id;g.ram[0x1eU+s]=(mysmb_u8)(v&4U?5U:0U);
        g.ram[0x71cU]=(mysmb_u8)x;g.ram[0x71aU]=(mysmb_u8)(v&2U?255U:0U);
        g.ram[0x71dU]=(mysmb_u8)(255U-x);g.ram[0x71bU]=(mysmb_u8)(g.ram[0x71aU]+1U);
        g.ram[0U]=0xa1U;g.ram[1U]=0xa2U;g.ram[2U]=0xa3U;g.ram[3U]=0xa4U;
        /* Word-domain oracle: special IDs wrap their +57 low byte before
         * the subtraction, and only the final page borrow feeds right +72. */
        raw_left=(long)g.ram[0x71aU]*256L;
        if(id==5U || id==13U)raw_left+=(long)((x+57U)%256U)-72L-(x+57U<256U?1L:0L);
        else raw_left+=(long)x-72L-(id<13U?1L:0L);
        left=(unsigned long)(raw_left+65536L)%65536UL;
        right=((unsigned long)g.ram[0x71bU]*256UL+g.ram[0x71dU]+72UL+(raw_left>=0L?1UL:0UL))%65536UL;
        switch(v) {
        case 0U:enemy=(left+65535UL)%65536UL;break;
        case 1U:enemy=left;break;
        case 2U:enemy=(left+1UL)%65536UL;break;
        case 3U:enemy=(right+65535UL)%65536UL;break;
        case 4U:enemy=right;break;
        case 5U:enemy=(right+1UL)%65536UL;break;
        case 6U:enemy=(left+32768UL)%65536UL;break;
        default:enemy=(right+32768UL)%65536UL;break;
        }
        g.ram[0x87U+s]=(mysmb_u8)enemy;g.ram[0x6eU+s]=(mysmb_u8)(enemy/256UL);
        memcpy(expected,g.ram,2048U);want=0U;
        if(id!=20U) {
            expected[0U]=(unsigned char)(left/256UL);expected[1U]=(unsigned char)left;
            expected[2U]=(unsigned char)(right/256UL);expected[3U]=(unsigned char)right;
            inside_left=((enemy+65536UL-left)%65536UL)<32768UL;
            inside_right=((enemy+65536UL-right)%65536UL)>=32768UL;
            want=!inside_left || (!inside_right && g.ram[0x1eU+s]!=5U && id!=13U && id!=48U && id!=49U && id!=50U);
        }
        mysmb_objects_check_enemy_offscreen_bounds(&g,s);
        if(calls!=want || memcmp(g.ram,expected,2048U))++failures;
        ++cases;
    }
    printf("offscreen bounds cases=%u failures=%u\n",cases,failures);
    return failures?1:0;
}
