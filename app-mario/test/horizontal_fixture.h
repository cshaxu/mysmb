#ifndef MYSMB_HORIZONTAL_FIXTURE_H
#define MYSMB_HORIZONTAL_FIXTURE_H
#include "entrance_fixture.h"
static void mysmb_horizontal_fixture(unsigned char *ram,unsigned char n)
{
    static const unsigned char speeds[8]={0U,1U,0x0fU,0x10U,0x7fU,0x80U,0xf0U,0xffU};
    unsigned char k;k=(unsigned char)(n%32U);
    mysmb_entrance_fixture(ram,0U);ram[0xeU]=8U;ram[0x747U]=0U;
    ram[0xceU]=0x80U;ram[0x1dU]=0U;
    ram[0x57U]=speeds[k%8U];ram[0x400U]=(k&8U)?0xffU:0U;
    ram[0x86U]=(k&8U)?0xffU:0U;
    ram[0x70eU]=(n<32U && (k&16U))?1U:0U;
    if(n>=32U && n<64U) {
        ram[0xfU]=1U;ram[0x16U]=6U;ram[0x1eU]=0U;
        ram[0x6eU]=7U;ram[0x87U]=0x80U;ram[0xb6U]=1U;ram[0xcfU]=0x80U;
        ram[0x58U]=speeds[k%8U];ram[0x401U]=(k&8U)?0xffU:0U;
        ram[0x46U]=(k&16U)?2U:1U;
    }
    if(n>=64U) {
        ram[0x27U]=2U;ram[0x77U]=7U;ram[0x90U]=(k&16U)?0xffU:0U;
        ram[0xbfU]=1U;ram[0xd8U]=0x80U;ram[0x61U]=speeds[k%8U];
        ram[0x40aU]=(k&8U)?0xffU:0U;ram[0xa9U]=0U;ram[0x41fU+1U]=0U;
        ram[0x43dU]=0U;ram[0x3edU]=0U;
    }
}
static int mysmb_horizontal_argument(const char *text)
{
    static const char prefix[]="--fixture=t37-horizontal=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>95U) return 0;
    return (int)value+1;
}
#endif
