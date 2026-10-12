#ifndef MYSMB_PLAYER_ENEMY_CONTACT_FIXTURE_H
#define MYSMB_PLAYER_ENEMY_CONTACT_FIXTURE_H
#include "power_up_actor_fixture.h"
static void mysmb_player_enemy_contact_fixture(unsigned char *r,unsigned int n)
{ (void)n;mysmb_power_up_actor_fixture(r,28U);r[0x747U]=0U; }
static void mysmb_player_enemy_contact_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char ids[16]={0,1,2,5,6,7,8,12,13,14,15,16,17,18,20,0x33};
    static const unsigned char states[4]={0,4,0x80,0x20};
    static const unsigned char extra_ids[16]={0,5,6,7,8,12,13,14,17,18,20,0x15,0x21,0x2d,0x2e,0xff};
    unsigned int variant,extra;
    extra=n>=1024U?n-1024U:0U;
    variant=n>=1024U?0U:n/64U;
    r[8U]=5U;r[9U]=0U;r[0xeU]=8U;r[0x3d0U]=0U;r[0x3d1U]=0U;r[0x3ddU]=0U;
    r[0xb5U]=1U;r[0xceU]=0x80U;r[0xd4U]=0x80U;r[0x9fU]=1U;
    r[0x1bU]=ids[n%16U];r[0x23U]=states[(n/16U)%4U];
    r[0x4acU]=0x40U;r[0x4adU]=0x80U;r[0x4aeU]=0x50U;r[0x4afU]=0x90U;
    r[0x4c4U]=0x48U;r[0x4c5U]=0x80U;r[0x4c6U]=0x58U;r[0x4c7U]=0x90U;
    r[0x496U]=0U;r[0x79fU]=0U;r[0x79eU]=0U;r[0x791U]=0U;
    r[0x756U]=1U;r[0x74eU]=1U;r[0x744U]=0U;r[0x753U]=0U;
    r[0x78fU]=3U;r[0x484U]=0U;r[0x76aU]=(unsigned char)(n&1U);
    r[0x4bU]=1U;r[0x73U]=0U;r[0x8cU]=0x48U;r[0x6dU]=0U;r[0x86U]=0x40U;
    r[0x3adU]=0x40U;r[0x3aeU]=0x48U;r[0x300U]=0U;
    switch(variant) {
    case 1U:r[9U]=1U;break;
    case 2U:r[0x3d0U]=0xf0U;break;
    case 3U:r[0x3ddU]=1U;break;
    case 4U:r[0xeU]=7U;break;
    case 5U:r[0x4c4U]=0x60U;r[0x4c6U]=0x70U;r[0x496U]=0xffU;break;
    case 6U:r[0x496U]=1U;break;
    case 7U:r[0x79fU]=1U;break;
    case 8U:r[0x756U]=0U;r[0x9fU]=0xffU;break;
    case 9U:r[0xceU]=0x70U;r[0x9fU]=0U;break;
    case 10U:r[0x791U]=1U;r[0x9fU]=0xffU;break;
    case 11U:r[0x79eU]=8U;r[0x9fU]=0xffU;break;
    case 12U:r[0x4bU]=2U;r[0x3adU]=0x60U;r[0x86U]=0x60U;r[0x9fU]=0xffU;break;
    case 13U:r[0x78fU]=1U;r[0x756U]=2U;r[0x9fU]=0xffU;break;
    case 14U:r[0x78fU]=2U;r[0x9fU]=0xffU;break;
    case 15U:r[0x78fU]=0U;r[0x484U]=0xffU;r[0x791U]=0xffU;break;
    }
    if(n>=1024U) {
        r[0x1bU]=extra_ids[extra%16U];
        r[0x23U]=states[(extra/16U)%4U];
        r[0x79bU]=(unsigned char)(extra/64U);
        r[0x9fU]=0xffU;
        switch(extra/64U) {
        case 0U:r[0x74eU]=0U;break;
        case 1U:r[0x79bU]=0U;break;
        case 2U:r[0x79bU]=1U;break;
        case 3U:r[0x79bU]=2U;break;
        case 4U:r[0x3adU]=0x60U;r[0x4bU]=1U;break;
        case 5U:r[0x3adU]=0x60U;r[0x4bU]=2U;r[0x86U]=0x60U;break;
        case 6U:r[0xceU]=0xc8U;r[0xd4U]=0xe0U;r[0x9fU]=0U;break;
        case 7U:r[0x79eU]=8U;r[0x756U]=0U;break;
        }
        if(extra>=512U) {
            r[0x3adU]=0x40U;r[0x4bU]=2U;r[0x79eU]=0U;
        }
    }
}
static int mysmb_player_enemy_contact_argument(const char *text)
{
    static const char prefix[]="--fixture=t42-player-enemy-contact=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0'&&text[i]<='9'&&digits<4U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits||text[i]!='\0'||value>=1600U)return 0;
    return (int)value+1;
}
#endif
