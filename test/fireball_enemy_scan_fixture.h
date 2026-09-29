#ifndef MYSMB_FIREBALL_ENEMY_SCAN_FIXTURE_H
#define MYSMB_FIREBALL_ENEMY_SCAN_FIXTURE_H
#include "entrance_fixture.h"
static unsigned char mysmb_fireball_enemy_scan_slot(unsigned int n)
{ return (unsigned char)(n & 1U); }
static void mysmb_fireball_enemy_scan_fixture(unsigned char *r,unsigned int n)
{
    unsigned char s;
    mysmb_entrance_fixture(r,0U);s=mysmb_fireball_enemy_scan_slot(n);
    r[0xeU]=8U;r[0x70bU]=1U;r[0x716U]=1U;r[0x756U]=2U;
    r[0x74eU]=1U;r[0x33U]=1U;r[0x70eU]=1U;
    r[0x24U]=0U;r[0x25U]=0U;r[0x24U+s]=1U;
    r[0x74U+s]=1U;r[0x8dU+s]=0x80U;r[0xd5U+s]=0x80U;
    r[0xbcU+s]=1U;r[0x4a0U+s]=7U;r[0x71aU]=1U;r[0x71cU]=0U;
    r[0x71bU]=1U;r[0x71dU]=0xffU;
}
/* Inputs applied only at a naturally reached root; never output/CPU patches. */
static void mysmb_fireball_enemy_scan_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char ids[16]={0,1,2,5,6,7,12,13,20,21,35,36,42,43,45,46};
    static const unsigned char states[8]={0,1,2,0x1f,0x20,0x40,0x80,0xff};
    unsigned int i,b;unsigned char s,id,variant;
    s=mysmb_fireball_enemy_scan_slot(n);id=ids[(n/2U)%16U];
    variant=(unsigned char)(n/32U);
    r[0x24U+s]=1U;r[9U]=0U;r[1U]=0xa5U;
    if(variant==28U)r[0x24U+s]=0U;
    if(variant==29U)r[0x24U+s]=0x80U;
    if(variant==30U)r[9U]=1U;
    for(i=0U;i<5U;++i){
        r[0xfU+i]=(unsigned char)(variant==26U?0U:1U);
        r[0x16U+i]=id;r[0x1eU+i]=states[variant%8U];
        r[0x3d8U+i]=(unsigned char)(variant==27U?1U:0U);
        r[0x87U+i]=0x80U;r[0x6eU+i]=1U;r[0xcfU+i]=0x80U;
        b=0x4b0U+i*4U;
        r[b]=(unsigned char)(variant>=8U&&variant<16U?0xb0U:0x78U);
        r[b+1U]=(unsigned char)(variant>=16U&&variant<24U?0xb0U:0x78U);
        r[b+2U]=(unsigned char)(r[b]+16U);r[b+3U]=(unsigned char)(r[b+1U]+16U);
    }
    if(variant==31U){r[0x1eU+4U]=0U;r[0xfU+4U]=0x83U;r[0x16U+3U]=45U;}
    b=0x4c8U+s*4U;r[b]=0x80U;r[b+1U]=0x80U;r[b+2U]=0x88U;r[b+3U]=0x88U;
    r[0x483U]=3U;r[0x75fU]=(unsigned char)(n%8U);
}
static int mysmb_fireball_enemy_scan_argument(const char *text)
{
    static const char prefix[]="--fixture=t42-fireball-enemy-scan=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0'&&text[i]<='9'&&digits<4U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits||text[i]!='\0'||value>=1024U)return 0;
    return (int)value+1;
}
#endif
