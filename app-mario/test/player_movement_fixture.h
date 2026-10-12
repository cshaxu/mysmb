#ifndef MYSMB_PLAYER_MOVEMENT_FIXTURE_H
#define MYSMB_PLAYER_MOVEMENT_FIXTURE_H
#include "entrance_fixture.h"
/* Normal NMI RAM inputs; original physics and all state children execute. */
static void mysmb_player_movement_fixture(unsigned char *ram,unsigned char scenario)
{
    mysmb_entrance_fixture(ram,0U);
    ram[0xeU]=8U;ram[0x716U]=1U;ram[0xceU]=0x80U;
    ram[0x714U]=4U;ram[0x70eU]=1U;ram[0x789U]=0x55U;
    ram[0x709U]=0x21U;ram[0x70aU]=0x42U;
    ram[0x706U]=6U;ram[0x708U]=0x80U;
    if(scenario>=182U) {
        static const unsigned char absolute[8]={0U,10U,11U,13U,14U,27U,28U,33U};
        static const unsigned char speed[8]={0U,1U,0xffU,0x28U,0xd8U,0x7fU,0x80U,0x81U};
        unsigned char n;
        n=(unsigned char)(scenario-182U);ram[0x1dU]=0U;ram[0x70bU]=0U;
        ram[0x700U]=absolute[n%8U];ram[0x57U]=speed[n%8U];
        ram[0x705U]=(n&16U)!=0U?0xffU:0U;
        ram[0x490U]=n<32U?3U:0U;
        ram[0x33U]=(n&4U)!=0U?2U:1U;ram[0x45U]=1U;
        ram[0x703U]=0x5aU;
        return;
    }
    if(scenario>=109U) {
        static const unsigned char speed[8]={0U,8U,9U,15U,16U,24U,25U,28U};
        unsigned char n;
        n=(unsigned char)(scenario-109U);ram[0x70bU]=1U;ram[0x70eU]=0U;
        ram[0x33U]=1U;ram[0x45U]=1U;ram[0x754U]=0U;
        ram[0x783U]=0U;ram[0x703U]=0U;ram[0xdU]=0U;
        if(n<16U) {
            ram[0x700U]=speed[n%8U];ram[0x754U]=(unsigned char)(n/8U);
        } else if(n<24U) {
            ram[0x704U]=1U;ram[0x47dU]=(unsigned char)(n%2U);
            ram[0xceU]=(n&2U)!=0U?0x14U:0x13U;
            ram[0x1dU]=(n&4U)!=0U?1U:0U;ram[0x782U]=1U;
        } else if(n<32U) {
            ram[0x1dU]=1U;ram[0x704U]=n==24U?0U:1U;
            ram[0x782U]=n==26U?1U:0U;ram[0x9fU]=n==27U?0U:0xffU;
            if(n==28U) ram[0xdU]=0x80U;
            if(n==29U) ram[0x70eU]=1U;
            if(n==31U) {ram[0x1dU]=0U;ram[0x700U]=27U;}
        } else if(n<64U) {
            ram[0x1dU]=(unsigned char)((n/4U)%2U);
            ram[0x74eU]=(unsigned char)((n/8U)%2U);
            ram[0x700U]=(unsigned char)(n%4U==0U?24U:(n%4U==1U?25U:(n%4U==2U?32U:33U)));
            ram[0x703U]=(unsigned char)((n/2U)%2U);
            ram[0x33U]=(n&1U)!=0U?2U:1U;
            ram[0x45U]=n<48U?1U:2U;
        } else if(n<70U) {
            ram[0x1dU]=3U;ram[0x490U]=n<67U?0xffU:0U;
        } else if(n==70U) {
            ram[0xeU]=7U;ram[0x710U]=6U;
        } else if(n==71U) {
            ram[0x783U]=3U;
        } else {
            ram[0x700U]=0x21U;ram[0x45U]=2U;
        }
        return;
    }
    if(scenario>=37U) {
        unsigned char n;
        n=(unsigned char)(scenario-37U);ram[0x1dU]=3U;ram[0x70bU]=0U;
        ram[0x33U]=(unsigned char)(1U+(n/4U)%2U);
        ram[0x789U]=(unsigned char)((n/8U)%2U);
        ram[0x416U]=0xffU;
        ram[0x86U]=(n&1U)!=0U?0xfeU:2U;
        ram[0xceU]=(n/16U)%2U!=0U?0xffU:0x80U;
        if(scenario>=101U) {
            ram[0x490U]=(unsigned char)((scenario-101U)%4U);
            ram[0x789U]=(unsigned char)((scenario-101U)/4U);
        }
        return;
    }
    if(scenario<16U) {
        ram[0x1dU]=(unsigned char)(scenario%4U);
        ram[0x754U]=(unsigned char)((scenario/4U)%2U);
        ram[0x70bU]=(unsigned char)(scenario/8U);
    } else if(scenario<18U) {
        ram[0x1dU]=0U;ram[0x754U]=0U;
        ram[0x6fcU]=scenario==16U?1U:4U;
    } else if(scenario<34U) {
        unsigned char n;
        n=(unsigned char)(scenario-18U);ram[0x1dU]=1U;
        ram[0x9fU]=(n&1U)!=0U?0xffU:0U;
        ram[0x6fcU]=(n&2U)!=0U?0x80U:0U;ram[0xdU]=ram[0x6fcU];
        ram[0x704U]=(n&8U)!=0U?1U:0U;
        ram[0xceU]=(n&8U)!=0U?0x13U:0x80U;
        ram[0x708U]=(unsigned char)(ram[0xceU]+((n&4U)!=0U?0x20U:0U));
        if((n&4U)!=0U) ram[0x6fcU]|=1U;
    } else {
        ram[0x1dU]=scenario==35U?2U:1U;ram[0x704U]=1U;
        ram[0xceU]=0x14U;ram[0x6fcU]=2U;ram[0x9fU]=0xffU;
        if(scenario==36U) {ram[0xeU]=11U;ram[0x747U]=0xefU;ram[0xcU]=2U;}
    }
}
static int mysmb_player_movement_argument(const char *text)
{
    static const char prefix[]="--fixture=t33-movement=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>245U) return 0;
    return (int)value+1;
}
#endif
