#ifndef MYSMB_POWERUP_PICKUP_FIXTURE_H
#define MYSMB_POWERUP_PICKUP_FIXTURE_H
#include "power_up_actor_fixture.h"
static void mysmb_powerup_pickup_fixture(unsigned char *r,unsigned int n)
{ (void)n;mysmb_power_up_actor_fixture(r,28U);r[0x747U]=0U; }
static void mysmb_powerup_pickup_contact(unsigned char *r)
{
    r[9U]=0U;r[0xeU]=8U;r[0x3d0U]=0U;r[0x3d1U]=0U;r[0x3ddU]=0U;
    r[0xb5U]=1U;r[0xceU]=0x80U;r[0x23U]=0x80U;r[0x1bU]=0x2eU;
    r[0x4acU]=0x40U;r[0x4adU]=0x80U;r[0x4aeU]=0x50U;r[0x4afU]=0x90U;
    r[0x4c4U]=0x48U;r[0x4c5U]=0x80U;r[0x4c6U]=0x58U;r[0x4c7U]=0x90U;
}
static void mysmb_powerup_pickup_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char types[8]={0,1,2,3,4,127,128,255};
    static const unsigned char status[4]={0,1,2,255};
    r[0x39U]=types[n%8U];r[0x756U]=status[(n/8U)%4U];
    r[0x753U]=(unsigned char)((n/32U)&1U);r[0x74eU]=(unsigned char)(n/32U);
    r[0x744U]=0U;r[0x300U]=(unsigned char)(7U*(n/32U));r[0xfbU]=0x55U;
    r[0x3aeU]=0x48U;r[0xd4U]=0x80U;r[0x115U]=0xffU;r[0x131U]=0xffU;
    r[0x3c5U+5U]=3U;r[0x78aU+5U]=0x22U;r[0x6d8U+5U]=0x33U;
}
static int mysmb_powerup_pickup_argument(const char *text)
{
    static const char prefix[]="--fixture=t42-powerup-pickup=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0'&&text[i]<='9'&&digits<3U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits||text[i]!='\0'||value>=128U)return 0;
    return (int)value+1;
}
#endif
