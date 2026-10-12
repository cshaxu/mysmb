#ifndef MYSMB_ENEMY_LOOP_FIXTURE_H
#define MYSMB_ENEMY_LOOP_FIXTURE_H
#include "entrance_fixture.h"

/* Controlled source RAM at NMI; CPU, stack and ROM remain untouched. */
static void mysmb_enemy_loop_fixture(unsigned char *ram, unsigned char n)
{
    static const unsigned char worlds[11]={3,3,6,6,6,6,6,6,7,7,7};
    static const unsigned char pages[11]={5,9,4,5,6,8,9,10,6,11,16};
    static const unsigned char heights[11]={0x40,0xb0,0xb0,0x80,0x40,0x40,
        0x80,0x40,0xf0,0xf0,0xf0};
    unsigned char row, kind;
    mysmb_entrance_fixture(ram,0U);
    if(n>=88U) {
        ram[0xeU]=8U;ram[0x747U]=0xffU;ram[0x71fU]=7U;
        ram[0x16U]=0x33U;
        if(n==88U) ram[0xfU]=0x81U;
        if(n==89U) { ram[0xfU]=0x81U;ram[0x10U]=1U; }
        if(n==90U) ram[0xfU]=0x80U;
        if(n==91U) { ram[0xfU]=0x8fU;ram[0x1eU]=0U; }
        if(n==92U) { ram[0xfU]=0x8fU;ram[0x1eU]=1U; }
        if(n==93U) ram[0xfU]=1U;
        if(n==95U) ram[0xfU]=0x7fU;
        return;
    }
    row=(unsigned char)(n/8U);kind=(unsigned char)(n%8U);
    /* The palette-transition state preserves ground state until the enemy
     * loop. Normal player control would mark an unsupported fixture falling. */
    ram[0xeU]=12U;ram[0x747U]=0xffU;ram[0x71fU]=0U;
    ram[0x745U]=1U;ram[0x726U]=0U;
    ram[0x75fU]=worlds[row];ram[0x725U]=pages[row];
    ram[0xceU]=heights[row];ram[0x1dU]=0U;
    ram[0x6d9U]=2U;ram[0x6daU]=2U;
    ram[0x6cdU]=0U;ram[0x6cbU]=0U;
    if(kind==1U) ++ram[0xceU];
    if(kind==2U) ram[0x1dU]=1U;
    if(kind==3U) { ram[0x6d9U]=0xffU;ram[0x6daU]=0xffU; }
    if(kind==4U) ram[0x745U]=0U;
    if(kind==5U) ram[0x726U]=1U;
    if(kind==6U) ram[0x75fU]=0U;
    if(kind==7U) ram[0x6cdU]=0x12U;
}
static int mysmb_enemy_loop_argument(const char *text)
{
    static const char prefix[]="--fixture=t38-loop=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>95U) return 0;
    return (int)value+1;
}
#endif
