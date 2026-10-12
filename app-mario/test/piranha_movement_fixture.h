#ifndef MYSMB_PIRANHA_MOVEMENT_FIXTURE_H
#define MYSMB_PIRANHA_MOVEMENT_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_piranha_movement_slot(unsigned int n)
{ return (unsigned char)((n&1U)*5U); }
static void mysmb_piranha_movement_fixture(unsigned char *r,unsigned int n)
{
    unsigned int i;unsigned char s;
    mysmb_actor_dispatch_fixture(r,26U+(n&1U));s=mysmb_piranha_movement_slot(n);
    for(i=0U;i<6U;++i)if(i!=s)r[0xfU+i]=0U;
    r[0x747U]=0U;
}
static void mysmb_piranha_movement_inputs(unsigned char *r,unsigned int n)
{
    static const unsigned char speeds[16]={1,1,255,1,255,1,1,1,1,1,1,0,128,127,1,254};
    static const unsigned char deltas[16]={0,0,0,0,0,0,32,33,224,223,255,64,64,64,33,0};
    unsigned char s,m,v,next,speed;
    s=mysmb_piranha_movement_slot(n);m=(unsigned char)((n/2U)%16U);v=(unsigned char)(n/32U);
    r[0x1eU+s]=(unsigned char)(m==0U?1U:0U);r[0x78aU+s]=(unsigned char)(m==1U?1U:0U);
    r[0xa0U+s]=(unsigned char)(m==3U || m==4U || m==15U?255U:0U);
    r[0x58U+s]=speeds[m];r[0x86U]=0x80U;r[0x6dU]=4U;
    r[0x87U+s]=(unsigned char)(0x80U+deltas[m]);r[0x6eU+s]=(unsigned char)(m==14U?3U:4U);
    r[9U]=(unsigned char)(v&1U);r[0x747U]=(unsigned char)((v/2U)&1U);
    r[0xcfU+s]=(unsigned char)(v&8U?0xffU:0x80U);
    speed=r[0xa0U+s]?speeds[m]:(unsigned char)(0U-speeds[m]);
    next=(unsigned char)(r[0xcfU+s]+speed);
    r[0x417U+s]=(unsigned char)(next+((v/4U)&1U));
    r[0x434U+s]=r[0x417U+s];r[0x3c5U+s]=0xc3U;r[0U]=0xa5U;
}
static int mysmb_piranha_movement_argument(const char *text)
{
    static const char prefix[]="--fixture=t41-piranha-movement=";
    unsigned int i,value,digits;
    for(i=0U;prefix[i]!='\0';++i)if(text[i]!=prefix[i])return 0;
    value=digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<4U){value=value*10U+(unsigned int)(text[i++]-'0');++digits;}
    if(!digits || text[i]!='\0' || value>=512U)return 0;
    return (int)value+1;
}
#endif
