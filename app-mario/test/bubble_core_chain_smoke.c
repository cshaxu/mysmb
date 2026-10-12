#include "core/fireball/fireball.h"
#include <stdio.h>
#include <string.h>
int main(void)
{
    static struct mysmb_game checked,direct;
    static const mysmb_u8 ys[6]={0U,1U,0x1fU,0x20U,0xf0U,0xffU};
    static const mysmb_u8 move_y[6]={0xffU,0xf8U,0xf8U,0xf8U,0xefU,0xfeU};
    unsigned int slot,bit,facing,x,y,cases;
    cases=0U;
    for(slot=0U;slot<3U;++slot)
    for(bit=0U;bit<2U;++bit)
    for(facing=1U;facing<=2U;++facing)
    for(x=0U;x<256U;++x)
    for(y=0U;y<6U;++y) {
        memset(&checked,0,sizeof(checked));
        checked.ram[0xe4U+slot]=0xf8U;
        checked.ram[0x7a8U+slot]=bit!=0U?0xffU:0xfeU;
        checked.ram[0x33U]=(mysmb_u8)facing;checked.ram[0x86U]=(mysmb_u8)x;
        checked.ram[0x6dU]=0xffU;checked.ram[0xceU]=ys[y];
        direct=checked;direct.ram[7U]=(mysmb_u8)bit;
        mysmb_fireball_check_bubble(&checked,(mysmb_u8)slot);
        mysmb_fireball_setup_bubble(&direct,(mysmb_u8)slot);
        if(memcmp(checked.ram,direct.ram,sizeof(checked.ram))!=0) return 1;
        if(checked.ram[0x792U]!=(bit!=0U?0x20U:0x40U) ||
           checked.ram[0xcbU+slot]!=1U) return 2;
        /* Initial F8 must fall through to movement, rather than idle. */
        if(ys[y]==0xf0U && checked.ram[0xe4U+slot]!=0xf7U) return 3;
        if(facing==1U && x==255U &&
           (checked.ram[0x9cU+slot]!=8U || checked.ram[0x83U+slot]!=0U)) return 4;
        ++cases;
    }
    for(slot=0U;slot<3U;++slot)
    for(bit=0U;bit<2U;++bit)
    for(y=0U;y<6U;++y) {
        memset(&checked,0,sizeof(checked));checked.ram[0xe4U+slot]=ys[y];
        checked.ram[0x7a8U+slot]=(mysmb_u8)bit;
        checked.ram[0x792U]=9U;
        mysmb_fireball_check_bubble(&checked,(mysmb_u8)slot);
        if(checked.ram[0xe4U+slot]!=move_y[y] || checked.ram[7U]!=bit ||
           checked.ram[0x792U]!=9U) return 5;
    }
    memset(&checked,0,sizeof(checked));checked.ram[0xe4U]=0xf8U;
    checked.ram[0x792U]=1U;checked.ram[0x42cU]=0x72U;checked.ram[0x7a8U]=1U;
    mysmb_fireball_check_bubble(&checked,0U);
    if(checked.ram[7U]!=1U || checked.ram[0xe4U]!=0xf8U || checked.ram[0x42cU]!=0x72U) return 6;
    printf("bubble entry equivalence=%u; wrap/borrow/idle checks passed\n",cases);
    return 0;
}
