#ifndef MYSMB_MISC_LIFETIME_FIXTURE_H
#define MYSMB_MISC_LIFETIME_FIXTURE_H
#include "scroll_fixture.h"
static void mysmb_misc_lifetime_fixture(unsigned char *ram,unsigned char n)
{
    static const unsigned char states[4]={1U,2U,0x2fU,0x81U};
    unsigned int i;
    /* The original pipe caller reaches ScrollHandler and then misc objects.
     * Its saved force yields nonzero scroll without modifying a mid-call state. */
    mysmb_scroll_fixture(ram,(unsigned char)((n&1U)!=0U?1U:0U));
    ram[0x747U]=n==41U?0xffU:0U;ram[0x6deU]=0xffU;
    ram[0x70bU]=1U;ram[0x716U]=1U;
    for(i=0U;i<9U;++i) {
        ram[0x2aU+i]=0U;ram[0x7aU+i]=7U;ram[0x93U+i]=0xffU;
        ram[0xc2U+i]=1U;ram[0xdbU+i]=0x70U;
        ram[0xacU+i]=(unsigned char)(4U+(n%3U));ram[0x440U+i]=0U;
        ram[0x423U+i]=0U;ram[0x64U+i]=0x10U;
        ram[0x6aeU+i]=4U;ram[0x4a2U+i]=7U;
        ram[0x6f3U+i]=(unsigned char)(0x20U+i*8U);
    }
    ram[0x72U]=7U;ram[0x8bU]=0xffU;ram[0xd3U]=0x90U;
    ram[0x4aU]=1U;ram[0x22U]=8U;
    if(n<36U) ram[0x2aU+n%9U]=states[n/9U];
    if(n>=37U) for(i=0U;i<9U;++i) {
        ram[0x2aU+i]=n==37U?2U:(n==38U?1U:states[i%4U]);
        if(n==40U) ram[0x2aU+i]=i==8U?0x7fU:(i==0U?0x30U:0U);
    }
    /* T44 S6: controlled parent-route graphics variants.  Keep the ordinary
     * MiscLoop entry and select only documented state/frame inputs. */
    if (n >= 42U && n <= 45U) {
        for (i = 0U; i < 9U; ++i) ram[0x2aU + i] = 0U;
        ram[0x2aU] = 1U;
        ram[0x00acU] = 0U;
        /* The root advances FrameCounter once before MiscLoop. */
        ram[9U] = (unsigned char)(((n - 42U) << 1U) - 1U);
    }
    if (n == 46U || n == 47U) {
        for (i = 0U; i < 9U; ++i) ram[0x2aU + i] = 0U;
        ram[0x2aU] = 2U;
        ram[9U] = (unsigned char)(n == 46U ? 0xffU : 0U);
    }
}
static int mysmb_misc_lifetime_argument(const char *text)
{
    static const char prefix[]="--fixture=t36-misc=";
    unsigned int i,value;
    for(i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    if(text[i]<'0'||text[i]>'9') return 0;
    value=(unsigned int)(text[i++]-'0');
    if(text[i]>='0'&&text[i]<='9') value=value*10U+(unsigned int)(text[i++]-'0');
    if(text[i]!='\0'||value>47U) return 0;
    return (int)value+1;
}
#endif
