#ifndef MYSMB_ENEMY_PAIR_FIXTURE_H
#define MYSMB_ENEMY_PAIR_FIXTURE_H
#include "normal_actor_fixture.h"
static unsigned char mysmb_enemy_pair_slot(unsigned int n)
{ return n >= 1008U ? 0U : 5U; }
static void mysmb_enemy_pair_fixture(unsigned char *r,unsigned int n)
{ mysmb_normal_actor_fixture(r,mysmb_enemy_pair_slot(n)==0U?0U:1U); }
static void mysmb_enemy_pair_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char ids[16]={0,1,2,5,6,7,8,12,13,14,15,16,17,18,20,21};
    static const unsigned char states[8]={0,4,6,0x80,0x84,0x20,0x26,0xa0};
    unsigned int s,variant;
    variant=n/64U;
    r[8U]=mysmb_enemy_pair_slot(n);r[9U]=1U;r[0x74eU]=1U;
    for(s=0U;s<6U;++s) {
        r[0xfU+s]=1U;r[0x16U+s]=0U;r[0x1eU+s]=0U;
        r[0x3d8U+s]=0U;r[0x491U+s]=0U;
        r[0x4b0U+s*4U]=0x40U;r[0x4b1U+s*4U]=0x80U;
        r[0x4b2U+s*4U]=0x50U;r[0x4b3U+s*4U]=0x90U;
        r[0x58U+s]=(unsigned char)(s*47U);r[0x46U+s]=(unsigned char)(s+1U);
        r[0x125U+s]=(unsigned char)(n+s);r[0xcfU+s]=0x80U;
    }
    r[0x1eU+5U]=states[n%8U];r[0x1eU+4U]=states[(n/8U)%8U];
    r[0x3aeU]=0x51U;r[0x3b9U]=0x82U;r[1U]=0xa5U;
    switch(variant) {
    case 1U:r[9U]=0U;break;
    case 2U:r[0x74eU]=0U;break;
    case 3U:r[0x1bU]=ids[n%16U];break;
    case 4U:r[0x3ddU]=0xffU;break;
    case 5U:for(s=0U;s<5U;++s)r[0xfU+s]=0U;break;
    case 6U:for(s=0U;s<5U;++s)r[0x16U+s]=ids[(n+s)%16U];break;
    case 7U:for(s=0U;s<5U;++s)r[0x3d8U+s]=1U;break;
    case 8U:for(s=0U;s<5U;++s){r[0x4b0U+s*4U]=0x70U;r[0x4b2U+s*4U]=0x80U;r[0x491U+s]=0xffU;}break;
    case 9U:for(s=0U;s<5U;++s)r[0x491U+s]=0xffU;break;
    case 10U:r[0x1bU]=5U;break;
    case 11U:r[0x1aU]=5U;break;
    case 12U:r[0x1bU]=14U;r[0x1aU]=18U;break;
    case 13U:r[0x1bU]=7U;r[0x1aU]=12U;break;
    case 14U:r[0x4c0U]=0xf8U;r[0x4c2U]=8U;break;
    case 15U:r[0x4c1U]=0xa0U;r[0x4c3U]=0xb0U;break;
    }
}
static int mysmb_enemy_pair_argument(const char *text)
{
    static const char prefix[]="--fixture=t42-enemy-pair=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0'&&text[i]<='9'&&digits<4U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits||text[i]!='\0'||value>=1024U)return 0;
    return (int)value+1;
}
#endif
