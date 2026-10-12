#ifndef MYSMB_PLATFORM_COLLISION_FIXTURE_H
#define MYSMB_PLATFORM_COLLISION_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_platform_collision_slot(unsigned int n)
{ return (unsigned char)((n&1U)*5U); }
static void mysmb_platform_collision_fixture(unsigned char *r,unsigned int n)
{
    unsigned int i;unsigned char s;
    mysmb_actor_dispatch_fixture(r,(n<1024U?74U:86U)+(n&1U));
    s=mysmb_platform_collision_slot(n);
    for(i=0U;i<6U;++i)if(i!=s)r[0xfU+i]=0U;
    r[0x747U]=0U;
}
static void mysmb_platform_collision_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char speeds[4]={0,1,0x80,0xff};
    static const unsigned char tops[16]={0x90,0x8b,0x8a,0x91,0x70,0x78,0x7c,0x7d,0x80,0x80,0x80,0x80,0x10,0xf8,0x30,0x80};
    unsigned int v,i,b,group,geom;unsigned char s,partner;
    s=mysmb_platform_collision_slot(n);partner=(unsigned char)(5U-s);
    v=(n%1024U)/2U;group=v/64U;geom=v%16U;
    r[8U]=s;r[0x747U]=0U;r[0x3d0U]=0U;r[0x3d1U]=0U;
    r[0xb5U]=1U;r[0xceU]=0x80U;r[0x9fU]=speeds[(v/16U)%4U];
    r[0x1dU]=2U;r[0x57U]=speeds[(v/16U)%4U];
    r[0x86U]=(unsigned char)v;r[0x6dU]=1U;r[0x490U]=0xffU;
    r[0x4acU]=0x40U;r[0x4adU]=0x80U;r[0x4aeU]=0x50U;r[0x4afU]=0x90U;
    for(i=0U;i<6U;++i) {
        r[0x1eU+i]=0U;r[0x16U+i]=(unsigned char)(n<1024U?37U:43U);
        r[0x3a2U+i]=0xa5U;r[0xcfU+i]=(unsigned char)(0x60U+i);
        b=0x4b0U+i*4U;r[b]=0x48U;r[b+1U]=tops[geom];
        r[b+2U]=0x68U;r[b+3U]=(unsigned char)(tops[geom]+8U);
        if(geom==4U)r[b+3U]=0x80U;
        if(geom==5U)r[b+3U]=0x83U;
        if(geom==6U)r[b+3U]=0x84U;
        if(geom==8U)r[b]=0x49U;
        if(geom==9U){r[b]=0x20U;r[b+2U]=0x48U;}
        if(geom==10U){r[b]=0x20U;r[b+2U]=0x49U;}
        if(geom==11U){r[b]=0x20U;r[b+2U]=0x4aU;}
        if(geom==14U){r[b]=0x70U;r[b+2U]=0x80U;}
        if(geom==15U){r[b]=0xf8U;r[b+2U]=8U;}
    }
    if(group==1U)r[0x747U]=1U;
    if(group==2U){if(n<1024U)r[0x1eU+s]=0x80U;else r[0x3d0U]=0xf0U;}
    if(group==3U){if(n&1U)r[0xceU]=0xd0U;else r[0xb5U]=0U;}
    if(n<1024U) {
        if(group==4U)r[0x3d0U]=0xf0U;
        if(group==5U||group==6U) {
            r[0x16U+s]=36U;r[0x1eU+s]=partner;
            if(group==6U){r[0x16U+partner]=44U;r[0x4b1U+partner*4U]=0x90U;r[0x4b3U+partner*4U]=0x98U;}
        }
        if(group==7U){r[0x4b1U+s*4U]=0x80U;r[0x4b3U+s*4U]=0x83U;}
    } else {
        if(group==4U)r[0x3d1U]=2U;
        if(group==5U)r[0x16U+s]=44U;
        if(group==6U){r[0x4b1U+s*4U]=0x10U;r[0x4b3U+s*4U]=0x18U;}
        if(group==7U){r[0x4b1U+s*4U]=0xa0U;r[0x4b3U+s*4U]=0xa8U;}
    }
    r[0U]=0xa5U;
}
static int mysmb_platform_collision_argument(const char *text)
{
    static const char prefix[]="--fixture=t42-platform-collision=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0'&&text[i]<='9'&&digits<4U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits||text[i]!='\0'||value>=2048U)return 0;
    return (int)value+1;
}
#endif
