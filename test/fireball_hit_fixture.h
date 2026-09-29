#ifndef MYSMB_FIREBALL_HIT_FIXTURE_H
#define MYSMB_FIREBALL_HIT_FIXTURE_H
/* Includes the admitted scan fixture: reach the hit root by real collision. */
#include "fireball_enemy_scan_fixture.h"
static void mysmb_fireball_hit_fixture(unsigned char *r,unsigned int n)
{ (void)n;mysmb_fireball_enemy_scan_fixture(r,0U); }
static void mysmb_fireball_hit_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char ids[16]={0,1,2,5,6,7,8,9,10,12,13,14,17,20,21,45};
    static const unsigned char ys[8]={0,1,0x78,0x80,0xe6,0xe7,0xf0,0xff};
    unsigned char s,v;
    v=(unsigned char)(n/16U);s=(unsigned char)((n&1U)?0U:4U);
    r[1U]=s;r[0x16U+s]=ids[n%16U];r[0x1eU+s]=(unsigned char)(n*13U);
    r[0xfU+s]=(unsigned char)(v>=16U?0x83U:1U);
    r[0x16U+3U]=(unsigned char)(v>=24U?2U:45U);
    r[0xcfU+s]=ys[v%8U];r[0x483U]=(unsigned char)(v<8U?0U:(v<24U?1U:2U));
    r[0x75fU]=(unsigned char)(v%8U);r[0x74eU]=(unsigned char)(v&1U);
    r[0x58U+3U]=0x31U;r[0xa0U+3U]=0x32U;r[0x434U+3U]=0x33U;
    r[0x58U+s]=0x41U;r[0xa0U+s]=0x42U;r[0x434U+s]=0x43U;r[0x6cbU]=0x55U;
}
static int mysmb_fireball_hit_argument(const char *text)
{
    static const char prefix[]="--fixture=t42-fireball-hit=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0'&&text[i]<='9'&&digits<3U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits||text[i]!='\0'||value>=512U)return 0;
    return (int)value+1;
}
#endif
